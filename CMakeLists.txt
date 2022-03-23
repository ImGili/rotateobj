cmake_minimum_required(VERSION 3.0)
project(RotateObj)
if(MSVC)
    message("Compiler: MSVC")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4 /source-charset:utf-8 /execution-charset:gbk /std:c++17")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MTd")
endif()

add_definitions(-DOSG_LIBRARY_STATIC)
######################### OSG ######################################
find_package(OpenSceneGraph 3.6.0 REQUIRED osgDB)

if(OSG_FOUND)
    message("FOUND OSG")
else()
    message("NOT FOUND OSG")
endif()


add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(${PROJECT_NAME}
        PUBLIC
        ${OSG_LIBRARIES} 
        ${OSGDB_LIBRARIES} 
)   

target_include_directories(${PROJECT_NAME}
        PUBLIC
        ${OSG_INCLUDE_DIR}
        ${CMAKE_SOURCE_DIR}
)