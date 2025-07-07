#include <data/task.h>
#include <data/config.h>

namespace vertelien2 {
    Task::Task(){
        version = TASK_VERSION;
        GetUUID(uuid);
        jobs = std::vector<std::shared_ptr<Job>>();
        buffer_job_uuid = std::vector<char[36]>();
        memset(title, 0, sizeof(title));
        memset(description, 0, sizeof(description));
        memset(cronjobKey, 0, sizeof(cronjobKey));
        memset(multiKey, 0, sizeof(multiKey));
    }

    Task::~Task() {
        for (auto i : jobs) i = nullptr;
    }

    void Task::ToBinary(char* data) const {
        serialization::TaskSerialization::ToBinary(*this, data);
    }

    namespace serialization {
        static TaskSerialization::SerializationCaller s_caller = nullptr;
        static TaskSerialization::DeserializationCaller ds_caller = nullptr;

        void TaskSerialization::RegisterCallerHandle(SerializationCaller caller) {
            s_caller = caller;
        }
        void TaskSerialization::RegisterCallerHandle(DeserializationCaller caller) {
            ds_caller = caller;
        }

        uint32_t TaskSerialization::ToBinary(const Task& task, char*& ptr) {
            uint32_t size = GetSize(task);

            uint32_t gap = 0;
            ptr = (char*)malloc(size);
            memcpy(&ptr[gap], &task.version, sizeof(Version));
            gap += sizeof(task.version);
            memcpy(&ptr[gap], &task.uuid, sizeof(task.uuid));
            gap += sizeof(task.uuid);
            memcpy(&ptr[gap], &task.title, sizeof(task.title));
            gap += sizeof(task.title);
            memcpy(&ptr[gap], &task.description, sizeof(task.description));
            gap += sizeof(task.description);
            memcpy(&ptr[gap], &task.type, sizeof(task.type));
            gap += sizeof(task.type);
            memcpy(&ptr[gap], &task.cronjobKey, sizeof(task.cronjobKey));
            gap += sizeof(task.cronjobKey);
            memcpy(&ptr[gap], &task.multiKey, sizeof(task.multiKey));
            gap += sizeof(task.multiKey);
            uint32_t jobsSize = task.jobs.size();
            memcpy(&ptr[gap], &jobsSize, sizeof(uint32_t));
            gap += sizeof(uint32_t);
            for (int i = 0; i < jobsSize; i++) {
                memcpy(&ptr[gap], &task.jobs.at(i).get()->uuid, sizeof(task.uuid));
                gap += sizeof(task.uuid);
            }
            return size;
        }
        Task* TaskSerialization::ToData(uint32_t size, const char* ptr) {
            Task* task = new Task();
            uint32_t gap = 0;
            memcpy(&task->version, &ptr[gap], sizeof(Version));
            gap += sizeof(Version);
            memcpy(&task->uuid, &ptr[gap], sizeof(task->uuid));
            gap += sizeof(task->uuid);
            memcpy(&task->title, &ptr[gap], sizeof(task->title));
            gap += sizeof(task->title);
            memcpy(&task->description, &ptr[gap], sizeof(task->description));
            gap += sizeof(task->description);
            memcpy(&task->type, &ptr[gap], sizeof(task->type));
            gap += sizeof(task->type);
            memcpy(&task->cronjobKey, &ptr[gap], sizeof(task->cronjobKey));
            gap += sizeof(task->cronjobKey);
            memcpy(&task->multiKey, &ptr[gap], sizeof(task->multiKey));
            gap += sizeof(task->multiKey);
            uint32_t jobsSize = 0;
            memcpy(&jobsSize, &ptr[gap], sizeof(jobsSize));
            gap += sizeof(jobsSize);
            task->buffer_job_uuid = std::vector<char[36]>(jobsSize);
            for (int i = 0; i < jobsSize; i++) {
                memcpy(&task->buffer_job_uuid[i], &ptr[gap], sizeof(task->uuid));
                gap += sizeof(task->uuid);
            }
            return task;
        }
        uint32_t TaskSerialization::GetSize(const Task& task) {
            uint32_t size = 0;
            size += sizeof(Version);
            size += sizeof(task.uuid);
            size += sizeof(task.title);
            size += sizeof(task.description);
            size += sizeof(uint32_t);
            size += sizeof(task.cronjobKey);
            size += sizeof(task.multiKey);
            size += sizeof(uint32_t);
            for (int i = 0; i < task.jobs.size(); i++) {
                size += sizeof(task.uuid);
            }
            return size;
        }

        uint32_t TaskSerialization::ToBinary_Whole(const Task &task, char *&ptr) {
            return 0;
        }
        Task* TaskSerialization::ToData_Whole(uint32_t size, const char *ptr) {

        }
        uint32_t TaskSerialization::GetSize_Whole(const Task &task) {
            uint32_t size = 0;
            size += sizeof(Version);
            size += sizeof(task.uuid);
            size += sizeof(task.title);
            size += sizeof(task.description);
            size += sizeof(uint32_t);
            size += sizeof(task.cronjobKey);
            size += sizeof(task.multiKey);
            size += sizeof(uint32_t);
            for (int i = 0; i < task.jobs.size(); i++) {
                size += JobSerialization::GetSize(*task.jobs.at(i).get());
            }
            return size;
        }
    }
}