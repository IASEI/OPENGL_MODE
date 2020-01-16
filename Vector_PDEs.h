//========================================================
/**
*  @file      Vector.h
*
*  ��Ŀ������ 3DS�ļ�����
*  �ļ�����:  ������  
*  ����ƽ̨�� Windows98/2000/NT/XP
*  
*  ���ߣ�     WWBOSS
*  �����ʼ�:  wwboss123@gmail.com
*  �������ڣ� 2006-12-06	
*  �޸����ڣ� 2006-12-10
*
*/     
//========================================================

#ifndef __VECTOR_PDE_H__
#define __VECTOR_PDE_H__


#include <stdio.h>
/** ������ */

#include <cmath>
class Vector3_PDE
{
public:
	/** ���캯�� */
	Vector3_PDE() { x = 0.0; y = 0.0; z = 0.0; }
	Vector3_PDE(float xx, float yy, float zz)
	{
		x = xx;
		y = yy;
		z = zz;
	}
	Vector3_PDE(const Vector3_PDE& vec)
	{
		x = vec.x;
		y = vec.y;
		z = vec.z;
	}
	Vector3_PDE(float xx, float yy, float zz, float ww)
	{
		///��ʼ��.
		x = xx;
		y = yy;
		z = zz;
		w = ww;
	}


	/** ��Ա���� */
	inline float length();                       /**< ������������ */
	Vector3_PDE normalize();/**< ��λ������ */

	float dotProduct(const Vector3_PDE& v);          /**< ������ */
	Vector3_PDE crossProduct(const Vector3_PDE& v);      /**< ������ */

												 /** ���ز����� */
	Vector3_PDE operator + (const Vector3_PDE& v);
	Vector3_PDE operator - (const Vector3_PDE& v);
	Vector3_PDE operator * (const Vector3_PDE& v);
	Vector3_PDE operator / (const Vector3_PDE& v);

	Vector3_PDE operator + (float f);
	Vector3_PDE operator - (float f);
	Vector3_PDE operator * (float f);
	Vector3_PDE operator / (float f);

	void operator +=(const Vector3_PDE & v);
	void operator -=(const Vector3_PDE & v);
	void operator *=(const Vector3_PDE & v);
	void operator /=(const Vector3_PDE & v);

	void operator +=(float & v);
	void operator -=(float & v);
	void operator *=(float & v);
	void operator /=(float & v);

	bool operator ==(Vector3_PDE &v);
	bool operator !=(Vector3_PDE &v);

	//���
	void CrossProduct(Vector3_PDE &v1, Vector3_PDE &v2);
	void CrossProduct3(Vector3_PDE &v1, Vector3_PDE &v2, Vector3_PDE &v3);

	//���
	float DotProduct3(Vector3_PDE &v1);
	float DotProduct4(Vector3_PDE &v1);
	Vector3_PDE operator - ();

public:
	float x, y, z,w;

};

/** ��ά������ */
class Vector2
{
public:
	/** ���캯�� */
	Vector2(float xx = 0.0, float yy = 0.0) { x = xx; y = yy; }
	Vector2(const Vector2& v)
	{
		x = v.x;
		y = v.y;
	}

public:
	float x, y;
};


inline float Vector3_PDE::length()
{
	return (float)(x * x + y * y + z * z);
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
	x +=v;
	y +=  v;
	z +=  v;

	
}

void  Vector3_PDE::operator -=(float &v)
{
	x -=  v;
	y -=  v;
	z -=v;

	
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
		x /=  v;
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


#endif //__VECTOR_H__