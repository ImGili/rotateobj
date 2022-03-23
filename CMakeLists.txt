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
find_package(OpenSceneGraph 3.6.0 REQUIRED osgDB osgGA osgUtil osgText osgViewer osgWidget osgUtil)

if(OSG_FOUND)
    message("FOUND OSG")
else()
    message("NOT FOUND OSG")
endif()
file(GLOB OSG_PLUGIN_LIBS               ${OSG_PLUGIN_LIB_DIR}/*.lib
                                    )

add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(${PROJECT_NAME}
        PUBLIC
        ${OSG_LIBRARIES} 
        ${OSGVIEWER_LIBRARIES}
        ${OSGUTIL_LIBRARIES} 
        ${OSGDB_LIBRARIES} 
        ${OSGGA_LIBRARIES} 
        ${OPENTHREADS_LIBRARIES}
        ${OSG_PLUGIN_LIBS}
        ${OSGTEXT_LIBRARIES}
        ${OSG_PLUGIN_LIB_DIR}/
        opengl32.lib
        D:/codes/vcpkg/installed/x64-windows-static/debug/lib/libpng16d.lib
        D:/codes/vcpkg/installed/x64-windows-static/debug/lib/zlibd.lib
)   

target_include_directories(${PROJECT_NAME}
        PUBLIC
        ${OSG_INCLUDE_DIR}
        ${CMAKE_SOURCE_DIR}
)