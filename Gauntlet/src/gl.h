#pragma once
//these files will be included a lot 
//too lazy to type these defines everytime
#ifdef WINDOWS
#include<glad/glad.h>
#elif RASPBERRY
#include <GLES3/gl3.h>
#endif