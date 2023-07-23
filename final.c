#include "CSCIx229.h"
int mode=0;       //  Texture mode
int ntex=0;       //  Cube faces
int axes=1;       //  Display axes
int th=0;         //  Azimuth of view angle
int ph=0;         //  Elevation of view angle
int light=1;      //  Lighting CHANGE
int rep=1;        //  Repitition
double asp=1;     //  Aspect ratio
double dim=3.0;   //  Size of world
// Light values
int emission  =   0;  // Emission intensity (%)
int ambient   =  30;  // Ambient intensity (%)
int diffuse   = 100;  // Diffuse intensity (%)
int specular  =   0;  // Specular intensity (%)
int shininess =   0;  // Shininess (power of two)
float shiny   =   1;    // Shininess (value)
int zh        =  90;  // Light azimuth
float ylight  =   0;  // Elevation of light
unsigned int texture[3]; // Texture names


/*
 *  Draw a ball
 *     at (x,y,z)
 *     radius r
 */
static void ball(double x,double y,double z,double r)
{
   //  Save transformation
   glPushMatrix();
   //  Offset, scale and rotate
   glTranslated(x,y,z);
   glScaled(r,r,r);
   //  White ball
   glColor3f(1,1,1);
   glutSolidSphere(1.0,16,16);
   //  Undo transofrmations
   glPopMatrix();
}

static void dPad(double x,double y,double z,
                 double dx,double dy,double dz,
                 double th)
{
   glPushMatrix();
   // //  Offset, scale and rotate
   glTranslated(x,y,z);
   glRotated(th,0,1,0);
   glScaled(dx,dy,dz);
   // Textures
   glEnable(GL_TEXTURE_2D);
   glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,mode?GL_REPLACE:GL_MODULATE);
   // glColor3f(1,1,1);
   glBindTexture(GL_TEXTURE_2D,texture[0]);
   
   // glColor3f(1, 1, 1); 
   // glTranslatef(0.0, 0.0, 0.0);
   glBegin(GL_QUADS);
   // Front face
   glNormal3f( 0, 0, 1);
   glVertex3f(-0.5, -0.5, -0.5); //bot left
   glVertex3f(0.5, -0.5, -0.5); //bot right
   glVertex3f(0.5, 0.5, -0.5); //top right
   glVertex3f(-0.5, 0.5, -0.5); //top left
   // Add arrows
   glTexCoord2f(0,0); glVertex3f(-0.5, -0.5, 0.5); //bot left
   glTexCoord2f(1,0); glVertex3f(0.5, -0.5, 0.5); //bot right
   glTexCoord2f(1,1); glVertex3f(0.5, 0.5, 0.5); //top right
   glTexCoord2f(0,1); glVertex3f(-0.5, 0.5, 0.5); //top left

   glVertex3f(-0.5, 0.5, -0.5); //bot left
   glVertex3f(0.5, 0.5, -0.5); //bot right
   glVertex3f(0.5, 1.5, -0.5); //top right
   glVertex3f(-0.5, 1.5, -0.5); //top left

   glTexCoord2f(0,0);glVertex3f(-0.5, 0.5, 0.5); //bot left
   glTexCoord2f(1,0);glVertex3f(0.5, 0.5, 0.5); //bot right
   glTexCoord2f(1,1);glVertex3f(0.5, 1.5, 0.5); //top right
   glTexCoord2f(0,1);glVertex3f(-0.5, 1.5, 0.5); //top left

   glVertex3f(-0.5, -0.5, -0.5); //bot left
   glVertex3f(0.5, -0.5, -0.5); //bot right
   glVertex3f(0.5, -1.5, -0.5); //top right
   glVertex3f(-0.5, -1.5, -0.5); //top left

   glTexCoord2f(0,0);glVertex3f(-0.5, -0.5, 0.5); //bot left
   glTexCoord2f(1,0);glVertex3f(0.5, -0.5, 0.5); //bot right
   glTexCoord2f(1,1);glVertex3f(0.5, -1.5, 0.5); //top right
   glTexCoord2f(0,1);glVertex3f(-0.5, -1.5, 0.5); //top left

   glTexCoord2f(0,0);glVertex3f(-0.5, 1.5, -0.5); //bot left
   glTexCoord2f(1,0);glVertex3f(0.5, 1.5, -0.5); //bot right
   glTexCoord2f(1,1);glVertex3f(0.5, 1.5, 0.5); //top right
   glTexCoord2f(0,1);glVertex3f(-0.5, 1.5, 0.5); //top left
   
   glTexCoord2f(0,0);glVertex3f(-0.5, -1.5, -0.5); //bot left
   glTexCoord2f(1,0);glVertex3f(0.5, -1.5, -0.5); //bot right
   glTexCoord2f(1,1);glVertex3f(0.5, -1.5, 0.5); //top right
   glTexCoord2f(0,1);glVertex3f(-0.5, -1.5, 0.5); //top left

   glTexCoord2f(0,0);glVertex3f(-1.5, 0.5, -0.5); //bot left
   glTexCoord2f(1,0);glVertex3f(-0.5, 0.5, -0.5); //bot right
   glTexCoord2f(1,1);glVertex3f(-0.5, 0.5, 0.5); //top right
   glTexCoord2f(0,1);glVertex3f(-1.5, 0.5, 0.5); //top left

   glTexCoord2f(0,0);glVertex3f(-1.5, -0.5, -0.5); //bot left
   glTexCoord2f(1,0);glVertex3f(-0.5, -0.5, -0.5); //bot right
   glTexCoord2f(1,1);glVertex3f(-0.5, -0.5, 0.5); //top right
   glTexCoord2f(0,1);glVertex3f(-1.5, -0.5, 0.5); //top left

   glTexCoord2f(0,0);glVertex3f(1.5, 0.5, -0.5); //bot left
   glTexCoord2f(1,0);glVertex3f(0.5, 0.5, -0.5); //bot right
   glTexCoord2f(1,1);glVertex3f(0.5, 0.5, 0.5); //top right
   glTexCoord2f(0,1);glVertex3f(1.5, 0.5, 0.5); //top 
   
   glTexCoord2f(0,0);glVertex3f(1.5, -0.5, -0.5); //bot left
   glTexCoord2f(1,0);glVertex3f(0.5, -0.5, -0.5); //bot right
   glTexCoord2f(1,1);glVertex3f(0.5, -0.5, 0.5); //top right
   glTexCoord2f(0,1);glVertex3f(1.5, -0.5, 0.5); //top left

   glTexCoord2f(0,0);glVertex3f(0.5,-0.5,-0.5); //bl
   glTexCoord2f(1,0);glVertex3f(0.5,-0.5,0.5); //br
   glTexCoord2f(1,1);glVertex3f(0.5,0.5,0.5); //tr
   glTexCoord2f(0,1);glVertex3f(0.5, 0.5, -0.5);
   
   glTexCoord2f(0,0);glVertex3f(0.5,.5,-0.5); //bl
   glTexCoord2f(1,0);glVertex3f(0.5,.5,0.5); //br
   glTexCoord2f(1,1);glVertex3f(0.5,1.5,0.5); //tr
   glTexCoord2f(0,1);glVertex3f(0.5, 1.5, -0.5);

   glTexCoord2f(0,0);glVertex3f(0.5,-0.5,-0.5); //bl
   glTexCoord2f(1,0);glVertex3f(0.5,-0.5,0.5); //br
   glTexCoord2f(1,1);glVertex3f(0.5,-1.5,0.5); //tr
   glTexCoord2f(0,1);glVertex3f(0.5, -1.5, -0.5);

   glTexCoord2f(0,0);glVertex3f(0.5,-0.5,-0.5); //bl
   glTexCoord2f(1,0);glVertex3f(-0.5,-0.5,0.5); //br
   glTexCoord2f(1,1);glVertex3f(-0.5,0.5,0.5); //tr
   glTexCoord2f(0,1);glVertex3f(-0.5, 0.5, -0.5);
   
   glTexCoord2f(0,0);glVertex3f(-0.5,.5,-0.5); //bl
   glTexCoord2f(1,0);glVertex3f(-0.5,.5,0.5); //br
   glTexCoord2f(1,1);glVertex3f(-0.5,1.5,0.5); //tr
   glTexCoord2f(0,1);glVertex3f(-0.5, 1.5, -0.5);

   glTexCoord2f(0,0);glVertex3f(-0.5,-0.5,-0.5); //bl
   glTexCoord2f(1,0);glVertex3f(-0.5,-0.5,0.5); //br
   glTexCoord2f(1,1);glVertex3f(-0.5,-1.5,0.5); //tr
   glTexCoord2f(0,1);glVertex3f(-0.5, -1.5, -0.5);

   glTexCoord2f(0,0);glVertex3f(1.5,-0.5,-0.5); //bl
   glTexCoord2f(1,0);glVertex3f(1.5,-0.5,0.5); //br
   glTexCoord2f(1,1);glVertex3f(1.5,0.5,0.5); //tr
   glTexCoord2f(0,1);glVertex3f(1.5, 0.5, -0.5);

   glTexCoord2f(0,0);glVertex3f(-1.5,-0.5,-0.5); //bl
   glTexCoord2f(1,0);glVertex3f(-1.5,-0.5,0.5); //br
   glTexCoord2f(1,1);glVertex3f(-1.5,0.5,0.5); //tr
   glTexCoord2f(0,1);glVertex3f(-1.5, 0.5, -0.5);

   glTexCoord2f(0,0);glVertex3f(0.5, -0.5, 0.5); //bot left
   glTexCoord2f(1,0);glVertex3f(1.5, -0.5, 0.5); //bot right
   glTexCoord2f(1,1);glVertex3f(1.5, 0.5, 0.5); //top right
   glTexCoord2f(0,1);glVertex3f(0.5, 0.5, 0.5); //top left

   glVertex3f(0.5, -0.5, -0.5); //bot left
   glVertex3f(1.5, -0.5, -0.5); //bot right
   glVertex3f(1.5, 0.5, -0.5); //top right
   glVertex3f(0.5, 0.5, -0.5); //top left

   glTexCoord2f(0,0);glVertex3f(-0.5, -0.5, 0.5); //bot left
   glTexCoord2f(1,0);glVertex3f(-1.5, -0.5, 0.5); //bot right
   glTexCoord2f(1,1);glVertex3f(-1.5, 0.5, 0.5); //top right
   glTexCoord2f(0,1);glVertex3f(-0.5, 0.5, 0.5); //top left

   glVertex3f(-0.5, -0.5, -0.5); //bot left
   glVertex3f(-1.5, -0.5, -0.5); //bot right
   glVertex3f(-1.5, 0.5, -0.5); //top right
   glVertex3f(-0.5, 0.5, -0.5); //top left

   glEnd();
   glPopMatrix();
   glDisable(GL_TEXTURE_2D);
}

