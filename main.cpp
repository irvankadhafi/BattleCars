/*
 *  FinalProject
 *
 *  m             Toggles light (sun) movement
 *  p             Toggles first person/perspective projection
 *  +/-           Change field of view of perspective
 *  x             Toggle axes display
 *  arrow keys    Change view angle
 *  PgDn/PgUp     Zoom in and out (in perspective view)
 *  0             Reset view angle
 *  ESC           Exit
 *
 */
#include "IRVANKDHF.h"

#ifndef GL_CLAMP_TO_EDGE
#define GL_CLAMP_TO_EDGE 0x812F
#endif
int axes=0;       //  Display axes
int mode=0;       //  Projection mode
int move=1;       //  Move light
int th=-90;         //  Azimuth of view angle
int ph=0;         //  Elevation of view angle
int fov=85;       //  Field of view (for perspective)
int light=1;      //  Lighting
double asp=1.333;  //  Aspect ratio
double dim=8.0;   //  Size of world
GLuint textures[30];
// Light values
int one       =   1;  // Unit value
int distance  =   25;  // Light distance
int inc       =  10;  // Ball increment
int smooth    =   1;  // Smooth/Flat shading
int local     =   0;  // Local Viewer Model
int emission  =  30;  // Emission intensity (%)
int ambient   =  80;  // Ambient intensity (%)
int diffuse   = 100;  // Diffuse intensity (%)
int specular  =   0;  // Specular intensity (%)
int shininess =   0;  // Shininess (power of two)
float shiny   =   1;  // Shininess (value)
int zh        =  90;  // Light azimuth
float ylight  = 13;  // Elevation of light

int at0=100;      //  Constant  attenuation %
int at1=20;        //  Linear    attenuation %
int at2=20;        //  Quadratic attenuation %

double fpMoveInc = 0.02; //Multiplier for how much to move each keystroke in FP mode

//First person camera location
double fpX = 10;
double fpY = 1.7;
double fpZ = 2.5;

//x, y, z for refrence point in glLookAt() for FP mode
double refX = 5;
double refY = 0;
double refZ = 0;

//Texture Variables
int tMode = 0;
float texScale = 0.5;
//Light Vecotrs
float Ambient[]   = {0.01*80 ,0.01*80 ,0.01*80 ,1.0};
float Diffuse[]   = {1.0,1.0,1.0,1.0};
float Specular[]  = {0.01*0,0.01*0,0.01*0,1.0};

float mvPlayerCar = 0.0;
float mvRoad = 0.0;
float leftRightPlayer =0.0;
float leftRightEnemy =0.0;
int refreshMills = 150;
int refreshMillsEnemy = 175;
bool bulletFired = false;
GLfloat playerBulletPos = 0;
GLfloat enemyBulletPos = 0;
int counterFire = 0;
bool enemyDirection = true;
void Init(){
    textures[TEX_METAL] = LoadTexBMP("textures/basic-metal.bmp");
    textures[TEX_GLASS] = LoadTexBMP("textures/glass.bmp");
    textures[TEX_CARWHEEL] = LoadTexBMP("textures/car-wheel.bmp");
    textures[TEX_TIRETREAD] = LoadTexBMP("textures/tire-tread.bmp");
    textures[TEX_CARGRILL] = LoadTexBMP("textures/car-grill.bmp");
    textures[TEX_HEADLAMP] = LoadTexBMP("textures/headlamp.bmp");
    textures[TEX_CARBONFIBER] = LoadTexBMP("textures/carbon-fiber.bmp");
    textures[TEX_SIDEWALK] = LoadTexBMP("textures/sidewalk.bmp");
    textures[TEX_GARAGEDOOR] = LoadTexBMP("textures/garage-door.bmp");
    textures[TEX_WALKWAY] = LoadTexBMP("textures/walkway.bmp");
    textures[TEX_HEDGE] = LoadTexBMP("textures/hedge.bmp");
    textures[TEX_GRASS] = LoadTexBMP("textures/grass.bmp");
    textures[TEX_GREYBRICK] = LoadTexBMP("textures/grey-brick.bmp");
    textures[TEX_WOODBEAM] = LoadTexBMP("textures/wood-beam.bmp");
    textures[TEX_FRONTDOOR] = LoadTexBMP("textures/front-door-2.bmp");
    textures[TEX_WINDOW] = LoadTexBMP("textures/window-1.bmp");
    textures[TEX_SKYBOXFRONT] = LoadTexBMP("textures/skybox-front.bmp");
    textures[TEX_SKYBOXBACK] = LoadTexBMP("textures/skybox-back.bmp");
    textures[TEX_SKYBOXRIGHT] = LoadTexBMP("textures/skybox-right.bmp");
    textures[TEX_SKYBOXLEFT] = LoadTexBMP("textures/skybox-left.bmp");
    textures[TEX_SKYBOXTOP] = LoadTexBMP("textures/skybox-top.bmp");
    textures[TEX_ASPALTH] = LoadTexBMP("textures/asphalt.bmp");
    textures[TEX_WOODFENCE] = LoadTexBMP("textures/wood-fence.bmp");
    textures[TEX_BROWNBRICK] = LoadTexBMP("textures/brown-brick.bmp");
    textures[TEX_WHITEBRICK] = LoadTexBMP("textures/white-brick.bmp");
    textures[TEX_METALROOF] = LoadTexBMP("textures/metal-roof.bmp");
    textures[TEX_WAREHOUSEWINDOW] = LoadTexBMP("textures/warehouse-window.bmp");
    textures[TEX_CHINDERBLOCK] = LoadTexBMP("textures/cinder-block.bmp");
    textures[TEX_DESERT] = LoadTexBMP("textures/sand.bmp");
}
void PlayerTimer(int val){
	if(bulletFired){
        if(playerBulletPos<=30){
		playerBulletPos = playerBulletPos + 0.5;
        }else{
            bulletFired = false;
            playerBulletPos = 0;
        }
	}
	glutPostRedisplay();
   glutTimerFunc(refreshMills, PlayerTimer, 0);
}
void EnemyTimer(int val){
    if(leftRightEnemy >= 1.5){ //Left
		enemyDirection = false;
	}
	if(leftRightEnemy <= -2){ //Right
		enemyDirection = true;
	}
    if(enemyDirection){
		leftRightEnemy += 0.05;
	}else{
		leftRightEnemy -= 0.05;
	}
    // if(enemyBulletPos < mvPlayerCar){
    //     counterFire++;
    // }
    
    // if(enemyBulletPos > -30){
    //     if(mvPlayerCar>= 5.5){
    //         counterFire++;
    //     }
    //     enemyBulletPos -= 0.5;
    // }else{
    //     enemyBulletPos = 0;
    // }
    // std::cout<<"counter :"<<counterFire<<std::endl;
    // mvPlayerCar += 0.05;
	glutPostRedisplay();
    glutTimerFunc(refreshMillsEnemy, EnemyTimer, 0);
}

static void cube(double x,double y,double z,
                 double dx,double dy,double dz,
                 double th)
{
    //  Save transformation
    glPushMatrix();
    //  Offset, scale and rotate
    glTranslated(x,y,z);
    glRotated(th,0,1,0);
    glScaled(dx,dy,dz);

    //Texture repitition values
    float texRepX = 1.0;
    float texRepY = 1.0;

    //  Cube
    glBegin(GL_QUADS);
    //  Front
    texRepX = dx/texScale;
    texRepY = dy/texScale;
    glNormal3f( 0, 0, 1);
    glTexCoord2f(0.0,0.0); glVertex3f(-1,-1, 1);
    glTexCoord2f(texRepX,0.0); glVertex3f(+1,-1, 1);
    glTexCoord2f(texRepX,texRepY); glVertex3f(+1,+1, 1);
    glTexCoord2f(0.0,texRepY); glVertex3f(-1,+1, 1);
    //  Back
    texRepX = dx/texScale;
    texRepY = dy/texScale;
    glNormal3f( 0, 0,-1);
    glTexCoord2f(0.0,0.0); glVertex3f(+1,-1,-1);
    glTexCoord2f(texRepX,0.0); glVertex3f(-1,-1,-1);
    glTexCoord2f(texRepX,texRepY); glVertex3f(-1,+1,-1);
    glTexCoord2f(0.0,texRepY); glVertex3f(+1,+1,-1);
    //  Right
    texRepX = dz/texScale;
    texRepY = dy/texScale;
    glNormal3f(+1, 0, 0);
    glTexCoord2f(0.0,0.0); glVertex3f(+1,-1,+1);
    glTexCoord2f(texRepX,0.0); glVertex3f(+1,-1,-1);
    glTexCoord2f(texRepX,texRepY); glVertex3f(+1,+1,-1);
    glTexCoord2f(0.0,texRepY); glVertex3f(+1,+1,+1);
    //  Left
    texRepX = dz/texScale;
    texRepY = dy/texScale;
    glNormal3f(-1, 0, 0);
    glTexCoord2f(0.0,0.0); glVertex3f(-1,-1,-1);
    glTexCoord2f(texRepX,0.0); glVertex3f(-1,-1,+1);
    glTexCoord2f(texRepX,texRepY); glVertex3f(-1,+1,+1);
    glTexCoord2f(0.0,texRepY); glVertex3f(-1,+1,-1);
    //  Top
    texRepX = dx/texScale;
    texRepY = dz/texScale;
    glNormal3f( 0,+1, 0);
    glTexCoord2f(0.0,0.0); glVertex3f(-1,+1,+1);
    glTexCoord2f(texRepX,0.0); glVertex3f(+1,+1,+1);
    glTexCoord2f(texRepX,texRepY); glVertex3f(+1,+1,-1);
    glTexCoord2f(0.0,texRepY); glVertex3f(-1,+1,-1);
    //  Bottom
    texRepX = dx/texScale;
    texRepY = dz/texScale;
    glNormal3f( 0,-one, 0);
    glTexCoord2f(0.0,0.0); glVertex3f(-1,-1,-1);
    glTexCoord2f(texRepX,0.0); glVertex3f(+1,-1,-1);
    glTexCoord2f(texRepX,texRepY); glVertex3f(+1,-1,+1);
    glTexCoord2f(0.0,texRepY); glVertex3f(-1,-1,+1);
    //  End
    glEnd();
    //  Undo transofrmations
    glPopMatrix();
}
/*
 *  Draw vertex in polar coordinates with normal
 */
static void Vertex(double th,double ph)
{
    double x = Sin(th)*Cos(ph);
    double y = Cos(th)*Cos(ph);
    double z =         Sin(ph);
    //  For a sphere at the origin, the position
    //  and normal vectors are the same
    glNormal3d(x,y,z);
    glVertex3d(x,y,z);
}

/*
 *  Draw a ball
 *     at (x,y,z)
 *     radius (r)
 */
