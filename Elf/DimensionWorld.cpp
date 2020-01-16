#include "DimensionWorld.h"



//GLWindow_PDE======================================================================

/** 构造函数 */
GLWindow_PDE::GLWindow_PDE()
{
	m_WindowPosX = 0;												/**< 窗口的左上角的X位置 */
	m_WindowPosY = 0;												/**< 窗口的左上角的Y位置 */
	m_WindowWidth = 1920/2;												/**< 窗口的宽度 */
	m_WindowHeight = 1080/2;												/**< 窗口的高度 */
	m_ScreenWidth = 1024;												/**< 全屏的宽度 */
	m_ScreenHeight = 768;												/**< 全屏的高度 */
	m_BitsPerPixel = 16;												/**< 颜色位深 */
	m_IsFullScreen = false;											/**< 不使用全屏 */

	m_hWnd = 0;
	m_hDC = 0;
	m_hRC = 0;
	
}

/** 返回窗口的大小 */
int GLWindow_PDE::GetWidth()
{
	if (m_IsFullScreen == true)
	{
		return m_ScreenWidth;
	}
	else
	{
		return m_WindowWidth;
	}
}

int GLWindow_PDE::GetHeight()
{
	if (m_IsFullScreen == true)
	{
		return m_ScreenHeight;
	}
	else
	{
		return m_WindowHeight;
	}
}

/** 设置窗口的大小 */
void GLWindow_PDE::SetWidth(int width)
{
	if (m_IsFullScreen == true)
	{
		m_ScreenWidth = width;
	}
	else
	{
		m_WindowWidth = width;
	}
}

void GLWindow_PDE::SetHeight(int height)
{
	if (m_IsFullScreen == true)
	{
		m_ScreenHeight = height;
	}
	else
	{
		m_WindowHeight = height;
	}
}

/** 返回窗口左上角的位置 */
int GLWindow_PDE::GetPosX()
{
	if (m_IsFullScreen == false)
	{
		return m_WindowPosX;
	}
	return 0;
}

int GLWindow_PDE::GetPosY()
{
	if (m_IsFullScreen == false)
	{
		return m_WindowPosY;
	}
	return 0;
}

/** 设置窗口左上角的位置 */
void GLWindow_PDE::SetPosX(int x)
{
	if (m_IsFullScreen == false)
	{
		m_WindowPosX = x;
	}
}

void GLWindow_PDE::SetPosY(int y)
{
	if (m_IsFullScreen == false)
	{
		m_WindowPosY = y;
	}
}

