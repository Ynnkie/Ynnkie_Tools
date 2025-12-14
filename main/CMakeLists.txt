cmake_minimum_required(VERSION 3.16) # CMake最小版本要求
project(main) # 项目名称

set(LIBRARY_OUTPUT_PATH ${LIB_PATH}) # 库文件输出目录

aux_source_directory(./ MAIN_SRC) # 添加源文件
add_library(${PROJECT_NAME} SHARED ${MAIN_SRC}) # 创建库文件

target_link_libraries(${PROJECT_NAME} PRIVATE
    # QT6
    Qt6::Widgets
    # 自定义
    public
) # 链接库
