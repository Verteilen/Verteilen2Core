#pragma once
#include <memory>
#include <vector>

#include "task.h"
#include "version.h"

namespace vertelien2 {
    struct Project {
        Version version;
        char uuid[36]{};
        char title[64]{};
        char description[256]{};
        /// The dataset binding target
        char binder[36]{};
        std::vector<std::shared_ptr<Task>> tasks;
        std::vector<char[36]> buffer_task_uuid;

        Project();
        ~Project();
        void ToBinary(char* data) const;
    };

    namespace serialization {
        struct ProjectSerialization {
            typedef void (*SerializationCaller)(const char* data);
            typedef void (*DeserializationCaller)(const Project& project);
            static void RegisterCallerHandle(SerializationCaller caller);
            static void RegisterCallerHandle(DeserializationCaller caller);

            static uint32_t ToBinary(const Project& project, char*& ptr);
            static Project* ToData(uint32_t size, const char* ptr);
            static uint32_t GetSize(const Project& project);

            static uint32_t ToBinary_Whole(const Project& project, char*& ptr);
            static Project* ToData_Whole(uint32_t size, const char* ptr);
            static uint32_t GetSize_Whole(const Project& project);
        };
    };
}