/** 当窗口大小改变时，通知OpenGL调整大小 */
void GLWindow_PDE::ReshapeGL()
{
	GLsizei width = GetWidth();
	GLsizei height = GetHeight();
	glViewport(0, 0, width, height);									/**< 重新设置视口 */
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f, (GLfloat)width / (GLfloat)height, 1.0f, 100000.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

/** 改变窗口的显示设置 */
bool GLWindow_PDE::ChangeScreenSetting()
{
	DEVMODE dmScreenSettings;											/**< 设备模式 */
	ZeroMemory(&dmScreenSettings, sizeof(DEVMODE));						/**< 清零结构 */
	dmScreenSettings.dmSize = sizeof(DEVMODE);					/**< 结构大小 */
	dmScreenSettings.dmPelsWidth = GetWidth();						/**< 设置宽度 */
	dmScreenSettings.dmPelsHeight = GetHeight();						/**< 设置高度 */
	dmScreenSettings.dmBitsPerPel = m_BitsPerPixel;					/**< 设置位深度 */
																	//dmScreenSettings.dmDisplayFrequency = 75;                           /**< 设置屏幕刷新率 */
	dmScreenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;//| DM_DISPLAYFREQUENCY;

																			 /// 改变显示模式
	if (ChangeDisplaySettings(&dmScreenSettings, 0) != DISP_CHANGE_SUCCESSFUL)
	{
		return false;													/**< 如果失败，返回false */
	}

	return true;														/**< 成功返回 */
}

/** 创建windows窗口 */
bool GLWindow_PDE::Create(const TCHAR * window_title, const TCHAR * class_name, bool fullscreen, HINSTANCE h_instance, LPVOID lpParam)
{
	m_IsFullScreen = fullscreen;
	int nX = 0;
	int nY = 0;
	PIXELFORMATDESCRIPTOR pfd =											/**< 设置像素描述结构 */
	{
		sizeof(PIXELFORMATDESCRIPTOR),									/**< 像素描述结构的大小 */
		1,																/**< 版本号 */
		PFD_DRAW_TO_WINDOW |											/**< 缓存区的输出显示在一个窗口中 */
		PFD_SUPPORT_OPENGL |											/**< 缓存区支持OpenGL绘图 */
		PFD_STEREO |											/**< 颜色缓存区是立体缓存 */
		PFD_DOUBLEBUFFER,												/**< 颜色缓存区是双缓存 */
		PFD_TYPE_RGBA,													/**< 使用RGBA颜色格式 */
		m_BitsPerPixel,													/**< 颜色缓存区中颜色值所占的位深 */
		0, 0, 0, 0, 0, 0,												/**< 使用默认的颜色设置 */
		0,																/**< 无Alpha缓存 */
		0,																/**< 颜色缓存区中alpha成分的移位计数 */
		0,																/**< 无累计缓存区 */
		0, 0, 0, 0,														/**< 累计缓存区无移位 */
		32,																/**< 32位深度缓存 */
		0,																/**< 无蒙版缓存 */
		0,																/**< 无辅助缓存区 */
		PFD_MAIN_PLANE,													/**< 必须为PFD_MAIN_PLANE，设置为主绘图层 */
		0,																/**< 表示OpenGL实现所支持的上层或下层平面的数量 */
		0, 0, 0															/**< 过时，已不再使用 */
	};

	DWORD windowStyle = WS_OVERLAPPEDWINDOW & ~WS_SIZEBOX & ~WS_MAXIMIZEBOX;	/**< 定义我们窗口类型，使用常规设定，去掉最大化按钮，并不能改变窗体大小 */
	DWORD windowExtendedStyle = WS_EX_APPWINDOW;

	if (m_IsFullScreen == true)											/**< 如果为全屏模式，尝试转化为全屏模式 */
	{
		if (ChangeScreenSetting() == false)
		{																/**< 全屏模式转换失败，弹出对话框提示，并尝试窗口模式 */
			MessageBox(HWND_DESKTOP, _T("模式转换失败.\n在窗口模式下运行."), _T("Error"), MB_OK | MB_ICONEXCLAMATION);
			m_IsFullScreen = false;										/**< 设置为窗口模式 */
		}
		else															/**< 如果为窗口模式 */
		{
			ShowCursor(true);											/**< 隐藏鼠标 */
			windowStyle = WS_POPUP;										/**< 设置窗口模式为顶层窗口 */
			windowExtendedStyle |= WS_EX_TOPMOST;
		}
	}

	/// 调整我们窗口的大小，使其客户区的大小为我们设置的大小
	RECT windowRect = { GetPosX(), GetPosY(), GetPosX() + GetWidth(), GetPosY() + GetHeight() };
	if (m_IsFullScreen == false)										/**< 在窗口模式下使用 */
	{
		windowExtendedStyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;	/**< 使窗口具有3D外观 */
		int wid = GetSystemMetrics(SM_CXSCREEN);		/**< 获取当前屏幕宽 */
		int hei = GetSystemMetrics(SM_CYSCREEN);		/**< 获取当前屏幕高 */
		nX = (wid - GetWidth()) / 2;                    /**< 计算窗口居中用 */
		nY = (hei - GetHeight()) / 2;
		/// 调整我们窗口的大小，使其客户区的大小为我们设置的大小
		AdjustWindowRectEx(&windowRect, windowStyle, 0, windowExtendedStyle);
		/// 判断窗口的左上角是否隐藏在桌面外
		if (windowRect.left < 0)										/**< 如果窗口X坐标为负，移动坐标到0处，并调整窗口的位置 */
		{
			windowRect.right -= windowRect.left;
			windowRect.left = 0;
		}
		if (windowRect.top < 0)											/**< 如果窗口Y坐标为负，移动坐标到0处，并调整窗口的位置 */
		{
			windowRect.bottom -= windowRect.top;
			windowRect.top = 0;
		}
	}

	/// 创建窗口
	m_hWnd = CreateWindowEx(windowExtendedStyle,						/**< 窗口的扩展风格 */
		class_name,									/**< 窗口的类名 */
		window_title,								/**< 窗口标题 */
		windowStyle,								/**< 窗口的风格 */
		nX, nY,                                      /**< 窗口的左上角位置 */
		windowRect.right - windowRect.left,			/**< 窗口的宽度 */
		windowRect.bottom - windowRect.top,			/**< 窗口的高度 */
		HWND_DESKTOP,								/**< 窗口的父窗口为桌面 */
		0,											/**< 无菜单 */
		h_instance,									/**< 传入窗口的实例句柄 */
		lpParam);									/**< 传入程序类参数 */

	while (m_hWnd != NULL)													/**< 窗口是否创建成功 */
	{
		m_hDC = GetDC(m_hWnd);											/**< 返回窗口的设备描述表 */
		if (m_hDC == 0)													/**< 如果为空 */
		{																/**< 失败 */
			break;
		}

		//GLuint PixelFormat = ChoosePixelFormat(m_hDC, &pfd);			/**< 查找一个兼容的像素格式 */
		//if (PixelFormat == 0)											/**< 如果没找到 */
		//{																/**< 失败 */

		//}

		GLuint PixelFormat;
		if (!arbMultisampleSupported)
		{
			PixelFormat = ChoosePixelFormat(m_hDC, &pfd);				// Find A Compatible Pixel Format
			if (PixelFormat == 0)												// Did We Find A Compatible Format?
			{
				// Failed
				ReleaseDC(m_hWnd, m_hDC);							// Release Our Device Context
				m_hDC = 0;												// Zero The Device Context
				DestroyWindow(m_hWnd);									// Destroy The Window
				m_hWnd = 0;												// Zero The Window Handle
				break;												// Return False
			}

		}
		else
		{
			PixelFormat = arbMultisampleFormat;
		}

		if (SetPixelFormat(m_hDC, PixelFormat, &pfd) == false)			/**< 设置像素格式 */
		{																/**< 失败 */
			break;
		}
		m_hRC = wglCreateContext(m_hDC);								/**< 创建OpenGL的渲染描述表 */
		if (m_hRC == 0)													/**< 如果为空 */
		{																/**< 失败 */
			break;
		}
		if (wglMakeCurrent(m_hDC, m_hRC) == false)						/**< 设置当前的OpenGL的渲染对象为当前的窗口 */
		{																/**< 失败 */
			break;
		}

		if (!arbMultisampleSupported && CHECK_FOR_MULTISAMPLE)
		{

			if (InitMultisample(h_instance, m_hWnd, pfd))
			{

				Destroy();
				return Create(window_title, class_name, fullscreen, h_instance, lpParam);
			}
		}

		ShowWindow(m_hWnd, SW_NORMAL);									/**< 显示窗口 */
		ReshapeGL();													/**< 告诉OpenGL调整窗口大小 */
		return true;													/**< 成功返回 */
	}

	Destroy();															/**< 释放资源 */
	return false;														/**< 返回失败 */
}

/** 删除OpenGL窗口 */
void GLWindow_PDE::Destroy()
{
	if (m_hWnd != 0)										/**< 窗口句柄是否存在 */
	{
		if (m_hDC != 0)										/**< 窗口设备描述表是否存在 */
		{
			wglMakeCurrent(m_hDC, 0);						/**< 设置当前的OpenGL的渲染对象为空NULL */
			if (m_hRC != 0)									/**< OpenGL的渲染描述表是否存在 */
			{
				wglDeleteContext(m_hRC);					/**< 释放OpenGL的渲染描述表 */
				m_hRC = 0;									/**< 设置OpenGL的渲染描述表为0 */
			}
			ReleaseDC(m_hWnd, m_hDC);						/**< 释放窗口的设备描述表 */
			m_hDC = 0;										/**< 设置窗口的设备描述表为0 */
		}
		DestroyWindow(m_hWnd);								/**< 删除窗口 */
		m_hWnd = 0;											/**< 设置窗口句柄为0 */
	}

	if (m_IsFullScreen)										/**< 如果为全屏模式，在程序结束后，变换到窗口模式，并显示鼠标 */
	{
		ChangeDisplaySettings(NULL, 0);						/**< 变换到窗口模式 */
		ShowCursor(true);									/**< 显示鼠标 */
	}
}

//DimensionWorld======================================================================
#define GWL_USERDATA (-21)
/** 主程序入口 */
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	int ret = -1;
	DimensionWorld * dimension = DimensionWorld::Create(_T("DimensionWorld"));			/**< 创建程序类 */
	if (dimension != 0)
	{
		ret = dimension->Main(hInstance, hPrevInstance, lpCmdLine, nCmdShow);/**< 执行程序主循环 */
		delete dimension;													/**< 删除程序类（在继承类中，使用GL_Example * example = new GL_Example(class_name);分配了一块内存）*/
	}
	else
	{																	/**< 创建程序出错 */
		MessageBox(HWND_DESKTOP, _T("创建程序出错"), _T("Error"), MB_OK | MB_ICONEXCLAMATION);
	}
	return ret;
}

