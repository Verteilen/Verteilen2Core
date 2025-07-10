#pragma once
#include <vector>
#include <memory>

#include "version.h"
#include "job.h"

namespace vertelien2 {
    namespace serialization {
        struct TaskSerialization;
    }

    struct Task {
        friend serialization::TaskSerialization;
        enum class TaskType {
            NONE = 0,
            SETUP = 1,
            CRONJOB = 2,
            MULTI = 4
        };

        Version version{0, 0, 1};
        char uuid[36]{};
        char title[64]{};
        char description[256]{};
        TaskType type = TaskType::NONE;
        char cronjobKey[64]{};
        char multiKey[64]{};
        std::vector<std::shared_ptr<Job>> jobs;
        std::vector<char[36]> buffer_job_uuid;

        Task();
        ~Task();
        void ToBinary(char* data) const;
    };

    namespace serialization {
        struct TaskSerialization {
            typedef void (*SerializationCaller)(const char* data);
            typedef void (*DeserializationCaller)(const Task& task);
            static void RegisterCallerHandle(SerializationCaller caller);
            static void RegisterCallerHandle(DeserializationCaller caller);

            static uint32_t ToBinary(const Task& task, char*& ptr);
            static Task* ToData(uint32_t size, const char* ptr);
            static uint32_t GetSize(const Task& task);

            static uint32_t ToBinary_Whole(const Task &task, char*& ptr, uint32_t& offset);
            static Task* ToData_Whole(uint32_t size, const char* ptr, uint32_t& offset);
            static uint32_t GetSize_Whole(const Task &task);
        };
    }
}
