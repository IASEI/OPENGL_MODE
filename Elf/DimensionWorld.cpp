#include "DimensionWorld.h"



//GLWindow_PDE======================================================================

/** ���캯�� */
GLWindow_PDE::GLWindow_PDE()
{
	m_WindowPosX = 0;												/**< ���ڵ����Ͻǵ�Xλ�� */
	m_WindowPosY = 0;												/**< ���ڵ����Ͻǵ�Yλ�� */
	m_WindowWidth = 1920/2;												/**< ���ڵĿ�� */
	m_WindowHeight = 1080/2;												/**< ���ڵĸ߶� */
	m_ScreenWidth = 1024;												/**< ȫ���Ŀ�� */
	m_ScreenHeight = 768;												/**< ȫ���ĸ߶� */
	m_BitsPerPixel = 16;												/**< ��ɫλ�� */
	m_IsFullScreen = false;											/**< ��ʹ��ȫ�� */

	m_hWnd = 0;
	m_hDC = 0;
	m_hRC = 0;
	
}

/** ���ش��ڵĴ�С */
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

/** ���ô��ڵĴ�С */
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

/** ���ش������Ͻǵ�λ�� */
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

/** ���ô������Ͻǵ�λ�� */
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

/** �����ڴ�С�ı�ʱ��֪ͨOpenGL������С */
void GLWindow_PDE::ReshapeGL()
{
	GLsizei width = GetWidth();
	GLsizei height = GetHeight();
	glViewport(0, 0, width, height);									/**< ���������ӿ� */
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f, (GLfloat)width / (GLfloat)height, 1.0f, 100000.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

/** �ı䴰�ڵ���ʾ���� */
bool GLWindow_PDE::ChangeScreenSetting()
{
	DEVMODE dmScreenSettings;											/**< �豸ģʽ */
	ZeroMemory(&dmScreenSettings, sizeof(DEVMODE));						/**< ����ṹ */
	dmScreenSettings.dmSize = sizeof(DEVMODE);					/**< �ṹ��С */
	dmScreenSettings.dmPelsWidth = GetWidth();						/**< ���ÿ�� */
	dmScreenSettings.dmPelsHeight = GetHeight();						/**< ���ø߶� */
	dmScreenSettings.dmBitsPerPel = m_BitsPerPixel;					/**< ����λ��� */
																	//dmScreenSettings.dmDisplayFrequency = 75;                           /**< ������Ļˢ���� */
	dmScreenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;//| DM_DISPLAYFREQUENCY;

																			 /// �ı���ʾģʽ
	if (ChangeDisplaySettings(&dmScreenSettings, 0) != DISP_CHANGE_SUCCESSFUL)
	{
		return false;													/**< ���ʧ�ܣ�����false */
	}

	return true;														/**< �ɹ����� */
}

/** ����windows���� */
bool GLWindow_PDE::Create(const TCHAR * window_title, const TCHAR * class_name, bool fullscreen, HINSTANCE h_instance, LPVOID lpParam)
{
	m_IsFullScreen = fullscreen;
	int nX = 0;
	int nY = 0;
	PIXELFORMATDESCRIPTOR pfd =											/**< �������������ṹ */
	{
		sizeof(PIXELFORMATDESCRIPTOR),									/**< ���������ṹ�Ĵ�С */
		1,																/**< �汾�� */
		PFD_DRAW_TO_WINDOW |											/**< �������������ʾ��һ�������� */
		PFD_SUPPORT_OPENGL |											/**< ������֧��OpenGL��ͼ */
		PFD_STEREO |											/**< ��ɫ�����������建�� */
		PFD_DOUBLEBUFFER,												/**< ��ɫ��������˫���� */
		PFD_TYPE_RGBA,													/**< ʹ��RGBA��ɫ��ʽ */
		m_BitsPerPixel,													/**< ��ɫ����������ɫֵ��ռ��λ�� */
		0, 0, 0, 0, 0, 0,												/**< ʹ��Ĭ�ϵ���ɫ���� */
		0,																/**< ��Alpha���� */
		0,																/**< ��ɫ��������alpha�ɷֵ���λ���� */
		0,																/**< ���ۼƻ����� */
		0, 0, 0, 0,														/**< �ۼƻ���������λ */
		32,																/**< 32λ��Ȼ��� */
		0,																/**< ���ɰ滺�� */
		0,																/**< �޸��������� */
		PFD_MAIN_PLANE,													/**< ����ΪPFD_MAIN_PLANE������Ϊ����ͼ�� */
		0,																/**< ��ʾOpenGLʵ����֧�ֵ��ϲ���²�ƽ������� */
		0, 0, 0															/**< ��ʱ���Ѳ���ʹ�� */
	};

	DWORD windowStyle = WS_OVERLAPPEDWINDOW & ~WS_SIZEBOX & ~WS_MAXIMIZEBOX;	/**< �������Ǵ������ͣ�ʹ�ó����趨��ȥ����󻯰�ť�������ܸı䴰���С */
	DWORD windowExtendedStyle = WS_EX_APPWINDOW;

	if (m_IsFullScreen == true)											/**< ���Ϊȫ��ģʽ������ת��Ϊȫ��ģʽ */
	{
		if (ChangeScreenSetting() == false)
		{																/**< ȫ��ģʽת��ʧ�ܣ������Ի�����ʾ�������Դ���ģʽ */
			MessageBox(HWND_DESKTOP, _T("ģʽת��ʧ��.\n�ڴ���ģʽ������."), _T("Error"), MB_OK | MB_ICONEXCLAMATION);
			m_IsFullScreen = false;										/**< ����Ϊ����ģʽ */
		}
		else															/**< ���Ϊ����ģʽ */
		{
			ShowCursor(true);											/**< ������� */
			windowStyle = WS_POPUP;										/**< ���ô���ģʽΪ���㴰�� */
			windowExtendedStyle |= WS_EX_TOPMOST;
		}
	}

	/// �������Ǵ��ڵĴ�С��ʹ��ͻ����Ĵ�СΪ�������õĴ�С
	RECT windowRect = { GetPosX(), GetPosY(), GetPosX() + GetWidth(), GetPosY() + GetHeight() };
	if (m_IsFullScreen == false)										/**< �ڴ���ģʽ��ʹ�� */
	{
		windowExtendedStyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;	/**< ʹ���ھ���3D��� */
		int wid = GetSystemMetrics(SM_CXSCREEN);		/**< ��ȡ��ǰ��Ļ�� */
		int hei = GetSystemMetrics(SM_CYSCREEN);		/**< ��ȡ��ǰ��Ļ�� */
		nX = (wid - GetWidth()) / 2;                    /**< ���㴰�ھ����� */
		nY = (hei - GetHeight()) / 2;
		/// �������Ǵ��ڵĴ�С��ʹ��ͻ����Ĵ�СΪ�������õĴ�С
		AdjustWindowRectEx(&windowRect, windowStyle, 0, windowExtendedStyle);
		/// �жϴ��ڵ����Ͻ��Ƿ�������������
		if (windowRect.left < 0)										/**< �������X����Ϊ�����ƶ����굽0�������������ڵ�λ�� */
		{
			windowRect.right -= windowRect.left;
			windowRect.left = 0;
		}
		if (windowRect.top < 0)											/**< �������Y����Ϊ�����ƶ����굽0�������������ڵ�λ�� */
		{
			windowRect.bottom -= windowRect.top;
			windowRect.top = 0;
		}
	}

	/// ��������
	m_hWnd = CreateWindowEx(windowExtendedStyle,						/**< ���ڵ���չ��� */
		class_name,									/**< ���ڵ����� */
		window_title,								/**< ���ڱ��� */
		windowStyle,								/**< ���ڵķ�� */
		nX, nY,                                      /**< ���ڵ����Ͻ�λ�� */
		windowRect.right - windowRect.left,			/**< ���ڵĿ�� */
		windowRect.bottom - windowRect.top,			/**< ���ڵĸ߶� */
		HWND_DESKTOP,								/**< ���ڵĸ�����Ϊ���� */
		0,											/**< �޲˵� */
		h_instance,									/**< ���봰�ڵ�ʵ����� */
		lpParam);									/**< ������������ */

	while (m_hWnd != NULL)													/**< �����Ƿ񴴽��ɹ� */
	{
		m_hDC = GetDC(m_hWnd);											/**< ���ش��ڵ��豸������ */
		if (m_hDC == 0)													/**< ���Ϊ�� */
		{																/**< ʧ�� */
			break;
		}

		//GLuint PixelFormat = ChoosePixelFormat(m_hDC, &pfd);			/**< ����һ�����ݵ����ظ�ʽ */
		//if (PixelFormat == 0)											/**< ���û�ҵ� */
		//{																/**< ʧ�� */

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

		if (SetPixelFormat(m_hDC, PixelFormat, &pfd) == false)			/**< �������ظ�ʽ */
		{																/**< ʧ�� */
			break;
		}
		m_hRC = wglCreateContext(m_hDC);								/**< ����OpenGL����Ⱦ������ */
		if (m_hRC == 0)													/**< ���Ϊ�� */
		{																/**< ʧ�� */
			break;
		}
		if (wglMakeCurrent(m_hDC, m_hRC) == false)						/**< ���õ�ǰ��OpenGL����Ⱦ����Ϊ��ǰ�Ĵ��� */
		{																/**< ʧ�� */
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

		ShowWindow(m_hWnd, SW_NORMAL);									/**< ��ʾ���� */
		ReshapeGL();													/**< ����OpenGL�������ڴ�С */
		return true;													/**< �ɹ����� */
	}

	Destroy();															/**< �ͷ���Դ */
	return false;														/**< ����ʧ�� */
}

/** ɾ��OpenGL���� */
void GLWindow_PDE::Destroy()
{
	if (m_hWnd != 0)										/**< ���ھ���Ƿ���� */
	{
		if (m_hDC != 0)										/**< �����豸�������Ƿ���� */
		{
			wglMakeCurrent(m_hDC, 0);						/**< ���õ�ǰ��OpenGL����Ⱦ����Ϊ��NULL */
			if (m_hRC != 0)									/**< OpenGL����Ⱦ�������Ƿ���� */
			{
				wglDeleteContext(m_hRC);					/**< �ͷ�OpenGL����Ⱦ������ */
				m_hRC = 0;									/**< ����OpenGL����Ⱦ������Ϊ0 */
			}
			ReleaseDC(m_hWnd, m_hDC);						/**< �ͷŴ��ڵ��豸������ */
			m_hDC = 0;										/**< ���ô��ڵ��豸������Ϊ0 */
		}
		DestroyWindow(m_hWnd);								/**< ɾ������ */
		m_hWnd = 0;											/**< ���ô��ھ��Ϊ0 */
	}

	if (m_IsFullScreen)										/**< ���Ϊȫ��ģʽ���ڳ�������󣬱任������ģʽ������ʾ��� */
	{
		ChangeDisplaySettings(NULL, 0);						/**< �任������ģʽ */
		ShowCursor(true);									/**< ��ʾ��� */
	}
}

//DimensionWorld======================================================================
#define GWL_USERDATA (-21)
/** ��������� */
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	int ret = -1;
	DimensionWorld * dimension = DimensionWorld::Create(_T("DimensionWorld"));			/**< ���������� */
	if (dimension != 0)
	{
		ret = dimension->Main(hInstance, hPrevInstance, lpCmdLine, nCmdShow);/**< ִ�г�����ѭ�� */
		delete dimension;													/**< ɾ�������ࣨ�ڼ̳����У�ʹ��GL_Example * example = new GL_Example(class_name);������һ���ڴ棩*/
	}
	else
	{																	/**< ����������� */
		MessageBox(HWND_DESKTOP, _T("�����������"), _T("Error"), MB_OK | MB_ICONEXCLAMATION);
	}
	return ret;
}

/** ��������Ϣ */
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	LONG user_data = GetWindowLong(hWnd, GWL_USERDATA);					/**< �����û��Զ����32λ�ĳ��򸽼�ֵ */
	if (user_data == 0)
	{
		/// ��������һ������
		if (uMsg == WM_CREATE)											/**< �����ڴ�����Ϣ */
		{
			/// ���ش��ڽṹ��ָ�룬������մ����ĳ���ʵ������
			CREATESTRUCT * creation = reinterpret_cast<CREATESTRUCT *>(lParam);
			/// ��ó���ʵ����ָ��
			DimensionWorld * dimension = reinterpret_cast<DimensionWorld *>(creation->lpCreateParams);
			/// �������ʵ����ָ��Ϊ�û��Զ���ĳ��򸽼�ֵ
			SetWindowLong(hWnd, GWL_USERDATA, reinterpret_cast<LONG>(dimension));
			dimension->m_IsVisible = true;									/**< ���ó���ɼ� */
			return 0;													/**< ���� */
		}
	}
	else
	{	/// ������ǵ�һ�δ��ڣ����س���ʵ����ָ��
		DimensionWorld * appl = reinterpret_cast<DimensionWorld *>(user_data);
		return appl->Message(hWnd, uMsg, wParam, lParam);				/**< ���ó���ʵ���Լ�����Ϣ������ */
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);					/**< ����Ĭ�ϵĴ�����Ϣ������ */
}

