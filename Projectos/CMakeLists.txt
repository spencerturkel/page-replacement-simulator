cmake_minimum_required(VERSION 3.5)
project(page-replacement-simulator LANGUAGES CXX)

include(ExternalProject)

externalproject_add(cxxopts_external
        GIT_REPOSITORY https://github.com/jarro2783/cxxopts.git
        CMAKE_ARGS -DCXXOPTS_BUILD_EXAMPLES=OFF
        INSTALL_COMMAND ""
        )

externalproject_get_property(cxxopts_external SOURCE_DIR)
add_library(cxxopts INTERFACE)
add_dependencies(cxxopts cxxopts_external)
target_include_directories(cxxopts INTERFACE ${SOURCE_DIR}/include)

add_executable(page-replacement-simulator 
        file_input_retriever.cpp
        iterative_replacement_algorithm.cpp
        main.cpp
        fifo_iterative_replacement_algorithm.h
        file_input_retriever.h
        frequency_iterative_algorithm.h
        input_retriever.h
        iterative_replacement_algorithm.h
        lfu_iterative_replacement_algorithm.h
        lru_iterative_replacement_algorithm.h
        mfu_iterative_replacement_algorithm.h
        optimal_iterative_replacement_algorithm.h
        step_result.h
        )
target_link_libraries(page-replacement-simulator PRIVATE cxxopts)
set_target_properties(page-replacement-simulator PROPERTIES 
        CXX_STANDARD 14 
        CXX_STANDARD_REQUIRED ON
        )
target_compile_options(page-replacement-simulator PRIVATE
        $<$<AND:$<CXX_COMPILER_ID:GNU>,$<CONFIG:Debug>>:-Wall -Wextra -g>
        $<$<AND:$<CXX_COMPILER_ID:MSVC>,$<CONFIG:Debug>>:/W3>
        )
