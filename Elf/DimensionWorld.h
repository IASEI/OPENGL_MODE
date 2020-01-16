#ifndef __DIMENSIONWORLD_H__
#define __DIMENSIONWORLD_H__

#include "fantastic.h"
#include "PurpleDreamElf.h"
#include "FantasyMagic.h"

using namespace std;

/** windows窗口类 */
class GLWindow_PDE 
{
public:
	/** 重要的窗口函数  */

	/** 构造函数 */
	GLWindow_PDE();
	/** 创建windows窗口 */
	bool	Create(const TCHAR * window_title, const TCHAR * class_name, bool fullscreen, HINSTANCE h_instance, LPVOID lpParam);
	/** 删除OpenGL窗口 */
	void	Destroy();
	/** 改变窗口的显示设置 */
	bool	ChangeScreenSetting();
	/** 当窗口大小改变时，通知OpenGL调整大小 */
	void	ReshapeGL();
	/** Swap Buffers (Double Buffering) */
	void	SwapBuffers() { ::SwapBuffers(m_hDC); }

	/** 下面函数为设置/返回窗口类的属性 */

	/** 设置窗口左上角的位置 */
	void	SetPosX(int x);
	void	SetPosX(unsigned short x) { SetPosX((signed short)x); }
	void	SetPosY(int y);
	void	SetPosY(unsigned short y) { SetPosY((signed short)y); }
	/** 返回窗口的大小 */
	int		GetWidth();
	int		GetHeight();
	/** 设置窗口的大小 */
	void	SetWidth(int width);
	void	SetHeight(int height);
	/** 返回窗口左上角的位置 */
	int		GetPosX();
	int		GetPosY();
	/** 设置窗口的颜色位深 */
	void	SetHiColor() { m_BitsPerPixel = 16; }
	void	SetTrueColor() { m_BitsPerPixel = 32; }
	//void	SetFullScreen(bool mode)	{ m_IsFullScreen = mode; }
	//bool	GetFullScreen()	{ return m_IsFullScreen; }
	/** 重载运算符，可以让GL_Window m_Window声明后的m_Window作为窗口句柄使用 */
	operator HWND() { return m_hWnd; }

	

private:
	HWND	m_hWnd;														/**< 窗口句柄 */
	HDC		m_hDC;														/**< 设备描述表 */
	HGLRC	m_hRC;														/**< OpenGL渲染描述表 */

	int		m_WindowPosX;												/**< 窗口的左上角的X位置 */
	int		m_WindowPosY;												/**< 窗口的左上角的Y位置 */
	int		m_WindowWidth;												/**< 窗口的宽度 */
	int		m_WindowHeight;												/**< 窗口的高度 */
	int		m_ScreenWidth;												/**< 全屏的宽度 */
	int		m_ScreenHeight;												/**< 全屏的高度 */
	int		m_BitsPerPixel;												/**< 颜色位深 */
	bool	m_IsFullScreen;												/**< 是否全屏 */

	
};

/** 定义键盘类 */
class Keys
{
public:
	/** 构造函数 */
	Keys() { Clear(); }
	/** 清空所有的按键信息 */
	void Clear() { ZeroMemory(&m_KeyDown, sizeof(m_KeyDown)); }
	/** 判断某个键是否按下 */
	bool IsPressed(unsigned int key) { return (key < MAX_KEYS) ? (m_KeyDown[key] == true) : false; }
	/** 设置某个键被按下 */
	void SetPressed(unsigned int key) { if (key < MAX_KEYS) m_KeyDown[key] = true; }
	/** 设置某个键被释放 */
	void SetReleased(unsigned int key) { if (key < MAX_KEYS) m_KeyDown[key] = false; }

private:
	static const unsigned int MAX_KEYS = 256;
	bool m_KeyDown[MAX_KEYS];									/**< 保存256个按键的状态 */
};

/** 基本的程序类，继承它用来创建OpenGL程序 */
class DimensionWorld
{
public:
	/** 创建一个全局的Create函数，这个函数必须被继承类实现 */
	static DimensionWorld * Create(const TCHAR * class_name);	/**< 创建你自己的子类 */
													/** 虚析构函数 */
	virtual ~DimensionWorld() {};
	
protected:
	/** 下面的函数必须被继承类实现，完成基本的OpenGL渲染过程 */
	virtual bool	Init() = 0;							/**< OpenGL的初始化 */
	virtual void	Uninit() = 0;							/**< OpenGL的卸载 */
	virtual void	Update(DWORD milliseconds) = 0;				/**< 执行OpenGL程序的更新 */
	virtual void	Draw() = 0;									/**< 绘制OpenGL场景 */

	
protected:
	
	

	
	void	ToggleFullscreen();									/**< 切换 全屏/窗口模式 */
	void	TerminateApplication();								/**< 结束程序 */
	void	ResizeDraw(bool enable) { m_ResizeDraw = enable; }	/**< 设置在窗口改变大小的时候，可以绘制 */


	Keys	m_Keys;												/**< 按键类 */
																/** 构造函数 */
	DimensionWorld(const TCHAR * class_name);

private:

	/** 程序的主循环 */
	friend int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow);
	int		Main(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow);

	/** 消息处理回调函数 */
	friend LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	LRESULT	Message(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

	static const UINT WM_TOGGLEFULLSCREEN = (WM_USER + 1);		/**< 自定义消息，在切换窗口模式的时候发送 */

	GLWindow_PDE	m_Window;										/**< Window类 */
	const TCHAR* m_ClassName;									/**< 程序名 */
	bool		m_IsProgramLooping;								/**< 程序循环标记，如果为false，则退出程序 */
	bool        m_CreateFullScreen;                             /**< 若为true，则创建全屏模式 */
	bool		m_IsVisible;									/**< 窗口是否可见 */
	bool		m_ResizeDraw;									/**< 是否在改变大小时，调用了绘制函数 */

	DWORD		m_LastTickCount;								/**< 上一次计时器的值 */


};


#endif

