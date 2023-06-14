Design Choices

The Crazy Panda Engine contains functionality such as:

 -   Entity Component System inspired by Unity.
 -   The gameloop consists of a fixed update, update, late update and render.
 -   Scenemanager that handles scenes and loads.
 -   SDL_mixer Audio service locator, runs on it's own seperate thread to make it sound smoother.
 -   Command pattern used in both inputsystem and button system. Input can be done both with controllers and keyboard.
 -   Logging using spdlog, inspired by The Cherno, for a nicer logging layout.
 -   Text, Texture2D and SpriteSheets work with source and destination rect using SDL.
 -   Observer pattern to keep track of lives and score.
 -   EngineTime to make elapsed seconds, totalseconds and timescale global for timer and time manipulation.
 -   The entire level is read from a JSON file.
 -   Box2D handles the collision.

Some Constraints:

 -   GetComponent needs a very specific type of data. If you ask for the base class of a datatype you will receive the base class instead of the derived variant.
 -   You need to know how to deal with your sprites early on and require the amount of Sprites to be filled in. (Because of the lack of a sprite slicer there is some need for magic numbers.)

Built in Visual Studio 2022 using C++20.

Link: https://github.com/minoarno/CrazyPandaEngine