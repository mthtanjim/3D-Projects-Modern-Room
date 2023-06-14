#include<GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <windows.h>
#include<mmsystem.h>
#include<math.h>

const int width = 1000;
const int height = 1000;
boolean L1a=true,L1d=true,L1s=true,L2a=true,L2d=true,L2s=true;

GLfloat eyeX = 5;
GLfloat eyeY = 4;
GLfloat eyeZ = -13;
GLfloat lookX = 5;
GLfloat lookY = 3;
GLfloat lookZ = 0;

float rot = 0,theta=0,speed=3.0;
boolean bRotate=true;

float l_height = 15;
float spt_cutoff = 30;

bool l_on1 = true,l_on2 = true;


//for image codes
GLuint textureID; // Texture ID


static GLfloat v_cube[8][3] =
{
    {0,0,0},
    {0,0,1},
    {0,1,0},
    {0,1,1},

    {1,0,0},
    {1,0,1},
    {1,1,0},
    {1,1,1}
};

static GLubyte c_ind[6][4] =
{
    {0,2,6,4},
    {1,3,7,5},
    {0,4,5,1},
    {2,6,7,3},
    {0,1,3,2},
    {4,5,7,6}
};

static void getNormal3p(GLfloat x1, GLfloat y1, GLfloat z1, GLfloat x2, GLfloat y2, GLfloat z2, GLfloat x3, GLfloat y3, GLfloat z3)
{
    GLfloat Ux, Uy, Uz, Vx, Vy, Vz, Nx, Ny, Nz;

    Ux = x2-x1;
    Uy = y2-y1;
    Uz = z2-z1;

    Vx = x3-x1;
    Vy = y3-y1;
    Vz = z3-z1;

    Nx = Uy*Vz - Uz*Vy;
    Ny = Uz*Vx - Ux*Vz;
    Nz = Ux*Vy - Uy*Vx;

    glNormal3f(Nx,Ny,Nz);
}
void light()
{

   GLfloat  lgt[4][4]={
       {0, 0, 0, 1.0},
       {0.2, 0.2, 0.2, 1.0},
       {1,1,1,1},
       {1,1,1,1}
   };

    GLfloat light_1_pos[] = {8,2,-1,1.0};
    GLfloat light_2_pos[] = {2,4,-8,1.0};


    glEnable(GL_LIGHT0);
    if(l_on1&&L1a) glLightfv(GL_LIGHT0, GL_AMBIENT, lgt[1]);
    else glLightfv(GL_LIGHT0, GL_AMBIENT,lgt[0]);
    if(l_on1&&L1d) glLightfv(GL_LIGHT0, GL_DIFFUSE,lgt[2]);
    else glLightfv(GL_LIGHT0, GL_DIFFUSE, lgt[0]);
    if(l_on1&&L1s) glLightfv(GL_LIGHT0, GL_SPECULAR,lgt[3]);
    else glLightfv(GL_LIGHT0, GL_SPECULAR,lgt[0]);
    glLightfv(GL_LIGHT0, GL_POSITION,light_1_pos);




    glEnable(GL_LIGHT1);
    if(l_on2&&L2a) glLightfv(GL_LIGHT1, GL_AMBIENT,lgt[1]);
    else glLightfv(GL_LIGHT1, GL_AMBIENT,lgt[0]);
    if(l_on2&&L2d) glLightfv(GL_LIGHT1, GL_DIFFUSE,lgt[2]);
    else glLightfv(GL_LIGHT1, GL_DIFFUSE,lgt[0]);
    if(l_on2&&L2s) glLightfv(GL_LIGHT1, GL_SPECULAR,lgt[3]);
    else glLightfv(GL_LIGHT1, GL_SPECULAR,lgt[0]);
    glLightfv(GL_LIGHT1, GL_POSITION,light_2_pos);


    glEnable(GL_LIGHT2);
    GLfloat l_spt[] = {0,-1,0,1};
    GLfloat spt_ct[] = {spt_cutoff};
    glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, l_spt);
    glLightfv(GL_LIGHT2, GL_SPOT_CUTOFF, spt_ct);




}

