#include "shared/gltools.h"   
#include "shared/math3d.h"
#include "shared/glframe.h"
#include <time.h>
#include<windows.h>
#include <iostream>
using namespace std;

// Rotation amounts
static GLfloat zPos = -50.0f;
static GLfloat xPos = 0.0f;
static GLfloat anglee= 5.0f;
GLfloat pro_up_down=29.0f;
GLFrame    frameCamera;float up=0;

#define TEXTURE_BRICK 0
#define TEXTURE_FLOOR   1
#define TEXTURE_CEILING 2
#define TEXTURE_DOOR 3
#define TEXTURE_BIAOQING 4
#define TEXTURE_BRICK2 5
#define TEXTURE_WINDOW 6
#define TEXTURE_BLACKBOARD 7
#define TEXTURE_STONE 8
#define TEXTURE_SPEAKERDESK 9
#define TEXTURE_STDESK 10
#define TEXTURE_COUNT 11
GLuint  textures[TEXTURE_COUNT];
const char *szTextureFiles[TEXTURE_COUNT] = { "brick.tga", "floor.tga", "ceiling.tga" ,"door.tga","pi.tga","brick2.tga","window.tga","blackboard.tga","stonesurface.tga","speakerdesk.tga","stdesk.tga"};
//#pragma comment(linker, "/NODEFAULTLIB:libc.lib")

/*******************************������������õĳ�������******************************************/

GLfloat light_position1[]={0,28,20,1.0};

GLfloat model_ambient[]={0.05f,0.05f,0.05f,1.0f};

GLfloat mat_specular[]={0.8,1.0,1.0,1.0};

GLfloat mat_shininess[]={5.0};

GLfloat mat_ambient[]={0.1,0.1,0.1,1};

GLfloat white_light[]={1.0,1.0,1.0,1.0};

GLfloat light[]={1.0,1.0,1.0,1};

GLfloat light_position0[]={0,28,50,1.0};

GLfloat	no_mat[]= {0.0f, 0.0f, 0.0f, 1.0f};		

GLfloat	mat_diffuse1[]= {0.1f, 0.5f, 0.8f, 1.0f};	

GLfloat	no_shininess[]= {0.0f};	

GLfloat sound[]={0.9,0.9,0.9,1};

GLint	WinWidth;
GLint	WinHeight;

GLUquadricObj *qobj;
int fantheta=0; // ����ת���Ƕ� 
BOOL FT = FALSE;//���ȿ���
BOOL REFT = FALSE;//���ȿ���
//.....................................ʱ���йر���...................................................//
GLfloat cx=30.0,cy=20.0,cz=-10.0,radius=2.5;
GLfloat hradius=1.0,mradius=1.5,sradius=2.0; 
GLfloat sangle,mangle,hangle;
GLuint second,miniter,hour;
char timebuffer[9]; 


void drawprojector()

{
glPushMatrix();
    glColor3f(1.0f,1.0f,1.0f);
	glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, textures[TEXTURE_BIAOQING]);
    glBegin(GL_QUADS);

	glNormal3f(0.0f, 0.0f, 1.0f); //���ڶ��巨������
	glTexCoord2f(0.0f, 1.0f);
	        glVertex3f(-2,30.0f,-9.45); 
	glTexCoord2f(1.0f, 1.0f);
	        glVertex3f(4+10*sqrt(2.0), 30.0f,-9.45); 
	glTexCoord2f(1.0f, 0.0f);
	        glVertex3f(4+10*sqrt(2.0), pro_up_down, -9.45); 
	glTexCoord2f(0.0f, 0.0f);
	        glVertex3f(-2, pro_up_down, -9.45);

	glEnd();

	glDisable(GL_TEXTURE_2D);

	glColor3f(0.0f,0.0f,0.0f);

	glLineWidth(4.0f);

	glBegin(GL_LINES);

	glVertex3f(9.0f,30.0f,10.0f);

	glVertex3f(9.0f,25.0f,10.0f);

	glEnd();



	glColor3f(0.0,0.0,0.0);

	glBegin(GL_LINE_LOOP);

	glVertex3f(-2,30.0f,-9.45); 

	glVertex3f(4+10*sqrt(2.0), 30.0f, -9.45); 

	glVertex3f(4+10*sqrt(2.0), pro_up_down, -9.45); 

	glVertex3f(-2, pro_up_down, -9.45);

	glEnd();

	glColor3f(0.5f,0.5f,0.5f);

	glPushMatrix();

	glTranslatef(9.0f,24.0f,10);

	glScalef(4.0f,2.0f,2.0f);

	glutSolidCube(1.0f);

	glPopMatrix();

glPopMatrix();


}
void projectup()
{

	pro_up_down+=1.0f;

	if(pro_up_down>=28.0f)

		pro_up_down=28.0f;

     glutPostRedisplay();



}
void projectdown()
{

	pro_up_down+=-1.0f;

	if(pro_up_down<=10.0f)

		pro_up_down=10.0f;

     glutPostRedisplay();

}

void drawsound(){

			//��������

			glColor3f(0.0f,0.0f,0.0f);

			glPushMatrix();

			glTranslatef(-37.5,26.25f,13);

		    glScalef(1.0f,1.5f,1.0f);

	        glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,sound);

		    glutSolidCube(1.5f);

			glPopMatrix();

			glPushMatrix();

			glTranslatef(37.5,26.25f,13);

		    glScalef(1.0f,1.5f,1.0f);

	        glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,sound);

		    glutSolidCube(1.5f);

			glPopMatrix();

}

void mydesk()  //���Ӻ�����ģ�ͽ������������
{

GLfloat desk[]={1,0.9647,0.56078};
	float zp =20;
for(int i = 0;i<2;i++){
	float xp = i*30;
glPushMatrix();	
  glTranslatef(-30.0f+xp,0.0f,-20);

	//glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  //glEnable(GL_DEPTH_TEST);
 // glDisable(GL_TEXTURE_2D);
  	glBindTexture(GL_TEXTURE_2D, textures[TEXTURE_SPEAKERDESK]);
	glEnable(GL_TEXTURE_2D);
//������һ
	glPushMatrix();
	glColor3f(0.75,0.75,0.75);
	glTranslatef(8, 2, 45);
	glScalef(1, 7.5, 1);
	glutSolidCube(0.5);
	glPopMatrix();
//	������һ
	glPushMatrix();
	glColor3f(0.75,0.75,0.75);
	glTranslatef(12.2, 2, 45);
	glScalef(1, 7.5, 1);
	glutSolidCube(0.5);
	glPopMatrix();
//�������
	glPushMatrix();
	glColor3f(0.75,0.75,0.75);
	glTranslatef(8, 2, 45+4);
	glScalef(1, 7.5, 1);
	glutSolidCube(0.5);
	glPopMatrix();
//	�����Ҷ�
	glPushMatrix();
	glColor3f(0.75,0.75,0.75);
	glTranslatef(12.2, 2, 45+4);
	glScalef(1, 7.5, 1);
	glutSolidCube(0.5);
	glPopMatrix();
//������
	glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, textures[TEXTURE_SPEAKERDESK]);
	glEnable(GL_TEXTURE_2D);
	glColor3f(0.25,0.25,0.25);
	glTranslatef(10, 4, 47);
	glScalef(10, 1, 8);
	glutSolidCube(0.5);
	glPopMatrix();


//������
glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, textures[TEXTURE_STDESK]);
	glEnable(GL_TEXTURE_2D);
	glTranslatef(10.0f,7.0f,40);
    glScalef(18.0f,0.3f,9.0f);
	glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,desk);
	glTexCoord2f(0.0f, 0.0f);
	glTexCoord2f(0.0f, 1.0f);
	glTexCoord2f(1.0f, 1.0f);
	glTexCoord2f(1.0f, 0.0f);
	glutSolidCube(1.0f);
