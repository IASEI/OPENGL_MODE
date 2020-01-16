//========================================================
/**
*  @file      Vector.h
*
*  项目描述： 3DS文件载入
*  文件描述:  向量类  
*  适用平台： Windows98/2000/NT/XP
*  
*  作者：     WWBOSS
*  电子邮件:  wwboss123@gmail.com
*  创建日期： 2006-12-06	
*  修改日期： 2006-12-10
*
*/     
//========================================================

#ifndef __VECTOR_PDE_H__
#define __VECTOR_PDE_H__


#include <stdio.h>
/** 向量类 */

#include <cmath>
class Vector3_PDE
{
public:
	/** 构造函数 */
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
		///初始化.
		x = xx;
		y = yy;
		z = zz;
		w = ww;
	}


	/** 成员函数 */
	inline float length();                       /**< 计算向量长度 */
	Vector3_PDE normalize();/**< 单位化向量 */

	float dotProduct(const Vector3_PDE& v);          /**< 计算点积 */
	Vector3_PDE crossProduct(const Vector3_PDE& v);      /**< 计算叉积 */

												 /** 重载操作符 */
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

	//叉乘
	void CrossProduct(Vector3_PDE &v1, Vector3_PDE &v2);
	void CrossProduct3(Vector3_PDE &v1, Vector3_PDE &v2, Vector3_PDE &v3);

	//点乘
	float DotProduct3(Vector3_PDE &v1);
	float DotProduct4(Vector3_PDE &v1);
	Vector3_PDE operator - ();

public:
	float x, y, z,w;

};

/** 二维向量类 */
class Vector2
{
public:
	/** 构造函数 */
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

/** 单位化一向量 */
Vector3_PDE Vector3_PDE::normalize()
{
	float len = length();                  /**< 计算向量长度 */
	if (len == 0)
		len = 1;
	x = x / len;
	y = y / len;
	z = z / len;

	return *this;
}

/** 点积 */
float Vector3_PDE::dotProduct(const Vector3_PDE& v)
{
	return (x * v.x + y * v.y + z * v.z);
}

/** 叉积 */
Vector3_PDE Vector3_PDE::crossProduct(const Vector3_PDE& v)
{
	Vector3_PDE vec;

	vec.x = y * v.z - z * v.y;
	vec.y = z * v.x - x * v.z;
	vec.z = x * v.y - y * v.x;

	return vec;
}

/** 操作符 + */
Vector3_PDE Vector3_PDE::operator +(const Vector3_PDE& v)
{
	Vector3_PDE vec;

	vec.x = x + v.x;
	vec.y = y + v.y;
	vec.z = z + v.z;

	return vec;
}

/** 操作符 - */
Vector3_PDE Vector3_PDE::operator -(const Vector3_PDE& v)
{
	Vector3_PDE vec;

	vec.x = x - v.x;
	vec.y = y - v.y;
	vec.z = z - v.z;

	return vec;
}

/** 操作符 * */
Vector3_PDE Vector3_PDE::operator *(const Vector3_PDE& v)
{
	Vector3_PDE vec;

	vec.x = x * v.x;
	vec.y = y * v.y;
	vec.z = z * v.z;

	return vec;
}
/** 操作符 / */
Vector3_PDE Vector3_PDE::operator /(const Vector3_PDE& v)
{
	Vector3_PDE vec;

	vec.x = x / v.x;
	vec.y = y / v.y;
	vec.z = z / v.z;

	return vec;
}
/** 操作符 + */
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

/** 操作符 * */
Vector3_PDE Vector3_PDE::operator *(float f)
{
	x = x * f;
	y = y * f;
	z = z * f;

	return *this;
}

/** 操作符 / */
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

/** 操作符 * */
void Vector3_PDE::operator *=(float &v)
{
	x *= v;
	y *= v;
	z *= v;


}
/** 操作符 / */
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



/// 叉乘
void Vector3_PDE::CrossProduct(Vector3_PDE &v1, Vector3_PDE &v2)
{

	x = ((v1.y * v2.z) - (v1.z * v2.y));
	y = ((v1.z * v2.x) - (v1.x * v2.z));
	z = ((v1.x * v2.y) - (v1.y * v2.x));
}


void Vector3_PDE::CrossProduct3(Vector3_PDE &v1, Vector3_PDE &v2, Vector3_PDE &v3)
{
	///求得v1,v2,v3的叉积
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

/// 点乘
float Vector3_PDE::DotProduct3(Vector3_PDE &v1)
{
	return x * v1.x + y * v1.y + z * v1.z;
}


float Vector3_PDE::DotProduct4(Vector3_PDE &v1)
{
	return x * v1.x + y * v1.y + z * v1.z + w * v1.w;
}


/** 负号 */
Vector3_PDE Vector3_PDE::operator -()
{
	Vector3_PDE vec(-x, -y, -z);
	return vec;
}


#endif //__VECTOR_H__