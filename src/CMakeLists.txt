# Project  Resource Manager
#
# @author  Roman Zelinskyi <lord.zelinskyi@gmail.com>

add_library(resource-mgr resource_manager.cpp)

target_include_directories(resource-mgr PRIVATE ${CMAKE_SOURCE_DIR}/include)
