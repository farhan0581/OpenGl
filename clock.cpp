#include <GLUT/glut.h>

#include <string.h>

#include <stdio.h>

#include <stdlib.h>

#include <math.h>

#include <time.h>



// define glu objects

int about_int=0;

int flag=0,xhr=10;



GLUquadricObj *Cylinder;

GLUquadricObj *Disk;



struct tm *newtime;

time_t ltime;

int M_TWOPI=0;

GLfloat rx, ry, rz, angle;



// lighting

GLfloat LightAmbient[]= { 0.1f, 0.5f, 0.5f, 1.0f };

GLfloat LightDiffuse[]= { 0.5f, 1.5f, 0.5f, 1.0f };

GLfloat LightPosition[]= { 5.0f, 5.0f, 15.0f, 1.0f };

GLfloat mat_specular[] = { 1.0, 10.0, 1.0, 1.0 };



static int light_state = 1; // light on = 1, light off = 0

static int view_state = 1; // Ortho view = 1, Perspective = 0







//copied 











void Sprint( float x, float y, char *st)

{

int l,i;

    

l=strlen( st );

glRasterPos3f( x, y, -1);

for( i=0; i < l; i++)

    {

glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, st[i]);

}

    

}



static void TimeEvent(int te)

{

    

rx = 30 * cos( angle );

ry = 30 * sin( angle );

rz = 30 * cos( angle );

angle += 0.01;

if (angle > M_TWOPI) angle = 0;

    

glutPostRedisplay();

glutTimerFunc( 100, TimeEvent, 1);

}



void init(void)

{

    

    

    glClearColor (2.0, 1.5, 1.0, 1.0);

    glShadeModel (GL_SMOOTH);

    glEnable(GL_DEPTH_TEST);

    // Lighting is added to scene

    glLightfv(GL_LIGHT1 ,GL_AMBIENT, LightAmbient);

    glLightfv(GL_LIGHT1 ,GL_DIFFUSE, LightDiffuse);

    glLightfv(GL_LIGHT1 ,GL_POSITION, LightPosition);

    glEnable(GL_LIGHTING);

    glEnable(GL_LIGHT1);

    

    

    Cylinder = gluNewQuadric();

    gluQuadricDrawStyle( Cylinder, GLU_FILL);

    gluQuadricNormals( Cylinder, GLU_SMOOTH);

    gluQuadricOrientation( Cylinder, GLU_OUTSIDE);

    gluQuadricTexture( Cylinder, GL_TRUE);

    

    Disk = gluNewQuadric();

    gluQuadricDrawStyle( Disk, GLU_FILL);

    gluQuadricNormals( Disk, GLU_SMOOTH);

    gluQuadricOrientation( Disk, GLU_OUTSIDE);

    gluQuadricTexture( Disk, GL_TRUE);

    

    

}



void Draw_gear( void )

{

glPushMatrix();

    gluDisk(Disk, 0, 2.5, 32, 16);

glPopMatrix();

}



void Draw_clock( GLfloat cx, GLfloat cy, GLfloat cz )

{

    

    int hour_ticks , sec_ticks;

    glPushMatrix();

    glTranslatef(cx,cy,cz);

    glRotatef( 180, 1.0, 0.0, 0.0);

    

    glPushMatrix(); // Draw clock face

    glColor3f(0.8, 2.0, 4.5);

    glTranslatef( 0, 0, 1.0);

    gluDisk(Disk, 0, 6.75, 32, 16);

    glPopMatrix();

    

    //xhr=11;

    glPushMatrix();// Draw hour hand

    glColor3f(0.8, 0.8, 0.8);

    glTranslatef( 0, 0, 0.0);

    glRotatef( (360/12) * xhr  + (360/60) * (60 / (newtime->tm_min+1)), 0.0, 0.0, 1.0);//newtime->tm_hour

    glPushMatrix();

    glTranslatef(0.0, 0.0, 2.0);

    glScalef(0.37, 0.37, 1.0);

    Draw_gear();

    glPopMatrix();

    glRotatef( 90, 1.0, 0.0, 0.0);

    gluCylinder(Cylinder, 0.5, 0, 4, 16, 16);

    glPopMatrix();

    

    glPushMatrix();// Draw minute hand

    glColor3f(4.5, 4.5, 4.5);//

    glTranslatef( 0, 0, 0.0);

    glRotatef( (360/60) * newtime->tm_min, 0.0, 0.0, 1.0);

    glPushMatrix();

    glTranslatef(0.0, 0.0, 3.0);

    glScalef(0.37, 0.37, 1.0);

    Draw_gear();

    glPopMatrix();

    glRotatef( 90, 1.0, 0.0, 0.0);

    gluCylinder(Cylinder, 0.37, 0, 6, 16, 16);

    glPopMatrix();

    

    glPushMatrix();// Draw second hand

    glColor3f(1.0, 0.5, 0.5);//

    glTranslatef( 0, 0, 0.0);//

    glRotatef( (360/60) * newtime->tm_sec, 0.0, 0.0, 1.0);

    glPushMatrix();

    glTranslatef(0.0, 0.0, 4.0);

    glScalef(0.25, 0.25, 1.0);

    Draw_gear();

    glPopMatrix();

    glRotatef( 90, 1.0, 0.0, 0.0);

    gluCylinder(Cylinder, 0.22, 0, 6, 16, 16);

    glPopMatrix();

    

    

    for(hour_ticks = 0; hour_ticks < 12; hour_ticks++)

    {

        glPushMatrix();// Draw next arm axis.

        glColor3f(1.0, 1.0, 1.0); // give it a color

        glTranslatef(0.0, 0.0, 0.0);

        glRotatef( (360/12) * hour_ticks, 0.0, 0.0, 1.0);

        glTranslatef( 6.0, 0.0, 0.0);

        //glutSolidCube(1.0);

        

        glPopMatrix();

    }

    

    for(sec_ticks = 0; sec_ticks < 60; sec_ticks++)

    {

        glPushMatrix();

        glTranslatef(0.0, 0.0, 0.0);

        glRotatef( (360/60) * sec_ticks, 0.0, 0.0, 1.0);

        glTranslatef(6.0, 0.0, 0.0);

        glutSolidCube(1.0);

        glPopMatrix();

}

    

    

    glPopMatrix();

    

}



