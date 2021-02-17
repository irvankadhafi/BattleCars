/***
Author : H. M. Tarek Ullah
***/

#include <stdio.h>
#include <GL/glut.h>
#include<math.h>

#define BULLETS 100

GLfloat rotation = 90.0;
float posX = 0, posY = 0, posZ = 0;
float move_unit = 3;
float rate = 1.0f;
float angle = -0.0f;
float RotateX = 0.f, RotateY = 45.f;
int missileLeftX = 0;
int missileLeftY = 0;

int viewY1, viewX1, viewX2, viewX3, viewY2, viewY3,viewZ1=0 ;

typedef struct {
    int inuse;
    float x;
    float y;
    float v;
    float xv;
    float yv;
    int expire;
} Bullet;

Bullet bullet[BULLETS];


//Initializes 3D rendering
void initRendering() {
	glEnable(GL_DEPTH_TEST);
}


//Called when the window is resized
void handleResize(int w, int h) {
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, (double)w / (double)h, 1.0, 200.0);
}



void Timer(int value)
{
	glutPostRedisplay();      // Post re-paint request to activate display()
	glutTimerFunc(16, Timer, 0); // next Timer call milliseconds later
}

void stand()
{
	// windmill stand
	glBegin(GL_QUADS);
	glColor3f(0.69, 0.43, 0.314);
	glVertex3i(106, 298,0);
	glVertex3i(199, 296,0);
	glVertex3i(160, 420,0);
	glVertex3i(140, 420,0);
	glEnd();
	glFlush();

}

void windmill()
{

	//left 1st wing
	glBegin(GL_QUADS);
	glColor3f(0.0, 0.0, 0.0);
	glVertex3i(200, 400, 0);
	glVertex3i(180, 450, 0);
	glVertex3i(20, 570, 0);
	glVertex3i(40, 520, 0);
	//glEnd();
	glFlush();
	//2nd wing
	glColor3f(0.0, 0.0, 0.0);
	glVertex3i(0, 400, 0);
	glVertex3i(190, 520, 0);
	glVertex3i(210, 570, 0);
	glVertex3i(20, 450, 0);
	glEnd();
	glFlush();


}