void cube(float ColR=0.9, float ColG=0.2, float ColB=0.5)
{

    GLfloat m_no[] = {0, 0, 0, 1.0};
    GLfloat m_amb[] = {ColR,ColG,ColB,1};
    GLfloat m_diff[] = {ColR,ColG,ColB,1};
    GLfloat m_spec[] = {1,1,1,1};
    GLfloat m_sh[] = {40};

    glMaterialfv(GL_FRONT, GL_AMBIENT, m_amb);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, m_diff);
    glMaterialfv(GL_FRONT, GL_SPECULAR, m_spec);
    glMaterialfv(GL_FRONT, GL_SHININESS, m_sh);


    glBegin(GL_QUADS);
    for (GLint i = 0; i <6; i++)
    {
        getNormal3p(v_cube[c_ind[i][0]][0], v_cube[c_ind[i][0]][1], v_cube[c_ind[i][0]][2],
                    v_cube[c_ind[i][1]][0], v_cube[c_ind[i][1]][1], v_cube[c_ind[i][1]][2],
                    v_cube[c_ind[i][2]][0], v_cube[c_ind[i][2]][1], v_cube[c_ind[i][2]][2]);

        for (GLint j=0; j<4; j++)
        {
            glVertex3fv(&v_cube[c_ind[i][j]][0]);
        }
    }
    glEnd();
}

void room()
{


    //main flore
    for(int i=0; i<10; i=i+2)
    {
        for(int j=0; j<10; j=j+2)
        {

            glPushMatrix();
            glTranslated(i,0,-j);
            glScalef(1,0.1,-1);
              cube(1,1, 1);
            glPopMatrix();
        }

        for(int j=1; j<10; j=j+2)
        {

            glPushMatrix();
            glTranslated(i,0,-j);
            glScalef(1,0.1,-1);

              cube(0, 0.616, 0.851);
            glPopMatrix();
        }


    }

    for(int i=1; i<10; i=i+2)
    {
        for(int j=1; j<10; j=j+2)
        {

            glPushMatrix();
            glTranslated(i,0,-j);
            glScalef(1,0.1,-1);
            cube(0, 0.616, 0.851);
            glPopMatrix();
        }

        for(int j=0; j<10; j=j+2)
        {

            glPushMatrix();
            glTranslated(i,0,-j);
            glScalef(1,0.1,-1);
           cube(1,1, 1);
            glPopMatrix();
        }


    }

    //back wall
    glPushMatrix();
    glScalef(10,10,0.5);
    cube(0.541, 0.169, 0.886);
    glPopMatrix();


    //left wall
    glPushMatrix();
    glScalef(.5,5,-10);
    cube(1, 0.851, 0.38);
    glPopMatrix();


    //right wall
    glPushMatrix();
    glTranslated(10,0,0);
    glScalef(.2,5,-10);
    cube(1, 0.459, 0.902);
    glPopMatrix();


    //ceil
    glPushMatrix();
    glTranslated(0,5,0);
    glScalef(10,.5,-10);
    cube(0.44, 0.706, 0.549);
    glPopMatrix();

}

void ac()
{

    glPushMatrix();
    glTranslated(2,3.5,0);
    glScalef(1.8,0.7,-0.5);
    cube(0.3,0.5,0.8);
    glPopMatrix();
}

void watch()
{
    glPushMatrix();
    glTranslated(4,3,-0.1);
    glScalef(1,1,-0.1);
    cube(.7,.7,.7);
    glPopMatrix();

//hour
    glPushMatrix();
    glTranslated(4.5,3.5,-0.12);
    glScalef(-.2,0.05,-0.1);
    cube(.1,.1,.1);
    glPopMatrix();
//minute
    glPushMatrix();
    glTranslated(4.5,3.5,-0.12);
    glScalef(0.05,0.4,-0.1);
    cube(.1,.1,.1);
    glPopMatrix();
}


void artwork()
{
    // Artwork body
    glPushMatrix();
    glTranslatef(7.0, 4.5, -4.5);
    glScalef(0.8, 0.8, 0.1);
    cube(0.804, 0.522, 0.247);
    glPopMatrix();

    // Artwork details
    glPushMatrix();
    glTranslatef(7.0, 4.5, -4.5);
    glScalef(0.6, 0.6, 0.1);

    glPopMatrix();
}


