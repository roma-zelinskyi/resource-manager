# Project  Resource Manager
#
# @author  Roman Zelinskyi <lord.zelinskyi@gmail.com>

find_package(GTest REQUIRED)

add_executable(
  unit-tests EXCLUDE_FROM_ALL
  main.cpp allocator_unit_test.cpp resource_user_unit_test.cpp
  resource_manager_unit_test.cpp)

target_include_directories(
  unit-tests PRIVATE ${GTEST_INCLUDE_DIRS} ${CMAKE_SOURCE_DIR}/include
                     ${CMAKE_SOURCE_DIR}/src)

target_link_libraries(unit-tests PRIVATE ${GTEST_LIBRARIES} pthread
                                         resource-mgr)

gtest_add_tests(TARGET unit-tests)

add_dependencies(tests unit-tests)
