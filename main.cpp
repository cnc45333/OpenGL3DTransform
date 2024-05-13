#include <GL/gl.h>
#include <GL/glu.h>
#include <stdio.h>
#include <GL/glut.h>
#include <math.h>

#define WIDTH 800
#define HEIGHT 600

int toggleProjection = 0;
int shape = 1;

double translate = 0.5;
double scale = 0.25;

double camX = 4.0;
double camY = 5.0;
double camZ = 6.0;
double lookX = 0.0;
double lookY = 0.0;
double lookZ = 0.0;
double fov = 60.0;

double transX = 0.0;
double transY = 0.0;
double transZ = 0.0;
double scaleX = 1.0;
double scaleY = 1.0;
double scaleZ = 1.0;
double rotateX = 0.0;
double rotateY = 0.0;
double rotateZ = 0.0;

void drawAxis() {
  glBegin(GL_LINES);
  glColor3f(1.0, 1.0, 1.0);
  glVertex3f(0.0,0.0,0.0);
  glVertex3f(10.0, 0.0, 0.0);

  glColor3f(1.0, 1.0, 1.0);
  glVertex3f(0.0,0.0,0.0);
  glVertex3f(0.0, 10.0, 0.0);

  glColor3f(1.0, 1.0, 1.0);
  glVertex3f(0.0,0.0,0.0);
  glVertex3f(0.0, 0.0, 10.0);
  glEnd();
}


void drawFigure() {
  if (shape == 1) {

    //Back - Teal
    glBegin(GL_POLYGON);
    glColor3f(0.0,1.0,1.0);
    glVertex3f(-0.35,-0.35,-0.35);
    glVertex3f(-0.35,0.35,-0.35);
    glVertex3f(0.35,0.35,-0.35);
    glVertex3f(0.35,-0.35,-0.35);
    glEnd();

    //Front - White
    glBegin(GL_POLYGON);
    glColor3f(1.0, 1.0, 1.0);
    glVertex3f(0.35, -0.35, 0.35);
    glVertex3f(0.35, 0.35, 0.35);
    glVertex3f(-0.35, 0.35, 0.35);
    glVertex3f(-0.35, -0.35, 0.35);
    glEnd();

    //Right - Purple
    glBegin(GL_POLYGON);
    glColor3f(1.0, 0.0, 1.0);
    glVertex3f(0.35, -0.35, -0.35);
    glVertex3f(0.35, 0.35, -0.35);
    glVertex3f(0.35, 0.35, 0.35);
    glVertex3f(0.35, -0.35, 0.35);
    glEnd();

    //Left - Green
    glBegin(GL_POLYGON);
    glColor3f(0.0, 1.0, 0.0);
    glVertex3f(-0.35, -0.35, 0.35);
    glVertex3f(-0.35, 0.35, 0.35);
    glVertex3f(-0.35, 0.35, -0.35);
    glVertex3f(-0.35, -0.35, -0.35);
    glEnd();

    //Top - Blue
    glBegin(GL_POLYGON);
    glColor3f(0.0, 0.0, 1.0);
    glVertex3f(0.35, 0.35, 0.35);
    glVertex3f(0.35, 0.35, -0.35);
    glVertex3f(-0.35, 0.35, -0.35);
    glVertex3f(-0.35, 0.35, 0.35);
    glEnd();

    //Bottom - Red
    glBegin(GL_POLYGON);
    glColor3f(1.0, 0.0, 0.0);
    glVertex3f(0.35, -0.35, -0.35);
    glVertex3f(0.35, -0.35, 0.35);
    glVertex3f(-0.35, -0.35, 0.35);
    glVertex3f(-0.35, -0.35, -0.35);
    glEnd();
  }

  //Cylinder
  else {
    double convert = 3.1415926535/180;
    glBegin(GL_QUAD_STRIP);
    //cylinder side
    for ( int j = 0; j <= 360; j+=5) {
      glColor3f(1.0, 0.0, 1.0);
      glVertex3f(cos(convert*j), +1, sin(convert*j));
      glVertex3f(cos(convert*j), -1, sin(convert*j));
    } //for
    glEnd();

    //top and bottom
    for (int i = -1; i <= 1; i+=2) {
      glBegin(GL_TRIANGLE_FAN);
      glColor3f(1.0, 0.0, 0.5);
      glVertex3f(0,i,0);
      for (int k = 0; k <= 360; k+= 5){
	glVertex3f(i*cos(convert*k), i, sin(convert*k));
      }
      glEnd();
    }
  }   
} //drawFigure


