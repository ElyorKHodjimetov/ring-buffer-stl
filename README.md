# Ring Buffer

**Тестовое задание**

* **Целевая платформа**: Windows x86 (поддерживается также x64)
* **Система сборки**: CMake ≥3.10
* **Контроль версий**: Git
* **Публикация**: GitHub / GitLab

## Описание задачи

Реализован шаблонный контейнер-кольцевой буфер на C++:

* Размер задаётся статически на этапе компиляции (`RingBuffer<T, N>`)
* При переполнении автоматически перезаписываются старые данные
* Поддерживаются методы:

  * `push(const T&)`, `pop(T&)`
  * `empty()`, `full()`, `size()`, `capacity()`
  * `clear()`, `operator[]`
  * Поддержка итераторов для `range-based for`

## Сборка и запуск (x86 / Win32)

```bash
mkdir build-release
cd build-release
cmake -G "Visual Studio 17 2022" -A Win32 ..
cmake --build . --config Release
cd Release
./test_ring.exe
./test_rb.exe
```

## Примеры вывода

### Демонстрация работы буфера (test\_ring.exe)

```text
Capacity: 5
Pushed: 1, size=1
Pushed: 2, size=2
Pushed: 3, size=3
Pushed: 4, size=4
Pushed: 5, size=5
Pushed: 6, size=5
Elements in buffer: 2 3 4 5 6
First element = 2
Popping all:
2 3 4 5 6
```

### Юнит-тесты (test\_rb.exe)

```text
===============================================================================
All tests passed (11 assertions in 2 test cases)
```

## Тестирование

Реализованы unit-тесты на Catch2:

### Основные сценарии

* Добавление элементов (`push`) и извлечение (`pop`)
* Переполнение и перезапись старых данных
* Проверка методов `empty`, `full`, `size`, `capacity`
* Доступ к элементам через `operator[]`

### Пример покрытия

```cpp
RingBuffer<int, 3> rb;
rb.push(1);
rb.push(2);
rb.push(3);
rb.push(4); // 1 будет перезаписан
REQUIRE(rb[0] == 2);
REQUIRE(rb[1] == 3);
REQUIRE(rb[2] == 4);
```

## Структура проекта

```text
ring-buffer-stl/
├── CMakeLists.txt
├── RingBuffer.hpp
├── RingBuffer.cpp
├── main.cpp
├── tests/
│   ├── catch.hpp
│   └── test_ringbuffer.cpp
├── build-release/       # Release-сборка (Win32)
│   └── Release/
└── .github/workflows/ci.yml  # CI для GitHub Actions
```

## CI (GitHub Actions)

Добавлен `.github/workflows/ci.yml`, который автоматически:

* собирает проект в Release (x86)
* прогоняет юнит-тесты на каждом push/pull request

В разделе **Actions** репозитория можно отследить статус каждого коммита.

## Лицензия

Этот проект распространяется под лицензией MIT. См. файл LICENSE для подробностей.
