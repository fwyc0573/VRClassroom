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

/*******************************定义程序中所用的常数变量******************************************/

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
int fantheta=0; // 风扇转过角度 
BOOL FT = FALSE;//风扇开关
BOOL REFT = FALSE;//风扇开关
//.....................................时钟有关变量...................................................//
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

	glNormal3f(0.0f, 0.0f, 1.0f); //用于定义法线向量
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

			//绘制音响

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

void mydesk()  //桌子和椅子模型皆在这个函数中
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
//椅腿左一
	glPushMatrix();
	glColor3f(0.75,0.75,0.75);
	glTranslatef(8, 2, 45);
	glScalef(1, 7.5, 1);
	glutSolidCube(0.5);
	glPopMatrix();
//	椅腿右一
	glPushMatrix();
	glColor3f(0.75,0.75,0.75);
	glTranslatef(12.2, 2, 45);
	glScalef(1, 7.5, 1);
	glutSolidCube(0.5);
	glPopMatrix();
//椅腿左二
	glPushMatrix();
	glColor3f(0.75,0.75,0.75);
	glTranslatef(8, 2, 45+4);
	glScalef(1, 7.5, 1);
	glutSolidCube(0.5);
	glPopMatrix();
//	椅腿右二
	glPushMatrix();
	glColor3f(0.75,0.75,0.75);
	glTranslatef(12.2, 2, 45+4);
	glScalef(1, 7.5, 1);
	glutSolidCube(0.5);
	glPopMatrix();
//椅子面
	glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, textures[TEXTURE_SPEAKERDESK]);
	glEnable(GL_TEXTURE_2D);
	glColor3f(0.25,0.25,0.25);
	glTranslatef(10, 4, 47);
	glScalef(10, 1, 8);
	glutSolidCube(0.5);
	glPopMatrix();


//桌子面
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
//桌子两侧
glPushMatrix();
     //glDisable(GL_TEXTURE_2D);
     glBegin(GL_QUADS);
	 glNormal3f(-1.0f, 0.0f, 0.0f); //用于定义法线向量
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
	glNormal3f(1.0f, 0.0f, 0.0f); //用于定义法线向量
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
//椅腿左一
  	glBindTexture(GL_TEXTURE_2D, textures[TEXTURE_SPEAKERDESK]);
	glEnable(GL_TEXTURE_2D);
	glPushMatrix();
	glColor3f(0.75,0.75,0.75);
	glTranslatef(8, 2, 45+zp);
	glScalef(1, 7.5, 1);
	glutSolidCube(0.5);
	glPopMatrix();
//	椅腿右一
	glPushMatrix();
	glColor3f(0.75,0.75,0.75);
	glTranslatef(12.2, 2, 45+zp);
	glScalef(1, 7.5, 1);
	glutSolidCube(0.5);
	glPopMatrix();
//椅腿左二
	glPushMatrix();
	glColor3f(0.75,0.75,0.75);
	glTranslatef(8, 2, 45+4+zp);
	glScalef(1, 7.5, 1);
	glutSolidCube(0.5);
	glPopMatrix();
//	椅腿右二
	glPushMatrix();
	glColor3f(0.75,0.75,0.75);
	glTranslatef(12.2, 2, 45+4+zp);
	glScalef(1, 7.5, 1);
	glutSolidCube(0.5);
	glPopMatrix();
