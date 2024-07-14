cmake_minimum_required(VERSION 3.5.0)
project(SocketChat VERSION 0.1.0 LANGUAGES C CXX)

# Add a library for the utility functions
add_library(util util.c)

# Include directories
include_directories(${PROJECT_SOURCE_DIR})

# Add executables
add_executable(client client.c)
add_executable(server server.c)

# Link the utility library with both executables
target_link_libraries(client util)
target_link_libraries(server util)