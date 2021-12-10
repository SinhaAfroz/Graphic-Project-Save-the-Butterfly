#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<iostream>
#include <windows.h>
#include <glut.h>

const int font=(int)GLUT_BITMAP_TIMES_ROMAN_24;
char s[30];

double arrow_x,arrow_y,butterfly_x[400],butterfly_y[400],arrow_pos,object_move;
bool state = false, pos_chg = false,fly_butterfly = false;
double pos_x, pos_y ,circle_x,circle_y,fly=0;
int count_point=0,flag=1;

void drawArrow()
{
    glBegin(GL_LINES);{
    glVertex3f( -350,50, 0);
    glVertex3f( -300,50, 0);
    }glEnd();

    glBegin(GL_POLYGON);{
    glVertex3f( -320,65, 0);
    glVertex3f( -300,50, 0);
    glVertex3f( -320,35, 0);
    }glEnd();

}

void drawD(float radius_x, float radius_y){
    int i = 0;
	float angle = 0.0;
    glColor3f(1.0, 1.0, 0.0);

    glTranslatef(-350,50,0);

	glBegin(GL_LINE_LOOP);
    {
		for(i = 0; i <100; i++)
		{
			angle =  3.1416 * i / 100;
			glVertex3f( (sin(angle) * radius_y) + pos_x,(cos(angle) * radius_x) + pos_y, 0);

		}

    }

	glEnd();
}
void drawCircle(float radius_x, float radius_y)
{
	int i = 0;
	float angle = 0.0;
    glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_LINES);
    {
		for(i = 0; i <100; i++)
		{
			angle = 2 * 3.1416 * i / 100;
			circle_x=cos(angle) * radius_x;
			circle_y=sin(angle) * radius_y;
			glVertex3f(circle_x,circle_y , 0);
		}

    }
      glColor3f(1.0, 1.0, 1.0);
	  glEnd();
	  glBegin(GL_LINES);{
      glVertex3f(0, 20 , 0);
      glVertex3f(0, -20, 0);
      }glEnd();
}
void drawButterfly(){
	int i = 0;
	float angle = 0.0;
    glColor3f(0.5,0.0,0.5);
	glBegin(GL_POLYGON);
    {
		for(i = 0; i <400; i++)
		{
			angle = 2 * 3.1416 * i / 400;
			//butterfly curve
			butterfly_x[i]=3*(sin(angle) * (exp(cos(angle))-(2*cos(4*angle))-pow(sin(angle/12),5)));
			butterfly_y[i]=3*(cos(angle) * (exp(cos(angle))-(2*cos(4*angle))-pow(sin(angle/12),5)));
			glVertex3f(butterfly_x[i],butterfly_y[i], 0);
		}

    }

	glEnd();

}

void drawSquare()
{
    glBegin(GL_QUADS);
    {
        glVertex3d( 40,  20, 0);
        glVertex3d( 40, -20, 0);
        glVertex3d(-40, -20, 0);
        glVertex3d(-40,  20, 0);
    }
    glEnd();
}



void keyboardListener(unsigned char key, int x,int y){
	switch(key){
        case '5':
            pos_chg=true;
            //glutPostRedisplay();
			break;
        case '1':
           // glutRedisplay();
		default:
			break;
	}
}

void specialKeyListener(int key, int x,int y){
	switch(key){
		case GLUT_KEY_UP:
		    pos_y = pos_y + 1;		//down arrow key
            glutPostRedisplay();
			break;
		case GLUT_KEY_DOWN:		// up arrow key
            pos_y = pos_y - 1;		//down arrow key
            glutPostRedisplay();
			break;
		default:
			break;
	}
}

void random(){

}

