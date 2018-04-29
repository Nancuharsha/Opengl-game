#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define BALL 1
#define STRIPES 2
#define PATCH 3
#define WALL1 4
#define WALL2 6
#define WALL3 7
#define BLOCK 5



GLfloat zb=0.0f,xb=1.5f,angb=0.0f,yb=0.0f; //ball coordinates and angle of rotation
GLfloat x2[2],y2=1.0f,z2[6]; //block coordinates
GLfloat blockspeed = 0.09f; //block speed / game level
int j=0, top=0,k=0; //jump flag  , ball top flag 
GLfloat xt;  // timer
int it;   
int gameon = 1;    //flag to show current game status 
GLfloat zm = 0.0f; // z-coordinate of stripes on road
GLfloat zw = 0.0f; // z-coordinate of side walls
GLfloat reft, reftime = 10; // timer variables
char score[5];       // score string
GLfloat angx=0,angy=0,angz=0;   // angles to rotate the camera
GLfloat ballspeed = 0.09f; 



void writetext(double x,double y,double z,double scale,char *s) //function to draw the text
{  int i;
   glPushMatrix();
   glTranslatef(x,y,z);
   glScalef(scale,scale,scale);
   for (i=0;i<strlen(s);i++)
     glutStrokeCharacter(GLUT_STROKE_ROMAN,s[i]);
   glPopMatrix();}


void ball()      //function to create the ball
{ glNewList(BALL, GL_COMPILE); 
  glPushMatrix();
  glColor3f(0.1f,0.9f,0.7f);
  glutWireSphere(0.6f,30,30);
  glPopMatrix();
  glEndList(); } //creating the ball list


void block()
{   glNewList(BLOCK, GL_COMPILE); //creating the list for blocks
    glPushMatrix();
    glColor3f(1.0f,0.398039f,0.0f);
    glScalef(1.2f,1.0f,0.6f);
    glutSolidCube(1.0f);        
    glColor3f(0.30f,0.30f,0.6f);
    glScalef(1.5f,1.5f,1.0f);
    glutSolidCube(0.9f); 
    glPopMatrix();
    glEndList();}


void stripe()
{   glNewList(STRIPES, GL_COMPILE); //creating the stripes list
    glPushMatrix();
    glScalef(0.07f,1.0f,0.2f);
    glTranslatef(0.0f,2.0f,15.0f);
    glColor3f(1.0f,1.0f,1.0f);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glBegin(GL_QUADS);
    glVertex3f(2.9f,-3.0f,-5.0f);
    glVertex3f(2.9f,-3.0f,-15.0f);
    glVertex3f(-2.9f,-3.0f,-15.0f);
    glVertex3f(-2.9f,-3.0f,-5.0f);
    glEnd();
    glPopMatrix();
    glEndList();} 

void stripeshow()
{ 

glPushMatrix();
glTranslatef(0.0f,0.0f,zm);  //function to show draw the stripes
glCallList(STRIPES);
glTranslatef(0.0f,0.0f,-3.0f);
glCallList(STRIPES);
glTranslatef(0.0f,0.0f,-3.0f);
glCallList(STRIPES);
glTranslatef(0.0f,0.0f,-3.0f);
glCallList(STRIPES);
glTranslatef(0.0f,0.0f,-3.0f);
glCallList(STRIPES);
glTranslatef(0.0f,0.0f,15.0f);
glCallList(STRIPES);

glPopMatrix();

}


void wall()
{
glNewList(WALL1,GL_COMPILE);
glPushMatrix();
glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
glBegin(GL_QUADS);
glColor3f(0.556863f,0.137255f ,0.137255f);     //function to create the walls
glVertex3f(6.0f,-3.0f,-24.0f);
glVertex3f(6.0f,-3.0f,-18.0f);
glVertex3f(6.0f,3.0f,-18.0f);
glVertex3f(6.0f,3.0f,-24.0f);
glEnd();
glPopMatrix();
glEndList();

glNewList(WALL3,GL_COMPILE);
glPushMatrix();
glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
glBegin(GL_QUADS);
glColor3f(0.184314f,0.309804f,0.309804f);
glVertex3f(6.0f,-3.0f,-24.0f);
glVertex3f(6.0f,-3.0f,-18.0f);
glVertex3f(6.0f,3.0f,-18.0f);
glVertex3f(6.0f,3.0f,-24.0f);
glEnd();
glPopMatrix();
glEndList();
}