//椅子TOP面
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
	 glNormal3f(-1.0f, 0.0f, 0.0f); //用于定义法线向量
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
	glNormal3f(1.0f, 0.0f, 0.0f); //用于定义法线向量
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

   //右边风扇
		glPushMatrix();
		glTranslatef(20.0,0.0,44.0-30*m);
		//开关
		if(FT==TRUE) 
		{ 
			fantheta+=31;
			if(fantheta >=760) //设置为760和360可以让关闭时候渐进停止效果更好，不然渐进转半圈就停下了。
			    {fantheta = 360;}//
		}

		if(FT == FALSE&&REFT==TRUE)
		{
		
			if(fantheta<-1)
			   {
				   fantheta= fantheta;
				   REFT=FALSE;//修正开关从第一判定开始就跳过，提高程序性能
			   }
			else
			{
				fantheta-=20;
			    Sleep(100);
			}
		}
		glRotatef(fantheta,0,1,0); //风扇旋转 


	//风扇中间的扁圆形
		glPushMatrix();
		glColor3f(0.7,0.7,0.7);
		glTranslatef(0.0,27.0,0.0);
		glScalef(1,0.3,1);
		gluSphere(qobj,2,20,20);
		glPopMatrix();

		//............风扇旋转120度的扇叶...............//
		glPushMatrix();//压入堆栈 
		glColor3f(0.7,0.7,0.7); 
		glTranslatef(0,27,0.0);//平移变换 
		glScalef(1,0.05,1);//缩放变换 
		glRotatef(120,0,1,0);//绕y轴旋转120度 
		gluCylinder(qobj,1,3,10,20,20);//绘制一个圆锥体 
        glPopMatrix();//弹出堆栈 

		//............风扇不做旋转的扇叶.................// 
        glPushMatrix();//压入堆栈 
		glColor3f(0.7,0.7,0.7); 
		glTranslatef(0,27,0.0);//平移变换 
		glScalef(1,0.05,1);//缩放变换 
		gluCylinder(qobj,1,3,10,20,20);//绘制一个圆锥体 
		glPopMatrix();//弹出堆栈

		//.............风扇旋转240度的扇叶...............// 
		glPushMatrix();//压入堆栈 
		glColor3f(0.7,0.7,0.7); 
        glTranslatef(0,27,0.0);//平移变换 
		glScalef(1,0.05,1);//缩放变换 
		glRotatef(240,0,1,0);//绕y轴旋转240度 
		gluCylinder(qobj,1,3,10,20,20);//绘制一个圆锥体 
		glPopMatrix();//弹出堆栈 

	
		//.............风扇的杆...........................//
		glPushMatrix();//压入堆栈 
		glTranslatef(0,33,0.0);//平移变换 
		glRotatef(90,1,0,0);//缩放变换 
		gluCylinder(qobj,0.5,0.5,6,10,10);//绘制一个圆柱体 
		glPopMatrix();//弹出堆栈 
    glPopMatrix();//弹出堆栈 


	glPushMatrix();
		glTranslatef(-20.0,0.0,44.0-30*m);
		//开关
		if(FT==TRUE) 
		{ 
			fantheta+=31;
			if(fantheta >=760) //设置为760和360可以让关闭时候渐进停止效果更好，不然渐进转半圈就停下了。
			    {fantheta = 360;}//
		}

		if(FT == FALSE&&REFT==TRUE)
		{
		
			if(fantheta<-1)
			   {
				   fantheta= fantheta;
				   REFT=FALSE;//修正开关从第一判定开始就跳过，提高程序性能
			   }
			else
			{
				fantheta-=10;
			    Sleep(40);
			}
		}
		glRotatef(fantheta,0,1,0); //风扇旋转 



	//风扇中间的扁圆形
		glPushMatrix();
		glColor3f(0.7,0.7,0.7);
		glTranslatef(0.0,27.0,0.0);
		glScalef(1,0.3,1);
		gluSphere(qobj,2,20,20);
		//glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,light_Diffuse);
		glPopMatrix();

		//............风扇旋转120度的扇叶...............//
		glPushMatrix();//压入堆栈 
		glColor3f(0.7,0.7,0.7); 
		glTranslatef(0,27,0.0);//平移变换 
		glScalef(1,0.05,1);//缩放变换 
		glRotatef(120,0,1,0);//绕y轴旋转120度 
		gluCylinder(qobj,1,3,10,20,20);//绘制一个底面圆半径为1、顶面圆半径为2、高为10的圆锥体 
		//glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,light_Diffuse);//定义材质光照 
        glPopMatrix();//弹出堆栈 

		//............风扇不做旋转的扇叶.................// 
        glPushMatrix();//压入堆栈 
		glColor3f(0.7,0.7,0.7); 
		glTranslatef(0,27,0.0);//平移变换 
		glScalef(1,0.05,1);//缩放变换 
		gluCylinder(qobj,1,3,10,20,20);//绘制一个底面圆半径为1、顶面圆半径为3、高为10的圆锥体 
		//glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,light_Diffuse);//定义材质光照 
		glPopMatrix();//弹出堆栈

		//.............风扇旋转240度的扇叶...............// 
		glPushMatrix();//压入堆栈 
		glColor3f(0.7,0.7,0.7); 
        glTranslatef(0,27,0.0);//平移变换 
		glScalef(1,0.05,1);//缩放变换 
		glRotatef(240,0,1,0);//绕y轴旋转240度 
		gluCylinder(qobj,1,3,10,20,20);//绘制一个底面圆半径为1、顶面圆半径为3、高为10的圆锥体 
		//glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,light_Diffuse);//定义材质光照 
		glPopMatrix();//弹出堆栈 

		//.............风扇的杆...........................//
		glPushMatrix();//压入堆栈 
		glTranslatef(0,33,0.0);//平移变换 
		glRotatef(90,1,0,0);//缩放变换 
		gluCylinder(qobj,0.5,0.5,6,10,10);//绘制一个半径为0.5、高为13的圆柱体 
		glPopMatrix();//弹出堆栈 
    glPopMatrix();//弹出堆栈 


	}

	   glutPostRedisplay();
	   glDisable(GL_TEXTURE_2D);
}

