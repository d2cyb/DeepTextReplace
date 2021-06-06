#ifndef DEEP_TEXT_REPLACE_SETTINGS_HPP
#define DEEP_TEXT_REPLACE_SETTINGS_HPP
#include <algorithm>
#include <cstdint>
#include <filesystem>
#include <iostream>
#include <fstream>
#include <map>
#include <memory>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <thread>

namespace dtr {

/**
 * @brief Settings file parser
 */
class Settings {
 private:
    const std::string STREAMS_CATALOG_HEADER = "[streams]";
    const std::string DIRECTORY_CATALOG_HEADER = "[directory]";
    const std::string TEMPLATES_CATALOG_HEADER = "[templates]";

    const uint32_t defaultThreadsCount = std::thread::hardware_concurrency();
    std::string defaultRootPath;
    std::map<std::string, std::string> streamsConfig{};
    std::map<std::string, std::string> fileSystemConfig{};
    std::shared_ptr<std::map<std::string, std::string>> templates;
    std::set<std::string> categoriesHeaders{STREAMS_CATALOG_HEADER, DIRECTORY_CATALOG_HEADER, TEMPLATES_CATALOG_HEADER};

 public:
    explicit Settings(std::istream&& settingsFileStream)
        : defaultRootPath{std::filesystem::current_path()}
        , templates{std::make_shared<std::map<std::string, std::string>>()} {
        this->parseSettingsFileStream(settingsFileStream);
    };

    explicit Settings(const std::string& settingsFilePath) : Settings(std::ifstream(settingsFilePath)) {
    }

    [[nodiscard]] auto getWorkThreadsCount() const -> uint32_t;
    [[nodiscard]] auto getRootDirPath() const -> std::string;
    [[nodiscard]] auto getTemplates() const -> std::shared_ptr<std::map<std::string, std::string>>;

 private:
    auto parseSettingsFileStream(std::istream& settingsFileStream) -> void;
    auto parseSettingsCategory(const std::string& line, std::map<std::string, std::string>& configMap) -> void;
};

}  // namespace dtr

#endif  // DEEP_TEXT_REPLACE_SETTINGS_HPP
