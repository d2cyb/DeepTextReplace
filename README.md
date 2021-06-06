# DeepTextReplace

## Описание
Поиск и замена данных в текстовых файлах по заданным шаблонам.

Поиск производится в указанной(в конфигурационном файле) директории и вложенных поддиректориях произвольной вложенности.

### Файла настроек
Формат файла конфигурации - [TOML](https://toml.io/en/).

Пример:
```ini
[streams]
count = 1

[directory]
root = "./"

[templates]
"<%COLOR%>" = "BLACK"
"CIRCLE" = "CIRCLE"
```


## Зависимости проекта
 * [googletest](https://github.com/google/googletest.git) - unit тесты
 * [google benchmark](https://github.com/google/benchmark) - bench тесты


## Сборка проекта
Создать в корне проекта директорию build, перейти в неё и выполнить следующие команды.

`cmake ..`

`make`

## Запуск программы
В корне проекта выполнить следующую команду:

`./build/bin/DeepTextReplace_cli`


## Запуск тестов

### Unit тесты
В корне проекта выполнить следующую команду:

`./build/bin/DeepTextReplace_unit`

### Нагрузочные тесты
В корне проекта выполнить следующую команду:

`./build/bin/DeepTextReplace_bench`

## Пример работы программы
Создать файл конфигурации config.toml. Пример файла:
```ini
[streams]
count = 1

[directory]
root = "/tmp/<путь к директории>"

[templates]
"<%COLOR%>" = "BLACK"
"SHAPE" = "CIRCLE"
```

В корне проекта выполнить следующую команду:

`./build/bin/DeepTextReplace_cli ./config.toml`

Либо, если в директории с исполняемым файлам уже есть config.toml, то можно запустить без параметров.