void drawclock()
{
	//........................................时钟..........................................................//
_strtime(timebuffer);//取系统时间到timebuffer数组中 
hour=((int)timebuffer[0]-48)*10+((int)timebuffer[1]-48);//从timebuffer数组中得到小时的值 
miniter=((int)timebuffer[3]-48)*10+((int)timebuffer[4]-48);//从timebuffer数组中得到分钟的值 
second=((int)timebuffer[6]-48)*10+((int)timebuffer[7]-48);//从timebuffer数组中得到秒钟的值 
sangle=(float)(3.1415/2-(float)second*2*3.1415/60);//算得秒针走过的角度 
mangle=(float)3.1415/2-(float)(miniter+(float)second/60)/60*2*3.1415;//算得分针走过的角度 
hangle=(float)3.1415/2-(float)(hour+(float)(miniter+(float)second/60)/60)*2*3.1415/12;//算得时针走过的角度 

//..............钟面上的时刻点............................// 
int array[13][2];//12个大点
float angle1;
angle1=2*3.1415/12;//将圆周分成12份 

for(int w=0;w<12;w++)
{
	array[w][0]=cx+radius*cos(w*angle1);//求得x轴坐标 
	array[w][1]=cy+radius*sin(w*angle1);//求得y轴坐标 
	glPointSize(2);//绘制点 
glBegin(GL_POINTS);//制定点的大小 
glVertex3f(array[w][0]+0.4,array[w][1]+0.4,cz);//确定点的位置 
glEnd(); 
} 


//.....................时钟的轮廓...........................// 
	glColor3f(1.0,1.0,1.0); 
	glLineWidth(2.0f);
	glBegin(GL_LINES); 
	glVertex3f(cx-3.5,cy-3,cz); 
	glVertex3f(cx+3.5,cy-3,cz); 
	glVertex3f(cx+3.5,cy+3,cz); 
	glVertex3f(cx-3.5,cy+3,cz); 
	glEnd(); 

glPointSize(1.5);//制定点的大小 
//....................秒针..................................// 
float harr1[2]; 
harr1[0]=cx+sradius*cos(sangle);//求得x轴坐标 
harr1[1]=cy+sradius*sin(sangle);//求得y轴坐标 
glBegin(GL_LINES);//绘制线段 
glVertex3f(harr1[0],harr1[1],cz);//线段终点 
glVertex3f(cx,cy,cz);//线段起点 
glEnd(); 


//.....................分针..................................// 
float harr2[2]; 
harr2[0]=cx+mradius*cos(mangle);//求得x轴坐标 
harr2[1]=cy+mradius*sin(mangle);//求得y轴坐标 
glBegin(GL_LINES);//绘制线段 
glVertex3f(harr2[0],harr2[1],cz);//线段终点 
glVertex3f(cx,cy,cz);//线段起点 
glEnd(); 


//......................时针..................................// 
float harr3[2]; 
harr3[0]=cx+hradius*cos(hangle);//求得x轴坐标 
harr3[1]=cy+hradius*sin(hangle);//求得y轴坐标 
glBegin(GL_LINES);//绘制线段 
glVertex3f(harr3[0],harr3[1],cz);//线段终点 
glVertex3f(cx,cy,cz);//线段起点 
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
				gltWriteTGA("ScreenShot.tga");for(int i =0;i<4;i++){printf("\n\n*****************场景截图成功,图片“ScreenShot.tga”已经保存在程序文件夹中******************\n");}
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
            frameCamera.MoveUp(1.0f);//上升
			up=up+1;
	}
    if(key == GLUT_KEY_DOWN&&up>=0)
		{

             frameCamera.MoveUp(-1.0f);//下降
			 up=up-1;
    	}
    if(key == GLUT_KEY_LEFT)
        frameCamera.RotateLocalY(0.1);//左旋转
      
    if(key == GLUT_KEY_RIGHT)
        frameCamera.RotateLocalY(-0.1);//右旋转

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
		//设置材质相关参数

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
		glNormal3f(0.0f, 1.0f, 0.0f); //用于定义法线向量
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
		glNormal3f(0.0f, -1.0f, 0.0f); //用于定义法线向量
            glTexCoord2f(0.0f, 0.0f);
            glVertex3f(-40.0f, 30.0f, z);

			glTexCoord2f(1.0f, 0.0f);
			glVertex3f(40.0f, 30.0f, z);

			glTexCoord2f(1.0f, 1.0f);
			glVertex3f(40.0f, 30.0f, z - 10.0f);

			glTexCoord2f(0.0f, 1.0f);
			glVertex3f(-40.0f, 30.0f, z - 10.0f);
		glEnd();