void table2()
{


    //main box1
    glPushMatrix();
    glTranslated(1,0.05,-7.5);
    glScalef(1,0.5,-0.5);
    cube(0.502, 0.000, 0.000);
    glPopMatrix();

    //box
    glPushMatrix();
    glTranslated(1,.07,-7.55);
    glScalef(1.03,0.4,-0.4);
    cube(0.1, 0.30, 0.40);
    glPopMatrix();
//hand1
    glPushMatrix();
    glTranslated(2,.3,-7.7);
    glScalef(0.1,0.05,-0.1);
    cube(1,1,1);
    glPopMatrix();



    //main box2
    glPushMatrix();
    glTranslated(1,0.48,-7.5);
    glScalef(1,0.5,-0.5);
    cube(0.502, 0.000, 0.000);
    glPopMatrix();

    //partision1
    glPushMatrix();
    glTranslated(1,.52,-7.55);
    glScalef(1.03,0.4,-0.4);
    cube(0.1, 0.30, 0.40);
    glPopMatrix();

    //hand2
    glPushMatrix();
    glTranslated(2,.7,-7.7);
    glScalef(0.1,0.05,-0.1);
    cube(1,1,1);
    glPopMatrix();



//main box3

    glPushMatrix();
    glTranslated(1,0.92,-7.5);
    glScalef(1,0.5,-0.5);
    cube(0.502, 0.000, 0.000);
    glPopMatrix();

    //box
    glPushMatrix();
    glTranslated(1,0.98,-7.55);
    glScalef(1.03,0.4,-0.4);
    cube(0.1, 0.30, 0.40);
    glPopMatrix();
//hand1
    glPushMatrix();
    glTranslated(2,1.1,-7.7);
    glScalef(0.1,0.05,-0.1);
    cube(1,1,1);
    glPopMatrix();



//main box4
    glPushMatrix();
    glTranslated(1,1.42,-7.5);
    glScalef(1,0.5,-0.5);
    cube(0.502, 0.000, 0.000);
    glPopMatrix();

    //box
    glPushMatrix();
    glTranslated(1,1.46,-7.55);
    glScalef(1.03,0.4,-0.4);
    cube(0.1, 0.30, 0.40);
    glPopMatrix();
//hand1
    glPushMatrix();
    glTranslated(2,1.6,-7.7);
    glScalef(0.1,0.05,-0.1);
    cube(1,1,1);
    glPopMatrix();




//main box5
    glPushMatrix();
    glTranslated(1,0.05,-8);
    glScalef(1,0.5,-0.5);
    cube(0.502, 0.000, 0.000);
    glPopMatrix();

    //box
    glPushMatrix();
    glTranslated(1,.07,-8.05);
    glScalef(1.03,0.4,-0.4);
    cube(0.1, 0.30, 0.40);
    glPopMatrix();
//hand1
    glPushMatrix();
    glTranslated(2,.3,-8.2);
    glScalef(0.1,0.05,-0.1);
    cube(1,1,1);
    glPopMatrix();

//main box6
    glPushMatrix();
    glTranslated(1,0.48,-8);
    glScalef(1,0.5,-0.5);
    cube(0.502, 0.000, 0.000);
    glPopMatrix();

    //partision1
    glPushMatrix();
    glTranslated(1,.52,-8.05);
    glScalef(1.03,0.4,-0.4);
    cube(0.1, 0.30, 0.40);
    glPopMatrix();

    //hand2
    glPushMatrix();
    glTranslated(2,.7,-8.2);
    glScalef(0.1,0.05,-0.1);
    cube(1,1,1);
    glPopMatrix();





//main box7

    glPushMatrix();
    glTranslated(1,0.92,-8);
    glScalef(1,0.5,-0.5);
    cube(0.502, 0.000, 0.000);
    glPopMatrix();

    //box
    glPushMatrix();
    glTranslated(1,0.98,-8.05);
    glScalef(1.03,0.4,-0.4);
    cube(0.1, 0.30, 0.40);
    glPopMatrix();
//hand1
    glPushMatrix();
    glTranslated(2,1.1,-8.2);
    glScalef(0.1,0.05,-0.1);
    cube(1,1,1);
    glPopMatrix();



//main box8
    glPushMatrix();
    glTranslated(1,1.42,-8);
    glScalef(1,0.5,-0.5);
    cube(0.502, 0.000, 0.000);
    glPopMatrix();

    //box
    glPushMatrix();
    glTranslated(1,1.46,-8.05);
    glScalef(1.03,0.4,-0.4);
    cube(0.1, 0.30, 0.40);
    glPopMatrix();
//hand1
    glPushMatrix();
    glTranslated(2,1.6,-8.2);
    glScalef(0.1,0.05,-0.1);
    cube(1,1,1);
    glPopMatrix();




}

