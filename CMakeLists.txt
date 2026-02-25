# Root/CMakeLists.txt
cmake_minimum_required(VERSION 3.16)

# 项目整体名称
project(QtLearning LANGUAGES CXX)

# ==========================================
# 通用构建设置
# ==========================================
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 开启 Qt 自动化 (MOC/RCC/UIC)
# 在根目录开启，所有子目录自动继承
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# ==========================================
# 查找依赖
# ==========================================
# 注意：这里没有路径！如果找不到，CMake 会报错提示用户配置环境
find_package(Qt5 COMPONENTS Widgets REQUIRED)

# ==========================================
# 管理子项目
# ==========================================
add_subdirectory(01_ModelView)
# add_subdirectory(02_Signals)  <-- 以后加新例子只需取消注释