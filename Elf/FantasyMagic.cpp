#include "FantasyMagic.h"
#include "PurpleDreamElf.h"


Texture_PDE::Texture_PDE()
{

}

Texture_PDE::~Texture_PDE()
{

}

bool Texture_PDE::LoadBitmap(const char *file, IMID *imid)
{
	FILE *pFile = 0; /**< �ļ�ָ�� */

					 /** ����λͼ�ļ���Ϣ��λͼ�ļ�ͷ�ṹ */
	BITMAPINFOHEADER bitmapInfoHeader;
	BITMAPFILEHEADER header;

	unsigned char textureColors = 0;/**< ���ڽ�ͼ����ɫ��BGR�任��RGB */

									/** ���ļ�,�������� */
	pFile = fopen(file, "rb");
	if (pFile == 0) return false;

	/** ����λͼ�ļ�ͷ��Ϣ */
	fread(&header, sizeof(BITMAPFILEHEADER), 1, pFile);

	/** �����ļ��Ƿ�Ϊλͼ�ļ� */
	if (header.bfType != BITMAP_ID)
	{
		fclose(pFile);             /**< ������λͼ�ļ�,��ر��ļ������� */
		return false;
	}

	/** ����λͼ�ļ���Ϣ */
	fread(&bitmapInfoHeader, sizeof(BITMAPINFOHEADER), 1, pFile);

	/** ����ͼ��Ŀ�Ⱥ͸߶� */
	imid->width = bitmapInfoHeader.biWidth;
	imid->height = bitmapInfoHeader.biHeight;

	/** ȷ����ȡ���ݵĴ�С */
	if (bitmapInfoHeader.biSizeImage == 0)
		bitmapInfoHeader.biSizeImage = bitmapInfoHeader.biWidth *
		bitmapInfoHeader.biHeight * 3;

	/** ��ָ���Ƶ����ݿ�ʼλ�� */
	fseek(pFile, header.bfOffBits, SEEK_SET);

	/** �����ڴ� */
	imid->pixels = new unsigned char[bitmapInfoHeader.biSizeImage];

	/** ����ڴ�����Ƿ�ɹ� */
	if (!imid->pixels)                        /**< �������ڴ�ʧ���򷵻� */
	{
		delete[] imid->pixels;
		fclose(pFile);
		return false;
	}

	/** ��ȡͼ������ */
	fread(imid->pixels, 1, bitmapInfoHeader.biSizeImage, pFile);

	/** ��ͼ����ɫ���ݸ�ʽ���н���,��BGRת��ΪRGB */
	for (int index = 0; index < (int)bitmapInfoHeader.biSizeImage; index += 3)
	{
		textureColors = imid->pixels[index];
		imid->pixels[index] = imid->pixels[index + 2];
		imid->pixels[index + 2] = textureColors;
	}

	fclose(pFile);       /**< �ر��ļ� */
	return true;         /**< �ɹ����� */
}

int Texture_PDE::CreateTextures(char *path, char *name)
{
	IMID textures;
	//1 ��ȡͼƬ��ʽ
	FREE_IMAGE_FORMAT fifmt = FreeImage_GetFileType(path, 0);

	//2 ����ͼƬ
	FIBITMAP    *dib = FreeImage_Load(fifmt, path, 0);

	//3 ת��Ϊrgb 24ɫ
	dib = FreeImage_ConvertTo24Bits(dib);

	//4 ��ȡ����ָ��
	textures.pixels = (BYTE*)FreeImage_GetBits(dib);

	textures.width = FreeImage_GetWidth(dib);
	textures.height = FreeImage_GetHeight(dib);

	/**
	*   ����һ������Id,������Ϊ��������������Ĳ����������������id
	*/
	strcpy(textures.name, name);
	glGenTextures(1, &textures.id);

	glBindTexture(GL_TEXTURE_2D, textures.id);

	//  ָ������ķŴ�,��С�˲���ʹ�����Է�ʽ������ͼƬ�Ŵ��ʱ���ֵ��ʽ

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
	/**
	*   ��ͼƬ��rgb�����ϴ���opengl.
	*/
	/*glTexImage2D(
	GL_TEXTURE_2D,      //! ָ���Ƕ�άͼƬ
	0,                  //! ָ��Ϊ��һ�������������mipmap,��lod,����ľͲ��ü����ģ�Զ��ʹ�ý�С������
	3,             //! �����ʹ�õĴ洢��ʽ
	textures.width,              //! ��ȣ���һ����Կ�����֧�ֲ��������������Ⱥ͸߶Ȳ���2^n��
	textures.height,             //! ��ȣ���һ����Կ�����֧�ֲ��������������Ⱥ͸߶Ȳ���2^n��
	0,                  //! �Ƿ�ı�
	GL_BGR,         //! ���ݵĸ�ʽ��bmp�У�windows,����ϵͳ�д洢��������bgr��ʽ
	GL_UNSIGNED_BYTE,   //! ������8bit����
	textures.pixels
	);
	*/
	gluBuild2DMipmaps(GL_TEXTURE_2D, 3, textures.width, textures.height, GL_BGR, GL_UNSIGNED_BYTE, textures.pixels);
	texture.push_back(textures);
	FreeImage_Unload(dib);
	return textures.id;
}

int Texture_PDE::CreateBitTextures(TCHAR *path, char *name)
{
	IMID textures;

	/** ����λͼ */
	char filename[255] = { "===" };
	int iLength;
	//��ȡ�ֽڳ���   
	iLength = WideCharToMultiByte(CP_ACP, 0, path, -1, NULL, 0, NULL, NULL);
	//��tcharֵ����_char    
	WideCharToMultiByte(CP_ACP, 0, path, -1, filename, iLength, NULL, NULL);

	//PurpleDreamElf::TcharTochar(, filename);

	if (!LoadBitmap(filename, &textures))
	{
		MessageBox(NULL, L"����λͼ�ļ�ʧ��!", L"����", MB_OK);
		return NULL;
	}
	/** ��������������� */
	glGenTextures(1, &textures.id);

	/** ����������� */
	glBindTexture(GL_TEXTURE_2D, textures.id);

	/** �����˲� */
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	/** �������� */
	gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, textures.width,
		textures.height, GL_RGB, GL_UNSIGNED_BYTE,
		textures.pixels);
	texture.push_back(textures);
	return textures.id;

}

void Texture_PDE::StartTextures(bool start)
{
	if (start)
	{
		glEnable(GL_TEXTURE_2D);
	}
	else
	{
		glDisable(GL_TEXTURE_2D);
	}
}

void Texture_PDE::SetImidVector(vector<IMID>* ttd)
{

}

GLuint Texture_PDE::GetTexturesIndex(char *name)
{

	return NULL;
}

//Vector3_PDE======================================================================

float Vector3_PDE::length()
{
	return (float)(x * x + y * y + z * z);
}

Vector3_PDE::Vector3_PDE()
{
	x = 0.0; y = 0.0; z = 0.0;
}

Vector3_PDE::Vector3_PDE(float xx, float yy, float zz)
{
	x = xx;
	y = yy;
	z = zz;
}

Vector3_PDE::Vector3_PDE(const Vector3_PDE& vec)
{
	x = vec.x;
	y = vec.y;
	z = vec.z;
}

Vector3_PDE::Vector3_PDE(float xx, float yy, float zz, float ww)
{
	///��ʼ��.
	x = xx;
	y = yy;
	z = zz;
	w = ww;
}
/** ��λ��һ���� */
Vector3_PDE Vector3_PDE::normalize()
{
	float len = length();                  /**< ������������ */
	if (len == 0)
		len = 1;
	x = x / len;
	y = y / len;
	z = z / len;

	return *this;
}

/** ��� */
float Vector3_PDE::dotProduct(const Vector3_PDE& v)
{
	return (x * v.x + y * v.y + z * v.z);
}

/** ��� */
Vector3_PDE Vector3_PDE::crossProduct(const Vector3_PDE& v)
{
	Vector3_PDE vec;

	vec.x = y * v.z - z * v.y;
	vec.y = z * v.x - x * v.z;
	vec.z = x * v.y - y * v.x;

	return vec;
}

/** ������ + */
Vector3_PDE Vector3_PDE::operator +(const Vector3_PDE& v)
{
	Vector3_PDE vec;

	vec.x = x + v.x;
	vec.y = y + v.y;
	vec.z = z + v.z;

	return vec;
}

/** ������ - */
Vector3_PDE Vector3_PDE::operator -(const Vector3_PDE& v)
{
	Vector3_PDE vec;

	vec.x = x - v.x;
	vec.y = y - v.y;
	vec.z = z - v.z;

	return vec;
}

/** ������ * */
Vector3_PDE Vector3_PDE::operator *(const Vector3_PDE& v)
{
	Vector3_PDE vec;

	vec.x = x * v.x;
	vec.y = y * v.y;
	vec.z = z * v.z;

	return vec;
}
/** ������ / */
Vector3_PDE Vector3_PDE::operator /(const Vector3_PDE& v)
{
	Vector3_PDE vec;

	vec.x = x / v.x;
	vec.y = y / v.y;
	vec.z = z / v.z;

	return vec;
}
/** ������ + */
Vector3_PDE Vector3_PDE::operator +(float f)
{
	x = x + f;
	y = y + f;
	z = z + f;

	return *this;
}

Vector3_PDE Vector3_PDE::operator -(float f)
{
	x = x - f;
	y = y - f;
	z = z - f;

	return *this;
}

/** ������ * */
Vector3_PDE Vector3_PDE::operator *(float f)
{
	x = x * f;
	y = y * f;
	z = z * f;

	return *this;
}

/** ������ / */
Vector3_PDE Vector3_PDE::operator /(float f)
{
	if (f != 0.0)
	{
		x = x / f;
		y = y / f;
		z = z / f;
	}
	return *this;
}

void Vector3_PDE::operator +=(const Vector3_PDE& v)
{
	x += v.x;
	y += v.y;
	z += v.z;


}

void Vector3_PDE::operator -=(const Vector3_PDE& v)
{
	x -= v.x;
	y -= v.y;
	z -= v.z;


}

void Vector3_PDE::operator *=(const Vector3_PDE& v)
{
	x *= v.x;
	y *= v.y;
	z *= v.z;


}

void Vector3_PDE::operator /=(const Vector3_PDE& v)
{
	x /= v.x;
	y /= v.y;
	z /= v.z;


}

void Vector3_PDE::operator +=(float &v)
{
	x += v;
	y += v;
	z += v;

}

void  Vector3_PDE::operator -=(float &v)
{
	x -= v;
	y -= v;
	z -= v;


}

/** ������ * */
void Vector3_PDE::operator *=(float &v)
{
	x *= v;
	y *= v;
	z *= v;


}

/** ������ / */
void Vector3_PDE::operator /=(float &v)
{
	if (v != 0.0)
	{
		x /= v;
		y /= v;
		z /= v;
	}

}

bool Vector3_PDE::operator ==(Vector3_PDE &v)
{
	return ((x == v.x) && (y == v.y) && (z == v.z));
}

bool Vector3_PDE::operator !=(Vector3_PDE &v)
{
	return ((x == v.x) && (y == v.y) && (z == v.z));
}