void dressing_table1()
{
    //main box1
    glPushMatrix();
    glTranslated(7,0.5,-0.5);
    glScalef(1,1,-1);
    cube(0.502, 0.000, 0.000);
    glPopMatrix();
    //box
    glPushMatrix();
    glTranslated(7.1,.6,-.6);
    glScalef(0.8,0.8,-1);
    cube(0.1, 0.30, 0.40);
    glPopMatrix();
//hand1
    glPushMatrix();
    glTranslated(7.3,.8,-.7);
    glScalef(0.3,0.1,-1);
    cube(1,1,1);
    glPopMatrix();


    //main box3
    glPushMatrix();
    glTranslated(7,1.5,-0.5);
    glScalef(1,1,-1);
    cube(0.502, 0.000, 0.000);
    glPopMatrix();
    //box
    glPushMatrix();
    glTranslated(7.1,1.6,-.6);
    glScalef(0.8,0.8,-1);
    cube(0.1, 0.30, 0.40);
    glPopMatrix();
//hand1
    glPushMatrix();
    glTranslated(7.3,1.8,-.7);
    glScalef(0.3,0.1,-1);
    cube(1,1,1);
    glPopMatrix();


    //main box4
    glPushMatrix();
    glTranslated(7,2.5,-0.5);
    glScalef(1,1,-1);
    cube(0.502, 0.000, 0.000);
    glPopMatrix();
    //box
    glPushMatrix();
    glTranslated(7.1,2.6,-.6);
    glScalef(0.8,0.8,-1);
    cube(0.1, 0.30, 0.40);
    glPopMatrix();
//hand1
    glPushMatrix();
    glTranslated(7.3,2.8,-.7);
    glScalef(0.3,0.1,-1);
    cube(1,1,1);
    glPopMatrix();





    //main box2
    glPushMatrix();
    glTranslated(8,0.5,-0.5);
    glScalef(1,1,-1);
    cube(0.502, 0.000, 0.000);
    glPopMatrix();
    //box
    glPushMatrix();
    glTranslated(8.1,.6,-.6);
    glScalef(0.8,0.8,-1);
    cube(0.1, 0.30, 0.40);
    glPopMatrix();
//hand1
    glPushMatrix();
    glTranslated(8.4,.8,-.7);
    glScalef(0.3,0.1,-1);
    cube(1,1,1);
    glPopMatrix();




    //main box2
    glPushMatrix();
    glTranslated(8,1.5,-0.5);
    glScalef(1,2,-0.1);
    cube(0.502, 0.000, 0.000);
    glPopMatrix();
    //box
    glPushMatrix();
    glTranslated(8.1,1.6,-.6);
    glScalef(0.8,1.8,-0.12);
    cube(1,1,1);
    glPopMatrix();


}

void dressing_table()
{
//main box 1
    glPushMatrix();
    glTranslated(7,0,0);
    glScalef(2,0.90,-1);
    cube(0.502, 0.000, 0.000);
    glPopMatrix();

    //main box partision
    glPushMatrix();
    glTranslated(7,0.90,-1);
    glScalef(1.8,0.8,-0.11);
    cube(0.15, 0.15, 0.15);
    glPopMatrix();

    //main box 2
    glPushMatrix();
    glTranslated(7,1,-1);
    glScalef(2,0.90,1);
    cube(0.502, 0.000, 0.000);
    glPopMatrix();

//ayna
    glPushMatrix();
    glTranslated(8,1.9,-1);
    glScalef(1,2.1,0.1);
    cube(1,1,1);
    glPopMatrix();

    //partision1
    glPushMatrix();
    glTranslated(7,1.9,-1);
    glScalef(1,0.1,0.1);
    cube(0.15, 0.15, 0.15);
    glPopMatrix();

//drawar1
    glPushMatrix();
    glTranslated(7,2,-1);
    glScalef(1,0.95,1);
    cube(0.502, 0.000, 0.000);
    glPopMatrix();

//partision2
    glPushMatrix();
    glTranslated(7,2.95,-1);
    glScalef(1,0.1,0.1);
    cube(0.15, 0.15, 0.15);
    glPopMatrix();

//drawar 2
    glPushMatrix();
    glTranslated(7,3.05,-1);
    glScalef(1,0.95,1);
    cube(0.502, 0.000, 0.000);
    glPopMatrix();


}

