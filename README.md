# handles

## Requirements
- C++ 20

## Building

### Installing
Example commands to install the library:
```sh
git clone https://github.com/sing-kuro/handles.git
cd handles
cmake -S . -B build -DBUILD_HANDLES_DOCS=ON -DENABLE_TESTING_HANDLES=ON -DCMAKE_BUILD_TYPE=Release
cmake --build build
ctest --test-dir build
cmake --install build --prefix "/your/install/dir"
```

### Linking
In your project's `CMakeLists.txt`, add:
```cmake
find_package(handles REQUIRED)
target_link_libraries(YourApp PRIVATE handles::handles)
```

If you have installed the library on your machine:
```sh
cmake -S . -B build -DCMAKE_PREFIX_PATH="/your/install/dir"
```

If you want to avoid installing the library locally:
```sh
cmake -S . -B build -Dhandles_DIR=/path/to/handles/build
```

If you prefer to use CMake's `FetchContent`:
```cmake
include(FetchContent)

FetchContent_Declare(
    handles
    GIT_REPOSITORY https://github.com/sing-kuro/handles.git
    GIT_TAG # The commit hash you want to use
)

FetchContent_MakeAvailable(handles)

add_executable(YourApp main.cpp)
target_link_libraries(YourApp PUBLIC handles)
```

## Usage

## Issue Report
If you find any issues on this project, please [report it on GitHub](https://github.com/sing-kuro/handles/issues).

## Acknowledgements
- This project utilizes OSS (Open Source Software)
    See [NOTICE.md](NOTICE.md)
