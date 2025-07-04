#pragma once
#include <vector>
#include <memory>

#include "version.h"
#include "job.h"

namespace vertelien2 {
    struct Task {
        enum class TaskType {
            NONE = 0,
            SETUP = 1,
            CRONJOB = 2,
            MULTI = 4
        };

        Version version;
        int index;
        char uuid[36];
        char title[128];
        char description[256];
        TaskType type;
        char cronjobKey[64];
        char multiKey[64];
        std::vector<std::shared_ptr<Job>> jobs;
    };
}