void janala()
{
    // Main window frame
    glPushMatrix();
    glTranslatef(0.5, 2, -2);
    glScalef(0.1, 2, -2);
    cube(1.0, 0.502, 0.502); // Gray color for the frame
    glPopMatrix();

    // Window divisions (horizontal)
    for (float y = 2.5; y <= 3.5; y += 0.5) {
        glPushMatrix();
        glTranslatef(0.55, y, -2);
        glScalef(0.1, 0.02, -2);
        cube(0.253, 0.753, 0.753);
        glPopMatrix();
    }

    // Window divisions (vertical)
    for (float x = 0.55; x <= 0.95; x += 0.2) {
        glPushMatrix();
        glTranslatef(x, 3, -2);
        glScalef(0.02, 0.5, -2);
        cube(0.753, 1.0, 0.753);
        glPopMatrix();
    }

    // Window glass
    glPushMatrix();
    glTranslatef(0.55, 2.75, -2);
    glScalef(0.1, 0.5, -2); // Adjust the size of the glass
    cube(0.878, 0.100, 0.8);
    glPopMatrix();
}


void tv()
{
    // TV frame
    glPushMatrix();
    glTranslated(0.5, 2, -2);
    glScalef(0.1, 2, -2);
    cube(0.329, 0.859, 0.055);
    glPopMatrix();

    // TV screen
    glPushMatrix();
    //glColor3f(0.0, 0.3, 0.9); // Black screen color
    glTranslated(0.5, 2.05, -2.1);
    glScalef(0.08, 1.9, -1.9);
    cube();
    glPopMatrix();

    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, textureID); // Bind the texture
    glBegin(GL_QUADS);
    glTexCoord2f(0.0, 0.0); glVertex3f(-1.0, -1.0, 0.0);
    glTexCoord2f(1.0, 0.0); glVertex3f(1.0, -1.0, 0.0);
    glTexCoord2f(1.0, 1.0); glVertex3f(1.0, 1.0, 0.0);
    glTexCoord2f(0.0, 1.0); glVertex3f(-1.0, 1.0, 0.0);
    glEnd();
    glBindTexture(GL_TEXTURE_2D, 0); // Unbind the texture
    glPopMatrix();
}

void bed()
{
    // Main bed frame
    glPushMatrix();
    glTranslated(2, 1.5, -1);
    glScalef(3, 0.1, -5);
    cube(0.933, 0.98, 1);
    glPopMatrix();

    // Back design
    glPushMatrix();
    glTranslated(2, 0, -1);
    glScalef(3, 2.5, -0.1);
    cube(0.4, 0.4, 0.4);
    glPopMatrix();

    // Front side (modern design)
    glPushMatrix();
    glTranslated(2, 0, -6);
    glScalef(3, 1.5, -0.1);
    cube(0.8, 0.8, 0.8);
    glPopMatrix();

    // Left side
    glPushMatrix();
    glTranslated(5, 0, -1);
    glScalef(0.1, 1.5, -5);
    cube(0.4, 0.4, 0.4);
    glPopMatrix();

    // Right side
    glPushMatrix();
    glTranslated(2, 0, -1);
    glScalef(0.1, 1.5, -5);
    cube(0.4, 0.4, 0.4);
    glPopMatrix();

     // Pillow
     glPushMatrix();
    glTranslated(2.12, 1.5, -1.9);
    glScalef(2.5, 0.3, 0.5);
    glColor3f(0, 0.5, 1.0); // White color for the pillow
    cube();
    glPopMatrix();

}