void game(){
    glColor3f(1,0,0);

     glPushMatrix();
         glTranslatef(arrow_pos,0,0);
         glTranslatef(0,pos_y,0);
         drawArrow();
     glPopMatrix();

    glPushMatrix();
       glTranslatef(0,object_move,0);
       glTranslatef(200,-300,0);
         glPushMatrix();
             glTranslatef(0,fly,0);
             //glTranslatef(200,-300,0);
             drawButterfly();
         glPopMatrix();

        drawCircle(20,20);
      glPopMatrix();

     glPushMatrix();
        drawD(30,30);
     glPopMatrix();
      glPushMatrix();
      glColor3f(0.6, 0.6, 0.6);
         glTranslatef(-200,255,0);
         glScaled(6,2,0);
        drawSquare();
     glPopMatrix();
     glPushMatrix();
         glTranslatef(-200,-255,0);
         glScaled(6,2,0);
        drawSquare();

     glPopMatrix();

}
void renderBitmapString(float x, float y, void *font,const char *string){
    const char *c;
    glRasterPos2f(x, y);
    for (c=string; *c != '\0'; c++) {
        glutBitmapCharacter(font, *c);
    }
}

void display(){

	//clear the display
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(1,1,1,1);	//color black
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	/********************
	/ set-up camera here
	********************/
	//load the correct matrix -- MODEL-VIEW matrix
	glMatrixMode(GL_MODELVIEW);

	//initialize the matrix
	glLoadIdentity();

	//gluLookAt(0,0,0,	0,0,-1,	0,1,0);


	//again select MODEL-VIEW
	glMatrixMode(GL_MODELVIEW);


	/****************************
	/ Add your objects from here
	****************************/
	//add objects

	//key_move();
	 //printf("/narrow y =%lf",arrow_pos);//530
	 //printf("/nb y =%lf",object_move);//37

      sprintf(s, "%d",count_point);

	 if(arrow_pos > 490 && arrow_pos < 500 && object_move > 110 && object_move <450 ){
        pos_chg=false;
        fly_butterfly=true;
        flag=0;
        count_point=100;
        //renderBitmapString(-100,50,(void *)font,"Game Over");
        renderBitmapString(-100,20,(void *)font,"you WIN");

	 }
	 else if(arrow_pos > 500 || object_move >500 ){
        renderBitmapString(-100,50,(void *)font,"Game Over");

	 }
     game();
     glColor3f(0,1,0);
     renderBitmapString(250,250,(void *)font,"Point :");
     renderBitmapString(350,250, (void*)font, s);

	//ADD this line in the end --- if you use double buffer (i.e. GL_DOUBLE)
	glutSwapBuffers();
}


void animate(){
    //incx+=0.5;

     if(pos_chg == true){
        arrow_pos+=.05;

     }
     if(fly_butterfly == true){
        fly+=.05;
     }
     if(flag == 1)
      object_move+=.03;

	//codes for any changes in Models, Camera
	glutPostRedisplay();
}

void init(){
	//codes for initialization
	//clear the screen
	glClearColor(0,0,0,0);

	/************************
	/ set-up projection here
	************************/
	//load the PROJECTION matrix
	glMatrixMode(GL_PROJECTION);

	//initialize the matrix
	glLoadIdentity();
	gluOrtho2D(-400, 400, -300, 300);
	//gluPerspective(80,	1,	1,	1000.0);

}

int main(int argc, char **argv){
	glutInit(&argc,argv);
	glutInitWindowSize(800, 600);
	glutInitWindowPosition(0, 0);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);	//Depth, Double buffer, RGB color

	glutCreateWindow("Free the butterfly");

	init();

	glEnable(GL_DEPTH_TEST);	//enable Depth Testing

	glutDisplayFunc(display);	//display callback function
	glutIdleFunc(animate);		//what you want to do in the idle time (when no drawing is occuring)

	glutKeyboardFunc(keyboardListener);
	glutSpecialFunc(specialKeyListener);
	//glutMouseFunc(mouseListener);


	glutMainLoop();		//The main loop of OpenGL

	return 0;
}
