# Project  Resource Manager
#
# @author  Roman Zelinskyi <lord.zelinskyi@gmail.com>

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    option(TESTS "Enable/disable tests" ON)
endif()

function(printOption name value)
    if(${value})
        message(STATUS "${name}: ON")
    else()
        message(STATUS "${name}: OFF")
    endif()
endfunction()

printOption("Tests" TESTS)
