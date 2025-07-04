#pragma once
#include <memory>
#include <vector>

#include "task.h"
#include "version.h"

namespace vertelien2 {
    struct Project {
        Version version;
        std::vector<std::shared_ptr<Task>> tasks;
    };
}