#ifndef __FANTASTIC_H__
#define __FANTASTIC_H__

#pragma warning(disable: 4311)                                 
#pragma warning(disable: 4312)
#pragma warning(disable: 4244)
#pragma warning(disable: 4018)
#pragma warning(disable: 4267)
#pragma warning(disable: 4838)
#pragma warning(disable: 4505)
#pragma warning(disable: 4100)
#pragma warning(disable: 4996)
#pragma warning(disable: 4189)
#pragma warning(disable: 4458)
#pragma warning(disable: 4996)
#pragma warning(disable: 4127)
#pragma warning(disable: 4477)
#pragma warning(disable: 4100)
#pragma warning(disable: 4715)
#pragma warning(disable: 4297)
#pragma warning(disable: 4275)
#pragma warning(disable: 4101)
#pragma warning(disable: 4245)
#pragma warning(disable: 4305)
#pragma warning(disable: 4272)


#ifdef _WIN32_

#ifdef _DEBUG
#pragma comment(lib,".\\tools32\\debug\\lib\\freeglutd.lib")
#pragma comment(lib,".\\tools32\\debug\\lib\\FreeImaged.lib")
#pragma comment(lib,".\\tools32\\debug\\lib\\glew32.lib")
#pragma comment(lib,".\\tools32\\debug\\lib\\MyGUIEngine_d.lib")
#pragma comment(lib,".\\tools32\\debug\\lib\\freetype2311_D.lib")
#pragma comment(lib,".\\tools32\\debug\\lib\\OIS.lib")
#pragma comment(lib,".\\tools32\\debug\\lib\\Common_d.lib")
#pragma comment(lib,".\\tools32\\debug\\lib\\MyGUI.OpenGLPlatform_d.lib")
#pragma comment(lib,".\\tools32\\debug\\lib\\Plugin_StrangeButton_d.lib")
#else
#pragma comment(lib,".\\tools32\\relase\\lib\\freeglut.lib")
#pragma comment(lib,".\\tools32\\relase\\lib\\FreeImage.lib")
#pragma comment(lib,".\\tools32\\relase\\lib\\glew32.lib")
#pragma comment(lib,".\\tools32\\relase\\lib\\MyGUIEngine.lib")
#pragma comment(lib,".\\tools32\\relase\\lib\\freetype2311.lib")
#pragma comment(lib,".\\tools32\\relase\\lib\\OIS.lib")
#pragma comment(lib,".\\tools32\\debug\\lib\\Common.lib")
#pragma comment(lib,".\\tools32\\debug\\lib\\MyGUI.OpenGLPlatform.lib")
#pragma comment(lib,".\\tools32\\debug\\lib\\Plugin_StrangeButton.lib")
#endif

#endif

#ifdef _WIN64_

#ifdef _DEBUG

#pragma comment(lib,".\\tools64\\debug\\lib\\freeglutd.lib")
#pragma comment(lib,".\\tools64\\debug\\lib\\FreeImaged.lib")
#pragma comment(lib,".\\tools64\\debug\\lib\\glew32.lib")
#pragma comment(lib,".\\tools64\\debug\\lib\\MyGUIEngine_d.lib")
#pragma comment(lib,".\\tools64\\debug\\lib\\freetype2311_D.lib")
#pragma comment(lib,".\\tools64\\debug\\lib\\OIS.lib")

#else

#pragma comment(lib,".\\tools64\\relase\\lib\\freeglut.lib")
#pragma comment(lib,".\\tools64\\relase\\lib\\FreeImage.lib")
#pragma comment(lib,".\\tools64\\relase\\lib\\glew32.lib")
#pragma comment(lib,".\\tools64\\relase\\lib\\MyGUIEngine.lib")
#pragma comment(lib,".\\tools64\\relase\\lib\\freetype2311.lib")
#pragma comment(lib,".\\tools64\\relase\\lib\\OIS.lib")

#endif

#endif

#include <vector>
#include <stdio.h>
#include <Windows.h>
#include <math.h>
#include <tchar.h>

#include "include\glew.h"
#include "include\freeglut.h"
#include "include\glext.h"
#include "include\wglew.h"
#include "include\FreeImage.h"



using namespace std;




#define BITMAP_ID 0x4D42	/**< 位图文件的标志 */

#define CHECK_FOR_MULTISAMPLE 1
#define WGL_SAMPLE_BUFFERS_ARB		 0x2041
#define WGL_SAMPLES_ARB			     0x2042

#endif