static void aButton(double x,double y,double z,
                 double dx,double dy,double dz,
                 double th) 
{
   glPushMatrix();
   // //  Offset, scale and rotate
   glTranslated(x,y,z);
   glRotated(th,0,1,0);
   glScaled(dx,dy,dz);
   //  Enable textures

   glEnable(GL_TEXTURE_2D);
   glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,mode?GL_REPLACE:GL_MODULATE);
   // glColor3f(1,1,1);
   glBindTexture(GL_TEXTURE_2D,texture[0]);

   // Check class example for lighting
   glBegin(GL_QUAD_STRIP);
   for(int i = 0; i <= 360; i+=10) {
      // glNormal3f(Cos(i),Sin(i),0);
      glTexCoord2f(i,1);
      glVertex3f(+1, Cos(i), Sin(i));
      // glNormal3f(Cos(i),1,Sin(i));
      glTexCoord2f(i,0);
      glVertex3f(-1, Cos(i), Sin(i));
   }
   glEnd();
   // glColor3f(.1,.1,.1);
   glBindTexture(GL_TEXTURE_2D,texture[1]);
   glBegin(GL_TRIANGLE_FAN);
   glNormal3f( -1, 0, 0);
   glTexCoord2f(0.5,0.5);
   glVertex3f(-1,0,0);
   for(int n=0; n <=360; n+=10) {
      glTexCoord2f(0.5*Cos(n)+0.5,0.5*Sin(n)+0.5);
      glVertex3f(-1, Cos(n),Sin(n));
   }
   glEnd();
   glDisable(GL_TEXTURE_2D);
   glPopMatrix();
}

static void bButton(double x,double y,double z,
                 double dx,double dy,double dz,
                 double th) 
{
   glPushMatrix();
   // //  Offset, scale and rotate
   glTranslated(x,y,z);
   glRotated(th,0,1,0);
   glScaled(dx,dy,dz);
   //  Enable textures

   glEnable(GL_TEXTURE_2D);
   glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,mode?GL_REPLACE:GL_MODULATE);
   // glColor3f(1,1,1);
   glBindTexture(GL_TEXTURE_2D,texture[0]);

   // Check class example for lighting
   glBegin(GL_QUAD_STRIP);
   for(int i = 0; i <= 360; i+=10) {
      // glNormal3f(Cos(i),Sin(i),0);
      glTexCoord2f(i,1);
      glVertex3f(+1, Cos(i), Sin(i));
      // glNormal3f(Cos(i),1,Sin(i));
      glTexCoord2f(i,0);
      glVertex3f(-1, Cos(i), Sin(i));
   }
   glEnd();
   // glColor3f(.1,.1,.1);
   glBindTexture(GL_TEXTURE_2D,texture[2]);
   glBegin(GL_TRIANGLE_FAN);
   glNormal3f( -1, 0, 0);
   glTexCoord2f(0.5,0.5);
   glVertex3f(-1,0,0);
   for(int n=0; n <=360; n+=10) {
      glTexCoord2f(0.5*Cos(n)+0.5,0.5*Sin(n)+0.5);
      glVertex3f(-1, Cos(n),Sin(n));
   }
   glEnd();
   glDisable(GL_TEXTURE_2D);
   glPopMatrix();
}

static void outerScreen(double x,double y,double z,
                 double dx,double dy,double dz,
                 double th)
{

   //  Save transformation
   glPushMatrix();
   //  Offset, scale and rotate
   glTranslated(x,y,z);
   glRotated(th,0,1,0);
   glScaled(dx,dy,dz);
   //  Enable textures
   glEnable(GL_TEXTURE_2D);
   glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,mode?GL_REPLACE:GL_MODULATE);
   glBindTexture(GL_TEXTURE_2D,texture[0]);

   //This section represents top of screen. One rectangluar prism, 2 quarter cylindrical prisms

   //top right quarter cylinder
   glBegin(GL_QUAD_STRIP);
   for(int i = 0; i <= 90; i+=10) {
      glVertex3f(Cos(i), Sin(i), 1);
      glVertex3f(Cos(i),Sin(i), -1);
   }
   glEnd();
   glBegin(GL_TRIANGLE_FAN);
   glVertex3f(0,0,1);
   for(int n=0; n <=90; n+=10) {
      glVertex3f(Cos(n), Sin(n),1);
   }
   glEnd();
   glBegin(GL_TRIANGLE_FAN);
   glVertex3f(0,0,-1);
   for(int n=0; n <=90; n+=10) {
      glVertex3f(Cos(n), Sin(n),-1);
   }
   // Rectangular mid section
   glEnd();
   glBegin(GL_QUADS);
   glVertex3f(-2,0,-1);
   glVertex3f(0,0,-1);
   glVertex3f(0,1,-1);
   glVertex3f(-2,1,-1);
   glEnd();
   glBegin(GL_QUADS);
   glVertex3f(-2,0,1);
   glVertex3f(0,0,1);
   glVertex3f(0,1,1);
   glVertex3f(-2,1,1);
   glEnd();
   glBegin(GL_QUADS);
   glVertex3f(-2,1,-1);
   glVertex3f(-2,1,1);
   glVertex3f(0,1,1);
   glVertex3f(0,1,-1);
   glEnd();
   //top left quarter cylinder
   glBegin(GL_QUAD_STRIP);
   for(int i = 0; i <= 90; i+=10) {
      glVertex3f(-2-Cos(i), Sin(i), 1);
      glVertex3f(-2-Cos(i),Sin(i), -1);
   }
   glEnd();
   glBegin(GL_TRIANGLE_FAN);
   glVertex3f(-2,0,1);
   for(int n=0; n <=90; n+=10) {
      glVertex3f(-2-Cos(n), Sin(n),1);
   }
   glEnd();
   glBegin(GL_TRIANGLE_FAN);
   glVertex3f(-2,0,-1);
   for(int n=0; n <=90; n+=10) {
      glVertex3f(-2-Cos(n), Sin(n),-1);
   }
   glEnd();

   //Body of screen
   glBegin(GL_QUADS);
   glVertex3f(-2,-4,-1);
   glVertex3f(0,-4,-1);
   glVertex3f(0,0,-1);
   glVertex3f(-2,0,-1);
   glEnd();

   glBegin(GL_QUADS);
   glVertex3f(-2,-4,1);
   glVertex3f(0,-4,1);
   glVertex3f(0,0,1);
   glVertex3f(-2,0,1);
   glEnd();

   //bottom of screen

   //bottom right quarter cylinder
   glBegin(GL_QUAD_STRIP);
   for(int i = 0; i <= 90; i+=10) {
      glVertex3f(Cos(i), -4-Sin(i), 1);
      glVertex3f(Cos(i),-4-Sin(i), -1);
   }
   glEnd();
   glBegin(GL_TRIANGLE_FAN);
   glVertex3f(0,-4,1);
   for(int n=0; n <=90; n+=10) {
      glVertex3f(Cos(n), -4-Sin(n),1);
   }
   glEnd();
   glBegin(GL_TRIANGLE_FAN);
   glVertex3f(0,-4,-1);
   for(int n=0; n <=90; n+=10) {
      glVertex3f(Cos(n), -4-Sin(n),-1);
   }
   glEnd();

   // Rectangular mid section
   glBegin(GL_QUADS);
   glVertex3f(-2,-5,-1);
   glVertex3f(0,-5,-1);
   glVertex3f(0,-4,-1);
   glVertex3f(-2,-4,-1);
   glEnd();
   glBegin(GL_QUADS);
   glVertex3f(-2,-5,1);
   glVertex3f(0,-5,1);
   glVertex3f(0,-4,1);
   glVertex3f(-2,-4,1);
   glEnd();
   glBegin(GL_QUADS);
   glVertex3f(-2,-5,-1);
   glVertex3f(-2,-5,1);
   glVertex3f(0,-5,1);
   glVertex3f(0,-5,-1);
   glEnd();

   //bottom left quarter cylinder
   glBegin(GL_QUAD_STRIP);
   for(int i = 0; i <= 90; i+=10) {
      glVertex3f(-2-Cos(i), -4-Sin(i), 1);
      glVertex3f(-2-Cos(i),-4-Sin(i), -1);
   }
   glEnd();
   glBegin(GL_TRIANGLE_FAN);
   glVertex3f(-2,-4,1);
   for(int n=0; n <=90; n+=10) {
      glVertex3f(-2-Cos(n), -4-Sin(n),1);
   }
   glEnd();
   glBegin(GL_TRIANGLE_FAN);
   glVertex3f(-2,-4,-1);
   for(int n=0; n <=90; n+=10) {
      glVertex3f(-2-Cos(n), -4-Sin(n),-1);
   }
   glEnd();

   //sides
   glBegin(GL_QUADS);
   glVertex3f(0,-4,-1);
   glVertex3f(1,-4,-1);
   glVertex3f(1,0,-1);
   glVertex3f(0,0,-1);
   glEnd();
   glBegin(GL_QUADS);
   glVertex3f(0,-4,1);
   glVertex3f(1,-4,1);
   glVertex3f(1,0,1);
   glVertex3f(0,0,1);
   glEnd();
   glBegin(GL_QUADS);
   glVertex3f(-3,-4,1);
   glVertex3f(-2,-4,1);
   glVertex3f(-2,0,1);
   glVertex3f(-3,0,1);
   glEnd();
   glBegin(GL_QUADS);
   glVertex3f(-3,-4,-1);
   glVertex3f(-2,-4,-1);
   glVertex3f(-2,0,-1);
   glVertex3f(-3,0,-1);
   glEnd();
   glBegin(GL_QUADS);
   glVertex3f(-3,-4,-1);
   glVertex3f(-2,-4,-1);
   glVertex3f(-2,0,-1);
   glVertex3f(-3,0,-1);
   glEnd();
   glBegin(GL_QUADS);
   glVertex3f(-3,-4,-1);
   glVertex3f(-3,-4,1);
   glVertex3f(-3,0,1);
   glVertex3f(-3,0,-1);
   glEnd();
   glBegin(GL_QUADS);
   glVertex3f(1,-4,-1);
   glVertex3f(1,-4,1);
   glVertex3f(1,0,1);
   glVertex3f(1,0,-1);
   glEnd();


   glDisable(GL_TEXTURE_2D);
   glPopMatrix();
}

