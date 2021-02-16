#include <stdlib.h>
#include <GL/glut.h>
#include <stdio.h>
#include <iostream>

int Width, Height;
int refreshMills = 550;
GLfloat Widthfactor;
GLfloat Heightfactor;
GLfloat Zoom = 1;
GLint spin_x = 0;
GLint spin_y = 0;
GLfloat New_x;
GLfloat New_y;
GLfloat pos = 0;
GLfloat bulletpos = 0;
GLfloat enemybulletpos = 15;
GLfloat enemypos = 0;
GLdouble eyex = 0;
GLdouble eyey = 30;
GLdouble eyez = -15;
GLdouble centerx = 0;
GLdouble centery = 0;
GLdouble centerz = 7.5;
int counterFire = 0;
int hitboss =999;
int tracercounter = 0;
int bossfire = 150;
bool enemyFired = false;
bool bulletFired = false;
bool enemyDirection = true;
bool collision =false;
bool playercollision = false;
bool bossdefeated = false;
bool topdown = true;
bool tps = false;
bool fps = false;

void MyInit() {
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glEnable(GL_DEPTH_TEST);
}
void Timer(int val){
	if(bulletFired){
		bulletpos = bulletpos + 0.5;
	}
	
	if(enemypos == 10){
		enemyDirection = false;
	}
	if(enemypos == -10){
		enemyDirection = true;
	}
	if(enemyDirection){
		enemypos += 0.5;
	}else{
		enemypos -= 0.5;
	}
	
	// enemybulletpos -= 0.5;
	// if(counterFire == 35){
	// 	enemybulletpos = 15;
	// 	counterFire = 0;
	// }
	counterFire++;
	
	if(collision){
		tracercounter++;
	}
	if(tracercounter>bossfire+35){
		tracercounter = 0;
	}
	std::cout<<"Enemypos : "<<enemypos<<std::endl;
	// std::cout<<"enemyDirection : "<<enemyDirection<<std::endl;
	glutPostRedisplay();
   glutTimerFunc(refreshMills, Timer, 0);
}
void DrawBullet(){
	glPushMatrix();
	glTranslatef(pos, 0, bulletpos);
	glColor3f(0.5,1,1);
	glBegin(GL_QUADS);
	glVertex3f(0.1,0.5,0);
	glVertex3f(-0.1,0.5,0);
	glVertex3f(-0.1,0.5,0.5);
	glVertex3f(0.1,0.5,0.5);
	glEnd();
	glPopMatrix();
}
void bosstracer(){
	glColor3f(1,1,1);
	glBegin(GL_QUADS);
	glVertex3f(0.5,0.5,-5);
	glVertex3f(-0.5,0.5,-5);
	glVertex3f(-0.5,0.5,15);
	glVertex3f(0.5,0.5,15);
	glEnd();
	glBegin(GL_QUADS);
	glVertex3f(5,0.5,-5);
	glVertex3f(6,0.5,-5);
	glVertex3f(0.5,0.5,15);
	glVertex3f(1.0,0.5,15.3);
	glEnd();
	glBegin(GL_QUADS);
	glVertex3f(-5,0.5,-5);
	glVertex3f(-6,0.5,-5);
	glVertex3f(-0.5,0.5,15);
	glVertex3f(-1.0,0.5,15.3);
	glEnd();
}
void bosslaser(){
	glColor3f(1,0,0);
	glBegin(GL_QUADS);
	glVertex3f(0.8,0.5,-5);
	glVertex3f(-0.8,0.5,-5);
	glVertex3f(-0.5,0.5,15);
	glVertex3f(0.5,0.5,15);
	glEnd();
	glBegin(GL_QUADS);
	glVertex3f(5,0.5,-5);
	glVertex3f(6,0.5,-5);
	glVertex3f(0.5,0.5,15);
	glVertex3f(1.0,0.5,15.3);
	glEnd();
	glBegin(GL_QUADS);
	glVertex3f(-5,0.5,-5);
	glVertex3f(-6,0.5,-5);
	glVertex3f(-0.5,0.5,15);
	glVertex3f(-1.0,0.5,15.3);
	glEnd();
}