static void ball(double x,double y,double z,double r)
{
    int th,ph;
    float yellow[] = {1.0,1.0,0.0,1.0};
    float Emission[]  = {1.0,1.0,1.0,1.0};
    //  Save transformation
    glPushMatrix();
    //  Offset, scale and rotate
    glTranslated(x,y,z);
    glScaled(r,r,r);
    //  White ball
    glColor3f(1,1,0.9);
    glMaterialf(GL_FRONT,GL_SHININESS,shiny);
    glMaterialfv(GL_FRONT,GL_SPECULAR,yellow);
    glMaterialfv(GL_FRONT,GL_EMISSION,Emission);
    //  Bands of latitude
    for (ph=-90;ph<90;ph+=inc)
    {
        glBegin(GL_QUAD_STRIP);
        for (th=0;th<=360;th+=2*inc)
        {
            Vertex(th,ph);
            Vertex(th,ph+inc);
        }
        glEnd();
    }
    //  Undo transofrmations
    glPopMatrix();
}
void DrawBullet(double x, double y, double z){
	glPushMatrix();
	glColor3f(0,0,0);
    ball(x,y,z,0.2);
    // cube(8-playerBulletPos,0.2,2.5+leftRightPlayer, 0.2,0.2,0.2, 45);
	glPopMatrix();
}
/*
 *  Draw a section of the car body
 *     at (x,y,z)
 *     dimensions (dx,dy,dz)
 *     rotated th about the y axis
 *     w (1 to color windows for car body, 0 otherwise)
 */
static void body(double x,double y,double z,
                 double dx,double dy,double dz,
                 double th,
                 int w)
{
    //  Set specular color to white
    float white[] = {1,1,1,1};
    float black[] = {0,0,0,1};
    glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,shiny);
    glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,white);
    glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,black);

    glBindTexture(GL_TEXTURE_2D,textures[TEX_METAL]);
    texScale = 0.1;

    glEnable(GL_POLYGON_OFFSET_FILL);

    //  Save transformation
    glPushMatrix();
    //  Offset
    glTranslated(x,y,z);
    glRotated(th,0,1,0);
    glScaled(dx,dy,dz);

    //Texture repitition values
    float texRepX = 1.0;
    float texRepY = 1.0;

    //  Cube
    glBegin(GL_QUADS);

    //  Top
    texRepX = dx/texScale;
    texRepY = dz/texScale;
    glNormal3f( 0,+1, 0);
    glTexCoord2f(0.0,0.0); glVertex3f(-1,+1,+1);
    glTexCoord2f(texRepX,0.0); glVertex3f(+1,+1,+1);
    glTexCoord2f(texRepX,texRepY); glVertex3f(+1,+1,-1);
    glTexCoord2f(0.0,texRepY); glVertex3f(-1,+1,-1);
    //  Bottom
    texRepX = dx/texScale;
    texRepY = dz/texScale;
    glNormal3f( 0,-one, 0);
    glTexCoord2f(0.0,0.0); glVertex3f(-1,-1,-1);
    glTexCoord2f(texRepX,0.0); glVertex3f(+1,-1,-1);
    glTexCoord2f(texRepX,texRepY); glVertex3f(+1,-1,+1);
    glTexCoord2f(0.0,texRepY); glVertex3f(-1,-1,+1);

    //  Front
    texRepX = dx/texScale;
    texRepY = dy/texScale;
    glNormal3f( 0, 0, 1);
    glTexCoord2f(0.0,0.0); glVertex3f(-1,-1, 1);
    glTexCoord2f(texRepX,0.0); glVertex3f(+1,-1, 1);
    glTexCoord2f(texRepX,texRepY); glVertex3f(+1,+1, 1);
    glTexCoord2f(0.0,texRepY); glVertex3f(-1,+1, 1);
    //  Back
    texRepX = dx/texScale;
    texRepY = dy/texScale;
    glNormal3f( 0, 0,-1);
    glTexCoord2f(0.0,0.0); glVertex3f(+1,-1,-1);
    glTexCoord2f(texRepX,0.0); glVertex3f(-1,-1,-1);
    glTexCoord2f(texRepX,texRepY); glVertex3f(-1,+1,-1);
    glTexCoord2f(0.0,texRepY); glVertex3f(+1,+1,-1);

    //  End
    glEnd();

    glDisable(GL_POLYGON_OFFSET_FILL);
    //Color and texture to add windows
    if(w == 1) {
        glColor3f(0.8, 0.8, 1);
        glBindTexture(GL_TEXTURE_2D,textures[TEX_GLASS]);
        texRepX = 1.0;
        texRepY = 1.0;
        glBegin(GL_QUADS);
        //  Front
        glNormal3f(0, 0, 1);
        glTexCoord2f(0.0,0.0); glVertex3f(-0.8,-1, 1);
        glTexCoord2f(texRepX,0.0); glVertex3f(+0.8,-1, 1);
        glTexCoord2f(texRepX,texRepY); glVertex3f(+0.8,+1, 1);
        glTexCoord2f(0.0,texRepY); glVertex3f(-0.8,+1, 1);
        //  Back
        glNormal3f(0, 0,-1);
        glTexCoord2f(0.0,0.0); glVertex3f(+0.8,-1,-1);
        glTexCoord2f(texRepX,0.0); glVertex3f(-0.8,-1,-1);
        glTexCoord2f(texRepX,texRepY); glVertex3f(-0.8,+1,-1);
        glTexCoord2f(0.0,texRepY); glVertex3f(+0.8,+1,-1);
        glEnd();
    }
    glEnable(GL_POLYGON_OFFSET_FILL);

    //  Undo transformations
    glPopMatrix();
}

static void wheel(double x,double y,double z,
                  double dx,double dy,double dz,
                  double th,
                  int d,
                  int s)
{
    //  Set specular color to white
    float white[] = {1,1,1,1};
    float black[] = {0,0,0,1};
    //Turn off shininess for the rubber tire
    glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,0);
    glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,white);
    glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,black);

    //  Save transformation
    glPushMatrix();
    //  Offset
    glTranslated(x,y,z);
    glRotated(th,0,1,0);
    glScaled(dx,dy,dz);

    glBindTexture(GL_TEXTURE_2D,textures[TEX_CARWHEEL]);

    glColor3f(0.8,0.8,0.8);
    //Tire
    glBegin(GL_TRIANGLE_FAN);
    glNormal3f(0, 0, -1);
    glTexCoord2f(0.5,0.5);
    glVertex3f(0, 0, -0.05);
    for (th=0;th<=360;th+=s)
    {
        double ph = d-90;
        glTexCoord2f(0.5*Cos(th)+0.5,0.5*Sin(th)+0.5);
        glVertex3d(Sin(th)*Cos(ph), Cos(th)*Cos(ph), -0.05);
    }
    glEnd();

    glBegin(GL_TRIANGLE_FAN);
    glNormal3f(0, 0, 1);
    glTexCoord2f(0.5,0.5);
    glVertex3f(0, 0, 0.05);
    for (th=360;th>=0;th-=s)
    {
        double ph = d-90;
        glTexCoord2f(0.5*Cos(th)+0.5,0.5*Sin(th)+0.5);
        glVertex3d(Sin(th)*Cos(ph) , Cos(th)*Cos(ph), 0.05);
    }
    glEnd();

    glBindTexture(GL_TEXTURE_2D,textures[TEX_TIRETREAD]);

    glColor3f(0.5,0.5,0.55);
    glBegin(GL_QUAD_STRIP);
    for (th=0;th<=360;th+=s)
    {
        double ph = d-90;
        glNormal3f(Sin(th)*Cos(ph), Cos(th)*Cos(ph), 0);
        glTexCoord2f(0,0.1*th); glVertex3d(Sin(th)*Cos(ph), Cos(th)*Cos(ph), -0.05);
        glTexCoord2f(1,0.1*th); glVertex3d(Sin(th)*Cos(ph), Cos(th)*Cos(ph), 0.05);
    }
    // glNormal3f(Sin(0)*Cos(-90), Cos(0)*Cos(-90), 0);
    // glVertex3d(Sin(0)*Cos(-90), Cos(0)*Cos(-90), -0.05);
    // glVertex3d(Sin(0)*Cos(-90), Cos(0)*Cos(-90), 0.05);
    glEnd();

    //  Undo transformations
    glPopMatrix();
}