void chair()
{
    // Seat
    glPushMatrix();
    glTranslatef(6.3, 0.75, -4.5);
    glScalef(1.2, 0.1, -1);
    cube(0.5, 0.5, 0.5); // Gray color for the seat
    glPopMatrix();

    // Backrest
    glPushMatrix();
    glTranslatef(6.3, 1.5, -4.5);
    glScalef(1, 1, -0.1);
    cube(0.5, 0.5, 0.5); // Gray color for the backrest
    glPopMatrix();

    // Front legs
    glPushMatrix();
    glTranslatef(6.3, 0.35, -4.2);
    glScalef(0.1, 1, -0.1);
    cube(0.3, 0.3, 0.3); // Dark gray color for the legs
    glPopMatrix();

    glPushMatrix();
    glTranslatef(6.3, 0.35, -4.8);
    glScalef(0.1, 1, -0.1);
    cube(0.3, 0.3, 0.3); // Dark gray color for the legs
    glPopMatrix();

    // Back legs
    glPushMatrix();
    glTranslatef(7.2, 0.35, -4.8);
    glScalef(0.1, 1, -0.1);
    cube(0.3, 0.3, 0.3); // Dark gray color for the legs
    glPopMatrix();

    glPushMatrix();
    glTranslatef(7.2, 0.35, -4.2);
    glScalef(0.1, 1, -0.1);
    cube(0.3, 0.3, 0.3); // Dark gray color for the legs
    glPopMatrix();
}


void curpus()
{
    glPushMatrix();
    glTranslated(3,0.1,-6.2);
    glScalef(1.5,0.05,-0.25);
    cube(1, 0.000, 0.000);
    glPopMatrix();

    glPushMatrix();
    glTranslated(3,0.1,-6.45);
    glScalef(1.5,0.05,-0.25);
    cube(0,1, 0.000);
    glPopMatrix();


    glPushMatrix();
    glTranslated(3,0.1,-6.7);
    glScalef(1.5,0.05,-0.25);
    cube(0, 0.000, 1);
    glPopMatrix();

}

void curpus2()
{
    glPushMatrix();
    glTranslated(3,0.1,-6.2);
    glScalef(1.5,0.05,-0.25);
    cube(1, 0.000, 0.000);
    glPopMatrix();

    glPushMatrix();
    glTranslated(3,0.1,-6.45);
    glScalef(1.5,0.05,-0.25);
    cube(0,1, 0.000);
    glPopMatrix();


    glPushMatrix();
    glTranslated(3,0.1,-6.7);
    glScalef(1.5,0.05,-0.25);
    cube(0, 0.000, 1);
    glPopMatrix();

}


void fan()
{
    ///fan's handle
    glPushMatrix();
    glTranslatef(4.15,6,-3);
    glRotated(10,0,1,0);
    glScalef(0.2,-2,-0.2);
    cube(0.7,0.6,0.8);
    glPopMatrix();

    ///body of fan;
    glPushMatrix();
    glTranslatef(4,4,-3);
    glRotated(10,0,1,0);
    glScalef(0.5,-0.5,-0.5);
    cube(0.545, 0.000, 0.000);
    glPopMatrix();

    /// pakha1
    glPushMatrix();
    glColor3f(1.000, 0.843, 0.000);
    glTranslatef(4,3.5,-3);
    glRotated(theta,0,1,0);
    glScalef(3,.1,.5);
    cube();
    glPopMatrix();
    ///pakha 2

    glPushMatrix();
    glColor3f(1.000, 0.843, 0.000);
    glTranslatef(4,3.5,-3);
    glRotated(theta+120,0,1,0);
    glScalef(3,.1,.5);
    cube();
    glPopMatrix();

    ///pakha 3

    glPushMatrix();
    glColor3f(1.000, 0.843, 0.000);
    glTranslatef(4,3.5,-4);
    glRotated(theta+240,0,1,0);
    glScalef(3,.1,.5);
    cube();
    glPopMatrix();
}


void table()
{
    //main part

      // Table top
    glPushMatrix();
    glTranslatef(7.5, 2.0, -4.0);
    glScalef(1.5, 0.1, -2.0);
    cube(0.663, 0.663, 0.663); // Adjust the color as needed
    glPopMatrix();

    // Table legs
    glPushMatrix();
    glTranslatef(9.0, 0.0, -4.0);
    glScalef(0.1, 2.0, 0.1);
    cube(0.663, 0.663, 0.663); // Adjust the color as needed
    glPopMatrix();

    glPushMatrix();
    glTranslatef(7.5, 0.0, -4.0);
    glScalef(0.1, 2.0, 0.1);
    cube(0.663, 0.663, 0.663); // Adjust the color as needed
    glPopMatrix();

    glPushMatrix();
    glTranslatef(8.9, 0.0, -5.9);
    glScalef(0.1, 2.0, 0.1);
    cube(0.663, 0.663, 0.663); // Adjust the color as needed
    glPopMatrix();

    glPushMatrix();
    glTranslatef(7.5, 0.0, -5.9);
    glScalef(0.1, 2.0, 0.1);
    cube(0.663, 0.663, 0.663); // Adjust the color as needed
    glPopMatrix();


}


