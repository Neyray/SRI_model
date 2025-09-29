cmake_minimum_required(VERSION 3.10)
project(SRI_Model VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# include 目录
include_directories(\/include)

# 主可执行文件（示例：把 main.cpp 和 test_sri.cpp 一起编译；将来可拆分）
add_executable(sri_model
    src/main.cpp
    src/test_sri.cpp
)

target_include_directories(sri_model PRIVATE \/include)
