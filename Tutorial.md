# Setting up IDE: Code::Blocks 16.01

Download and install MinGW. This will give us GCC and G++. If you have this installed, skip this step.

Download Code::Blocks here: http://www.codeblocks.org/downloads/26

Download the SDL MinGW dev library from https://www.libsdl.org/release/SDL-devel-1.2.15-mingw32.tar.gz

Download the QuickCG files from the github folder "Dependencies".


#### Adding SDL to MinGW, CodeBlocks and setting up QuickCG.


1) Install CodeBlocks as normal.

2) Open the SDL .tar.gz file you downloaded.

3) Copy SDL.dll from 'bin' to your compilers 'bin' directory (ie C:\Mingw\bin) This allows the compiler to find the dll at runtime time without having to put it in the same folder as your program or in the windows folder. 
 
3) Copy the contents of 'lib' to your compiler's 'lib' folder. If MinGW is installed under C:\MinGW, then this will be C:\MinGW\lib.

4) Copy the complete folder SDL from inside the folder 'include' to your compiler's 'include' directory (for example C:\MinGW\include). Be sure to copy the folder, not the individual files.

5) Create a new empty project. Use the GNU GCC compiler. Go to the 'Linker Settings' tab, and add "-lmingw32 -lSDLmain -lSDL" (without the quotations) to 'other linker options'.

6) Go over to the 'Toolchain executables' tab and make sure everything matches: ![alt text](http://i.imgur.com/BNWKZnu.png)

7) Right click the project on the left, go into Properties, Build Targets, and make it look like this for Debug and Release: ![alt text](http://i.imgur.com/2Q3polR.png) and ![alt text](http://i.imgur.com/VYqypdT.png)

8) Find where the project is being stored on your drive, add the quickcg.cpp and quickcg.h files that you downloaded from the GitHub to the project folder, and also copy SDL.dll into the project folder too. 

9) You can now make a 'main.cpp' file, put this code at the top of it, and begin to code:

```
#ifdef __cplusplus
    #include <cstdlib>
#else
    #include <stdlib.h>
#endif

#include <SDL/SDL.h>

#include <cmath>
#include <string>
#include <vector>
#include <iostream>

#include "quickcg.h"
using namespace QuickCG;

/*
g++ *.cpp -lSDL -O3 -W -Wall -ansi -pedantic
g++ *.cpp -lSDL
*/
```