static void bumper(double x,double y,double z,
                   double dx,double dy,double dz,
                   double th,
                   int m)
{
    //  Set specular color to white
    float white[] = {1,1,1,1};
    float black[] = {0,0,0,1};
    glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,shiny);
    glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,white);
    glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,black);

    //  Save transformation
    glPushMatrix();
    //  Offset
    glTranslated(x,y,z);
    glRotated(th,0,1,0);
    glScaled(dx,dy,dz);

    //Texture repitition values
    float texRepX = 1.0;
    float texRepY = 1.0;

    glBindTexture(GL_TEXTURE_2D,textures[TEX_METAL]);
    texScale = 0.1;

    //Offset the bumper so that the lights and grill are drawn directly on the surface
    glEnable(GL_POLYGON_OFFSET_FILL);

    //Bumper

    //Base
    texRepX = dx/texScale;
    texRepY = dy/texScale;
    glBegin(GL_POLYGON);
    glNormal3f(0, -1, 0);
    glTexCoord2f(0.0,0.0); glVertex3f(0,0,0.4);
    glTexCoord2f(texRepX,0.0); glVertex3f(0,0,-0.4);
    glTexCoord2f(texRepX,texRepY); glVertex3f(0.1,0,-0.35);
    glTexCoord2f(0.0,texRepY); glVertex3f(0.1,0,0.35);
    glEnd();

    //Front Panels
    glBegin(GL_QUADS);
    texRepX = dx/texScale;
    texRepY = dy/texScale;
    glNormal3f(0.447214, 0, 0.894427);
    glTexCoord2f(0.0,0.0); glVertex3f(0.1, 0, 0.35);
    glTexCoord2f(texRepX,0.0); glVertex3f(0.1, 0.2, 0.35);
    glTexCoord2f(texRepX,texRepY); glVertex3f(0, 0.2, 0.4);
    glTexCoord2f(0.0,texRepY); glVertex3f(0, 0, 0.4);

    texRepX = dx/texScale;
    texRepY = dy/texScale;
    glNormal3f(1, 0, 0);
    glTexCoord2f(0.0,0.0); glVertex3f(0.1, 0, -0.35);
    glTexCoord2f(texRepX,0.0); glVertex3f(0.1, 0.2, -0.35);
    glTexCoord2f(texRepX,texRepY); glVertex3f(0.1, 0.2, 0.35);
    glTexCoord2f(0.0,texRepY); glVertex3f(0.1, 0, 0.35);

    texRepX = dx/texScale;
    texRepY = dy/texScale;
    glNormal3f(0.447214, 0, -0.894427);
    glTexCoord2f(0.0,0.0); glVertex3f(0.1, 0, -0.35);
    glTexCoord2f(texRepX,0.0); glVertex3f(0, 0, -0.4);
    glTexCoord2f(texRepX,texRepY); glVertex3f(0, 0.2, -0.4);
    glTexCoord2f(0.0,texRepY); glVertex3f(0.1, 0.2, -0.35);

    glEnd();

    //Upper Bumper
    glBegin(GL_QUADS);
    texRepX = dx/texScale;
    texRepY = dy/texScale;
    glNormal3f(0.447214, 0.894427, 0);
    glTexCoord2f(0.0,0.0); glVertex3f(0, 0.25, 0.35);
    glTexCoord2f(texRepX,0.0); glVertex3f(0.1, 0.2, 0.35);
    glTexCoord2f(texRepX,texRepY); glVertex3f(0.1, 0.2, -0.35);
    glTexCoord2f(0.0,texRepY); glVertex3f(0, 0.25, -0.35);
    glEnd();

    glBegin(GL_TRIANGLES);
    texRepX = dx/texScale;
    texRepY = dy/texScale;
    glNormal3f(0.333333, 0.666667, 0.666667);
    glTexCoord2f(0.0, 0.0); glVertex3f(0, 0.2, 0.4);
    glTexCoord2f(texRepX/2, texRepY); glVertex3f(0.1, 0.2, 0.35);
    glTexCoord2f(texRepX, 0.0); glVertex3f(0, 0.25, 0.35);

    texRepX = dx/texScale;
    texRepY = dy/texScale;
    glNormal3f(0.333333, 0.666667, -0.666667);
    glTexCoord2f(0.0, 0.0); glVertex3f(0, 0.25, -0.35);
    glTexCoord2f(texRepX/2, texRepY); glVertex3f(0.1, 0.2, -0.35);
    glTexCoord2f(texRepX, 0.0); glVertex3f(0, 0.2, -0.4);
    glEnd();

    //  Disable polygon offset
    glDisable(GL_POLYGON_OFFSET_FILL);

    if (m == 1) {
        glColor3f(0.2,0.2,0.2);
        glBindTexture(GL_TEXTURE_2D,textures[TEX_CARGRILL]);

        //Grill
        glBegin(GL_QUADS);
        glNormal3f(1, 0, 0);
        glTexCoord2f(0.0,0.0); glVertex3f(0.1, 0.15, 0.18);
        glTexCoord2f(0.5,0.0); glVertex3f(0.1, 0.03, 0.18);
        glTexCoord2f(0.5,1.0); glVertex3f(0.1, 0.03, -0.18);
        glTexCoord2f(0.0,1.0); glVertex3f(0.1, 0.15, -0.18);
        glEnd();
    }

    //Lights (taillights or headlights)
    float emColor[4];
    if(m == 1) {
        emColor[0] = 1.0 * emission;
        emColor[1] = 1.0 * emission;
        emColor[2] = 0.8 * emission;
        emColor[3] = 1.0 * emission;
        glColor3f(1, 1, 0.8);
    } else {
        emColor[0] = 0.8 * emission;
        emColor[1] = 0.0 * emission;
        emColor[2] = 0.0 * emission;
        emColor[3] = 1.0 * emission;
        glColor3f(.8, 0, 0);
    }

    glMaterialf(GL_FRONT,GL_SHININESS,0);
    glMaterialfv(GL_FRONT,GL_SPECULAR,emColor);
    glMaterialfv(GL_FRONT,GL_EMISSION,emColor);

    glBindTexture(GL_TEXTURE_2D,textures[TEX_HEADLAMP]);

    glBegin(GL_TRIANGLE_FAN);
    glNormal3f(1, 0, 0);
    glTexCoord2f(0.5,0.5); glVertex3f(0.1, 0.13, -0.25);
    for (th=0;th<=360;th+=10)
    {
        double ph = 3-90;
        glTexCoord2f(0.5*Cos(th)+0.5,0.5*Sin(th)+0.5);
        glVertex3d(0.1, 0.13+(Cos(th)*Cos(ph)), -0.25+(Sin(th)*Cos(ph)));
    }
    glEnd();

    glBegin(GL_TRIANGLE_FAN);
    glNormal3f(1, 0, 0);
    glTexCoord2f(0.5,0.5); glVertex3f(0.1, 0.13, 0.25);
    for (th=0;th<=360;th+=10)
    {
        double ph = 3-90;
        glTexCoord2f(0.5*Cos(th)+0.5,0.5*Sin(th)+0.5);
        glVertex3d(0.1, 0.13+(Cos(th)*Cos(ph)), 0.25+(Sin(th)*Cos(ph)));
    }
    glEnd();

    glEnable(GL_POLYGON_OFFSET_FILL);

    glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,shiny);
    glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,white);
    glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,black);

    //Undo transformations
    glPopMatrix();
}
static void car(double x,double y,double z,
                double dx,double dy,double dz,
                double th,
                float cr, float cb, float cg)
{
    //  Set specular color to white
    float white[] = {1,1,1,1};
    float black[] = {0,0,0,1};
    glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,shiny);
    glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,white);
    glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,black);

    //  Save transformation
    glPushMatrix();
    //  Offset
    glTranslated(x,y,z);
    glRotated(th,0,1,0);
    glScaled(dx,dy,dz);

    glPolygonOffset(1,1);

    wheel(0.6,0,0.4, 1,1,1, 0, 8, 10);
    wheel(-0.6,0,-0.4, 1,1,1, 0, 8, 10);
    wheel(0.6,0,-0.4, 1,1,1, 0, 8, 10);
    wheel(-0.6,0,0.4, 1,1,1, 0, 8, 10);

    glColor3f(cr, cb, cg);

    //Lower Body
    body(0,0.1,0, 0.8,0.1,0.4, 0, 0);
    //Cabin
    body(-0.1,0.3,0, 0.3,0.1,0.35, 0, 1);

    texScale = 1.0;

    glColor3f(cr, cb, cg);

    //Front Bumper
    bumper(0.8,0,0, 1,1,1, 0, 1);

    glColor3f(cr, cb, cg);

    //Rear Bumper
    bumper(-0.8,0,0, 1,1,1, 180, 0);

    //  Set specular color to white
    glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,shiny);
    glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,white);
    glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,black);

    glEnable(GL_POLYGON_OFFSET_FILL);

    glColor3f(cr, cb, cg);

    glBindTexture(GL_TEXTURE_2D,textures[TEX_METAL]);

    //Texture repitition values
    float texRepX = 1.0;
    float texRepY = 1.0;

    //Hood and upper side pannels
    texRepX = dx/texScale;
    texRepY = dz/texScale;
    glBegin(GL_QUADS);
    glNormal3f(0, 0.707107, 0.707107);
    glTexCoord2f(0.0,0.0); glVertex3f(-0.8, 0.25, 0.35);
    glTexCoord2f(texRepX,0.0); glVertex3f(-0.8, 0.2, 0.4);
    glTexCoord2f(texRepX,texRepY); glVertex3f(0.8, 0.2, 0.4);
    glTexCoord2f(0.0,texRepY); glVertex3f(0.8, 0.25, 0.35);

    glNormal3f(0, 1, 0);
    glTexCoord2f(0.0,0.0); glVertex3f(0.4, 0.25, 0.35);
    glTexCoord2f(texRepX,0.0); glVertex3f(0.8, 0.25, 0.35);
    glTexCoord2f(texRepX,texRepY); glVertex3f(0.8, 0.25, -0.35);
    glTexCoord2f(0.0,texRepY); glVertex3f(0.4, 0.25, -0.35);

    glNormal3f(0, 0.707107, -0.707107);
    glTexCoord2f(0.0,0.0); glVertex3f(-0.8, 0.2, -0.4);
    glTexCoord2f(texRepX,0.0); glVertex3f(-0.8, 0.25, -0.35);
    glTexCoord2f(texRepX,texRepY); glVertex3f(0.8, 0.25, -0.35);
    glTexCoord2f(0.0,texRepY); glVertex3f(0.8, 0.2, -0.4);
    glEnd();

    //Trunk
    texRepX = dx/texScale;
    texRepY = dz/texScale;
    glBegin(GL_QUADS);
    glNormal3f(0,1,0);
    glTexCoord2f(0.0,0.0); glVertex3f(-0.8, 0.25, -0.35);
    glTexCoord2f(texRepX,0.0); glVertex3f(-0.8, 0.25, 0.35);
    glTexCoord2f(texRepX,texRepY); glVertex3f(-0.6, 0.25, 0.35);
    glTexCoord2f(0.0,texRepY); glVertex3f(-0.6, 0.25, -0.35);
    glEnd();

    glBindTexture(GL_TEXTURE_2D,textures[TEX_GLASS]);

    glColor3f(0.8, 0.8, 1);

    //Windshield
    texRepX = 1.0;
    texRepY = 1.0;
    glBegin(GL_QUADS);
    glNormal3f(0.6, 0.8, 0);
    glTexCoord2f(0.0,0.0); glVertex3f(0.4,0.25,0.35);
    glTexCoord2f(texRepX,0.0); glVertex3f(0.4,0.25,-0.35);
    glTexCoord2f(texRepX,texRepY); glVertex3f(0.2,0.4,-0.35);
    glTexCoord2f(0.0,texRepY); glVertex3f(0.2,0.4,0.35);
    glEnd();

    glBegin(GL_TRIANGLES);
    glNormal3f(0,0,1);
    glTexCoord2f(0.0,0.0); glVertex3f(0.2,0.4,0.35);
    glTexCoord2f(texRepX, 0.0); glVertex3f(0.2,0.25,0.35);
    glTexCoord2f(texRepX, texRepY); glVertex3f(0.4,0.25,0.35);

    glNormal3f(0,0,-1);
    glTexCoord2f(0.0,0.0); glVertex3f(0.4,0.25,-0.35);
    glTexCoord2f(texRepX, 0.0); glVertex3f(0.2,0.25,-0.35);
    glTexCoord2f(texRepX, texRepY); glVertex3f(0.2,0.4,-0.35);
    glEnd();

    //Rear Window
    texRepX = 1.0;
    texRepY = 1.0;
    glBegin(GL_QUADS);
    glNormal3f(-0.6, 0.8, 0);
    glTexCoord2f(0.0,0.0); glVertex3f(-0.6,0.25,-0.35);
    glTexCoord2f(texRepX,0.0); glVertex3f(-0.6,0.25,0.35);
    glTexCoord2f(texRepX,texRepY); glVertex3f(-0.4,0.4,0.35);
    glTexCoord2f(0.0,texRepY); glVertex3f(-0.4,0.4,-0.35);
    glEnd();

    glBegin(GL_TRIANGLES);
    glNormal3f(0,0,1);
    glTexCoord2f(0.0,0.0); glVertex3f(-0.6,0.25,0.35);
    glTexCoord2f(texRepX, 0.0); glVertex3f(-0.4,0.25,0.35);
    glTexCoord2f(texRepX, texRepY); glVertex3f(-0.4,0.4,0.35);

    glNormal3f(0,0,-1);
    glTexCoord2f(0.0,0.0); glVertex3f(-0.4,0.4,-0.35);
    glTexCoord2f(texRepX, 0.0); glVertex3f(-0.4,0.25,-0.35);
    glTexCoord2f(texRepX, texRepY); glVertex3f(-0.6,0.25,-0.35);
    glEnd();

    glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,shiny);
    glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,white);
    glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,black);

    glBindTexture(GL_TEXTURE_2D,textures[TEX_CARBONFIBER]);

    //Spoiler
    glColor3f(0.3,0.3,0.3);
    cube(-0.75,0.28,0.3, 0.02,0.03,0.02, 0);
    cube(-0.75,0.28,-0.3, 0.02,0.03,0.02, 0);

    texRepX = 5.0;
    texRepY = 1.0;

    glBegin(GL_QUADS);
    glNormal3f(0, -1, 0);
    glTexCoord2f(0.0,0.0); glVertex3f(-0.7,0.31,-0.35);
    glTexCoord2f(texRepX,0.0); glVertex3f(-0.7,0.31,0.35);
    glTexCoord2f(texRepX,texRepY); glVertex3f(-0.8,0.31,0.35);
    glTexCoord2f(0.0,texRepY); glVertex3f(-0.8,0.31,-0.35);

    glNormal3f(0.196116, 0.980581, 0);
    glTexCoord2f(0.0,0.0); glVertex3f(-0.8,0.33,-0.35);
    glTexCoord2f(texRepX,0.0); glVertex3f(-0.8,0.33,0.35);
    glTexCoord2f(texRepX,texRepY); glVertex3f(-0.7,0.31,0.35);
    glTexCoord2f(0.0,texRepY); glVertex3f(-0.7,0.31,-0.35);

    texRepX = 5.0;
    texRepY = 0.2;
    glNormal3f(-1, 0, 0);
    glTexCoord2f(0.0,0.0); glVertex3f(-0.8,0.33,0.35);
    glTexCoord2f(texRepX,0.0); glVertex3f(-0.8,0.33,-0.35);
    glTexCoord2f(texRepX,texRepY); glVertex3f(-0.8,0.31,-0.35);
    glTexCoord2f(0.0,texRepY); glVertex3f(-0.8,0.31,0.35);

    glEnd();

    glBindTexture(GL_TEXTURE_2D,textures[TEX_METAL]);
    glColor3f(cr, cb, cg);

    //Spoiler Fins
    texRepX = dx/texScale;
    texRepY = dy/texScale;
    glBegin(GL_TRIANGLES);
    glNormal3f(0,0,-1);
    glTexCoord2f(0.0,0.0); glVertex3f(-0.68,0.31,-0.35);
    glTexCoord2f(texRepX, 0.0); glVertex3f(-0.82,0.31,-0.35);
    glTexCoord2f(texRepX, texRepY); glVertex3f(-0.82,0.35,-0.35);

    glNormal3f(0,0,1);
    glTexCoord2f(0.0,0.0); glVertex3f(-0.82,0.35,0.35);
    glTexCoord2f(texRepX, 0.0); glVertex3f(-0.82,0.31,0.35);
    glTexCoord2f(texRepX, texRepY); glVertex3f(-0.68,0.31,0.35);

    //Duplicate to draw both sides (with inverted normals) when face culling is on
    glNormal3f(0,0,1);
    glTexCoord2f(0.0,0.0); glVertex3f(-0.68,0.31,-0.35);
    glTexCoord2f(texRepX, 0.0); glVertex3f(-0.82,0.31,-0.35);
    glTexCoord2f(texRepX, texRepY); glVertex3f(-0.82,0.35,-0.35);

    glNormal3f(0,0,-1);
    glTexCoord2f(0.0,0.0); glVertex3f(-0.82,0.35,0.35);
    glTexCoord2f(texRepX, 0.0); glVertex3f(-0.82,0.31,0.35);
    glTexCoord2f(texRepX, texRepY); glVertex3f(-0.68,0.31,0.35);

    glEnd();

    //Undo transformations
    glPopMatrix();
}
static void policeCar(double x,double y,double z,
                      double dx,double dy,double dz,
                      double th)
{
    //  Set specular color to white
    float white[] = {1,1,1,1};
    float black[] = {0,0,0,1};
    glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,shiny);
    glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,white);
    glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,black);

    float cr = 0.1;
    float cb = 0.1;
    float cg = 0.1;

    //  Save transformation
    glPushMatrix();
    //  Offset
    glTranslated(x,y,z);
    glRotated(th,0,1,0);
    glScaled(dx,dy,dz);

    glPolygonOffset(1,1);

    wheel(0.6,0,0.4, 1,1,1, 0, 8, 10);
    wheel(-0.6,0,-0.4, 1,1,1, 0, 8, 10);
    wheel(0.6,0,-0.4, 1,1,1, 0, 8, 10);
    wheel(-0.6,0,0.4, 1,1,1, 0, 8, 10);

    glColor3f(cr, cb, cg);

    //Lower Body
    body(0,0.1,0, 0.8,0.1,0.4, 0, 0);
    //Cabin
    glColor3f(cr, cb, cg);
    body(0,0.3,0, 0.2,0.1,0.35, 0, 1);
    glColor3f(cr, cb, cg);
    body(-0.4,0.3,0, 0.2,0.1,0.35, 0, 1);

    texScale = 1.0;

    glColor3f(cr, cb, cg);

    //Front Bumper
    bumper(0.8,0,0, 1,1,1, 0, 1);

    glColor3f(cr, cb, cg);

    //Rear Bumper
    bumper(-0.8,0,0, 1,1,1, 180, 0);

    //  Set specular color to white
    glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,shiny);
    glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,white);
    glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,black);

    glEnable(GL_POLYGON_OFFSET_FILL);

    glColor3f(cr, cb, cg);

    glBindTexture(GL_TEXTURE_2D,textures[TEX_METAL]);

    //Texture repitition values
    float texRepX = 1.0;
    float texRepY = 1.0;

    //Hood and upper side pannels
    texRepX = dx/texScale;
    texRepY = dz/texScale;
    glBegin(GL_QUADS);
    glNormal3f(0, 0.707107, 0.707107);
    glTexCoord2f(0.0,0.0); glVertex3f(-0.8, 0.25, 0.35);
    glTexCoord2f(texRepX,0.0); glVertex3f(-0.8, 0.2, 0.4);
    glTexCoord2f(texRepX,texRepY); glVertex3f(0.8, 0.2, 0.4);
    glTexCoord2f(0.0,texRepY); glVertex3f(0.8, 0.25, 0.35);

    glNormal3f(0, 1, 0);
    glTexCoord2f(0.0,0.0); glVertex3f(0.4, 0.25, 0.35);
    glTexCoord2f(texRepX,0.0); glVertex3f(0.8, 0.25, 0.35);
    glTexCoord2f(texRepX,texRepY); glVertex3f(0.8, 0.25, -0.35);
    glTexCoord2f(0.0,texRepY); glVertex3f(0.4, 0.25, -0.35);

    glNormal3f(0, 0.707107, -0.707107);
    glTexCoord2f(0.0,0.0); glVertex3f(-0.8, 0.2, -0.4);
    glTexCoord2f(texRepX,0.0); glVertex3f(-0.8, 0.25, -0.35);
    glTexCoord2f(texRepX,texRepY); glVertex3f(0.8, 0.25, -0.35);
    glTexCoord2f(0.0,texRepY); glVertex3f(0.8, 0.2, -0.4);
    glEnd();

    glBindTexture(GL_TEXTURE_2D,textures[TEX_GLASS]);

    glColor3f(0.8, 0.8, 1);

    //Windshield
    texRepX = 1.0;
    texRepY = 1.0;
    glBegin(GL_QUADS);
    glNormal3f(0.6, 0.8, 0);
    glTexCoord2f(0.0,0.0); glVertex3f(0.4,0.25,0.35);
    glTexCoord2f(texRepX,0.0); glVertex3f(0.4,0.25,-0.35);
    glTexCoord2f(texRepX,texRepY); glVertex3f(0.2,0.4,-0.35);
    glTexCoord2f(0.0,texRepY); glVertex3f(0.2,0.4,0.35);
    glEnd();

    glBegin(GL_TRIANGLES);
    glNormal3f(0,0,1);
    glTexCoord2f(0.0,0.0); glVertex3f(0.2,0.4,0.35);
    glTexCoord2f(texRepX, 0.0); glVertex3f(0.2,0.25,0.35);
    glTexCoord2f(texRepX, texRepY); glVertex3f(0.4,0.25,0.35);

    glNormal3f(0,0,-1);
    glTexCoord2f(0.0,0.0); glVertex3f(0.4,0.25,-0.35);
    glTexCoord2f(texRepX, 0.0); glVertex3f(0.2,0.25,-0.35);
    glTexCoord2f(texRepX, texRepY); glVertex3f(0.2,0.4,-0.35);
    glEnd();

    //Rear Window
    texRepX = 1.0;
    texRepY = 1.0;
    glBegin(GL_QUADS);
    glNormal3f(-0.6, 0.8, 0);
    glTexCoord2f(0.0,0.0); glVertex3f(-0.8,0.25,-0.35);
    glTexCoord2f(texRepX,0.0); glVertex3f(-0.8,0.25,0.35);
    glTexCoord2f(texRepX,texRepY); glVertex3f(-0.6,0.4,0.35);
    glTexCoord2f(0.0,texRepY); glVertex3f(-0.6,0.4,-0.35);
    glEnd();

    glBegin(GL_TRIANGLES);
    glNormal3f(0,0,1);
    glTexCoord2f(0.0,0.0); glVertex3f(-0.8,0.25,0.35);
    glTexCoord2f(texRepX, 0.0); glVertex3f(-0.6,0.25,0.35);
    glTexCoord2f(texRepX, texRepY); glVertex3f(-0.6,0.4,0.35);

    glNormal3f(0,0,-1);
    glTexCoord2f(0.0,0.0); glVertex3f(-0.6,0.4,-0.35);
    glTexCoord2f(texRepX, 0.0); glVertex3f(-0.6,0.25,-0.35);
    glTexCoord2f(texRepX, texRepY); glVertex3f(-0.8,0.25,-0.35);
    glEnd();

    float t = glutGet(GLUT_ELAPSED_TIME)/1000.0;

    //Light bar

    glBindTexture(GL_TEXTURE_2D,textures[TEX_GLASS]);
    //Mid section
    glColor3f(0.1, 0.1, 0.1);
    cube(-0.2,0.42,0, 0.07,0.02,0.05, 0);

    //  Enable light 1 - Police Light
    glEnable(GL_LIGHT1);

    if ((int)(t/0.5) % 2 == 0) {
        float amb[4] = {0,0,0,0};
        float dif[4] = {0.8,0,0,1};
        float spec[4] = {0,0,0,1};
        float pos[4] = {-0.2,0.26,-0.15,1.0};
        //Red Light
        glLightfv(GL_LIGHT1,GL_AMBIENT ,amb);
        glLightfv(GL_LIGHT1,GL_DIFFUSE ,dif);
        glLightfv(GL_LIGHT1,GL_SPECULAR,spec);
        glLightfv(GL_LIGHT1,GL_POSITION,pos);

        glLightf(GL_LIGHT1,GL_CONSTANT_ATTENUATION ,at0/100.0);
        glLightf(GL_LIGHT1,GL_LINEAR_ATTENUATION   ,at1/100.0);
        glLightf(GL_LIGHT1,GL_QUADRATIC_ATTENUATION,at2/100.0);

        //Red Light
        float redEm[4] = {0.8, 0, 0, 1.0};
        glMaterialf(GL_FRONT,GL_SHININESS,0);
        glMaterialfv(GL_FRONT,GL_SPECULAR,redEm);
        glMaterialfv(GL_FRONT,GL_EMISSION,redEm);
        glColor3f(0.5, 0, 0);
        cube(-0.2,0.42,-0.15, 0.07,0.02,0.1, 0);
        //Blue Light
        glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,shiny);
        glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,white);
        glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,black);
        glColor3f(0, 0, 0.5);
        cube(-0.2,0.42,0.15, 0.07,0.02,0.1, 0);
    } else {
        float amb[4] = {0,0,0,0};
        float dif[4] = {0,0,0.8,1};
        float spec[4] = {0,0,0,1};
        float pos[4] = {-0.2,0.26,0.15,1.0};
        //Blue Light
        glLightfv(GL_LIGHT1,GL_AMBIENT ,amb);
        glLightfv(GL_LIGHT1,GL_DIFFUSE ,dif);
        glLightfv(GL_LIGHT1,GL_SPECULAR,spec);
        glLightfv(GL_LIGHT1,GL_POSITION,pos);

        glLightf(GL_LIGHT1,GL_CONSTANT_ATTENUATION ,at0/100.0);
        glLightf(GL_LIGHT1,GL_LINEAR_ATTENUATION   ,at1/100.0);
        glLightf(GL_LIGHT1,GL_QUADRATIC_ATTENUATION,at2/100.0);

        //Red Light
        glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,shiny);
        glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,white);
        glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,black);
        glColor3f(0.5, 0, 0);
        cube(-0.2,0.42,-0.15, 0.07,0.02,0.1, 0);
        //Blue Light
        float blueEm[4] = {0, 0, 0.8, 1.0};
        glMaterialf(GL_FRONT,GL_SHININESS,0);
        glMaterialfv(GL_FRONT,GL_SPECULAR,blueEm);
        glMaterialfv(GL_FRONT,GL_EMISSION,blueEm);
        glColor3f(0, 0, 0.5);
        cube(-0.2,0.42,0.15, 0.07,0.02,0.1, 0);
    }

    glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,shiny);
    glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,white);
    glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,black);

    //Undo transformations
    glPopMatrix();
}
static void workshop(double x, double z, double th)
{
    //  Save transformation
    glPushMatrix();
    //  Offset
    glTranslated(x,0,z);
    glRotated(th,0,1,0);

    //Building - Brown Workshop
    texScale = 0.5;
    cube(0,1.6,0, 2,0.4,1, 0); //Top
    cube(-1.75,0.65,0, 0.25,0.55,1, 0); //Left
    cube(1.75,0.65,0, 0.25,0.55,1, 0); //Right
    cube(0,0.65,0, 0.2,0.55,1, 0); //Middle

    //"Floor" for brown workshop
    glColor3f(0.7, 0.7, 0.7);
    glBindTexture(GL_TEXTURE_2D,textures[TEX_SIDEWALK]);
    texScale = 1;
    cube(0,-0.05,0.9, 2,0.15,0.1, 0);

    //Garage Doors
    glColor3f(0.5, 0.5, 0.5);
    glBindTexture(GL_TEXTURE_2D,textures[TEX_GARAGEDOOR]);
    glBegin(GL_QUADS);
    float texRepX = 1.0;
    float texRepY = 1.0;
    //Left
    glNormal3f(0, 0, 1);
    glTexCoord2f(0.0,0.0); glVertex3f(-1.5, 0.1, 0.9);
    glTexCoord2f(texRepX,0.0); glVertex3f(-0.2, 0.1, 0.9);
    glTexCoord2f(texRepX,texRepY); glVertex3f(-0.2, 1.2, 0.9);
    glTexCoord2f(0.0,texRepY); glVertex3f(-1.5, 1.2, 0.9);
    //Right
    glNormal3f(0, 0, 1);
    glTexCoord2f(0.0,0.0); glVertex3f(0.2, 0.1, 0.9);
    glTexCoord2f(texRepX,0.0); glVertex3f(1.5, 0.1, 0.9);
    glTexCoord2f(texRepX,texRepY); glVertex3f(1.5, 1.2, 0.9);
    glTexCoord2f(0.0,texRepY); glVertex3f(0.2, 1.2, 0.9);
    glEnd();

    //Undo transformations
    glPopMatrix();
}