/// ���
void Vector3_PDE::CrossProduct(Vector3_PDE &v1, Vector3_PDE &v2)
{

	x = ((v1.y * v2.z) - (v1.z * v2.y));
	y = ((v1.z * v2.x) - (v1.x * v2.z));
	z = ((v1.x * v2.y) - (v1.y * v2.x));
}

void Vector3_PDE::CrossProduct3(Vector3_PDE &v1, Vector3_PDE &v2, Vector3_PDE &v3)
{
	///���v1,v2,v3�Ĳ��
	x = v1.y * v2.z * v3.w +
		v1.z * v2.w * v3.y +
		v1.w * v2.y * v3.z -
		v1.y * v2.w * v3.z -
		v1.z * v2.y * v3.w -
		v1.w * v2.z * v3.y;

	y = v1.x * v2.w * v3.z +
		v1.z * v2.x * v3.w +
		v1.w * v2.z * v3.x -
		v1.x * v2.z * v3.w -
		v1.z * v2.w * v3.x -
		v1.w * v2.x * v3.z;

	z = v1.x * v2.y * v3.w +
		v1.y * v2.w * v3.x +
		v1.w * v2.x * v3.y -
		v1.x * v2.w * v3.y -
		v1.y * v2.x * v3.w -
		v1.w * v2.y * v3.x;

	w = v1.x * v2.z * v3.y +
		v1.y * v2.x * v3.z +
		v1.z * v2.y * v3.x -
		v1.x * v2.y * v3.z -
		v1.y * v2.z * v3.x -
		v1.z * v2.x * v3.y;
}

/// ���
float Vector3_PDE::DotProduct3(Vector3_PDE &v1)
{
	return x * v1.x + y * v1.y + z * v1.z;
}

float Vector3_PDE::DotProduct4(Vector3_PDE &v1)
{
	return x * v1.x + y * v1.y + z * v1.z + w * v1.w;
}

/** ���� */
Vector3_PDE Vector3_PDE::operator -()
{
	Vector3_PDE vec(-x, -y, -z);
	return vec;
}

//Matrix4x4_PDE======================================================================

Matrix4x4_PDE::Matrix4x4_PDE()
{
	///��ʼ����Ԫ��
	Clear();
}

Matrix4x4_PDE::Matrix4x4_PDE(const Matrix4x4_PDE &m)
{
	matrix[0] = m.matrix[0];
	matrix[4] = m.matrix[4];
	matrix[8] = m.matrix[8];
	matrix[12] = m.matrix[12];

	matrix[1] = m.matrix[1];
	matrix[5] = m.matrix[5];
	matrix[9] = m.matrix[9];
	matrix[13] = m.matrix[13];

	matrix[2] = m.matrix[2];
	matrix[6] = m.matrix[6];
	matrix[10] = m.matrix[10];
	matrix[14] = m.matrix[14];

	matrix[3] = m.matrix[3];
	matrix[7] = m.matrix[7];
	matrix[11] = m.matrix[11];
	matrix[15] = m.matrix[15];
}

Matrix4x4_PDE::Matrix4x4_PDE(float r11, float r12, float r13, float r14,
	float r21, float r22, float r23, float r24,
	float r31, float r32, float r33, float r34,
	float r41, float r42, float r43, float r44)
{

	matrix[0] = r11; matrix[1] = r12; matrix[2] = r13; matrix[3] = r14;
	matrix[4] = r21; matrix[5] = r22; matrix[6] = r23; matrix[7] = r24;
	matrix[8] = r31; matrix[9] = r32; matrix[10] = r33; matrix[11] = r34;
	matrix[12] = r41; matrix[13] = r42; matrix[14] = r43; matrix[15] = r44;
}

Matrix4x4_PDE::~Matrix4x4_PDE()
{

}

void Matrix4x4_PDE::operator =(Matrix4x4_PDE m)
{

	matrix[0] = m.matrix[0]; matrix[1] = m.matrix[1]; matrix[2] = m.matrix[2];
	matrix[3] = m.matrix[3];
	matrix[4] = m.matrix[4]; matrix[5] = m.matrix[5]; matrix[6] = m.matrix[6];
	matrix[7] = m.matrix[7];
	matrix[8] = m.matrix[8]; matrix[9] = m.matrix[9]; matrix[10] = m.matrix[10];
	matrix[11] = m.matrix[11];
	matrix[12] = m.matrix[12]; matrix[13] = m.matrix[13]; matrix[14] = m.matrix[14];
	matrix[15] = m.matrix[15];
}

/// �������
Matrix4x4_PDE Matrix4x4_PDE::operator -(Matrix4x4_PDE m)
{

	return Matrix4x4_PDE(matrix[0] - m.matrix[0], matrix[1] - m.matrix[1], matrix[2] - m.matrix[2],
		matrix[3] - m.matrix[3], matrix[4] - m.matrix[4], matrix[5] - m.matrix[5],
		matrix[6] - m.matrix[6], matrix[7] - m.matrix[7], matrix[8] - m.matrix[8],
		matrix[9] - m.matrix[9], matrix[10] - m.matrix[10], matrix[11] - m.matrix[11],
		matrix[12] - m.matrix[12], matrix[13] - m.matrix[13],
		matrix[14] - m.matrix[14], matrix[15] - m.matrix[15]);
}

/// �������
Matrix4x4_PDE Matrix4x4_PDE::operator +(Matrix4x4_PDE m)
{

	return Matrix4x4_PDE(matrix[0] + m.matrix[0], matrix[1] + m.matrix[1], matrix[2] + m.matrix[2],
		matrix[3] + m.matrix[3], matrix[4] + m.matrix[4], matrix[5] + m.matrix[5],
		matrix[6] + m.matrix[6], matrix[7] + m.matrix[7], matrix[8] + m.matrix[8],
		matrix[9] + m.matrix[9], matrix[10] + m.matrix[10], matrix[11] + m.matrix[11],
		matrix[12] + m.matrix[12], matrix[13] + m.matrix[13],
		matrix[14] + m.matrix[14], matrix[15] + m.matrix[15]);
}

/// �������
Matrix4x4_PDE Matrix4x4_PDE::operator *(Matrix4x4_PDE m)
{

	float newMatrix[16];
	const float *m1 = matrix, *m2 = m.matrix;

	newMatrix[0] = m1[0] * m2[0] + m1[4] * m2[1] + m1[8] * m2[2];
	newMatrix[1] = m1[1] * m2[0] + m1[5] * m2[1] + m1[9] * m2[2];
	newMatrix[2] = m1[2] * m2[0] + m1[6] * m2[1] + m1[10] * m2[2];
	newMatrix[3] = 0;

	newMatrix[4] = m1[0] * m2[4] + m1[4] * m2[5] + m1[8] * m2[6];
	newMatrix[5] = m1[1] * m2[4] + m1[5] * m2[5] + m1[9] * m2[6];
	newMatrix[6] = m1[2] * m2[4] + m1[6] * m2[5] + m1[10] * m2[6];
	newMatrix[7] = 0;

	newMatrix[8] = m1[0] * m2[8] + m1[4] * m2[9] + m1[8] * m2[10];
	newMatrix[9] = m1[1] * m2[8] + m1[5] * m2[9] + m1[9] * m2[10];
	newMatrix[10] = m1[2] * m2[8] + m1[6] * m2[9] + m1[10] * m2[10];
	newMatrix[11] = 0;

	newMatrix[12] = m1[0] * m2[12] + m1[4] * m2[13] + m1[8] * m2[14] + m1[12];
	newMatrix[13] = m1[1] * m2[12] + m1[5] * m2[13] + m1[9] * m2[14] + m1[13];
	newMatrix[14] = m1[2] * m2[12] + m1[6] * m2[13] + m1[10] * m2[14] + m1[14];
	newMatrix[15] = 1;

	return Matrix4x4_PDE(newMatrix[0], newMatrix[1], newMatrix[2], newMatrix[3], newMatrix[4],
		newMatrix[5], newMatrix[6], newMatrix[7], newMatrix[8], newMatrix[9],
		newMatrix[10], newMatrix[11], newMatrix[12], newMatrix[13], newMatrix[14],
		newMatrix[15]);
}

/// �������
Matrix4x4_PDE Matrix4x4_PDE::operator /(Matrix4x4_PDE m)
{
	return Matrix4x4_PDE(matrix[0] / m.matrix[0] + matrix[4] / m.matrix[1] + matrix[8] /
		m.matrix[2] + matrix[12] / m.matrix[3],
		matrix[1] / m.matrix[0] + matrix[5] / m.matrix[1] + matrix[9] /
		m.matrix[2] + matrix[13] / m.matrix[3],
		matrix[2] / m.matrix[0] + matrix[6] / m.matrix[1] + matrix[10] /
		m.matrix[2] + matrix[14] / m.matrix[3],
		matrix[3] / m.matrix[0] + matrix[7] / m.matrix[1] + matrix[11] /
		m.matrix[2] + matrix[15] / m.matrix[3],
		matrix[0] / m.matrix[4] + matrix[4] / m.matrix[5] + matrix[8] /
		m.matrix[6] + matrix[12] / m.matrix[7],
		matrix[1] / m.matrix[4] + matrix[5] / m.matrix[5] + matrix[9] /
		m.matrix[6] + matrix[13] / m.matrix[7],
		matrix[2] / m.matrix[4] + matrix[6] / m.matrix[5] + matrix[10] /
		m.matrix[6] + matrix[14] / m.matrix[7],
		matrix[3] / m.matrix[4] + matrix[7] / m.matrix[5] + matrix[11] /
		m.matrix[6] + matrix[15] / m.matrix[7],
		matrix[0] / m.matrix[8] + matrix[4] / m.matrix[9] + matrix[8] /
		m.matrix[10] + matrix[12] / m.matrix[11],
		matrix[1] / m.matrix[8] + matrix[5] / m.matrix[9] + matrix[9] /
		m.matrix[10] + matrix[13] / m.matrix[11],
		matrix[2] / m.matrix[8] + matrix[6] / m.matrix[9] + matrix[10] /
		m.matrix[10] + matrix[14] / m.matrix[11],
		matrix[3] / m.matrix[8] + matrix[7] / m.matrix[9] + matrix[11] /
		m.matrix[10] + matrix[15] / m.matrix[11],
		matrix[0] / m.matrix[12] + matrix[4] / m.matrix[13] + matrix[8] /
		m.matrix[14] + matrix[12] / m.matrix[15],
		matrix[1] / m.matrix[12] + matrix[5] / m.matrix[13] + matrix[9] /
		m.matrix[14] + matrix[13] / m.matrix[15],
		matrix[2] / m.matrix[12] + matrix[6] / m.matrix[13] + matrix[10] /
		m.matrix[14] + matrix[14] / m.matrix[15],
		matrix[3] / m.matrix[12] + matrix[7] / m.matrix[13] + matrix[11] /
		m.matrix[14] + matrix[15] / m.matrix[15]);
}

