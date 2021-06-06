#include <iostream>
#include <filesystem>
#include "DeepTextReplace/Settings.hpp"
#include "DeepTextReplace/EditFiles.hpp"

auto main([[maybe_unused]] int argc, [[maybe_unused]] char* argv[]) -> int {
    std::filesystem::path configFilePath =
        std::filesystem::canonical(std::filesystem::current_path() / "settings.toml");

    if (argc > 1) {
        configFilePath = std::filesystem::path(argv[1]);
    }

    if (std::filesystem::exists(configFilePath) == false ||
        std::filesystem::is_regular_file(configFilePath) == false) {
        std::cout << "Отсутствует файл настроек по пути " << configFilePath.c_str() << '\n';
        return -1;
    }

    dtr::Settings settings(configFilePath.c_str());

    std::string searchPath = settings.getRootDirPath();
    std::shared_ptr<std::map<std::string, std::string>> templates = settings.getTemplates();
    size_t threadsCount = settings.getWorkThreadsCount();

    std::cout << "Запуск редактироване файлов по шаблону в дирректории " << searchPath
              << ", шаблонов " << templates->size()
              << ", потоков: " << threadsCount << '\n';

    if (templates->size() == 0) {
        std::cout << "Список шаблонов пуст" << std::endl;
        return 0;
    }

    dtr::concurrencyEditFiles(searchPath, templates, threadsCount);

    std::cout << "Редактирование файлов завершено" << std::endl;

    return 0;
}