glPopMatrix();
//��������
glPushMatrix();
     //glDisable(GL_TEXTURE_2D);
     glBegin(GL_QUADS);
	 glNormal3f(-1.0f, 0.0f, 0.0f); //���ڶ��巨������
	        glTexCoord2f(0.0f, 0.0f);
	        glVertex3f(3,7.0f,40-4.5);
			glTexCoord2f(0.0f, 1.0f);
	        glVertex3f(3, 7.0f, 49-4.5);
			glTexCoord2f(1.0f, 1.0f);
	        glVertex3f(3, 0, 49-4.5);
			glTexCoord2f(1.0f, 0.0f);
	        glVertex3f(3, 0, 41-4.5);
	glEnd();
	glBegin(GL_QUADS);
	glNormal3f(1.0f, 0.0f, 0.0f); //���ڶ��巨������
	        glTexCoord2f(0.0f, 0.0f);
	        glVertex3f(3+14,7.0f,40-4.5);
			  glTexCoord2f(0.0f, 1.0f);
	        glVertex3f(3+14, 7.0f, 49-4.5);
			  glTexCoord2f(1.0f, 1.0f);
	        glVertex3f(3+14, 0, 49-4.5);
			  glTexCoord2f(1.0f, 0.0f);
	        glVertex3f(3+14, 0, 41-4.5);
	glEnd();
glPopMatrix();
//******************************************************
glDisable(GL_TEXTURE_2D);
//������һ
  	glBindTexture(GL_TEXTURE_2D, textures[TEXTURE_SPEAKERDESK]);
	glEnable(GL_TEXTURE_2D);
	glPushMatrix();
	glColor3f(0.75,0.75,0.75);
	glTranslatef(8, 2, 45+zp);
	glScalef(1, 7.5, 1);
	glutSolidCube(0.5);
	glPopMatrix();
//	������һ
	glPushMatrix();
	glColor3f(0.75,0.75,0.75);
	glTranslatef(12.2, 2, 45+zp);
	glScalef(1, 7.5, 1);
	glutSolidCube(0.5);
	glPopMatrix();
//�������
	glPushMatrix();
	glColor3f(0.75,0.75,0.75);
	glTranslatef(8, 2, 45+4+zp);
	glScalef(1, 7.5, 1);
	glutSolidCube(0.5);
	glPopMatrix();
//	�����Ҷ�
	glPushMatrix();
	glColor3f(0.75,0.75,0.75);
	glTranslatef(12.2, 2, 45+4+zp);
	glScalef(1, 7.5, 1);
	glutSolidCube(0.5);
	glPopMatrix();
//����TOP��
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, textures[TEXTURE_SPEAKERDESK]);
	glEnable(GL_TEXTURE_2D);
	glColor3f(0.25,0.25,0.25);
	glTranslatef(10, 4, 47+zp);
	glScalef(10, 1, 8);
	glutSolidCube(0.5);
	glPopMatrix();

glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, textures[TEXTURE_STDESK]);
	glEnable(GL_TEXTURE_2D);
//	glColor3f(0.5f,0.5f,0.5f);
	glTranslatef(10.0f,7.0f,40+zp);
    glScalef(18.0f,0.3f,9.0f);
	glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,desk);
	glutSolidCube(1.0f);
glPopMatrix();

glPushMatrix();
     //glDisable(GL_TEXTURE_2D);
//	 glColor3f(1,0.9647,0.56078);
     glBegin(GL_QUADS);
	 glNormal3f(-1.0f, 0.0f, 0.0f); //���ڶ��巨������
	        glTexCoord2f(0.0f, 0.0f);
	        glVertex3f(3,7.0f,40-4.5+zp); 
			 glTexCoord2f(0.0f, 1.0f);
	        glVertex3f(3, 7.0f, 49-4.5+zp); 
			 glTexCoord2f(1.0f, 1.0f);
	        glVertex3f(3, 0, 49-4.5+zp); 
			 glTexCoord2f(1.0f, 0.0f);
	        glVertex3f(3, 0, 41-4.5+zp);
	glEnd();
	glBegin(GL_QUADS);
	glNormal3f(1.0f, 0.0f, 0.0f); //���ڶ��巨������
	        glTexCoord2f(0.0f, 0.0f);
	        glVertex3f(3+14,7.0f,40-4.5+zp); 
			 glTexCoord2f(0.0f, 1.0f);
	        glVertex3f(3+14, 7.0f, 49-4.5+zp); 
			 glTexCoord2f(1.0f, 1.0f);
	        glVertex3f(3+14, 0, 49-4.5+zp); 
			 glTexCoord2f(1.0f, 0.0f);
	        glVertex3f(3+14, 0, 41-4.5+zp);
	glEnd();
glPopMatrix();


glPopMatrix();
}
}  