void wallshow()
{
 
glPushMatrix();
glTranslatef(0.0f,0.0f,zw);
glTranslatef(0.0f,0.0f,-6.0f);    //function to draw the walls
glCallList(WALL1);
glTranslatef(0.0f,0.0f,6.0f);
glCallList(WALL3);
glTranslatef(0.0f,0.0f,6.0f);
glCallList(WALL1);
glTranslatef(0.0f,0.0f,6.0f);
glCallList(WALL3);
glTranslatef(0.0f,0.0f,6.0f);
glCallList(WALL1);
glTranslatef(0.0f,0.0f,6.0f);
glCallList(WALL3);
glTranslatef(0.0f,0.0f,6.0f);
glCallList(WALL1);


glTranslatef(-12.0f,0.0f,-36.0f);
glCallList(WALL1);
glTranslatef(0.0f,0.0f,6.0f);
glCallList(WALL3);
glTranslatef(0.0f,0.0f,6.0f);
glCallList(WALL1);
glTranslatef(0.0f,0.0f,6.0f);
glCallList(WALL3);
glTranslatef(0.0f,0.0f,6.0f);
glCallList(WALL1);
glTranslatef(0.0f,0.0f,6.0f);
glCallList(WALL3);
glTranslatef(0.0f,0.0f,6.0f);
glCallList(WALL1);

glPopMatrix();
}

void wallanim(){
  if(zw<6.0f)
  zw = zw + blockspeed;    //function to animate walls
else
  zw = 0.0f;

}

void ballanim()     //function to animate the ball
{
glPushMatrix();
glColor3f(0.0f,0.0f,1.0f);
glTranslatef(xb,-2.0f+yb,1.5f+zb);
if(zb >= -3.2f)
zb = zb -ballspeed;
angb = angb + 1.2f;
glRotatef(-15.0f-angb,1.0f,0.0f,0.0f);
glCallList(BALL);
glPopMatrix();
}

void blockanim()         //function to animate the block
{
  glPushMatrix();

  glTranslatef(x2[0],-3.0f+y2,z2[0]);
    glCallList(BLOCK);
    glPopMatrix();
     
    glPushMatrix(); 

    glTranslatef(x2[1],-3.0f+y2,z2[1]);
    glCallList(BLOCK);
    glPopMatrix();
    
    glPushMatrix();

    glTranslatef(x2[2],-3.0f+y2,z2[2]);
    glCallList(BLOCK);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(0.0f,0.0f,30.0f);
    glTranslatef(x2[3],-3.0f+y2,z2[3]);
    glCallList(BLOCK);
    glPopMatrix();
}



int hit(GLfloat z,int i)        //function to check whether the hit condition is met
{ if(x2[i] == xb && (yb>=-0.1f && yb <= 0.6f) &&( z <= -1.75f && z >= -2.00f))
   return 1;
   else 
    return 0;
}


void blockmove()         //function to animate the blocks
{ 

  int i;


for(i=0 ; i<4 ; i++)
{
  if(z2[i] <= 1.5f)
    {if(hit(z2[i],i) )
              {gameon = 0;}
            z2[i] = z2[i] + blockspeed;
    }
  else
    z2[i] = rand()%10 - 20;
}


  
}


void jump()
{  
if( j == 1){
if(top == 0){         //function to make the ball jump

    if(yb<2.0f)
       yb = yb+0.10f;
    else
      top = 1;}

else if(top == 1)
   {
     if(yb>0.0f)
     yb=yb-0.10f;
     else{
        top = 0;
         j = 0;}
   }
}
}



void stripemove()
{                                    //funtion to animate the stripes
  if(zm < 3.0f)
    zm = zm + blockspeed;

  else
    zm = 0.0f;
}


void animate()
{                                       //animate function to call all other animating functions
  if(gameon){
  blockmove();
  stripemove();
  wallanim();
  

  if(j)
  {jump();}
  
sprintf(score,"%f",reft);
   }
glutPostRedisplay();
  blockspeed = blockspeed + 0.00005f;
  
    
}