static void house(double x, double z, double th) {
    //  Save transformation
    glPushMatrix();
    //  Offset
    glTranslated(x,0,z);
    glRotated(th,0,1,0);

    glPolygonOffset(1,1);
    glEnable(GL_POLYGON_OFFSET_FILL);

    float white[] = {1,1,1,1};
    float black[] = {0,0,0,1};
    glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,shiny);
    glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,white);
    glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,black);

    //Building - Grey House
    glColor3f(0.7, 0.7, 0.7);
    glBindTexture(GL_TEXTURE_2D,textures[TEX_GREYBRICK]);
    texScale = 0.5;
    cube(0,0.9,-3, 2,0.8,1, 0);

    //Door Frame
    glColor3f(0.5, 0.5, 0.5);
    glBindTexture(GL_TEXTURE_2D,textures[TEX_WOODBEAM]);
    texScale = 0.5;
    cube(-0.4,0.65,-1.95, 0.1,0.55,0.05, 0);
    cube(0.4,0.65,-1.95, 0.1,0.55,0.05, 0);
    cube(0,1.25,-1.95, 0.5,0.05,0.05, 0);

    //Window Sills
    cube(-1.3,0.65,-1.95, 0.45,0.05,0.05, 0); //Left
    cube(1.3,0.65,-1.95, 0.45,0.05,0.05, 0); //Right

    glDisable(GL_POLYGON_OFFSET_FILL);

    //Door
    glColor3f(0.5, 0.5, 0.5);
    glBindTexture(GL_TEXTURE_2D,textures[TEX_FRONTDOOR]);
    glBegin(GL_QUADS);
    double texRepX = 1.0;
    double texRepY = 1.0;
    glNormal3f(0, 0, 1);
    glTexCoord2f(0.0,0.0); glVertex3f(-0.31, 0.1, -2);
    glTexCoord2f(texRepX,0.0); glVertex3f(0.31, 0.1, -2);
    glTexCoord2f(texRepX,texRepY); glVertex3f(0.31, 1.21, -2);
    glTexCoord2f(0.0,texRepY); glVertex3f(-0.31, 1.21, -2);
    glEnd();

    //Windows
    glColor3f(0.7, 0.7, 0.7);

    glBindTexture(GL_TEXTURE_2D,textures[TEX_WINDOW]);
    glBegin(GL_QUADS);
    texRepX = 1.0;
    texRepY = 2.0;

    //Left Window
    glNormal3f(0, 0, 1);
    glTexCoord2f(0.0,0.0); glVertex3f(-1.7, 0.7, -2);
    glTexCoord2f(texRepX,0.0); glVertex3f(-0.9, 0.7, -2);
    glTexCoord2f(texRepX,texRepY); glVertex3f(-0.9, 1.3, -2);
    glTexCoord2f(0.0,texRepY); glVertex3f(-1.7, 1.3, -2);

    //Right Window
    glNormal3f(0, 0, 1);
    glTexCoord2f(0.0,0.0); glVertex3f(0.9, 0.7, -2);
    glTexCoord2f(texRepX,0.0); glVertex3f(1.7, 0.7, -2);
    glTexCoord2f(texRepX,texRepY); glVertex3f(1.7, 1.3, -2);
    glTexCoord2f(0.0,texRepY); glVertex3f(0.9, 1.3, -2);

    glEnd();

    //Undo transformations
    glPopMatrix();
}
static void greyHouse(double x, double z, double th) {
    //  Save transformation
    glPushMatrix();
    //  Offset
    glTranslated(x,0,z);
    glRotated(th,0,1,0);

    glPolygonOffset(1,1);
    glEnable(GL_POLYGON_OFFSET_FILL);

    float white[] = {1,1,1,1};
    float black[] = {0,0,0,1};
    glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,shiny);
    glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,white);
    glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,black);

    //Walkway (to house)
    glColor3f(0.7, 0.7, 0.7);
    glBindTexture(GL_TEXTURE_2D,textures[TEX_WALKWAY]);
    texScale = 0.4;
    cube(0,-0.05,-1.5, 0.5,0.15,0.4, 90); // Between hedges

    //Hedges
    glColor3f(0, 0.3, 0.1);
    glBindTexture(GL_TEXTURE_2D,textures[TEX_HEDGE]);
    texScale = 0.25;
    cube(1.23,0.3,-1.2, 0.77,0.2,0.17, 0);
    cube(-1.23,0.3,-1.2, 0.77,0.2,0.17, 0);

    //Grass
    glColor3f(0.7, 0.7, 0.7);
    glBindTexture(GL_TEXTURE_2D,textures[TEX_GRASS]);
    texScale = 0.5;
    cube(-1.2,-0.05,-1.5, 0.8,0.15,0.5, 0);
    cube(1.2,-0.05,-1.5, 0.8,0.15,0.5, 0);

    //Building - Grey House
    glColor3f(0.7, 0.7, 0.7);
    glBindTexture(GL_TEXTURE_2D,textures[TEX_GREYBRICK]);
    texScale = 0.5;
    cube(0,0.9,-3, 2,0.8,1, 0);

    //Door Frame
    glColor3f(0.5, 0.5, 0.5);
    glBindTexture(GL_TEXTURE_2D,textures[TEX_WOODBEAM]);
    texScale = 0.5;
    cube(-0.4,0.65,-1.95, 0.1,0.55,0.05, 0);
    cube(0.4,0.65,-1.95, 0.1,0.55,0.05, 0);
    cube(0,1.25,-1.95, 0.5,0.05,0.05, 0);

    //Window Sills
    cube(-1.3,0.65,-1.95, 0.45,0.05,0.05, 0); //Left
    cube(1.3,0.65,-1.95, 0.45,0.05,0.05, 0); //Right

    glDisable(GL_POLYGON_OFFSET_FILL);

    //Door
    glColor3f(0.5, 0.5, 0.5);
    glBindTexture(GL_TEXTURE_2D,textures[TEX_FRONTDOOR]);
    glBegin(GL_QUADS);
    double texRepX = 1.0;
    double texRepY = 1.0;
    glNormal3f(0, 0, 1);
    glTexCoord2f(0.0,0.0); glVertex3f(-0.31, 0.1, -2);
    glTexCoord2f(texRepX,0.0); glVertex3f(0.31, 0.1, -2);
    glTexCoord2f(texRepX,texRepY); glVertex3f(0.31, 1.21, -2);
    glTexCoord2f(0.0,texRepY); glVertex3f(-0.31, 1.21, -2);
    glEnd();

    //Windows
    glColor3f(0.7, 0.7, 0.7);

    glBindTexture(GL_TEXTURE_2D,textures[TEX_WINDOW]);
    glBegin(GL_QUADS);
    texRepX = 1.0;
    texRepY = 2.0;

    //Left Window
    glNormal3f(0, 0, 1);
    glTexCoord2f(0.0,0.0); glVertex3f(-1.7, 0.7, -2);
    glTexCoord2f(texRepX,0.0); glVertex3f(-0.9, 0.7, -2);
    glTexCoord2f(texRepX,texRepY); glVertex3f(-0.9, 1.3, -2);
    glTexCoord2f(0.0,texRepY); glVertex3f(-1.7, 1.3, -2);

    //Right Window
    glNormal3f(0, 0, 1);
    glTexCoord2f(0.0,0.0); glVertex3f(0.9, 0.7, -2);
    glTexCoord2f(texRepX,0.0); glVertex3f(1.7, 0.7, -2);
    glTexCoord2f(texRepX,texRepY); glVertex3f(1.7, 1.3, -2);
    glTexCoord2f(0.0,texRepY); glVertex3f(0.9, 1.3, -2);

    glEnd();

    //Undo transformations
    glPopMatrix();
}
static void skybox(float dim) {
    glDisable(GL_POLYGON_OFFSET_FILL);

    //  Set specular color to white
    float white[] = {1,1,1,1};
    float black[] = {0,0,0,1};
    glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,0);
    glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,white);
    glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,black);

    glColor3f(0.7, 0.7, 0.7);
    glBindTexture(GL_TEXTURE_2D,textures[TEX_SKYBOXFRONT]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glBegin(GL_QUADS);
    glNormal3f(0, 0, -1);
    glTexCoord2f(1.0,0.0); glVertex3f(+dim,-dim, dim);
    glTexCoord2f(0.0,0.0); glVertex3f(-dim,-dim, dim);
    glTexCoord2f(0.0,1.0); glVertex3f(-dim,+dim, dim);
    glTexCoord2f(1.0,1.0); glVertex3f(+dim,+dim, dim);
    glEnd();

    glBindTexture(GL_TEXTURE_2D,textures[TEX_SKYBOXBACK]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glBegin(GL_QUADS);
    glNormal3f(0, 0, 1);
    glTexCoord2f(1.0,0.0); glVertex3f(-dim,-dim, -dim);
    glTexCoord2f(0.0,0.0); glVertex3f(+dim,-dim, -dim);
    glTexCoord2f(0.0,1.0); glVertex3f(+dim,+dim, -dim);
    glTexCoord2f(1.0,1.0); glVertex3f(-dim,+dim, -dim);
    glEnd();

    glBindTexture(GL_TEXTURE_2D,textures[TEX_SKYBOXRIGHT]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glBegin(GL_QUADS);
    glNormal3f(-1, 0, 0);
    glTexCoord2f(1.0,0.0); glVertex3f(dim,-dim, -dim);
    glTexCoord2f(0.0,0.0); glVertex3f(dim,-dim, +dim);
    glTexCoord2f(0.0,1.0); glVertex3f(dim,+dim, +dim);
    glTexCoord2f(1.0,1.0); glVertex3f(dim,+dim, -dim);
    glEnd();

    glBindTexture(GL_TEXTURE_2D,textures[TEX_SKYBOXLEFT]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glBegin(GL_QUADS);
    glNormal3f(1, 0, 0);
    glTexCoord2f(1.0,0.0); glVertex3f(-dim,-dim, +dim);
    glTexCoord2f(0.0,0.0); glVertex3f(-dim,-dim, -dim);
    glTexCoord2f(0.0,1.0); glVertex3f(-dim,+dim, -dim);
    glTexCoord2f(1.0,1.0); glVertex3f(-dim,+dim, +dim);
    glEnd();

    glBindTexture(GL_TEXTURE_2D,textures[TEX_SKYBOXTOP]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glBegin(GL_QUADS);
    glNormal3f(0, -1, 0);
    glTexCoord2f(1.0,0.0); glVertex3f(+dim,dim, +dim);
    glTexCoord2f(0.0,0.0); glVertex3f(-dim,dim, +dim);
    glTexCoord2f(0.0,1.0); glVertex3f(-dim,dim, -dim);
    glTexCoord2f(1.0,1.0); glVertex3f(+dim,dim, -dim);
    glEnd();
}

static void lampPost(double x,double y,double z,
                     double dx,double dy,double dz,
                     double th)
{
    //  Save transformation
    glPushMatrix();
    //  Offset
    glTranslated(x,y,z);
    glRotated(th,0,1,0);

    //  Set specular color to white
    float white[] = {1,1,1,1};
    float black[] = {0,0,0,1};
    glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,shiny);
    glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,white);
    glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,black);

    float radScale = 0.03;
    float baseRadScale = 0.05;
    float capRadScale = 0.01;
    float outerRadScale = 0.08;

    //Pole
    glColor3f(0.4, 0.4, 0.4);
    glBindTexture(GL_TEXTURE_2D,textures[TEX_METAL]);
    glBegin(GL_QUADS);
    int i;
    for(i=45; i <= 360; i += 45) {
        //Base
        glNormal3f(Cos(i-22.5),0,Sin(i-22.5));
        glTexCoord2f(Cos(i), 0); glVertex3f(baseRadScale*Cos(i), 0, baseRadScale*Sin(i));
        glTexCoord2f(Cos(i), 0); glVertex3f(baseRadScale*Cos(i-45), 0, baseRadScale*Sin(i-45));
        glTexCoord2f(Cos(i), 1); glVertex3f(radScale*Cos(i-45), 0.1, radScale*Sin(i-45));
        glTexCoord2f(Cos(i), 1); glVertex3f(radScale*Cos(i), 0.1, radScale*Sin(i));
        //Pole Lower
        glNormal3f(Cos(i-22.5),0,Sin(i-22.5));
        glTexCoord2f(Cos(i), 0); glVertex3f(radScale*Cos(i), 0.1, radScale*Sin(i));
        glTexCoord2f(Cos(i), 0); glVertex3f(radScale*Cos(i-45), 0.1, radScale*Sin(i-45));
        glTexCoord2f(Cos(i), 2); glVertex3f(radScale*Cos(i-45), 0.5, radScale*Sin(i-45));
        glTexCoord2f(Cos(i), 2); glVertex3f(radScale*Cos(i), 0.5, radScale*Sin(i));
        //Pole Upper
        glNormal3f(Cos(i-22.5),0,Sin(i-22.5));
        glTexCoord2f(Cos(i), 0); glVertex3f(radScale*Cos(i), 0.5, radScale*Sin(i));
        glTexCoord2f(Cos(i), 0); glVertex3f(radScale*Cos(i-45), 0.5, radScale*Sin(i-45));
        glTexCoord2f(Cos(i), 2); glVertex3f(radScale*Cos(i-45), 1, radScale*Sin(i-45));
        glTexCoord2f(Cos(i), 2); glVertex3f(radScale*Cos(i), 1, radScale*Sin(i));
        //Light Cap
        glNormal3f(Cos(i-22.5),0,Sin(i-22.5));
        glTexCoord2f(Cos(i), 0); glVertex3f(radScale*Cos(i), 1.15, radScale*Sin(i));
        glTexCoord2f(Cos(i), 0); glVertex3f(radScale*Cos(i-45), 1.15, radScale*Sin(i-45));
        glTexCoord2f(Cos(i), 1); glVertex3f(capRadScale*Cos(i-45), 1.17, capRadScale*Sin(i-45));
        glTexCoord2f(Cos(i), 1); glVertex3f(capRadScale*Cos(i), 1.17, capRadScale*Sin(i));
    }
    glEnd();

    //Light
    float em[4] = {0.8, 0.8, 0.1, 1.0};
    glMaterialf(GL_FRONT,GL_SHININESS,0);
    glMaterialfv(GL_FRONT,GL_SPECULAR,em);
    glMaterialfv(GL_FRONT,GL_EMISSION,em);
    glColor3f(0.8, 0.8, 0.1);
    glBindTexture(GL_TEXTURE_2D,textures[TEX_GLASS]);
    glBegin(GL_QUADS);
    i = 45;
    for(i = 45; i <= 360; i += 45) {
        //Lower
        glNormal3f(Cos(i-22.5),0,Sin(i-22.5));
        glTexCoord2f(Cos(i), 0); glVertex3f(radScale*Cos(i), 1, radScale*Sin(i));
        glTexCoord2f(Cos(i), 0); glVertex3f(radScale*Cos(i-45), 1, radScale*Sin(i-45));
        glTexCoord2f(Cos(i), 1); glVertex3f(outerRadScale*Cos(i-45), 1.1, outerRadScale*Sin(i-45));
        glTexCoord2f(Cos(i), 1); glVertex3f(outerRadScale*Cos(i), 1.1, outerRadScale*Sin(i));
        //Upper
        glNormal3f(Cos(i-22.5),0,Sin(i-22.5));
        glTexCoord2f(Cos(i), 0); glVertex3f(outerRadScale*Cos(i), 1.1, outerRadScale*Sin(i));
        glTexCoord2f(Cos(i), 0); glVertex3f(outerRadScale*Cos(i-45), 1.1, outerRadScale*Sin(i-45));
        glTexCoord2f(Cos(i), 1); glVertex3f(radScale*Cos(i-45), 1.15, radScale*Sin(i-45));
        glTexCoord2f(Cos(i), 1); glVertex3f(radScale*Cos(i), 1.15, radScale*Sin(i));
    }
    glEnd();

    glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,shiny);
    glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,white);
    glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,black);

    //Undo transformations
    glPopMatrix();
}