// 前面的墙
	glBindTexture(GL_TEXTURE_2D, textures[TEXTURE_BRICK]);
	//glEnable( GL_COLOR_MATERIAL );
	glEnable(GL_TEXTURE_2D);
	glNormal3f(0.0f, 0.0f, 1.0f); //用于定义法线向量
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
		glNormal3f(1.0f, 0.0f, 0.0f); //用于定义法线向量
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
		glNormal3f(-1.0f, 0.0f, 0.0f); //用于定义法线向量
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

//绘制后边墙*******************************************************************************
	
		glEnable(GL_TEXTURE_2D);
	    glBindTexture(GL_TEXTURE_2D, textures[TEXTURE_BRICK]);
        glColor3f(1.0f,1.0f,1.0f);

        glBegin(GL_QUADS);

        glNormal3f(0.0f, 0.0f, -1.0f); //用于定义法线向量

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

        glNormal3f(-1.0, 0.0f, 0.0f);	                  //用于定义法线向量

        glTexCoord2f(1.0f, 0.0f);glVertex3f(-39.5, 10, 8); 

		glTexCoord2f(1.0f, 1.0f);glVertex3f(-39.5, 20, 8); 

		glTexCoord2f(0.0f, 1.0f);glVertex3f(-39.5, 20, -2); 

		glTexCoord2f(0.0f, 0.0f);glVertex3f(-39.5, 10, -2);

		glEnd();
		glBegin(GL_QUADS);
		//glBindTexture(GL_TEXTURE_2D, textures[TEXTURE_BRICK2]);
        glNormal3f(-1.0, 0.0f, 0.0f);	                  //用于定义法线向量

        glTexCoord2f(1.0f, 0.0f);glVertex3f(-39.5, 10, 30); 

		glTexCoord2f(1.0f, 1.0f);glVertex3f(-39.5, 20, 30); 

		glTexCoord2f(0.0f, 1.0f);glVertex3f(-39.5, 20, 20); 

		glTexCoord2f(0.0f, 0.0f);glVertex3f(-39.5, 10, 20);

		glEnd();

		// Right Wall's Windows

        glBegin(GL_QUADS);

        glNormal3f(-1.0, 0.0f, 0.0f);	                  //用于定义法线向量

        glTexCoord2f(1.0f, 0.0f);glVertex3f(39.5, 10, 8); 

		glTexCoord2f(1.0f, 1.0f);glVertex3f(39.5, 20, 8); 

		glTexCoord2f(0.0f, 1.0f);glVertex3f(39.5, 20, -2); 

		glTexCoord2f(0.0f, 0.0f);glVertex3f(39.5, 10, -2);

		glEnd();


	//前门
			glBindTexture(GL_TEXTURE_2D, textures[TEXTURE_DOOR]);

			glEnable(GL_TEXTURE_2D);

			glBegin(GL_QUADS);

			glNormal3f(0.0f, 1.0f, 0.0f); //用于定义法线向量

			glTexCoord2f(0.0f, 0.0f);glVertex3f(40-0.1, 0, 20); 

			glTexCoord2f(0.0f, 1.0f);glVertex3f(40-0.1, 18, 20); 

			glTexCoord2f(1.0f, 1.0f);glVertex3f(40-0.1,  18, 30); 

			glTexCoord2f(1.0f, 0.0f);glVertex3f(40-0.1,  0, 30);

			glEnd();

			
