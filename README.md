## Physics Modeling / Visualizer

Included dependencies are build for Windows only. If you plan to use this on a different architecture then mine, you will have to compile and include the binaries for the vendors yourself. Eventually I will add submodules, but not today.

Note about STB 3rd party library use in Texture.cpp:
- create a .cpp with only the following, where the include is pointing to your stb_image.h header file:
```
#define STB_IMAGE_IMPLEMENTATION
#include "../../../vendor/stb/stb_image.h"
```
- compile the obj file with:
```
g++ -c stb.cpp -o stb.o
```
- then
```
ar rcs stb.a stb.o
```
- Now move the static lib file to where the header file lives and add the paths to the makefile commands for the compiler to link to
- Append the include header preprocessor command where it is needed in the project

Documentation:
https://docs.gl

OpenGL Pipeline:
https://open.gl/drawing

GLFW Windows Guide:
https://www.glfw.org/docs/3.3/window_guide.html

GLFW Events Guide:
https://www.glfw.org/docs/3.3/input_guide.html#events

Math Overview:
https://morning-flow.com/2023/02/06/the-math-behind-the-lookat-transform/
https://www.songho.ca/opengl/gl_projectionmatrix.html
https://open.gl/transformations

ECS Talks/Overview/References:
https://austinmorlan.com/posts/entity_component_system/#what-is-an-ecs
https://www.youtube.com/watch?v=NTWSeQtHZ9M&t=1485s
https://www.youtube.com/watch?v=3N1pLtTV2Uc&t=1s
https://github.com/skypjack/entt

TODO (roadmap):

- rewrite build system to use cmake (implemented - needs some cleaning)
- wrap existing vendor dependencies into git submodules
- research meta-programming libraries (consider: boost::mpl11, boost::hana, hyperion::mpl)
- bundle mpl submodule w/ project
- continue implementing component system
- implement scene system with new ecs
- add a logging library (consider: spdlog)
- implement serializer
- research math libraries (consider: glm)
- (tbd) rewrite to use 3rd party math lib
- move uniform types list into the shader constructor
- update floor/terrain to be "infinite" by default
- add instanced rendering for models
- (delayed) add simple gravity forces 
- (delayed) add simple non-elastic collision forces

![alt text](image.png)
