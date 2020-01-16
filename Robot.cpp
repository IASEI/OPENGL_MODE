//=========================================================================
/**
*  @file     robot.cpp
*
*  ��Ŀ������ OpenGL�任
*  �ļ�����:  ����ʵ���� 
*  ����ƽ̨�� Windows98/2000/NT/XP
*  
*  ���ߣ�     WWBOSS
*  �����ʼ�:  wwboss123@gmail.com
*  �������ڣ� 2006-09-13	
*  �޸����ڣ� 2006-10-10
*
*  ����������������������¼����麯��
*																								
*	virtual bool Init();														
*		ִ�����еĳ�ʼ������������ɹ���������true							
*																			
*	virtual void Uninit();													
*		ִ�����е�ж�ع���										
*																			
*	virtual void Update(DWORD milliseconds);										
*		ִ�����еĸ��²���������Ĳ���Ϊ���β���������ʱ�䣬�Ժ���Ϊ��λ
*																			
*	virtual void Draw();															
*		ִ�����еĻ��Ʋ���
*/
//=========================================================================

#include "Robot.h"											    /**< ����ͷ�ļ� */

#include "Compress\x64\include_pde\glew.h"
#include "Compress\x64\include_pde\freeglut.h"										


						


/** ����һ�������ʵ�� */
GLApplication * GLApplication::Create(const TCHAR * class_name)
{
	Robot * example = new Robot(class_name);
	return reinterpret_cast<GLApplication *>(example);
}


/** ���캯�� */
Robot::Robot(const TCHAR * class_name) : GLApplication(class_name)
{
  
}

/** ��ʼ��OpenGL */
bool Robot::Init()									
{
/** �û��Զ���ĳ�ʼ������ */
	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);						
	glClearDepth(1.0f);											
	glDepthFunc(GL_LEQUAL);										
	glEnable(GL_DEPTH_TEST);									
	glShadeModel(GL_SMOOTH);									
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);			
	ResizeDraw(true);											/**< �ı�OpenGL���ڴ�С��ֱ�ӵ�������ĺ��� */

	return true;												/**< �ɹ����� */
}

/** �û��Զ����ж�غ��� */
void Robot::Uninit()									
{
/** �û��Զ����ж�ع��� */
///......
///......
}

/** ������º��� */
void Robot::Update(DWORD milliseconds)						
{
	
     
}

/** ���������� */
void Robot::DrawCube(float xPos, float yPos, float zPos)
{
	glPushMatrix();
		glTranslatef(xPos, yPos, zPos);
		glBegin(GL_POLYGON);
			
		    /** ���� */
		    glVertex3f(0.0f, 0.0f, 0.0f);	 
			glVertex3f(0.0f, 0.0f, -1.0f);
			glVertex3f(-1.0f, 0.0f, -1.0f);
			glVertex3f(-1.0f, 0.0f, 0.0f);
			
            /** ǰ�� */
			glVertex3f(0.0f, 0.0f, 0.0f);	 
			glVertex3f(-1.0f, 0.0f, 0.0f);
			glVertex3f(-1.0f, -1.0f, 0.0f);
			glVertex3f(0.0f, -1.0f, 0.0f);
			
			/** ���� */
			glVertex3f(0.0f, 0.0f, 0.0f);	
			glVertex3f(0.0f, -1.0f, 0.0f);
			glVertex3f(0.0f, -1.0f, -1.0f);
			glVertex3f(0.0f, 0.0f, -1.0f);
			
			/** ����*/
			glVertex3f(-1.0f, 0.0f, 0.0f);	
			glVertex3f(-1.0f, 0.0f, -1.0f);
			glVertex3f(-1.0f, -1.0f, -1.0f);
			glVertex3f(-1.0f, -1.0f, 0.0f);
			
			/** ���� */
			glVertex3f(0.0f, 0.0f, 0.0f);	
			glVertex3f(0.0f, -1.0f, -1.0f);
			glVertex3f(-1.0f, -1.0f, -1.0f);
			glVertex3f(-1.0f, -1.0f, 0.0f);
				
			
			/** ���� */
			glVertex3f(0.0f, 0.0f, 0.0f);
			glVertex3f(-1.0f, 0.0f, -1.0f);
			glVertex3f(-1.0f, -1.0f, -1.0f);
			glVertex3f(0.0f, -1.0f, -1.0f);
		glEnd();
	glPopMatrix();
}

/** ����һ���ֱ� */
void Robot::DrawArm(float xPos, float yPos, float zPos)
{
	glPushMatrix();
	    glColor3f(1.0f, 0.0f, 0.0f);    /**< ��ɫ */	
		glTranslatef(xPos, yPos, zPos);
		glScalef(1.0f, 4.0f, 1.0f);	    /**< �ֱ���1x4x1�������� */
		DrawCube(0.0f, 0.0f, 0.0f);
	glPopMatrix();
}

/** ����ͷ�� */
void Robot::DrawHead(float xPos, float yPos, float zPos)
{
	glPushMatrix();
		glColor3f(1.0f, 1.0f, 1.0f);	/**< ��ɫ */
		glTranslatef(xPos, yPos, zPos);
		glScalef(2.0f, 2.0f, 2.0f);		/**<ͷ���� 2x2x2������ */
		DrawCube(0.0f, 0.0f, 0.0f);
	glPopMatrix();
}

