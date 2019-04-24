# Nyngine
Window's sandbox in C++. 

## Dependencies
* GLFW
* GLAD
* ImGUI
* spdlog

## Requirements
* python3

## Installation
1. ```Tools/_generate_sln.py```
2. ```Tools/git_copy_hooks.py```

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
Genereating vs solution.
- ```.clang-format``` - all code formatting rules
- ```premake5_main.lua``` - main config file


### Code formatting
Formatting all (c, cpp, h, hpp) files in _Game_ and _Nyngine_ directories.

* Auto-formatting on ```git commit```
* Manual-formatting by ```Tools/_clang_format_all.py```