static void innerScreen(double x,double y,double z,
                 double dx,double dy,double dz,
                 double th)
{

      //  Save transformation
   glPushMatrix();
   //  Offset, scale and rotate
   glTranslated(x,y,z);
   glRotated(th,0,1,0);
   glScaled(dx,dy,dz);
   //  Enable textures
   glEnable(GL_TEXTURE_2D);
   glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,mode?GL_REPLACE:GL_MODULATE);
   glBindTexture(GL_TEXTURE_2D,texture[0]);

   //This section represents top of screen. One rectangluar prism, 2 quarter cylindrical prisms

   //top right quarter cylinder
   glBegin(GL_QUAD_STRIP);
   // glNormal3f(0,0,1);
   for(int i = 0; i <= 90; i+=10) {
      glTexCoord2f(0,0.5*i);glVertex3f(0.8+0.2*Cos(i), 0.8+0.2*Sin(i), 1);
      glTexCoord2f(1,0.5*i);glVertex3f(0.8+0.2*Cos(i),0.8+0.2*Sin(i), -1);
   }
   glEnd();
   glBegin(GL_TRIANGLE_FAN);
   glNormal3f( 0, 0, 1);
   glVertex3f(0.8,0.8,1);
   for(int n=0; n <=90; n+=10) {
      glTexCoord2f(n,1);
      glVertex3f(0.8+0.2*Cos(n), 0.8+0.2*Sin(n),1);
      glTexCoord2f(n,0);
   }
   glEnd();
   glBegin(GL_TRIANGLE_FAN);
   glVertex3f(0.8,0.8,-1);
   for(int n=0; n <=90; n+=10) {
      glTexCoord2f(n,1);
      glVertex3f(0.8+0.2*Cos(n), 0.8+0.2*Sin(n),-1);
      glTexCoord2f(n,0);
   }
   glEnd();
   glBegin(GL_QUADS);
   glNormal3f( 0, 0, -1);
   glVertex3f(-2.8,0,-1);
   glVertex3f(0.8,0,-1);
   glVertex3f(0.8,1,-1);
   glVertex3f(-2.8,1,-1);
   glEnd();
   // glBegin(GL_QUADS);
   // glNormal3f( 0, 0, 1);
   // glTexCoord2f(0,0);glVertex3f(-2.8,0,1);
   // glTexCoord2f(1,0);glVertex3f(.8,0,1);
   // glTexCoord2f(1,1);glVertex3f(0.8,1,1);
   // glTexCoord2f(0,1);glVertex3f(-2.8,1,1);
   // glEnd();
   glBegin(GL_QUADS);
   glNormal3f( 0, 1, 0);
   glTexCoord2f(0,0);glVertex3f(-2.8,1,-1);
   glTexCoord2f(1,0);glVertex3f(-2.8,1,1);
   glTexCoord2f(1,1);glVertex3f(0.8,1,1);
   glTexCoord2f(0,1);glVertex3f(0.8,1,-1);
   glEnd();
   //top left quarter cylinder
   glBegin(GL_QUAD_STRIP);
   for(int i = 0; i <= 90; i+=10) {
      glNormal3f(Cos(i),Sin(i),0);
      glVertex3f(-2.8-0.2*Cos(i), 0.8+0.2*Sin(i), 1);
      glVertex3f(-2.8-0.2*Cos(i),0.8+0.2*Sin(i), -1);
   }
   glEnd();
   glBegin(GL_TRIANGLE_FAN);
   glNormal3f( 0, 0, 1);
   glVertex3f(-2.8,0.8,1);
   for(int n=0; n <=90; n+=10) {
      glTexCoord2f(n,1);
      glVertex3f(-2.8-0.2*Cos(n), 0.8+0.2*Sin(n),1);
      glTexCoord2f(n,0);
   }
   glEnd();
   glBegin(GL_TRIANGLE_FAN);
   glVertex3f(-2.8,0.8,-1);
   for(int n=0; n <=90; n+=10) {
      glVertex3f(-2.8-0.2*Cos(n), 0.8+0.2*Sin(n),-1);
   }
   glEnd();

   //Body of screen
   // glBegin(GL_QUADS);
   // glVertex3f(-2,-4,-1);
   // glVertex3f(0,-4,-1);
   // glVertex3f(0,0,-1);
   // glVertex3f(-2,0,-1);
   // glEnd();

   // glBegin(GL_QUADS);
   // glVertex3f(-2,-4,1);
   // glVertex3f(0,-4,1);
   // glVertex3f(0,0,1);
   // glVertex3f(-2,0,1);
   // glEnd();

   //bottom of screen

   // bottom right quarter cylinder
   glBegin(GL_QUAD_STRIP);
   for(int i = 0; i <= 90; i+=10) {
      glNormal3f(Cos(i),Sin(i),0);
      glVertex3f(0.8+0.2*Cos(i), -4.8-0.2*Sin(i), 1);
      glVertex3f(0.8+0.2*Cos(i),-4.8-0.2*Sin(i), -1);
   }
   glEnd();
   glBegin(GL_TRIANGLE_FAN);
   glNormal3f( 0, 0, 1);
   glVertex3f(0.8,-4.8,1);
   for(int n=0; n <=90; n+=10) 
   {
      glTexCoord2f(n,1);
      glVertex3f(0.8+0.2*Cos(n), -4.8-0.2*Sin(n),1);
      glTexCoord2f(n,0);
   }
   glEnd();
   glBegin(GL_TRIANGLE_FAN);
   glVertex3f(0.8,-4.8,-1);
   for(int n=0; n <=90; n+=10) {
      glTexCoord2f(n,1);
      glVertex3f(0.8+0.2*Cos(n), -4.8-0.2*Sin(n),-1);
      glTexCoord2f(n,0);
   }
   glEnd();

   // Rectangular mid section
   glBegin(GL_QUADS);
   glTexCoord2f(0,0);glVertex3f(-2.8,-5,-1);
   glTexCoord2f(0,1);glVertex3f(0.8,-5,-1);
   glTexCoord2f(1,1);glVertex3f(0.8,1,-1);
   glTexCoord2f(0,1);glVertex3f(-2.8,1,-1);
   glEnd();
   glBegin(GL_QUADS);
   // glNormal3f( 0, 0, 1);
   glTexCoord2f(0,0);glVertex3f(-2.8,-5,1);
   glTexCoord2f(1,0);glVertex3f(0.8,-5,1);
   glTexCoord2f(1,1);glVertex3f(0.8,1,1);
   glTexCoord2f(0,1);glVertex3f(-2.8,1,1); //here
   glEnd();
   glBegin(GL_QUADS);
   // glNormal3f( 0, 0, -1);
   glTexCoord2f(0,0);glVertex3f(-2.8,-5,-1);
   glTexCoord2f(1,0);glVertex3f(-2.8,-5,1);
   glTexCoord2f(1,1);glVertex3f(0.8,-5,1);
   glTexCoord2f(0,1);glVertex3f(0.8,-5,-1);
   glEnd();

   //bottom left quarter cylinder
   glBegin(GL_QUAD_STRIP);
   for(int i = 0; i <= 90; i+=10) {
      glNormal3f(Cos(i),Sin(i),0);
      glVertex3f(-2.8-0.2*Cos(i), -4.8-0.2*Sin(i), 1);
      glVertex3f(-2.8-0.2*Cos(i),-4.8-0.2*Sin(i), -1);
   }
   glEnd();
   glBegin(GL_TRIANGLE_FAN);
   glNormal3f( 0, 0, 1);
   glVertex3f(-2.8,-4.8,1);
   for(int n=0; n <=90; n+=10) {
      glTexCoord2f(n,1);
      glVertex3f(-2.8-0.2*Cos(n), -4.8-0.2*Sin(n),1);
      glTexCoord2f(n,0);
   }
   glEnd();
   glBegin(GL_TRIANGLE_FAN);
   glVertex3f(-2.8,-4.8,-1);
   for(int n=0; n <=90; n+=10) {
      glTexCoord2f(n,1);
      glVertex3f(-2.8-0.2*Cos(n), -4.8-0.2*Sin(n),-1);
      glTexCoord2f(n,0);
   }
   glEnd();

   //sides
   glBegin(GL_QUADS);
   glVertex3f(0.8,-4.8,-1);
   glVertex3f(1,-4.8,-1);
   glVertex3f(1,0.8,-1);
   glVertex3f(0.8,0.8,-1);
   glEnd();
   glBegin(GL_QUADS);
   glNormal3f( 0, 0, 1);
   glTexCoord2f(0,0);glVertex3f(0.8,-4.8,1);
   glTexCoord2f(1,0);glVertex3f(1,-4.8,1);
   glTexCoord2f(1,1);glVertex3f(1,0.8,1);
   glTexCoord2f(0,1);glVertex3f(0.8,0.8,1);
   glEnd();
   glBegin(GL_QUADS);
   // glNormal3f( 0, 0, 1);
   glTexCoord2f(0,0);glVertex3f(-3,-4.8,1);
   glTexCoord2f(1,0);glVertex3f(-2.8,-4.8,1);
   glTexCoord2f(1,1);glVertex3f(-2.8,0.8,1);
   glTexCoord2f(0,1);glVertex3f(-3,0.8,1);
   glEnd();
   glBegin(GL_QUADS);
   glTexCoord2f(0,0);glVertex3f(-3,-4.8,-1);
   glTexCoord2f(1,0);glVertex3f(-2.8,-4.8,-1);
   glTexCoord2f(1,1);glVertex3f(-2.8,0.8,-1);
   glTexCoord2f(0,1);glVertex3f(-3,0.8,-1);
   glEnd();
   glBegin(GL_QUADS);
   glNormal3f(1,0,0);
   glVertex3f(0.8,-4.8,-0.8);
   glVertex3f(0.8,-4.8,0.8);
   glVertex3f(0.8,0.8,0.8);
   glVertex3f(0.8,0.8,-0.8);
   glEnd();
   glBegin(GL_QUADS);
   glNormal3f(-1,0,0);
   glVertex3f(-2.8,-4.8,-0.8);
   glVertex3f(-2.8,-4.8,0.8);
   glVertex3f(-2.8,0.8,0.8);
   glVertex3f(-2.8,0.8,-0.8);
   glEnd();

   glDisable(GL_TEXTURE_2D);
   glPopMatrix();
}

