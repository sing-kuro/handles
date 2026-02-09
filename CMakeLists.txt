cmake_minimum_required(VERSION 3.21)

project(handles VERSION 0.1.0 LANGUAGES CXX)

option(ENABLE_TESTING_HANDLES "Enable testing" OFF)
option(BUILD_HANDLES_DOCS "Build documentation" OFF)

if (ENABLE_TESTING_HANDLES)
    enable_testing()
    add_subdirectory(tests)
endif()

if (BUILD_HANDLES_DOCS)
    add_subdirectory(docs)
endif()

include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

add_library(handles INTERFACE)
target_include_directories(handles
    INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

# C++ standard
target_compile_features(handles INTERFACE cxx_std_20)

#Export + Install rules
install(TARGETS handles
    EXPORT handlesTargets
)

# Install headers
install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

install(EXPORT handlesTargets
    FILE handlesTargets.cmake
    NAMESPACE handles::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/handles
)

# Generate config files
configure_package_config_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake/handlesConfig.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/handlesConfig.cmake"
    INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/handles
)

# Generate version file
write_basic_package_version_file(
    "${CMAKE_CURRENT_BINARY_DIR}/handlesConfigVersion.cmake"
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY SameMajorVersion
)

# Install config and version files
install(FILES
    "${CMAKE_CURRENT_BINARY_DIR}/handlesConfig.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/handlesConfigVersion.cmake"
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/handles
)

# Export build-tree package config
export(EXPORT handlesTargets
    FILE "${CMAKE_CURRENT_BINARY_DIR}/handlesTargets.cmake"
    NAMESPACE handles::
)

#Add the build tree as a package registry entry
set(HANDLES_DIR "${CMAKE_CURRENT_BINARY_DIR}")