//绘制教室两边石柱前边两根
	glDisable(GL_TEXTURE_2D);
		//glEnable(GL_TEXTURE_2D);
		//glBindTexture(GL_TEXTURE_2D, textures[TEXTURE_STONE]);
		for(int i=0;i<=3;i++)

		{

			glColor3f(1.0f,1.0f,1.0f);

			//石柱上表面

			glBegin(GL_QUADS);

			glNormal3f(0.0f, -1.0f, 0.0f); //用于定义法线向量

			glTexCoord2f(0.0f, 0.0f);glVertex3f(-40.0,30.0f, -8.0f+22*i); 

			glTexCoord2f(1.0f, 0.0f);glVertex3f(-40.0, 30.0f, -10.0f+22*i); 

			glTexCoord2f(1.0f, 1.0f);glVertex3f(-38.0, 30.0f, -10.0f+22*i); 

			glTexCoord2f(0.0f, 1.0f);glVertex3f(-38.0f, 30.0f, -8.0f+22*i);

			glEnd();

			//石柱前表面

			glBegin(GL_QUADS);

			glNormal3f(0.0f, 0.0f, 1.0f); //用于定义法线向量

			glTexCoord2f(0.0f, 0.0f);glVertex3f(-40.0,0.0f, -8.0f+22*i); 

			glTexCoord2f(0.0f, 1.0f);glVertex3f(-40.0, 30.0f, -8.0f+22*i); 

			glTexCoord2f(1.0f, 1.0f);glVertex3f(-38.0, 30.0f, -8.0f+22*i); 

			glTexCoord2f(1.0f, 0.0f);glVertex3f(-38.0, 0.0f, -8.0f+22*i);

			glEnd();

			//石柱后表面

			glBegin(GL_QUADS);

			glNormal3f(0.0f, 0.0f, -1.0f); //用于定义法线向量

			glTexCoord2f(0.0f, 0.0f);glVertex3f(-40.0,0.0f, -10.0f+22*i); 

			glTexCoord2f(0.0f, 1.0f);glVertex3f(-40.0, 30.0f, -10.0f+22*i); 

			glTexCoord2f(1.0f, 1.0f);glVertex3f(-38.0, 30.0f, -10.0f+22*i); 

			glTexCoord2f(1.0f, 0.0f);glVertex3f(-38.0, 0.0f, -10.0f+22*i);

			glEnd();

			//石柱右表面

			glBegin(GL_QUADS);

			glNormal3f(0.0f, 0.0f, -1.0f); //用于定义法线向量

			glTexCoord2f(0.0f, 0.0f);glVertex3f(-38.0, 0.0f, -8.0f+22*i); 

			glTexCoord2f(0.0f, 1.0f);glVertex3f(-38.0, 30.0f, -8.0f+22*i); 

			glTexCoord2f(1.0f, 1.0f);glVertex3f(-38.0, 30.0f, -10.0f+22*i); 

			glTexCoord2f(1.0f, 0.0f);glVertex3f(-38.0, 0.0f, -10.0f+22*i);

			glEnd();
//*******************************************************右侧石柱*********************
		    glColor3f(1.0f,1.0f,1.0f);

			//石柱上表面

			glBegin(GL_QUADS);

			glNormal3f(0.0f, -1.0f, 0.0f); //用于定义法线向量

			glTexCoord2f(0.0f, 0.0f);glVertex3f(-40.0+1*78,30.0f, -8.0f+22*i); 

			glTexCoord2f(1.0f, 0.0f);glVertex3f(-40.0+1*78, 30.0f, -10.0f+22*i); 

			glTexCoord2f(1.0f, 1.0f);glVertex3f(-38.0+1*78, 30.0f, -10.0f+22*i); 

			glTexCoord2f(0.0f, 1.0f);glVertex3f(-38.0f+1*78, 30.0f, -8.0f+22*i);

			glEnd();

			//石柱前表面

			glBegin(GL_QUADS);

			glNormal3f(0.0f, 0.0f, 1.0f); //用于定义法线向量

			glTexCoord2f(0.0f, 0.0f);glVertex3f(-40.0+1*78,0.0f, -8.0f+22*i); 

			glTexCoord2f(0.0f, 1.0f);glVertex3f(-40.0+1*78, 30.0f, -8.0f+22*i); 

			glTexCoord2f(1.0f, 1.0f);glVertex3f(-38.0+1*78, 30.0f, -8.0f+22*i); 

			glTexCoord2f(1.0f, 0.0f);glVertex3f(-38.0+1*78, 0.0f, -8.0f+22*i);

			glEnd();

			//石柱后表面

			glBegin(GL_QUADS);

			glNormal3f(0.0f, 0.0f, -1.0f); //用于定义法线向量

			glTexCoord2f(0.0f, 0.0f);glVertex3f(-40.0+1*78,0.0f, -10.0f+22*i); 

			glTexCoord2f(0.0f, 1.0f);glVertex3f(-40.0+1*78, 30.0f, -10.0f+22*i); 

			glTexCoord2f(1.0f, 1.0f);glVertex3f(-38.0+1*78, 30.0f, -10.0f+22*i); 

			glTexCoord2f(1.0f, 0.0f);glVertex3f(-38.0+1*78, 0.0f, -10.0f+22*i);

			glEnd();

			//石柱右表面

			glBegin(GL_QUADS);

			glNormal3f(0.0f, 0.0f, -1.0f); //用于定义法线向量

			glTexCoord2f(0.0f, 0.0f);glVertex3f(-38.0+1*76, 0.0f, -8.0f+22*i); 

			glTexCoord2f(0.0f, 1.0f);glVertex3f(-38.0+1*76, 30.0f, -8.0f+22*i); 

			glTexCoord2f(1.0f, 1.0f);glVertex3f(-38.0+1*76, 30.0f, -10.0f+22*i); 

			glTexCoord2f(1.0f, 0.0f);glVertex3f(-38.0+1*76, 0.0f, -10.0f+22*i);

			glEnd();

			}

			glDisable(GL_TEXTURE_2D);

			//绘制讲台
            //贴讲台纹理

	        glBindTexture(GL_TEXTURE_2D, textures[TEXTURE_SPEAKERDESK]);

			glEnable(GL_TEXTURE_2D);

			glBegin(GL_QUADS);

			glNormal3f(0.0f, 1.0f, 0.0f); //用于定义法线向量

			glTexCoord2f(0.0f, 0.0f);glVertex3f(-17.5f, 1.5f, -1.0f); 

			glTexCoord2f(0.0f, 1.0f);glVertex3f(-17.5f, 9.5f, -1.0f); 

			glTexCoord2f(1.0f, 1.0f);glVertex3f(-3.5f,  9.5f, -1.0f); 

			glTexCoord2f(1.0f, 0.0f);glVertex3f(-3.5f,  1.5f, -1.0f);

			glEnd();

			glBegin(GL_QUADS);

			glNormal3f(0.0f, 1.0f, 0.0f); //用于定义法线向量

			glTexCoord2f(0.0f, 0.0f);glVertex3f(-3.5f, 1.5f, -1.0f); 

			glTexCoord2f(0.0f, 1.0f);glVertex3f(-3.5f, 9.5f, -1.0f); 

			glTexCoord2f(1.0f, 1.0f);glVertex3f(-3.5f,  9.5f, -5.0f); 

			glTexCoord2f(1.0f, 0.0f);glVertex3f(-3.5f,  1.5f, -5.0f);

			glEnd();

			glBegin(GL_QUADS);

			glNormal3f(0.0f, 1.0f, 0.0f); //用于定义法线向量

			glTexCoord2f(0.0f, 0.0f);glVertex3f(-17.5f, 1.5f, -1.0f); 

			glTexCoord2f(0.0f, 1.0f);glVertex3f(-17.5f, 9.5f, -1.0f); 

			glTexCoord2f(1.0f, 1.0f);glVertex3f(-17.5f,  9.5f, -5.0f); 

			glTexCoord2f(1.0f, 0.0f);glVertex3f(-17.5f,  1.5f, -5.0f);

			glEnd();

			glBegin(GL_QUADS);

			glNormal3f(0.0f, 1.0f, 0.0f); //用于定义法线向量

			glTexCoord2f(0.0f, 0.0f);glVertex3f(-17.5f, 9.5f, -1.0f); 

			glTexCoord2f(0.0f, 1.0f);glVertex3f(-17.5f, 9.5f, -3.0f); 

			glTexCoord2f(1.0f, 1.0f);glVertex3f(-3.5f,  9.5f, -3.0f); 

			glTexCoord2f(1.0f, 0.0f);glVertex3f(-3.5f,  9.5f, -1.0f);

			glEnd();

			glDisable(GL_TEXTURE_2D);