void drawfans()
{

	GLuint m = 0;
	GLuint x = 0;

	for(;m<2;m++)
	{
		qobj = gluNewQuadric();

   //�ұ߷���
		glPushMatrix();
		glTranslatef(20.0,0.0,44.0-30*m);
		//����
		if(FT==TRUE) 
		{ 
			fantheta+=31;
			if(fantheta >=760) //����Ϊ760��360�����ùر�ʱ�򽥽�ֹͣЧ�����ã���Ȼ����ת��Ȧ��ͣ���ˡ�
			    {fantheta = 360;}//
		}

		if(FT == FALSE&&REFT==TRUE)
		{
		
			if(fantheta<-1)
			   {
				   fantheta= fantheta;
				   REFT=FALSE;//�������شӵ�һ�ж���ʼ����������߳�������
			   }
			else
			{
				fantheta-=20;
			    Sleep(100);
			}
		}
		glRotatef(fantheta,0,1,0); //������ת 


	//�����м�ı�Բ��
		glPushMatrix();
		glColor3f(0.7,0.7,0.7);
		glTranslatef(0.0,27.0,0.0);
		glScalef(1,0.3,1);
		gluSphere(qobj,2,20,20);
		glPopMatrix();

		//............������ת120�ȵ���Ҷ...............//
		glPushMatrix();//ѹ���ջ 
		glColor3f(0.7,0.7,0.7); 
		glTranslatef(0,27,0.0);//ƽ�Ʊ任 
		glScalef(1,0.05,1);//���ű任 
		glRotatef(120,0,1,0);//��y����ת120�� 
		gluCylinder(qobj,1,3,10,20,20);//����һ��Բ׶�� 
        glPopMatrix();//������ջ 

		//............���Ȳ�����ת����Ҷ.................// 
        glPushMatrix();//ѹ���ջ 
		glColor3f(0.7,0.7,0.7); 
		glTranslatef(0,27,0.0);//ƽ�Ʊ任 
		glScalef(1,0.05,1);//���ű任 
		gluCylinder(qobj,1,3,10,20,20);//����һ��Բ׶�� 
		glPopMatrix();//������ջ

		//.............������ת240�ȵ���Ҷ...............// 
		glPushMatrix();//ѹ���ջ 
		glColor3f(0.7,0.7,0.7); 
        glTranslatef(0,27,0.0);//ƽ�Ʊ任 
		glScalef(1,0.05,1);//���ű任 
		glRotatef(240,0,1,0);//��y����ת240�� 
		gluCylinder(qobj,1,3,10,20,20);//����һ��Բ׶�� 
		glPopMatrix();//������ջ 

	
		//.............���ȵĸ�...........................//
		glPushMatrix();//ѹ���ջ 
		glTranslatef(0,33,0.0);//ƽ�Ʊ任 
		glRotatef(90,1,0,0);//���ű任 
		gluCylinder(qobj,0.5,0.5,6,10,10);//����һ��Բ���� 
		glPopMatrix();//������ջ 
    glPopMatrix();//������ջ 


	glPushMatrix();
		glTranslatef(-20.0,0.0,44.0-30*m);
		//����
		if(FT==TRUE) 
		{ 
			fantheta+=31;
			if(fantheta >=760) //����Ϊ760��360�����ùر�ʱ�򽥽�ֹͣЧ�����ã���Ȼ����ת��Ȧ��ͣ���ˡ�
			    {fantheta = 360;}//
		}

		if(FT == FALSE&&REFT==TRUE)
		{
		
			if(fantheta<-1)
			   {
				   fantheta= fantheta;
				   REFT=FALSE;//�������شӵ�һ�ж���ʼ����������߳�������
			   }
			else
			{
				fantheta-=10;
			    Sleep(40);
			}
		}
		glRotatef(fantheta,0,1,0); //������ת 



	//�����м�ı�Բ��
		glPushMatrix();
		glColor3f(0.7,0.7,0.7);
		glTranslatef(0.0,27.0,0.0);
		glScalef(1,0.3,1);
		gluSphere(qobj,2,20,20);
		//glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,light_Diffuse);
		glPopMatrix();

		//............������ת120�ȵ���Ҷ...............//
		glPushMatrix();//ѹ���ջ 
		glColor3f(0.7,0.7,0.7); 
		glTranslatef(0,27,0.0);//ƽ�Ʊ任 
		glScalef(1,0.05,1);//���ű任 
		glRotatef(120,0,1,0);//��y����ת120�� 
		gluCylinder(qobj,1,3,10,20,20);//����һ������Բ�뾶Ϊ1������Բ�뾶Ϊ2����Ϊ10��Բ׶�� 
		//glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,light_Diffuse);//������ʹ��� 
        glPopMatrix();//������ջ 

		//............���Ȳ�����ת����Ҷ.................// 
        glPushMatrix();//ѹ���ջ 
		glColor3f(0.7,0.7,0.7); 
		glTranslatef(0,27,0.0);//ƽ�Ʊ任 
		glScalef(1,0.05,1);//���ű任 
		gluCylinder(qobj,1,3,10,20,20);//����һ������Բ�뾶Ϊ1������Բ�뾶Ϊ3����Ϊ10��Բ׶�� 
		//glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,light_Diffuse);//������ʹ��� 
		glPopMatrix();//������ջ

		//.............������ת240�ȵ���Ҷ...............// 
		glPushMatrix();//ѹ���ջ 
		glColor3f(0.7,0.7,0.7); 
        glTranslatef(0,27,0.0);//ƽ�Ʊ任 
		glScalef(1,0.05,1);//���ű任 
		glRotatef(240,0,1,0);//��y����ת240�� 
		gluCylinder(qobj,1,3,10,20,20);//����һ������Բ�뾶Ϊ1������Բ�뾶Ϊ3����Ϊ10��Բ׶�� 
		//glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,light_Diffuse);//������ʹ��� 
		glPopMatrix();//������ջ 

		//.............���ȵĸ�...........................//
		glPushMatrix();//ѹ���ջ 
		glTranslatef(0,33,0.0);//ƽ�Ʊ任 
		glRotatef(90,1,0,0);//���ű任 
		gluCylinder(qobj,0.5,0.5,6,10,10);//����һ���뾶Ϊ0.5����Ϊ13��Բ���� 
		glPopMatrix();//������ջ 
    glPopMatrix();//������ջ 


	}

	   glutPostRedisplay();
	   glDisable(GL_TEXTURE_2D);
}

