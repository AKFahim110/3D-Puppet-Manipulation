/**********************************************************************
    Project Name: 3D Puppet Manipulation
    Student ID:2021521460110
    Student Name: Adult Khan Fahim
**********************************************************************//* -------- start various header files needed ---------- */
#include<windows.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>
#include <GL/glut.h>
#include <GL/glu.h>
#include "bitmap.h"
#include <vector>


/* ---------- end of header files ----------- */

/* ----- start of glNewlist serial number (display list) definitions ----- */
#define TORSO        1
#define HIP          2
#define SHOULDER     3
#define UPPER_ARM    4
#define FOREARM	     5
#define UPPER_LEG    6
#define LOWER_LEG    7
#define FOOT         8
#define HEAD		 9	
#define ENVIRONMENT		10
/* ----- end of glNewlist serial number (display list) definitions ----- */

/* ----- start of motion rate definitions ----- */
#define TORSO_ROTATE_RATE	10		/* motion rate for variable "pivot" */
#define TORSO_TILT_RATE	1			/* motion rate for variable "tilt" */

#define UPPER_LEG_RATE	3			/* motion rate for variable "left_hip" and "right_hip" */
#define LOW_LEG_RATE	3			/* motion rate for variable "left_knee" and "right_knee" */
#define ANKLE_RATE	3				/* motion rate for variable "left_ankle" and "right_ankle" */

#define SHOULDER_RATE	5			/* motion rate for variable "left_shoulder" and "right_shoulder" */
#define ELBOW_RATE	3				/* motion rate for variable "left_elbow" and "right_elbow" */

#define LIGHT_TURN_RATE	10			/* motion rate for variable "lightturn" and "lightturn1" */
#define VIEW_TURN_RATE	10			/* motion rate for variable "turn" and "turn1"*/
/* ----- end of motion rate definitions ----- */

#define M_PI 3.141592654

GLubyte* teximage1, * teximage2, * teximage3;
int w1, w2, w3, h1, h2, h3;
GLUquadricObj* sphere1, * sphere2;

/* ----- start of definitions on motion variables ----- */
/* definitions on rotation angles for different joints */
int right_shoulder = 0, left_shoulder = 0;		/* rotate forward and backward at the left and right shoulder joints */
int right_elbow = 0, left_elbow = 0;			/* rotate at both elbow joints */
int pivot = 0;			                        /* rotate around pivot at waist joint */
int tilt = 2;									/* rotate forward and backward at waist joint */
int right_ankle = 0, left_ankle = 0;			/* rotate at the left and right ankle joints */
int right_knee = 0, left_knee = 0;				/* rotate at the left and rght knee joints */
int right_hip = 0, left_hip = 0;				/* rotate forward and backward at the left and right coxa joints */

/* definitions on rotation angles for view and lights */
int turn = 0, turn1 = 0;						/* turn view to left and right, forward and backward */
int lightturn = 0, lightturn1 = 0;				/* turn light to left and right, forward and backward */

float elevation = 0.0, distance = 0.0, frame = 1.0;  /* variable use for animation */

int step_status;
enum STEP_STATUS {
    NO_STATUS,
    LEFT_UPPER_LEG, LEFT_LOWER_LEG, LEFT_LEG_DOING_UPPER, LEFT_LEG_DOING_LOWER,
    RIGHT_UPPER_LEG, RIGHT_LOWER_LEG, RIGHT_LEG_DOING_UPPER, RIGHT_LEG_DOING_LOWER,
};
/* ----- end of motion variables ----- */

/* ----- start of material definitions ----- */
// Updated material properties for torso
GLfloat mat_specular1[] = { 0.0, 0.0, 1.0, 1.0 };
GLfloat mat_ambient1[] = { 0.0, 0.0, 0.4, 1.0 };
GLfloat mat_diffuse1[] = { 0.0, 0.0, 0.6, 1.0 };
GLfloat mat_shininess1[] = { 128.0 * 0.4 };