void ttable()
{
    // Table top (circle)
    glPushMatrix();
    glTranslatef(7.5, 2, -4);
    glScalef(2, 0.1, 1.5);
    glColor3f(1.0, 0.0, 1.0);
    glutSolidSphere(0.65, 50, 50);
    glPopMatrix();

    // Table leg
    glPushMatrix();
    glTranslatef(7.5, 0.05, -4);
    glScalef(0.2, 2.0, 0.2);
    glColor3f(0.0, 0.0, 0.0);
    cube(0.7, 0.25, 0.9);
    glPopMatrix();


    // Books
    glPushMatrix();
    glTranslatef(7.2, 1.8, -4);
    glColor3f(0.2, 0.2, 0.2);
    glScalef(0.8, 0.4, 0.2);
    cube(0.9, 0.2, 0.2);

    glPopMatrix();
}

void calendar()
{
    // Calendar body
    glPushMatrix();
    glTranslatef(9.8, 2.5, -4.5);
    glScalef(0.8, 1.2, 0.1);
    cube(0.502, 0.000, 0.000);
    glPopMatrix();

    // Calendar days
    glPushMatrix();
    glTranslatef(9.8, 2.5, -4.5);
    glScalef(0.1, 0.2, 0.1);

    // Draw the calendar days
    for (int i = 0; i < 7; i++) {
        for (int j = 0; j < 6; j++) {
            glPushMatrix();
            glTranslatef(i * 0.2, -j * 0.3, 0);
            cube(1.0, 1.0, 1.0); // You can modify the colors as needed
            glPopMatrix();
        }
    }

    glPopMatrix();
}

void wallMountedStorage()
{
    // Storage unit body
    glPushMatrix();
    glTranslatef(6.0, 2.0, -8.0);
    glScalef(0.8, 1.2, 0.1);
    cube(0.196, 0.804, 0.196); // Green color for the body
    glPopMatrix();

    // Storage compartments
    glPushMatrix();
    glTranslatef(6.0, 2.0, -8.0);
    glScalef(0.1, 0.2, 0.1);

    // Draw the storage compartments with different colors
    float colors[4][3] = {
        {0.827, 0.827, 0.827},
        {0.753, 0.753, 0.753},
        {0.878, 0.878, 0.878},
        {0.902, 0.902, 0.902}
    };

    for (int i = 0; i < 4; i++) {
        glPushMatrix();
        glTranslatef(0, -i * 0.3, 0);
        cube(colors[i][0], colors[i][1], colors[i][2]);
        glPopMatrix();
    }

    glPopMatrix();
}

void bathroomDoor()
{
    // Door frame
    glPushMatrix();
    glTranslatef(9.5, 0.5, -3.5);
    glScalef(0.03, 3.1, -0.7);
    cube(0.3, 0.2, 0.2);
    glPopMatrix();

    // Door panel
    glPushMatrix();
    glTranslatef(9.4, 0.5, -3.5);
    glScalef(0.01, 3.1, -0.7);
    cube(0.9, 0.7, 0.616);
    glPopMatrix();

    // Door handle
    glPushMatrix();
    glTranslatef(9.5, 2.1, -3.2);
    glScalef(0.3, 0.5, -0.1);
    cube(0, 0, 0.227);
    glPopMatrix();
}

static void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-3, 3, -3, 3, 2.0, 100.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(eyeX,eyeY,eyeZ, lookX,lookY,lookZ, 0,1,0);
    glViewport(0, 0, width, height);

    glRotatef(rot, 0,1,0);
    // axes();