/** ���캯�� */
DimensionWorld::DimensionWorld(const TCHAR * class_name)
{
	m_ClassName = class_name;											/**< �������� */
	m_IsProgramLooping = true;											/**< ���ó���ѭ��Ϊtrue */
	m_CreateFullScreen = false;											/**< ʹ��ȫ��ģʽ */
	m_IsVisible = false;												/**< ���ɼ� */
	m_ResizeDraw = false;												/**< �ڴ��ڸı��С��ʱ�򣬲��ɻ��� */
	
	m_LastTickCount = 0;

}

void DimensionWorld::ToggleFullscreen()									/**< �л� ȫ��/����ģʽ */
{
	PostMessage(m_Window, WM_TOGGLEFULLSCREEN, 0, 0);					/**< �����Զ����л���Ϣ */
}

void DimensionWorld::TerminateApplication()								/**< �������� */
{
	PostMessage(m_Window, WM_QUIT, 0, 0);								/**< �����˳���Ϣ */
	m_IsProgramLooping = false;											/**< ֹͣ����ѭ�� */
}

/** ��Ϣѭ�� */
LRESULT DimensionWorld::Message(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)														/**< ����ͬ��Windows��Ϣ */
	{
	case WM_SYSCOMMAND:												/**< �ػ�ϵͳ���� */
		switch (wParam)
		{
		case SC_SCREENSAVE:										/**< �ػ���Ļ������������ */
		case SC_MONITORPOWER:									/**< �ػ���ʾ��ʡ��ģʽ�������� */
			return 0;											/**< ���������������� */
			break;
		}
		break;															/**< �˳� */

	case WM_CLOSE:													/**< �رմ��� */
		TerminateApplication();										/**< ����TerminateApplication���� */
		return 0;
		break;

	case WM_EXITMENULOOP:
	case WM_EXITSIZEMOVE:
		m_LastTickCount = GetTickCount();							/**< ���¼�������ֵ */
		return 0;
		break;

	case WM_MOVE:
		m_Window.SetPosX(LOWORD(lParam));							/**< ������������ */
		m_Window.SetPosY(HIWORD(lParam));
		return 0;
		break;

	case WM_PAINT:
		if (m_ResizeDraw == true)									/**< �����Ҫ�ػ� */
		{
			m_Window.ReshapeGL();									/**< �������ô��ڵĴ�С */
			Draw();													/**< ���»��� */
			m_Window.SwapBuffers();									/**< ����ǰ��֡���� */
		}
		break;

	case WM_SIZING:													/**< �������ڸı��С */
	{
		RECT * rect = (RECT *)lParam;
		m_Window.SetWidth(rect->right - rect->left);				/**< ���ô��ڿ�� */
		m_Window.SetHeight(rect->bottom - rect->top);				/**< ���ô��ڸ߶� */
		return TRUE;
	}
	break;

	case WM_SIZE:													/**< ���ڸı��С�� */
		switch (wParam)												/**< ����ͬ�Ĵ���״̬ */
		{
		case SIZE_MINIMIZED:									/**< �Ƿ���С��? */
			m_IsVisible = false;								/**< ����ǣ������ò��ɼ� */
			return 0;
			break;

		case SIZE_MAXIMIZED:									/**< �����Ƿ����? */
		case SIZE_RESTORED:										/**< ���ڱ���ԭ? */
			m_IsVisible = true;									/**< ����Ϊ�ɼ� */
			m_Window.SetWidth(LOWORD(lParam));					/**< ���ô��ڿ�� */
			m_Window.SetHeight(HIWORD(lParam));					/**< ���ô��ڸ߶� */
			m_Window.ReshapeGL();								/**< �ı䴰�ڴ�С */
			m_LastTickCount = GetTickCount();					/**< ���¼�������ֵ */
			return 0;
			break;
		}
		break;

	case WM_KEYDOWN:												/**< ���°�����Ϣ */
		m_Keys.SetPressed(wParam);
		return 0;
		break;

	case WM_KEYUP:													/**< �����ͷż���Ϣ */
		m_Keys.SetReleased(wParam);
		return 0;
		break;

	case WM_TOGGLEFULLSCREEN:										/**< �л� ȫ��/����ģʽ */
																	/*  m_Window.SetFullScreen(!m_Window.GetFullScreen());
																	if(!m_Window.GetFullScreen())
																	ShowCursor(true);
																	else
																	ShowCursor(false);*/

		m_CreateFullScreen = !m_CreateFullScreen;
		PostMessage(hWnd, WM_QUIT, 0, 0);
		break;
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);					/**< ����Ĭ�ϵĴ�����Ϣ������ */
}

