# Minigin

Minigin is a very small project using [SDL2](https://www.libsdl.org/) and [glm](https://github.com/g-truc/glm) for 2D c++ game projects. It is in no way a game engine, only a barebone start project where everything sdl related has been set up. It contains glm for vector math, to aleviate the need to write custom vector and matrix classes.

[![Build Status](https://github.com/avadae/minigin/actions/workflows/msbuild.yml/badge.svg)](https://github.com/avadae/msbuild/actions)
[![GitHub Release](https://img.shields.io/github/v/release/avadae/minigin?logo=github&sort=semver)](https://github.com/avadae/minigin/releases/latest)

# Goal

Minigin can/may be used as a start project for the exam assignment in the course 'Programming 4' at DAE. In that assignment students need to recreate a popular 80's arcade game with a game engine they need to program themselves. During the course we discuss several game programming patterns, using the book '[Game Programming Patterns](https://gameprogrammingpatterns.com/)' by Robert Nystrom as reading material. These patterns need to be applied (when applicable) as well as all (most) [C++ Core Guidelines](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines).

# Disclaimer

Minigin is, despite perhaps the suggestion in its name, not a game engine. It is just a very simple sdl2 ready project. None of the patterns discussed in the course are used (except singleton which use we challenge during the course). It is up to the students to implement their own vision for their engine, apply patterns as they see fit, create their game as efficient as possible.

# Use

Download the latest release of this project and compile/run in visual studio. Since students need to have their work on github too, they can use this repository as a template.

# Design Choices

The Crazy Panda Engine contains functionality such as:
- Entity Component System inspired by Unity.
- The gameloop consists of a fixed update, update, late update and render.
- Scenemanager that handles scenes and loads.
- SDL_mixer Audio service locator, runs on it's own seperate thread to make it sound smoother.
- Command pattern used in both inputsystem and button system. Input can be done both with controllers and keyboard.
- Logging using spdlog, inspired by The Cherno, for a nicer logging layout.
- Text, Texture2D and SpriteSheets work with source and destination rect using SDL.
- Observer pattern to keep track of lives and score.
- EngineTime to make elapsed seconds, totalseconds and timescale global for timer and time manipulation.
- The entire level is read from a JSON file.
- Box2D handles the collision.

Some Constraints:
- GetComponent needs a very specific type of data. If you ask for the base class of a datatype you will receive the base class instead of the derived variant.
- You need to know how to deal with your sprites early on and require the amount of Sprites to be filled in. (Because of the lack of a sprite slicer there is some need for magic numbers.)

Built in Visual Studio 2022 using C++20.
Link: https://github.com/minoarno/CrazyPandaEngine
