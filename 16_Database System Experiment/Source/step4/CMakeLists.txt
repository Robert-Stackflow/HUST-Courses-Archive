
cmake_minimum_required(VERSION 3.10)
project(Step4)

set(CMAKE_CXX_STANDARD 17)
add_definitions(-w)

INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/src/include
        ${PROJECT_SOURCE_DIR}/src/third_party
        )
#Ϊ����߱����ٶȣ���ѧ����д����Ŀ�ļ������ó���
#src�е���Ŀ�������ɿ��ļ��������lib��ֱ��ʹ��
#add_subdirectory(src)
#����������ٱ���ʱ��
LINK_DIRECTORIES(${PROJECT_SOURCE_DIR}/lib)

add_executable(main main.cpp b_plus_tree.cpp index_iterator.cpp)

target_link_libraries(main bustub_shared)
