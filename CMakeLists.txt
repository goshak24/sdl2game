cmake_minimum_required(VERSION 3.15)
project(game1 VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Try to find SDL2 via CMake config or fallback to include/library variables
find_package(SDL2 REQUIRED)

find_package(SDL2_image REQUIRED)

add_executable(game1 
src/main.cpp 
src/game.cpp 
src/texture_manager.cpp 
src/game_object.cpp 
src/Map.cpp 
src/game.hpp 
src/texture_manager.hpp 
src/game_object.hpp 
src/Map.hpp 
src/player.hpp 
src/player.cpp
src/enemy.hpp
src/enemy.cpp
src/bullet.hpp
src/bullet.cpp
)

if (TARGET SDL2::SDL2)
  target_link_libraries(game1 PRIVATE SDL2::SDL2)
else()
  target_include_directories(game1 PRIVATE ${SDL2_INCLUDE_DIRS})
  target_link_libraries(game1 PRIVATE ${SDL2_LIBRARIES})
endif()

if (TARGET SDL2_image::SDL2_image)
  target_link_libraries(game1 PRIVATE SDL2_image::SDL2_image)
else()
  if (DEFINED SDL2_IMAGE_INCLUDE_DIRS)
    target_include_directories(game1 PRIVATE ${SDL2_IMAGE_INCLUDE_DIRS})
  endif()
  if (DEFINED SDL2_IMAGE_LIBRARIES)
    target_link_libraries(game1 PRIVATE ${SDL2_IMAGE_LIBRARIES})
  endif()
endif()
