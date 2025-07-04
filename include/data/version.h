#pragma once
#include <string>

namespace vertelien2 {
    /// Simple version info structure
    /// Contain major, minor and patch number
    struct Version {
        int major;
        int minor;
        int patch;

        std::string to_string()
        {
            std::string r = std::to_string(major);
            r += ".";
            r += std::to_string(minor);
            r += ".";
            r += std::to_string(patch);
            return r;
        }
        char* to_char() {
            return to_string().data();
        }
        bool operator==(const Version& rhs) const {
            return major == rhs.major && minor == rhs.minor && patch == rhs.patch;
        }
        bool operator!=(const Version& rhs) const {
            return major != rhs.major || minor != rhs.minor || patch != rhs.patch;
        }
    };
}