/** ���ƻ����˵����� */ 
void Robot::DrawTorso(float xPos, float yPos, float zPos)
{
	glPushMatrix();
		glColor3f(0.0f, 0.0f, 1.0f);	 /**< ��ɫ */
		glTranslatef(xPos, yPos, zPos);
		glScalef(3.0f, 5.0f, 2.0f);	     /**< ������3x5x2�ĳ����� */
		DrawCube(0.0f, 0.0f, 0.0f);
	glPopMatrix();
}

/** ����һ���� */
void Robot::DrawLeg(float xPos, float yPos, float zPos)
{
	glPushMatrix();
		glColor3f(1.0f, 1.0f, 0.0f);	/**< ��ɫ */
		glTranslatef(xPos, yPos, zPos);
		glScalef(1.0f, 5.0f, 1.0f);		/**< ����1x5x1������ */
		DrawCube(0.0f, 0.0f, 0.0f);
	glPopMatrix();
}

/** ��ָ��λ�û��ƻ����� */
void Robot::DrawRobot(float xPos, float yPos, float zPos)
{
	static bool leg1 = true;		/**< �������ȵ�״̬��true��ǰ��flase��� */
	static bool leg2 = false;		
	
	static bool arm1 = true;
	static bool arm2 = false;

	glPushMatrix();	

		glTranslatef(xPos, yPos, zPos);	/**< ��λ */

	    ///���Ƹ�������
		DrawHead(1.0f, 2.0f, 0.0f);     /**< ����ͷ�� */		
		DrawTorso(1.5f, 0.0f, 0.0f);   /**< �������� */
		
		///���Ƹ첲
		glPushMatrix();
			///����첲������ǰ�˶���������Ƕȣ�����ݼ��Ƕ� 
			if (arm1)
				armAngle[0] = armAngle[0] + 0.1f;
			else
				armAngle[0] = armAngle[0] - 0.1f;

			///����첲�ﵽ�����Ƕ���ı���״̬
			if (armAngle[0] >= 15.0f)
					arm1 = false;
			if (armAngle[0] <= -15.0f)
					arm1 = true;

			///ƽ�Ʋ���ת����Ƹ첲
			glTranslatef(0.0f, -0.5f, 0.0f);
			glRotatef(armAngle[0], 1.0f, 0.0f, 0.0f);
			DrawArm(2.5f, 0.0f, -0.5f);
		glPopMatrix();

		///ͬ��arm0
		glPushMatrix();
			
			if (arm2)
				armAngle[1] = armAngle[1] + 0.1f;
			else
				armAngle[1] = armAngle[1] - 0.1f;

			
			if (armAngle[1] >= 15.0f)
					arm2 = false;
			if (armAngle[1] <= -15.0f)
					arm2 = true;

			
			glTranslatef(0.0f, -0.5f, 0.0f);
			glRotatef(armAngle[1], 1.0f, 0.0f, 0.0f);
			DrawArm(-1.5f, 0.0f, -0.5f);
		glPopMatrix();

		///�����Ȳ�
		glPushMatrix();					

			///�����������ǰ�˶���������Ƕȣ�����ݼ��Ƕ� 
			if (leg1)
				legAngle[0] = legAngle[0] + 0.1f;
			else
				legAngle[0] = legAngle[0] - 0.1f;

			///����ȴﵽ�����Ƕ���ı���״̬
			if (legAngle[0] >= 15.0f)
					leg1 = false;
			if (legAngle[0] <= -15.0f)
					leg1 = true;

			///ƽ�Ʋ���ת����Ƹ첲
			glTranslatef(0.0f, -0.5f, 0.0f);
			glRotatef(legAngle[0], 1.0f, 0.0f, 0.0f);
			DrawLeg(-0.5f, -5.0f, -0.5f);

		glPopMatrix();

		///ͬ��leg1
		glPushMatrix();

			if (leg2)
				legAngle[1] = legAngle[1] + 0.1f;
			else
				legAngle[1] = legAngle[1] - 0.1f;

			if (legAngle[1] >= 15.0f)
				leg2 = false;
			if (legAngle[1] <= -15.0f)
				leg2 = true;

			glTranslatef(0.0f, -0.5f, 0.0f);
			glRotatef(legAngle[1], 1.0f, 0.0f, 0.0f);
			DrawLeg(1.5f, -5.0f, -0.5f);

		glPopMatrix();
	glPopMatrix();
}

/** ���ƺ��� */
void Robot::Draw()											
{
/** �û��Զ���Ļ��ƹ��� */
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);			
	glLoadIdentity();											
	
	///����ģ�ͱ任�����ƻ�����
	glPushMatrix();
	  glTranslatef(0.0f, 0.0f, -30.0f);	
	  glRotatef(angle, 0.0f, 1.0f, 0.0f);
	  DrawRobot(0.0f, 0.0f, 0.0f);
    glPopMatrix();

	
	glFlush();													/**< ǿ��ִ�����е�OpenGL���� */
}
