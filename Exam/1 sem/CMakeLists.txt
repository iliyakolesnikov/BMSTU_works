cmake_minimum_required(VERSION 3.10)
project(online_store CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Найти PostgreSQL
find_package(PostgreSQL REQUIRED)

# Включить директории с заголовками
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${PostgreSQL_INCLUDE_DIRS}
)

# Добавить исполняемый файл
add_executable(online_store 
    src/main.cpp
)

# Линковка библиотек
target_link_libraries(online_store
    ${PostgreSQL_LIBRARIES}
    pqxx
    pq
)

# Установка флагов компилятора
if(MSVC)
    target_compile_options(online_store PRIVATE /W4)
else()
    target_compile_options(online_store PRIVATE -Wall -Wextra -Wpedantic)
endif()

# Вывод информации
message(STATUS "PostgreSQL включена: ${PostgreSQL_FOUND}")
message(STATUS "Версия PostgreSQL: ${PostgreSQL_VERSION_STRING}")
