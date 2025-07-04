#pragma once
#include <iostream>
#include <cstdint>
#include <cstring>
#include <vector>
#include <string>

#include "../utility/uuid.h"
#include "version.h"

namespace vertelien2 {
    /// The action descriptor,
    /// cluster will send this to compute node to do what it says
    struct Job {
        /// Describe raw data type casting
        enum class ArgType {
            RAW = 0,
            STRING = 1,
            INTEGER = 2,
            FLOAT = 3,
            BOOLEAN = 4,
        };

        enum class Category {
            EXECUTE = 0,
            CONDITION = 1
        };

        enum class Execute {
            JAVASCRIPT = 0
        };

        enum class Condition {
            JAVASCRIPT = 0
        };

        union SubCategory {
            int32_t index;
            Execute execute;
            Condition condition;
        };

        Version version;
        /// The uuid for the job <br />
        /// During the process, this will replace by the runtime uuid <br />
        /// In order to know the source running process target
        char uuid[36];
        Category category;
        SubCategory subCategory;
        std::string script;
        /// The job arguments <br />
        /// It's kinda like command parameters <br />
        /// The data which require for the command
        std::vector<std::pair<std::pair<ArgType, uint32_t>, void*>> args;

        Job() {
            version = {0, 0, 1};
            GetUUID(uuid);
            category = Category::EXECUTE;
            subCategory.execute = Execute::JAVASCRIPT;
            script = "";
            args = std::vector<std::pair<std::pair<ArgType, uint32_t>, void*>>();
        }
    };

    namespace serialization {
        struct JobSerialization {
            static uint32_t ToBinary(const Job& job, char*& ptr) {
                uint32_t size = GetSize(job);
                uint32_t scriptSize = job.script.size();

                uint32_t gap = 0;
                ptr = (char*)malloc(size);
                memcpy(&ptr[gap], &job.version, sizeof(Version));
                gap += sizeof(job.version);
                memcpy(&ptr[gap], &job.uuid, sizeof(job.uuid));
                gap += sizeof(job.uuid);
                memcpy(&ptr[gap], &job.category, sizeof(job.category));
                gap += sizeof(job.category);
                memcpy(&ptr[gap], &job.subCategory, sizeof(job.subCategory));
                gap += sizeof(job.subCategory);
                memcpy(&ptr[gap], &scriptSize, sizeof(uint32_t));
                gap += sizeof(uint32_t);
                memcpy(&ptr[gap], job.script.c_str(), scriptSize);
                gap += scriptSize;
                for (int i = 0; i < job.args.size(); i++) {
                    memcpy(&ptr[gap], &job.args.at(i).first.first, sizeof(uint32_t));
                    gap += sizeof(uint32_t);
                    memcpy(&ptr[gap], &job.args.at(i).first.second, sizeof(uint32_t));
                    gap += sizeof(uint32_t);
                    memcpy(&ptr[gap], &job.args.at(i).second, job.args.at(i).first.second);
                    gap += job.args.at(i).first.second;
                }
                return size;
            }
            static Job* ToData(const uint32_t size, const char* ptr) {
                Job* job = new Job();
                uint32_t gap = 0;
                memcpy(&job->version, &ptr[gap], sizeof(Version));
                gap += sizeof(Version);
                memcpy(&job->uuid, &ptr[gap], sizeof(job->uuid));
                gap += sizeof(job->uuid);
                memcpy(&job->category, &ptr[gap], sizeof(job->category));
                gap += sizeof(job->category);
                memcpy(&job->subCategory, &ptr[gap], sizeof(job->subCategory));
                gap += sizeof(job->subCategory);
                uint32_t scriptSize = 0;
                memcpy(&scriptSize, &ptr[gap], sizeof(uint32_t));
                gap += sizeof(uint32_t);
                char content[scriptSize];
                memcpy(&content, &ptr[gap], scriptSize);
                gap += scriptSize;
                job->script = std::string(content, scriptSize).c_str();
                return job;
            }
            static uint32_t GetSize(const Job& job) {
                uint32_t size = 0;
                size += sizeof(Version);
                size += sizeof(job.uuid);
                size += sizeof(job.category);
                size += sizeof(job.subCategory);
                size += sizeof(uint32_t);
                size += job.script.size();
                for (int i = 0; i < job.args.size(); i++) {
                    size += sizeof(uint32_t);
                    size += sizeof(uint32_t);
                    size += job.args.at(i).first.second;
                }
                return size;
            }
        };
    }
}
