#include <cstdint>
#include <sstream>
#include <string>
#include <filesystem>
#include <gtest/gtest.h>
#include "DeepTextReplace/Settings.hpp"

using dtr::Settings;
using std::string;

const string testSettingsFilePath = "./tests/unit/fixtures/settings.toml";

// Количество потоков на парсинг файлов
TEST(Settings, getWorkThreadsCount_parse) {  // NOLINT
    std::istringstream settingsFileStream{"[streams]\ncount = 10"};
    uint32_t expect = 10;

    Settings settings{std::move(settingsFileStream)};
    auto result = settings.getWorkThreadsCount();

    ASSERT_EQ(result, expect);
}

TEST(Settings, getWorkThreadsCount_negative_value) {  // NOLINT
    std::istringstream settingsFileStream{"[streams]\ncount = -10"};
    uint32_t expect = std::thread::hardware_concurrency();

    Settings settings{std::move(settingsFileStream)};
    auto result = settings.getWorkThreadsCount();

    ASSERT_EQ(result, expect);
}

TEST(Settings, getWorkThreadsCount_zero_value) {  // NOLINT
    std::istringstream settingsFileStream{"[streams]\ncount = 0"};
    uint32_t expect = std::thread::hardware_concurrency();

    Settings settings{std::move(settingsFileStream)};
    auto result = settings.getWorkThreadsCount();

    ASSERT_EQ(result, expect);
}

TEST(Settings, getWorkThreadsCount_default) {  // NOLINT
    std::istringstream settingsFileStream{};
    uint32_t expect = std::thread::hardware_concurrency();

    Settings settings{std::move(settingsFileStream)};
    auto result = settings.getWorkThreadsCount();

    ASSERT_EQ(result, expect);
}

TEST(Settings, getWorkThreadsCount_wrong_format_value) {  // NOLINT
    std::istringstream settingsFileStream{"[streams]\ncount = value"};
    uint32_t expect = std::thread::hardware_concurrency();

    Settings settings{std::move(settingsFileStream)};
    auto result = settings.getWorkThreadsCount();

    ASSERT_EQ(result, expect);
}

TEST(Settings, getWorkThreadsCount_wrong_format_settings) {  // NOLINT
    std::istringstream settingsFileStream{"[streams]\ncount"};
    uint32_t expect = std::thread::hardware_concurrency();

    Settings settings{std::move(settingsFileStream)};
    auto result = settings.getWorkThreadsCount();

    ASSERT_EQ(result, expect);
}

// Адрес корневой директории с файлами и папками
TEST(Settings, getRootDirPath_parse) {  // NOLINT
    std::istringstream settingsFileStream{"[directory]\nroot = \"test_directory/test_path\""};
    auto expect = "test_directory/test_path";

    Settings settings{std::move(settingsFileStream)};
    auto result = settings.getRootDirPath();

    ASSERT_EQ(result, expect);
}

TEST(Settings, getRootDirPath_default) {  // NOLINT
    std::istringstream settingsFileStream{};
    string expect = std::filesystem::current_path();

    Settings settings{std::move(settingsFileStream)};
    auto result = settings.getRootDirPath();

    ASSERT_EQ(result, expect);
}

TEST(Settings, getRootDirPath_wrong_format) {  // NOLINT
    std::istringstream settingsFileStream{"[directory]\ncount = 1"};
    string expect = std::filesystem::current_path();

    Settings settings{std::move(settingsFileStream)};
    auto result = settings.getRootDirPath();

    ASSERT_EQ(result, expect);
}


// Перечисление шаблонов и их замен (неограниченное количество)
TEST(Settings, getTemplates_wrong_format) {  // NOLINT
    std::istringstream settingsFileStream{"[templates]\n\"<%COLOR%>\" \"BLACK\""};

    Settings settings{std::move(settingsFileStream)};
    auto templates = settings.getTemplates();

    ASSERT_THROW(templates->at("<%COLOR%>"), std::out_of_range);
}

TEST(Settings, getTemplates_parse_ignore_duplicate_store_first) {  // NOLINT
    std::istringstream settingsFileStream{
        "[templates]\n"
        "\"<%COLOR%>\" = \"BLACK\"\n"
        "\"<%COLOR%>\" = \"BLACK2\""};
    string expected = "BLACK";

    Settings settings{std::move(settingsFileStream)};
    auto templates = settings.getTemplates();
    string result = templates->at("<%COLOR%>");

    ASSERT_STREQ(result.c_str(), expected.c_str());
}

TEST(Settings, DISABLED_getTemplates_config_keywords) {  // NOLINT
    // TODO (implement) check next parameters keys
    // streams
    // count
    // directory
    // root
    // templates
    // " = "
    // "="
    // "<%COLOR\'s%>
    // key - two or more words
    // value -two or more words
    // key - contains regexp anchors
    // value - contains regexp anchors

    ASSERT_EQ(true, false);
}