// Updated material properties for fore arm
GLfloat mat_specular2[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat mat_ambient2[] = { 0.8, 0.8, 0.8, 1.0 };
GLfloat mat_diffuse2[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat mat_shininess2[] = { 128.0 * 0.6 };

GLfloat mat_specular3[] = { 0.296648, 0.296648, 0.296648 };
GLfloat mat_ambient3[] = { 0.25, 0.20725, 0.20725 };
GLfloat mat_diffuse3[] = { 1, 0.829, 0.829 };
GLfloat mat_shininess3[] = { 128.0 * 0.088 };

GLfloat mat_specular4[] = { 0.633, 0.727811, 0.633 };
GLfloat mat_ambient4[] = { 0.0215, 0.1745, 0.0215 };
GLfloat mat_diffuse4[] = { 0.07568, 0.61424, 0.07568 };
GLfloat mat_shininess4[] = { 128 * 0.6 };
// Updated material properties for head
GLfloat mat_specular5[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat mat_ambient5[] = { 0.8, 0.8, 0.8, 1.0 };
GLfloat mat_diffuse5[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat mat_shininess5[] = { 128.0 * 0.25 };

GLfloat mat_specular6[] = { 0.628281, 0.555802, 0.366065, 1.0 };
GLfloat mat_ambient6[] = { 0.24725, 0.1995, 0.0745, 1.0 };
GLfloat mat_diffuse6[] = { 0.75164, 0.60648, 0.22648, 1.0 };
GLfloat mat_shininess6[] = { 128.0 * 0.4 };

GLfloat mat_specular7[] = { 0.60, 0.60, 0.50 };
GLfloat mat_ambient7[] = { 0.0, 0.9, 0.0 };
GLfloat mat_diffuse7[] = { 0.0, 0.9, 0.0 };
GLfloat mat_shininess7[] = { 128.0 * 0.25 };

GLfloat mat_specular8[] = { 0.508273, 0.508273, 0.508373 };
GLfloat mat_ambient8[] = { 0.0, 0.0, 0.9 };
GLfloat mat_diffuse8[] = { 0.0, 0.0, 0.9 };
GLfloat mat_shininess8[] = { 128.0 * 0.6 };

unsigned int texture;
unsigned int texture_moon;
unsigned int texture_saturn;
unsigned int texture_earth;
/* end of material definitions */

void RotWithPoint(GLfloat angle, GLfloat x, GLfloat y, GLfloat z,
    GLfloat direction_x, GLfloat direction_y, GLfloat direction_z)
{
    glTranslatef(-x, -y, -z);
    glRotatef(angle, direction_x, direction_y, direction_z);
    glTranslatef(x, y, z);
}

/* ----- start of function to define materials properties ----- */
void SetMaterial(GLfloat spec[], GLfloat amb[], GLfloat diff[], GLfloat shin[])
{

    glMaterialfv(GL_FRONT, GL_SPECULAR, spec);
    glMaterialfv(GL_FRONT, GL_SHININESS, shin);
    glMaterialfv(GL_FRONT, GL_AMBIENT, amb);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, diff);
}
/* ----- end of function to define materials properties ----- */


/* -------------------- start of drawing head --------------------- */


void DrawHead(void)
{
    glNewList(HEAD, GL_COMPILE);

    glPushMatrix();

    // Translate the head to the appropriate position
    glTranslatef(0.0, 1.1, 0.0);
    glScalef(1.5, 1.0, 1.0);

    // Enable texture mapping for the main head
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture_moon);  // Assuming 'texture_saturn' is the Saturn texture ID

    // Use quadrics for drawing the head
    GLUquadricObj* sphere = gluNewQuadric();
    gluQuadricTexture(sphere, GL_TRUE);

    // Draw the main head
    gluSphere(sphere, 0.5, 40, 40);

    // Draw the first smaller sphere on top of the head
    glPushMatrix();
    glTranslatef(0.2, 0.15, 0.48); // Adjust the position relative to the main head
    glScalef(1.0, 2.0, 0.2);
    glColor3f(0.0, 0.0, 0.0);
    glutSolidSphere(0.08, 8, 8);  // Adjust the size as needed
    glPopMatrix();

    // Draw the second smaller sphere on top of the head with a small gap
    glPushMatrix();
    glTranslatef(-0.2, 0.15, 0.48); // Adjust the position relative to the main head on the opposite side
    glScalef(1.0, 2.0, 0.2);
    glColor3f(0.0, 0.0, 0.0);
    glutSolidSphere(0.08, 8, 8);  // Adjust the size as needed
    glPopMatrix();

    // Disable texture mapping for the main head
    glDisable(GL_TEXTURE_2D);

    glPopMatrix();

    glEndList();
}

/* -------------------- end of drawing head --------------------- */

/* -------------- start of drawing torso ---------------- */
void DrawTorso() {
    glNewList(TORSO, GL_COMPILE);

    // Design torso of your puppet here
    SetMaterial(mat_specular1, mat_ambient1, mat_diffuse1, mat_shininess1);

    glPushMatrix();
    glScalef(2.3, 2.25, 1.5);

    // Enable texture mapping
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture);  // Assuming 'texture' is the Earth texture ID

    // Use quadrics for drawing the torso
    GLUquadricObj* torso = gluNewQuadric();
    gluQuadricTexture(torso, GL_TRUE);

    glutSolidSphere(.5, 100, 100); // Use glutSolidSphere to create an ellipsoid as torso

    // Disable texture mapping after drawing
    glDisable(GL_TEXTURE_2D);

    glPopMatrix();
    glEndList();
}


/* -------------- end of drawing torso ---------------- */

/* -------------------- start of drawing shoulder --------------------- */
void DrawShoulder(void)
{
    glNewList(SHOULDER, GL_COMPILE);

    /* design shoulder of your puppet here */
    SetMaterial(mat_specular2, mat_ambient2, mat_diffuse2, mat_shininess2);
    glPushMatrix();
    glScalef(7.0, 3, 1.0); // Adjust scaling to elongate along the x-axis
    glutSolidSphere(0.25, 100, 100); // Use glutSolidSphere to create an ellipsoid
    glPopMatrix();

    glEndList();
}

/* -------------------- end of drawing shoulder --------------------- */

/* -------------------- start of drawing hip --------------------- */
void DrawHip(void)
{
    glNewList(HIP, GL_COMPILE);

    /* design hip of your puppet here */
    SetMaterial(mat_specular2, mat_ambient2, mat_diffuse2, mat_shininess2);
    glPushMatrix();
    glScaled(3.0, 3, 0.8); // Adjust scaling to make it more proportional
    glutSolidSphere(0.25, 100, 100); // Use glutSolidSphere to create a rugby ball-like shape
    glPopMatrix();

    glEndList();
}

/* -------------------- end of drawing hip --------------------- */

/* -------------------- start of drawing upper arm --------------------- */
void DrawUpperArm(void)
{
    glNewList(UPPER_ARM, GL_COMPILE);

    /* design upper arm of your puppet here */
    SetMaterial(mat_specular1, mat_ambient1, mat_diffuse1, mat_shininess1);

    glPushMatrix();
    glScalef(1.0, 3.5, 1.0); // Adjust scaling to make it longer
    glutSolidSphere(0.3, 100, 100); // Use glutSolidSphere to create an ellipsoid
    glPopMatrix();

    glEndList();
}

/* -------------------- end of drawing upper arm --------------------- */


/* -------------------- start of drawing forearm --------------------- */
void DrawForeArm(void)
{
    glNewList(FOREARM, GL_COMPILE);

    /* design forearm of your puppet here */
    SetMaterial(mat_specular2, mat_ambient2, mat_diffuse2, mat_shininess2);

    // Draw elliptical forearm with increased size
    glPushMatrix();
    glScalef(1, 3.5, 1); // Adjust scaling to make it larger and thicker
    glutSolidSphere(0.25, 20, 20); // Adjust the size of the sphere to make it elliptical
    glPopMatrix();

    glEndList();
}


/* -------------------- end of drawing forearm --------------------- */


/* -------------------- start of drawing upper leg --------------------- */
void DrawUpperLeg(void)
{
    glNewList(UPPER_LEG, GL_COMPILE);

    /* design upper leg of your puppet here */

    glPushMatrix();

    glScalef(1.0, 2.5, 1.0); // Adjust scaling to make it thicker and elliptical
    RotWithPoint(left_hip, 0, 0.15, 0, 1, 0, 0);

    // Enable texture mapping
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture);  // Assuming 'texture' is the Earth texture ID

    // Use quadrics for drawing the upper leg
    GLUquadricObj* sphere = gluNewQuadric();
    gluQuadricTexture(sphere, GL_TRUE);

    // Draw the upper leg as a sphere
    gluSphere(sphere, 0.4, 20, 20);

    // Disable texture mapping after drawing
    glDisable(GL_TEXTURE_2D);

    glPopMatrix();

    glEndList();
}