//绘制黑板

			glEnable(GL_TEXTURE_2D);

			glBindTexture(GL_TEXTURE_2D, textures[TEXTURE_BLACKBOARD]);

			glBegin(GL_QUADS);

			glNormal3f(0.0f, 0.0f, 1.0f); //用于定义法线向量

			glTexCoord2f(0.0f, 0.0f);glVertex3f(-20.0,8.0f, -9.5); 

			glTexCoord2f(0.0f, 1.0f);glVertex3f(-20.0, 23.0f, -9.5); 

			glTexCoord2f(1.0f, 1.0f);glVertex3f(22.0, 23.0f,-9.5); 

			glTexCoord2f(1.0f, 0.0f);glVertex3f(22.0, 8.0f, -9.5);

			glEnd();

			glDisable(GL_TEXTURE_2D);

			//画黑板凹槽
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
	        //绘制教室前边一块高地并贴纹理

           glEnable(GL_TEXTURE_2D);

		   glBindTexture(GL_TEXTURE_2D, textures[TEXTURE_SPEAKERDESK]);

			//贴上面

			glBegin(GL_POLYGON);

			glNormal3f(0.0f, 1.0f, 0.0f); //用于定义法线向量

			glTexCoord2f(0.0f, 0.0f);glVertex3f(-30.0f, 2.5f, 1.0f); //A

			glTexCoord2f(0.0f, 1.0f);glVertex3f(-30.0f, 2.5f, -9.5); //B

			glTexCoord2f(1.0f, 1.0f);glVertex3f(30.0f, 2.5f, -9.5); //C

            glTexCoord2f(0.0f, 0.0f);glVertex3f(30.0f, 2.5f, 1.0f); //D

			glTexCoord2f(0.0f, 0.0f);glVertex3f(20.0f, 2.5f, 8.0f); //E

        	glTexCoord2f(1.0f, 0.0f);glVertex3f(-20.0f,  2.5f, 8.0f);//F

			glEnd();

			//贴左边

			glBegin(GL_QUADS);

			glNormal3f(0.0f, 0.0f, 1.0f); //用于定义法线向量

			glTexCoord2f(0.0f, 0.0f);glVertex3f(-30.0f, 0, 1.0f); 

			glTexCoord2f(0.0f, 1.0f);glVertex3f(-30.0f, 2.5f, 1.0f); 

			glTexCoord2f(1.0f, 1.0f);glVertex3f(-30.0f,  2.5f,-9.5); 

			glTexCoord2f(1.0f, 0.0f);glVertex3f(-30.0f,  0, -9.5);

			glEnd();

			//贴左斜边

			glBegin(GL_QUADS);

			glNormal3f(0.0f, 0.0f, 1.0f); //用于定义法线向量

			glTexCoord2f(0.0f, 0.0f);glVertex3f(-30.0f, 0, 1.0f); 

			glTexCoord2f(0.0f, 1.0f);glVertex3f(-30.0f, 2.5f, 1.0f); 

			glTexCoord2f(1.0f, 1.0f);glVertex3f(-20.0f,  2.5f, 8.0f); 

			glTexCoord2f(1.0f, 0.0f);glVertex3f(-20.0f,  0, 8.0f);

			glEnd();

			//贴右斜边

			glBegin(GL_QUADS);

			glNormal3f(0.0f, 0.0f, 1.0f); //用于定义法线向量

			glTexCoord2f(0.0f, 0.0f);glVertex3f(30.0f, 0, 1.0f); 

			glTexCoord2f(0.0f, 1.0f);glVertex3f(30.0f, 2.5f, 1.0f); 

			glTexCoord2f(1.0f, 1.0f);glVertex3f(20.0f,  2.5f, 8.0f); 

			glTexCoord2f(1.0f, 0.0f);glVertex3f(20.0f,  0, 8.0f);

			glEnd();


			//贴前边

			glBegin(GL_QUADS);

			glNormal3f(0.0f, 1.0f, 0.0f); //用于定义法线向量

			glTexCoord2f(0.0f, 0.0f);glVertex3f(-20.0f, 0, 8.0f); 

			glTexCoord2f(0.0f, 1.0f);glVertex3f(-20.0f, 2.5f, 8.0f); 

			glTexCoord2f(1.0f, 1.0f);glVertex3f(20.0f,  2.5f, 8.0f); 

			glTexCoord2f(1.0f, 0.0f);glVertex3f(20.0f,  0, 8.0f);

			glEnd();

			//贴右边

			glBegin(GL_QUADS);

			glNormal3f(0.0f, 1.0f, 0.0f); //用于定义法线向量

			glTexCoord2f(0.0f, 0.0f);glVertex3f(30.0f, 0, 1.0f); 

			glTexCoord2f(0.0f, 1.0f);glVertex3f(30.0f, 2.5f, 1.0f); 

			glTexCoord2f(1.0f, 1.0f);glVertex3f(30.0f,  2.5f,-9.5); 

			glTexCoord2f(1.0f, 0.0f);glVertex3f(30.0f,  0,-9.5);

			glEnd();

			glDisable(GL_TEXTURE_2D);



