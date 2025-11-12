cmake_minimum_required(VERSION 3.10)
project(SFML1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB SOURCES
    "${CMAKE_SOURCE_DIR}/*.cpp"
)

add_executable(SFML1 ${SOURCES})

find_package(SFML 2.5 COMPONENTS system window graphics audio REQUIRED)

target_link_libraries(SFML1 PRIVATE sfml-system sfml-window sfml-graphics sfml-audio)

file(COPY
    ${CMAKE_SOURCE_DIR}/fonts
    ${CMAKE_SOURCE_DIR}/images
    ${CMAKE_SOURCE_DIR}/music
    DESTINATION ${CMAKE_BINARY_DIR}
)
