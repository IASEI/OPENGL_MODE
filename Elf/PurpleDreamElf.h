#ifndef __PURPLEDREAMELF_H__
#define __PURPLEDREAMELF_H__

#include "fantastic.h"

extern bool	arbMultisampleSupported;
extern int arbMultisampleFormat;

bool InitMultisample(HINSTANCE hInstance, HWND hWnd, PIXELFORMATDESCRIPTOR pfd);

//»ù±¾Àà=================================================================
class PurpleDreamElf
{
public:
	PurpleDreamElf();
	~PurpleDreamElf();
	static char *TcharTochar(const TCHAR *str,  char *cstr);
	static TCHAR *CharToTchar(const char *str, TCHAR *Tstr);

private:
	
	
};

#endif 

