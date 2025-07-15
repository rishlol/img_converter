cmake_minimum_required(VERSION 3.10)
project(img_converter)

# Use C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Find OpenCV
find_package(OpenCV REQUIRED)

# Print OpenCV info (optional, for debugging)
message(STATUS "OpenCV libraries: ${OpenCV_LIBS}")
message(STATUS "OpenCV include dir: ${OpenCV_INCLUDE_DIRS}")

# Add executable
add_executable(img_converter main.cpp)

# Include OpenCV headers
target_include_directories(img_converter PRIVATE ${OpenCV_INCLUDE_DIRS})

# Link OpenCV libraries
target_link_libraries(img_converter PRIVATE ${OpenCV_LIBS})