/** 处理窗口消息 */
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	LONG user_data = GetWindowLong(hWnd, GWL_USERDATA);					/**< 返回用户自定义的32位的程序附加值 */
	if (user_data == 0)
	{
		/// 如果程序第一次运行
		if (uMsg == WM_CREATE)											/**< 处理窗口创建消息 */
		{
			/// 返回窗口结构的指针，它保存刚创建的程序实例的类
			CREATESTRUCT * creation = reinterpret_cast<CREATESTRUCT *>(lParam);
			/// 获得程序实例的指针
			DimensionWorld * dimension = reinterpret_cast<DimensionWorld *>(creation->lpCreateParams);
			/// 保存程序实例的指针为用户自定义的程序附加值
			SetWindowLong(hWnd, GWL_USERDATA, reinterpret_cast<LONG>(dimension));
			dimension->m_IsVisible = true;									/**< 设置程序可见 */
			return 0;													/**< 返回 */
		}
	}
	else
	{	/// 如果不是第一次窗口，返回程序实例的指针
		DimensionWorld * appl = reinterpret_cast<DimensionWorld *>(user_data);
		return appl->Message(hWnd, uMsg, wParam, lParam);				/**< 调用程序实例自己的消息处理函数 */
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);					/**< 调用默认的窗口消息处理函数 */
}