glPushMatrix();
 glTranslated(5,-0.7,-1);
    bed();
 glPopMatrix();


 glPushMatrix();
 glTranslated(0,0,-5);
     bathroomDoor();
 glPopMatrix();


  glPushMatrix();
    glTranslated(-3.9,-1,-3.4);
    ttable();
    glPopMatrix();

    glPushMatrix();
    glTranslated(0,-0.5,0);
    janala();
    glPopMatrix();

    glPushMatrix();
    glTranslated(3,0,0);
    fan();
    glPopMatrix();

  //tv
    glPushMatrix();
    glTranslated(0,0,-5);
    tv();
    glPopMatrix();

    //artwork
    glPushMatrix();
    glTranslated(0,-0.8,3.8);
    artwork();
    glPopMatrix();

     glPushMatrix();
    glTranslated(-1.5,-0.7,4);
    wallMountedStorage();
    glPopMatrix();

  //room calender
    glPushMatrix();
    glTranslated(0,0,-2);
    calendar();
    glPopMatrix();

    //table
    glPushMatrix();
    glTranslated(-5.8,-1,0);
    table();
    glPopMatrix();

    room();
    //bed();
    ac();

    //dressing_table1();
    //chair();

    glPushMatrix();
    glTranslated(3,0,2);
    curpus();
    glPopMatrix();

    //carpus 2
  glPushMatrix();
    glTranslated(5.3,0,-1.85);
    curpus2();
    glPopMatrix();

    watch();
    table2();

   // glPushMatrix();
   // glTranslated(8,2.5,-5.5);
   // glutSolidSphere(.5,40,4);
    //glPopMatrix();

    glPushMatrix();
    //glRotatef(45, 0,1,0);
    light();
    glPopMatrix();

    glutSwapBuffers();
}

static void key(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 27 :
    case 'q':
        exit(0);
        break;

    case ',':
        rot++;
        break;
    case '.':
        rot--;
        break;


    case 'w':
        eyeY=eyeY+0.1;
        break;
    case 's':
        eyeY=eyeY-0.1;
        break;
    case 'd':
        eyeX=eyeX+0.1;
        break;
    case 'a':
        eyeX=eyeX-0.1;
        break;


    case 'i':
        lookY=lookY+0.1;
        break;
    case 'k':
        lookY=lookY-0.1;
        break;
    case 'j':
        lookX=lookX+0.1;
        break;
    case 'l':
        lookX=lookX-0.1;
        break;


    case '+':
        eyeZ=eyeZ+0.1;
        break;
    case '-':
        eyeZ=eyeZ-0.1;
        break;

    case 'r':
        speed+=0.5;
        break;
    case 't':
        speed-=0.5;
        break;




    case '1':
        l_on1=1-l_on1;
        break;
    case 'z':
        L1a=1-L1a;
        break;
    case 'x':
        L1d=1-L1d;
        break;
    case 'c':
        L1s=1-L1s;
        break;


    case '2':
        l_on2=1-l_on2;
        break;
    case 'm':
        L2a=1-L2a;
        break;
    case 'n':
        L2d=1-L2d;
        break;
    case 'b':
        L2s=1-L2s;
        break;

    case 'f':
        if(bRotate)
        {
            bRotate=false;
        }
        else
        {
            bRotate=true;
        }
        break;

    }

    glutPostRedisplay();
}


void animate()
{
    if (bRotate == true)
    {
        theta -= speed;
        if(theta > 360.0)
            theta -= 360.0*floor(theta/360.0);
    }
    glutPostRedisplay();

}


static void idle(void)
{
    glutPostRedisplay();
}

/* Program entry point */

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitWindowSize(width,height);
    glutInitWindowPosition(10,10);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

    glutCreateWindow("GLUT Shapes");

    glutDisplayFunc(display);
    glutKeyboardFunc(key);
    //glutIdleFunc(idle);
    glutIdleFunc(animate);

//    glClearColor(1,1,1,1);

    glEnable(GL_DEPTH_TEST);
    glShadeModel( GL_SMOOTH );
    glEnable(GL_NORMALIZE);
    glEnable(GL_BLEND);

    glEnable(GL_LIGHTING);

    PlaySound("example.mp3", NULL, SND_ASYNC|SND_FILENAME|SND_LOOP);
    printf("##############           PLEASE FOLLOW THE BELOW INSTRUCTIONS          #################\n");
    printf("Use 'w' to look up, 's' to look down, 'd' to look right, and 'a' to look left.\n");
    printf("Use 'i' to move camera up, 'k' to move camera down, 'l' to move camera right, and 'j' to move camera left with the look at point fixed.\n");
    printf("Use '+' to zoom in and '-' to zoom out.\n\n\n");
    printf("Use 'f' to start and stop fan,r for speedup and t for speed down.\n\n\n");

    glutMainLoop();

    return EXIT_SUCCESS;
}
