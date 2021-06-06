#include <gtest/gtest.h>
#include <DeepTextReplace/ParsedFiles.hpp>

using std::string;

TEST(ParsedFiles, DISABLED_concurrencyEditFiles) {  // NOLINT
    // TODO (implement concurrencyEditFiles use cases)
}

TEST(ParsedFiles, DISABLED_file_descriptor_limit) {  // NOLINT
    // TODO (check) file descriptor limit
}

TEST(ParsedFiles, DISABLED_threads_limit) {  // NOLINT
    // TODO (check) file threads limit
}

TEST(ParsedFiles, replaceByTemplates_multiple_replaces) {  // NOLINT
    std::string expected{"text dolorem, text dolorem"};
    auto patterns = std::make_shared<std::map<string, string>>();
    patterns->try_emplace("ipsum lorem", "dolorem");

    auto result = dtr::replaceByTemplates("text ipsum lorem, text ipsum lorem", patterns);

    ASSERT_EQ(result, expected);
}

TEST(ParsedFiles, DISABLED_editFileByTemplates) {  // NOLINT
    // TODO (implement editFileByTemplates use cases)
}
