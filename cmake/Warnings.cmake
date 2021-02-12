# Project  Resource Manager
#
# @author  Roman Zelinskyi <lord.zelinskyi@gmail.com>

option(WARNINGS_AS_ERRORS "Treat compiler warnings as errors" TRUE)

set(CLANG_WARNINGS
    -Wall
    -Wextra
    -Wshadow
    -Wnon-virtual-dtor
    -Wold-style-cast
    -Wcast-align
    -Wunused
    -Woverloaded-virtual
    -Wpedantic
    -Wconversion
    -Wsign-conversion
    -Wnull-dereference
    -Wdouble-promotion
    -Wformat=2)

if(WARNINGS_AS_ERRORS)
  set(CLANG_WARNINGS ${CLANG_WARNINGS} -Werror)
endif()

set(GCC_WARNINGS ${CLANG_WARNINGS} -Wmisleading-indentation -Wduplicated-cond
                 -Wduplicated-branches -Wlogical-op -Wuseless-cast)

if(CMAKE_CXX_COMPILER_ID MATCHES ".*Clang")
  set(PROJECT_WARNINGS ${CLANG_WARNINGS})
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
  set(PROJECT_WARNINGS ${GCC_WARNINGS})
else()
  message(
    AUTHOR_WARNING
      "No compiler warnings set for '${CMAKE_CXX_COMPILER_ID}' compiler.")
endif()

add_compile_options("$<$<COMPILE_LANGUAGE:CXX>:${PROJECT_WARNINGS}>")

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