/*
 *  OpenGL (GLUT) calls this routine to display the scene
 */
void display()
{
    const double len=2.0;  //  Length of axes
    //  Erase the window and the depth buffer
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    //  Enable Z-buffering in OpenGL
    glEnable(GL_DEPTH_TEST);
    //Enable Face Culling
    glEnable(GL_CULL_FACE);
    //Enable Textures
    glEnable(GL_TEXTURE_2D);
    glTexEnvi(GL_TEXTURE_ENV , GL_TEXTURE_ENV_MODE , tMode?GL_REPLACE:GL_MODULATE);

    //  Undo previous transformations
    glLoadIdentity();
    //  Perspective - set eye position
    if (mode)
    {
        double Ex = -2*dim*Sin(th)*Cos(ph);
        double Ey = +2*dim        *Sin(ph);
        double Ez = +2*dim*Cos(th)*Cos(ph);
        gluLookAt(Ex,Ey,Ez , 0,0,0 , 0,Cos(ph),0);
    }
        //  First Person
    else
    {
        refX = (dim * Sin(th)) + fpX;
        refY = (dim * Sin(ph));
        refZ = (dim * -Cos(th)) + fpZ;
        gluLookAt(fpX,fpY,fpZ, refX,refY,refZ, 0,1,0);
    }

    //  Flat or smooth shading
    glShadeModel(smooth ? GL_SMOOTH : GL_FLAT);

    //  Light position
    float Position[]  = {(double)distance*Cos(zh),(double)distance*Sin(zh),0,1.0};
    // float MoonPosition[]  = {-(distance*Cos(zh)),-(distance*Sin(zh)),0,1.0};

    //  Draw light position as ball (still no lighting here)
    glColor3f(1,1,1);
    // ball(Position[0],Position[1],Position[2] , 1); //Sun
    // ball(MoonPosition[0],MoonPosition[1],MoonPosition[2], 0.3); //Moon

    //  OpenGL should normalize normal vectors
    glEnable(GL_NORMALIZE);
    //  Enable lighting
    glEnable(GL_LIGHTING);
    //  Location of viewer for specular calculations
    glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER,local);
    //  glColor sets ambient and diffuse color materials
    glColorMaterial(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE);
    glEnable(GL_COLOR_MATERIAL);

    //  Enable light 0 - Sun
    glEnable(GL_LIGHT0);
    //  Set ambient, diffuse, specular components and position of light 0 (Sun)
    glLightfv(GL_LIGHT0,GL_AMBIENT ,Ambient);
    glLightfv(GL_LIGHT0,GL_DIFFUSE ,Diffuse);
    glLightfv(GL_LIGHT0,GL_SPECULAR,Specular);
    glLightfv(GL_LIGHT0,GL_POSITION,Position);


    //Inital values for texture repitition
    double texRepX = 1.0;
    double texRepY = 1.0;

    //Draw scene
    //Skybox
    skybox(64);

    //  Set specular color to white
    float white[] = {1,1,1,1};
    float black[] = {0,0,0,1};
    glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,shiny);
    glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,white);
    glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,black);

    //Enable offset for windows, doors, and other decals
    glPolygonOffset(1,1);
    glEnable(GL_POLYGON_OFFSET_FILL);

    //Lights for street lamps
    float amb[4] = {0,0,0,0};
    float dif[4] = {0.8,0.8,0.1,1};
    float spec[4] = {0.0,0.0,0.0,1};

    float posThree[4] = {3,1.1,-0.1,1.0};
    float posFour[4] = {-3,1.1,-0.1,1.0};
    float posFive[4] = {3,1.1,3.1,1.0};
    float posSix[4] = {-3,1.1,3.1,1.0};

    if(Sin(zh) <= 0) {
        glEnable(GL_LIGHT3);
        glLightfv(GL_LIGHT3,GL_AMBIENT ,amb);
        glLightfv(GL_LIGHT3,GL_DIFFUSE ,dif);
        glLightfv(GL_LIGHT3,GL_SPECULAR,spec);
        glLightfv(GL_LIGHT3,GL_POSITION,posThree);

        glLightf(GL_LIGHT3,GL_CONSTANT_ATTENUATION ,at0/100.0);
        glLightf(GL_LIGHT3,GL_LINEAR_ATTENUATION   ,at1/100.0);
        glLightf(GL_LIGHT3,GL_QUADRATIC_ATTENUATION,at2/100.0);

        glEnable(GL_LIGHT4);
        glLightfv(GL_LIGHT4,GL_AMBIENT ,amb);
        glLightfv(GL_LIGHT4,GL_DIFFUSE ,dif);
        glLightfv(GL_LIGHT4,GL_SPECULAR,spec);
        glLightfv(GL_LIGHT4,GL_POSITION,posFour);

        glLightf(GL_LIGHT4,GL_CONSTANT_ATTENUATION ,at0/100.0);
        glLightf(GL_LIGHT4,GL_LINEAR_ATTENUATION   ,at1/100.0);
        glLightf(GL_LIGHT4,GL_QUADRATIC_ATTENUATION,at2/100.0);

        glEnable(GL_LIGHT5);
        glLightfv(GL_LIGHT5,GL_AMBIENT ,amb);
        glLightfv(GL_LIGHT5,GL_DIFFUSE ,dif);
        glLightfv(GL_LIGHT5,GL_SPECULAR,spec);
        glLightfv(GL_LIGHT5,GL_POSITION,posFive);

        glLightf(GL_LIGHT5,GL_CONSTANT_ATTENUATION ,at0/100.0);
        glLightf(GL_LIGHT5,GL_LINEAR_ATTENUATION   ,at1/100.0);
        glLightf(GL_LIGHT5,GL_QUADRATIC_ATTENUATION,at2/100.0);

        glEnable(GL_LIGHT6);
        glLightfv(GL_LIGHT6,GL_AMBIENT ,amb);
        glLightfv(GL_LIGHT6,GL_DIFFUSE ,dif);
        glLightfv(GL_LIGHT6,GL_SPECULAR,spec);
        glLightfv(GL_LIGHT6,GL_POSITION,posSix);

        glLightf(GL_LIGHT6,GL_CONSTANT_ATTENUATION ,at0/100.0);
        glLightf(GL_LIGHT6,GL_LINEAR_ATTENUATION   ,at1/100.0);
        glLightf(GL_LIGHT6,GL_QUADRATIC_ATTENUATION,at2/100.0);
    } else {
        glDisable(GL_LIGHT3);
        glDisable(GL_LIGHT4);
        glDisable(GL_LIGHT5);
        glDisable(GL_LIGHT6);
    }

    if(mvPlayerCar >= 36) {exit(0);}
    //Enemy Car
    car(-29,0.13,2.5+leftRightEnemy, 1,1,1, 0,0,0.8,0);
    DrawBullet(-28.5-enemyBulletPos,0.2,2.5+leftRightEnemy);
    // std::cout<<"en : "<<enemyBulletPos<<std::endl;
    //Police Car
    policeCar(8.5-mvPlayerCar,0.13,2.5+leftRightPlayer, 1,1,1, 180);
    DrawBullet(8-playerBulletPos-mvPlayerCar,0.2,2.5+leftRightPlayer);
    // cube(7.5-playerBulletPos-mvPlayerCar,0.2,2.5+leftRightPlayer,0.05,0.5,0.4,0);
    // std::cout<<"pl : "<<mvPlayerCar<<std::endl<<std::endl;

    // Hitbox
    glColor3f(0.4, 0.4, 0.4);
    glBindTexture(GL_TEXTURE_2D,textures[TEX_WOODFENCE]);
    texScale = 0.5;
    cube(3,0.6,1, 0.4,0.4,0.4, 90); //Right
    cube(-1,0.6,4, 0.4,0.4,0.4, 90); //Left

    //Lamp Posts
    for(int i=0; i< 39; i+=2){
        lampPost(8-i,0.1,-0.1, 1,1,1, 0);
        lampPost(8-i,0.1,5.1, 1,1,1, 0);
    }


    //Street surface - Main Street
    glColor3f(0.4, 0.4, 0.4);
    texScale = 0.5;
    float xPos = -30;
    int i;
    for(i = 0; i < 21; i++){
        if(i%3==0){
            glBindTexture(GL_TEXTURE_2D,textures[TEX_DESERT]);
        }else{
            glBindTexture(GL_TEXTURE_2D,textures[TEX_ASPALTH]);
        }
        // mvRoad >= 1.5 ? mvRoad = 0 : NULL;
        cube(xPos,-0.1,2.25, 1,0.1,3, 0);
        xPos += 2;
    }
    //Grass Square Beside Road
    glColor3f(0.7, 0.7, 0.7);
    glBindTexture(GL_TEXTURE_2D,textures[TEX_GRASS]);
    texScale = 0.5;
    cube(-16,-0.05,8, 14,0.15,2, 0); //Left
    cube(-16,-0.05,-3, 14,0.15,2, 0); //Right
    //Hedge
    glBindTexture(GL_TEXTURE_2D,textures[TEX_HEDGE]);
    texScale = 0.5;
    cube(-17,0.3,6.25, 15,0.15,0.3, 0); //Left
    cube(-31.25,0.3,2.85, 3.75,0.15,0.75, 90); //MiddleFar
    cube(-17,0.3,-1.25, 15,0.15,0.3, 0); //Right
    //Walkway
    glBindTexture(GL_TEXTURE_2D,textures[TEX_WALKWAY]);
    texScale = 0.4;
    cube(-16,0.15,6.95, 14,0.05,0.3, 0); //Left
    cube(-16,0.15,-1.95, 14,0.05,0.3, 0); //Right

    // Desert Sands
    glColor3f(0.4, 0.4, 0.4);
    texScale = 0.5;
    xPos = -50;
    for(int i = 0; i < 20; i++){
        glBindTexture(GL_TEXTURE_2D,textures[TEX_DESERT]);
        cube(xPos,-1.0,8.25, 10,0.1,50, 0);
        xPos += 5;
    }

    //Sidewalks (Player Side)
    glColor3f(0.7, 0.7, 0.7);
    glBindTexture(GL_TEXTURE_2D,textures[TEX_SIDEWALK]);
    texScale = 0.5;
    //Sidewalks (Kanan)
    cube(-10,-0.05,-0.5, 20,0.15,0.5, 0); // Along Street

    //Sidewalks (Kiri)
    cube(-10,-0.05,5.5, 20,0.15,0.5, 0);


    cube(10.5,-0.05,2.5, 3.5,0.15,0.5, 90); // Middle Player Side
    cube(-30.5,-0.05,2.5, 3.5,0.15,0.5, 90); // Middle Far Side

    //Grey town house - player side
    greyHouse(0,0,0);
    // house(5,0,0);

    //Rumah Belakang Sekarang
    //Grey town house - Far
    // greyHouse(10,-2.05,-90); //Left
    greyHouse(10,2.05,-90); //Middle
    //Hedges
    glColor3f(0, 0.3, 0.1);
    glBindTexture(GL_TEXTURE_2D,textures[TEX_HEDGE]);
    texScale = 0.25;
    cube(11.497,0.13,5.05, 1,0.3,0.5, 90);
    cube(11.497,0.13,-0.5, 0.75,0.3,0.5, 90);
    // greyHouse(10,6.15,-90); //Right

    // Fence
    glColor3f(0.4, 0.4, 0.4);
    glBindTexture(GL_TEXTURE_2D,textures[TEX_WOODFENCE]);
    texScale = 0.5;
    cube(-19,0.6,-2.5, -0.05,0.5,13, 90); //Right Far Side
    cube(-17,0.6,7.525, -0.05,0.5,15, 90); //Left Far Side
    
    cube(8,0.6,-1.05, -0.05,0.5,3, 90); //Right Player Side
    cube(10.49,0.6,6.05, 0.05,0.5,0.5, 90); //Left Player Side


    //Brown workshop - player side
    glColor3f(0.7, 0.7, 0.7);
    glBindTexture(GL_TEXTURE_2D,textures[TEX_BROWNBRICK]);
    workshop(-4,-2,0);

    //Storage Facility
    glColor3f(0.33, 0.22, 0.11);
    glBindTexture(GL_TEXTURE_2D,textures[TEX_WHITEBRICK]);
    workshop(8,7,180);
    glColor3f(0.33, 0.22, 0.11);
    glBindTexture(GL_TEXTURE_2D,textures[TEX_WHITEBRICK]);
    workshop(4,7,180);
    glColor3f(0.33, 0.22, 0.11);
    glBindTexture(GL_TEXTURE_2D,textures[TEX_WHITEBRICK]);
    workshop(0,7,180);

    //Triagular Roof
    texRepX = 2/texScale;
    texRepY = 0.7/texScale;
    float xVal = 10;
    for(i = 0; i < 6; i++){
        texRepX = 2/texScale;
        texRepY = 0.7/texScale;
        glColor3f(0.33, 0.22, 0.11);
        //Side
        glBindTexture(GL_TEXTURE_2D,textures[TEX_WHITEBRICK]);
        glBegin(GL_TRIANGLES);
        glNormal3f(0,0,-1);
        glTexCoord2f(0.0,0.0); glVertex3f(xVal,2,6);
        glTexCoord2f(texRepX, 0.0); glVertex3f(xVal-2,2,6);
        glTexCoord2f(texRepX, texRepY); glVertex3f(xVal-2,2.7,6);
        glEnd();

        texRepX = 4/texScale;
        texRepY = 2/texScale;
        glColor3f(0.5, 0.5, 0.5);
        //Roof
        glBindTexture(GL_TEXTURE_2D,textures[TEX_METALROOF]);
        glBegin(GL_QUADS);
        glNormal3f(-0.33035, 0.943858, 0);
        glTexCoord2f(0.0,0.0); glVertex3f(xVal,2,6);
        glTexCoord2f(texRepX,0.0); glVertex3f(xVal-2,2.7,6);
        glTexCoord2f(texRepX,texRepY); glVertex3f(xVal-2,2.7,8);
        glTexCoord2f(0.0,texRepY); glVertex3f(xVal,2,8);
        glEnd();

        texRepX = 1;
        texRepY = 3;
        glColor3f(0.5, 0.5, 0.5);
        //Windows
        glBindTexture(GL_TEXTURE_2D,textures[TEX_WAREHOUSEWINDOW]);
        glBegin(GL_QUADS);
        glNormal3f(-1, 0, 0);
        glTexCoord2f(texRepX,0.0); glVertex3f(xVal-2,2.7,6);
        glTexCoord2f(0.0,0.0); glVertex3f(xVal-2,2,6);
        glTexCoord2f(0.0,texRepY); glVertex3f(xVal-2,2,8);
        glTexCoord2f(texRepX,texRepY); glVertex3f(xVal-2,2.7,8);
        glEnd();

        xVal -= 2;
    }

    //Grass Square
    glColor3f(0.7, 0.7, 0.7);
    glBindTexture(GL_TEXTURE_2D,textures[TEX_GRASS]);
    texScale = 0.5;
    cube(4,-0.05,-3, 2,0.15,2, 0);



    //Fence
    glColor3f(0.4, 0.4, 0.4);
    glBindTexture(GL_TEXTURE_2D,textures[TEX_WOODFENCE]);
    texScale = 0.5;
    cube(2.05,0.6,-3, 0.05,0.5,2, 0); //Left
    cube(5.95,0.6,-3, 0.05,0.5,2, 0); //Right
    cube(2.8,0.6,-1.05, 0.05,0.5,0.7, 90); //Front Left
    cube(5.2,0.6,-1.05, 0.05,0.5,0.7, 90); //Front Right

    //Cinder block wall - Far Side
    // glColor3f(0.4, 0.4, 0.4);
    // glBindTexture(GL_TEXTURE_2D,textures[TEX_CHINDERBLOCK]);
    // texScale = 0.5;
    // cube(-30.05,0.13,3, 6,0.5,0.05, 90); //Left

    //  Draw axes - no lighting from here on
    glDisable(GL_LIGHTING);
    //  Switch off textures so it doesn't apply to the rest
    glDisable(GL_TEXTURE_2D);

    glColor3f(1,1,1);
    if (axes)
    {
        glBegin(GL_LINES);
        glVertex3d(0.0,0.0,0.0);
        glVertex3d(len,0.0,0.0);
        glVertex3d(0.0,0.0,0.0);
        glVertex3d(0.0,len,0.0);
        glVertex3d(0.0,0.0,0.0);
        glVertex3d(0.0,0.0,len);
        glEnd();
        //  Label axes
        glRasterPos3d(len,0.0,0.0);
        Print("X");
        glRasterPos3d(0.0,len,0.0);
        Print("Y");
        glRasterPos3d(0.0,0.0,len);
        Print("Z");
    }

    //  Display parameters
    // glWindowPos2i(5,5);
    Print("Angle=%d,%d  Dim=%.1f  FOV=%d  Projection=%s",th,ph,dim,fov,mode?"Perpective":"FP");

    //  Render the scene and make it visible
    ErrCheck("display");
    glFlush();
    glutSwapBuffers();
}