void drawclock()
{
	//........................................ʱ��..........................................................//
_strtime(timebuffer);//ȡϵͳʱ�䵽timebuffer������ 
hour=((int)timebuffer[0]-48)*10+((int)timebuffer[1]-48);//��timebuffer�����еõ�Сʱ��ֵ 
miniter=((int)timebuffer[3]-48)*10+((int)timebuffer[4]-48);//��timebuffer�����еõ����ӵ�ֵ 
second=((int)timebuffer[6]-48)*10+((int)timebuffer[7]-48);//��timebuffer�����еõ����ӵ�ֵ 
sangle=(float)(3.1415/2-(float)second*2*3.1415/60);//��������߹��ĽǶ� 
mangle=(float)3.1415/2-(float)(miniter+(float)second/60)/60*2*3.1415;//��÷����߹��ĽǶ� 
hangle=(float)3.1415/2-(float)(hour+(float)(miniter+(float)second/60)/60)*2*3.1415/12;//���ʱ���߹��ĽǶ� 

//..............�����ϵ�ʱ�̵�............................// 
int array[13][2];//12�����
float angle1;
angle1=2*3.1415/12;//��Բ�ֳܷ�12�� 

for(int w=0;w<12;w++)
{
	array[w][0]=cx+radius*cos(w*angle1);//���x������ 
	array[w][1]=cy+radius*sin(w*angle1);//���y������ 
	glPointSize(2);//���Ƶ� 
glBegin(GL_POINTS);//�ƶ���Ĵ�С 
glVertex3f(array[w][0]+0.4,array[w][1]+0.4,cz);//ȷ�����λ�� 
glEnd(); 
} 


//.....................ʱ�ӵ�����...........................// 
	glColor3f(1.0,1.0,1.0); 
	glLineWidth(2.0f);
	glBegin(GL_LINES); 
	glVertex3f(cx-3.5,cy-3,cz); 
	glVertex3f(cx+3.5,cy-3,cz); 
	glVertex3f(cx+3.5,cy+3,cz); 
	glVertex3f(cx-3.5,cy+3,cz); 
	glEnd(); 

glPointSize(1.5);//�ƶ���Ĵ�С 
//....................����..................................// 
float harr1[2]; 
harr1[0]=cx+sradius*cos(sangle);//���x������ 
harr1[1]=cy+sradius*sin(sangle);//���y������ 
glBegin(GL_LINES);//�����߶� 
glVertex3f(harr1[0],harr1[1],cz);//�߶��յ� 
glVertex3f(cx,cy,cz);//�߶���� 
glEnd(); 


//.....................����..................................// 
float harr2[2]; 
harr2[0]=cx+mradius*cos(mangle);//���x������ 
harr2[1]=cy+mradius*sin(mangle);//���y������ 
glBegin(GL_LINES);//�����߶� 
glVertex3f(harr2[0],harr2[1],cz);//�߶��յ� 
glVertex3f(cx,cy,cz);//�߶���� 
glEnd(); 


//......................ʱ��..................................// 
float harr3[2]; 
harr3[0]=cx+hradius*cos(hangle);//���x������ 
harr3[1]=cy+hradius*sin(hangle);//���y������ 
glBegin(GL_LINES);//�����߶� 
glVertex3f(harr3[0],harr3[1],cz);//�߶��յ� 
glVertex3f(cx,cy,cz);//�߶���� 
glEnd(); 

}




// Change texture filter for each texture object
void ProcessMenu(int value)
	{

        switch(value)
            {
            case 0:
                FT = true;REFT = true;
                break;
                
            case 1:
               FT = false;REFT = false;
                break;
                
            case 2:
                glEnable(GL_LIGHT1);
                break;
            
            case 3:
                glDisable(GL_LIGHT1);
                break;
            
            case 4:
				gltWriteTGA("ScreenShot.tga");for(int i =0;i<4;i++){printf("\n\n*****************������ͼ�ɹ�,ͼƬ��ScreenShot.tga���Ѿ������ڳ����ļ�����******************\n");}
				break;
            default:
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
                break;
            
        }
        
    // Trigger Redraw
	  glutSwapBuffers();
	glutPostRedisplay();
	}


// This function does any needed initialization on the rendering context.  Here it sets up and initializes the texture objects. 
void SetupRC()
    {
   GLbyte *pBytes;
    GLint iWidth, iHeight, iComponents;
    GLenum eFormat;
    GLint iLoop;
    
	// Black background
	glClearColor(0.0f, 0.0f, 0.0f,1.0f);

    // Textures applied as decals, no lighting or coloring effects
	glEnable(GL_TEXTURE_2D);
	//glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    // Load textures
    glGenTextures(TEXTURE_COUNT, textures);
    for(iLoop = 0; iLoop < TEXTURE_COUNT; iLoop++)
        {
        // Bind to next texture object
        glBindTexture(GL_TEXTURE_2D, textures[iLoop]);
        
        // Load texture, set filter and wrap modes
        pBytes = gltLoadTGA(szTextureFiles[iLoop],&iWidth, &iHeight,
                              &iComponents, &eFormat);

        // Load texture, set filter and wrap modes
        gluBuild2DMipmaps(GL_TEXTURE_2D, iComponents, iWidth, iHeight, eFormat, GL_UNSIGNED_BYTE, pBytes);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        
        // Don't need original texture data any more
        free(pBytes);
        }
    }
    

// Shutdown the rendering context. Just deletes thetexture objects
void ShutdownRC(void)
    {
    glDeleteTextures(TEXTURE_COUNT, textures);
    }
    

// Respond to arrow keys, move the viewpoint back and forth
void SpecialKeys2(int key, int x, int y)
    {

    if(key == GLUT_KEY_UP&&up<=23)
		{
            frameCamera.MoveUp(1.0f);//����
			up=up+1;
	}
    if(key == GLUT_KEY_DOWN&&up>=0)
		{

             frameCamera.MoveUp(-1.0f);//�½�
			 up=up-1;
    	}
    if(key == GLUT_KEY_LEFT)
        frameCamera.RotateLocalY(0.1);//����ת
      
    if(key == GLUT_KEY_RIGHT)
        frameCamera.RotateLocalY(-0.1);//����ת

	if(key == GLUT_KEY_F1)
		//anglee += 5.0f;
		frameCamera.RotateLocalX(0.1);

	if(key == GLUT_KEY_F2)
		//anglee -= 5.0f;
		frameCamera.RotateLocalX(-0.1);

	if(key == GLUT_KEY_F4)
		projectup(); 

	if(key == GLUT_KEY_F3)
		projectdown();

	if(key == GLUT_KEY_F5)
	{
		 FT = TRUE;
		 REFT = TRUE;
	}

	if(key == GLUT_KEY_F6)
	{
		 FT = FALSE;
		// REFT = FALSE;
	}

                       
    // Refresh the Window
    glutPostRedisplay();
    }

void keyboard2(unsigned char key,int x,int y){
   switch(key){
    case'w':
		zPos += 1.0f; glutPostRedisplay();
		if(zPos == 8.0f)
			 zPos = 6;
		break;
	case's':
		zPos -=1.0f; glutPostRedisplay();
		if(zPos == -61.0f)
			 zPos = -60;
		break;
	case'a':
		xPos += 1.0f; glutPostRedisplay();
		if(xPos == 40.0f)
			 xPos = 36;
		break;

	case'd':
		xPos -= 1.0f; glutPostRedisplay();
		if(xPos == -40.0f)
			 xPos = -36;
		break;

   }
}

// Change viewing volume and viewport.  Called when window is resized
void ChangeSize(int w, int h)
    {
    GLfloat fAspect;

    // Prevent a divide by zero
    if(h == 0)
        h = 1;

    // Set Viewport to window dimensions
    glViewport(0, 0, w, h);

    fAspect = (GLfloat)w/(GLfloat)h;
	 
    // Reset coordinate system
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // Produce the perspective projection
	gluPerspective(90.0f,fAspect,1,120);


    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    }

// Called to draw scene
void RenderScene(void)
    {	
		//���ò�����ز���

	glMaterialfv(GL_FRONT, GL_AMBIENT, no_mat);

	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse1);

	glMaterialfv(GL_FRONT, GL_SPECULAR, no_mat);

	glMaterialfv(GL_FRONT, GL_SHININESS, no_shininess);

	glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);   

    GLfloat z;
    
    // Clear the window with current clearing color
   // glClear(GL_COLOR_BUFFER_BIT);
	glClear( GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);