void keyboard(unsigned char key, int x, int y)    //accessing keyboard input
{ 
  switch(key)
  {
    case 'w':
    j = 1;
    break;
    case 'd':
        xb = 1.5f;
        break;
        case 'a' :
        xb = -1.5f;
        break;
        case 'r':
        {   angx = 0;
            angy = 0;
             angz = 0;}
         break;
         case '1' :
          angx = angx+5;
          break;
         case '2' :
          angx = angx-5;
          break; 
        case '3' :
          angy = angy+5;
          break;
          case '4' :
          angy = angy-5;
          break;
          case '5' :
          angz = angz+5;
          break;
          case '6' :
          angz = angz+5;
          break;


        };


}
void myMouseFunc(int button, int state, int x, int y)      // accessing mouse controls
{
  if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
   blockspeed=blockspeed + 0.09f;
 }
}

 
void display()       //display function
{
glClearColor(0.0, 0.0, 0.0, 0.0);
glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
glEnable(GL_DEPTH_TEST);

glPushMatrix();
glRotatef(15.0f+angx,1.0f,0.0f,0.0f);
glRotatef(angy,0.0f,1.0f,0.0f);
glRotatef(angz,0.0f,0.0f,1.0f);

glBegin(GL_QUADS);
 glColor3f(0.2f,0.2f,0.2f);
glVertex3f(3.5f,-3.0f,-35.0f);
glVertex3f(-3.5f,-3.0f,-35.0f);
glVertex3f(-3.5f,-3.0f,5.0f);
glVertex3f(3.5f,-3.0f,5.0f);
glEnd();
glBegin(GL_QUADS);
 glColor3f(0.0f,0.8f,0.2f);
glVertex3f(-3.5f,-3.0f,-35.0f);
glVertex3f(-6.0f,-3.0f,-35.0f);
glVertex3f(-6.0f,-3.0f,5.0f);
glVertex3f(-3.5f,-3.0f,5.0f);
glEnd();
glBegin(GL_QUADS);
 glColor3f(0.0f,0.8f,0.2f);
glVertex3f(3.5f,-3.0f,-35.0f);
glVertex3f(6.0f,-3.0f,-35.0f);
glVertex3f(6.0f,-3.0f,5.0f);
glVertex3f(3.5f,-3.0f,5.0f);
glEnd();
//sky blue
glBegin(GL_QUADS);
 glColor3f(0.196078f,0.6f,0.8f);
glVertex3f(-100.0f,-3.0f,-24.0f);
glVertex3f(100.0f,-3.0f,-24.0f);
glVertex3f(100.0f,15.0f,-24.0f);
glVertex3f(-100.0f,15.0f,-24.0f);
glEnd();


ballanim();
glColor3f(1.0f,1.0f,1.0f);
stripeshow();
blockanim();
wallshow();


glPushMatrix();

glColor3f(1.0f,1.0f,1.0f);
 glPolygonMode(GL_FRONT_AND_BACK,GL_LINES);
 glBegin(GL_QUADS);
 glColor3f(0.35f,0.35f, 0.67f);
 glVertex3f(xb+0.5f,zb, yb+0.5f );
 glVertex3f(xb+0.5f,zb, yb+0.5f );
  glVertex3f(xb+1.0f,zb, yb+0.25f );
 glVertex3f(xb+1.0f,zb, yb+0.5f );
glEnd();

glColor3f(1.0f,1.0f,1.0f);
writetext(xb+1.0f,yb+1.1f,zb,0.0015,"your score");
glColor3f(0.439216f, 0.858824f,0.576471f);
writetext(xb+1.0f,yb+0.4f,zb,0.0055,score);

glPopMatrix();

glPopMatrix();



glFlush();
glutSwapBuffers();
}



void timer(int value) {
   
   glutTimerFunc(reftime, timer, 0); // next timer call milliseconds later
   reft = reft+reftime;
}

void myinit(void)
{
    glEnable(GL_DEPTH_TEST);
    glRotatef(10.0f,1.0f,0.0f,0.0f);        //initialise all lists
    ball();
    wall();
   
    block();
    stripe();

  
    z2[0] = -15.0f;
z2[1] = -15.0f;
z2[2] = -15.0f;
z2[3] = -15.0f;
x2[1] = -1.5f;
x2[0] = 1.5f;
x2[3] = -1.5f;
x2[2] = 1.5f;
}


void myReshape(int w, int h)                  //reshape function
{
  glViewport(0, 0, w, h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(70.0, (GLfloat) w / (GLfloat) h, 1.0, 30.0);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glTranslatef(0.0, 0.0, -5.5);
}

int main(int argc,char** argv)
{
glutInit(&argc,argv);
glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
glutInitWindowSize(1000, 600);
glutCreateWindow("my game");
myinit();
glutDisplayFunc(display);
glutReshapeFunc(myReshape);
glutIdleFunc(animate);

glutKeyboardFunc(keyboard);
glutMouseFunc(myMouseFunc);
//glutSpecialFunc(special);
glutTimerFunc(0, timer, 0);

glutMainLoop();

return 0;
}