static void blackScreen(double x,double y,double z,
                 double dx,double dy,double dz,
                 double th)
{

      //  Save transformation
   glPushMatrix();
   //  Offset, scale and rotate
   glTranslated(x,y,z);
   glRotated(th,0,1,0);
   glScaled(dx,dy,dz);
   //  Enable textures
   glEnable(GL_TEXTURE_2D);
   glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,mode?GL_REPLACE:GL_MODULATE);
   glBindTexture(GL_TEXTURE_2D,texture[0]);

   //This section represents top of screen. One rectangluar prism, 2 quarter cylindrical prisms

   //top right quarter cylinder
   glBegin(GL_QUAD_STRIP);
   for(int i = 0; i <= 90; i+=10) {
      glVertex3f(0.8+0.2*Cos(i), 0.8+0.2*Sin(i), 1);
      glVertex3f(0.8+0.2*Cos(i),0.8+0.2*Sin(i), -1);
   }
   glEnd();
   glBegin(GL_TRIANGLE_FAN);
   glVertex3f(0.8,0.8,1);
   for(int n=0; n <=90; n+=10) {
      glVertex3f(0.8+0.2*Cos(n), 0.8+0.2*Sin(n),1);
   }
   glEnd();
   glBegin(GL_TRIANGLE_FAN);
   glVertex3f(0.8,0.8,-1);
   for(int n=0; n <=90; n+=10) {
      glVertex3f(0.8+0.2*Cos(n), 0.8+0.2*Sin(n),-1);
   }
   glEnd();
   glBegin(GL_QUADS);
   glVertex3f(-2.8,0,-1);
   glVertex3f(0.8,0,-1);
   glVertex3f(0.8,1,-1);
   glVertex3f(-2.8,1,-1);
   glEnd();
   glBegin(GL_QUADS);
   glVertex3f(-2.8,0,1);
   glVertex3f(.8,0,1);
   glVertex3f(0.8,1,1);
   glVertex3f(-2.8,1,1);
   glEnd();
   glBegin(GL_QUADS);
   glVertex3f(-2.8,1,-1);
   glVertex3f(-2.8,1,1);
   glVertex3f(0.8,1,1);
   glVertex3f(0.8,1,-1);
   glEnd();
   //top left quarter cylinder
   glBegin(GL_QUAD_STRIP);
   for(int i = 0; i <= 90; i+=10) {
      glVertex3f(-2.8-0.2*Cos(i), 0.8+0.2*Sin(i), 1);
      glVertex3f(-2.8-0.2*Cos(i),0.8+0.2*Sin(i), -1);
   }
   glEnd();
   glBegin(GL_TRIANGLE_FAN);
   glVertex3f(-2.8,0.8,1);
   for(int n=0; n <=90; n+=10) {
      glVertex3f(-2.8-0.2*Cos(n), 0.8+0.2*Sin(n),1);
   }
   glEnd();
   glBegin(GL_TRIANGLE_FAN);
   glVertex3f(-2.8,0.8,-1);
   for(int n=0; n <=90; n+=10) {
      glVertex3f(-2.8-0.2*Cos(n), 0.8+0.2*Sin(n),-1);
   }
   glEnd();

   //Body of screen
   // glBegin(GL_QUADS);
   // glVertex3f(-2,-4,-1);
   // glVertex3f(0,-4,-1);
   // glVertex3f(0,0,-1);
   // glVertex3f(-2,0,-1);
   // glEnd();

   // glBegin(GL_QUADS);
   // glVertex3f(-2,-4,1);
   // glVertex3f(0,-4,1);
   // glVertex3f(0,0,1);
   // glVertex3f(-2,0,1);
   // glEnd();

   //bottom of screen

   // bottom right quarter cylinder
   glBegin(GL_QUAD_STRIP);
   for(int i = 0; i <= 90; i+=10) {
      glVertex3f(0.8+0.2*Cos(i), -4.8-0.2*Sin(i), 1);
      glVertex3f(0.8+0.2*Cos(i),-4.8-0.2*Sin(i), -1);
   }
   glEnd();
   glBegin(GL_TRIANGLE_FAN);
   glVertex3f(0.8,-4.8,1);
   for(int n=0; n <=90; n+=10) {
      glVertex3f(0.8+0.2*Cos(n), -4.8-0.2*Sin(n),1);
   }
   glEnd();
   glBegin(GL_TRIANGLE_FAN);
   glVertex3f(0.8,-4.8,-1);
   for(int n=0; n <=90; n+=10) {
      glVertex3f(0.8+0.2*Cos(n), -4.8-0.2*Sin(n),-1);
   }
   glEnd();

   // Rectangular mid section
   glBegin(GL_QUADS);
   glVertex3f(-2.8,-5,-1);
   glVertex3f(0.8,-5,-1);
   glVertex3f(0.8,1,-1);
   glVertex3f(-2.8,1,-1);
   glEnd();
   glBegin(GL_QUADS);
   glVertex3f(-2.8,-5,1);
   glVertex3f(0.8,-5,1);
   glVertex3f(0.8,0.8,1);
   glVertex3f(-2.8,0.8,1); //here
   glEnd();
   glBegin(GL_QUADS);
   glVertex3f(-2.8,-5,-1);
   glVertex3f(-2.8,-5,1);
   glVertex3f(0.8,-5,1);
   glVertex3f(0.8,-5,-1);
   glEnd();

   //bottom left quarter cylinder
   glBegin(GL_QUAD_STRIP);
   for(int i = 0; i <= 90; i+=10) {
      glVertex3f(-2.8-0.2*Cos(i), -4.8-0.2*Sin(i), 1);
      glVertex3f(-2.8-0.2*Cos(i),-4.8-0.2*Sin(i), -1);
   }
   glEnd();
   glBegin(GL_TRIANGLE_FAN);
   glVertex3f(-2.8,-4.8,1);
   for(int n=0; n <=90; n+=10) {
      glVertex3f(-2.8-0.2*Cos(n), -4.8-0.2*Sin(n),1);
   }
   glEnd();
   glBegin(GL_TRIANGLE_FAN);
   glVertex3f(-2.8,-4.8,-1);
   for(int n=0; n <=90; n+=10) {
      glVertex3f(-2.8-0.2*Cos(n), -4.8-0.2*Sin(n),-1);
   }
   glEnd();

   //sides
   glBegin(GL_QUADS);
   glVertex3f(0.8,-4.8,-1);
   glVertex3f(1,-4.8,-1);
   glVertex3f(1,0.8,-1);
   glVertex3f(0.8,0.8,-1);
   glEnd();
   glBegin(GL_QUADS);
   glVertex3f(0.8,-4.8,1);
   glVertex3f(1,-4.8,1);
   glVertex3f(1,0.8,1);
   glVertex3f(0.8,0.8,1);
   glEnd();
   glBegin(GL_QUADS);
   glVertex3f(-3,-4.8,1);
   glVertex3f(-2.8,-4.8,1);
   glVertex3f(-2.8,0.8,1);
   glVertex3f(-3,0.8,1);
   glEnd();
   glBegin(GL_QUADS);
   glVertex3f(-3,-4.8,-1);
   glVertex3f(-2.8,-4.8,-1);
   glVertex3f(-2.8,0.8,-1);
   glVertex3f(-3,0.8,-1);
   glEnd();
   glBegin(GL_QUADS);
   glVertex3f(0.8,-4.8,-0.8);
   glVertex3f(0.8,-4.8,0.8);
   glVertex3f(0.8,0.8,0.8);
   glVertex3f(0.8,0.8,-0.8);
   glEnd();
   glBegin(GL_QUADS);
   glVertex3f(-2.8,-4.8,-0.8);
   glVertex3f(-2.8,-4.8,0.8);
   glVertex3f(-2.8,0.8,0.8);
   glVertex3f(-2.8,0.8,-0.8);
   glEnd();

   glDisable(GL_TEXTURE_2D);
   glPopMatrix();
}

