#include<windows.h>
#include<stdio.h>
#include<stdlib.h>
#include<GL/glut.h>


GLfloat vertices[][3] = {{-1.0,-1.0,-1.0},{1.0,-1.0,-1.0},{1.0,1.0,-1.0},{-1.0,1.0,-1.0},{-1.0,-1.0,1.0},{1.0,-1.0,1.0},{1.0,1.0,1.0},{-1.0,1.0,1.0}};
GLfloat colors[][3] = {{0.0,0.0,0.0},{1.0,0.0,0.0},{1.0,0.0,0.0},{1.0,1.0,0.0},
{0.0,0.0,1.0},{1.0,0.0,1.0},{1.0,1.0,1.0},{0.0,1.0,1.0}};
static GLfloat theta[]={0.0,0.0,0.0};
GLint axis =1;
static float a=1.0f,b=1.0f,c=1.0f;
static float alpha=0.0;
void special(int key, int, int) {
  switch (key) {
    case GLUT_KEY_UP:
        {
            a=a+0.05f;
            b=b+0.05f;
            c=c+0.05f;
            glutPostRedisplay();
            break;
        }
    case GLUT_KEY_DOWN:
        {
            a=a-0.05f;
            b=b-0.05f;
            c=c-0.05f;
            glutPostRedisplay();
            break;

        }
    case GLUT_KEY_LEFT:
        {
            alpha=alpha+1.0;
            glutPostRedisplay();
            break;
        }
    case GLUT_KEY_RIGHT:
        {
            alpha=alpha-1.0;
            glutPostRedisplay();
            break;
        }
    default: return;
  }
  glutPostRedisplay();
}
void polygon(int a, int b,int c,int d)
{
//draw a polygon via list of vertice
glBegin(GL_POLYGON);
  glColor3fv(colors[a]);
  glVertex3fv(vertices[a]);
  glColor3fv(colors[b]);
  glVertex3fv(vertices[b]);
  glColor3fv(colors[c]);
  glVertex3fv(vertices[c]);
  glColor3fv(colors[d]);
  glVertex3fv(vertices[d]);
  glEnd();
}
void colorcube(void)
{ //map vertices to faces
polygon(0,3,2,1);
polygon(2,3,7,6);
polygon(0,4,7,3);
polygon(1,2,6,5);
polygon(4,5,6,7);
polygon(0,1,5,4);
}

void display(void)
{
// display callback , clear frame buffer an Z buffer ,rotate cube and draw , swap buffer.
   glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
   glLoadIdentity();
   //glRotatef(alpha,1.0,0.0,0.0);
   glRotatef(alpha,0.0,1.0,0.0);
   glRotatef(alpha,0.0,0.0,1.0);
   //alpha=alpha+1.0;
   glScalef(a,b,c);


  colorcube();
  glFlush();
glutSwapBuffers();
}
//void spinCube()
//{
  // idle callback,spin cube 2 degreees about selected axis
  // theta[axis] +=1.0;
//if(theta[axis]>360.0)
//theta[axis]-= 360.0;
//glutPostRedisplay();
//}
void mouse(int btn,int state,int x,int y)
{
//mouse calback ,select an axis about which to rotate
if(btn== GLUT_LEFT_BUTTON && state ==GLUT_DOWN)
{
    axis=0;

}
if(btn== GLUT_MIDDLE_BUTTON && state ==GLUT_DOWN) axis =1;
if(btn== GLUT_RIGHT_BUTTON && state ==GLUT_DOWN) axis =2;
}
void myReshape(int w,int h)
{
    glViewport(0,0,w,h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-2.0,2.0,-2.0 , 2.0, -10.0,10.0);
    glMatrixMode(GL_MODELVIEW);
}
int main(int argc,char** argv)
{
glutInit(&argc,argv);
//need both double buffering and Zbuffer
glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB|GLUT_DEPTH);
glutInitWindowSize(500,500);
glutCreateWindow("scaling and rotating a coloured cube using arrow keys ");
glutReshapeFunc(myReshape);
glutDisplayFunc(display);
//glutIdleFunc(spinCube);
glutMouseFunc(mouse);
glutSpecialFunc(special);//for special arrow keys....
glEnable(GL_DEPTH_TEST);  //Enable hidden surface removal
glutMainLoop();
return 0;
}
