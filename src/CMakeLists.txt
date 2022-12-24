project(SAMP-WebSockets)
set(CMAKE_BUILD_TYPE Release)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

cmake_minimum_required(VERSION 2.8)

include_directories(${PROJECT_SOURCE_DIR})

add_compile_definitions(ASIO_STANDALONE)
add_compile_definitions(_WEBSOCKETPP_CPP11_TYPE_TRAITS_)
add_compile_definitions(ASIO_SEPARATE_COMPILATION)

#Compiler-Flags
if(WIN32)
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT /w")
else()
    set(CMAKE_CXX_FLAGS "-static-libgcc -static-libstdc++ -w -std=c++11 ")
endif()

# Look for the source-files
if(WIN32)
    file(GLOB_RECURSE SRC_FILES ${PROJECT_SOURCE_DIR}/*.cpp ${PROJECT_SOURCE_DIR}/*.def)
else()
    file(GLOB_RECURSE SRC_FILES ${PROJECT_SOURCE_DIR}/*.cpp)
endif()

#Create binaries
add_library(${PROJECT_NAME} SHARED ${SRC_FILES})
