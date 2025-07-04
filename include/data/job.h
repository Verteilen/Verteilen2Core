#pragma once
#include <vector>
#include <string>

#include "version.h"

namespace vertelien2 {
    /// The action descriptor,
    /// cluster will send this to compute node to do what it says
    struct Job {
        /// Describe raw data type casting
        enum class ArgType {
            RAW,
            STRING,
            INTEGER,
            FLOAT,
            BOOLEAN,
        };

        enum class Category {
            EXECUTE,
            CONDITION
        };

        enum class SubCategory_Execute {

        };

        enum class SubCategory_Condition {

        };

        Version version;
        /// The uuid for the job <br />
        /// During the process, this will replace by the runtime uuid <br />
        /// In order to know the source running process target
        char uuid[36];
        Category category;
        union type {
            SubCategory_Execute execute;
            SubCategory_Condition condition;
        };
        std::string script;
        /// The job arguments <br />
        /// It's kinda like command parameters <br />
        /// The data which require for the command
        std::vector<std::pair<ArgType, void*>> args;
    };
}
