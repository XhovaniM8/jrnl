# Building jrnl

This document provides detailed instructions for building jrnl on different platforms.

## Table of Contents
- [Prerequisites](#prerequisites)
- [Ubuntu/Debian](#ubuntudebian)
- [macOS](#macos)
- [Building](#building)
- [Running](#running)
- [Troubleshooting](#troubleshooting)

## Prerequisites

jrnl requires:
- **CMake** 3.16 or higher
- **Qt6** development libraries (Core, Widgets, Gui modules)
- **C++17** compatible compiler (GCC 7+, Clang 5+, or MSVC 2017+)

## Ubuntu/Debian

### Installing Dependencies

```bash
# Update package lists
sudo apt-get update

# Install build tools and Qt6
sudo apt-get install -y \
    build-essential \
    cmake \
    qt6-base-dev \
    libqt6core6 \
    libqt6gui6 \
    libqt6widgets6
```

### Verify Installation

```bash
# Check CMake version (should be 3.16+)
cmake --version

# Check for Qt6
qmake6 -version
# or
pkg-config --modversion Qt6Core
```

## macOS

### Installing Dependencies

#### Using Homebrew

```bash
# Install Homebrew if not already installed
/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"

# Install dependencies
brew install cmake qt@6

# Add Qt6 to PATH (add to ~/.zshrc or ~/.bash_profile)
echo 'export PATH="/usr/local/opt/qt@6/bin:$PATH"' >> ~/.zshrc
source ~/.zshrc
```

#### Using MacPorts

```bash
# Install dependencies
sudo port install cmake qt6-qtbase
```

### Verify Installation

```bash
# Check CMake version
cmake --version

# Check Qt6 location
which qmake6
```

## Building

### Clone the Repository

```bash
git clone https://github.com/XhovaniM8/jrnl.git
cd jrnl
```

### Build Steps

#### Ubuntu/Debian

```bash
# Create build directory
mkdir build
cd build

# Configure with CMake
cmake ..

# Build (use all CPU cores)
make -j$(nproc)

# The executable will be at: build/jrnl
```

#### macOS (Homebrew)

```bash
# Create build directory
mkdir build
cd build

# Configure with CMake (specify Qt6 path)
cmake -DCMAKE_PREFIX_PATH=/usr/local/opt/qt@6 ..

# Build (use all CPU cores)
make -j$(sysctl -n hw.ncpu)

# The executable will be at: build/jrnl
```

#### macOS (MacPorts)

```bash
# Create build directory
mkdir build
cd build

# Configure with CMake
cmake -DCMAKE_PREFIX_PATH=/opt/local/libexec/qt6 ..

# Build
make -j$(sysctl -n hw.ncpu)
```

### CMake Build Options

You can customize the build with CMake options:

```bash
# Debug build
cmake -DCMAKE_BUILD_TYPE=Debug ..

# Release build with optimizations
cmake -DCMAKE_BUILD_TYPE=Release ..

# Install to custom location
cmake -DCMAKE_INSTALL_PREFIX=/usr/local ..
```

## Running

### From Build Directory

```bash
# Ubuntu/Linux
./build/jrnl

# macOS
./build/jrnl.app/Contents/MacOS/jrnl
# or
open ./build/jrnl.app
```

### Installing System-Wide

```bash
cd build
sudo make install

# Then run from anywhere
jrnl
```

## Troubleshooting

### Qt6 Not Found

**Error:**
```
CMake Error at CMakeLists.txt:X (find_package):
  Could not find a package configuration file provided by "Qt6"
```

**Solution:**
- Make sure Qt6 is installed
- Specify Qt6 location: `cmake -DCMAKE_PREFIX_PATH=/path/to/qt6 ..`
- On Ubuntu: Ensure `qt6-base-dev` is installed
- On macOS: Ensure Qt6 is in PATH or specify with CMAKE_PREFIX_PATH

### CMake Version Too Old

**Error:**
```
CMake 3.X or higher is required. You are running version 3.Y
```

**Solution:**
- Ubuntu: Install from Kitware's repository:
  ```bash
  wget -O - https://apt.kitware.com/keys/kitware-archive-latest.asc 2>/dev/null | sudo apt-key add -
  sudo apt-add-repository 'deb https://apt.kitware.com/ubuntu/ focal main'
  sudo apt-get update
  sudo apt-get install cmake
  ```
- macOS: `brew upgrade cmake`

### Compiler Not Found

**Error:**
```
No CMAKE_CXX_COMPILER could be found
```

**Solution:**
- Ubuntu: `sudo apt-get install build-essential`
- macOS: Install Xcode Command Line Tools: `xcode-select --install`

### Missing Include Files

**Error:**
```
fatal error: QPushButton: No such file or directory
```

**Solution:**
- This usually means Qt6 development headers are not installed
- Ubuntu: `sudo apt-get install qt6-base-dev`
- macOS: Reinstall Qt6: `brew reinstall qt@6`

### Runtime Library Issues (macOS)

**Error:**
```
dyld: Library not loaded: @rpath/QtCore.framework/Versions/6/QtCore
```

**Solution:**
```bash
# Set library path
export DYLD_LIBRARY_PATH=/usr/local/opt/qt@6/lib:$DYLD_LIBRARY_PATH

# Or install Qt6 libraries globally
brew link qt@6 --force
```

## Development

### Rebuilding After Changes

```bash
cd build
make -j$(nproc)  # Linux
make -j$(sysctl -n hw.ncpu)  # macOS
```

### Clean Build

```bash
# Remove build directory
rm -rf build

# Rebuild from scratch
mkdir build && cd build
cmake ..
make
```

### IDE Integration

#### Qt Creator

1. Open `CMakeLists.txt` in Qt Creator
2. Configure project with Qt6 kit
3. Build and run

#### CLion

1. Open project folder in CLion
2. CMake should auto-configure
3. Build and run

#### VS Code

1. Install C/C++ and CMake Tools extensions
2. Open project folder
3. Select kit and configure
4. Build with CMake Tools

## Additional Resources

- [Qt6 Documentation](https://doc.qt.io/qt-6/)
- [CMake Documentation](https://cmake.org/documentation/)
- [jrnl GitHub Repository](https://github.com/XhovaniM8/jrnl)