void plane1() {
	/*----------------------- Plane ------------- */
	//plane


	glColor3ub(255, 0, 0);
	glBegin(GL_POLYGON);
	glPointSize(3.0);

	glVertex3i(10 + viewX1, 245 + viewY1, viewZ1);
	glVertex3i(15 + viewX1, 245 + viewY1, viewZ1);
	glVertex3i(35 + viewX1, 235 + viewY1, viewZ1);
	glVertex3i(15 + viewX1, 225 + viewY1, viewZ1);
	glEnd();

	//plane wing back
	glColor3ub(255, 0, 0);
	glBegin(GL_POLYGON);
	glVertex3i(80 + viewX1, 225 + viewY1, viewZ1);
	glVertex3i(90 + viewX1, 245 + viewY1, viewZ1);
	glVertex3i(85 + viewX1, 245 + viewY1, viewZ1);
	glVertex3i(50 + viewX1, 225 + viewY1, viewZ1);
	glEnd();

	glColor3ub(255, 0, 0);
	glBegin(GL_POLYGON);
	glVertex3i(80 + viewX1, 225 + viewY1, viewZ1);
	glVertex3i(90 + viewX1, 245 + viewY1, viewZ1);
	glVertex3i(88 + viewX1, 245 + viewY1, viewZ1);
	glVertex3i(55 + viewX1, 225 + viewY1, viewZ1);
	glEnd();

	glColor3ub(0, 0, 255);
	glBegin(GL_POLYGON);
	glVertex3i(90 + viewX1, 220 + viewY1, viewZ1);
	glVertex3i(30 + viewX1, 220 + viewY1, viewZ1);
	glVertex3i(15 + viewX1, 225 + viewY1, viewZ1);
	glVertex3i(35 + viewX1, 235 + viewY1, viewZ1);
	glVertex3i(80 + viewX1, 235 + viewY1, viewZ1);
	glVertex3i(90 + viewX1, 230 + viewY1, viewZ1);
	glEnd();

	glColor3ub(0, 0, 255);
	glBegin(GL_POLYGON);
	glVertex3i(90 + viewX1, 227 + viewY1, viewZ1);
	glVertex3i(30 + viewX1, 227 + viewY1, viewZ1);
	glVertex3i(30 + viewX1, 230 + viewY1, viewZ1);
	glVertex3i(90 + viewX1, 230 + viewY1, viewZ1);
	glEnd();

	glColor3ub(255, 0, 0);//head
	glBegin(GL_POLYGON);
	glVertex3i(90 + viewX1, 220 + viewY1, viewZ1);
	glVertex3i(90 + viewX1, 230 + viewY1, viewZ1);
	glVertex3i(100 + viewX1, 222 + viewY1, viewZ1);
	glVertex3i(100 + viewX1, 220 + viewY1, viewZ1);
	glEnd();

	glColor3ub(0, 220, 0);//glass
	glBegin(GL_POLYGON);
	glVertex3i(80 + viewX1, 225 + viewY1, viewZ1);
	glVertex3i(90 + viewX1, 225 + viewY1, viewZ1);
	glVertex3i(90 + viewX1, 228 + viewY1, viewZ1);
	glVertex3i(78 + viewX1, 237 + viewY1, viewZ1);
	glEnd();

	glColor3ub(255, 0, 0);
	glBegin(GL_POLYGON);
	glVertex3i(80 + viewX1, 225 + viewY1, viewZ1);
	glVertex3i(35 + viewX1, 212 + viewY1, viewZ1);
	glVertex3i(25 + viewX1, 212 + viewY1, viewZ1);
	glVertex3i(50 + viewX1, 225 + viewY1, viewZ1);
	glEnd();


	glutPostRedisplay();

}


 /*void drawBullets(void)
 {
     int i;
     glBegin(GL_POINTS);
     glColor3f(1.0, 0.0, 1.0);

     for (i=0; i<BULLETS; i++)
       {
            if (bullet[i].inuse) {
                glVertex2f(bullet[i].x, bullet[i].y); }
        }
                glEnd();
    } */

void drawMissileLeft(int missileX, int missileY)

{
	missileLeftX = missileX + 700 - 550;
	missileLeftY = missileY + 450;

	//printf("%d %d \n",missileLeftX,missileLeftY);
	//missile head
	glBegin(GL_TRIANGLES);
	glColor3f(1, 0, 0);
	glVertex2f(missileX + 700 - 550, missileY + 450);
	glVertex2f(missileX + 700 - 565, missileY + 447);
	glVertex2f(missileX + 700 - 565, missileY + 452);
	glEnd();

	//body
	glBegin(GL_QUADS);
	glColor3f(.8, .4, .1);
	glVertex2f(missileX + 700 - 565, missileY + 447);
	glVertex2f(missileX + 700 - 565, missileY + 452);
	glVertex2f(missileX + 700 - 560, missileY + 452);
	glVertex2f(missileX + 700 - 560, missileY + 447);
	glEnd();

	//tail
	glBegin(GL_POLYGON);
	glColor3f(0, .3, 0);
	glVertex2f(missileX + 700 - 560, missileY + 452);
	glVertex2f(missileX + 700 - 560, missileY + 447);
	glVertex2f(missileX + 700 - 580, missileY + 442);
	glVertex2f(missileX + 700 - 573, missileY + 450);
	glVertex2f(missileX + 700 - 580, missileY + 457);
	glEnd();


	//glFlush();


}
void drawCircle(int x1, int y1, int radius)