/* -------------------- end of drawing upper leg --------------------- */
/* -------------------- start of drawing lower leg --------------------- */
void DrawLowerLeg(void)
{
    glNewList(LOWER_LEG, GL_COMPILE);

    /* design lower leg of your puppet here */
    SetMaterial(mat_specular2, mat_ambient2, mat_diffuse2, mat_shininess2);

    glPushMatrix();
    glTranslatef(0.0, -0.25, 0.0); // Adjust the position to connect lower leg with foot
    glScalef(1.0, 3.0, 1.0); // Adjust scaling to make it larger and elliptical
    glutSolidSphere(0.25, 20, 20); // Adjust the size of the sphere to make it elliptical
    glPopMatrix();

    glEndList();
}

/* -------------------- end of drawing lower leg -----------------------*/


/* -------------------- start of drawing foot --------------------- */
void DrawFoot(void)
{
    glNewList(FOOT, GL_COMPILE);

    /* design foot of your puppet here */
    SetMaterial(mat_specular1, mat_ambient1, mat_diffuse1, mat_shininess1);

    glPushMatrix();
    glScalef(1.0, 0.5, 1.75); // Adjust scaling to make it smaller and elliptical
    glutSolidSphere(0.25, 20, 20); // Adjust the size of the sphere to make it elliptical
    glPopMatrix();

    glEndList();
}
/* -------------------- end of drawing foot --------------------- */

