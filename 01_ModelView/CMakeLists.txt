# 项目名称
project(01_ModelView)

# 添加可执行文件
add_executable(${PROJECT_NAME}
    main.cpp
	SimpleModel.h
	SimpleModel.cpp
)

# 链接 Qt 库
target_link_libraries(${PROJECT_NAME} PRIVATE Qt5::Widgets)