void reset() {
  translate = 0.5;
  scale = 0.25;

 
  transX = 0.0;
  transY = 0.0;
  transZ = 0.0;
  scaleX = 1.0;
  scaleY = 1.0;
  scaleZ = 1.0;
  rotateX = 0.0;
  rotateY = 0.0;
  rotateZ = 0.0;
 
  glClearColor(0.0, 0.0, 0.0, 1.0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  
  if(toggleProjection == 0) {    //perspective
    gluPerspective(fov, 4.0/3.0, 1, 40);
  } else {         //orthographic
    glOrtho(-4.0, 4.0, -3.0, 3.0, 1.0, 40.0);
  }   
  
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt(camX,camY,camZ,lookX,lookY,lookZ,0,1,0);

  drawFigure();
  drawAxis();
  
  glutSwapBuffers();

}

void project() {
  glClearColor(0.0, 0.0, 0.0, 1.0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  
  if(toggleProjection == 0) {    //perspective
    gluPerspective(fov, 4.0/3.0, 1, 40);
  } else {         //orthographic
    glOrtho(-4.0, 4.0, -3.0, 3.0, 1.0, 40.0);
  }   
  
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt(camX,camY,camZ,lookX,lookY,lookZ,0,1,0);

  glPushMatrix();
  glTranslatef(transX, transY, transZ);
  glScalef(scaleX, scaleY, scaleZ);
  //drawFigure();

  
  glTranslatef(-transX, -transY, -transZ);
  glRotatef(rotateX, 1, 0, 0);
  glRotatef(rotateY, 0, 1, 0);
  glRotatef(rotateZ, 0, 0, 1);
  glTranslatef((transX), (transY), (transZ));
  //drawFigure();

 

 
 
  

 
  drawFigure();
  
  glPopMatrix();
  drawAxis();
  
  
  glutSwapBuffers();
  
} //project


void camReset() {
  camX = 4.0;
  camY = 5.0;
  camZ = 6.0;
  lookX = 0.0;
  lookY = 0.0;
  lookZ = 0.0;
  fov = 60.0;
  project();
}


void cameraMove(int direction) {
  double increase = 0.1;
  switch(direction) {
  case 1:
    camY += increase;
    lookY += increase;
    break;
  case 2:
    camY -= increase;
    lookY -= increase;
    break;
  case 3:
    camX -= increase;
    lookX -= increase;
    break;
  case 4:
    camX += increase;
    lookX += increase;
    break;
  case 5:
    camZ += increase;
    lookZ += increase;
    break;
  case 6:
    camZ -= increase;
    lookZ -= increase;
    break;   
  }
  project();
} //cameraMove

void keySpecial(int key, int x, int y) {
  if (key == GLUT_KEY_UP) {
    cameraMove(1);
  }else if (key == GLUT_KEY_DOWN) {
      cameraMove(2);
  }else if (key == GLUT_KEY_LEFT) {
    cameraMove(3);
  }else if (key == GLUT_KEY_RIGHT) {
    cameraMove(4);
  }else if (key == GLUT_KEY_F1) {
    camReset();
  }
} //keySpecial

void keyPressed(unsigned char key, int x, int y)
{
  if (key ==  '0') {
      exit(0); //exit program
  }else if (key == '1') {
    cameraMove(5);
  }else if (key == '2') {
    cameraMove(6);
  }else if (key == '3') {
    if (shape == 1) 
      shape = 2;
    else
      shape = 1;
    project();
  } else if (key == 27){
    reset();
  } else if (key == '+') {
    fov -= 5.0;
    project();
  }else if (key == '-') {
    fov += 5.0;
    project();
  }else if (key == 'w') {
     //translate up
    transY += translate;
  }else if (key == 's') {
    //translate down
    transY -= translate;
  }else if (key == 'a') {
    //translate left
    transX -= translate;
  }else if (key == 'd') {
    //translate right
    transX += translate;
  }else if (key == 'q') {
    //translate towards WCS
    transZ -= translate;
  }else if (key == 'e') {
    //translate away from WCS
    transZ += translate;
  }else if (key == 'x') {
     //rotate counterclockwise around x axis
    rotateX += 1;
  }else if (key == 'y') {
    //rotate counterclockwise around y axis
    rotateY += 1;
  }else if (key == 'z') {
      //rotate counterclockwise around z axis
    rotateZ += 1;
  }else if (key == 'u') {
      //scale up on x axis
    scaleX /= scale;
  }else if (key == 'j') {
      //scale down on x axis
    scaleX *= scale;
  }else if (key == 'i') {
      //scale up on y axis
    scaleY /= scale;
  }else if (key == 'k') {
      //scale down on y axis
    scaleY *= scale;
  }else if (key == 'o') {
      //scale up on z axis
    scaleZ /= scale;
  }else if (key == 'l') {
      //scale down on z axis
    scaleZ *= scale;
  }else if (key == 't') {
    //toggle between camera perspective and orthographic projection
    if (toggleProjection == 0) {
      toggleProjection = 1;
    } else {
      toggleProjection = 0;
    }
    project();
  }
}



void display(void)   // Create The Display Function
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	      // Clear Screen
  printf("\nChoose between the following menu options. \n");
  printf("\nEnter 0 :  to exit main program\n");
  printf("Press t :  to toggle between orthographic and perspective projections\n");
  printf("Press 3 :  to toggle between the cube and cylinder\n");
  printf("Press esc :  to eset the object\n");
  printf("Press F1 :   to reset the camera\n");
  printf("\nTranslate: \n");
  printf("Press w :  to translate UP \n");
  printf("Press s :  to translate DOWN \n");
  printf("Press a :  to translate LEFT\n");
  printf("Press d :  to translate RIGHT\n");
  printf("Press q :  to translate TOWARD the WCS\n");
  printf("Press e :  to translate AWAY from the WCS \n");
  printf("\nRotate: \n");
  printf("Press x :  to rotate around the X Axis \n");
  printf("Press y :  to rotate around the Y Axis\n");
  printf("Press z :  to rotate around the Z Azis \n");
  printf("\nScale: \n");
  printf("Press u :  to scale UP on the X Axis\n");
  printf("Press j :  to scale DOWN on the X Axis\n");
  printf("Press i :  to scale UP on the Y Axis\n");
  printf("Press j :  to scale DOWN on the Y Axis\n");
  printf("Press o :  to scale UP on the Z Axis\n");
  printf("Press l :  to scale DOWN on the Z Axis\n");
  printf("\nCamera:\n");
  printf("Press UP ARROW    :  to move camera UP\n");
  printf("Press DOWN ARROW  :  to move camera DOWN\n");
  printf("Press LEFT ARROW  :  to move camera LEFT\n");
  printf("Press RIGHT ARROW :  to move camera RIGHT\n");
  printf("Press 1           :  to move camera CLOSER to origin\n");
  printf("Press 2           :  to move camera AWAY from origin\n");
  printf("Press +           :  to DECREASE field of view\n");
  printf("Press -           :  to INCREASE field of view\n");                                     
}

void init() {
  display();
 
  glClearColor(0.0, 0.0, 0.0, 1.0);
  
  glEnable(GL_DEPTH_TEST);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  
  
    gluPerspective(fov, 4.0/3.0, 1, 40);
 
  
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt(camX,camY,camZ,lookX,lookY,lookZ,0,1,0);
   
  drawFigure();
  drawAxis();

  glutSwapBuffers();
}


int main (int argc, char** argv)
{
/* This main function sets up the main loop of the program and continues the
   loop until the end of the data is reached.  Then the window can be closed
   using the 0 key.						  */
	
	//while (currExample != 0)
	{
	  glutInit            ( &argc, argv ); 
	  glutInitDisplayMode ( GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH ); 
	  glutInitWindowSize  ( WIDTH,HEIGHT );
	  glutInitWindowPosition(100,100);
	  glutCreateWindow    ( "6050 Assignment 3" );
	  glEnable(GL_DEPTH_TEST);
	  glutDisplayFunc     (project);
	  glutIdleFunc	    (project);
	  glutKeyboardFunc    (keyPressed);
	  glutSpecialFunc     (keySpecial);
	  init();			       //create_window
		
	  glutMainLoop();                 // Initialize The Main Loop

		
	}

} //main

