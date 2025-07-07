#pragma once
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
        char uuid[36]{};
        Category category;
        SubCategory subCategory{0};
        std::string script;
        /// The job arguments <br />
        /// It's kinda like command parameters <br />
        /// The data which require for the command
        std::vector<std::pair<std::pair<ArgType, uint32_t>, void*>> args;

        Job();
        void ToBinary(char* data) const;
    };

    namespace serialization {
        struct JobSerialization {
            typedef void (*SerializationCaller)(const char* data);
            typedef void (*DeserializationCaller)(const Job& job);
            static void RegisterCallerHandle(SerializationCaller caller);
            static void RegisterCallerHandle(DeserializationCaller caller);

            static uint32_t ToBinary(const Job& job, char*& ptr);
            static Job* ToData(uint32_t size, const char* ptr);
            static uint32_t GetSize(const Job& job);
        };
    }
}
