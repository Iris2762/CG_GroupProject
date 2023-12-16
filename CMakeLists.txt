cmake_minimum_required(VERSION 3.5)

project(Playground)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")

aux_source_directory(source SOURCES)
aux_source_directory(source/shader SOURCES)
aux_source_directory(source/model SOURCES)
add_library(GLAD STATIC ${PROJECT_SOURCE_DIR}/import/source/glad/glad.c)
target_include_directories(GLAD PRIVATE ${PROJECT_SOURCE_DIR}/import/include)

link_directories(${PROJECT_SOURCE_DIR}/lib)

add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME}
    PRIVATE
        glfw3
        GLAD
)

target_include_directories(${PROJECT_NAME}
    PRIVATE
        ${PROJECT_SOURCE_DIR}/include
        ${PROJECT_SOURCE_DIR}/import/include
)