static void setEnvLighting()
{
    float ambScale = 0.8;

    if(Sin(zh) >= 0.2) {
        Ambient[0] = (255 / 255) * ambScale;
        Ambient[1] = (255 / 255) * ambScale;
        Ambient[2] = (255 / 255) * ambScale;

        Diffuse[0] = 1.0;
        Diffuse[1] = 1.0;
        Diffuse[2] = 1.0;
    } else if (Sin(zh) < 0.4 && Sin(zh) >= 0) {
        Ambient[0] = (255 / 255) * ambScale;
        Ambient[1] = ((60 + (195*Sin(zh)*2.5)) / 255) * ambScale;
        Ambient[2] = ((60 + (195*Sin(zh)*2.5)) / 255) * ambScale;

        Diffuse[0] = Sin(zh)*2.5;
        Diffuse[1] = Sin(zh)*2.5;
        Diffuse[2] = Sin(zh)*2.5;
    } else if (Sin(zh) < 0 && Sin(zh) >= -0.4){
        Ambient[0] = ((255 - (235*Sin(zh)*-2.5)) / 255) * ambScale;
        Ambient[1] = (60 / 255) * ambScale;
        Ambient[2] = ((60 + (120*Sin(zh)*-2.5)) / 255) * ambScale;

        Diffuse[0] = 0;
        Diffuse[1] = 0;
        Diffuse[2] = 0;
    } else {
        Ambient[0] = (20 / 255) * ambScale;
        Ambient[1] = (60 / 255) * ambScale;
        Ambient[2] = (180 / 255) * ambScale;

        Diffuse[0] = 0;
        Diffuse[1] = 0;
        Diffuse[2] = 0;
    }
}