static void back(double x,double y,double z,
                 double dx,double dy,double dz,
                 double th)
{
   glPushMatrix();
   // //  Offset, scale and rotate
   glTranslated(x,y,z);
   glRotated(th,0,1,0);
   glScaled(dx,dy,dz);
   //  Enable textures
   glEnable(GL_TEXTURE_2D);
   glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,mode?GL_REPLACE:GL_MODULATE);
   // glColor3f(.1,.1,.1);
   glBindTexture(GL_TEXTURE_2D,texture[0]);

   glBegin(GL_QUAD_STRIP);
   for(int i = 0; i <= 180; i+=10) {
      glNormal3f(0,Cos(i),Sin(i));
      glTexCoord2f(0,0.5*i);glVertex3f(1,Cos(i), 0.3*Sin(i));
      glTexCoord2f(1,0.5*i);glVertex3f(-1,Cos(i),0.3*Sin(i));
   }
   glEnd();
   glBegin(GL_TRIANGLE_FAN);
   glNormal3f(-1, 0, 0);
   glTexCoord2f(0.5,0.5);glVertex3f(-1,0,0);
   for(int n=0; n <=180; n+=10) {
      glTexCoord2f(0.5*Cos(n)+0.5,0.5*Sin(n)+0.5);
      glVertex3f(-1,Cos(n), 0.3*Sin(n));
   }
   glEnd();
   glBegin(GL_TRIANGLE_FAN);
   glNormal3f(1, 0, 0);
   glTexCoord2f(0.5,0.5);glVertex3f(1,0,0);
   for(int n=0; n <=180; n+=10) {
      glTexCoord2f(0.5*Cos(n)+0.5,0.5*Sin(n)+0.5);
      glVertex3f(1,Cos(n), 0.3*Sin(n));
   }
   glEnd();

   glBegin(GL_QUAD_STRIP);
   glNormal3f(0,0,1);
   glTexCoord2f(0,0);glVertex3f(-0.8,1, 0);
   glTexCoord2f(0,1);glVertex3f(0.8,1,0);
   glTexCoord2f(1,1);glVertex3f(-0.8,1.7,0);
   glTexCoord2f(1,0);glVertex3f(0.8,1.7,0);
   glEnd();
   glBegin(GL_QUAD_STRIP);
   glTexCoord2f(0,0);glVertex3f(1,-1,0);
   glTexCoord2f(0,1);glVertex3f(-1,-1,0);
   glTexCoord2f(1,1);glVertex3f(1,-1,-0.2);
   glTexCoord2f(1,0);glVertex3f(-1,-1, -0.2);
   glEnd();
   glBegin(GL_QUAD_STRIP);
   glNormal3f(1,0,0);
   glTexCoord2f(0,0);glVertex3f(1,-1,-0.2);
   glTexCoord2f(0,1);glVertex3f(1,-1,0);
   glTexCoord2f(1,1);glVertex3f(1,1,-0.2);
   glTexCoord2f(1,0);glVertex3f(1,1,0);
   glEnd();
   glBegin(GL_QUAD_STRIP);
   glNormal3f(-1,0,0);
   glTexCoord2f(0,0);glVertex3f(-1,-1,-0.2);
   glTexCoord2f(0,1);glVertex3f(-1,-1,0);
   glTexCoord2f(1,1);glVertex3f(-1,1,-0.2);
   glTexCoord2f(1,0);glVertex3f(-1,1,0);
   glEnd();

   glBegin(GL_QUAD_STRIP);
   for(int i = 0; i <= 90; i+=10) {
      glNormal3f(Cos(i),0,Sin(i));
      glTexCoord2f(0,0.5*i);glVertex3f(0.8+0.2*Cos(i), 1, -0.2+0.2*Sin(i));
      glTexCoord2f(1,0.5*i);glVertex3f(0.8+0.2*Cos(i), 1.8, -0.2+0.2*Sin(i));
   }
   glEnd();
   glBegin(GL_TRIANGLE_FAN);
   glNormal3f(0,1,0);
   glTexCoord2f(0.5,0.5);
   glVertex3f(0.8,1.8, -0.2);
   for(int n=0; n <=90; n+=10) {
      glTexCoord2f(0.5*Cos(n)+0.5,0.5*Sin(n)+0.5);
      glVertex3f(0.8+0.2*Cos(n),1.8, -0.2+0.2*Sin(n));
   }
   glEnd();
   glBegin(GL_QUAD_STRIP);
   for(int i = 0; i <= 90; i+=10) {
      glNormal3f(-Cos(i),0,Sin(i));
      glTexCoord2f(0,0.5*i);glVertex3f(-0.8-0.2*Cos(i), 1, -0.2+0.2*Sin(i));
      glTexCoord2f(1,0.5*i);glVertex3f(-0.8-0.2*Cos(i), 1.8, -0.2+0.2*Sin(i));
   }
   glEnd();
   glBegin(GL_TRIANGLE_FAN);
   glTexCoord2f(0.5,0.5);
   glNormal3f(0,1,0);
   glVertex3f(-0.8,1.8, -0.2);
   for(int n=0; n <=90; n+=10) {
      glTexCoord2f(0.5*Cos(n)+0.5,0.5*Sin(n)+0.5);
      glVertex3f(-0.8-0.2*Cos(n),1.8, -0.2+0.2*Sin(n));
   }
   glEnd();
   // glBegin(GL_QUAD_STRIP);
   // for(int i = 0; i <= 90; i+=10) {
   //    glVertex3f(Cos(i), -1, -0.2+0.2*Sin(i));
   //    glVertex3f(Cos(i), 0.3*Sin(i), 0.3*Sin(i));
   // }
   // glEnd();

   glDisable(GL_TEXTURE_2D);
   glPopMatrix();
}

