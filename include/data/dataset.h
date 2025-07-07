#pragma once
#include <cstdint>
#include <vector>

#include "version.h"

namespace vertelien2 {
    struct Dataset {
        /// Describe raw data type casting
        enum class ArgType {
            RAW = 0,
            STRING = 1,
            INTEGER = 2,
            FLOAT = 3,
            BOOLEAN = 4,
        };

        Version version{0, 0, 1};
        char uuid[36]{};
        std::vector<std::pair<std::pair<ArgType, uint32_t>, void*>> args;

        Dataset();
        void ToBinary(char* data) const;
    };

    namespace serialization {
        struct DatasetSerialization {
            static uint32_t ToBinary(const Dataset& dataset, char*& ptr);
            static Dataset* ToData(uint32_t size, const char* ptr);
            static uint32_t GetSize(const Dataset& dataset);
        };
    }
}