Matrix4x4_PDE Matrix4x4_PDE::operator -(float f)
{
	return Matrix4x4_PDE(matrix[0] - f, matrix[1] - f, matrix[2] - f, matrix[3] - f,
		matrix[4] - f, matrix[5] - f, matrix[6] - f, matrix[7] - f,
		matrix[8] - f, matrix[9] - f, matrix[10] - f, matrix[11] - f,
		matrix[12] - f, matrix[13] - f, matrix[14] - f, matrix[15] - f);
}

Matrix4x4_PDE Matrix4x4_PDE::operator +(float f)
{
	return Matrix4x4_PDE(matrix[0] + f, matrix[1] + f, matrix[2] + f, matrix[3] + f,
		matrix[4] + f, matrix[5] + f, matrix[6] + f, matrix[7] + f,
		matrix[8] + f, matrix[9] + f, matrix[10] + f, matrix[11] + f,
		matrix[12] + f, matrix[13] + f, matrix[14] + f, matrix[15] + f);
}

Matrix4x4_PDE Matrix4x4_PDE::operator *(float f)
{
	return Matrix4x4_PDE(matrix[0] * f, matrix[1] * f, matrix[2] * f, matrix[3] * f,
		matrix[4] * f, matrix[5] * f, matrix[6] * f, matrix[7] * f,
		matrix[8] * f, matrix[9] * f, matrix[10] * f, matrix[11] * f,
		matrix[12] * f, matrix[13] * f, matrix[14] * f, matrix[15] * f);
}

Matrix4x4_PDE Matrix4x4_PDE::operator /(float f)
{

	if (f == 0) f = 1;
	f = 1 / f;

	return Matrix4x4_PDE(matrix[0] * f, matrix[1] * f, matrix[2] * f, matrix[3] * f,
		matrix[4] * f, matrix[5] * f, matrix[6] * f, matrix[7] * f,
		matrix[8] * f, matrix[9] * f, matrix[10] * f, matrix[11] * f,
		matrix[12] * f, matrix[13] * f, matrix[14] * f, matrix[15] * f);
}

bool Matrix4x4_PDE::operator ==(Matrix4x4_PDE m)
{

	for (int i = 0; i < 16; i++)
	{
		if (matrix[i] != m.matrix[i])
			return false;
	}

	return true;
}

void Matrix4x4_PDE::operator +=(Matrix4x4_PDE m)
{
	(*this) = (*this) + m;
}

void Matrix4x4_PDE::operator -=(Matrix4x4_PDE m)
{
	(*this) = (*this) - m;
}

void Matrix4x4_PDE::operator *=(Matrix4x4_PDE m)
{
	(*this) = (*this) * m;
}

void Matrix4x4_PDE::operator /=(Matrix4x4_PDE m)
{
	(*this) = (*this) / m;
}

bool Matrix4x4_PDE::operator !=(Matrix4x4_PDE m)
{
	return !((*this) == m);
}

void Matrix4x4_PDE::operator -=(float f)
{
	(*this) = (*this) - f;
}

void Matrix4x4_PDE::operator +=(float f)
{
	(*this) = (*this) + f;
}

void Matrix4x4_PDE::operator *=(float f)
{
	(*this) = (*this) * f;
}

void Matrix4x4_PDE::operator /=(float f)
{
	(*this) = (*this) / f;
}

void Matrix4x4_PDE::Clear()
{
	///���þ���Ϊ��λ����
	matrix[0] = 1.0f; matrix[1] = 0.0f; matrix[2] = 0.0f; matrix[3] = 0.0f;
	matrix[4] = 0.0f; matrix[5] = 1.0f; matrix[6] = 0.0f; matrix[7] = 0.0f;
	matrix[8] = 0.0f; matrix[9] = 0.0f; matrix[10] = 1.0f; matrix[11] = 0.0f;
	matrix[12] = 0.0f; matrix[13] = 0.0f; matrix[14] = 0.0f; matrix[15] = 1.0f;

}

void Matrix4x4_PDE::Zero()
{
	///���þ����Ԫ��Ϊ0
	matrix[0] = 0.0f; matrix[1] = 0.0f; matrix[2] = 0.0f; matrix[3] = 0.0f;
	matrix[4] = 0.0f; matrix[5] = 0.0f; matrix[6] = 0.0f; matrix[7] = 0.0f;
	matrix[8] = 0.0f; matrix[9] = 0.0f; matrix[10] = 0.0f; matrix[11] = 0.0f;
	matrix[12] = 0.0f; matrix[13] = 0.0f; matrix[14] = 0.0f; matrix[15] = 0.0f;
}

///ƽ�Ʊ任
void Matrix4x4_PDE::Translate(Vector3_PDE Translate)
{

	matrix[12] = Translate.x;
	matrix[13] = Translate.y;
	matrix[14] = Translate.z;
	matrix[15] = 1.0f;
}

void Matrix4x4_PDE::Translate(float x, float y, float z)
{

	matrix[12] = x;
	matrix[13] = y;
	matrix[14] = z;
	matrix[15] = 1.0f;
}

void Matrix4x4_PDE::inverseTranslate()
{
	matrix[12] = -matrix[12];
	matrix[13] = -matrix[13];
	matrix[14] = -matrix[14];
}

/// ��ת�任
void Matrix4x4_PDE::Rotate(double angle, float x, float y, float z)
{
	float sine = (float)sin(angle);
	float cosine = (float)cos(angle);

	float sinAngle = (float)sin(3.14 * angle / 180);
	float cosAngle = (float)cos(3.14 * angle / 180);
	float oneSubCos = 1.0f - cosAngle;

	matrix[0] = (x * x) * oneSubCos + cosAngle;
	matrix[4] = (x * y) * oneSubCos - (z * sinAngle);
	matrix[8] = (x * z) * oneSubCos + (y * sinAngle);

	matrix[1] = (y * x) * oneSubCos + (sinAngle * z);
	matrix[5] = (y * y) * oneSubCos + cosAngle;
	matrix[9] = (y * z) * oneSubCos - (x * sinAngle);

	matrix[2] = (z * x) * oneSubCos - (y * sinAngle);
	matrix[6] = (z * y) * oneSubCos + (x * sinAngle);
	matrix[10] = (z * z) * oneSubCos + cosAngle;
}

///������������
Vector3_PDE Matrix4x4_PDE::VectorMatrixMultiply(Vector3_PDE v)
{
	Vector3_PDE out;

	out.x = (v.x * matrix[0]) + (v.y * matrix[4]) + (v.z * matrix[8]) + matrix[12];
	out.y = (v.x * matrix[1]) + (v.y * matrix[5]) + (v.z * matrix[9]) + matrix[13];
	out.z = (v.x * matrix[2]) + (v.y * matrix[6]) + (v.z * matrix[10]) + matrix[14];

	return out;
}


Vector3_PDE Matrix4x4_PDE::VectorMatrixMultiply3x3(Vector3_PDE v)
{
	Vector3_PDE out;

	out.x = (v.x * matrix[0]) + (v.y * matrix[4]) + (v.z * matrix[8]);
	out.y = (v.x * matrix[1]) + (v.y * matrix[5]) + (v.z * matrix[9]);
	out.z = (v.x * matrix[2]) + (v.y * matrix[6]) + (v.z * matrix[10]);

	return out;
}

//Quaternion_PDE======================================================================

Quaternion_PDE::Quaternion_PDE()
{
	x = 0;
	y = 0;
	z = 0;
	w = 0;
}

Quaternion_PDE::Quaternion_PDE(float _x, float _y, float _z, float _w)
{

	x = _x;
	y = _y;
	z = _z;
	w = _w;
}

Quaternion_PDE::~Quaternion_PDE()
{

}

void Quaternion_PDE::ToMatrix(float *matrix)
{

	/*//Q_ASSERT(matrix != Q_NULLPTR);
	#ifndef MATRIX
	#define MATRIX( row, col ) matrix[row * 4 + col]
	#endif
	MATRIX(0, 0) = 2 * (x * x + w * w) - 1;
	MATRIX(0, 1) = 2 * (x * y + z * w);
	MATRIX(0, 2) = 2 * (x * z - y * w);
	MATRIX(0, 3) = 0.0f;
	MATRIX(1, 0) = 2 * (x * y - z * w);
	MATRIX(1, 1) = 2 * (y * y + w * w) - 1;
	MATRIX(1, 2) = 2 * (y * z + x * w);
	MATRIX(1, 3) = 0.0f;
	MATRIX(2, 0) = 2 * (x * z + y * w);
	MATRIX(2, 1) = 2 * (y * z - x * w);
	MATRIX(2, 2) = 2 * (z * z + w * w) - 1;
	MATRIX(2, 3) = 0.0f;
	MATRIX(3, 0) = 0.0f;
	MATRIX(3, 1) = 0.0f;
	MATRIX(3, 2) = 0.0f;
	MATRIX(3, 3) = 1.0f;
	#undef MATRIX

	*/

	float x2 = x * x;
	float y2 = y * y;
	float z2 = z * z;
	float xy = x * y;
	float xz = x * z;
	float yz = y * z;
	float wx = w * x;
	float wy = w * y;
	float wz = w * z;

	// This calculation would be a lot more complicated for non-unit length Quaternion_PDEs
	// Note: The constructor of Matrix4 expects the Matrix in column-major format like expected by
	//   OpenGL

	matrix[0] = 1.0f - 2.0f * (y2 + z2);
	matrix[1] = 2.0f * (xy - wz);
	matrix[2] = 2.0f * (xz + wy);
	matrix[3] = 0.0f;

	matrix[4] = 2.0f * (xy + wz);
	matrix[5] = 1.0f - 2.0f * (x2 + z2);
	matrix[6] = 2.0f * (yz - wx);
	matrix[7] = 0.0f;
	matrix[8] = 2.0f * (xz - wy);
	matrix[9] = 2.0f * (yz + wx);
	matrix[10] = 1.0f - 2.0f * (x2 + y2);
	matrix[11] = 0.0f;

	matrix[12] = 0.0f;
	matrix[13] = 0.0f;
	matrix[14] = 0.0f;
	matrix[15] = 1.0f;


}

Quaternion_PDE Quaternion_PDE::FromRotation(float _x, float _y, float _z, float angleInDegree)
{
	// �����ĵ�λ��
	float length = sqrt(_x * _x + _y * _y + _z * _z);
	//Q_ASSERT(!qFuzzyCompare(length, 0.0f));// ϣ��length��Ϊ0

	_x /= length;
	_y /= length;
	_z /= length;

	float alpha = angleInDegree / 180 * 3.1415926;// ��ת��������

	return Quaternion_PDE(
		sin(alpha / 2) * _x,
		sin(alpha / 2) * _y,
		sin(alpha / 2) * _z,
		cos(alpha / 2));
}

//Camera_PDE======================================================================

Camera_PDE* Camera_PDE::m_pCamera = NULL;

/** ���캯�� */
Camera_PDE::Camera_PDE()
{
	/** ��ʼ������ֵ */
	Vector3_PDE zero = Vector3_PDE(0.0, 0.0, 0.0);
	Vector3_PDE view = Vector3_PDE(0.0, 1.0, 0.5);
	Vector3_PDE up = Vector3_PDE(0.0, 0.0, 1.0);

	/** ��ʼ������� */
	m_Position = zero;
	m_View = view;
	m_UpVector = up;
	m_Speed = 0.00001f;

	m_pCamera = this;
}


