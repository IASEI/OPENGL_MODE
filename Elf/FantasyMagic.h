#ifndef __FANTASYMAGIC_H__
#define __FANTASYMAGIC_H__

#include "fantastic.h"
//��ѧ��=================================================================

class Vector3_PDE
{
public:
	/** ���캯�� */
	Vector3_PDE();
	Vector3_PDE(float xx, float yy, float zz);
	Vector3_PDE(const Vector3_PDE& vec);
	Vector3_PDE(float xx, float yy, float zz, float ww);


	/** ��Ա���� */
	float length();                       /**< ������������ */
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
	float x, y, z, w;

};

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

class  Matrix4x4_PDE
{
public:
	///���캯��
	Matrix4x4_PDE();
	Matrix4x4_PDE(const Matrix4x4_PDE &m);
	Matrix4x4_PDE(float r11, float r12, float r13, float r14,
		float r21, float r22, float r23, float r24,
		float r31, float r32, float r33, float r34,
		float r41, float r42, float r43, float r44);
	~Matrix4x4_PDE();

	///���þ���
	void Clear();
	void Zero();

	///���������
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

	///ƽ��һ����
	void Translate(Vector3_PDE Translate);
	void Translate(float x, float y, float z);
	void inverseTranslate();

	///��תһ����
	void Rotate(double angle, float x, float y, float z);

	///������������
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

//�ṹ��=================================================================

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

	//֧������
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
	bool IsMultiType;//�Ƿ�Ϊ���ز���
	int  materialId;//�Ƿ�Ϊ���ز���(�ǣ�������-1)

	int materialIndex;//��������
	int textureNum;//��������
	int subMaterialNum;//�Ӳ�������

					   //���Ƕ��ز���
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
	TCHAR modelName[255];//ģ������
	TCHAR modelType[255];//����



	int coordNum;
	int vertexNum;//������Ŀ
	int faceNum;//�����Ŀ
	int normalNum;//������Ŀ
	int mapChannelNum;//ӳ��ͨ��
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

				//����
	Matrix4x4_PDE relative;
	Matrix4x4_PDE absolute;
	Matrix4x4_PDE ma;

	vector<coord_pde> coord;
	vector<mapChannel_pde> mapChannel;//exportMesh
	vector<normal_pde> meshnormal;//�淨��
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

//һ����=================================================================
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

/** ������� */
class Camera_PDE
{
public:

	/** ���캯������������ */
	Camera_PDE();
	~Camera_PDE();

	/** ��������״̬���� */
	Vector3_PDE getPosition() { return m_Position; }
	Vector3_PDE getView() { return m_View; }
	Vector3_PDE getUpVector() { return m_UpVector; }
	float   getSpeed() { return m_Speed; }

	/** �����ٶ� */
	void setSpeed(float speed)
	{
		m_Speed = speed;
	}

	/** �����������λ��, �۲����������� */
	void setCamera(float positionX, float positionY, float positionZ,
		float viewX, float viewY, float viewZ,
		float upVectorX, float upVectorY, float upVectorZ);

	/** ��ת��������� */
	void rotateView(float angle, float X, float Y, float Z);

	/** �����������������۲췽�� */
	void setViewByMouse();

	/** ����������ƶ� */
	void yawCamera(float speed);

	/** ǰ���ƶ������ */
	void moveCamera(float speed);

	/** ��������� */
	void setLook();

	//�õ������ָ��
	static Camera_PDE* GetCamera(void) { return m_pCamera; }


private:
	/** ��������� */
	static Camera_PDE  *m_pCamera;      /**< ��ǰȫ�������ָ�� */
	Vector3_PDE        m_Position;      /**< λ�� */
	Vector3_PDE        m_View;          /**< ���� */
	Vector3_PDE        m_UpVector;      /**< �������� */
	float          m_Speed;         /**< �ٶ� */

};

class ModelInput_PDE
{
public:
	ModelInput_PDE();

	~ModelInput_PDE();

	//�������뺯��
public:

	//������Ϣ�ֱ�1
	void ImportChoose(const TCHAR *channge, model_pde *models, FILE *fp);

	//������Ϣ�ֱ�2
	void ImportChoose(const TCHAR *channge, FILE *fp);

	//����ģ����Ϣ
	bool ImportFile(const TCHAR *filename);

	//�����ܵ�����
	void ImportModelRoot(FILE *fp);

	//���뵥��ģ����Ϣ����תվ��
	void ImportModel(modelRoot_pde *modelRoot, FILE *fp);

	//���뵥��ģ��ͷ��Ϣ
	void ImportModelName(model_pde *models, FILE *fp);

	//���뵥��ģ��ȫ����Ϣ
	void ImportModelInformation(model_pde *models, FILE *fp);

	//����ͨ��
	void ImportMapChannel(model_pde *models, FILE *fp);

	//���뷨��
	void ImportNormals(model_pde *models, FILE *fp);

	//���붥��
	void ImportVertex(model_pde *models, FILE *fp);

	//������������
	void ImportCoord(model_pde *models, FILE *fp);

	//���������Ϣ
	void ImportMesh(model_pde *models, FILE *fp);

	//����ƹ�
	void ImportLight(model_pde *models, FILE *fp);

	//�����޸���
	void ImportModifier(model_pde *models, FILE *fp);

	//�������
	void ImportMaterial(FILE *fp);

	//�����Ӳ���
	void ImportMaterialChild(material_pde *material, FILE *fp);

public:

	material_pde *GetMaterial(modelRoot_pde modelRoots, const TCHAR *materialName);

	modifier_pde *GetModifier(model_pde model, const TCHAR *modelName);

	//Ϊ�������id
	void GenTexxtureID();

	//Ϊ�������id��
	void GenTextureIDChild(material_pde *material);

	//�����淨��
	void GenerationMeshNormal(model_pde *model);

	//ȫ�������淨��

	void GenerationAllMeshNormal();

	void IndexVertexToCoord(model_pde *model);//ʹ������Ŀ����������Ŀ

	void IndexVertexAndCoordAndNormal(model_pde *model);//ʹ������Ŀ��������Ŀ,������Ŀ�����

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

	/** ��ʼ���������� */
	bool initMultiTexture();

	void GenVertex(model_pde *model);

	void DrawVertex(EBO_pde ebo);

	modelRoot_pde *GetModelRoot();

	vector<EBO_pde> GetEBOVector();

	Matrix4x4_PDE ma[25];

private:
	FILE *fp;

	bool textureOrNormalEBO;//true ʹ��������������Ϊ��Ҫ������falseʹ�÷�������Ϊ��Ҫ����
	
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