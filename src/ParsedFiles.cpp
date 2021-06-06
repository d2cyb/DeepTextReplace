#include "DeepTextReplace/ParsedFiles.hpp"

namespace dtr {
using std::string;

auto replaceByTemplates(const string &line, const std::shared_ptr<std::map<std::string, std::string>> templates)
    -> string {
    string tmpString = line;
    for (auto it = templates->cbegin(); it != templates->end(); ++it) {
        tmpString = regex_replace(line, std::regex{it->first}, it->second);
    }

    return tmpString;
}

void editFileByTemplates(const string &&filePath, const std::shared_ptr<std::map<std::string, std::string>> patterns) {
    string outputFilePath = filePath + "~";
    std::ifstream searchFileStream{filePath};
    std::ofstream outFileStream{outputFilePath};

    string line;
    for (size_t lineIndex{1}; getline(searchFileStream, line); ++lineIndex) {
        line = replaceByTemplates(line, patterns);
        outFileStream << line << '\n';
    }

    std::filesystem::remove(filePath);
    std::filesystem::rename(outputFilePath, filePath);
}

void concurrencyEditFiles(const string &rootPath, const std::shared_ptr<std::map<std::string, std::string>> patterns,
                          size_t threadsCount) {
    Semaphore maxJobs(threadsCount);

    std::vector<std::future<void>> tasks;
    for (const auto &entry : std::filesystem::recursive_directory_iterator(std::filesystem::path{rootPath})) {
        tasks.emplace_back(std::async([entry, &maxJobs, &patterns] {
            std::scoped_lock w(maxJobs);

            if (std::filesystem::is_regular_file(entry) == true) {
                editFileByTemplates(entry.path().c_str(), patterns);
            }
        }));
    }

    for (auto &&task : tasks) {
        task.get();
    }
}

}  // namespace dtr