// static void power(double x,double y,double z,
//                  double dx,double dy,double dz,
//                  double th)
// {
//    //  Save transformation
//    glPushMatrix();
//    //  Offset, scale and rotate
//    glTranslated(x,y,z);
//    glRotated(th,0,1,0);
//    glScaled(dx,dy,dz);
//    //  Enable textures
//    glEnable(GL_TEXTURE_2D);
//    glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,mode?GL_REPLACE:GL_MODULATE);
//    glBindTexture(GL_TEXTURE_2D,texture[0]);

//    glBegin(GL_QUADS);
//    glVertex3f(0,0,0);
//    glVertex3f(0,1,0);
//    glVertex3f(1,1,0);
//    glVertex3f(1,0,0);
//    glEnd();
//    glBegin(GL_QUADS);
//    glVertex3f(0,0,2);
//    glVertex3f(0,1,2);
//    glVertex3f(1,1,2);
//    glVertex3f(1,0,2);
//    glEnd();
//    glBegin(GL_QUADS);
//    glVertex3f(0,0,0);
//    glVertex3f(0,0,2);
//    glVertex3f(0,1,2);
//    glVertex3f(0,1,0);
//    glEnd();
//    glBegin(GL_QUADS);
//    glVertex3f(1,0,0);
//    glVertex3f(1,0,2);
//    glVertex3f(1,1,2);
//    glVertex3f(1,1,0);
//    glEnd();
//    glBegin(GL_QUADS);
//    glVertex3f(1,1,0);
//    glVertex3f(0,1,0);
//    glVertex3f(0,1,2);
//    glVertex3f(1,1,2);
//    glEnd();
//    //top part
//    glBegin(GL_QUADS);
//    glVertex3f(0,1,0.9);
//    glVertex3f(0,1,1.1);
//    glVertex3f(0,1.2,1.1);
//    glVertex3f(0,1.2,0.9);
//    glEnd();
//    glBegin(GL_QUADS);
//    glVertex3f(1,1,0.9);
//    glVertex3f(1,1,1.1);
//    glVertex3f(1,1.2,1.1);
//    glVertex3f(1,1.2,0.9);
//    glEnd();
//    glBegin(GL_QUADS);
//    glVertex3f(0,1  ,1.1);
//    glVertex3f(0,1.2,1.1);
//    glVertex3f(1,1.2,1.1);
//    glVertex3f(1,1  ,1.1);
//    glEnd();
//    glBegin(GL_QUADS);
//    glVertex3f(0,1  ,0.9);
//    glVertex3f(0,1.2,0.9);
//    glVertex3f(1,1.2,0.9);
//    glVertex3f(1,1  ,0.9);
//    glEnd();
//    glBegin(GL_QUADS);
//    glVertex3f(0,1.2,0.9);
//    glVertex3f(0,1.2,1.1);
//    glVertex3f(1,1.2,1.1);
//    glVertex3f(1,1.2,0.9);
//    glEnd();

//    glDisable(GL_TEXTURE_2D);
//    glPopMatrix();
// }

