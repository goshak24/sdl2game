# game1 — SDL2 C++ project

This repository contains a minimal SDL2 C++ project with a `CMakeLists.txt` so you can generate a Visual Studio solution.

Windows (Visual Studio) quick start:

1. Download the SDL2 development package for Visual C++ from https://www.libsdl.org/download-2.0.php and extract it (for example `C:/libs/SDL2`).
2. Generate a Visual Studio solution with CMake (example for VS 2022 x64):

```bash
cmake -S . -B build -G "Visual Studio 17 2022" -A x64 -DSDL2_DIR="C:/libs/SDL2"
``` 

3. Open the generated solution `build/game1.sln` in Visual Studio and build.
4. Copy `SDL2.dll` from the SDL2 `lib` folder into the output folder (e.g. `build/Debug`), or place it next to the executable.

If CMake cannot find SDL2, point CMake to the extracted package using `-DSDL2_DIR=` or set `CMAKE_PREFIX_PATH`.

macOS quick start (optional):

```bash
brew install sdl2
cmake -S . -B build
cmake --build build
```

Files added:
- `CMakeLists.txt` — CMake project to generate Visual Studio solution or other generators.
- `src/main.cpp` — minimal SDL2 app.



COMPILE COMMAND: g++ -std=c++17 -O2 src/main.cpp src/game.cpp -o build/game1 $(sdl2-config --cflags --libs)

RUN COMMAND: ./build/game1


CMAKE::: 

CLEAN AND RECONFIGURE (CMake): 
rm -rf build
mkdir build
cd build
cmake .. -DCMAKE_PREFIX_PATH=/opt/homebrew -DCMAKE_BUILD_TYPE=Debug

BUILD AFTER RECONFIGURE (CMake): 
# from build/
cmake --build . --parallel 4

CLEAN ONLY (w/ CMake): 
cmake --build . --target clean# sdl2game
