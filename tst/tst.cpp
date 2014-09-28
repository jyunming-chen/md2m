// viewer
// grid
// md2m clipboard

// init
#if 0
t3DModel *AAA;
float scale, center[3], size[3];
int loopover;
AAA = MD2MReadMD2 (char* meshfile, char*skinfile);
MD2MFindDimension  (AAA, center, size);
#define max(x,y) ((x)>(y)?(x):(y))
#define max3(x,y,z) (max(max(x,y),max(y,z)))
scale = max3 (size[0],size[1],size[2]);
#undef max
#undef max3

MD2MSetLoop (AAA, GLboolean); 
MD2MSetAnimation (AAA, int pose);
MD2MSetAnimationSpeed (AAA, float Hz); 
glEnable (GL_TEXTURE_2D);

// display
glPushMatrix();
glTranslatef (0,1,0);
glScalef (2/scale, 2/scale, 2/scale);
glTranslatef (-center[0],-center[1],-center[2]);
loopover = MD2MInterpolate (AAA);
glPopMatrix();
#endif


////////////////////////////////////
#include "gluit.h"
#include "md2m.h"

#pragma comment (lib, "md2m-vc9.lib")
#pragma comment (lib, "gluit-vc9.lib")
#pragma comment (lib, "glpngd-vc9.lib")


int mainwin, viewer;
void display(){}
void reshape(int w, int h)
{
	glViewport(0,0,w,h);
	ViewerReshape(viewer);
}

void grid()
{
	glPushAttrib (GL_ALL_ATTRIB_BITS);
	glDisable (GL_LIGHTING);
	glDisable (GL_TEXTURE_2D);
	glLineWidth (1.0);
	glColor3f (1,1,1);
	glBegin (GL_LINES);
	for (int i = -5; i <= 5; i++) {
		glVertex3i (-5,0,i); glVertex3i (5,0,i);
		glVertex3i (i,0,-5); glVertex3i (i,0,5);
	}
	glEnd();
	glPopAttrib();
}
t3DModel *mario;
float scale, center[3], size[3];
int loopover;

void content()
{
	glClear (GL_DEPTH_BUFFER_BIT|GL_COLOR_BUFFER_BIT);
	grid();
	
	glPolygonMode (GL_FRONT_AND_BACK, GL_LINE);

	glPushMatrix();
	glTranslatef (0,1,0);
	glScalef (2/scale, 2/scale, 2/scale);
	glTranslatef (-center[0],-center[1],-center[2]);
	loopover = MD2MInterpolate (mario);
	glPopMatrix();
	
	glutSwapBuffers();
}

void init()
{
	glEnable (GL_DEPTH_TEST);
	glClearColor (.6,.6,.6,1);

	mario = MD2MReadMD2 ("../tris.md2", "../mario2.png");
	MD2MFindDimension  (mario, center, size);
	#define max(x,y) ((x)>(y)?(x):(y))
	#define max3(x,y,z) (max(max(x,y),max(y,z)))
	scale = max3 (size[0],size[1],size[2]);
	#undef max
	#undef max3

	glEnable (GL_TEXTURE_2D);
	MD2MSetLoop (mario, GL_TRUE); 
	MD2MSetAnimation (mario, 0);
	MD2MSetAnimationSpeed (mario, 10); 

//	MD2MSetViewMode (mario, GL_LINE);
}

void timer (int dummy)
{
	glutTimerFunc (10, timer, 0);
	glutPostRedisplay();
}

void main (int argc, char** argv)
{
	glutInit (&argc, argv);
	glutInitDisplayMode (GLUT_RGB|GLUT_DOUBLE|GLUT_DEPTH);
	glutInitWindowSize (400,400);
	mainwin = glutCreateWindow ("tst");

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);

	viewer = ViewerNew (mainwin, 0,0,400,400, content);
	init();
	glutTimerFunc (0, timer, 0);

	glutMainLoop();
}
