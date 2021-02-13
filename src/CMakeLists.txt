# Project  Resource Manager
#
# @author  Roman Zelinskyi <lord.zelinskyi@gmail.com>

add_library(resource-mgr SHARED resource_manager.cpp allocator.cpp)

target_include_directories(resource-mgr PRIVATE ${CMAKE_SOURCE_DIR}/include)
