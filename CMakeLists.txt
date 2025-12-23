cmake_minimum_required(VERSION 3.16)    # 最低版本要求
project(Ynnkie_Tools VERSION 1.0.0 LANGUAGES CXX)   # 项目名称 版本号 语言

set(CMAKE_AUTOUIC ON)   # 自动处理UI文件
set(CMAKE_AUTOMOC ON)   # 自动处理MOC文件
set(CMAKE_AUTORCC ON)   # 自动处理资源文件

set(CMAKE_CXX_STANDARD 17)  # 设置C++标准
set(CMAKE_CXX_STANDARD_REQUIRED ON) # 要求使用C++标准

find_package(Qt6 REQUIRED COMPONENTS Widgets)   # 查找Qt6模块

set(EXE_PATH ${CMAKE_SOURCE_DIR}/bin)   # 可执行文件输出路径
set(LIB_PATH ${CMAKE_SOURCE_DIR}/bin)   # 库文件输出路径
set(RES_PATH ${CMAKE_SOURCE_DIR}/bin/res)   # 资源文件路径

set(EXECUTABLE_OUTPUT_PATH ${EXE_PATH}) # 设置可执行文件输出路径

execute_process( COMMAND ${CMAKE_COMMAND} -E copy_directory ${PROJECT_SOURCE_DIR}/res ${RES_PATH})  # 复制资源文件

# 包含目录
include_directories(public)
include_directories(components)

# 添加子目录
add_subdirectory(public)
add_subdirectory(components)
add_subdirectory(main)

qt_add_executable(
    ${PROJECT_NAME} # 项目名称
    MANUAL_FINALIZATION # 手动最终化
    icon.rc # 资源文件
)   # 生产可执行文件

target_link_libraries(${PROJECT_NAME} PRIVATE
    # QT
    Qt6::Widgets
    # 自定义
    public
    components
    main
)   # 链接库

set_target_properties(
    ${PROJECT_NAME} PROPERTIES
    # 控制台 ON不生成 OFF生成
    # WIN32_EXECUTABLE ON
    WIN32_EXECUTABLE OFF
)   # 设置目标属性

qt_finalize_executable(${PROJECT_NAME}) # 手动完成