/** 构造函数 */
DimensionWorld::DimensionWorld(const TCHAR * class_name)
{
	m_ClassName = class_name;											/**< 保存类名 */
	m_IsProgramLooping = true;											/**< 设置程序循环为true */
	m_CreateFullScreen = false;											/**< 使用全屏模式 */
	m_IsVisible = false;												/**< 不可见 */
	m_ResizeDraw = false;												/**< 在窗口改变大小的时候，不可绘制 */
	
	m_LastTickCount = 0;

}

void DimensionWorld::ToggleFullscreen()									/**< 切换 全屏/窗口模式 */
{
	PostMessage(m_Window, WM_TOGGLEFULLSCREEN, 0, 0);					/**< 发送自定的切换消息 */
}

void DimensionWorld::TerminateApplication()								/**< 结束程序 */
{
	PostMessage(m_Window, WM_QUIT, 0, 0);								/**< 发送退出消息 */
	m_IsProgramLooping = false;											/**< 停止程序循环 */
}

/** 消息循环 */
LRESULT DimensionWorld::Message(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)														/**< 处理不同的Windows消息 */
	{
	case WM_SYSCOMMAND:												/**< 截获系统命令 */
		switch (wParam)
		{
		case SC_SCREENSAVE:										/**< 截获屏幕保护启动命令 */
		case SC_MONITORPOWER:									/**< 截获显示其省电模式启动命令 */
			return 0;											/**< 不启用这两个命令 */
			break;
		}
		break;															/**< 退出 */

	case WM_CLOSE:													/**< 关闭窗口 */
		TerminateApplication();										/**< 调用TerminateApplication函数 */
		return 0;
		break;

	case WM_EXITMENULOOP:
	case WM_EXITSIZEMOVE:
		m_LastTickCount = GetTickCount();							/**< 更新计数器的值 */
		return 0;
		break;

	case WM_MOVE:
		m_Window.SetPosX(LOWORD(lParam));							/**< 更新鼠标的坐标 */
		m_Window.SetPosY(HIWORD(lParam));
		return 0;
		break;

	case WM_PAINT:
		if (m_ResizeDraw == true)									/**< 如果需要重绘 */
		{
			m_Window.ReshapeGL();									/**< 重新设置窗口的大小 */
			Draw();													/**< 重新绘制 */
			m_Window.SwapBuffers();									/**< 交换前后帧缓存 */
		}
		break;

	case WM_SIZING:													/**< 窗口正在改变大小 */
	{
		RECT * rect = (RECT *)lParam;
		m_Window.SetWidth(rect->right - rect->left);				/**< 设置窗口宽度 */
		m_Window.SetHeight(rect->bottom - rect->top);				/**< 设置窗口高度 */
		return TRUE;
	}
	break;

	case WM_SIZE:													/**< 窗口改变大小后 */
		switch (wParam)												/**< 处理不同的窗口状态 */
		{
		case SIZE_MINIMIZED:									/**< 是否最小化? */
			m_IsVisible = false;								/**< 如果是，则设置不可见 */
			return 0;
			break;

		case SIZE_MAXIMIZED:									/**< 窗口是否最大化? */
		case SIZE_RESTORED:										/**< 窗口被还原? */
			m_IsVisible = true;									/**< 设置为可见 */
			m_Window.SetWidth(LOWORD(lParam));					/**< 设置窗口宽度 */
			m_Window.SetHeight(HIWORD(lParam));					/**< 设置窗口高度 */
			m_Window.ReshapeGL();								/**< 改变窗口大小 */
			m_LastTickCount = GetTickCount();					/**< 更新计数器的值 */
			return 0;
			break;
		}
		break;

	case WM_KEYDOWN:												/**< 更新按键信息 */
		m_Keys.SetPressed(wParam);
		return 0;
		break;

	case WM_KEYUP:													/**< 更新释放键信息 */
		m_Keys.SetReleased(wParam);
		return 0;
		break;

	case WM_TOGGLEFULLSCREEN:										/**< 切换 全屏/窗口模式 */
																	/*  m_Window.SetFullScreen(!m_Window.GetFullScreen());
																	if(!m_Window.GetFullScreen())
																	ShowCursor(true);
																	else
																	ShowCursor(false);*/

		m_CreateFullScreen = !m_CreateFullScreen;
		PostMessage(hWnd, WM_QUIT, 0, 0);
		break;
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);					/**< 调用默认的窗口消息处理函数 */
}