glPushMatrix();
	        frameCamera.ApplyCameraTransform();

    // Save the matrix state and do the rotations
    glPushMatrix();
        // Move object back and do in place rotation


        glTranslatef(xPos, 0.0f, zPos);
		glRotatef(anglee, 1.0f, 0.0f, 0.0f);
    

        for(z = 70.0f; z >= 0.0f; z -= 10)
        {
		// Floor
        glBindTexture(GL_TEXTURE_2D, textures[TEXTURE_FLOOR]); 
        glBegin(GL_QUADS);
		glNormal3f(0.0f, 1.0f, 0.0f); //���ڶ��巨������
            glTexCoord2f(0.0f, 0.0f);
            glVertex3f(-40.0f, 0.0f, z);

			glTexCoord2f(1.0f, 0.0f);
			glVertex3f(40.0f, 0.0f, z);

			glTexCoord2f(1.0f, 1.0f);
			glVertex3f(40.0f, 0.0f, z - 10.0f);

			glTexCoord2f(0.0f, 1.0f);
			glVertex3f(-40.0f, 0.0f, z - 10.0f);
		glEnd();

		// Ceiling
	 glBindTexture(GL_TEXTURE_2D, textures[TEXTURE_BRICK2]);
        glBegin(GL_QUADS);
		glNormal3f(0.0f, -1.0f, 0.0f); //���ڶ��巨������
            glTexCoord2f(0.0f, 0.0f);
            glVertex3f(-40.0f, 30.0f, z);

			glTexCoord2f(1.0f, 0.0f);
			glVertex3f(40.0f, 30.0f, z);

			glTexCoord2f(1.0f, 1.0f);
			glVertex3f(40.0f, 30.0f, z - 10.0f);

			glTexCoord2f(0.0f, 1.0f);
			glVertex3f(-40.0f, 30.0f, z - 10.0f);
		glEnd();


// ǰ���ǽ
	glBindTexture(GL_TEXTURE_2D, textures[TEXTURE_BRICK]);
	//glEnable( GL_COLOR_MATERIAL );
	glEnable(GL_TEXTURE_2D);
	glNormal3f(0.0f, 0.0f, 1.0f); //���ڶ��巨������
		glBegin(GL_QUADS);
		glColor3f(1.0f,1.0f,1.0f);
			glTexCoord2f(0.0f, 0.0f);
			glVertex3f(-40.0f, 0.0f, -10.5);

			glTexCoord2f(1.0f, 0.0f);
			glVertex3f(40.0f, 0.0f,-10.5);

			glTexCoord2f(1.0f, 1.0f);
			glVertex3f(40.0f, 30.0f,-10.5);

			glTexCoord2f(0.0f, 1.0f);
			glVertex3f(-40.0f, 30.0f,-10.5);
		glEnd();
		
		// Left Wall
	glBindTexture(GL_TEXTURE_2D, textures[TEXTURE_BRICK2]);
		
		glBegin(GL_QUADS);
		glNormal3f(1.0f, 0.0f, 0.0f); //���ڶ��巨������
			glTexCoord2f(0.0f, 0.0f);
			glVertex3f(-40.0f, 0.0f, z);

			glTexCoord2f(1.0f, 0.0f);
			glVertex3f(-40.0f, 0.0f, z - 10.0f);

			glTexCoord2f(1.0f, 1.0f);
			glVertex3f(-40.0f, 30.0f, z - 10.0f);

			glTexCoord2f(0.0f, 1.0f);
			glVertex3f(-40.0f, 30.0f, z);
		glEnd();

		glDisable(GL_TEXTURE_2D);

		glEnable(GL_TEXTURE_2D);
		// Right Wall
		glBindTexture(GL_TEXTURE_2D, textures[TEXTURE_BRICK2]);
		glBegin(GL_QUADS);
		glNormal3f(-1.0f, 0.0f, 0.0f); //���ڶ��巨������
			glTexCoord2f(0.0f, 1.0f);
			glVertex3f(40.0f, 30.0f, z);

			glTexCoord2f(1.0f, 1.0f);
			glVertex3f(40.0f, 30.0f, z - 10.0f);

			glTexCoord2f(1.0f, 0.0f);
			glVertex3f(40.0f, 0.0f, z - 10.0f);

			glTexCoord2f(0.0f, 0.0f);
			glVertex3f(40.0f,0.0f, z);
		glEnd();

		}

//���ƺ��ǽ*******************************************************************************
	
		glEnable(GL_TEXTURE_2D);
	    glBindTexture(GL_TEXTURE_2D, textures[TEXTURE_BRICK]);
        glColor3f(1.0f,1.0f,1.0f);

        glBegin(GL_QUADS);

        glNormal3f(0.0f, 0.0f, -1.0f); //���ڶ��巨������

        glTexCoord2f(0.0f, 0.0f);

		glVertex3f(-40.0f,0.0f, 60.0f); 

		glTexCoord2f(0.0f, 1.0f);

		glVertex3f(-40.0f, 30.0f, 60.0f); 

		glTexCoord2f(1.0f, 1.0f);

		glVertex3f(40.0f, 30.0f, 60.0f); 

		glTexCoord2f(1.0f, 0.0f);

		glVertex3f(40.0f, 0.0f, 60.0f);

		glEnd();
//*****************************************************************************************


		glDisable(GL_TEXTURE_2D);

		// Left Wall's Windows
        glEnable(GL_TEXTURE_2D);
	    glBindTexture(GL_TEXTURE_2D, textures[TEXTURE_WINDOW]);

        glBegin(GL_QUADS);

        glNormal3f(-1.0, 0.0f, 0.0f);	                  //���ڶ��巨������

        glTexCoord2f(1.0f, 0.0f);glVertex3f(-39.5, 10, 8); 

		glTexCoord2f(1.0f, 1.0f);glVertex3f(-39.5, 20, 8); 

		glTexCoord2f(0.0f, 1.0f);glVertex3f(-39.5, 20, -2); 

		glTexCoord2f(0.0f, 0.0f);glVertex3f(-39.5, 10, -2);

		glEnd();
		glBegin(GL_QUADS);
		//glBindTexture(GL_TEXTURE_2D, textures[TEXTURE_BRICK2]);
        glNormal3f(-1.0, 0.0f, 0.0f);	                  //���ڶ��巨������

        glTexCoord2f(1.0f, 0.0f);glVertex3f(-39.5, 10, 30); 

		glTexCoord2f(1.0f, 1.0f);glVertex3f(-39.5, 20, 30); 

		glTexCoord2f(0.0f, 1.0f);glVertex3f(-39.5, 20, 20); 

		glTexCoord2f(0.0f, 0.0f);glVertex3f(-39.5, 10, 20);

		glEnd();

		// Right Wall's Windows

        glBegin(GL_QUADS);

        glNormal3f(-1.0, 0.0f, 0.0f);	                  //���ڶ��巨������

        glTexCoord2f(1.0f, 0.0f);glVertex3f(39.5, 10, 8); 

		glTexCoord2f(1.0f, 1.0f);glVertex3f(39.5, 20, 8); 

		glTexCoord2f(0.0f, 1.0f);glVertex3f(39.5, 20, -2); 

		glTexCoord2f(0.0f, 0.0f);glVertex3f(39.5, 10, -2);

		glEnd();


	//ǰ��
			glBindTexture(GL_TEXTURE_2D, textures[TEXTURE_DOOR]);

			glEnable(GL_TEXTURE_2D);

			glBegin(GL_QUADS);

			glNormal3f(0.0f, 1.0f, 0.0f); //���ڶ��巨������

			glTexCoord2f(0.0f, 0.0f);glVertex3f(40-0.1, 0, 20); 

			glTexCoord2f(0.0f, 1.0f);glVertex3f(40-0.1, 18, 20); 

			glTexCoord2f(1.0f, 1.0f);glVertex3f(40-0.1,  18, 30); 

			glTexCoord2f(1.0f, 0.0f);glVertex3f(40-0.1,  0, 30);

			glEnd();

			
