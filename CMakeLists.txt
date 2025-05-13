cmake_minimum_required(VERSION 3.10)
project(RingBufferExample LANGUAGES CXX)

# Настройка стандарта
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Библиотека RingBuffer (интерфейсная, т.к. шаблон)
add_library(ringbuffer INTERFACE)
target_include_directories(ringbuffer INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

# Исполняемый файл-демонстратор
add_executable(test_ring main.cpp)
target_link_libraries(test_ring PRIVATE ringbuffer)

# Unit-тесты с Catch2
enable_testing()
add_executable(test_rb
    tests/test_ringbuffer.cpp
)
# подключаем заголовки
target_include_directories(test_rb PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/tests
)
target_link_libraries(test_rb PRIVATE ringbuffer)
add_test(NAME RingBufferTests COMMAND test_rb)
