# MyFirstCrossPlatform
This project was made by me in year 1 of my studies at BUAS. It is a project made from scratch, which runs on windows. 
The code also runs on linux(RaspBerry Pie) it has a seperation for graphics.cpp and input.cpp, however the premake setup does not work for this platform. I decided to not upload the visual studio files and solutions since this would take away the showcase of using premake, so it does not run on linux out of the box.

How to run:
1. Download zip
2. Unzip zip and click on CreateProject.Bat
3. Open solution and run

This project implements a few things:
- OpenGL rendering rasterization pipeline with basic lighting, animations and debug drawing
- keyboard and mouse input
- Random name generator
- Game loop with gamestates, update, draw and intialize
- Custom entities and components

Usecase for renderComponent

![image](https://github.com/JamiePenningnieuwland/MyFirstCrossPlatform/assets/106588989/7d7516f4-7d64-4c01-baf1-d2a4d5f4d574)

- A scene class that updates the entities and their components which can dynamically load/unload and save scene files made with YAML
- Debug editor made with ImGui that allows creation, alteration and deleting of game Objects of loaded scenes

![image](https://github.com/JamiePenningnieuwland/MyFirstCrossPlatform/assets/106588989/3ad699bf-2874-4937-bfd7-da07093fe5d2)