void enemyBullet(){
	glPushMatrix();
	glTranslatef(enemypos, 0, enemybulletpos);
	glColor3f(1,0,0);
	glBegin(GL_QUADS);
	glVertex3f(0.1,0.5,0);
	glVertex3f(-0.1,0.5,0);
	glVertex3f(-0.1,0.5,0.5);
	glVertex3f(0.1,0.5,0.5);
	glEnd();
	glPopMatrix();
}
void DrawBoss(){
	//wings
	glColor3f(0.4,0.4,0.4);
	glBegin(GL_QUADS);
	glVertex3f(2,0,0);
	glVertex3f(2,1.2,0);
	glVertex3f(0,0.8,0.8);
	glVertex3f(0,0.6,0.8);
	glEnd();
	glBegin(GL_QUADS);
	glVertex3f(-2,0,0);
	glVertex3f(-2,1.2,0);
	glVertex3f(0,0.8,0.8);
	glVertex3f(0,0.6,0.8);
	glEnd();
	
	//body
	glColor3f(0.3,0.3,0.3);
	glBegin(GL_TRIANGLES);
	glVertex3f(0.5,0.8,0.6);
	glVertex3f(-0.5,0.8,0.6);
	glVertex3f(0,0.1,0.6);
	glEnd();
	glColor3f(1,0.0,0.0);
	glPushMatrix();
	glTranslatef(0.5,0.7,0.55);
	glutSolidTorus(0.1,0.1,10,10);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-0.5,0.7,0.55);
	glutSolidTorus(0.1,0.1,10,10);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0,0.4,0.55);
	glutSolidTorus(0.1,0.1,10,10);
	glPopMatrix();
}
void DrawEnemy(){
	//wings
	glColor3f(0.4,0.4,0.4);
	glBegin(GL_QUADS);
	glVertex3f(0.8,0,0);
	glVertex3f(0.8,1.2,0);
	glVertex3f(0,0.8,0.8);
	glVertex3f(0,0.6,0.8);
	glEnd();
	glBegin(GL_QUADS);
	glVertex3f(-0.8,0,0);
	glVertex3f(-0.8,1.2,0);
	glVertex3f(0,0.8,0.8);
	glVertex3f(0,0.6,0.8);
	glEnd();
	
	//body
	glColor3f(1,0.0,0.0);
	glPushMatrix();
	glTranslatef(0,0.7,0.55);
	glutSolidTorus(0.1,0.1,10,10);
	glPopMatrix();
	glColor3f(1,1,0.0);
	glPushMatrix();
	glTranslatef(0,0.4,0.55);
	glutSolidTorus(0.1,0.1,10,10);
	glPopMatrix();
}

