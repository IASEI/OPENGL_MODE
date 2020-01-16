#ifndef __FANTASYMAGIC_H__
#define __FANTASYMAGIC_H__

#include "fantastic.h"
//数学类=================================================================

class Vector3_PDE
{
public:
	/** 构造函数 */
	Vector3_PDE();
	Vector3_PDE(float xx, float yy, float zz);
	Vector3_PDE(const Vector3_PDE& vec);
	Vector3_PDE(float xx, float yy, float zz, float ww);


	/** 成员函数 */
	float length();                       /**< 计算向量长度 */
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
	float x, y, z, w;

};

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

class  Matrix4x4_PDE
{
public:
	///构造函数
	Matrix4x4_PDE();
	Matrix4x4_PDE(const Matrix4x4_PDE &m);
	Matrix4x4_PDE(float r11, float r12, float r13, float r14,
		float r21, float r22, float r23, float r24,
		float r31, float r32, float r33, float r34,
		float r41, float r42, float r43, float r44);
	~Matrix4x4_PDE();

	///重置矩阵
	void Clear();
	void Zero();

	///运算符重载
	void operator=(Matrix4x4_PDE m);
	Matrix4x4_PDE operator-(Matrix4x4_PDE m);
	Matrix4x4_PDE operator+(Matrix4x4_PDE m);
	Matrix4x4_PDE operator*(Matrix4x4_PDE m);
	Matrix4x4_PDE operator/(Matrix4x4_PDE m);

	void operator +=(Matrix4x4_PDE m);
	void operator -=(Matrix4x4_PDE m);
	void operator *=(Matrix4x4_PDE m);
	void operator /=(Matrix4x4_PDE m);

	Matrix4x4_PDE operator-(float f);
	Matrix4x4_PDE operator+(float f);
	Matrix4x4_PDE operator*(float f);
	Matrix4x4_PDE operator/(float f);

	void operator -=(float f);
	void operator +=(float f);
	void operator *=(float f);
	void operator /=(float f);

	bool operator ==(Matrix4x4_PDE v);
	bool operator !=(Matrix4x4_PDE v);

	///平移一个点
	void Translate(Vector3_PDE Translate);
	void Translate(float x, float y, float z);
	void inverseTranslate();

	///旋转一个点
	void Rotate(double angle, float x, float y, float z);

	///向量与矩阵相乘
	Vector3_PDE VectorMatrixMultiply(Vector3_PDE v);
	Vector3_PDE VectorMatrixMultiply3x3(Vector3_PDE v);


public:
	float matrix[16];
};

class Quaternion_PDE
{
public:
	Quaternion_PDE();
	~Quaternion_PDE();
	Quaternion_PDE(float _x, float _y, float _z, float _w);
	void ToMatrix(float *matrix);

	static Quaternion_PDE FromRotation(float _x, float _y, float _z, float angleInDegree);
private:
	float x, y, z, w;
};

//结构体=================================================================

struct boneAndweight_pde
{
	int boneId;
	float weight;
};

struct skinVert_pde
{
	TCHAR skinVertType[255];
	int vertexId;
	int num;
	vector<boneAndweight_pde> bone;
};

struct mapVert_pde
{
	float x, y, z;

};

struct mapFace_pde
{
	float x, y, z;
};

struct texture_pde
{
	TCHAR name[255];
	GLuint textureIndex;
	bool isSupport;

	//支持纹理
	TCHAR fileName[255];
	float ClipU, ClipV, ClipW, ClipH;
	//
	vector<texture_pde> textureChild;
};

struct normal_pde
{
	float x, y, z;
};

struct coord_pde
{
	float coord_x, coord_y;
};

struct vertex_pde
{
	float x, y, z;
};

struct vertex_coord_pde
{
	float vx, vy, vz, cx, cy;
};

struct modifier_pde
{
	TCHAR modName[255];
	bool isSkin;
	TCHAR skinType[255];
	int skinVertnum;
	vector<skinVert_pde>skinVert;
};

struct light_pde
{
	TCHAR type[255];
	int targetId;
	float R, G, B;
	float multiplier;
	float aspectRatio;
	float end;
	float start;
	float fallOff;


};

struct face_pde
{
	float meshNormal;
	float v[3];
	float n[3];
	float coord[3];
	unsigned int smGroups;
	int matId;
	float edges[3];
};

struct mapChannel_pde
{
	int id;

	int mapVertNum;
	int mapfaceNum;

	TCHAR type[255];

	vector<mapVert_pde> mapVert;
	vector<mapFace_pde> mapFace;

};