{
	float x2, y2;
	float angle;
	glBegin(GL_POLYGON);
	for (angle = .1f; angle<361.0f; angle += 1.0f)

	{
		x2 = x1 + sin(angle)*radius;
		y2 = y1 + cos(angle)*radius;
		glVertex2f(x2, y2);
	}

	glEnd();
}



void megh()

{
	glColor3f(0.4, 0.4, 0.4);
	drawCircle(45, 680, 20);
	drawCircle(75, 680, 40);
	drawCircle(90, 680, 45);
	drawCircle(120, 680, 35);
	drawCircle(140, 680, 20);

	drawCircle(200, 670, 25);
	drawCircle(220, 670, 35);
	drawCircle(260, 670, 50);
	drawCircle(290, 670, 35);
	drawCircle(320, 670, 20);

}

void tree()
{
	//right leaf
	glColor3f(0, 0.98, 0);
	drawCircle(1170, 288, 25);
	drawCircle(1190, 344, 45);
	drawCircle(1185, 320, 30);
	drawCircle(1245, 380, 55);
	drawCircle(1238, 310, 25);
	drawCircle(1259, 315, 30);
	drawCircle(1200, 295, 25);

	//left leaf

	glColor3f(0, 0.98, 0);
	drawCircle(956, 364, 20);
	drawCircle(990, 361, 25);
	drawCircle(1046, 361, 25);
	drawCircle(1070, 360, 20);

	glColor3f(0, 0.98, 0);
	drawCircle(980, 400, 25);
	drawCircle(1020, 387, 35);
	drawCircle(1065, 392, 25);

 	glColor3f(0, 0.98, 0);
	drawCircle(999, 440, 30);
	drawCircle(1030, 435, 35);



}

void background()
{
	//*******backgrounds*******
	//back sky ash background
	glMatrixMode(GL_MODELVIEW); //Switch to the drawing perspective
	glLoadIdentity(); //Reset the drawing perspective

    glColor3f(0.30, 0.701, 0.235);
	glBegin(GL_QUADS);
	glColor3f(0.70, 0.76, 0.96);
	glVertex2i(0, 420);
	glVertex2i(1277, 420);
	glVertex2i(1277, 780);
	glVertex2i(0, 780);
	glEnd();
	glFlush();

	///back grass left
	glBegin(GL_QUADS);
	glColor3f(0.30, 0.701, 0.235);
	glVertex3i(0, 420,0);
	glVertex3i(0, 80,0);
	glVertex3i(1236, 80,0);
	glVertex3i(625, 420,0);
	glEnd();
	glFlush();



	///back grass right
	glBegin(GL_TRIANGLES);
	glColor3f(0.30, 0.701, 0.235);
	glVertex3i(1277, 117,0);
	glVertex3i(1277, 420,0);
	glVertex3i(600, 420,0);
	glEnd();
	glFlush();

	///river side
  	glBegin(GL_QUADS);

	glColor3f(0.30, 0.701, 0.235);
	glVertex3i(0, 80,0);
	glVertex3i(0, 50,0);
	glVertex3i(1277, 50,0);
	glVertex3i(1277, 80,0);
	glEnd();
	glFlush();



	glFlush();
	glPopMatrix() ;
}