static void midScreen(double x,double y,double z,
                 double dx,double dy,double dz,
                 double th)
{
       //  Save transformation
   glPushMatrix();
   //  Offset, scale and rotate
   glTranslated(x,y,z);
   glRotated(th,0,1,0);
   glScaled(dx,dy,dz);
   //  Enable textures
   glEnable(GL_TEXTURE_2D);
   glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,mode?GL_REPLACE:GL_MODULATE);
   glBindTexture(GL_TEXTURE_2D,texture[0]);

   //This section represents top of screen. One rectangluar prism, 2 quarter cylindrical prisms

   // top right quarter cylinder
   glBegin(GL_QUAD_STRIP);
   // glNormal3f(0,0,1);
   for(int i = 0; i <= 90; i+=10) {
      glNormal3f(Cos(i),Sin(i),0);
      glTexCoord2f(0,0.5*i);glVertex3f(0.8+0.2*Cos(i), 0.8+0.2*Sin(i), 1);
      glTexCoord2f(1,0.5*i);glVertex3f(0.8+0.2*Cos(i),0.8+0.2*Sin(i), -1);
   }
   glEnd();
   glBegin(GL_TRIANGLE_FAN);
   glNormal3f(0,0,1);
   glVertex3f(0.8,0.8,1);
   for(int n=0; n <=90; n+=10) {
      glVertex3f(0.8+0.2*Cos(n), 0.8+0.2*Sin(n),1);
   }
   glEnd();
   glBegin(GL_TRIANGLE_FAN);
   glNormal3f(0,0,-1);
   glVertex3f(0.8,0.8,-1);
   for(int n=0; n <=90; n+=10) {
      glVertex3f(0.8+0.2*Cos(n), 0.8+0.2*Sin(n),-1);
   }
   glEnd();
   glBegin(GL_QUADS);
   glNormal3f(0,0,-1);
   glTexCoord2f(0,0);glVertex3f(-2.8,0,-1);
   glTexCoord2f(0,1);glVertex3f(0.8,0,-1);
   glTexCoord2f(1,1);glVertex3f(0.8,1,-1);
   glTexCoord2f(1,0);glVertex3f(-2.8,1,-1);
   glEnd();
   glBegin(GL_QUADS);
   glTexCoord2f(0,0);glVertex3f(-2.8,0,1);
   glTexCoord2f(0,1);glVertex3f(.8,0,1);
   glTexCoord2f(1,1);glVertex3f(0.8,1,1);
   glTexCoord2f(1,0);glVertex3f(-2.8,1,1);
   glEnd();
   glBegin(GL_QUADS);
   glTexCoord2f(0,0);glVertex3f(-2.8,1,-1);
   glTexCoord2f(0,1);glVertex3f(-2.8,1,1);
   glTexCoord2f(1,1);glVertex3f(0.8,1,1);
   glTexCoord2f(1,0);glVertex3f(0.8,1,-1);
   glEnd();
   //top left quarter cylinder
   glBegin(GL_QUAD_STRIP);
   for(int i = 0; i <= 90; i+=10) {
      glNormal3f(-Cos(i),Sin(i),0);
      glTexCoord2f(0,0.5*i);glVertex3f(-2.8-0.2*Cos(i), 0.8+0.2*Sin(i), 1);
      glTexCoord2f(1,0.5*i);glVertex3f(-2.8-0.2*Cos(i),0.8+0.2*Sin(i), -1);
   }
   glEnd();
   glBegin(GL_TRIANGLE_FAN);
   glNormal3f(0,0,1);
   glVertex3f(-2.8,0.8,1);
   glTexCoord2f(0.5,0.5);
   for(int n=0; n <=90; n+=10) {
      glTexCoord2f(0.5*Cos(n)+0.5,0.5*Sin(n)+0.5);
      glVertex3f(-2.8-0.2*Cos(n), 0.8+0.2*Sin(n),1);
   }
   glEnd();
   glBegin(GL_TRIANGLE_FAN);
   glNormal3f(0,0,-1);
   glVertex3f(-2.8,0.8,-1);
   glTexCoord2f(0.5,0.5);
   for(int n=0; n <=90; n+=10) {
      glTexCoord2f(0.5*Cos(n)+0.5,0.5*Sin(n)+0.5);
      glVertex3f(-2.8-0.2*Cos(n), 0.8+0.2*Sin(n),-1);
   }
   glEnd();

   
   // bottom right quarter cylinder
   glBegin(GL_QUAD_STRIP);
   for(int i = 0; i <= 90; i+=10) {
      glNormal3f(Cos(i),-Sin(i),0);
      glTexCoord2f(0,0.5*i);glVertex3f(0.8+0.2*Cos(i), -4.8-0.2*Sin(i), 1);
      glTexCoord2f(1,0.5*i);glVertex3f(0.8+0.2*Cos(i),-4.8-0.2*Sin(i), -1);
   }
   glEnd();
   glBegin(GL_TRIANGLE_FAN);
   glNormal3f(0,0,1);
   glVertex3f(0.8,-4.8,1);
   for(int n=0; n <=90; n+=10) {
      glVertex3f(0.8+0.2*Cos(n), -4.8-0.2*Sin(n),1);
   }
   glEnd();
   glBegin(GL_TRIANGLE_FAN);
   glNormal3f(0,0,-1);
   glVertex3f(0.8,-4.8,-1);
   glTexCoord2f(0.5,0.5);
   for(int n=0; n <=90; n+=10) {
      glTexCoord2f(0.5*Cos(n)+0.5,0.5*Sin(n)+0.5);
      glVertex3f(0.8+0.2*Cos(n), -4.8-0.2*Sin(n),-1);
   }
   glEnd();

   // // Rectangular mid section
   glBegin(GL_QUADS);
   glTexCoord2f(0,0);glVertex3f(-2.8,-5,-1);
   glTexCoord2f(0,1);glVertex3f(0.8,-5,-1);
   glTexCoord2f(1,1);glVertex3f(0.8,1,-1);
   glTexCoord2f(1,0);glVertex3f(-2.8,1,-1);
   glEnd();
   glBegin(GL_QUADS);
   glTexCoord2f(0,0);glVertex3f(-2.8,-5,1);
   glTexCoord2f(0,1);glVertex3f(0.8,-5,1);
   glTexCoord2f(1,1);glVertex3f(0.8,0.8,1);
   glTexCoord2f(1,0);glVertex3f(-2.8,0.8,1); 
   glEnd();
   glBegin(GL_QUADS);
   glTexCoord2f(0,0);glVertex3f(-2.8,-5,-1);
   glTexCoord2f(0,1);glVertex3f(-2.8,-5,1);
   glTexCoord2f(1,1);glVertex3f(0.8,-5,1);
   glTexCoord2f(1,0);glVertex3f(0.8,-5,-1);
   glEnd();

   //bottom left quarter cylinder
   glBegin(GL_QUAD_STRIP);
   for(int i = 0; i <= 90; i+=10) {
      glNormal3f(-Cos(i),-Sin(i),0);
      glTexCoord2f(0,0.5*i);glVertex3f(-2.8-0.2*Cos(i), -4.8-0.2*Sin(i), 1);
      glTexCoord2f(1,0.5*i);glVertex3f(-2.8-0.2*Cos(i),-4.8-0.2*Sin(i), -1);
   }
   glEnd();
   glBegin(GL_TRIANGLE_FAN);
   glVertex3f(-2.8,-4.8,1);
   for(int n=0; n <=90; n+=10) {
      glVertex3f(-2.8-0.2*Cos(n), -4.8-0.2*Sin(n),1);
   }
   glEnd();
   glBegin(GL_TRIANGLE_FAN);
   glNormal3f(0,0,-1);
   glVertex3f(-2.8,-4.8,-1);
   for(int n=0; n <=90; n+=10) {
      glTexCoord2f(0.5*Cos(n)+0.5,0.5*Sin(n)+0.5);
      glVertex3f(-2.8-0.2*Cos(n), -4.8-0.2*Sin(n),-1);
   }
   glEnd();

   //sides
   glBegin(GL_QUADS);
   glTexCoord2f(0,0);glVertex3f(0.8,-4.8,-1);
   glTexCoord2f(0,1);glVertex3f(1,-4.8,-1);
   glTexCoord2f(1,1);glVertex3f(1,0.8,-1);
   glTexCoord2f(1,0);glVertex3f(0.8,0.8,-1);
   glEnd();
   glBegin(GL_QUADS);
   glTexCoord2f(0,0);glVertex3f(0.8,-4.8,1);
   glTexCoord2f(0,1);glVertex3f(1,-4.8,1);
   glTexCoord2f(1,1);glVertex3f(1,0.8,1);
   glTexCoord2f(1,0);glVertex3f(0.8,0.8,1);
   glEnd();
   glBegin(GL_QUADS);
   glTexCoord2f(0,0);glVertex3f(-3,-4.8,1);
   glTexCoord2f(0,1);glVertex3f(-2.8,-4.8,1);
   glTexCoord2f(1,1);glVertex3f(-2.8,0.8,1);
   glTexCoord2f(1,0);glVertex3f(-3,0.8,1);
   glEnd();
   glBegin(GL_QUADS);
   glTexCoord2f(0,0);glVertex3f(-3,-4.8,-1);
   glTexCoord2f(0,1);glVertex3f(-2.8,-4.8,-1);
   glTexCoord2f(1,1);glVertex3f(-2.8,0.8,-1);
   glTexCoord2f(1,0);glVertex3f(-3,0.8,-1);
   glEnd();

   glBegin(GL_QUAD_STRIP);
   glNormal3f(-1,0,0);
   glTexCoord2f(0,0);glVertex3f(-3,0,-1);
   glTexCoord2f(0,1);glVertex3f(-3,0.8,-1);
   glTexCoord2f(1,1);glVertex3f(-3,0,1);
   glTexCoord2f(1,0);glVertex3f(-3,0.8,1);
   glEnd();
   // glBegin(GL_QUAD_STRIP);
   // glVertex3f(-3,-5,-1);
   // glVertex3f(-3,-1,-1);
   // glVertex3f(-3,-5,1);
   // glVertex3f(-3,-1,1);
   // glEnd();
   // glColor3f(0.3,0.3,0.3);
   glBegin(GL_QUAD_STRIP);
   glNormal3f(0,-1,0);
   glTexCoord2f(0,0);glVertex3f(-2.8, -1, -1);
   glTexCoord2f(0,1);glVertex3f(-3, -1, -1);
   glTexCoord2f(1,1);glVertex3f(-2.8, -1, 1);
   glTexCoord2f(1,0);glVertex3f(-3, -1, 1);
   glEnd();
   glBegin(GL_QUAD_STRIP);
   // glNormal3f(0,0,0);
   glTexCoord2f(0,0);glVertex3f(-2.8, 0, -1);
   glTexCoord2f(0,1);glVertex3f(-3, 0, -1);
   glTexCoord2f(1,1);glVertex3f(-2.8, 0, 1);
   glTexCoord2f(1,0);glVertex3f(-3, 0, 1);
   glEnd();
   glBegin(GL_QUAD_STRIP);
   glTexCoord2f(0,0);glVertex3f(-2.8, -1, -1);
   glTexCoord2f(0,1);glVertex3f(-2.8, -1, -0.1);
   glTexCoord2f(1,1);glVertex3f(-2.8, 0, -1);
   glTexCoord2f(1,0);glVertex3f(-2.8, 0, -0.1);
   glEnd();
   glBegin(GL_QUAD_STRIP);
   glNormal3f(-1,0,0);
   glTexCoord2f(0,0);glVertex3f(-2.8, -1, 0.1);
   glTexCoord2f(0,1);glVertex3f(-2.8, -1, 1);
   glTexCoord2f(1,1);glVertex3f(-2.8, 0, 0.1);
   glTexCoord2f(1,0);glVertex3f(-2.8, 0, 1);
   glEnd();
   glBegin(GL_QUAD_STRIP);
   glNormal3f(-1,0,0);
   glTexCoord2f(0,0);glVertex3f(-2.6, -1, -0.1);
   glTexCoord2f(0,1);glVertex3f(-2.6, -1, 0.1);
   glTexCoord2f(1,1);glVertex3f(-2.6, 0, -0.1);
   glTexCoord2f(1,0);glVertex3f(-2.6, 0, 0.1);
   glEnd();
   glBegin(GL_QUADS);
   // glNormal3f(0,0,-1);
   glTexCoord2f(0,0);glVertex3f(-2.8,-1,-.1);
   glTexCoord2f(0,1);glVertex3f(-2.6,-1,-.1);
   glTexCoord2f(1,1);glVertex3f(-2.6,0 ,-.1);
   glTexCoord2f(1,0);glVertex3f(-2.8,0 ,-.1);
   glEnd();
   glBegin(GL_QUADS);
   // glNormal3f(0,0,1);
   glTexCoord2f(0,0);glVertex3f(-2.8,-1,.1);
   glTexCoord2f(0,1);glVertex3f(-2.6,-1,.1);
   glTexCoord2f(1,1);glVertex3f(-2.6,0 ,.1);
   glTexCoord2f(1,0);glVertex3f(-2.8,0 ,.1);
   glEnd();
   glBegin(GL_QUADS);
   glNormal3f(0,0,-1);
   glTexCoord2f(0,0);glVertex3f(-2.8,-1,-.1);
   glTexCoord2f(0,1);glVertex3f(-2.8,-1,.1);
   glTexCoord2f(1,1);glVertex3f(-2.6,-1,.1);
   glTexCoord2f(1,0);glVertex3f(-2.6,-1,-.1);
   glEnd();
   glBegin(GL_QUADS);
   glNormal3f(-1,0,0);
   glTexCoord2f(0,0);glVertex3f(-2.8,0,-.1);
   glTexCoord2f(0,1);glVertex3f(-2.8,0,.1);
   glTexCoord2f(1,1);glVertex3f(-2.6,0,.1);
   glTexCoord2f(1,0);glVertex3f(-2.6,0,-.1);
   glEnd();
   // glColor3f(1,1,1);
   glBegin(GL_QUADS);
   glNormal3f(-1,0,0);
   glTexCoord2f(0,0);glVertex3f(-3,-4.8,-1);
   glTexCoord2f(1,0);glVertex3f(-3,-4.8,1);
   glTexCoord2f(1,1);glVertex3f(-3,-1,1);
   glTexCoord2f(0,1);glVertex3f(-3,-1,-1);
   glEnd();
   glBegin(GL_QUADS);
   glNormal3f(1,0,0);
   glTexCoord2f(0,0);glVertex3f(1,-4.8,-1);
   glTexCoord2f(1,0);glVertex3f(1,-4.8,1);
   glTexCoord2f(1,1);glVertex3f(1,0.8,1);
   glTexCoord2f(0,1);glVertex3f(1,0.8,-1);
   glEnd();

   glDisable(GL_TEXTURE_2D);
   glPopMatrix();
}

