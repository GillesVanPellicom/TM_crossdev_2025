cmake_minimum_required(VERSION 3.31)
project(crossdev)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Profiling and sanitizer flags
set(CMAKE_C_FLAGS "-Wall -Wextra -Werror -pedantic-errors -Wsign-compare -O0 -fno-omit-frame-pointer -mno-omit-leaf-frame-pointer -fsanitize=address -fsanitize=undefined")
set(CMAKE_CXX_FLAGS "-Wall -Wextra -Werror -pedantic-errors -Wsign-compare -O0 -fno-omit-frame-pointer -mno-omit-leaf-frame-pointer -fsanitize=address -fsanitize=undefined")

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# Suppress erronious Qt memory leak warnings
add_compile_options(-Wno-mismatched-new-delete)

find_package(Qt6 COMPONENTS Core Gui Widgets REQUIRED)

add_executable(crossdev
    src/main.cpp
    src/ui/windows/MainWindow.cpp
    src/ui/widgets/DisplayWidget.cpp
    src/ui/dialogs/SettingsDialog.cpp
    src/app/handlers/Preferences.cpp
)

target_include_directories(crossdev PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_sources(crossdev PRIVATE
    src/ui/windows/MainWindow.h
    src/ui/widgets/DisplayWidget.h
    src/ui/dialogs/SettingsDialog.h
    src/app/handlers/Preferences.h
)

target_link_libraries(crossdev
    Qt::Core
    Qt::Gui
    Qt::Widgets
)
