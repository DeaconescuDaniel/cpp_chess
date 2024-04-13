cmake_minimum_required(VERSION 3.22)
project(chess_cpp)

set(CMAKE_CXX_STANDARD 14)

include_directories("SDL2/x86_64-w64-mingw32/include" "SDL2_image/x86_64-w64-mingw32/include")
link_directories("SDL2/x86_64-w64-mingw32/lib" "SDL2_image/x86_64-w64-mingw32/lib")

# Must set the path to the main.cpp, for example: scripts/main.cpp if it is inside a folder
add_executable(chess_cpp scripts/main.cpp
        scripts/chess.h
        scripts/chess.cpp)

target_link_libraries(chess_cpp mingw32 SDL2main SDL2 SDL2_image)

