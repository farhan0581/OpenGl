#include<math.h>

#define WIDTH 1000

#define HEIGHT 1000

#include<stdio.h>

#include<stdlib.h>

#include<string.h>

#include<GLUT/glut.h>



using namespace std;

static float arr[10][5000][2];

//float arr1[5000][2];

int z=0, z1=0, z2=0, mat[100];

int flag=1, ff=0;

float radius=15.0;

int ptr=0;

float color[3][3]={{1.0,0.0,0.0},{1.0,1.0,0.0},{1.0,1.0,0.0}};

float c1=0.2, c2=2.0, c3=1.2;



float xpos, ypos;

//ALL THE DRAWING FUNCTIONS//

//Draw A ball to Follow the path



//Draw Path

void drawLines()

{

    float r1=1.0,r2=0.0,r3=0.0;

    

    for(int i=0;i<z;i++)

    {

        glBegin(GL_LINE_STRIP);

        glColor3f(r1,r2,r3);

        for(int j=0;j<mat[i];j++)

        {

            glVertex2f(arr[i][j][0],arr[i][j][1]);

        }

        

        glEnd();

        r1=r1-0.15;

        r2=r2+0.1;

        r3=r3+0.1;

        

        //addValue(<#int x#>, <#int y#>)

    }

    

}

//INITIALISATION

void init()

{

    glClearColor( 1.0, 1.0, 1.0, 0.3);

    glMatrixMode( GL_PROJECTION);

    gluOrtho2D(0.0,WIDTH,0.0,HEIGHT);

    //memset(arr,0,5000);

    glPointSize(20.0);

}

//Reseting the Function

void resetAll()

{

    //memset(arr,0,5000);

z=0;

}

///OPENGL MAPPING///

float getOpenGLX(int x)

{

    double ox = x/ (double)WIDTH*(WIDTH);

    return ox;

}

float getOpenGLY(int y)

{

    double oy = (1 - y/ (double) HEIGHT)*HEIGHT;

    return oy;

}

//Insert Mouse coordinate to an array after mapping

void addValue(int x,int y)

{

arr[z][z1][0]=getOpenGLX(x);

arr[z][z1++][1]=getOpenGLY(y);

    

}

//Rest of the glut based special functions and their definition

void myDisplay()

{

    glClear( GL_COLOR_BUFFER_BIT);

    if(flag)

{

        drawLines();

        // drawBall(arr[ptr][0],arr[ptr][1]);

}

    glutSwapBuffers();

    glutPostRedisplay();

    glFlush();

}

void myPressedMove(int x,int y)

{

    if(flag)

{

        addValue(x,y);

}

}

void myMouseStat(int button,int state,int x, int y)

{

    if(button==GLUT_LEFT_BUTTON && state==GLUT_DOWN)

{

        //myPressedMove(x,y);

        //Sprintf(-1, -1);

        

        // if(!flag)

//{

        //resetAll();

//	flag=1;

//}

}

    else if(button==GLUT_LEFT_BUTTON && state==GLUT_UP)

{

        mat[z] = z1;

        z++;

        z1=0;

        

        // if(flag)

//{

        //ptr=0;

        //flag=0;

//}

}

}



void myTimer(int t)

{

    if(ptr!=z)

{

ptr++;

}

    else

{

ptr=0;

}

    glutTimerFunc(100,myTimer,0);

}

int main( int argc, char ** argv)

{

    glutInit( &argc, argv);

    glutInitDisplayMode( GLUT_DOUBLE| GLUT_RGB);

    glutInitWindowPosition( 100, 100);

    glutInitWindowSize(WIDTH,HEIGHT);

    glutCreateWindow( "paint");

    init();

    glutDisplayFunc(myDisplay);

    glutMouseFunc(myMouseStat);

    glutMotionFunc(myPressedMove);

    glutTimerFunc(100,myTimer,0);

    glutMainLoop();

    return 0;

}