//绘制投影仪
			drawprojector();

//绘制音响
			drawsound();

//绘制电风扇
			drawfans();
//绘制时钟
			drawclock();
//绘制桌子
	     	mydesk();








/***************************************************************************人物********************************/
    glPushMatrix();
 //   glRotatef(angle,0,1,0);//小人物整体旋转
 //   glTranslatef(0,-5,30);
	//draw_body();
 //   draw_head();
 //   draw_leftshoulder();
 //   draw_rightshoulder();
 //   draw_leftfoot();
 //   draw_rightfoot();
	    glPopMatrix();
/***************************************************************************人物********************************/


    // Restore the matrix state

    glPopMatrix();
 glPopMatrix();


    glutSwapBuffers();
    }


void initial()//灯光初始化

{

    glClearColor(0,0,0,0);

	glEnable(GL_TEXTURE_2D);

	glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_REPLACE);

	/*********************************************对灯光进行初始化****************************************************/

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

	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);	//指定材料着色的面

	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);	//指定材料对镜面光的反射

	glEnable(GL_DEPTH_TEST);//	

}

void print()

{

	printf("**************************************************** \n");

	printf(" \n");

	printf("欢迎进入OpenGL教室三维空间！ \n");

	printf("以下为操作说明：\n");

	printf("  上键和下键分别控制视角向上和向下平移 \n");

	printf("  左键和右键分别控制向左环视和向右环视 \n");

	printf("  w,s,a,d键分别表示向前，后，左，右，进行平移（注意键盘大小写）\n");

	printf("  F1、F2键分别控制视角向下和向上旋转 \n");

	printf("  F3、F4键分别控制投影仪放下和收起 \n");

	printf("  F5、F6键分别控制电扇的开关 \n");

	printf("  鼠标右击可以打开功能菜单（可使用之前部分功能），并补充了截图功能 \n");

	printf(" \n\n");

    printf("**************************************************** \n");



	printf(" \n\n\n\n");
	printf("                              *****************************************************\n");
	printf("************在这要特别感谢一些 《OpenGL宝典第四版》的诸多用例程序讲解以及网上一些优秀案例************************* \n");
	printf("*****************************************是你们带着我入门，给了我启发。******************************************* \n");
	printf("**************************************************特别感谢我的女朋友********************************************** \n");
	printf("*****************************************在我无助的时候给我精神的鼓励********************************************* \n");
	printf("                              *****************************************************\n");

	printf(" \n");
	printf("                                                                          制作人：江大数媒学院  冯一诚  \n");
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
    glutAddMenuEntry("打开电扇",0);
    glutAddMenuEntry("关闭电扇",1);
    glutAddMenuEntry("打开室灯",2);
    glutAddMenuEntry("关闭室灯", 3);
	glutAddMenuEntry("场景截图",4);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
    
	print();
    // Startup, loop, shutdown
    SetupRC();

    glutMainLoop();
    ShutdownRC();
    
    return 0;
    }