/*
 *  GLUT calls this routine when the window is resized
 */
void idle()
{
    //  Elapsed time in seconds
    double t = glutGet(GLUT_ELAPSED_TIME)/1000.0;
    zh = fmod(10*t,360.0);

    setEnvLighting();

    //  Tell GLUT it is necessary to redisplay the scene
    glutPostRedisplay();
}

/*
 *  GLUT calls this routine when an arrow key is pressed
 */
void special(int key,int x,int y)
{
    //  Right arrow key - increase angle by 5 degrees
    if (key == GLUT_KEY_RIGHT)
        th += 5;
        //  Left arrow key - decrease angle by 5 degrees
    else if (key == GLUT_KEY_LEFT)
        th -= 5;
        //  Up arrow key - increase elevation by 5 degrees
    else if (key == GLUT_KEY_UP)
        ph += 5;
        //  Down arrow key - decrease elevation by 5 degrees
    else if (key == GLUT_KEY_DOWN)
        ph -= 5;
        //  PageUp key - increase dim
    else if (key == GLUT_KEY_PAGE_DOWN)
        dim += 0.1;
        //  PageDown key - decrease dim
    else if (key == GLUT_KEY_PAGE_UP && dim>1)
        dim -= 0.1;
    th %= 360;
    ph %= 360;
    //  Update projection
    Project(fov,asp,dim);
    //  Tell GLUT it is necessary to redisplay the scene
    glutPostRedisplay();
}