/* -------------------- start of drawing environment --------------------- */
void DrawEnvironment(void)
{
    int i, j;

    glNewList(ENVIRONMENT, GL_COMPILE);

    SetMaterial(mat_specular7, mat_ambient7, mat_diffuse7, mat_shininess7);

    glPushMatrix();

    /* -------------- start of adding texture to the floor --------------- */

    glEnable(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, texture_saturn);  // Use 'texture_saturn' instead of 'texture'

    // Set floor color to fully transparent
    glColor4f(1.0, 1.0, 1.0, 0.0);

    // Specify texture coordinates for the floor
    glBegin(GL_QUADS);
    glTexCoord2f(0.0, 0.0);
    glVertex3f(-10.0, 0.0, -15.0);

    glTexCoord2f(10.0, 0.0);
    glVertex3f(10.0, 0.0, -15.0);

    glTexCoord2f(10.0, 10.0);
    glVertex3f(10.0, 0.0, 15.0);

    glTexCoord2f(0.0, 10.0);
    glVertex3f(-10.0, 0.0, 15.0);
    glEnd();

    //glDisable(GL_TEXTURE_2D);

    /* --------------- end of adding texture to the floor --------------- */


    glPopMatrix();
    SetMaterial(mat_specular6, mat_ambient8, mat_diffuse3, mat_shininess4);
    glColor3f(0.6, 0.6, 0.6);
    glTranslatef(0.0, 0.0, -10.0);
    for (j = 0; j < 6; j++) {
        for (i = 0; i < 2; i++) {
            if (i)
                glScalef(-1.0, 1.0, 1.0);
            glTranslatef(10.0, 4.0, 0.0);
            glPushMatrix();
            glScalef(4.0, 8.0, 2.0);
            glutSolidSphere(0.7, 100, 100);
            glPopMatrix();
            glTranslatef(0.0, -1.0, -3.0);
            glPushMatrix();
            glScalef(4.0, 5.0, 2.0);
            glutSolidSphere(0.6, 100, 100);
            glPopMatrix();
            glTranslatef(-10.0, -3.0, 3.0);
        }
        glScalef(-1.0, 1.0, 1.0);
        glTranslatef(0.0, 0.0, 5.0);
    }

    glEndList();
}
/* -------------------- end of drawing environment --------------------- */


void disable(void)
{
    glDisable(GL_LIGHTING);
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_NORMALIZE);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}


/*-----------------LIGHTS STUFF------------------*/
void lighting(void)
{
    /* light position */
    /* you may need to midify 2.0 to larger value according to size of your model */
    GLfloat position[] = { 0.0, 0.0, 2.0, 1.0 };

    /* you need to draw a wire cube or sphere to simulate position of lighting */
    /* use spot lighting  and rotate light*/

    /* write your code here */
    GLfloat ambient[] = { 0.5, 0.5, 0.5, 1 };
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambient);

    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 0.0 };
    GLfloat mat_shininess[] = { 50.0 };
    GLfloat light_pos[] = { 0, 1, 1.5, 1.0 };
    glColor3f(1.0, 1.0, 1.0);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
    glPushMatrix();
    /*
    Rotate the lighting with a fixed point.
    Translate -> Rotate -> Translate back
    */
    glTranslatef(0, -2, 0);
    glRotatef(lightturn, 0, 1, 0);
    glRotated(lightturn1, 1, 0, 0);
    glTranslatef(0, 2, 0);

    glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
    glDisable(GL_LIGHTING);
    glPopMatrix();
    glColor3f(1, 0, 0);
    /*
    Rotate the lighting with a fixed point.
    Translate -> Rotate -> Translate back
    */
    glTranslatef(0, -2, 0);
    glRotatef(lightturn, 0, 1, 0);
    glRotated(lightturn1, 1, 0, 0);
    glTranslatef(0, 2, 0);

    glTranslatef(light_pos[0], light_pos[1], light_pos[2]);
    glutWireCube(0.05);
    glEnable(GL_LIGHTING);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

}



/* ----------- start of integration of whole puppet ---------	----- */
void DrawPuppet(void)
{

    /* construct the puppet part by part here
    Note: use PushMatrix and PopMatrix to construct the hierarchical relationship
    between defferent parts.
    Note the relationship betweem parts:
    shoulder and hip are torso's children, upper arm is shoulder's child, and forearm is upper arm's child;
    upper leg is hip's child, and lower leg is upper leg's child;
    So if we move torso for example, arms and forarms move too.
    */
    /* Write your code below  */
    glPushMatrix();

    glTranslatef(0, -2.5, 0);
    glTranslatef(0, -.7, 0);
    glTranslatef(0, 6.5, 0);
    glRotatef(tilt, -1, 0, 0);
    glRotatef(pivot, 0, 1, 0);
    glCallList(TORSO);



    glPushMatrix();
    //glTranslatef(0, 0.7, 0);
    glTranslatef(0, 0.6, 0);
    glCallList(SHOULDER);
    glPushMatrix();

    glTranslatef(0, -0.15, 0);
    glRotatef(right_shoulder, 1, 0, 0);
    glTranslatef(-0.9, -0.05, 0);
    glTranslatef(-0.8, -0.5, 0);
    glCallList(UPPER_ARM);
    RotWithPoint(right_elbow, 0, 0.2, 0, 1, 0, 0);
    glTranslatef(0, -1.5, 0);
    glCallList(FOREARM);

    glPopMatrix();

    glPushMatrix();

    RotWithPoint(left_shoulder, 0, 0.2, 0, 1, 0, 0);
    glTranslatef(0, -0.15, 0);
    glRotatef(left_shoulder, 1, 0, 0);
    glTranslatef(0.9, -0.4, 0);
    glTranslatef(0.8, -.2, 0);
    glCallList(UPPER_ARM);
    RotWithPoint(left_elbow, 0, 0.2, 0, 1, 0, 0);
    glTranslatef(0, -1.5, 0);
    glCallList(FOREARM);


    glPopMatrix();

    glTranslatef(0, 0, 0);
    glCallList(HEAD);
    glPopMatrix();

    glPushMatrix();

    glTranslatef(0, -0.7, 0);
    glRotatef(pivot, 0, -1, 0);
    glRotatef(tilt, 1, 0, 0);
    glTranslatef(0, 0.7, 0);
    glTranslatef(0, -1.05, 0);
    glCallList(HIP);


    glPushMatrix();

    RotWithPoint(right_hip, 0, 0.15, 0, 1, 0, 0);
    glTranslatef(-0.8, -1, 0);
    glCallList(UPPER_LEG);
    RotWithPoint(right_knee, 0, 0.2, 0, 1, 0, 0);
    glTranslatef(0, -1.2, 0);
    glCallList(LOWER_LEG);
    RotWithPoint(right_ankle, 0, 0.2, 0, 1, 0, 0);
    glTranslatef(0, -.9, 0.25);
    glCallList(FOOT);
    glPopMatrix();


    glPushMatrix();
    RotWithPoint(left_hip, 0, 0.15, 0, 1, 0, 0);
    glTranslatef(0.8, -1, 0);
    glCallList(UPPER_LEG);
    RotWithPoint(left_knee, 0, 0.2, 0, 1, 0, 0);
    glTranslatef(0, -1.2, 0);
    glCallList(LOWER_LEG);
    RotWithPoint(left_ankle, 0, 0.2, 0, 1, 0, 0);
    glTranslatef(0, -.9, 0.25);
    glCallList(FOOT);
    glPopMatrix();

    glPopMatrix();
    glPopMatrix();

}
/* ----------- end of integration of whole puppet -------------- */


