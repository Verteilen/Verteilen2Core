#include <data/job.h>
#include <data/config.h>

namespace vertelien2 {
    Job::Job(){
        version = JOB_VERSION;
        GetUUID(uuid);
        category = Category::EXECUTE;
        subCategory.execute = Execute::JAVASCRIPT;
        script = "";
        args = std::vector<std::pair<std::pair<ArgType, uint32_t>, void*>>();
    }

    void Job::ToBinary(char* data) const {
        serialization::JobSerialization::ToBinary(*this, data);
    }

    namespace serialization {
        uint32_t JobSerialization::ToBinary(const Job& job, char*& ptr) {
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
        Job* JobSerialization::ToData(uint32_t size, const char* ptr) {
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
        uint32_t JobSerialization::GetSize(const Job& job) {
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
    }
}