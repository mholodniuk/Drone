cmake_minimum_required(VERSION 3.10)
project(Drone VERSION 1.0)

set(CMAKE_CXX_STANDARD 14)

file(GLOB_RECURSE SOURCES LIST_DIRECTORIES true inc/*.hpp src/*.cpp)

add_library(${PROJECT_NAME}-lib STATIC ${SOURCES})

set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ../)
add_executable(${PROJECT_NAME} app/main.cpp)
target_link_libraries(${PROJECT_NAME} ${PROJECT_NAME}-lib)



#[[ to generate documentation uncomment 
find_package(Doxygen)
if(DOXYGEN_FOUND)
    set(DOXYGEN_IN ${CMAKE_CURRENT_SOURCE_DIR}/docs/Doxyfile.in)
    set(DOXYGEN_OUT ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)
    configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)
    message("Doxygen build started")
    add_custom_target(doc_doxygen ALL
        COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        COMMENT "Generating API documentation with Doxygen"
        VERBATIM
    )
else (DOXYGEN_FOUND)
    message("Doxygen need to be installed to generate the doxygen documentation")
endif (DOXYGEN_FOUND)
]]