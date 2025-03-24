cmake_minimum_required(VERSION 3.10.0)
project(SDS VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(SDS main.cpp AppHandler.cpp AppHandler.hpp GameState.cpp GameState.hpp ShooterState.cpp ShooterState.hpp LevelOne.cpp LevelOne.hpp)

target_include_directories(SDS PRIVATE include)

target_link_libraries(SDS PRIVATE ${CMAKE_SOURCE_DIR}/lib/libsfml-system-d.a)
target_link_libraries(SDS PRIVATE ${CMAKE_SOURCE_DIR}/lib/libsfml-window-d.a)
target_link_libraries(SDS PRIVATE ${CMAKE_SOURCE_DIR}/lib/libsfml-main-d.a)
target_link_libraries(SDS PRIVATE ${CMAKE_SOURCE_DIR}/lib/libsfml-graphics-d.a)



add_custom_command(TARGET SDS POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/bin $<TARGET_FILE_DIR:SDS>)
