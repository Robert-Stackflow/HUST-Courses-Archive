cmake_minimum_required(VERSION 3.10)
project(Step2)

set(CMAKE_CXX_STANDARD 17)
add_definitions(-w)

INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/src/include
        ${PROJECT_SOURCE_DIR}/src/third_party
        )
#为了提高编译速度，将学生填写的项目文件单独拿出来
#src中的项目代码编译成库文件，存放于lib中直接使用
#add_subdirectory(src)
#这样大幅减少编译时间
LINK_DIRECTORIES(${PROJECT_SOURCE_DIR}/lib)

add_executable(main main.cpp b_plus_tree_internal_page.cpp)

target_link_libraries(main bustub_shared)