/* ------------- start of display function --------------- */
void display(void)
{
    /* Clear Screen And Depth Buffer  */
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);

    glPushMatrix();
    /* camera stuff */
    glRotatef((GLfloat)turn, 0.0, 1.0, 0.0);
    glRotatef((GLfloat)turn1, 1.0, 0.0, 0.0);

    /* light stuff */
    glPushMatrix();
    lighting();
    glPopMatrix();

    /* draw puppet */
    glPushMatrix();
    glTranslatef(0.0, elevation, 0.0);
    DrawPuppet();
    glPopMatrix();

    /* draw environment */
    glPushMatrix();
    if (distance >= 20.136)
        distance = 0.0;
    glTranslatef(0.0, -5.0, -distance);
    glCallList(ENVIRONMENT);
    glTranslatef(0.0, 0.0, 10.0);
    glCallList(ENVIRONMENT);
    glPopMatrix();

    glPopMatrix();
    glFlush();
    glutSwapBuffers();
}
/* ------------- end of display function --------------- */

GLubyte* TextureLoadBitmap(char* filename, int* w, int* h) /* I - Bitmap file to load */
{
    BITMAPINFO* info;       /* Bitmap information */
    void* bits;             /* Bitmap pixel bits */
    GLubyte* rgb;           /* Bitmap RGB pixels */

    /*
    * Try loading the bitmap and converting it to RGB...
    */

    bits = LoadDIBitmap(filename, &info);  // Assuming LoadDIBitmap is a function to load a DIB bitmap
    if (bits == nullptr) {
        // Handle error here, perhaps return nullptr or perform other error-handling tasks
        return nullptr;
    }
    rgb = ConvertRGB(info, bits);          // Assuming ConvertRGB is a function to convert to RGB format
    if (rgb == nullptr)
    {
        free(info);
        free(bits);
        // Handle error here, perhaps return nullptr or perform other error-handling tasks
    }

    *w = info->bmiHeader.biWidth;   // Set the width of the image
    *h = info->bmiHeader.biHeight;  // Set the height of the image

    /*
    * Free the bitmap and RGB images, then return the RGB data.
    */

    free(info);
    free(bits);
    return rgb;
}

void LoadGLTextures()
{
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    // Set texture parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    // Load texture image via TextureLoadBitmap function
    char f_name[1][20] = { "earth.bmp" };
    int w1, h1;
    GLubyte* teximage1 = TextureLoadBitmap(f_name[0], &w1, &h1);

    // Specify texture image
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w1, h1, 0, GL_RGB, GL_UNSIGNED_BYTE, teximage1);

    // Free texture image memory
    free(teximage1);

    glGenTextures(1, &texture_moon);
    glBindTexture(GL_TEXTURE_2D, texture_moon);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    // Load texture image via TextureLoadBitmap function
    char f_name_moon[1][20] = { "moon.bmp" };
    int w2, h2;
    GLubyte* teximage2 = TextureLoadBitmap(f_name_moon[0], &w2, &h2);

    // Specify texture image for Moon
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w2, h2, 0, GL_RGB, GL_UNSIGNED_BYTE, teximage2);

    // Free texture image memory for Moon
    free(teximage2);

    glGenTextures(1, &texture_saturn);
    glBindTexture(GL_TEXTURE_2D, texture_saturn);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    // Load texture image via TextureLoadBitmap function
    char f_name_saturn[1][20] = { "saturn.bmp" };
    int w3, h3;
    GLubyte* teximage3 = TextureLoadBitmap(f_name_saturn[0], &w3, &h3);

    // Specify texture image for saturn
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w3, h3, 0, GL_RGB, GL_UNSIGNED_BYTE, teximage3);

    // Free texture image memory for saturn
    free(teximage3);


}


