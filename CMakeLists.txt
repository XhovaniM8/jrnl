cmake_minimum_required(VERSION 3.16)

project(jrnl VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# Find Qt6
find_package(Qt6 REQUIRED COMPONENTS Core Widgets Gui)

# Include directories
include_directories(
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}/src/core
    ${CMAKE_SOURCE_DIR}/src/ui
)

# Core backend sources
set(CORE_SOURCES
    src/core/Vault.cpp
    src/core/Entry.cpp
    src/core/Storage.cpp
    src/core/SearchEngine.cpp
)

set(CORE_HEADERS
    src/core/Vault.h
    src/core/Entry.h
    src/core/Storage.h
    src/core/SearchEngine.h
)

# UI sources
set(UI_SOURCES
    src/ui/MainWindow.cpp
    src/ui/EntryEditor.cpp
    src/ui/EntryList.cpp
    src/ui/VaultSelector.cpp
)

set(UI_HEADERS
    src/ui/MainWindow.h
    src/ui/EntryEditor.h
    src/ui/EntryList.h
    src/ui/VaultSelector.h
)

# Main application
set(APP_SOURCES
    src/main.cpp
)

# Create executable
add_executable(jrnl
    ${APP_SOURCES}
    ${CORE_SOURCES}
    ${CORE_HEADERS}
    ${UI_SOURCES}
    ${UI_HEADERS}
)

# Link Qt6 libraries
target_link_libraries(jrnl
    Qt6::Core
    Qt6::Widgets
    Qt6::Gui
)

# Install target
install(TARGETS jrnl
    RUNTIME DESTINATION bin
)