/** �������ѭ�� */
int DimensionWorld::Main(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	/// ע��һ������
	WNDCLASSEX windowClass;												/**< ������ */
	ZeroMemory(&windowClass, sizeof(WNDCLASSEX));						/**< ��սṹΪ0 */
	windowClass.cbSize = sizeof(WNDCLASSEX);					/**< ���ڽṹ�Ĵ�С */
	windowClass.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;	/**< ���ô�������Ϊ���ƶ�ʱ�ػ�����Ϊ����ȡ��DC */
	windowClass.lpfnWndProc = (WNDPROC)(WindowProc);				/**< WndProc������Ϣ */
	windowClass.hInstance = hInstance;							/**< ����ʵ�� */
	windowClass.hbrBackground = (HBRUSH)(COLOR_APPWORKSPACE);			/**< ���ñ��� */
	windowClass.hCursor = LoadCursor(NULL, IDC_ARROW);			/**< ������ */
	windowClass.lpszClassName = m_ClassName;							/**< �������� */
	if (RegisterClassEx(&windowClass) == 0)								/**< ����ע�ᴰ���� */
	{																	/**< NOTE: Failure, Should Never Happen */
		MessageBox(HWND_DESKTOP, _T("ע�ᴰ��ʧ��!"), _T("Error"), MB_OK | MB_ICONEXCLAMATION);
		return -1;														/**< �˳�������FALSE */
	}

	// ѯ���Ƿ���ȫ��״̬������?
	//if (MessageBox(HWND_DESKTOP, _T("������ȫ��״̬������ô ?"), _T("�Ƿ�ȫ������?"), MB_YESNO | MB_ICONQUESTION) == IDNO)
	//{
	//	m_CreateFullScreen = false;										/**< m_CreateFullScreen��¼��ǰ����ʾģʽΪ���� */
	//}
	
	while (m_IsProgramLooping)											/**< ѭ��ֱ��WM_QUIT�˳����� */
	{
		/// ����һ������
		if (m_Window.Create(_T(""), m_ClassName, m_CreateFullScreen, hInstance, this))
		{

			// �����ʼ��ʧ�ܣ����˳�
			if (!Init())									/**< �����Զ���ĳ�ʼ������ */
			{															/**< ʧ�� */
				TerminateApplication();									/**< �رմ����˳����� */
			}
			else														/**< �ɹ���ʼ��Ϣѭ�� */
			{
				MSG msg;												/**< Window��Ϣ�ṹ */
				bool isMessagePumpActive = true;						/**< ����Ϣ��Ϊ��ʱ��������Ϣѭ�� */
				m_LastTickCount = GetTickCount();						/**< ���ص�ǰ�ļ�ʱ����ֵ */
				m_Keys.Clear();											/**< ������еİ�����Ϣ */
			
				while (isMessagePumpActive == true)						/**< ����Ϣ��Ϊ��ʱ��������Ϣѭ�� */
				{														/**< �ɹ��������ڣ���ⴰ����Ϣ */
					if (PeekMessage(&msg, m_Window, 0, 0, PM_REMOVE) != 0)
					{
						/// ����Ƿ�ΪWM_QUIT��Ϣ
						if (msg.message != WM_QUIT)
						{
							DispatchMessage(&msg);						/**< ������Ƿ�����Ϣ����Ϣ�ص������д��� */
						}
						else
						{
							isMessagePumpActive = false;				/**< ����ǣ����˳� */
						}
					}
					/// ���û����Ϣ
					else
					{
						if (m_IsVisible == false)						/**< ������ڲ��ɼ� */
						{
							WaitMessage();								/**< ��ͣ���򣬵ȴ���Ϣ */
						}
						else											/**< ������ڿɼ� */
						{
																		/**< ִ����Ϣѭ�� */
							DWORD tickCount = GetTickCount();			/**< ���ؼ�ʱ���ĵ�ǰֵ */
							Update(tickCount - m_LastTickCount);		/**< �����û��Զ���ĸ��º��� */
							m_LastTickCount = tickCount;				/**< ����������һ�Σ���������ֵ */
							
							Draw();										/**< �����û��Զ���Ļ��ƺ��� */
							m_Window.SwapBuffers();						/**< ����ǰ��֡���� */
						}
					}
				}														/**< ���isMessagePumpActive == true����ѭ�� */
			}
			/**< ������� */
			Uninit();												/**< �û��Զ����ж�غ��� */
			m_Window.Destroy();											/**< ɾ������ */
		}
		else															/**< �����������ʧ�� */
		{
			MessageBox(HWND_DESKTOP, _T("����OpenGL���ڴ���"), _T("Error"), MB_OK | MB_ICONEXCLAMATION);
			m_IsProgramLooping = false;									/**< ֹͣ����ѭ�� */
		}
	}

	UnregisterClass(m_ClassName, hInstance);							/**< ȡ��ע��Ĵ��� */
	return 0;
}