void num()

{

    if(view_state == 1)

{

        glColor3f( 0.0, 0.0, 1.0); 

        Sprint(-3.2,-0.2,"9"); //counting from center

        Sprint(2.7,-6.2,"6"); 

        Sprint(2.7,5.7,"12");

        Sprint(8.8,-0.2,"3");

}

}



void display_clock()

{

time(&ltime); // Get time

    newtime = localtime(&ltime); // Convert to local time

    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    

    // easy way to put text on the screen.

    glMatrixMode (GL_PROJECTION);

    glLoadIdentity();

    glOrtho(-12.0, 12.0, -12.0, 12.0, 1.0, 60.0);

    glMatrixMode(GL_MODELVIEW);

    glLoadIdentity();

    glDisable(GL_LIGHTING);

    glDisable(GL_COLOR_MATERIAL);

    

    // Put view state on screen

    

    glColor3f(0.0, 0.0, 0.0);

    Sprint(-11.5,0.0, asctime(newtime));

    

    // Turn Perspective mode on/off

    if (view_state == 0)

    {

        glMatrixMode (GL_PROJECTION);

        glLoadIdentity();

        

        gluPerspective(60.0, 1, 1.0, 60.0);

        glMatrixMode(GL_MODELVIEW);

        glLoadIdentity();

        gluLookAt( rx, 0.0, rz, 0.0, 0.0, -14.0, 0, 1, 0);

    }

    

if (light_state == 1)

    {

        glEnable(GL_LIGHTING);

        glEnable(GL_COLOR_MATERIAL);  // Enable for lighing

    }else

    {

        glDisable(GL_LIGHTING);

        glDisable(GL_COLOR_MATERIAL);  // Disable for no lighing

    }

    

    Draw_clock( 3.0, 0.0, -14.0);

    //num();

    glutSwapBuffers();

}





void display(void)

{

    //glClear(GL_COLOR_BUFFER_BIT);

    display_clock();

    //glFlush();

}



void reshape (int w, int h)

{

    glViewport (0, 0, (GLsizei) w, (GLsizei) h);

    glMatrixMode (GL_PROJECTION);

    glLoadIdentity ();

}



void special(int key, int, int) {

    switch (key) {

        case GLUT_KEY_LEFT:

        {

            xhr=xhr+1.0;

            display();

            break;

        }

        case GLUT_KEY_RIGHT:

        {

            xhr=xhr-1.0;

            display();

            break;

        }

        default: return;

    }

    glutPostRedisplay();

}



int main(int argc, char** argv)

{

    int gh;

    glutInit(&argc, argv);

    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);

    glutInitWindowSize (800, 800);

    glutInitWindowPosition (50, 50);

    glutCreateWindow (argv[0]);

    glutSetWindowTitle("DIGITAL AND ANALOG CLOCK");

    init ();

    //glutCreateMenu(options);

   

    glutDisplayFunc(display);

    glutReshapeFunc(reshape);

    glutTimerFunc( 10, TimeEvent, 1);

    glutSpecialUpFunc(special);

    //glutSpecialFunc(special);

    glutMainLoop();



    return 0;

}