void DrawShip(){
	//cockpit
	glColor3f(0.0,0.0,1.0);
	glBegin(GL_QUADS);
	glVertex3f(0.3,0.45,4);
	glVertex3f(-0.3,0.45,4);
	glVertex3f(-0.3,1.15,2.2);
	glVertex3f(0.3,1.15,2.2);
	glEnd();
	glBegin(GL_TRIANGLES);
	glVertex3f(0.3,1.15,2.2);
	glVertex3f(0.3, 0.85,2.2);
	glVertex3f(0.3, 0.45,4);
	glEnd();
	glBegin(GL_TRIANGLES);
	glVertex3f(-0.3,1.15,2.2);
	glVertex3f(-0.3, 0.85,2.2);
	glVertex3f(-0.3, 0.45,4);
	glEnd();
	
	//body
	glColor3f(1.0,0.0,0.0);
	//top panel
	glBegin(GL_QUADS);
	glVertex3f(-0.3,1.15,2.2);
	glVertex3f(0.3,1.15,2.2);
	glVertex3f(0.3,0.45,0.5);
	glVertex3f(-0.3,0.45,0.5);
	glEnd();
	//side panel
	glBegin(GL_TRIANGLES);
	glVertex3f(0.3,1.15,2.2);
	glVertex3f(0.3, 0.85,2.2);
	glVertex3f(0.3, 0.45,0.5);
	glEnd();
	glBegin(GL_TRIANGLES);
	glVertex3f(-0.3,1.15,2.2);
	glVertex3f(-0.3, 0.85,2.2);
	glVertex3f(-0.3, 0.45,0.5);
	glEnd();
	//cockpit side panel
	glBegin(GL_TRIANGLES);
	glVertex3f(0.3,0.85,2.2);
	glVertex3f(0.3, 0.45,4);
	glVertex3f(0.3, 0.45,0.5);
	glEnd();
	glBegin(GL_TRIANGLES);
	glVertex3f(-0.3,0.85,2.2);
	glVertex3f(-0.3, 0.45,4);
	glVertex3f(-0.3, 0.45,0.5);
	glEnd();
	//cockpitsidewinder
	glBegin(GL_TRIANGLES);
	glVertex3f(0.3,0.45,1.2);
	glVertex3f(0.7, 0.45,1.2);
	glVertex3f(0.3, 0.45,4);
	glEnd();
	glBegin(GL_TRIANGLES);
	glVertex3f(-0.3,0.45,1.2);
	glVertex3f(-0.7, 0.45,1.2);
	glVertex3f(-0.3, 0.45,4);
	glEnd();
	
}

void DrawScene() {

	glRotatef(spin_x, 0.0, 1.0, 0.0);
	glRotatef(spin_y, 0.0, 0.0, 1.0);
	glScalef(Zoom, Zoom, Zoom);
	

	glColor3f(1.0, 0.0, 0.0);
	for(int xm = -20; xm < 20; xm++){					// x merah
	glPushMatrix();
	glTranslatef(0,0,xm);
	glBegin(GL_LINE_LOOP);
	glVertex3f(20.0, 0.0, 0.0);
	glVertex3f(-20.0, 0.0, 0.0);
	glEnd();
	glPopMatrix();
	}

	glColor3f(0.0, 1.0, 0.0);					//y hijau
	glBegin(GL_LINE_LOOP);
	glVertex3f(0.0, 10.0, 0.0);
	glVertex3f(0.0, 0.0, 0.0);
	glEnd();
	
	glColor3f(0.0, 0.0, 1.0);
	for(int zb = -20; zb < 20; zb++){	// z biru
	glPushMatrix();
	glTranslatef(zb,0,0);
	glBegin(GL_LINE_LOOP);
	glVertex3f(0.0, 0.0, 20.0);
	glVertex3f(0.0, 0.0, -20.0);
	glEnd();
	glPopMatrix();
	}
	if(bulletpos >= 15 && bulletpos <= 16 && pos >= enemypos-0.8 && pos<= enemypos+0.8){
		collision = true;	
	}
	
	if(bulletpos ==15 && pos >= -2 && pos<= 2 && collision){
		hitboss++;
		if(hitboss>=10)bossdefeated = true;	
	}
	
	if(enemybulletpos >= 0 && enemybulletpos <= 3 && enemypos >= pos-0.3 && enemypos<= pos+0.3 && !collision){
		playercollision = true;	
	}
	if(collision && tracercounter>= bossfire && (pos == 4 || pos == 5 || pos == -4 || pos == -5 || pos==1 || pos==-1 || pos == 0) && !bossdefeated){
		playercollision = true;
	}
	if(!collision){
		enemyBullet();
		glPushMatrix();
		glTranslatef(enemypos,0,15);
		DrawEnemy();
		glPopMatrix();
	}
	
	if(collision && hitboss<10){
		if(tracercounter<=bossfire && tracercounter>= bossfire-50){
		bosstracer();
		}else{
			if(tracercounter>= bossfire)bosslaser();
		}
		glPushMatrix();
		glTranslatef(0,0,15);
		DrawBoss();
		glPopMatrix();
	}
	
	if(!playercollision){
		DrawBullet();
		glPushMatrix();
		glTranslatef(pos,0,-1);
		DrawShip();
		glPopMatrix();
	}
	
}

