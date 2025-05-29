cmake_minimum_required(VERSION 3.10)
project(leetcode_solutions)

# Find all CMakeLists.txt files in subdirectories
file(GLOB_RECURSE SUBDIR_CMAKE_LISTS LIST_DIRECTORIES false */CMakeLists.txt)
set(EXECUTABLE_TARGETS "")

foreach(cmake_file ${SUBDIR_CMAKE_LISTS})
    get_filename_component(subdir ${cmake_file} DIRECTORY)
    get_filename_component(dirname ${subdir} NAME)
    if(NOT ${subdir} STREQUAL ${CMAKE_SOURCE_DIR})
        add_subdirectory(${subdir})
        # Assume executable name matches directory name
        list(APPEND EXECUTABLE_TARGETS ${dirname})
    endif()
endforeach()

# Create custom target to run all executables
add_custom_target(run_all
    COMMENT "Running all executables..."
)

foreach(target ${EXECUTABLE_TARGETS})
    add_custom_command(TARGET run_all POST_BUILD
        COMMAND ${CMAKE_BINARY_DIR}/${target}/${target}
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/${target}
        COMMENT "Running ${target}"
    )
endforeach()

add_dependencies(run_all ${EXECUTABLE_TARGETS})