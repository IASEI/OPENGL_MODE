#include "test.h"

#include "Elf\fantastic.h"

bool My::Init()
{

	glewInit();
	GLfloat ambient[] = { 200.0, 200.0, 200.0, 200.0 }; /**< 环境光 */
	GLfloat diffuse[] = { 1.0, 1.0, 1.0, 1.0 }; /**< 漫射光 */
	GLfloat specular[] = { 1.0, 1.0, 1.0, 1.0 };/**< 镜面光 */
	GLfloat position[] = { 0.0, 3.0, 2.0, 0.0 };/**< 光源位置 */

												///设置光源属性
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
	glEnable(GL_LIGHTING); /**< 启用光源 */
	glEnable(GL_LIGHT0);  /**< 启用0号光源 */
	glEnable(GL_TEXTURE_2D);
	return true;
}

void My::UpdateCamera()
{
	m_Camera.setViewByMouse();

	/** 键盘按键响应 */
	if (m_Keys.IsPressed(VK_SHIFT))                        /**< 按下SHIFT键时加速 */
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
	if (m_Keys.IsPressed(VK_UP) || m_Keys.IsPressed('W'))   /**< 向上方向键或'W'键按下 */
		m_Camera.moveCamera(m_Camera.getSpeed());          /**< 移动摄像机 */

	if (m_Keys.IsPressed(VK_DOWN) || m_Keys.IsPressed('S')) /**< 向下方向键或'S'键按下 */
		m_Camera.moveCamera(-m_Camera.getSpeed());         /**< 移动摄像机 */

	if (m_Keys.IsPressed(VK_LEFT) || m_Keys.IsPressed('A')) /**< 向左方向键或'A'键按下 */
		m_Camera.yawCamera(-m_Camera.getSpeed());          /**< 移动摄像机 */

	if (m_Keys.IsPressed(VK_RIGHT) || m_Keys.IsPressed('D')) /**< 向右方向键或'D'键按下 */
		m_Camera.yawCamera(m_Camera.getSpeed());            /**< 移动摄像机 */

	if (m_Keys.IsPressed(VK_RIGHT) || m_Keys.IsPressed('T')) /**< 向右方向键或'D'键按下 */
		t++;            /**< 移动摄像机 */

	Vector3_PDE vPos = m_Camera.getPosition();                  /**< 得到当前摄像机位置 */
	Vector3_PDE vNewPos = vPos;
	Vector3_PDE vView = m_Camera.getView();											/** 设置摄像机 */
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
	/*reinterpret_cast将数据从一种类型的转换为另一种类型。
	所谓“通常为操作数的位模式提供较低层
	的重新解释”也就是说将数据以二进制存
	在形式的重新解释*/
	My * example = new My(class_name);
	return reinterpret_cast<My *>(example);
}

My::My(const TCHAR * class_name) : DimensionWorld(class_name)
{
}