project(SAMP-WebSockets)
set(CMAKE_BUILD_TYPE Release)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

cmake_minimum_required(VERSION 2.8)

#Compiler-Flags
if(WIN32)
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT /w")
else()
    set(CMAKE_CXX_FLAGS "-static-libgcc -static-libstdc++ -w -std=c++11 ")
endif()

# Boost
if(UNIX)
    set(Boost_USE_STATIC_LIBS ON)
    set(Boost_USE_MULTITHREADED ON)

    find_package(Boost 1.45.0 COMPONENTS thread system REQUIRED)

    if(Boost_FOUND)
        include_directories(${Boost_INCLUDE_DIRS})
    else(Error)
        message(FATAL_ERROR "Boost can not be found!")
    endif()
endif()

# Look for the source-files
if(WIN32)
    file(GLOB_RECURSE SRC_FILES ${PROJECT_SOURCE_DIR}/*.cpp ${PROJECT_SOURCE_DIR}/*.def)
else()
    file(GLOB_RECURSE SRC_FILES ${PROJECT_SOURCE_DIR}/*.cpp)
endif()

#Create binaries
add_library(${PROJECT_NAME} SHARED ${SRC_FILES})

# Link boost just on Unix, MSVC has an autolink support for boost
if(Boost_FOUND AND UNIX)
    target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES})
endif()
