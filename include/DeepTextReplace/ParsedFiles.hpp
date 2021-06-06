#ifndef DEEP_TEXT_REPLACE_PARSED_FILES_HPP
#define DEEP_TEXT_REPLACE_PARSED_FILES_HPP

#include <string>
#include <map>
#include <filesystem>
#include <regex>
#include <iostream>
#include <fstream>
#include <future>

#include "DeepTextReplace/Semaphore.hpp"

namespace dtr {

/**
 * @brief Replace words at line by templates
 * @param line line with words
 * @param patterns map of replace patterns
 * @return edited line
 */
auto replaceByTemplates(const std::string &line, const std::shared_ptr<std::map<std::string, std::string>> templates) -> std::string;

/**
 * @brief edit one file by template
 * @param filePath path of edit file
 * @param patterns map of replace patterns
 */
void editFileByTemplates(const std::string &&filePath, const std::shared_ptr<std::map<std::string, std::string>> patterns);

/**
 * @brief Run concurrency edit files in directory by templates
 * @param rootPath root search directory path
 * @param patterns map of replace patterns
 * @param threadsCount count of concurrency threads
 */
void concurrencyEditFiles(const std::string &rootPath, const std::shared_ptr<std::map<std::string, std::string>> patterns, size_t threadsCount);

}  // namespace dtr

#endif  // DEEP_TEXT_REPLACE_PARSED_FILES_HPP
