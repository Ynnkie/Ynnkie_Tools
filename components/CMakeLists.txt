cmake_minimum_required(VERSION 3.16)    # 最低版本要求
project(components) # 项目名称

set(LIBRARY_OUTPUT_PATH ${LIB_PATH})    # 库文件输出目录

add_definitions(-DCOMPONENTS_LIBRARY)   # 定义宏 导出符号

aux_source_directory(./ COMPONENTS_SRC) # 添加源文件
add_library(${PROJECT_NAME} SHARED ${COMPONENTS_SRC})   # 创建库文件

target_link_libraries(${PROJECT_NAME} PRIVATE
    Qt6::Core
    Qt6::Widgets
    public
)    # 链接库