Camera_PDE::~Camera_PDE()
{
}

/** �����������λ��,������������� */
void Camera_PDE::setCamera(float positionX, float positionY, float positionZ,
	float viewX, float viewY, float viewZ,
	float upVectorX, float upVectorY, float upVectorZ)
{
	/** �������� */
	Vector3_PDE Position = Vector3_PDE(positionX, positionY, positionZ);
	Vector3_PDE View = Vector3_PDE(viewX, viewY, viewZ);
	Vector3_PDE UpVector = Vector3_PDE(upVectorX, upVectorY, upVectorZ);

	/** ��������� */
	m_Position = Position;
	m_View = View;
	m_UpVector = UpVector;
}

/**  ��ת���������  */
void Camera_PDE::rotateView(float angle, float x, float y, float z)
{
	Vector3_PDE newView;

	/** ���㷽������ */
	Vector3_PDE view = m_View - m_Position;

	/** ���� sin ��cosֵ */
	float cosTheta = (float)cos(angle);
	float sinTheta = (float)sin(angle);

	/** ������ת������xֵ */
	newView.x = (cosTheta + (1 - cosTheta) * x * x)		* view.x;
	newView.x += ((1 - cosTheta) * x * y - z * sinTheta)	* view.y;
	newView.x += ((1 - cosTheta) * x * z + y * sinTheta)	* view.z;

	/** ������ת������yֵ */
	newView.y = ((1 - cosTheta) * x * y + z * sinTheta)	* view.x;
	newView.y += (cosTheta + (1 - cosTheta) * y * y)		* view.y;
	newView.y += ((1 - cosTheta) * y * z - x * sinTheta)	* view.z;

	/** ������ת������zֵ */
	newView.z = ((1 - cosTheta) * x * z - y * sinTheta)	* view.x;
	newView.z += ((1 - cosTheta) * y * z + x * sinTheta)	* view.y;
	newView.z += (cosTheta + (1 - cosTheta) * z * z)		* view.z;

	/** ����������ķ��� */
	m_View = m_Position + newView;
}

/** �������ת����� */
void Camera_PDE::setViewByMouse()
{
	POINT mousePos;									  /**< ���浱ǰ���λ�� */
	int middleX = GetSystemMetrics(SM_CXSCREEN) >> 1; /**< �õ���Ļ��ȵ�һ�� */
	int middleY = GetSystemMetrics(SM_CYSCREEN) >> 1; /**< �õ���Ļ�߶ȵ�һ�� */
	float angleY = 0.0f;							  /**< �����������ת�Ƕ� */
	float angleZ = 0.0f;		                      /**< �����������ת�Ƕ� */
	static float currentRotX = 0.0f;

	/** �õ���ǰ���λ�� */
	GetCursorPos(&mousePos);
	ShowCursor(false);

	/** ������û���ƶ�,���ø��� */
	if ((mousePos.x == middleX) && (mousePos.y == middleY))
		return;

	/** �������λ������Ļ���� */
	SetCursorPos(middleX, middleY);

	/**< �õ�����ƶ����� */
	angleY = (float)((middleX - mousePos.x)) / 1000.0f;
	angleZ = (float)((middleY - mousePos.y)) / 1000.0f;

	static float lastRotX = 0.0f;      /**< ���ڱ�����ת�Ƕ� */
	lastRotX = currentRotX;

	/** ���������������ת�Ƕ� */
	currentRotX += angleZ;

	/** ���������ת���ȴ���1.0,���ǽ�ȡ��1.0����ת */
	if (currentRotX > 1.0f)
	{
		currentRotX = 1.0f;

		/** ���ݱ���ĽǶ���ת���� */
		if (lastRotX != 1.0f)
		{
			/** ͨ������ҵ�����ת����ֱ������ */
			Vector3_PDE vAxis = m_View - m_Position;
			vAxis = vAxis.crossProduct(m_UpVector);
			vAxis = vAxis.normalize();

			///��ת
			rotateView(1.0f - lastRotX, vAxis.x, vAxis.y, vAxis.z);
		}
	}
	/** �����ת����С��-1.0,��Ҳ��ȡ��-1.0����ת */
	else if (currentRotX < -1.0f)
	{
		currentRotX = -1.0f;

		if (lastRotX != -1.0f)
		{

			/** ͨ������ҵ�����ת����ֱ������ */
			Vector3_PDE vAxis = m_View - m_Position;
			vAxis = vAxis.crossProduct(m_UpVector);
			vAxis = vAxis.normalize();

			///��ת
			rotateView(-1.0f - lastRotX, vAxis.x, vAxis.y, vAxis.z);
		}
	}
	/** �������תangleZ�� */
	else
	{
		/** �ҵ�����ת����ֱ���� */
		Vector3_PDE vAxis = m_View - m_Position;
		vAxis = vAxis.crossProduct(m_UpVector);
		vAxis = vAxis.normalize();

		///��ת
		rotateView(angleZ, vAxis.x, vAxis.y, vAxis.z);
	}

	/** ����������ת����� */
	rotateView(angleY, 0, 1, 0);
}


/** �����ƶ������ */
void Camera_PDE::yawCamera(float speed)
{
	Vector3_PDE yaw;
	Vector3_PDE oldPos, oldView;
	Vector3_PDE cross = m_View - m_Position;
	oldPos = m_Position;
	oldView = m_View;
	cross = cross.crossProduct(m_UpVector);

	///��һ������
	yaw = cross.normalize();

	m_Position.x += yaw.x * speed;
	m_Position.z += yaw.z * speed;

	m_View.x += yaw.x * speed;
	m_View.z += yaw.z * speed;

	/** ���б߽�����޶�
	if(m_View.x > MAP_WIDTH - 20 || m_View.x < 2*CELL_WIDTH)
	{
	m_Position.x = oldPos.x ;
	m_View.x = oldView.x;
	}

	if(m_View.z > MAP_WIDTH - 20 || m_View.z < 2*CELL_WIDTH)
	{
	m_Position.z = oldPos.z ;
	m_View.z = oldView.z;
	}
	*/


}

/** ǰ���ƶ������ */
void Camera_PDE::moveCamera(float speed)
{
	/** ���㷽������ */
	Vector3_PDE vector = m_View - m_Position;
	vector = vector.normalize();         /**< ��λ�� */
	Vector3_PDE oldPos, oldView;
	oldPos = m_Position;
	oldView = m_View;

	/** ��������� */
	m_Position.x += vector.x * speed;    /**< �����ٶȸ���λ�� */
	m_Position.z += vector.z * speed;
	m_Position.y += vector.y * speed;


	m_View.x += vector.x * speed;		 /**< �����ٶȸ��·��� */
	m_View.y += vector.y * speed;
	m_View.z += vector.z * speed;

	/** ���б߽�����޶�
	if(m_View.x > MAP_WIDTH - 20 || m_View.x <  2*CELL_WIDTH)
	{
	m_Position.x = oldPos.x ;
	m_View.x = oldView.x;
	}

	if(m_View.z > MAP_WIDTH - 20 || m_View.z < 2*CELL_WIDTH)
	{
	m_Position.z = oldPos.z ;
	m_View.z = oldView.z;
	}*/


}

/** �����ӵ� */
void Camera_PDE::setLook()
{

	/** �����ӿ� */
	gluLookAt(m_Position.x, m_Position.y, m_Position.z,
		m_View.x, m_View.y, m_View.z,
		m_UpVector.x, m_UpVector.y, m_UpVector.z);
}


//ModelInput_PDE======================================================================

ModelInput_PDE::ModelInput_PDE()
{
	textureOrNormalEBO = true;

}

ModelInput_PDE::~ModelInput_PDE()
{

}

modelRoot_pde *ModelInput_PDE::GetModelRoot()
{
	return &modelRoot;
}

vector<EBO_pde> ModelInput_PDE::GetEBOVector()
{
	return vertexEBO;
}
//������Ϣ�ֱ�1
void ModelInput_PDE::ImportChoose(const TCHAR *channge, model_pde *models, FILE *fp)
{

	if (!wcscmp(channge, _T("modelRoot_pde")))
	{
	}
	else if (!wcscmp(channge, _T("vertex_pde")))
	{
		ImportVertex(models, fp);
	}
	else if (!wcscmp(channge, _T("model_pde")))
	{
	}
	else if (!wcscmp(channge, _T("modifier_pde")))
	{
		ImportModifier(models, fp);
	}
	else if (!wcscmp(channge, _T("mapChannel_pde")))
	{
		ImportMapChannel(models, fp);
	}
	else if (!wcscmp(channge, _T("normal_pde")))
	{
		ImportNormals(models, fp);
	}
	else if (!wcscmp(channge, _T("face_pde")))
	{
		ImportMesh(models, fp);
	}
	else if (!wcscmp(channge, _T("coord_pde")))
	{
		ImportCoord(models, fp);
	}
	else if (!wcscmp(channge, _T("model_imformation")))
	{
		ImportModelName(models, fp);
	}
	else
	{
		MessageBox(NULL, L"error", L"", MB_OK);
		exit(0);
	}
}

//������Ϣ�ֱ�2
void ModelInput_PDE::ImportChoose(const TCHAR *channge, FILE *fp)
{

	if (!wcscmp(channge, _T("Begin_ModelRoot")))
	{
		ImportModelRoot(fp);
	}

	else if (!wcscmp(channge, _T("Begin_Model")))
	{
		ImportModel(&modelRoot, fp);
	}

	else if (!wcscmp(channge, _T("Begin_Material")))
	{
		ImportMaterial(fp);
	}
}

//����ģ����Ϣ
bool ModelInput_PDE::ImportFile(const TCHAR *filename)
{
	fp = _wfopen(filename, _T("r"));
	if (fp == NULL)
	{
		MessageBox(NULL, L"��ȡʧ��\n", L"error", MB_OK);
		return false;
	}

	fwscanf(fp, _T("%s\n"), change);
	if (wcscmp(change, _T("BEGIN_PDE")))
	{
		MessageBox(NULL, L"����PDE�ļ�", L"error", MB_OK);
		fclose(fp);
		return false;
	}

	while (1)
	{
		fwscanf(fp, _T("%s\n"), change);
		if (!wcscmp(change, _T("END_PDE")))
		{
			break;

		}
		else if ((!wcscmp(change, _T("Begin_ModelRoot"))) || (!wcscmp(change, _T("Begin_Model"))) || (!wcscmp(change, _T("Begin_Material"))))
		{
			ImportChoose(change, fp);
		}
		else
		{
			MessageBox(NULL, L"PDE�ļ���", L"error", MB_OK);
			return false;
		}
	}


	GenTexxtureID();
	GenerationAllMeshNormal();
	fclose(fp);


	return true;
}

