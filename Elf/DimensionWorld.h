#ifndef __DIMENSIONWORLD_H__
#define __DIMENSIONWORLD_H__

#include "fantastic.h"
#include "PurpleDreamElf.h"
#include "FantasyMagic.h"

using namespace std;

/** windows������ */
class GLWindow_PDE 
{
public:
	/** ��Ҫ�Ĵ��ں���  */

	/** ���캯�� */
	GLWindow_PDE();
	/** ����windows���� */
	bool	Create(const TCHAR * window_title, const TCHAR * class_name, bool fullscreen, HINSTANCE h_instance, LPVOID lpParam);
	/** ɾ��OpenGL���� */
	void	Destroy();
	/** �ı䴰�ڵ���ʾ���� */
	bool	ChangeScreenSetting();
	/** �����ڴ�С�ı�ʱ��֪ͨOpenGL������С */
	void	ReshapeGL();
	/** Swap Buffers (Double Buffering) */
	void	SwapBuffers() { ::SwapBuffers(m_hDC); }

	/** ���溯��Ϊ����/���ش���������� */

	/** ���ô������Ͻǵ�λ�� */
	void	SetPosX(int x);
	void	SetPosX(unsigned short x) { SetPosX((signed short)x); }
	void	SetPosY(int y);
	void	SetPosY(unsigned short y) { SetPosY((signed short)y); }
	/** ���ش��ڵĴ�С */
	int		GetWidth();
	int		GetHeight();
	/** ���ô��ڵĴ�С */
	void	SetWidth(int width);
	void	SetHeight(int height);
	/** ���ش������Ͻǵ�λ�� */
	int		GetPosX();
	int		GetPosY();
	/** ���ô��ڵ���ɫλ�� */
	void	SetHiColor() { m_BitsPerPixel = 16; }
	void	SetTrueColor() { m_BitsPerPixel = 32; }
	//void	SetFullScreen(bool mode)	{ m_IsFullScreen = mode; }
	//bool	GetFullScreen()	{ return m_IsFullScreen; }
	/** �����������������GL_Window m_Window�������m_Window��Ϊ���ھ��ʹ�� */
	operator HWND() { return m_hWnd; }

	

private:
	HWND	m_hWnd;														/**< ���ھ�� */
	HDC		m_hDC;														/**< �豸������ */
	HGLRC	m_hRC;														/**< OpenGL��Ⱦ������ */

	int		m_WindowPosX;												/**< ���ڵ����Ͻǵ�Xλ�� */
	int		m_WindowPosY;												/**< ���ڵ����Ͻǵ�Yλ�� */
	int		m_WindowWidth;												/**< ���ڵĿ�� */
	int		m_WindowHeight;												/**< ���ڵĸ߶� */
	int		m_ScreenWidth;												/**< ȫ���Ŀ�� */
	int		m_ScreenHeight;												/**< ȫ���ĸ߶� */
	int		m_BitsPerPixel;												/**< ��ɫλ�� */
	bool	m_IsFullScreen;												/**< �Ƿ�ȫ�� */

	
};

/** ��������� */
class Keys
{
public:
	/** ���캯�� */
	Keys() { Clear(); }
	/** ������еİ�����Ϣ */
	void Clear() { ZeroMemory(&m_KeyDown, sizeof(m_KeyDown)); }
	/** �ж�ĳ�����Ƿ��� */
	bool IsPressed(unsigned int key) { return (key < MAX_KEYS) ? (m_KeyDown[key] == true) : false; }
	/** ����ĳ���������� */
	void SetPressed(unsigned int key) { if (key < MAX_KEYS) m_KeyDown[key] = true; }
	/** ����ĳ�������ͷ� */
	void SetReleased(unsigned int key) { if (key < MAX_KEYS) m_KeyDown[key] = false; }

private:
	static const unsigned int MAX_KEYS = 256;
	bool m_KeyDown[MAX_KEYS];									/**< ����256��������״̬ */
};

/** �����ĳ����࣬�̳�����������OpenGL���� */
class DimensionWorld
{
public:
	/** ����һ��ȫ�ֵ�Create����������������뱻�̳���ʵ�� */
	static DimensionWorld * Create(const TCHAR * class_name);	/**< �������Լ������� */
													/** ���������� */
	virtual ~DimensionWorld() {};
	
protected:
	/** ����ĺ������뱻�̳���ʵ�֣���ɻ�����OpenGL��Ⱦ���� */
	virtual bool	Init() = 0;							/**< OpenGL�ĳ�ʼ�� */
	virtual void	Uninit() = 0;							/**< OpenGL��ж�� */
	virtual void	Update(DWORD milliseconds) = 0;				/**< ִ��OpenGL����ĸ��� */
	virtual void	Draw() = 0;									/**< ����OpenGL���� */

	
protected:
	
	

	
	void	ToggleFullscreen();									/**< �л� ȫ��/����ģʽ */
	void	TerminateApplication();								/**< �������� */
	void	ResizeDraw(bool enable) { m_ResizeDraw = enable; }	/**< �����ڴ��ڸı��С��ʱ�򣬿��Ի��� */


	Keys	m_Keys;												/**< ������ */
																/** ���캯�� */
	DimensionWorld(const TCHAR * class_name);

private:

	/** �������ѭ�� */
	friend int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow);
	int		Main(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow);

	/** ��Ϣ����ص����� */
	friend LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	LRESULT	Message(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

	static const UINT WM_TOGGLEFULLSCREEN = (WM_USER + 1);		/**< �Զ�����Ϣ�����л�����ģʽ��ʱ���� */

	GLWindow_PDE	m_Window;										/**< Window�� */
	const TCHAR* m_ClassName;									/**< ������ */
	bool		m_IsProgramLooping;								/**< ����ѭ����ǣ����Ϊfalse�����˳����� */
	bool        m_CreateFullScreen;                             /**< ��Ϊtrue���򴴽�ȫ��ģʽ */
	bool		m_IsVisible;									/**< �����Ƿ�ɼ� */
	bool		m_ResizeDraw;									/**< �Ƿ��ڸı��Сʱ�������˻��ƺ��� */

	DWORD		m_LastTickCount;								/**< ��һ�μ�ʱ����ֵ */


};


#endif

