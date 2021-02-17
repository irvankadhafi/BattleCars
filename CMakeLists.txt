cmake_minimum_required(VERSION 3.17)
project(BattleCars)

set(CMAKE_CXX_STANDARD 14)

add_executable(${PROJECT_NAME}  main.cpp IRVANKDHF.h loadtextbmp.cpp object.cpp print.cpp project.cpp fatal.cpp errcheck.cpp)
# add_executable(${PROJECT_NAME}  PlaneShooter.cpp)
target_link_libraries(${PROJECT_NAME} -lglut -lGLU -lGL -lm)
target_compile_options(${PROJECT_NAME} PRIVATE -Wno-everything)
