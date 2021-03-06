# BELOSGL - OpenGL Framework by BELOS Thomas

[![Build Status](https://travis-ci.org/belosthomas/glframework.svg?branch=master)](https://travis-ci.org/belosthomas/glframework)

![Screenshot](example/noel/res/screenshot.png)


## Required packages

 - You need a cmake version **higher than 3.13.2** ! You can download the latest binary here : https://cmake.org/download/ or use the utility scripts in ```utils/install-cmake.sh```.
 - OpenGL, SDL2, GLEW, GLM, and ASSIMP are required.

You can install these packages on Ubuntu by using : 

```
sudo apt install gcc g++ make git
sudo apt install libsdl2-dev libglew-dev libglm-dev libassimp-dev
```

## Compilation and installation

[![Build Status](https://travis-ci.org/belosthomas/glframework.svg?branch=master)](https://travis-ci.org/belosthomas/glframework)

Clone the repository : 
```
git clone https://github.com/belosthomas/glframework.git
cd glframework
```

Build the project with cmake : 
```
mkdir build
cmake ..
make
```

From your project, you can use the generated ```libbelosgl.a```.


## Example : GL Noel Viewer

From the build directory, go into the executable directory, and run on of the generated binaries
```
cd noel

# Load the default model
./noel

# Load a .obj model with ASSIMP
./noel res/objs/sponza
# or
./noel ASSIMP res/objs/sponza

# Load a GLTF model
./noel GLTF res/gltfs/Buggy.glb
```

Warning : to not specify the extension for .obj files.

## FAQ

### Unknown CMake command "add_compile_definitions"

You need a more recent version of CMake. A cmake version higher than 3.13.2 is needed.

### CMake not found, or the same version after install-cmake.sh

Try to use ```/usr/share/bin/cmake``` instead of ```cmake```

### File not found, when executing ```./noel```

Please make sure that you run the executable in the ```noel``` directory : 
```
cd noel
./noel
```

## References

#### IMGUI

https://github.com/ocornut/imgui

#### STB Image

https://github.com/nothings/stb

#### TinyGLTF

https://github.com/syoyo/tinygltf

#### TinyGLTL Sample models

https://github.com/KhronosGroup/glTF-Sample-Models/tree/master/2.0

#### Planet Pixel Emporium

http://planetpixelemporium.com/

#### NASA

https://nssdc.gsfc.nasa.gov/planetary/planetfact.html

#### McGuire Computer Graphics Archive

https://casual-effects.com/data/