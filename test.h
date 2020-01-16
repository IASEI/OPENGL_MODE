#ifndef __TEST_H__
#define __TEST_H__

#include "Elf\fantastic.h"

#include "Elf\DimensionWorld.h"
#include "Elf\FantasyMagic.h"
#include "Elf\PurpleDreamElf.h"


class My :public DimensionWorld
{
public:
	bool Init();
	void Uninit();
	void Update(DWORD milliseconds);
	void Draw();
	void UpdateCamera();
	My(const TCHAR * class_name);
private:
	ModelInput_PDE modelinput;
	ModelInput_PDE modelinput1;
	friend class GLApplication;
	


	float R;
	int t;
	Camera_PDE     m_Camera;

	GLint xRotation;
	GLint yRotation;




	
};
#endif
