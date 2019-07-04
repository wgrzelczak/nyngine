# Nyngine
Window's sandbox in C++. 

## Dependencies
* GLFW
* GLAD
* ImGUI
* spdlog
* fx-gltf

## Requirements
* python3 + pip

## Issues
https://app.gitkraken.com/glo/board/XR4CR2LZywAP4u39

## Installation
Execute ```Tools/initialize.py```

## Directory Hierarchy
- Build
    - bin - binaries
    - obj - intermediates
- External - 3rd parties
- Game - game code
- Nyngine - engine code
- Tools - tools and utilities

## Tools
### Premake5
Genereating vs solution. Every project has separate lua configuration file.
- ```premake5_main.lua``` - main solution, which includes all project's configurations
- ```premake5_engine.lua``` - engine project
- ```premake5_game.lua``` - game project
- ```premake5_glad.lua``` - GLAD project
- ```premake5_glfw.lua``` - GLFW project
- ```premake5_imgui.lua``` - ImGui project

### Code formatting
Formatting all (c, cpp, h, hpp) files in _Game_ and _Nyngine_ directories.
- ```.clang-format``` - all code formatting rules
- Auto-formatting on ```git commit```
- Manual-formatting by ```Tools/clang_format_all.py```