//���ƽ�������ʯ��ǰ������
	glDisable(GL_TEXTURE_2D);
		//glEnable(GL_TEXTURE_2D);
		//glBindTexture(GL_TEXTURE_2D, textures[TEXTURE_STONE]);
		for(int i=0;i<=3;i++)

		{

			glColor3f(1.0f,1.0f,1.0f);

			//ʯ���ϱ���

			glBegin(GL_QUADS);

			glNormal3f(0.0f, -1.0f, 0.0f); //���ڶ��巨������

			glTexCoord2f(0.0f, 0.0f);glVertex3f(-40.0,30.0f, -8.0f+22*i); 

			glTexCoord2f(1.0f, 0.0f);glVertex3f(-40.0, 30.0f, -10.0f+22*i); 

			glTexCoord2f(1.0f, 1.0f);glVertex3f(-38.0, 30.0f, -10.0f+22*i); 

			glTexCoord2f(0.0f, 1.0f);glVertex3f(-38.0f, 30.0f, -8.0f+22*i);

			glEnd();

			//ʯ��ǰ����

			glBegin(GL_QUADS);

			glNormal3f(0.0f, 0.0f, 1.0f); //���ڶ��巨������

			glTexCoord2f(0.0f, 0.0f);glVertex3f(-40.0,0.0f, -8.0f+22*i); 

			glTexCoord2f(0.0f, 1.0f);glVertex3f(-40.0, 30.0f, -8.0f+22*i); 

			glTexCoord2f(1.0f, 1.0f);glVertex3f(-38.0, 30.0f, -8.0f+22*i); 

			glTexCoord2f(1.0f, 0.0f);glVertex3f(-38.0, 0.0f, -8.0f+22*i);

			glEnd();

			//ʯ�������

			glBegin(GL_QUADS);

			glNormal3f(0.0f, 0.0f, -1.0f); //���ڶ��巨������

			glTexCoord2f(0.0f, 0.0f);glVertex3f(-40.0,0.0f, -10.0f+22*i); 

			glTexCoord2f(0.0f, 1.0f);glVertex3f(-40.0, 30.0f, -10.0f+22*i); 

			glTexCoord2f(1.0f, 1.0f);glVertex3f(-38.0, 30.0f, -10.0f+22*i); 

			glTexCoord2f(1.0f, 0.0f);glVertex3f(-38.0, 0.0f, -10.0f+22*i);

			glEnd();

			//ʯ���ұ���

			glBegin(GL_QUADS);

			glNormal3f(0.0f, 0.0f, -1.0f); //���ڶ��巨������

			glTexCoord2f(0.0f, 0.0f);glVertex3f(-38.0, 0.0f, -8.0f+22*i); 

			glTexCoord2f(0.0f, 1.0f);glVertex3f(-38.0, 30.0f, -8.0f+22*i); 

			glTexCoord2f(1.0f, 1.0f);glVertex3f(-38.0, 30.0f, -10.0f+22*i); 

			glTexCoord2f(1.0f, 0.0f);glVertex3f(-38.0, 0.0f, -10.0f+22*i);

			glEnd();
//*******************************************************�Ҳ�ʯ��*********************
		    glColor3f(1.0f,1.0f,1.0f);

			//ʯ���ϱ���

			glBegin(GL_QUADS);

			glNormal3f(0.0f, -1.0f, 0.0f); //���ڶ��巨������

			glTexCoord2f(0.0f, 0.0f);glVertex3f(-40.0+1*78,30.0f, -8.0f+22*i); 

			glTexCoord2f(1.0f, 0.0f);glVertex3f(-40.0+1*78, 30.0f, -10.0f+22*i); 

			glTexCoord2f(1.0f, 1.0f);glVertex3f(-38.0+1*78, 30.0f, -10.0f+22*i); 

			glTexCoord2f(0.0f, 1.0f);glVertex3f(-38.0f+1*78, 30.0f, -8.0f+22*i);

			glEnd();

			//ʯ��ǰ����

			glBegin(GL_QUADS);

			glNormal3f(0.0f, 0.0f, 1.0f); //���ڶ��巨������

			glTexCoord2f(0.0f, 0.0f);glVertex3f(-40.0+1*78,0.0f, -8.0f+22*i); 

			glTexCoord2f(0.0f, 1.0f);glVertex3f(-40.0+1*78, 30.0f, -8.0f+22*i); 

			glTexCoord2f(1.0f, 1.0f);glVertex3f(-38.0+1*78, 30.0f, -8.0f+22*i); 

			glTexCoord2f(1.0f, 0.0f);glVertex3f(-38.0+1*78, 0.0f, -8.0f+22*i);

			glEnd();

			//ʯ�������

			glBegin(GL_QUADS);

			glNormal3f(0.0f, 0.0f, -1.0f); //���ڶ��巨������

			glTexCoord2f(0.0f, 0.0f);glVertex3f(-40.0+1*78,0.0f, -10.0f+22*i); 

			glTexCoord2f(0.0f, 1.0f);glVertex3f(-40.0+1*78, 30.0f, -10.0f+22*i); 

			glTexCoord2f(1.0f, 1.0f);glVertex3f(-38.0+1*78, 30.0f, -10.0f+22*i); 

			glTexCoord2f(1.0f, 0.0f);glVertex3f(-38.0+1*78, 0.0f, -10.0f+22*i);

			glEnd();

			//ʯ���ұ���

			glBegin(GL_QUADS);

			glNormal3f(0.0f, 0.0f, -1.0f); //���ڶ��巨������

			glTexCoord2f(0.0f, 0.0f);glVertex3f(-38.0+1*76, 0.0f, -8.0f+22*i); 

			glTexCoord2f(0.0f, 1.0f);glVertex3f(-38.0+1*76, 30.0f, -8.0f+22*i); 

			glTexCoord2f(1.0f, 1.0f);glVertex3f(-38.0+1*76, 30.0f, -10.0f+22*i); 

			glTexCoord2f(1.0f, 0.0f);glVertex3f(-38.0+1*76, 0.0f, -10.0f+22*i);

			glEnd();

			}

			glDisable(GL_TEXTURE_2D);

			//���ƽ�̨
            //����̨����

	        glBindTexture(GL_TEXTURE_2D, textures[TEXTURE_SPEAKERDESK]);

			glEnable(GL_TEXTURE_2D);

			glBegin(GL_QUADS);

			glNormal3f(0.0f, 1.0f, 0.0f); //���ڶ��巨������

			glTexCoord2f(0.0f, 0.0f);glVertex3f(-17.5f, 1.5f, -1.0f); 

			glTexCoord2f(0.0f, 1.0f);glVertex3f(-17.5f, 9.5f, -1.0f); 

			glTexCoord2f(1.0f, 1.0f);glVertex3f(-3.5f,  9.5f, -1.0f); 

			glTexCoord2f(1.0f, 0.0f);glVertex3f(-3.5f,  1.5f, -1.0f);

			glEnd();

			glBegin(GL_QUADS);

			glNormal3f(0.0f, 1.0f, 0.0f); //���ڶ��巨������

			glTexCoord2f(0.0f, 0.0f);glVertex3f(-3.5f, 1.5f, -1.0f); 

			glTexCoord2f(0.0f, 1.0f);glVertex3f(-3.5f, 9.5f, -1.0f); 

			glTexCoord2f(1.0f, 1.0f);glVertex3f(-3.5f,  9.5f, -5.0f); 

			glTexCoord2f(1.0f, 0.0f);glVertex3f(-3.5f,  1.5f, -5.0f);

			glEnd();

			glBegin(GL_QUADS);

			glNormal3f(0.0f, 1.0f, 0.0f); //���ڶ��巨������

			glTexCoord2f(0.0f, 0.0f);glVertex3f(-17.5f, 1.5f, -1.0f); 

			glTexCoord2f(0.0f, 1.0f);glVertex3f(-17.5f, 9.5f, -1.0f); 

			glTexCoord2f(1.0f, 1.0f);glVertex3f(-17.5f,  9.5f, -5.0f); 

			glTexCoord2f(1.0f, 0.0f);glVertex3f(-17.5f,  1.5f, -5.0f);

			glEnd();

			glBegin(GL_QUADS);

			glNormal3f(0.0f, 1.0f, 0.0f); //���ڶ��巨������

			glTexCoord2f(0.0f, 0.0f);glVertex3f(-17.5f, 9.5f, -1.0f); 

			glTexCoord2f(0.0f, 1.0f);glVertex3f(-17.5f, 9.5f, -3.0f); 

			glTexCoord2f(1.0f, 1.0f);glVertex3f(-3.5f,  9.5f, -3.0f); 

			glTexCoord2f(1.0f, 0.0f);glVertex3f(-3.5f,  9.5f, -1.0f);

			glEnd();

			glDisable(GL_TEXTURE_2D);
