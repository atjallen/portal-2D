# Portal 2D

A 2D version of Valve's Portal developed in C++ with SFML. Uses a custom game engine written from scratch. Still very much in the early stages.

## Features

- Uses a custom component-based game engine modelled on Unity
- You can create custom level files and have them be imported
- You can move a player around a level
- Collision between the player and structures works in general

## To-Do

- Set up some actual gameplay mechanics
  - Portals
  - Cubes
  - Turrets
- Non-placeholder art
- Menus
- UI

## Development Setup

### Dependencies

- [git](https://git-scm.com/)
- [Visual Studio](https://visualstudio.microsoft.com/)
- [SFML](https://www.sfml-dev.org/)
- [nlohmann/json](https://github.com/nlohmann/json)

### Setup

- Install all the dependencies
- Pull the repo
- Open `portal-2D.sln`
- Right click on the `portal-2D` project and select `Properties`
- Edit the properties dealing with external libraries to point at your installations of the third party libraries
  - In particular, you'll need to edit at least the `Additional Include Directories` and `Additional Library Directories` settings
- Build and run
