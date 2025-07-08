#pragma once
#include <cstdint>
#include <cstring>
#include <vector>

extern char **environ;

namespace vertelien2 {
    /// You can use this to pull the environment string <br />
    /// Leave the name empty for pull all
    /// @param name The name of the environment variable
    /// @return The result environment variable string, It will have ':' character as seperator
    inline std::string getenv(const char* name = "") {
        if (strlen(name) == 0) {
            std::string r = std::string();
            char **s = environ;
            for (; *s; s++) {
                r += *s;
                r += ":";
            }
            r.pop_back();
            return std::move(r);
        }
        if (std::getenv(name)) return std::string(std::getenv(name));
        return std::string();
    }

    /// Base on the string symbol input, split the string into multiple string <br />
    /// You can think this method works like javascript string split
    /// @param content The content string
    /// @param sym The seperator, default is ':'
    /// @return The list of string which just getting split
    inline std::vector<std::string> split(std::string content, char sym = ':') {
        std::vector<std::string> d = std::vector<std::string>();
        if (content.size() == 0) return d;
        std::string target = std::string();
        for (uint32_t i = 0; i < content.size(); i++) {
            if (content[i] == sym) {
                d.push_back(std::string(target));
                target = "";
            }else {
                target += content[i];
            }
        }
        d.push_back(std::string(target));
        return std::move(d);
    }


    inline std::string GetEnvironment(const char* path, const char* default_value) {
        std::string all = getenv();
        std::vector<std::string> all_split = split(all, ':');
        for (auto i = all_split.begin(); i != all_split.end(); i++) {
            std::vector<std::string> target = split((*i), '=');
            if (target.size() == 2) {
                if (strcmp(target.at(0).c_str(), path) == 0) {
                    return target.at(1);
                }
            }
        }
        return default_value;
    }
}