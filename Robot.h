//=========================================================================
/**
*  @file      Robot.h
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

#ifndef __ROBOT_H__
#define __ROBOT_H__


#include "GLFrame.h"												/**< ���������Ŀ���� */

/** ��GL_Application������һ������ */
class Robot : GLApplication								
{
public:
	bool	Init();										   /**< ��ʼ��e */
	void	Uninit();									   /**< ж�� */
	void	Update(DWORD milliseconds);					   /**< ���� */
	void	Draw();										   /**< ���� */

	void    DrawRobot(float xPos, float yPos, float zPos); /**< ���ƻ����� */

private:
	void    DrawHead(float xPos,float yPos,float zPos);    /**< ����ͷ�� */
	void    DrawTorso(float xPos, float yPos, float zPos); /**< �������� */
	void    DrawLeg(float xPos, float yPos, float zPos);   /**< ������ */
	void    DrawArm(float xPos, float yPos, float zPos);   /**< ���Ƹ첲 */
   
	void    DrawCube(float xPos, float yPos, float zPos);  /**< ���������� */

private:
	friend class GLApplication;							  /**< ����Ϊ����һ����Ԫ�� */
	Robot(const TCHAR * class_name);						  /**< ���캯�� */

		
	float angle;            /**< ���������ӵ���ת�ĽǶ� */
	float legAngle[2];		/**< �ȵĵ�ǰ��ת�Ƕ� */
    float armAngle[2];      /**< �첲�ĵ�ǰ��ת�Ƕ� */

};


#endif	// __ROBOT_H__