//�����ܵ�����
void ModelInput_PDE::ImportModelRoot(FILE *fp)
{
	PurpleDreamElf_model mod;
	modelRoot = mod.modelRoot;
	fwscanf(fp, _T("\t%s\n"), buffer);
	fwscanf(fp, _T("\t\tmodelNum:%d,materialNum:%d\n"), &modelRoot.modelNum, &modelRoot.materialNum);
	fwscanf(fp, _T("%s\n"), change);
	if (wcscmp(change, _T("End_ModelRoot")))
	{
		MessageBox(NULL, L"PDE�ļ���", L"error", MB_OK);
	}
}

//���뵥��ģ����Ϣ����תվ��
void ModelInput_PDE::ImportModel(modelRoot_pde *modelRoot, FILE *fp)
{

	PurpleDreamElf_model mod;
	model_pde model = mod.model;
	ImportModelInformation(&model, fp);
	modelRoot->modelList.push_back(model);

}

//���뵥��ģ��ͷ��Ϣ
void ModelInput_PDE::ImportModelName(model_pde *models, FILE *fp)
{

	fwscanf(fp, _T("\t\tmodelName:%s\n"), models->modelName);
	fwscanf(fp, _T("\t\tmodelType:%s\n"), models->modelType);
	fwscanf(fp, _T("\t\thaveMaterialIndex:%d\n"), &models->haveMaterialIndex);
	fwscanf(fp, _T("\t\tmaterialIndex:%d\n"), &models->materialIndex);
	fwscanf(fp, _T("\t\tparentId:%d,nodeId:%d,coordNum:%d,vertexNum:%d,faceNum:%d,normalNum:%d,mapChannelNum:%d,modifierNum:%d,groupChildNum:%d\n"),
		&models->parentId, &models->nodeId, &models->coordNum, &models->vertexNum, &models->faceNum, &models->normalNum, &models->mapChannelNum, &models->modifierNum, &models->groupChildNum);
	fwscanf(fp, _T("\t\tgroup:%d\n"), &models->isGroup);

	fwscanf(fp, _T("\t\t%s\n"), buffer);
	fwscanf(fp, _T("\t\t%d,%d,%d\n"), &models->R, &models->G, &models->B);
	fwscanf(fp, _T("\t\t%s\n"), buffer);
	fwscanf(fp, _T("\t\t%s\n"), buffer);
	fwscanf(fp, _T("\t\t%f,%f,%f\n"), &models->translation[0], &models->translation[1], &models->translation[2]);
	fwscanf(fp, _T("\t\t%s\n"), buffer);
	fwscanf(fp, _T("\t\t%f,%f,%f,%f\n"), &models->rotation[0], &models->rotation[1], &models->rotation[2], &models->rotation[3]);
	fwscanf(fp, _T("\t\t%s\n"), buffer);
	fwscanf(fp, _T("\t\t%f,%f,%f,%f,%f,%f,%f\n"), &models->scale[0], &models->scale[1], &models->scale[2], &models->scale[3], &models->scale[4], &models->scale[5], &models->scale[6]);
	fwscanf(fp, _T("\t\tgroup:%d\n"), &models->isGroup);
}

//���뵥��ģ��ȫ����Ϣ
void ModelInput_PDE::ImportModelInformation(model_pde *models, FILE *fp)
{


	while (1)
	{
		fwscanf(fp, _T("%s\n"), change);
		if (!wcscmp(change, _T("End_Model")))
			break;
		if (wcscmp(change, _T("Begin")))
			return;

		fwscanf(fp, _T("\t%s\n"), buffer);
		ImportChoose(buffer, models, fp);

		fwscanf(fp, _T("%s\n"), change);

		if (wcscmp(change, _T("End")))
			return;

	}


}

//����ͨ��
void ModelInput_PDE::ImportMapChannel(model_pde *models, FILE *fp)
{
	TCHAR type[20];
	if (!wcscmp(buffer, _T("mapChannel_pde")))
	{
		PurpleDreamElf_model mod;
		fwscanf(fp, _T("\t\tmapChannelNum:%d\n"), &models->mapChannelNum);
		for (int mapChannel_i = 0; mapChannel_i < models->mapChannelNum; mapChannel_i++)
		{
			mapChannel_pde mapChannel = mod.mapChannel;
			fwscanf(fp, _T("\t\ttype:%s\n"), type);
			fwscanf(fp, _T("\t\tid:%d,mapVertNum:%d,mapfaceNum:%d\n"), &mapChannel.id, &mapChannel.mapVertNum, &mapChannel.mapfaceNum);
			//mapChannel.type = (TCHAR *)malloc(lstrlen(type)*sizeof(TCHAR));
			wcscpy(mapChannel.type, type);

			fwscanf(fp, _T("\t\t%s\n"), buffer);
			for (int mapVert_i = 0; mapVert_i < mapChannel.mapVertNum; mapVert_i++)
			{
				mapVert_pde mapVert = mod.mapVert;
				fwscanf(fp, _T("\t\tx,%f,y:%f,z:%f\n"), &mapVert.x, &mapVert.y, &mapVert.z);
				mapChannel.mapVert.push_back(mapVert);
			}
			fwscanf(fp, _T("\t\t%s\n"), buffer);
			for (int mapFace_i = 0; mapFace_i < mapChannel.mapfaceNum; mapFace_i++)
			{
				mapFace_pde mapFace = mod.mapFace;
				fwscanf(fp, _T("\t\tx:%f,y:%f,z:%f\n"), &mapFace.x, &mapFace.y, &mapFace.z);
				mapChannel.mapFace.push_back(mapFace);
			}
			models->mapChannel.push_back(mapChannel);
		}


	}
}

//���뷨��
void ModelInput_PDE::ImportNormals(model_pde *models, FILE *fp)
{

	if (!wcscmp(buffer, _T("normal_pde")))
	{
		PurpleDreamElf_model mod;
		fwscanf(fp, _T("\t\tnormalNum:%d\n"), &models->normalNum);
		models->normal.reserve(models->normalNum);
		for (int normal_i = 0; normal_i < models->normalNum; normal_i++)
		{
			normal_pde normal = mod.normal;
			fwscanf(fp, _T("\t\tx:%f,y:%f,z:%f:\n"), &normal.x, &normal.y, &normal.z);
			models->normal.push_back(normal);
		}

	}
}

//���붥��
void ModelInput_PDE::ImportVertex(model_pde *models, FILE *fp)
{
	if (!wcscmp(buffer, _T("vertex_pde")))
	{
		PurpleDreamElf_model mod;
		fwscanf(fp, _T("\t\tvertexNum:%d\n"), &models->vertexNum);
		models->vertex.reserve(models->vertexNum);
		for (int vertex_i = 0; vertex_i < models->vertexNum; vertex_i++)
		{
			vertex_pde vertex = mod.vertex;
			fwscanf(fp, _T("\t\tx:%f,y:%f,z:%f\n"), &vertex.x, &vertex.y, &vertex.z);
			models->vertex.push_back(vertex);
		}
	}
}

//������������
void ModelInput_PDE::ImportCoord(model_pde *models, FILE *fp)
{
	if (!wcscmp(buffer, _T("coord_pde")))
	{
		PurpleDreamElf_model mod;
		fwscanf(fp, _T("\t\tcoordNum:%d\n"), &models->coordNum);
		models->coord.reserve(models->coordNum);
		for (int coord_i = 0; coord_i < models->coordNum; coord_i++)
		{
			coord_pde coords;
			fwscanf(fp, _T("\t\tcoord_x:%f,coord_y:%f\n"), &coords.coord_x, &coords.coord_y);
			models->coord.push_back(coords);
		}
	}
}

//���������Ϣ
void ModelInput_PDE::ImportMesh(model_pde *models, FILE *fp)
{
	if (!wcscmp(buffer, _T("face_pde")))
	{
		PurpleDreamElf_model mod;
		fwscanf(fp, _T("\t\tfaceNum:%d\n"), &models->faceNum);
		models->mesh.reserve(models->faceNum);
		for (int mesh_i = 0; mesh_i < models->faceNum; mesh_i++)
		{
			face_pde face = mod.face;
			fwscanf(fp, _T("\t\tmatID:%d\n"), &face.matId);
			fwscanf(fp, _T("\t\tv[0]:%f,v[1]:%f,v[2]:%f,n[0]:%f,n[1]:%f,n[2]:%f,coord[0]:%f,coord[1]:%f,coord[2]:%f,edges[0]:%f,edges[1]:%f,edges[2]:%f\n"),
				&face.v[0], &face.v[1], &face.v[2], &face.n[0], &face.n[1], &face.n[2], &face.coord[0], &face.coord[1], &face.coord[2], &face.edges[0], &face.edges[1], &face.edges[2]);
			models->mesh.push_back(face);
		}
	}
}

//����ƹ�
void ModelInput_PDE::ImportLight(model_pde *models, FILE *fp)
{
	TCHAR lightType[20];
	//fwscanf(fp, _T("\t\t%s\n"), buffer);
	if (!wcscmp(buffer, _T("light_pde")))
	{
		PurpleDreamElf_model mod;
		models->light = mod.model.light;
		fwscanf(fp, _T("\t\tlightType:%s\n"), lightType);
		fwscanf(fp, _T("\t\ttargetId:%d,R:%f,G:%f,B:%f,multiplier:%f,aspectRatio:%f,end:%f,start:%f,fallOff:%f\n"),
			&models->light[0].targetId, &models->light[0].R, &models->light[0].G, &models->light[0].B,
			&models->light[0].multiplier, &models->light[0].aspectRatio, &models->light[0].end, &models->light[0].start,
			&models->light[0].fallOff);
		//models->light[0].type = (TCHAR*)malloc(lstrlen(lightType)*sizeof(TCHAR));
		wcscpy(models->light[0].type, lightType);
	}
}

//�����޸���
void ModelInput_PDE::ImportModifier(model_pde *models, FILE *fp)
{


	if (!wcscmp(buffer, _T("modifier_pde")))
	{
		PurpleDreamElf_model mod;
		fwscanf(fp, _T("\t\tmodifierNum:%d\n"), &models->modifierNum);
		for (int modeifier_i = 0; modeifier_i < models->modifierNum; modeifier_i++)
		{
			modifier_pde modifier = mod.modifier;
			fwscanf(fp, _T("\t\tisSkin:%d\n"), &modifier.isSkin);
			if (modifier.isSkin)
			{
				modifier.isSkin = true;
				fwscanf(fp, _T("\t\tskinType:%s\n"), modifier.skinType);
				fwscanf(fp, _T("\t\tskinVertnum:%d\n"), &modifier.skinVertnum);

				for (int skinVert_i = 0; skinVert_i < modifier.skinVertnum; skinVert_i++)
				{

					skinVert_pde skinVert = mod.skinVert;
					fwscanf(fp, _T("\t\tskinVertType:%s\n"), skinVert.skinVertType);
					fwscanf(fp, _T("\t\tvertexId:%d,Num:%d\n"), &skinVert.vertexId, &skinVert.num);


					for (int i = 0; i < skinVert.num; i++)
					{
						boneAndweight_pde boneAndweight = mod.boneAndweight;
						fwscanf(fp, _T("\t\tboneId:%d,weight:%f\n"), &boneAndweight.boneId, &boneAndweight.weight);
						skinVert.bone.push_back(boneAndweight);
					}
					modifier.skinVert.push_back(skinVert);
				}
			}

			models->modifier.push_back(modifier);
		}
	}
}

