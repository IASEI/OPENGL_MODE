#include "test.h"

#include "Elf\fantastic.h"

bool My::Init()
{

	glewInit();
	GLfloat ambient[] = { 200.0, 200.0, 200.0, 200.0 }; /**< ������ */
	GLfloat diffuse[] = { 1.0, 1.0, 1.0, 1.0 }; /**< ����� */
	GLfloat specular[] = { 1.0, 1.0, 1.0, 1.0 };/**< ����� */
	GLfloat position[] = { 0.0, 3.0, 2.0, 0.0 };/**< ��Դλ�� */

												///���ù�Դ����
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
	glLightfv(GL_LIGHT0, GL_POSITION, position);

	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);
	glClearDepth(1.0f);
	glDepthFunc(GL_LEQUAL);
	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_POLYGON_SMOOTH);
	glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glEnable(GL_POINT_SMOOTH);
	glHint(GL_POINT_SMOOTH_HINT,GL_NICEST);
	glEnable(GL_LINE_SMOOTH);
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);

	ResizeDraw(true);
	R = 0;
	t = 0;
	xRotation = 0;
	yRotation = 0;
	m_Camera.setCamera(0, 15.5, 15, 0, -1, -3, 0, 1, 0);
	glEnable(GL_LIGHTING); /**< ���ù�Դ */
	glEnable(GL_LIGHT0);  /**< ����0�Ź�Դ */
	glEnable(GL_TEXTURE_2D);
	return true;
}

void My::UpdateCamera()
{
	m_Camera.setViewByMouse();

	/** ���̰�����Ӧ */
	if (m_Keys.IsPressed(VK_SHIFT))                        /**< ����SHIFT��ʱ���� */
	{
		exit(0);
	}

	if (m_Keys.IsPressed('Q'))
	{
		
	}

	if (!m_Keys.IsPressed(VK_SHIFT))
	{
		m_Camera.setSpeed(1.0f);
	}
	if (m_Keys.IsPressed(VK_UP) || m_Keys.IsPressed('W'))   /**< ���Ϸ������'W'������ */
		m_Camera.moveCamera(m_Camera.getSpeed());          /**< �ƶ������ */

	if (m_Keys.IsPressed(VK_DOWN) || m_Keys.IsPressed('S')) /**< ���·������'S'������ */
		m_Camera.moveCamera(-m_Camera.getSpeed());         /**< �ƶ������ */

	if (m_Keys.IsPressed(VK_LEFT) || m_Keys.IsPressed('A')) /**< ���������'A'������ */
		m_Camera.yawCamera(-m_Camera.getSpeed());          /**< �ƶ������ */

	if (m_Keys.IsPressed(VK_RIGHT) || m_Keys.IsPressed('D')) /**< ���ҷ������'D'������ */
		m_Camera.yawCamera(m_Camera.getSpeed());            /**< �ƶ������ */

	if (m_Keys.IsPressed(VK_RIGHT) || m_Keys.IsPressed('T')) /**< ���ҷ������'D'������ */
		t++;            /**< �ƶ������ */

	Vector3_PDE vPos = m_Camera.getPosition();                  /**< �õ���ǰ�����λ�� */
	Vector3_PDE vNewPos = vPos;
	Vector3_PDE vView = m_Camera.getView();											/** ��������� */
	m_Camera.setCamera(vNewPos.x, vNewPos.y, vNewPos.z,
		vView.x, vView.y, vView.z,
		0, 1, 0);


}
void My::Draw()
{
	EBO_pde ebo;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_MULTISAMPLE_ARB);	
	glLoadIdentity();
	
	m_Camera.setLook();
	glColor3ub(255, 0, 0);
	glBegin(GL_TRIANGLES);
		glVertex3f(-20, 0, 0);
		glVertex3f(20, 0, 0);
		glVertex3f(0, 20, 0);
	glEnd();
}

void My::Uninit()
{

}

void My::Update(DWORD milliseconds)
{
	
	
	R += 1;
	Matrix4x4_PDE transpose, rotTemp1, rotTemp2, tempRelative;
	rotTemp1.Rotate(R, 0, 1, 0);
	UpdateCamera();
}


DimensionWorld *DimensionWorld::Create(const TCHAR * class_name)
{
	/*reinterpret_cast�����ݴ�һ�����͵�ת��Ϊ��һ�����͡�
	��ν��ͨ��Ϊ��������λģʽ�ṩ�ϵͲ�
	�����½��͡�Ҳ����˵�������Զ����ƴ�
	����ʽ�����½���*/
	My * example = new My(class_name);
	return reinterpret_cast<My *>(example);
}

My::My(const TCHAR * class_name) : DimensionWorld(class_name)
{
}