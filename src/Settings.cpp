#include "DeepTextReplace/Settings.hpp"

namespace dtr {
using std::string;

auto Settings::getWorkThreadsCount() const -> uint32_t {
    int count = this->defaultThreadsCount;

    auto found = this->streamsConfig.find("count");
    if (found != this->streamsConfig.end()) {
        try {
            int value = std::stoi(found->second);
            if (value > 0) {
                count = value;
            }
        } catch (std::logic_error& error) {
            std::cout << "Streams count parse error at " << error.what() << ".\n"
                      << "Set default value - 1" << std::endl;
        }
    }

    return count;
}

auto Settings::getRootDirPath() const -> string {
    auto found = this->fileSystemConfig.find("root");
    if (found != this->fileSystemConfig.end()) {
        return found->second;
    }
    return this->defaultRootPath;
}

auto Settings::getTemplates() const -> std::shared_ptr<std::map<std::string, std::string>> {
    return this->templates;
}

auto Settings::parseSettingsFileStream(std::istream& settingsFileStream) -> void {
    std::map<std::string, std::string>* currentConfigCategory = nullptr;
    for (string configFileLine; std::getline(settingsFileStream, configFileLine);) {
        if (configFileLine == STREAMS_CATALOG_HEADER) {
            currentConfigCategory = &streamsConfig;
            continue;
        } else if (configFileLine == DIRECTORY_CATALOG_HEADER) {
            currentConfigCategory = &fileSystemConfig;
            continue;
        } else if (configFileLine == TEMPLATES_CATALOG_HEADER) {
            currentConfigCategory = templates.get();
            continue;
        }

        if (currentConfigCategory != nullptr) {
            parseSettingsCategory(configFileLine, *currentConfigCategory);
        }
    }
}

auto Settings::parseSettingsCategory(const std::string& keyValueLine, std::map<std::string, std::string>& configMap)
    -> void {
    std::stringstream settingsValueStream;

    string key;
    string delimiter;
    string value{""};

    settingsValueStream << keyValueLine;
    settingsValueStream >> key >> delimiter >> value;

    if (key != "" && delimiter == "=" && value != "") {
        key.erase(std::remove(key.begin(), key.end(), '\"'), key.end());
        value.erase(std::remove(value.begin(), value.end(), '\"'), value.end());

        configMap.try_emplace(key, value);
    }
}

}  // namespace dtr
