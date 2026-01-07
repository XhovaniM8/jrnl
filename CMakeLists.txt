cmake_minimum_required(VERSION 3.16)
project(jrnl VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# Find Qt6 packages
find_package(Qt6 REQUIRED COMPONENTS Core Widgets Gui)

# Optional: Find Python for integration
find_package(Python3 COMPONENTS Interpreter Development)

# Include directories
include_directories(${CMAKE_SOURCE_DIR}/include)

# Source files
set(SOURCES
    src/main.cpp
    src/mainwindow.cpp
    src/journalentry.cpp
    src/filemanager.cpp
    src/markdowneditor.cpp
)

# Header files
set(HEADERS
    include/mainwindow.h
    include/journalentry.h
    include/filemanager.h
    include/markdowneditor.h
)

# Create executable
add_executable(jrnl ${SOURCES} ${HEADERS})

# Link Qt6 libraries
target_link_libraries(jrnl
    Qt6::Core
    Qt6::Widgets
    Qt6::Gui
)

# Optional: Link Python if found
if(Python3_FOUND)
    target_include_directories(jrnl PRIVATE ${Python3_INCLUDE_DIRS})
    target_link_libraries(jrnl ${Python3_LIBRARIES})
    target_compile_definitions(jrnl PRIVATE PYTHON_ENABLED)
endif()

# Installation
install(TARGETS jrnl
    RUNTIME DESTINATION bin
)

# Platform-specific settings
if(APPLE)
    set_target_properties(jrnl PROPERTIES
        MACOSX_BUNDLE TRUE
        MACOSX_BUNDLE_GUI_IDENTIFIER "com.jrnl.app"
        MACOSX_BUNDLE_BUNDLE_NAME "jrnl"
        MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION}
    )
endif()