//�������
void ModelInput_PDE::ImportMaterial(FILE *fp)
{
	PurpleDreamElf_model mod;
	modelRoot.materialList.reserve(modelRoot.materialNum);
	for (int i = 0; i < modelRoot.materialNum; i++)
	{
		material_pde materials = mod.material;
		ImportMaterialChild(&materials, fp);
		modelRoot.materialList.push_back(materials);
	}

	fwscanf(fp, _T("%s\n"), change);
	if (wcscmp(change, _T("End_Material")))
	{
		MessageBox(NULL, L"PDE�ļ���", L"error", MB_OK);

	}

}

//�����Ӳ���
void ModelInput_PDE::ImportMaterialChild(material_pde *material, FILE *fp)
{
	int isMultiType = 0;
	fwscanf(fp, _T("\t\tisMultiType:%d\n"), &material->IsMultiType);
	if (material->IsMultiType)
	{

		fwscanf(fp, _T("\t\tmaterialName:%s\n"), material->materialName);
		fwscanf(fp, _T("\t\tclassName:%s\n"), material->className);
		fwscanf(fp, _T("\t\tmaterialIndex:%d,subMaterialNum:%d\n"), &material->materialIndex, &material->subMaterialNum);
		material->subMaterial.reserve(material->subMaterialNum);
		for (int material_child = 0; material_child < material->subMaterialNum; material_child++)
		{
			PurpleDreamElf_model mod;
			material_pde materialChild = mod.material;
			ImportMaterialChild(&materialChild, fp);
			material->subMaterial.push_back(materialChild);
		}

	}
	else
	{
		fwscanf(fp, _T("\t\tmaterialName:%s\n"), material->materialName);
		fwscanf(fp, _T("\t\tclassName:%s\n"), material->className);
		fwscanf(fp, _T("\t\tmaterialIndex:%d,materialId:%d,textureNum:%d\n"), &material->materialIndex, &material->materialId, &material->textureNum);
		fwscanf(fp, _T("\t\tdiffuse[0]:%f,diffuse[1]:%f,diffuse[2]:%f\n"), &material->diffuse[0], &material->diffuse[1], &material->diffuse[2]);
		fwscanf(fp, _T("\t\tambient[0]:%f,ambient[1]:%f,ambient[2]:%f\n"), &material->ambient[0], &material->ambient[1], &material->ambient[2]);
		fwscanf(fp, _T("\t\tspecular[0]:%f,specular[1]:%f,specular[2]:%f\n"), &material->specular[0], &material->specular[1], &material->specular[2]);
		fwscanf(fp, _T("\t\tspecularLever:%f,glossiness:%f,opacity:%f\n"), &material->specularLevel, &material->glossiness, &material->opacity);
		//texture_pde======================================================================
		fwscanf(fp, _T("\t%s\n"), buffer);
		fwscanf(fp, _T("\t\ttextureNum:%d\n"), &material->textureNum);
		material->texture.reserve(material->textureNum);
		for (int texture_i = 0; texture_i < material->textureNum; texture_i++)
		{
			PurpleDreamElf_model mod;
			texture_pde texture = mod.texture;
			fwscanf(fp, _T("\t\ttextureName:%s\n"), texture.name);
			fwscanf(fp, _T("\t\ttextureIndex:%d\n"), &texture.textureIndex);
			fwscanf(fp, _T("\t\tisSupport:%d\n"), &texture.isSupport);
			if (texture.isSupport)
			{
				fwscanf(fp, _T("\t\tfileName:%s\n"), texture.fileName);
				fwscanf(fp, _T("\t\tClipU:%f,ClipV:%f,ClipW:%f,ClipH:%f\n"), &texture.ClipU, &texture.ClipV, &texture.ClipW, &texture.ClipH);
			}
			material->texture.push_back(texture);
		}
	}
}


material_pde * ModelInput_PDE::GetMaterial(modelRoot_pde modelRoots, const TCHAR *materialName)
{
	for (int i = 0; i < modelRoots.materialNum; i++)
	{
		if (!wcscmp(modelRoots.materialList[i].materialName, materialName))
		{
			return &modelRoots.materialList[i];
		}
	}
}

modifier_pde * ModelInput_PDE::GetModifier(model_pde model, const TCHAR *modelName)
{
	for (int i = 0; i < model.modifierNum; i++)
	{
		if (!wcscmp(model.modifier[i].modName, modelName))
		{
			return &model.modifier[i];
		}
	}
}

//Ϊ�������id
void ModelInput_PDE::GenTexxtureID()
{
	for (int i = 0; i < modelRoot.materialNum; i++)
	{
		material_pde *material = &modelRoot.materialList[i];
		GenTextureIDChild(material);
	}
}

//Ϊ�������id��
void ModelInput_PDE::GenTextureIDChild(material_pde *material)
{
	if (!material->IsMultiType)
	{
		if (material->textureNum)
		{
			for (int i = 0; i < material->textureNum; i++)
			{
				texture_pde *texture = &material->texture[i];
				if (texture->fileName == NULL)
					return;
				char filename[255];
				PurpleDreamElf::TcharTochar(texture->fileName, filename);
				texture->textureIndex = TexGen.CreateTextures(filename, "yuyu");
				//texture->textureIndex=TexGen.CreateBitTextures(texture->fileName, "yuyu");

			}
		}
	}
	else
	{
		for (int i = 0; i < material->subMaterialNum; i++)
		{
			GenTextureIDChild(&material->subMaterial[i]);
		}

	}
}

void ModelInput_PDE::GenerationMeshNormal(model_pde *model)
{
	Vector3_PDE vector[5];
	for (int i = 0;i < model->faceNum;i++)
	{
		vector[0].x = model->vertex[model->mesh[i].v[0]].x;
		vector[0].y = model->vertex[model->mesh[i].v[0]].y;
		vector[0].z = model->vertex[model->mesh[i].v[0]].z;

		vector[1].x = model->vertex[model->mesh[i].v[1]].x;
		vector[1].y = model->vertex[model->mesh[i].v[1]].y;
		vector[1].z = model->vertex[model->mesh[i].v[1]].z;

		vector[2].x = model->vertex[model->mesh[i].v[2]].x;
		vector[2].y = model->vertex[model->mesh[i].v[2]].y;
		vector[2].z = model->vertex[model->mesh[i].v[2]].z;

		vector[3] = vector[0] - vector[2];
		vector[4] = vector[2] - vector[1];

		vector[3] = vector[3].crossProduct(vector[4]);

		vector[3] = vector[3].normalize();
		normal_pde normal;

		normal.x = vector[3].x;
		normal.y = vector[3].y;
		normal.z = vector[3].z;
		model->meshnormal.push_back(normal);
		model->mesh[i].meshNormal = i;
	}
}

void ModelInput_PDE::IndexVertexToCoord(model_pde *model)
{
	vector<vertex_pde> vertes = model->vertex;
	vector<vertex_pde>().swap(model->vertexReset);
	for (int i = 0; i < model->coordNum; i++)
	{
		vertex_pde v;
		v.x = 0; v.y = 0; v.z = 0;

		model->vertexReset.push_back(v);
	}

	for (int i = 0; i < model->faceNum; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			model->vertexReset[model->mesh[i].coord[j]].x = vertes[model->mesh[i].v[j]].x;
			model->vertexReset[model->mesh[i].coord[j]].y = vertes[model->mesh[i].v[j]].y;
			model->vertexReset[model->mesh[i].coord[j]].z = vertes[model->mesh[i].v[j]].z;
		}
	}
}

void ModelInput_PDE::IndexVertexAndCoordAndNormal(model_pde *model)
{

	vector<vertex_pde> vertes = model->vertex;
	vector<coord_pde> coord = model->coord;
	vector<normal_pde> normal = model->normal;
	if (model->coordNum < model->normalNum)
	{
		for (int i = 0; i < model->normalNum; i++)
		{
			vertex_pde v;
			coord_pde c;
			v.x = 0; v.y = 0; v.z = 0;
			c.coord_x = 0; c.coord_y = 0;
			model->vertexReset.push_back(v);
			model->coordReset.push_back(c);
		}

		for (int i = 0; i < model->faceNum; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				model->vertexReset[model->mesh[i].n[j]].x = vertes[model->mesh[i].v[j]].x;
				model->vertexReset[model->mesh[i].n[j]].y = vertes[model->mesh[i].v[j]].y;
				model->vertexReset[model->mesh[i].n[j]].z = vertes[model->mesh[i].v[j]].z;

				model->coordReset[model->mesh[i].n[j]].coord_x = coord[model->mesh[i].coord[j]].coord_x;
				model->coordReset[model->mesh[i].n[j]].coord_y = coord[model->mesh[i].coord[j]].coord_y;

			}

		}
	}
	else
	{
		for (int i = 0; i < model->coordNum; i++)
		{
			vertex_pde v;
			normal_pde n;
			v.x = 0; v.y = 0; v.z = 0;
			n.x = 0; n.y = 0; n.z = 0;
			model->vertexReset.push_back(v);
			model->normalReset.push_back(n);
		}

		for (int i = 0; i < model->faceNum; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				model->vertexReset[model->mesh[i].coord[j]].x = vertes[model->mesh[i].v[j]].x;
				model->vertexReset[model->mesh[i].coord[j]].y = vertes[model->mesh[i].v[j]].y;
				model->vertexReset[model->mesh[i].coord[j]].z = vertes[model->mesh[i].v[j]].z;

				model->normalReset[model->mesh[i].coord[j]].x = normal[model->mesh[i].n[j]].x;
				model->normalReset[model->mesh[i].coord[j]].y = normal[model->mesh[i].n[j]].y;
				model->normalReset[model->mesh[i].coord[j]].z = normal[model->mesh[i].n[j]].z;

			}

		}
	}

}

void ModelInput_PDE::GenerationAllMeshNormal()
{
	for (int i = 0;i < modelRoot.modelNum;i++)
	{
		model_pde *model = &modelRoot.modelList[i];
		GenerationMeshNormal(model);
	}
}


