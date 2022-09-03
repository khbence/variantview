cmake_minimum_required(VERSION 3.15)

set(VARIANT_VIEWS_LIBRARY "variantViews")
set(TEST_BINARY "testBin")

project(variantViews CXX)
include(cmake/StandardProjectSettings.cmake)
# include(cmake/PreventInSourceBuilds.cmake)

# Link this 'library' to set the c++ standard / compile-time options requested
add_library(${PROJECT_NAME}_options INTERFACE)
# target_compile_features(project_options INTERFACE cxx_std_17)

# Link this 'library' to use the warnings specified in CompilerWarnings.cmake
add_library(${PROJECT_NAME}_warnings INTERFACE)

# enable cache system
include(cmake/Cache.cmake)

# standard compiler warnings
include(cmake/CompilerWarnings.cmake)
set_project_warnings(${PROJECT_NAME}_warnings)

# sanitizer options if supported by compiler
include(cmake/Sanitizers.cmake)
enable_sanitizers(${PROJECT_NAME}_options)

# enable doxygen
include(cmake/Doxygen.cmake)
enable_doxygen()

# allow for static analysis options
include(cmake/StaticAnalyzers.cmake)

option(BUILD_SHARED_LIBS "Enable compilation of shared libraries" OFF)
option(ENABLE_TESTING "Enable Test Builds" ON)

# option(ENABLE_FUZZING "Enable Fuzzing Builds" OFF)
# if(ENABLE_FUZZING)
#   message(
#     "Building Fuzz Tests, using fuzzing sanitizer https://www.llvm.org/docs/LibFuzzer.html"
#   )
#   add_subdirectory(fuzz_test)
# endif()

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(ENABLE_TESTING)
  add_subdirectory(test)
endif()

add_library(${VARIANT_VIEWS_LIBRARY} INTERFACE)
target_include_directories(${VARIANT_VIEWS_LIBRARY} INTERFACE include)

