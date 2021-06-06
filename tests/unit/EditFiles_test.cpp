#include <gtest/gtest.h>
#include <DeepTextReplace/EditFiles.hpp>

using std::string;

TEST(EditFiles, DISABLED_concurrencyEditFiles) {  // NOLINT
    // TODO (implement concurrencyEditFiles use cases)
}

TEST(EditFiles, DISABLED_file_descriptor_limit) {  // NOLINT
    // TODO (check) file descriptor limit
}

TEST(EditFiles, DISABLED_threads_limit) {  // NOLINT
    // TODO (check) file threads limit
}

TEST(EditFiles, replaceByTemplates_multiple_replaces) {  // NOLINT
    std::string expected{"text dolorem, text dolorem"};
    auto patterns = std::make_shared<std::map<string, string>>();
    patterns->try_emplace("ipsum lorem", "dolorem");

    auto result = dtr::replaceByTemplates("text ipsum lorem, text ipsum lorem", patterns);

    ASSERT_EQ(result, expected);
}

TEST(EditFiles, DISABLED_editFileByTemplates) {  // NOLINT
    // TODO (implement editFileByTemplates use cases)
}