void ModelInput_PDE::ModelDraw(TCHAR *name)
{
	for (int a = 0; a < modelRoot.modelNum; a++)
	{
		model_pde model = modelRoot.modelList[a];

		if (wcscmp(model.modelName, name))
			continue;
		vector<vertex_pde> vertex = model.vertex;
		vector<normal_pde> normal = model.normal;
		vector<normal_pde> meshNormal = model.meshnormal;
		vector<coord_pde> coord = model.coord;
		vector<texture_pde> texture;
		//glPushMatrix();
		//glMultMatrixf(model.ma.matrix);
		for (int i = 0; i < model.faceNum; i++)
		{
			face_pde face = model.mesh[i];
			material_pde materials;
			if (model.haveMaterialIndex)
			{
				materials = modelRoot.materialList[model.materialIndex];
				if (materials.IsMultiType)
				{
					materials = materials.subMaterial[face.matId];
				}

				if (materials.textureNum)
				{
					TCHAR textureBuf[255] = { 0 };
					for (int t = 0; t < materials.textureNum; t++)
					{
						//wsprintf(textureBuf, L"GL_TEXTURE%d_ARB", t);

						glBindTexture(GL_TEXTURE_2D, materials.texture[t].textureIndex);

					}

				}
				else
				{
					glDisable(GL_TEXTURE_2D);
				}

				//	glMaterialfv(GL_FRONT, GL_AMBIENT, materials.ambient);
				//	glMaterialfv(GL_FRONT, GL_DIFFUSE, materials.diffuse);
				//	glMaterialfv(GL_FRONT, GL_SPECULAR, materials.specular);
				//glMaterialfv(GL_FRONT, GL_SHININESS, materials.specularLevel);
				//glMaterialfv(GL_FRONT, GL_EMISSION, material);


			}

			//glColor3f(1.0f, 1.0f, 1.0f);
			//glNormal3f(meshNormal[face.meshNormal].x, meshNormal[face.meshNormal].y, meshNormal[face.meshNormal].z);
			glBegin(GL_TRIANGLES);

			for (int j = 0; j < 3; j++)
			{

				glNormal3f(normal[face.n[j]].x, normal[face.n[j]].y, normal[face.n[j]].z);
				glTexCoord2f(coord[face.coord[j]].coord_x, coord[face.coord[j]].coord_y);
				glVertex3f(vertex[face.v[j]].x, vertex[face.v[j]].y, vertex[face.v[j]].z);


			}
			glEnd();

			//if(i==1)
			//break;
		}
		//glPopMatrix();
	}
}

void ModelInput_PDE::all()
{
	for (int a = 0; a < modelRoot.modelNum; a++)
	{
		model_pde model = modelRoot.modelList[a];
		vector<vertex_pde> vertex = model.vertex;
		vector<normal_pde> normal = model.normal;
		vector<normal_pde> meshNormal = model.meshnormal;
		vector<coord_pde> coord = model.coord;
		vector<texture_pde> texture;
		//glPushMatrix();
		//glMultMatrixf(model.ma.matrix);
		for (int i = 0; i < model.faceNum; i++)
		{
			face_pde face = model.mesh[i];
			material_pde materials;
			if (model.haveMaterialIndex)
			{
				materials = modelRoot.materialList[model.materialIndex];
				if (materials.IsMultiType)
				{
					materials = materials.subMaterial[face.matId];
				}

				if (materials.textureNum)
				{
					TCHAR textureBuf[255] = { 0 };
					for (int t = 0; t < materials.textureNum; t++)
					{
						//wsprintf(textureBuf, L"GL_TEXTURE%d_ARB", t);
						glEnable(GL_TEXTURE_2D);
						glBindTexture(GL_TEXTURE_2D, materials.texture[t].textureIndex);

					}

				}
				else
				{
					glDisable(GL_TEXTURE_2D);
				}

				//	glMaterialfv(GL_FRONT, GL_AMBIENT, materials.ambient);
				//	glMaterialfv(GL_FRONT, GL_DIFFUSE, materials.diffuse);
				//	glMaterialfv(GL_FRONT, GL_SPECULAR, materials.specular);
				//glMaterialfv(GL_FRONT, GL_SHININESS, materials.specularLevel);
				//glMaterialfv(GL_FRONT, GL_EMISSION, material);


			}

			//glColor3f(1.0f, 1.0f, 1.0f);
			//glNormal3f(meshNormal[face.meshNormal].x, meshNormal[face.meshNormal].y, meshNormal[face.meshNormal].z);

			glBegin(GL_TRIANGLES);

			for (int j = 0; j < 3; j++)
			{

				glNormal3f(normal[face.n[j]].x, normal[face.n[j]].y, normal[face.n[j]].z);
				glTexCoord2f(coord[face.coord[j]].coord_x, coord[face.coord[j]].coord_y);
				glVertex3f(vertex[face.v[j]].x, vertex[face.v[j]].y, vertex[face.v[j]].z);


			}
			glEnd();

			//if(i==1)
			//break;
		}
		//glPopMatrix();
	}
}

void ModelInput_PDE::ModelDrawUseVertex(model_pde model, GLenum type)
{


	vector<vertex_pde> vertex = model.vertex;
	vector<normal_pde> normal = model.normal;
	vector<coord_pde> coord = model.coord;
	vector<modifier_pde>modifier = model.modifier;
	vector<texture_pde> texture;
	glPushMatrix();
	for (int i = 0; i < model.faceNum; i++)
	{
		face_pde face = model.mesh[i];
		material_pde materials;
		float x = 0, y = 0, z = 0;
		if (model.haveMaterialIndex)
		{
			materials = modelRoot.materialList[model.materialIndex];
			if (materials.IsMultiType)
			{
				materials = materials.subMaterial[face.matId];
			}

			if (materials.textureNum)
			{
				TCHAR textureBuf[255] = { 0 };
				for (int t = 0; t < materials.textureNum; t++)
				{
					//wsprintf(textureBuf, L"GL_TEXTURE%d_ARB", t);
					glEnable(GL_TEXTURE_2D);
					glBindTexture(GL_TEXTURE_2D, materials.texture[t].textureIndex);
				}

			}
			else
			{
				glDisable(GL_TEXTURE_2D);
			}

			glMaterialfv(GL_FRONT, GL_AMBIENT, materials.ambient);
			glMaterialfv(GL_FRONT, GL_DIFFUSE, materials.diffuse);
			glMaterialfv(GL_FRONT, GL_SPECULAR, materials.specular);
			//glMaterialfv(GL_FRONT, GL_SHININESS, materials.specularLevel);
			//glMaterialfv(GL_FRONT, GL_EMISSION, material);


		}


		glBegin(type);
		for (int j = 0; j < 3; j++)
		{

			glNormal3f(normal[face.n[j]].x, normal[face.n[j]].y, normal[face.n[j]].z);


			//glTexCoord2f(coord[face.coord[j]].coord_x, coord[face.coord[j]].coord_y);
			x = vertex[face.v[j]].x;
			y = vertex[face.v[j]].y;
			z = vertex[face.v[j]].z;

			for (int i1 = 0; i1 < model.modifierNum; i1++)
			{
				vector<skinVert_pde> skin = modifier[i1].skinVert;
				for (int i2 = 0; i2 < modifier[i1].skinVertnum; i2++)
				{
					if (face.v[j] == skin[i2].vertexId)
					{

						Vector3_PDE ve(0, 0, 0, 0);
						skinVert_pde *skinVert = &skin[i2];
						Vector3_PDE ve1(vertex[skinVert->vertexId].x, vertex[skinVert->vertexId].y, vertex[skinVert->vertexId].z);
						if (wcscmp(skinVert->skinVertType, _T("Blended")))
							continue;

						for (int x = 0; x < skinVert->num; x++)
						{
							boneAndweight_pde *bone = &skinVert->bone[x];
							ve += ve;
							ve += (modelRoot.modelList[bone->boneId].relative.VectorMatrixMultiply(ve1)*bone->weight);
						}
						x = ve.x;
						y = ve.y;
						z = ve.z;

					}
				}
			}
			glVertex3f(x, y, z);


		}
		glEnd();

		//if(i==1)
		//break;
	}
	glPopMatrix();
}

void ModelInput_PDE::ModelSkinSet(model_pde &model, model_pde &bone)
{

	if (!(model.isGroup || model.groupChildNum))
	{
		if (model.modifierNum)
		{
			for (int i = 0; i < model.modifierNum; i++)
			{
				modifier_pde modifier = model.modifier[i];
				//Matrix_PDE mat;
				if (modifier.isSkin&&modifier.skinVertnum)
				{
					for (int j = 0; j < modifier.skinVertnum; j++)
					{
						//�������ã�Ȩ������
						skinVert_pde skinVert = modifier.skinVert[j];
						vertex_pde &vertex = model.vertex[skinVert.vertexId];
						normal_pde &normal = model.normal[skinVert.vertexId];
						for (int t = 0; t < skinVert.num; t++)
						{

							model_pde bones = bone;
							while (model.groupChildNum&&wcscmp(bones.modelType, _T("bone")))
							{
								if (model.nodeId == skinVert.bone[t].boneId)
								{
									//										mat = model.absolute;
									break;
								}
								bones = bones.modelChild[0];
							}


						}
					}
				}
			}
		}

	}
	else
	{
		for (int i = 0; i < model.groupChildNum; i++)
		{
			ModelSkinSet(model.modelChild[i], bone);
		}
	}
}

void ModelInput_PDE::GenerationEBO(model_pde *model)
{
	int t = 0;
	EBO_pde vertexebos;
	unsigned int *mesh = new unsigned int[model->faceNum * 3];
	vertexebos.textureIndex = modelRoot.materialList[model->materialIndex].texture[0].textureIndex;
	if (!textureOrNormalEBO)
	{
		IndexVertexAndCoordAndNormal(model);
	}
	else
	{
		IndexVertexToCoord(model);
	}
	for (int i = 0; i < model->faceNum; i++)
	{
		mesh[t] = model->mesh[i].coord[0];
		mesh[t + 1] = model->mesh[i].coord[1];
		mesh[t + 2] = model->mesh[i].coord[2];
		t += 3;
	}

	glGenVertexArrays(1, &vertexebos.Cvaoid);
	glBindVertexArray(vertexebos.Cvaoid);

	if (!textureOrNormalEBO)
	{
		//����vbo
		glGenBuffers(1, &vertexebos.Nvboid);
		glBindBuffer(GL_ARRAY_BUFFER, vertexebos.Nvboid);
		glBufferData(GL_ARRAY_BUFFER, 3 * model->normalReset.size()*sizeof(float), model->normalReset.data(), GL_STATIC_DRAW);

	}

	//����vbo
	glGenBuffers(1, &vertexebos.Vvboid);
	glBindBuffer(GL_ARRAY_BUFFER, vertexebos.Vvboid);
	glBufferData(GL_ARRAY_BUFFER, 3 * model->vertexReset.size()*sizeof(float), model->vertexReset.data(), GL_STATIC_DRAW);


	//����vbo
	glGenBuffers(1, &vertexebos.Cvboid);
	glBindBuffer(GL_ARRAY_BUFFER, vertexebos.Cvboid);
	glBufferData(GL_ARRAY_BUFFER, 2 * model->coord.size()*sizeof(float), model->coord.data(), GL_STATIC_DRAW);

	//����EBO����	
	glGenBuffers(1, &vertexebos.Ceboid);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vertexebos.Ceboid);
	//����EBO����
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, model->faceNum * 3 * sizeof(unsigned int), mesh, GL_STATIC_DRAW);

	//���EBO
	glBindVertexArray(0);
	//���EBO
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	//���VBO
	glBindBuffer(GL_ARRAY_BUFFER, 0);


	vertexebos.CvertexNum = model->faceNum * 3;
	vertexEBO.push_back(vertexebos);
	delete[] mesh;

}

void ModelInput_PDE::GenerationAllEBO()
{

	for (int i = 0;i < modelRoot.modelNum;i++)
	{
		model_pde *model = &modelRoot.modelList[i];
		GenerationEBO(model);
	}

}