void MyDisplay() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glColor3f(0,0,0);
	
	glViewport(0, 0, (Width * Widthfactor), (Height * Heightfactor) );						// ??? 
		glMatrixMode(GL_PROJECTION);
		glPushMatrix();
        glLoadIdentity();
        gluPerspective(30, 1.0 *(Widthfactor / Heightfactor ), 3.0, 50.0);												// ?, ???,
        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
        	if(fps || tps){
        		eyex = pos;
        		centerx = pos;
        		gluLookAt(eyex, eyey, eyez,  centerx, centery, centerz,  0.0, 1.0, 0.0);
			}else{
				gluLookAt(eyex, eyey, eyez,  centerx, centery, centerz,  0.0, 1.0, 0.0);	
			}
            DrawScene();
        glPopMatrix();
        glMatrixMode(GL_PROJECTION);
    glPopMatrix();
	glPopMatrix();
	glFlush();
}

void MyReshape(int NewWidth, int NewHeight) {
	Widthfactor = (GLfloat)NewWidth / (GLfloat)500;
	Heightfactor = (GLfloat)NewHeight / (GLfloat)500;

}


void MySpecial(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_UP:
	{
		spin_y += 1;
		spin_y = spin_y % 360;
		DrawScene();
		glutPostRedisplay();
		break;
	}
	case GLUT_KEY_DOWN:
	{
		spin_y -= 1;
		spin_y = spin_y % 360;
		DrawScene();
		glutPostRedisplay();
		break;
	}
	case GLUT_KEY_LEFT:
	{
		if(pos<9)pos = pos + 1;
		glutPostRedisplay();
		break;
	}
	case GLUT_KEY_RIGHT:
	{
		if(pos>-9)pos = pos - 1;
		glutPostRedisplay();
		break;
	}
	case GLUT_KEY_PAGE_UP:
	{
		Zoom = Zoom + 0.01;
		DrawScene();
		glutPostRedisplay();
		break;
	}
	case GLUT_KEY_PAGE_DOWN:
	{
		if (Zoom >= 0) {
			Zoom = Zoom - 0.01;
			DrawScene();
		}
		glutPostRedisplay();
		break;
	}
	case GLUT_KEY_HOME:
	{
		collision = false;
		break;
	}
	case GLUT_KEY_END:
	{
		playercollision = false;
		break;
	}
	}
}

void MyMouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		New_x = x;
		New_y = y;
	}
}
void MyMotion(int x, int y)
{
	spin_x = x - New_x;
	spin_y = y - New_y;
	DrawScene();
	glutPostRedisplay();
}
void KeyboardHandler(unsigned char key, int x, int y)
{
	
	switch (key) {
	case 'x':
		bulletFired = true;
		bulletpos = 0;
		break;
	case 'q':
		exit(0);
		break;
	case 'z':
		if(topdown){
			topdown = false;
			tps = true;
			eyex = 0;
			eyey = 7;
			eyez = -10;
			centerx = 0;
			centery = 1;
			centerz = 7.5;
		}else{
			if(tps){
				tps = false;
				fps = true;
				eyex = 0;
				eyey = 2;
				eyez = 0;
				centerx = 0;
				centery = 1;
				centerz = 7.5;
			}else{
				if(fps){
					fps = false;
					topdown = true;
					eyex = 0;
					eyey = 30;
					eyez = -15;
					centerx = 0;
					centery = 0;
					centerz = 7.5;
				}
			}
		}
		break;
	default: 
		break;
	}
	glutPostRedisplay();
}
int main(int argc, char** argv) {
	Width = 500;
	Height = 500;
	     glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	glutInitWindowSize(Width, Height);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("181524021");
	MyInit();
	glutDisplayFunc(MyDisplay);
	glutReshapeFunc(MyReshape);
	glutSpecialFunc(MySpecial);
	glutMouseFunc(MyMouse);
	glutMotionFunc(MyMotion);
	glutTimerFunc(refreshMills, Timer, 0);
	glutKeyboardFunc(KeyboardHandler);
	glutMainLoop();
	return 0;
}