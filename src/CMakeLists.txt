cmake_minimum_required(VERSION 3.10)
project(MyExecutables LANGUAGES CXX)

# 自动查找当前目录下所有 .cc 文件（不递归子目录）
file(GLOB SOURCES CONFIGURE_DEPENDS "*.cc")

# 如果你希望递归子目录，改用下面这行：
# file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS "*.cc")

# 检查是否找到源文件
if(NOT SOURCES)
    message(FATAL_ERROR "No .cc files found in the current directory!")
endif()

# 设置 C++ 标准（统一设置后续所有目标）
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# 为每个 .cc 文件创建一个可执行文件
foreach(source_file IN LISTS SOURCES)
    # 获取不带路径和扩展名的文件名，作为可执行文件名
    get_filename_component(exec_name ${source_file} NAME_WE)

    # 创建可执行文件
    add_executable(${exec_name} ${source_file})
endforeach()