struct  material_pde
{
	TCHAR materialName[255];
	TCHAR className[255];
	bool IsMultiType;//是否为多重材质
	int  materialId;//是否为多重材质(是，不等于-1)

	int materialIndex;//材质索引
	int textureNum;//纹理数量
	int subMaterialNum;//子材质数量

					   //不是多重材质
	float diffuse[3];
	float ambient[3];
	float specular[3];
	float specularLevel;
	float glossiness;
	float opacity;

	vector<texture_pde> texture;

	//
	vector<material_pde> subMaterial;
};

struct model_pde
{
	TCHAR modelName[255];//模型名称
	TCHAR modelType[255];//类型



	int coordNum;
	int vertexNum;//顶点数目
	int faceNum;//面的数目
	int normalNum;//法线数目
	int mapChannelNum;//映射通道
	int modifierNum;
	int matIdNum;
	int smgroupNum;

	//NodeTM
	float translation[3];
	float rotation[4];
	float scale[7];

	//	Matrix_PDE relative;
	//Matrix_PDE absolute;

	// group ?
	bool isGroup;
	int groupChildNum;

	//
	//bool isObjectXRef;
	//

	int parentId;
	int nodeId;//parent id

	bool haveMaterialIndex;// material index ?

	int materialIndex;//material index

	int R, G, B;//RGB

				//骨骼
	Matrix4x4_PDE relative;
	Matrix4x4_PDE absolute;
	Matrix4x4_PDE ma;

	vector<coord_pde> coord;
	vector<mapChannel_pde> mapChannel;//exportMesh
	vector<normal_pde> meshnormal;//面法线
	vector<normal_pde> normal;//exportMesh
	vector<vertex_pde> vertex;//exportMesh
	vector<face_pde> mesh;	//exportMesh

	vector<normal_pde> normalReset;//exportMesh
	vector<vertex_pde> vertexReset;//exportMesh
	vector<coord_pde> coordReset;

	//vector<int> matID;
	//vector<int>	smGroup;
	vector<light_pde> light;
	vector<modifier_pde> modifier;//exportAll


								  //group ?
	vector<model_pde> modelChild;

};

struct modelRoot_pde
{
	int modelNum;
	int materialNum;
	vector<model_pde> modelList;
	vector<material_pde> materialList;
};

typedef struct ImageID
{
	char name[10];
	BYTE  *pixels;
	int width;
	int height;
	GLuint id;
}IMID;

struct EBO_pde
{
	GLuint Vvaoid, Cvaoid, Nvaoid;
	GLuint Vvboid, Cvboid, Nvboid;
	GLuint Veboid, Ceboid, Neboid;
	GLuint VvertexNum, CvertexNum, NvertexNum;
	GLuint textureIndex;
};

//一般类=================================================================
class Texture_PDE
{
public:
	Texture_PDE();
	~Texture_PDE();
	int CreateTextures(char *path, char *name);
	int  CreateBitTextures(TCHAR *path, char *name);
	bool LoadBitmap(const char *file, IMID *imid);
	void StartTextures(bool start);
	void SetImidVector(vector<IMID>* ttd);
	GLuint GetTexturesIndex(char *name);
	//vector<IMID> GetTextureVector();
private:
	vector<IMID> texture;
};

/** 摄像机类 */
class Camera_PDE
{
public:

	/** 构造函数和析构函数 */
	Camera_PDE();
	~Camera_PDE();

	/** 获得摄像机状态方法 */
	Vector3_PDE getPosition() { return m_Position; }
	Vector3_PDE getView() { return m_View; }
	Vector3_PDE getUpVector() { return m_UpVector; }
	float   getSpeed() { return m_Speed; }

	/** 设置速度 */
	void setSpeed(float speed)
	{
		m_Speed = speed;
	}

	/** 设置摄像机的位置, 观察点和向上向量 */
	void setCamera(float positionX, float positionY, float positionZ,
		float viewX, float viewY, float viewZ,
		float upVectorX, float upVectorY, float upVectorZ);

	/** 旋转摄像机方向 */
	void rotateView(float angle, float X, float Y, float Z);

	/** 根据鼠标设置摄像机观察方向 */
	void setViewByMouse();

	/** 左右摄像机移动 */
	void yawCamera(float speed);

	/** 前后移动摄像机 */
	void moveCamera(float speed);

	/** 放置摄像机 */
	void setLook();

