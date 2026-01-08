# Building jrnl

## Prerequisites

This document provides detailed instructions for building jrnl on different platforms.

## Ubuntu/Debian Linux

### Install Dependencies

```bash
# Update package list
sudo apt-get update

# Install Qt6 and build tools
sudo apt-get install -y \
    qt6-base-dev \
    qt6-base-dev-tools \
    cmake \
    g++ \
    make \
    git

# Optional: Python development files for analytics
sudo apt-get install -y python3-dev python3-pip
```

### Build

```bash
# Create build directory
mkdir -p build
cd build

# Configure
cmake ..

# Build (use all CPU cores)
make -j$(nproc)

# Test the executable
./jrnl
```

## macOS

### Install Dependencies

Using Homebrew:

```bash
# Install Homebrew if not already installed
/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"

# Install dependencies
brew install qt@6 cmake python3

# Add Qt6 to PATH (add to ~/.zshrc or ~/.bash_profile for persistence)
export PATH="/opt/homebrew/opt/qt@6/bin:$PATH"
```

### Build

```bash
# Create build directory
mkdir -p build
cd build

# Configure with Qt6 path
cmake .. -DCMAKE_PREFIX_PATH=/opt/homebrew/opt/qt@6

# Build
make -j$(sysctl -n hw.ncpu)

# Run
./jrnl
```

## Windows (Future Support)

Windows support is planned for future releases. The application can be built using:
- Visual Studio 2019 or later
- Qt6 for Windows
- CMake

## Build Options

### Release Build

For an optimized release build:

```bash
cmake -DCMAKE_BUILD_TYPE=Release ..
make
```

### Debug Build

For development with debug symbols:

```bash
cmake -DCMAKE_BUILD_TYPE=Debug ..
make
```

### Python Integration

To build with Python integration enabled:

```bash
cmake -DPYTHON_ENABLED=ON ..
make
```

## Installation

### System-wide Installation (Linux/macOS)

```bash
# After building
sudo make install
```

This installs the `jrnl` binary to `/usr/local/bin` (or the configured prefix).

### Custom Installation Path

```bash
cmake -DCMAKE_INSTALL_PREFIX=/custom/path ..
make
make install
```

## Troubleshooting

### Qt6 Not Found

If CMake cannot find Qt6:

**Linux:**
```bash
# Check if Qt6 is installed
dpkg -l | grep qt6

# Find Qt6 installation
find /usr -name Qt6Config.cmake 2>/dev/null

# Set Qt6_DIR if needed
export Qt6_DIR=/usr/lib/x86_64-linux-gnu/cmake/Qt6
```

**macOS:**
```bash
# Ensure Homebrew Qt6 is in PATH
export CMAKE_PREFIX_PATH="/opt/homebrew/opt/qt@6"
```

### Python Not Found

If you want Python integration but CMake can't find it:

```bash
# Find Python installation
which python3

# Set Python paths manually
cmake .. \
  -DPython3_EXECUTABLE=/usr/bin/python3 \
  -DPython3_INCLUDE_DIRS=/usr/include/python3.x \
  -DPython3_LIBRARIES=/usr/lib/libpython3.x.so
```

### Compiler Errors

Ensure you have a C++17 compatible compiler:

**Linux:**
```bash
g++ --version  # Should be 7.0 or later
```

**macOS:**
```bash
clang --version  # Should support C++17
```

## Development Build

For faster iteration during development:

```bash
# Use ccache if available
cmake -DCMAKE_CXX_COMPILER_LAUNCHER=ccache ..

# Build only changed files
make -j$(nproc)
```

## Clean Build

To start fresh:

```bash
cd build
rm -rf *
cmake ..
make
```

## Verification

After building, verify the executable:

```bash
# Check the binary
file ./jrnl
ldd ./jrnl  # Linux - check linked libraries
otool -L ./jrnl  # macOS - check linked libraries

# Run with version info
./jrnl --version  # (if implemented)
```