/*
 *  GLUT calls this routine when a key is pressed
 */
void key(unsigned char ch,int x,int y)
{
    switch(ch){
        //  Exit on ESC
        case 27 :
            exit(0);
            break;
        // Reset view Angle
        case 0 :
            th = ph = 0;
            break;
        // Toggle axes
        case 'x' :
        case 'X' :
            axes = 1-axes;
            break;
        // Switch projection mode
        case 'p' :
        case 'P' :
            mode = 1-mode;
            break;
        //  Toggle light movement
        case 'm' :
        case 'M' :
            move = 1-move;
            break;
        // Player shoot with SPACEBAR
        case 32 :
            bulletFired = true;
            playerBulletPos = 0;
            break;
        //  Player moving forward car
        case 'w' :
        case 'W' :
            mvPlayerCar += 0.05;
            mvRoad += 0.05;
            break;
        //  Player moving backward car
        case 's' :
        case 'S' :
            mvPlayerCar -= 0.05;
            mvRoad -= 0.05;
            break;
        //  Player moving left car
        case 'a' :
        case 'A' :
            (leftRightPlayer<1.5) ? leftRightPlayer += 0.05 : leftRightPlayer += 0 ;
            // std::cout<<"left : "<<leftRightPlayer<<std::endl;
            break;
        //  Player moving right car
        case 'd' :
        case 'D' :
            (leftRightPlayer<-2) ? leftRightPlayer -= 0 : leftRightPlayer -= 0.05 ;
            break;
    }
    // std::cout<<"mvPlayerCar : "<<mvPlayerCar<<std::endl;
    //  Change field of view angle
    if (ch == '-' && ch>1)
        fov--;
    else if (ch == '+' && ch<179)
        fov++;
    //  Reproject
    Project(fov,asp,dim);
    //  Animate if requested
    glutIdleFunc(move?idle:NULL);
    //  Tell GLUT it is necessary to redisplay the scene
    glutPostRedisplay();
}

/*
 *  GLUT calls this routine when the window is resized
 */
void reshape(int width,int height)
{
    //  Ratio of the width to the height of the window
    asp = (height>0) ? (double)width/height : 1;
    //  Set the viewport to the entire window
    glViewport(0,0, width,height);
    //  Set projection
    Project(fov,asp,dim);
}

/*
 *  Start up GLUT and tell it what to do
 */
int main(int argc,char* argv[])
{
    //  Initialize GLUT
    glutInit(&argc,argv);
    //  Request double buffered, true color window with Z buffering at 600x600
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
    glutInitWindowSize(1024,720);
    glutCreateWindow("Battle Cars V1");
    //  Set callbacks
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutSpecialFunc(special);
    glutTimerFunc(refreshMillsEnemy, EnemyTimer, 0);
    glutTimerFunc(refreshMills, PlayerTimer, 0);
    glutKeyboardFunc(key);
    Init();
    glutIdleFunc(idle);
    //  Pass control to GLUT so it can interact with the user
    ErrCheck("init");
    glutMainLoop();
    return 0;
}