	//得到摄像机指针
	static Camera_PDE* GetCamera(void) { return m_pCamera; }


private:
	/** 摄像机属性 */
	static Camera_PDE  *m_pCamera;      /**< 当前全局摄像机指针 */
	Vector3_PDE        m_Position;      /**< 位置 */
	Vector3_PDE        m_View;          /**< 朝向 */
	Vector3_PDE        m_UpVector;      /**< 向上向量 */
	float          m_Speed;         /**< 速度 */

};

class ModelInput_PDE
{
public:
	ModelInput_PDE();

	~ModelInput_PDE();

	//公共导入函数
public:

	//导入信息分辨1
	void ImportChoose(const TCHAR *channge, model_pde *models, FILE *fp);

	//导入信息分辨2
	void ImportChoose(const TCHAR *channge, FILE *fp);

	//导入模型信息
	bool ImportFile(const TCHAR *filename);

	//导入总的数据
	void ImportModelRoot(FILE *fp);

	//导入单个模型信息（中转站）
	void ImportModel(modelRoot_pde *modelRoot, FILE *fp);

	//导入单个模型头信息
	void ImportModelName(model_pde *models, FILE *fp);

	//导入单个模型全部信息
	void ImportModelInformation(model_pde *models, FILE *fp);

	//导入通道
	void ImportMapChannel(model_pde *models, FILE *fp);

	//导入法线
	void ImportNormals(model_pde *models, FILE *fp);

	//导入顶点
	void ImportVertex(model_pde *models, FILE *fp);

	//导入纹理坐标
	void ImportCoord(model_pde *models, FILE *fp);

	//导入面的信息
	void ImportMesh(model_pde *models, FILE *fp);

	//导入灯光
	void ImportLight(model_pde *models, FILE *fp);

	//导入修改器
	void ImportModifier(model_pde *models, FILE *fp);

	//导入材质
	void ImportMaterial(FILE *fp);

	//导入子材质
	void ImportMaterialChild(material_pde *material, FILE *fp);

public:

	material_pde *GetMaterial(modelRoot_pde modelRoots, const TCHAR *materialName);

	modifier_pde *GetModifier(model_pde model, const TCHAR *modelName);

	//为纹理分配id
	void GenTexxtureID();

	//为纹理分配id续
	void GenTextureIDChild(material_pde *material);

	//生成面法线
	void GenerationMeshNormal(model_pde *model);

	//全部生成面法线

	void GenerationAllMeshNormal();

	void IndexVertexToCoord(model_pde *model);//使顶点数目等于纹理数目

	void IndexVertexAndCoordAndNormal(model_pde *model);//使顶点数目，纹理数目,法线数目都相等

public:

	void ModelDraw(TCHAR *name);

	void all();

	void ModelDrawUseVertex(model_pde model, GLenum type);

	void ModelSkinSet(model_pde &model, model_pde &bone);

	void GenerationEBO(model_pde *model);

	void GenerationAllEBO();

	bool IsExtensionSupported(char* szTargetExtension);

	void DrawEBO(EBO_pde ebo);

	void DrawAllEBO();

	/** 初始化多重纹理 */
	bool initMultiTexture();

	void GenVertex(model_pde *model);

	void DrawVertex(EBO_pde ebo);

	modelRoot_pde *GetModelRoot();

	vector<EBO_pde> GetEBOVector();

	Matrix4x4_PDE ma[25];

private:
	FILE *fp;

	bool textureOrNormalEBO;//true 使用纹理索引的作为主要索引，false使用法向量作为主要索引
	
	TCHAR buffer[100];
	TCHAR change[255];

	Texture_PDE TexGen;
	modelRoot_pde modelRoot;

	vector<EBO_pde> vertexEBO;
	
	
};

class PurpleDreamElf_model
{
public:
	PurpleDreamElf_model();

	~PurpleDreamElf_model();

	modelRoot_pde InitModelRoot(int modelNum, int materialNum);

	model_pde InitModel(int vertexNum, int faceNum, int normalNum, int mapChannelNum, int modifierNum);



	mapChannel_pde InitMapChannel(int mapVertNum, int mapfaceNum);

	modifier_pde InitModifier(int skinVertnum);

	skinVert_pde InitSkinVert(int num);

	vector<normal_pde> InitNormal(int normalNum);

public:
	boneAndweight_pde boneAndweight;
	skinVert_pde skinVert;
	mapVert_pde mapVert;
	mapFace_pde mapFace;
	texture_pde texture;
	normal_pde normal;
	vertex_pde vertex;
	modifier_pde modifier;
	light_pde light;
	face_pde face;
	mapChannel_pde mapChannel;
	//bone_pde bone;
	material_pde material;
	model_pde model;

	modelRoot_pde modelRoot;

};

#endif