bool ModelInput_PDE::IsExtensionSupported(char* szTargetExtension)
{
	const unsigned char *pszExtensions = NULL;
	const unsigned char *pszStart;
	unsigned char *pszWhere, *pszTerminator;

	// Extension names should not have spaces
	pszWhere = (unsigned char *)strchr(szTargetExtension, ' ');
	if (pszWhere || *szTargetExtension == '\0')
		return false;

	// Get Extensions String
	pszExtensions = glGetString(GL_EXTENSIONS);

	// Search The Extensions String For An Exact Copy
	pszStart = pszExtensions;
	for (;;)
	{
		pszWhere = (unsigned char *)strstr((const char *)pszStart, szTargetExtension);
		if (!pszWhere)
			break;
		pszTerminator = pszWhere + strlen(szTargetExtension);
		if (pszWhere == pszStart || *(pszWhere - 1) == ' ')
			if (*pszTerminator == ' ' || *pszTerminator == '\0')
				return true;
		pszStart = pszTerminator;
	}
	return false;
}

void ModelInput_PDE::DrawEBO(EBO_pde ebo)
{

	glBindTexture(GL_TEXTURE_2D, ebo.textureIndex);

	//������ذ�
	if (!textureOrNormalEBO)
	{
		glEnableClientState(GL_NORMAL_ARRAY);
		glBindBuffer(GL_ARRAY_BUFFER, ebo.Nvboid);
		//glNormalPointer(GL_FLOAT, 0, 0);
	}

	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glEnableClientState(GL_VERTEX_ARRAY);
	///*
	glBindBuffer(GL_ARRAY_BUFFER, ebo.Cvboid);
	glTexCoordPointer(2, GL_FLOAT, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, ebo.Vvboid);
	glVertexPointer(3, GL_FLOAT, 0, 0);

	//��vao�����л���
	//*/
	//glBindVertexArray(ebo.Cvaoid);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo.Ceboid);
	glDrawElements(GL_TRIANGLES, ebo.CvertexNum, GL_UNSIGNED_INT, NULL);



	//�����ذ�
	if (!textureOrNormalEBO)
	{
		glDisableClientState(GL_NORMAL_ARRAY);
	}
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	//glBindBuffer(GL_ARRAY_BUFFER, 0);


}

void ModelInput_PDE::DrawAllEBO()
{

	for (int i = 0; i < vertexEBO.size(); i++)
	{
		DrawEBO(vertexEBO[i]);
	}

}

/** ��ʼ���������� */
bool ModelInput_PDE::initMultiTexture()
{
	/** ����Ƿ�֧����չ */
	//if (isExtensionSupported("GL_ARB_multitexture"))
	//{

	/** ��ú���ָ���ַ */
	glActiveTextureARB = (PFNGLACTIVETEXTUREARBPROC)wglGetProcAddress("glActiveTextureARB");
	glMultiTexCoord2fARB = (PFNGLMULTITEXCOORD2FARBPROC)wglGetProcAddress("glMultiTexCoord2fARB");

	return true;
	//}
	//else
	//	return false;
}

void ModelInput_PDE::GenVertex(model_pde *model)
{
	int t = 0;
	EBO_pde vertexebos;

	unsigned int *mesh = new unsigned int[model->faceNum * 3];
	glBindTexture(GL_TEXTURE_2D, modelRoot.materialList[model->materialIndex].texture[0].textureIndex);
	if (!textureOrNormalEBO)
	{
		IndexVertexAndCoordAndNormal(model);
	}
	else
	{
		IndexVertexToCoord(model);
	}
	for (int i = 0; i < model->faceNum; i++)
	{
		mesh[t] = model->mesh[i].coord[0];
		mesh[t + 1] = model->mesh[i].coord[1];
		mesh[t + 2] = model->mesh[i].coord[2];
		t += 3;
	}


	//������ذ�
	if (!textureOrNormalEBO)
	{
		glEnableClientState(GL_NORMAL_ARRAY);
		//glNormalPointer(GL_FLOAT, 0, 0);
	}

	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glEnableClientState(GL_VERTEX_ARRAY);

	glTexCoordPointer(2, GL_FLOAT, 0, model->coord.data());
	glVertexPointer(3, GL_FLOAT, 0, model->vertexReset.data());

	glDrawElements(GL_TRIANGLES, model->faceNum * 3, GL_UNSIGNED_INT, mesh);



	//�����ذ�
	if (!textureOrNormalEBO)
	{
		glDisableClientState(GL_NORMAL_ARRAY);
	}
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);

	delete[] mesh;

}

void ModelInput_PDE::DrawVertex(EBO_pde ebo)
{

}


//Texture_PDE======================================================================
PurpleDreamElf_model::PurpleDreamElf_model()
{
	boneAndweight.boneId = -1;
	boneAndweight.weight = 0;

	//skinVert.skinVertType = NULL;
	skinVert.num = 0;
	skinVert.vertexId = -1;

	mapVert.x = 0;
	mapVert.y = 0;
	mapVert.z = 0;

	mapFace.x = 0;
	mapFace.y = 0;
	mapFace.z = 0;

	//texture.fileName = NULL;
	//texture.name = NULL;
	texture.ClipH = 0;
	texture.ClipU = 0;
	texture.ClipV = 0;
	texture.ClipW = 0;
	texture.isSupport = false;
	texture.textureIndex = -1;

	normal.x = 0;
	normal.y = 0;
	normal.z = 0;

	vertex.x = 0;
	vertex.y = 0;
	vertex.z = 0;

	//modifier.modName = NULL;
	//modifier.skinType = NULL;
	modifier.isSkin = false;
	modifier.skinVertnum = 0;

	//light.type = NULL;
	light.aspectRatio = 0;
	light.B = 0;
	light.end = 0;
	light.fallOff = 0;
	light.G = 0;
	light.multiplier = 0;
	light.R = 0;
	light.start = 0;
	light.targetId = -1;


	face.edges[0] = 0;
	face.edges[1] = 0;
	face.edges[2] = 0;
	face.matId = -1;
	face.n[0] = 0;
	face.n[1] = 0;
	face.n[2] = 0;
	face.smGroups = 0;
	face.v[0] = 0;
	face.v[1] = 0;
	face.v[2] = 0;

	//mapChannel.type = NULL;
	mapChannel.id = -1;
	mapChannel.mapfaceNum = 0;
	mapChannel.mapVertNum = 0;

	//material.className = NULL;
	//material.materialName = NULL;
	//material.materialName = NULL;
	material.ambient[0] = 0;
	material.ambient[1] = 0;
	material.ambient[2] = 0;
	material.diffuse[0] = 0;
	material.diffuse[1] = 0;
	material.diffuse[2] = 0;
	material.glossiness = 0;
	material.IsMultiType = false;
	material.materialId = -1;
	material.materialIndex = -1;
	material.opacity = 0;
	material.specular[0] = 0;
	material.specular[1] = 0;
	material.specular[2] = 0;
	material.specularLevel = 0;
	material.subMaterialNum = 0;
	material.textureNum = 0;

	//model.modelName = NULL;
	//model.modelType = NULL;
	model.matIdNum = 0;
	model.smgroupNum = 0;
	model.B = 0;
	model.faceNum = 0;
	model.G = 0;
	model.groupChildNum = 0;
	model.haveMaterialIndex = false;
	model.isGroup = false;
	//model.isObjectXRef = false;
	model.mapChannelNum = 0;
	model.materialIndex = -1;
	model.modifierNum = 0;
	model.nodeId = -1;
	model.normalNum = 0;
	model.parentId = -1;
	model.R = 0;
	model.rotation[0] = 0;
	model.rotation[1] = 0;
	model.rotation[2] = 0;
	model.rotation[3] = 0;
	model.scale[0] = 0;
	model.scale[1] = 0;
	model.scale[2] = 0;
	model.scale[3] = 0;
	model.scale[4] = 0;
	model.scale[5] = 0;
	model.scale[6] = 0;
	model.translation[0] = 0;
	model.translation[1] = 0;
	model.translation[2] = 0;
	model.vertexNum = 0;

	modelRoot.materialNum = 0;
	modelRoot.modelNum = 0;


}

PurpleDreamElf_model::~PurpleDreamElf_model()
{
}

modelRoot_pde PurpleDreamElf_model::InitModelRoot(int modelNum, int materialNum)
{
	PurpleDreamElf_model mod;
	modelRoot.modelNum = modelNum;
	modelRoot.materialNum = materialNum;
	for (int i = 0;i < modelNum;i++)
	{
		modelRoot.modelList.push_back(mod.model);
	}

	for (int i = 0;i < materialNum;i++)
	{
		modelRoot.materialList.push_back(mod.material);
	}
	return modelRoot;
}

model_pde PurpleDreamElf_model::InitModel(int vertexNum, int faceNum, int normalNum, int mapChannelNum, int modifierNum)
{
	PurpleDreamElf_model mod;
	model.vertexNum = vertexNum;
	model.faceNum = faceNum;
	model.normalNum = normalNum;
	model.mapChannelNum = mapChannelNum;
	model.modifierNum = modifierNum;

	for (int i = 0;i < vertexNum;i++)
	{
		model.vertex.push_back(mod.vertex);
	}

	for (int i = 0;i < faceNum;i++)
	{
		model.mesh.push_back(mod.face);
	}

	for (int i = 0;i < normalNum;i++)
	{
		model.normal.push_back(mod.normal);
	}

	for (int i = 0;i < mapChannelNum;i++)
	{
		model.mapChannel.push_back(mod.mapChannel);
	}

	for (int i = 0;i < modifierNum;i++)
	{
		model.modifier.push_back(mod.modifier);
	}
	return model;
}

mapChannel_pde PurpleDreamElf_model::InitMapChannel(int mapVertNum, int mapfaceNum)
{
	PurpleDreamElf_model mod;
	mapChannel.mapVertNum = mapVertNum;
	mapChannel.mapfaceNum = mapfaceNum;
	for (int i = 0;i < mapVertNum;i++)
	{
		mapChannel.mapVert.push_back(mod.mapVert);
	}

	for (int i = 0;i < mapfaceNum;i++)
	{
		mapChannel.mapFace.push_back(mod.mapFace);
	}
	return mapChannel;
}

modifier_pde PurpleDreamElf_model::InitModifier(int skinVertnum)
{
	PurpleDreamElf_model mod;
	modifier.skinVertnum = skinVertnum;
	for (int i = 0;i < skinVertnum;i++)
	{
		modifier.skinVert.push_back(mod.skinVert);
	}
	return modifier;
}

skinVert_pde PurpleDreamElf_model::InitSkinVert(int num)
{
	PurpleDreamElf_model mod;
	skinVert.num = num;
	for (int i = 0;i < num;i++)
	{
		skinVert.bone.push_back(mod.boneAndweight);
	}
	return skinVert;
}

vector<normal_pde> PurpleDreamElf_model::InitNormal(int normalNum)
{
	PurpleDreamElf_model mod;
	vector<normal_pde> normalChild;
	for (int i = 0; i < normalNum; i++)
	{
		normalChild.push_back(mod.normal);
	}
	return normalChild;
}