/** 程序的主循环 */
int DimensionWorld::Main(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	/// 注册一个窗口
	WNDCLASSEX windowClass;												/**< 窗口类 */
	ZeroMemory(&windowClass, sizeof(WNDCLASSEX));						/**< 清空结构为0 */
	windowClass.cbSize = sizeof(WNDCLASSEX);					/**< 窗口结构的大小 */
	windowClass.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;	/**< 设置窗口类型为，移动时重画，并为窗口取得DC */
	windowClass.lpfnWndProc = (WNDPROC)(WindowProc);				/**< WndProc处理消息 */
	windowClass.hInstance = hInstance;							/**< 设置实例 */
	windowClass.hbrBackground = (HBRUSH)(COLOR_APPWORKSPACE);			/**< 设置背景 */
	windowClass.hCursor = LoadCursor(NULL, IDC_ARROW);			/**< 载入光标 */
	windowClass.lpszClassName = m_ClassName;							/**< 设置类名 */
	if (RegisterClassEx(&windowClass) == 0)								/**< 尝试注册窗口类 */
	{																	/**< NOTE: Failure, Should Never Happen */
		MessageBox(HWND_DESKTOP, _T("注册窗口失败!"), _T("Error"), MB_OK | MB_ICONEXCLAMATION);
		return -1;														/**< 退出并返回FALSE */
	}

	// 询问是否在全屏状态下运行?
	//if (MessageBox(HWND_DESKTOP, _T("你想在全屏状态下运行么 ?"), _T("是否全屏运行?"), MB_YESNO | MB_ICONQUESTION) == IDNO)
	//{
	//	m_CreateFullScreen = false;										/**< m_CreateFullScreen记录当前的显示模式为窗口 */
	//}
	
	while (m_IsProgramLooping)											/**< 循环直道WM_QUIT退出程序 */
	{
		/// 创建一个窗口
		if (m_Window.Create(_T(""), m_ClassName, m_CreateFullScreen, hInstance, this))
		{

			// 如果初始化失败，则退出
			if (!Init())									/**< 调用自定义的初始化函数 */
			{															/**< 失败 */
				TerminateApplication();									/**< 关闭窗口退出程序 */
			}
			else														/**< 成功开始消息循环 */
			{
				MSG msg;												/**< Window消息结构 */
				bool isMessagePumpActive = true;						/**< 当消息不为空时，处理消息循环 */
				m_LastTickCount = GetTickCount();						/**< 返回当前的计时器的值 */
				m_Keys.Clear();											/**< 清空所有的按键信息 */
			
				while (isMessagePumpActive == true)						/**< 当消息不为空时，处理消息循环 */
				{														/**< 成功创建窗口，检测窗口消息 */
					if (PeekMessage(&msg, m_Window, 0, 0, PM_REMOVE) != 0)
					{
						/// 检测是否为WM_QUIT消息
						if (msg.message != WM_QUIT)
						{
							DispatchMessage(&msg);						/**< 如果不是发送消息到消息回调函数中处理 */
						}
						else
						{
							isMessagePumpActive = false;				/**< 如果是，则退出 */
						}
					}
					/// 如果没有消息
					else
					{
						if (m_IsVisible == false)						/**< 如果窗口不可见 */
						{
							WaitMessage();								/**< 暂停程序，等待消息 */
						}
						else											/**< 如果窗口可见 */
						{
																		/**< 执行消息循环 */
							DWORD tickCount = GetTickCount();			/**< 返回计时器的当前值 */
							Update(tickCount - m_LastTickCount);		/**< 调用用户自定义的更新函数 */
							m_LastTickCount = tickCount;				/**< 重新设置上一次，计数器的值 */
							
							Draw();										/**< 调用用户自定义的绘制函数 */
							m_Window.SwapBuffers();						/**< 交换前后帧缓存 */
						}
					}
				}														/**< 如果isMessagePumpActive == true，则循环 */
			}
			/**< 程序结束 */
			Uninit();												/**< 用户自定义的卸载函数 */
			m_Window.Destroy();											/**< 删除窗口 */
		}
		else															/**< 如果创建窗口失败 */
		{
			MessageBox(HWND_DESKTOP, _T("创建OpenGL窗口错误"), _T("Error"), MB_OK | MB_ICONEXCLAMATION);
			m_IsProgramLooping = false;									/**< 停止程序循环 */
		}
	}

	UnregisterClass(m_ClassName, hInstance);							/**< 取消注册的窗口 */
	return 0;
}
