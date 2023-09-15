# Exercise 3

## Setup

1. Install [CMake](https://cmake.org/)
1. Clone the [SimpleRenderEngineProject repository](https://github.com/mortennobel/SimpleRenderEngineProject) (follow the instruction on its README carefully , there are a few small but necessary extra steps)
1. Create the project
	1. run CMake configuration step, targeting Win32
1. Create your project inside SimpleRenderEngineProject
	1. Create a new folder inside the SimpleRenderEngineProject repository and copy the `data` folder,
	   the `CMakeLists.txt` file (replace `<Project_Name>` in the file with your project name)
	   and your Snake project files there
	1. At the very end of the `CMakeLists` in the root of the repository, add `add_subdirectory(<your_new_dir>)`
	1. refresh your CMake project

## Basic
Update the Snake game to use SimpleRenderEngineProject
1. Remove references to `ITUGames.h`
1. Show an empty window with a sprite in the center (see W3 slide 52 "A starting point")
1. Render snake and collectible using `sre::Sprite` (tip: the sprite doesn't know your gameObject position, you will need to keep them synched manually)
1. Get SDL events from SimpleRenderEngine and use them to control the snake
1. Update player movement to new game scale
  (screen size is in pixel right now, while before was in terminal character.				
  One snake element is exactly one character, but more than one pixel)

Some refactoring of your code may be needed to adapt to SimpleRenderEngine framework-style architecture (as opposed to the ITUGames.h library-style architecture)

## Advanced
Package everything nice and tidy.
1. All the SimpleRenderEngine state (SDLrenderer, Camera and so on) should be encapsulated in our Engine class
1. GameObjects contain their own sprites. Every sprite could have its own SpriteAtlas for convenience, or we could have a single shared instance for performance reasons.
1. SimpleRenderEngine has separate API for different kind of inputs (`keyEvent`, `mouseEvent`, ...)
   while so far we worked with a single `HandleInput()`. We either need to change our Engine and Game code to adapt,
   or we could handle all the events with the same function. (what are advantages and disadvantages of both?)

## Challenge
SimpleRenderEngine makes a lot of decisions in favor of clarity and simplicity, rather then performance.
Think carefully about what happens when passing objects and pointers around, and try to minimize waste.