void treeBase()
{
	//tree base

	glBegin(GL_QUADS);
	glColor3f(0.313, 0.321, 0.258);
	glVertex3i(1230, 304, 0);
	glVertex3i(1230, 169, 0);
	glVertex3i(1260, 169, 0);
	glVertex3i(1260, 304, 0);
	glEnd();
	glFlush();

	glBegin(GL_QUADS);
	glColor3f(0.313, 0.321, 0.258);
	glVertex3i(1230, 180, 0);
	glVertex3i(1225, 170, 0);
	glVertex3i(1265, 170, 0);
	glVertex3i(1260, 180, 0);
	glEnd();
	glFlush();


	//tree base 2

	glBegin(GL_QUADS);
	glColor3f(0.313, 0.321, 0.258);
	glVertex3i(1004, 360, 0);
	glVertex3i(1004, 267, 0);
	glVertex3i(1027, 267, 0);
	glVertex3i(1027, 360, 0);
	glEnd();
	glFlush();

	glBegin(GL_QUADS);
	glColor3f(0.313, 0.321, 0.258);
	glVertex3i(1004, 267, 0);
	glVertex3i(1000, 265, 0);
	glVertex3i(1029, 265, 0);
	glVertex3i(1027, 267, 0);
	glEnd();
	glFlush();
    //glColor3f(0.0, 0.98, 0.0);
	tree();

}
void enemyObject(){
    glBegin(GL_QUADS);
	glColor3f(1, 0.0, 0.0);
	glVertex3i(1230, 180, 0);
	glVertex3i(1225, 170, 0);
	glVertex3i(1265, 170, 0);
	glVertex3i(1260, 180, 0);
	glEnd();
	glFlush();

}

void _bullet(){
    // glBegin(GL_QUAD) ;

    glutSolidSphere(.2, 50,50) ;
  // glEnd() ;
    glFlush() ;

}
void Display1(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.0, 0.0, 0.5);
	glPointSize(4.0);

	background();
	glPushMatrix() ;

     glutSolidSphere(.2, 50,50) ;
	glPopMatrix() ;

	//stand();

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glPushMatrix();
	glScalef(0.7, 0.7, 0.0) ;
	glTranslatef(213.0, 595.0f, 1);
	glRotatef(angle, 0.0f, 0.0f, 1.0f);
	if(angle >= 360){
	angle = angle - 360;
	}
	else{
        angle+=.50;
	}
	glTranslatef(-100.0f, -500.0f, -2.0f);


	//windmill();
	glPopMatrix();
	glFlush();


	treeBase();


//    drawBullets() ;

    glMatrixMode(GL_MODELVIEW); //Switch to the drawing perspective
	glLoadIdentity(); //Reset the drawing perspective

    glTranslatef(0.0,370.0, 0.0) ;
   // glTranslatef(posX, posY, posZ) ;

    plane1() ;
    enemyObject();
    _bullet() ;




    glPopMatrix( ) ;

	glLoadIdentity();

	glPushMatrix();
	glTranslatef(posX, posY, posZ);
	megh();

	glPopMatrix();



	glutSwapBuffers();

}

void myInit(void)
{
	glClearColor(0.30, 0.701, 0.235, 0.0);
	glColor3f(0.0f, 0.0f, 0.0f);
	glPointSize(3.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, 1280.0, 0.0, 768.0);
	//PlaySound("starwars.wav", NULL, SND_ASYNC|SND_FILENAME|SND_LOOP);
	//sndPlaySound("startwars.wav",SND_ASYNC);
}

void update(int value)
{
	posX += move_unit;
	if (posX>1000)
	{
		posX -= 1000;
	}
	glutPostRedisplay();
	glutTimerFunc(50, update, 0);
}

void keyboardown(int key, int x, int y)
{
	switch (key){


	case GLUT_KEY_UP:

		viewX1 ++;
		glutPostRedisplay();

		break;

	case GLUT_KEY_DOWN:

		viewX1 --;
		glutPostRedisplay();

		break;
    case GLUT_KEY_LEFT:
        viewY1++;
        glutPostRedisplay();

		break;
    case GLUT_KEY_RIGHT:
        viewY1--;
        glutPostRedisplay();

		break;
    case GLUT_KEY_F1 :
        viewZ1 += 20;
        glutPostRedisplay();

		break;
    case GLUT_KEY_F2 :
        viewZ1 -= 20;
        glutPostRedisplay();

		break;

	default:
		break;


	}

}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(1300, 800);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Shooter plane");
	glutDisplayFunc(Display1);
	myInit();
	glutTimerFunc(1000, update, 0);
    glutSpecialFunc(keyboardown);





	glutMainLoop();
}