/* ----------- start of initial function ----------- */
void myinit(void)
{
    /* Clear Screen color and Enable Hidden Surface Removal */
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_NORMALIZE);
    /* other environment setting */
    glShadeModel(GL_SMOOTH);

    // load texture
    LoadGLTextures();

    /* initial puppet structures */
    DrawTorso();
    DrawHip();
    DrawShoulder();
    DrawHead();
    DrawUpperArm();
    DrawForeArm();
    DrawUpperLeg();
    DrawLowerLeg();
    DrawFoot();

    DrawEnvironment();
}
/* ----------- end of initial function ----------- */


/* ------------- start of reshape function --------------- */
void myReshape(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    /* you may need to midify the parameters in next sentence according to size of your model */
    gluPerspective(90.0, (GLfloat)w / (GLfloat)h, 1.0, 20.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    /* you may need to midify following parameters according to coordinates of your model */
    glTranslatef(0.0, -2.0, -5.5);  /* viewing transform  */
}
// Define variables for jump animation
static bool is_jumping = false;
static float jump_height = 0.0;
static float jump_speed = 0.02;

// Store the original positions of the legs
static float original_left_leg_y = 0.0;
static float original_right_leg_y = 0.0;
float left_leg_y = 0.0;
float right_leg_y = 0.0;

void animation_jump(void)
{
    if (!is_jumping) {
        // Start the jump
        is_jumping = true;

        // Store the original positions of the legs
        original_left_leg_y = left_leg_y;
        original_right_leg_y = right_leg_y;
    }

    // Simulate jumping motion
    if (is_jumping && jump_height < 1.0) {
        // During the jump
        jump_height += jump_speed;

        // Update relevant body parts for the jump
        left_leg_y += jump_speed * 2.0; // Adjust the factor to control the leg movement
        right_leg_y += jump_speed * 2.0;

        // You may need to adjust other body parts as well based on your puppet structure

        glutPostRedisplay();
    }
    else {
        // End of the jump
        is_jumping = false;
        jump_height = 0.0;

        // Reset body parts to their original positions after the jump
        left_leg_y = original_left_leg_y;
        right_leg_y = original_right_leg_y;

        glutIdleFunc(NULL); // Stop the jump animation when it reaches the peak
    }
}


/* ------------- start of animation function --------------- */
void animation_run(void)
{
    //write your code here
    int angle = 30;
    /*
    These codes are simplified. You may add more codes to control the robot walk better.
    */
    switch (step_status)
    {
    case NO_STATUS:
        step_status = LEFT_UPPER_LEG;
        right_hip = 0;
        right_knee = 0;
        left_hip = 0;
        left_knee = 0;

    case LEFT_UPPER_LEG:
        if (right_hip > -1 * angle)
        {
            right_hip -= frame;
            right_knee += frame;
        }
        left_knee = 0;
        if (right_hip <= -1 * angle)
            step_status = LEFT_LOWER_LEG;
        break;
    case LEFT_LOWER_LEG:
        right_knee -= frame;
        //left_hip += frame / 3 * 2;
        if (right_knee == 0) step_status = LEFT_LEG_DOING_UPPER;
        break;

    case LEFT_LEG_DOING_UPPER:
        right_hip += frame;
        right_knee = 0;
        //left_hip -= frame;
        left_hip = 0;
        left_knee += frame * 2;
        if (right_hip == 0) step_status = RIGHT_UPPER_LEG;
        break;

    case RIGHT_UPPER_LEG:
        if (left_hip > -1 * angle);
        {
            left_hip -= frame;
            left_knee += frame;
        }
        right_knee = 0;
        std::cout << left_hip << std::endl;
        if (left_hip <= -1 * angle)
            step_status = RIGHT_LOWER_LEG;
        break;


    case RIGHT_LOWER_LEG:
        left_knee -= frame;
        //right_hip += frame / 3 * 2;
        if (left_knee == 0) step_status = RIGHT_LEG_DOING_UPPER;
        break;

    case RIGHT_LEG_DOING_UPPER:
        left_hip += frame;
        left_knee == 0;
        //right_hip -= frame;
        right_hip = 0;
        right_knee += frame * 2;
        if (left_hip == 0) step_status = LEFT_UPPER_LEG;
        break;

    default:
        break;



    }
    right_shoulder = left_hip;
    left_shoulder = right_hip;
    /*
    Take a random value to add. You can use formula to calculte to accurate value to add.
    */
    distance += 0.03;

    display();
    glutPostRedisplay();
}
/* ------------- end of animation function --------------- */


/* ----------- start of keyboard events handling functions ------------ */
void keyboard(unsigned char key, int x, int y)
{
    int i = 1;
    switch (key) {
        /* start arm control functions */
    case 'q':
        /* wirte your code here */
        if (left_shoulder >= -180)
            left_shoulder = (left_shoulder - SHOULDER_RATE) % 360; break;
    case 'Q':
        /* wirte your code here */
        if (left_shoulder <= 0)
            left_shoulder = (left_shoulder + SHOULDER_RATE) % 360; break;
    case 'w':
        /* wirte your code here */
        if (right_shoulder >= -180)
            right_shoulder = (right_shoulder - SHOULDER_RATE) % 360; break;
    case 'W':
        /* wirte your code here */
        if (right_shoulder <= 0)
            right_shoulder = (right_shoulder + SHOULDER_RATE) % 360; break;
    case 'e':
        /* wirte your code here */
        if (left_elbow >= -70)   //-170
            left_elbow = (left_elbow - ELBOW_RATE) % 360; break;
    case 'E':
        /* wirte your code here */
        if (left_elbow <= 0)
            left_elbow = (left_elbow + ELBOW_RATE) % 360; break;
    case 'r':
        /* wirte your code here */
        if (right_elbow >= -70)  //-170
            right_elbow = (right_elbow - ELBOW_RATE) % 360; break;
    case 'R':
        /* wirte your code here */
        if (right_elbow <= 0)
            right_elbow = (right_elbow + ELBOW_RATE) % 360; break;
        /* end of arm control functions */

        /* start of torso control functions */
    case 'y':
        /* wirte your code here */
        if (pivot >= -90)
            pivot = (pivot - TORSO_ROTATE_RATE) % 360;
        break;
    case 'Y':
        /* wirte your code here */
        if (pivot <= 90)
            pivot = (pivot + TORSO_ROTATE_RATE) % 360; break;
        //case 'u':
        //	if (tilt >= -120)
        /* wirte your code here */
        //	tilt = (tilt - TORSO_TILT_RATE) % 360; break;
        //case 'U':
        /* wirte your code here */
        //if (tilt <= 0)
        //	tilt = (tilt + TORSO_TILT_RATE) % 360; break;
        /* end of torso control functions */

    case 'u':
        if (tilt >= -50)
            /* wirte your code here */
            tilt = (tilt - TORSO_TILT_RATE) % 360; break;
    case 'U':
        /* wirte your code here */
        if (tilt <= 0)
            tilt = (tilt + TORSO_TILT_RATE) % 360; break;
        /* end of torso control functions */


        /* start of leg control functions */
    case 'a':
        /* wirte your code here */
        if (left_hip >= -120)
            left_hip = (left_hip - UPPER_LEG_RATE) % 360; break;
    case 'A':
        /* wirte your code here */
        if (left_hip <= 0)
            left_hip = (left_hip + UPPER_LEG_RATE) % 360; break;
    case 's':
        /* wirte your code here */
        if (right_hip >= -120)
            right_hip = (right_hip - UPPER_LEG_RATE) % 360; break;
    case 'S':
        /* wirte your code here */
        if (right_hip <= 0)
            right_hip = (right_hip + UPPER_LEG_RATE) % 360; break;
    case 'd':
        /* wirte your code here */
        if (left_knee >= 0)
            left_knee = (left_knee - LOW_LEG_RATE) % 360; break;
    case 'D':
        /* wirte your code here */
        if (left_knee <= 80)
            left_knee = (left_knee + LOW_LEG_RATE) % 360; break;
    case 'f':
        /* wirte your code here */
        if (right_knee >= 0)
            right_knee = (right_knee - LOW_LEG_RATE) % 360; break;
    case 'F':
        /* wirte your code here */
        if (right_knee <= 80)
            right_knee = (right_knee + LOW_LEG_RATE) % 360; break;
    case 'g':
        /* wirte your code here */
        if (left_ankle >= -60)
            left_ankle = (left_ankle - ANKLE_RATE) % 360; break;
    case 'G':
        /* wirte your code here */
        if (left_ankle <= 20)
            left_ankle = (left_ankle + ANKLE_RATE) % 360; break;
    case 'h':
        /* wirte your code here */
        if (right_ankle >= -60)
            right_ankle = (right_ankle - ANKLE_RATE) % 360; break;
    case 'H':
        /* wirte your code here */
        if (right_ankle <= 20)
            right_ankle = (right_ankle + ANKLE_RATE) % 360; break;
        /* end of leg control functions */

        /* start of light source position functions */
    case 'o':
        /* wirte your code here */
        lightturn = (lightturn - LIGHT_TURN_RATE) % 360;
        break;
    case 'p':
        /* wirte your code here */
        lightturn = (lightturn + LIGHT_TURN_RATE) % 360;
        break;
    case 'k':
        /* wirte your code here */
        lightturn1 = (lightturn1 - LIGHT_TURN_RATE) % 360;
        break;
    case 'l':
        /* wirte your code here */
        lightturn1 = (lightturn1 + LIGHT_TURN_RATE) % 360;
        break;
        /* end of light source position functions */
    default:
        i--;
        break;
    }
    if (i)
        glutPostRedisplay();
}
/* ----------- end of keyboard events handling functions ------------ */


/* --------- start of special keys implementation --------- */
void special(int key, int x, int y)
{
    int i = 0;

    switch (key) {
        /* start of view position functions */
    case GLUT_KEY_RIGHT:
        turn = (turn - VIEW_TURN_RATE) % 360;
        i++;
        break;
    case GLUT_KEY_LEFT:
        turn = (turn + VIEW_TURN_RATE) % 360;
        i++;
        break;
    case GLUT_KEY_DOWN:
        turn1 = (turn1 - VIEW_TURN_RATE) % 360;
        i++;
        break;
    case GLUT_KEY_UP:
        turn1 = (turn1 + VIEW_TURN_RATE) % 360;
        i++;
        break;
        /* end of view postions functions */
    }
    if (i)
        glutPostRedisplay();
}
/* --------- end of special keys implementation --------- */


/* --------- start of menu implementation ---------- */
void menu_select(int mode)
{
    switch (mode) {
    case 1:
        // Start Run
        glutIdleFunc(animation_run);
        break;
    case 2:
        // Stop Run
        step_status = NO_STATUS;
        glutIdleFunc(NULL);
        break;
    case 3:
        // Exit
        exit(EXIT_SUCCESS);
        break;
    case 4:
        // Jump
        animation_jump();
        break;
    }
}


/* ARGSUSED */
void null_select(int mode)
{
}


void glutMenu(void)
{
    int glut_menu[12];

    /* move the arms -- at the shoulders */
    glut_menu[4] = glutCreateMenu(null_select);
    glutAddMenuEntry("forward       : q,w", 0);
    glutAddMenuEntry("backwards     : Q,W", 0);

    /* move the arms -- at the elbows */
    glut_menu[5] = glutCreateMenu(null_select);
    glutAddMenuEntry("upwards       : e,r", 0);
    glutAddMenuEntry("downwards     : E,R", 0);

    /* move the legs -- at the hips */
    glut_menu[7] = glutCreateMenu(null_select);
    glutAddMenuEntry("forward       : a,s", 0);
    glutAddMenuEntry("backwards     : A,S", 0);

    /* move the legs -- at the knees */
    glut_menu[8] = glutCreateMenu(null_select);
    glutAddMenuEntry("forward       : d,f", 0);
    glutAddMenuEntry("backwards     : D,F", 0);

    /* move the legs -- at the ankles */
    glut_menu[9] = glutCreateMenu(null_select);
    glutAddMenuEntry("toes up       : g,h", 0);
    glutAddMenuEntry("toes down     : G,H", 0);

    /* rotate the scene */
    glut_menu[10] = glutCreateMenu(null_select);
    glutAddMenuEntry("right         : right arrow", 0);
    glutAddMenuEntry("left          : left arrow", 0);
    glutAddMenuEntry("down          : up arrow", 0);
    glutAddMenuEntry("up            : down arrow", 0);

    /* rotate the light source */
    glut_menu[11] = glutCreateMenu(null_select);
    glutAddMenuEntry("right         : o", 0);
    glutAddMenuEntry("left          : p", 0);
    glutAddMenuEntry("up            : k", 0);
    glutAddMenuEntry("down          : l", 0);

    /* move the arms */
    glut_menu[3] = glutCreateMenu(NULL);
    glutAddSubMenu("at the shoulders? ", glut_menu[4]);
    glutAddSubMenu("at the elbows?", glut_menu[5]);

    /* move the legs */
    glut_menu[6] = glutCreateMenu(NULL);
    glutAddSubMenu("at the hip? ", glut_menu[7]);
    glutAddSubMenu("at the knees?", glut_menu[8]);
    glutAddSubMenu("at the ankles? ", glut_menu[9]);

    /* rotate at waist */
    glut_menu[1] = glutCreateMenu(null_select);
    glutAddMenuEntry("turn left    : u", 0);
    glutAddMenuEntry("turn right   : U", 0);

    /* move the torso */
    glut_menu[2] = glutCreateMenu(null_select);
    glutAddMenuEntry("tilt backwards : y", 0);
    glutAddMenuEntry("tilt forwards  : Y", 0);

    glut_menu[0] = glutCreateMenu(NULL);
    glutAddSubMenu("move the arms.. ", glut_menu[3]);
    glutAddSubMenu("move the legs.. ", glut_menu[6]);
    glutAddSubMenu("rotate the waist?", glut_menu[1]);
    glutAddSubMenu("move the torso?", glut_menu[2]);
    glutAddSubMenu("rotate the scene..", glut_menu[10]);
    glutAddSubMenu("rotate the light source..", glut_menu[11]);

    glutCreateMenu(menu_select);

    glutAddMenuEntry("Start Run", 1);
    glutAddMenuEntry("Stop Run", 2);
    glutAddSubMenu("How can I ..", glut_menu[0]);

    glutAddMenuEntry("Exit", 3);

    glutAttachMenu(GLUT_LEFT_BUTTON);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}
/* --------- end of menu implementation ---------- */


int main(int argc, char** argv)
{
    /* start of glut windowing and control functions */
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("ROBOTA");
    myinit();
    glutDisplayFunc(display);
    glutReshapeFunc(myReshape);

    glutKeyboardFunc(keyboard);

    glutSpecialFunc(special);
    glutMenu();
    glutMainLoop();
    /* end of glut windowing and control functions */
    return 0;             /* ANSI C requires main to return int. */
}