/*
 *  OpenGL (GLUT) calls this routine to display the scene
 */
void display()
{
   //  Eye position
   double Ex = -2*dim*Sin(th)*Cos(ph);
   double Ey = +2*dim        *Sin(ph);
   double Ez = +2*dim*Cos(th)*Cos(ph);
   //  Erase the window and the depth buffer
   glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
   //  Enable Z-buffering in OpenGL
   glEnable(GL_DEPTH_TEST);
   //  Set perspective
   glLoadIdentity();
   gluLookAt(Ex,Ey,Ez , 0,0,0 , 0,Cos(ph),0);
   //  Light switch
   float Ambient[]   = {0.01*ambient ,0.01*ambient ,0.01*ambient ,1.0};
   float Position[]  = {5*Cos(zh),ylight,5*Sin(zh),1};
   if (light)
   {
      //  Translate intensity to color vectors
      // float Ambient[]   = {0.01*ambient ,0.01*ambient ,0.01*ambient ,1.0};
      float Diffuse[]   = {0.01*diffuse ,0.01*diffuse ,0.01*diffuse ,1.0};
      float Specular[]  = {0.01*specular,0.01*specular,0.01*specular,1.0};
      
      //  Draw light position as ball (still no lighting here)
      glColor3f(1,1,1);
      ball(Position[0],Position[1],Position[2] , 0.1);
      //  OpenGL should normalize normal vectors
      glEnable(GL_NORMALIZE);
      //  Enable lighting
      glEnable(GL_LIGHTING);
      //  glColor sets ambient and diffuse color materials
      glColorMaterial(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE);
      glEnable(GL_COLOR_MATERIAL);
      //  Enable light 0
      glEnable(GL_LIGHT0);
      //  Set ambient, diffuse, specular components and position of light 0
      glLightfv(GL_LIGHT0,GL_AMBIENT ,Ambient);
      glLightfv(GL_LIGHT0,GL_DIFFUSE ,Diffuse);
      glLightfv(GL_LIGHT0,GL_SPECULAR,Specular);
      glLightfv(GL_LIGHT0,GL_POSITION,Position);

      glColor3f(0.1,0.1,0.1);
      dPad(-0.5,-0.3,-0.05,.15,.15,.05,0);
      aButton(0.3,-0.35,-0.05,.05,.1,.1,90);
      bButton(0.6,-0.25,-0.05,.05,.1,.1,90);
      outerScreen(-0.1,-0.8,-0.05,0.03,0.01,0.01,0);
      outerScreen(0.1,-0.8,-0.05,0.03,0.01,0.01,0);
      glColor3f(0.3,0.0,0.9);
      innerScreen(0.5,1.25,-0.1,0.5,0.5,0.01,0);
      midScreen(0.5,1.25,-0.2,0.5,0.5,0.1,0); 
      glColor3f(0.1,0.1,0.1);
      blackScreen(0.42,1.3,-0.09,0.4,0.25,0.01,0);
      glColor3f(0.3,0.0,0.9);
      back(0,-0.3,-0.36,1,0.8,0.3,180);
      glDisable(GL_LIGHTING);
      glColor3f(1,1,1);
   }
   else {
      glDisable(GL_LIGHTING);
      back(0,-0.3,-0.36,1,0.8,0.3,180);
   }
   //Testing
   // midScreen(0,0,0,0.5,0.5,0.5,0);   
   // power(0,0,0,0.5,0.5,0.5,0);
   // back(0,0,0,0.5,0.5,0.5,0);
   // dPad(-0.5,-0.3,-0.05,.15,.15,.05,0);
   //  Draw scene
   // glColor3f(0.1,0.1,0.1);
   // dPad(-0.5,-0.3,-0.05,.15,.15,.05,0);
   // aButton(0.3,-0.35,-0.05,.05,.1,.1,90);
   // bButton(0.6,-0.25,-0.05,.05,.1,.1,90);
   // outerScreen(-0.1,-0.8,-0.05,0.03,0.01,0.01,0);
   // outerScreen(0.1,-0.8,-0.05,0.03,0.01,0.01,0);
   // glColor3f(0.3,0.0,0.9);
   // innerScreen(0.5,1.25,-0.1,0.5,0.5,0.01,0);
   // midScreen(0.5,1.25,-0.2,0.5,0.5,0.1,0); 
   // glColor3f(0.1,0.1,0.1);
   // blackScreen(0.42,1.3,-0.09,0.4,0.25,0.01,0);
   // glColor3f(0.3,0.0,0.9);
   // back(0,-0.3,-0.36,1,0.8,0.3,180);
   // glDisable(GL_LIGHTING);
   // glColor3f(1,1,1);
   if (axes)
   {
      const double len=1.5;  //  Length of axes
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
   glWindowPos2i(5,5);
   // Print("Angle=%d,%d  Dim=%.1f Light=%s Texture=%s",th,ph,dim,light?"On":"Off",mode?"Replace":"Modulate");
   if (light)
   {
      glWindowPos2i(5,25);
      // Print("Ambient=%d  Diffuse=%d Specular=%d Emission=%d Shininess=%.0f",ambient,diffuse,specular,emission,shiny);
   }
   //  Render the scene and make it visible
   ErrCheck("display");
   glFlush();
   glutSwapBuffers();
}

/*
 *  GLUT calls this routine when the window is resized
 */
void idle()
{
   //  Elapsed time in seconds
   double t = glutGet(GLUT_ELAPSED_TIME)/10000.0;
   zh = fmod(90*t,360.0);
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
   //  Keep angles to +/-360 degrees
   th %= 360;
   ph %= 360;
   //  Update projection
   Project(45,asp,dim);
   //  Tell GLUT it is necessary to redisplay the scene
   glutPostRedisplay();
}

/*
 *  GLUT calls this routine when a key is pressed
 */
void key(unsigned char ch,int x,int y)
{
   //  Exit on ESC
   if (ch == 27)
      exit(0);
   //  Reset view angle
   else if (ch == '0')
      th = ph = 0;
   //  Toggle texture mode
   else if (ch == 'm' || ch == 'M')
      mode = 1-mode;
   //  Toggle axes
   else if (ch == 'x' || ch == 'X')
      axes = 1-axes;
   //  Toggle lighting
   else if (ch == 'b' || ch == 'B')
      light = 1-light;
   //  Toggle textures mode
   //  Translate shininess power to value (-1 => 0)
   //  Reproject
   Project(45,asp,dim);
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
   glViewport(0,0, RES*width,RES*height);
   //  Set projection
   Project(45,asp,dim);
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
   glutInitWindowSize(600,600);
   glutCreateWindow("Jack Higgins");
#ifdef USEGLEW
   //  Initialize GLEW
   if (glewInit()!=GLEW_OK) Fatal("Error initializing GLEW\n");
#endif
   //  Set callbacks
   glutDisplayFunc(display);
   glutReshapeFunc(reshape);
   glutSpecialFunc(special);
   glutKeyboardFunc(key);
   glutIdleFunc(idle);
   //  Load textures
   texture[0] = LoadTexBMP("plastic.bmp");
   texture[1] = LoadTexBMP("aButton.bmp");
   texture[2] = LoadTexBMP("bButton.bmp");
   // texture[3] = LoadTexBMP("arrow.bmp");
   // texture[4] = LoadTexBMP("a1.bmp");
   // texture[5] = LoadTexBMP("a2.bmp");
   // texture[6] = LoadTexBMP("a3.bmp");
   //  Pass control to GLUT so it can interact with the user
   ErrCheck("init");
   glutMainLoop();
   return 0;
}
