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
        static JobSerialization::SerializationCaller s_caller = nullptr;
        static JobSerialization::DeserializationCaller ds_caller = nullptr;

        void JobSerialization::RegisterCallerHandle(SerializationCaller caller) {
            s_caller = caller;
        }
        void JobSerialization::RegisterCallerHandle(DeserializationCaller caller) {
            ds_caller = caller;
        }

        uint32_t JobSerialization::ToBinary(const Job& job, char*& ptr) {
            uint32_t size = GetSize(job);
            uint32_t scriptSize = job.script.size();

            uint32_t offset = 0;
            ptr = (char*)malloc(size);
            memcpy(&ptr[offset], &job.version, sizeof(Version));
            offset += sizeof(job.version);
            memcpy(&ptr[offset], &job.uuid, sizeof(job.uuid));
            offset += sizeof(job.uuid);
            memcpy(&ptr[offset], &job.category, sizeof(job.category));
            offset += sizeof(job.category);
            memcpy(&ptr[offset], &job.subCategory, sizeof(job.subCategory));
            offset += sizeof(job.subCategory);
            memcpy(&ptr[offset], &scriptSize, sizeof(uint32_t));
            offset += sizeof(uint32_t);
            memcpy(&ptr[offset], job.script.c_str(), scriptSize);
            offset += scriptSize;
            for (int i = 0; i < job.args.size(); i++) {
                memcpy(&ptr[offset], &job.args.at(i).first.first, sizeof(uint32_t));
                offset += sizeof(uint32_t);
                memcpy(&ptr[offset], &job.args.at(i).first.second, sizeof(uint32_t));
                offset += sizeof(uint32_t);
                memcpy(&ptr[offset], &job.args.at(i).second, job.args.at(i).first.second);
                offset += job.args.at(i).first.second;
            }
            return size;
        }
        Job* JobSerialization::ToData(uint32_t size, const char* ptr) {
            Job* job = new Job();
            uint32_t offset = 0;
            memcpy(&job->version, &ptr[offset], sizeof(Version));
            offset += sizeof(Version);
            memcpy(&job->uuid, &ptr[offset], sizeof(job->uuid));
            offset += sizeof(job->uuid);
            memcpy(&job->category, &ptr[offset], sizeof(job->category));
            offset += sizeof(job->category);
            memcpy(&job->subCategory, &ptr[offset], sizeof(job->subCategory));
            offset += sizeof(job->subCategory);
            uint32_t scriptSize = 0;
            memcpy(&scriptSize, &ptr[offset], sizeof(uint32_t));
            offset += sizeof(uint32_t);
            char content[scriptSize];
            memcpy(&content, &ptr[offset], scriptSize);
            offset += scriptSize;
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

        uint32_t JobSerialization::ToBinary_Whole(const Job &job, char *&ptr, uint32_t &offset) {
            return 0;
        }

        Job* JobSerialization::ToData_Whole(uint32_t size, const char *ptr, uint32_t &offset) {
            return nullptr;
        }
    }
}