//���ƺڰ�

			glEnable(GL_TEXTURE_2D);

			glBindTexture(GL_TEXTURE_2D, textures[TEXTURE_BLACKBOARD]);

			glBegin(GL_QUADS);

			glNormal3f(0.0f, 0.0f, 1.0f); //���ڶ��巨������

			glTexCoord2f(0.0f, 0.0f);glVertex3f(-20.0,8.0f, -9.5); 

			glTexCoord2f(0.0f, 1.0f);glVertex3f(-20.0, 23.0f, -9.5); 

			glTexCoord2f(1.0f, 1.0f);glVertex3f(22.0, 23.0f,-9.5); 

			glTexCoord2f(1.0f, 0.0f);glVertex3f(22.0, 8.0f, -9.5);

			glEnd();

			glDisable(GL_TEXTURE_2D);

			//���ڰ尼��
		    glEnable(GL_TEXTURE_2D);

			glBindTexture(GL_TEXTURE_2D, textures[TEXTURE_BLACKBOARD]);

            GLfloat blacklight[]={0.9,0.9,0.9,1};

			glColor3f(1.0f,1.0f,1.0f);

			glPushMatrix();

			glTranslatef(0,8,-9.5);

		    glScalef(50.0f,0.8,1.0f);

	        glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,blacklight);

		    glutSolidCube(1.0f);

			glPopMatrix();

			glDisable(GL_TEXTURE_2D);
	        //���ƽ���ǰ��һ��ߵز�������

           glEnable(GL_TEXTURE_2D);

		   glBindTexture(GL_TEXTURE_2D, textures[TEXTURE_SPEAKERDESK]);

			//������

			glBegin(GL_POLYGON);

			glNormal3f(0.0f, 1.0f, 0.0f); //���ڶ��巨������

			glTexCoord2f(0.0f, 0.0f);glVertex3f(-30.0f, 2.5f, 1.0f); //A

			glTexCoord2f(0.0f, 1.0f);glVertex3f(-30.0f, 2.5f, -9.5); //B

			glTexCoord2f(1.0f, 1.0f);glVertex3f(30.0f, 2.5f, -9.5); //C

            glTexCoord2f(0.0f, 0.0f);glVertex3f(30.0f, 2.5f, 1.0f); //D

			glTexCoord2f(0.0f, 0.0f);glVertex3f(20.0f, 2.5f, 8.0f); //E

        	glTexCoord2f(1.0f, 0.0f);glVertex3f(-20.0f,  2.5f, 8.0f);//F

			glEnd();

			//�����

			glBegin(GL_QUADS);

			glNormal3f(0.0f, 0.0f, 1.0f); //���ڶ��巨������

			glTexCoord2f(0.0f, 0.0f);glVertex3f(-30.0f, 0, 1.0f); 

			glTexCoord2f(0.0f, 1.0f);glVertex3f(-30.0f, 2.5f, 1.0f); 

			glTexCoord2f(1.0f, 1.0f);glVertex3f(-30.0f,  2.5f,-9.5); 

			glTexCoord2f(1.0f, 0.0f);glVertex3f(-30.0f,  0, -9.5);

			glEnd();

			//����б��

			glBegin(GL_QUADS);

			glNormal3f(0.0f, 0.0f, 1.0f); //���ڶ��巨������

			glTexCoord2f(0.0f, 0.0f);glVertex3f(-30.0f, 0, 1.0f); 

			glTexCoord2f(0.0f, 1.0f);glVertex3f(-30.0f, 2.5f, 1.0f); 

			glTexCoord2f(1.0f, 1.0f);glVertex3f(-20.0f,  2.5f, 8.0f); 

			glTexCoord2f(1.0f, 0.0f);glVertex3f(-20.0f,  0, 8.0f);

			glEnd();

			//����б��

			glBegin(GL_QUADS);

			glNormal3f(0.0f, 0.0f, 1.0f); //���ڶ��巨������

			glTexCoord2f(0.0f, 0.0f);glVertex3f(30.0f, 0, 1.0f); 

			glTexCoord2f(0.0f, 1.0f);glVertex3f(30.0f, 2.5f, 1.0f); 

			glTexCoord2f(1.0f, 1.0f);glVertex3f(20.0f,  2.5f, 8.0f); 

			glTexCoord2f(1.0f, 0.0f);glVertex3f(20.0f,  0, 8.0f);

			glEnd();


			//��ǰ��

			glBegin(GL_QUADS);

			glNormal3f(0.0f, 1.0f, 0.0f); //���ڶ��巨������

			glTexCoord2f(0.0f, 0.0f);glVertex3f(-20.0f, 0, 8.0f); 

			glTexCoord2f(0.0f, 1.0f);glVertex3f(-20.0f, 2.5f, 8.0f); 

			glTexCoord2f(1.0f, 1.0f);glVertex3f(20.0f,  2.5f, 8.0f); 

			glTexCoord2f(1.0f, 0.0f);glVertex3f(20.0f,  0, 8.0f);

			glEnd();

			//���ұ�

			glBegin(GL_QUADS);

			glNormal3f(0.0f, 1.0f, 0.0f); //���ڶ��巨������

			glTexCoord2f(0.0f, 0.0f);glVertex3f(30.0f, 0, 1.0f); 

			glTexCoord2f(0.0f, 1.0f);glVertex3f(30.0f, 2.5f, 1.0f); 

			glTexCoord2f(1.0f, 1.0f);glVertex3f(30.0f,  2.5f,-9.5); 

			glTexCoord2f(1.0f, 0.0f);glVertex3f(30.0f,  0,-9.5);

			glEnd();

			glDisable(GL_TEXTURE_2D);



//����ͶӰ��
			drawprojector();

//��������
			drawsound();

//���Ƶ����
			drawfans();
//����ʱ��
			drawclock();
//��������
	     	mydesk();








/***************************************************************************����********************************/
    glPushMatrix();
 //   glRotatef(angle,0,1,0);//С����������ת
 //   glTranslatef(0,-5,30);
	//draw_body();
 //   draw_head();
 //   draw_leftshoulder();
 //   draw_rightshoulder();
 //   draw_leftfoot();
 //   draw_rightfoot();
	    glPopMatrix();
/***************************************************************************����********************************/


    // Restore the matrix state

    glPopMatrix();
 glPopMatrix();


    glutSwapBuffers();
    }


void initial()//�ƹ��ʼ��

{

    glClearColor(0,0,0,0);

	glEnable(GL_TEXTURE_2D);

	glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_REPLACE);

	/*********************************************�Եƹ���г�ʼ��****************************************************/

    glLightModelfv(GL_LIGHT_MODEL_AMBIENT,model_ambient);

	glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER,GL_TRUE);

	glMaterialfv(GL_FRONT,GL_SPECULAR,mat_specular);

	glMaterialfv(GL_FRONT,GL_SHININESS,mat_shininess);



	glLightfv(GL_LIGHT0,GL_POSITION,light_position0);

	glLightfv(GL_LIGHT0,GL_AMBIENT,mat_ambient);

	glLightfv(GL_LIGHT0,GL_DIFFUSE,light);

	glLightfv(GL_LIGHT0,GL_SPECULAR,light);


	glLightfv(GL_LIGHT1,GL_POSITION,light_position1);

	glLightfv(GL_LIGHT1,GL_AMBIENT,mat_ambient);

	glLightfv(GL_LIGHT1,GL_DIFFUSE,white_light);

	glLightfv(GL_LIGHT1,GL_SPECULAR,white_light);

	glEnable(GL_LIGHTING);

	glEnable(GL_LIGHT0);	

	glEnable(GL_COLOR_MATERIAL);	



    /**********************************************************************************************/

	glShadeModel(GL_SMOOTH);				

	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);	//ָ��������ɫ����

	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);	//ָ�����϶Ծ����ķ���

	glEnable(GL_DEPTH_TEST);//	

}

void print()

{

	printf("**************************************************** \n");

	printf(" \n");

	printf("��ӭ����OpenGL������ά�ռ䣡 \n");

	printf("����Ϊ����˵����\n");

	printf("  �ϼ����¼��ֱ�����ӽ����Ϻ�����ƽ�� \n");

	printf("  ������Ҽ��ֱ���������Ӻ����һ��� \n");

	printf("  w,s,a,d���ֱ��ʾ��ǰ�������ң�����ƽ�ƣ�ע����̴�Сд��\n");

	printf("  F1��F2���ֱ�����ӽ����º�������ת \n");

	printf("  F3��F4���ֱ����ͶӰ�Ƿ��º����� \n");

	printf("  F5��F6���ֱ���Ƶ��ȵĿ��� \n");

	printf("  ����һ����Դ򿪹��ܲ˵�����ʹ��֮ǰ���ֹ��ܣ����������˽�ͼ���� \n");

	printf(" \n\n");

    printf("**************************************************** \n");



	printf(" \n\n\n\n");
	printf("                              *****************************************************\n");
	printf("************����Ҫ�ر��лһЩ ��OpenGL������İ桷������������򽲽��Լ�����һЩ���㰸��************************* \n");
	printf("*****************************************�����Ǵ��������ţ�������������******************************************* \n");
	printf("**************************************************�ر��л�ҵ�Ů����********************************************** \n");
	printf("*****************************************����������ʱ����Ҿ���Ĺ���********************************************* \n");
	printf("                              *****************************************************\n");

	printf(" \n");
	printf("                                                                          �����ˣ�������ýѧԺ  ��һ��  \n");
	printf("                                                                          2019.5.9 21:29  \n");



}

int main(int argc, char *argv[])
    {
    // Standard initialization stuff
  
    glEnable(GL_DEPTH_TEST);
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutCreateWindow("BIG HOMEWORK");
	initial();
   glutReshapeFunc(ChangeSize);

    glutSpecialFunc(SpecialKeys2);
	glutKeyboardFunc(keyboard2);
    glutDisplayFunc(RenderScene);
    
    // Add menu entries to change filter
    glutCreateMenu(ProcessMenu);
    glutAddMenuEntry("�򿪵���",0);
    glutAddMenuEntry("�رյ���",1);
    glutAddMenuEntry("���ҵ�",2);
    glutAddMenuEntry("�ر��ҵ�", 3);
	glutAddMenuEntry("������ͼ",4);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
    
	print();
    // Startup, loop, shutdown
    SetupRC();

    glutMainLoop();
    ShutdownRC();
    
    return 0;
    }