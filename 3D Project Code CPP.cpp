#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <math.h>
#include <stdlib.h>
#include<cstdlib>
#include <string>
#include <string.h>
#include <inttypes.h>
#include<unistd.h>



float angle=0,xx=-20, yy=-20, cloudz1=-40, cloudz2=-110;
int lap=0,lap2=0,state=0,winner=0,slow_down1=0, step_animLight=0, slow_down2=100,color_red=1,color_yellow=0,color_green=0;


void display();
void anim(int);
void anim2(int);
void animStopLight(int);
void cloudAnim(int);

//display that shows winner of race
void winDisplay()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor3f(1,1,0);

    //used to print the text in display
    glRasterPos3f(-2,6,-10);
    char msg1[]="Car Racing Game 3D";
    for(int i=0;i<strlen(msg1);i++){glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,msg1[i]);}

    //used to print the text in display
    glRasterPos3f(-3,5.8,-10);
    char msg5[]="_______________________";
    for(int i=0;i<strlen(msg5);i++){glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,msg5[i]);}

    char msg2[50];

    //winner=0 --> RED || winner=1 --> PURPLE
    if(winner==0)
    {
        strcat(msg2,"Winner: Red Player!  Loser: Purple Player..");
    }
    else if(winner==1)
    {
        strcat(msg2,"Winner: Purple Player!  Loser: Red Player..");
    }
    else
    {
        strcat(msg2,"It's a tie!");
    }

    //used to print the text in display
    glRasterPos3f(-4,3,-10);
    for(int i=0;i<strlen(msg2);i++){glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,msg2[i]);}

    //used to print the text in display, if clicked, closes the game
    char msg3[50]="Quit Game: X";
    glRasterPos3f(-2,2,-10);
    for(int i=0;i<strlen(msg3);i++){glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,msg3[i]);}


    //used to print the text in display
    glRasterPos3f(1,-7,-10);
    char msg4[]="Created by <<Name>>";
    for(int i=0;i<strlen(msg4);i++){glutBitmapCharacter(GLUT_BITMAP_9_BY_15,msg4[i]);}

    glutSwapBuffers();

}
//display that shows main menu of race
void welcomeDisplay()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor3f(1,1,0);

    //used to print text
    glRasterPos3f(-2,6,-10);
    char msg1[]="Car Racing Game 3D";
    for(int i=0;i<strlen(msg1);i++){glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,msg1[i]);}

    //used to print text
    glRasterPos3f(-3,5.8,-10);
    char msg5[]="_______________________";
    for(int i=0;i<strlen(msg5);i++){glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,msg5[i]);}

    //used to print text, loads game when M is clicked
    glRasterPos3f(-1.5,3,-10);
    char msg2[]="Start Game: M";
    for(int i=0;i<strlen(msg2);i++){glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,msg2[i]);}

    //used to print text, exits game when X is clicked
    glRasterPos3f(-1.5,1,-10);
    char msg3[]="Exit Game: X";
    for(int i=0;i<strlen(msg3);i++){glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,msg3[i]);}

    //used to print text;
    glRasterPos3f(-4,-1,-10);
    char msg6[]="Controls: Red Car --> W & Purple Car --> I";
    for(int i=0;i<strlen(msg6);i++){glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,msg6[i]);}

    //used to print text;
    glRasterPos3f(1,-7,-10);
    char msg4[]="Created by Ziad Assem, Youssef El-Habrouk, and Youssef Etreby";
    for(int i=0;i<strlen(msg4);i++){glutBitmapCharacter(GLUT_BITMAP_9_BY_15,msg4[i]);}


    glutSwapBuffers();

}

void road()
{
    glColor3f(0,0,0);

    //draws a 2d rectangle along the Z axis to mimic a road
    glBegin(GL_POLYGON);

    glVertex3f(-250,-10,-250);
    glVertex3f(250,-10,-250);
    glVertex3f(250,-10,250);
    glVertex3f(-250,-10,250);

    glEnd();

    //for loop to draw yellow rectangles in the middle of the road to divide the road
    //and make it look more realistic
    for(int i=0;i>=-120;i-=20)
    {


        glColor3f(1.000, 0.843, 0.000);
        glBegin(GL_POLYGON);


        glVertex3f(-0.5,-9.9,-20+i);
        glVertex3f(0.5,-9.9,-20+i);
        glVertex3f(0.5,-9.9,-10+i);
        glVertex3f(-0.5,-9.9,-10+i);

        glEnd();

    }

}

void leftSand()
{
    glColor3f(0.933, 0.910, 0.667);


    //draws rectangle on the left side of the road till the border
    glBegin(GL_POLYGON);

    glVertex3f(-250,-9.9,-250);
    glVertex3f(-10,-9.9,-250);
    glVertex3f(-10,-9.9,250);
    glVertex3f(-250,-9.9,250);

    glEnd();

}

void rightSand()
{
    glColor3f(0.933, 0.910, 0.667);

    //draws rectangle on the left side of the road till the border
    glBegin(GL_POLYGON);

    glVertex3f(250,-9.9,-250);
    glVertex3f(10,-9.9,-250);
    glVertex3f(10,-9.9,250);
    glVertex3f(250,-9.9,250);

    glEnd();

}

/*
{
    {glMatrixMode(GL_PROJECTION);
    double *matrix=new double[16];
    glGetDoublev(GL_PROJECTION_MATRIX, matrix);
    glLoadIdentity();

    glOrtho(0,800,0,600,-5,5);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();
    glLoadIdentity();
    glRasterPos2i(x,y);
    for(int i=0;i<length; i++){

        glutBitmapCharacter((GLUT_BITMAP_9_BY_15),(int)text[i]);
    }
    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glLoadMatrixd(matrix);
    glMatrixMode(GL_MODELVIEW);
}
*/
void finish_sign()
{
    glColor3f(0,0,0);


    //left stand
    glPushMatrix();
    glTranslatef(-12,-9,-115);

    glBegin(GL_POLYGON);

    glVertex3f(-.5,0,0);
    glVertex3f(.5,0,0);
    glVertex3f(.5,12,0);
    glVertex3f(-.5,12,0);

    glEnd();
    glPopMatrix();

    //right stand
    glPushMatrix();
    glTranslatef(12,-9,-115);

    glBegin(GL_POLYGON);

    glVertex3f(-.5,0,0);
    glVertex3f(.5,0,0);
    glVertex3f(.5,12,0);
    glVertex3f(-.5,12,0);

    glEnd();
    glPopMatrix();

    //count so i can use it in loop to switch from black and white colors
    int count=1;

    //middle checkers
    for(int i=-10;i<=10;i+=2)
    {
        //to choose between black and white colors
        if(count%2==0){glColor3f(0,0,0);}
        else{glColor3f(1,1,1);}

        count++;

        glPushMatrix();

        glTranslatef(i,2,-110);

        //draws checkers
        glBegin(GL_POLYGON);

        glVertex3f(-1,1,0);
        glVertex3f(1,1,0);
        glVertex3f(1,-1,0);
        glVertex3f(-1,-1,0);

        glEnd();

        glPopMatrix();
    }

}
//function to draw red car
void car1()
{



    glPushMatrix();
    glTranslatef(-4,-7.5,xx+10);
    //glRotatef(270,0,1,0);


////////////bottom part of car////////////////////
    //front rectangle
    glBegin(GL_POLYGON);
    glColor3f(0.545, 0.000, 0.000);

    glVertex3f(-2,1,0);
    glVertex3f(2,1,0);
    glVertex3f(2,0,0);
    glVertex3f(-2,0,0);

    glEnd();

    //back rectangle

    glBegin(GL_POLYGON);

    glVertex3f(-2,1,-4);
    glVertex3f(2,1,-4);
    glVertex3f(2,0,-4);
    glVertex3f(-2,0,-4);

    glEnd();


    //right rectangle
    glBegin(GL_POLYGON);
    glColor3f(0.698, 0.133, 0.133);

    glVertex3f(2,1,0);
    glVertex3f(2,1,-4);
    glVertex3f(2,0,-4);
    glVertex3f(2,0,0);

    glEnd();

    //left rectangle

    glBegin(GL_POLYGON);

    glVertex3f(-2,1,0);
    glVertex3f(-2,1,-4);
    glVertex3f(-2,0,-4);
    glVertex3f(-2,0,0);

    glEnd();

    //top rectangle
    glBegin(GL_POLYGON);
    glColor3f(0.863, 0.078, 0.235);

    glVertex3f(-2,1,0);
    glVertex3f(2,1,0);
    glVertex3f(2,1,-4);
    glVertex3f(-2,1,-4);


    //bottom rectangle
    glBegin(GL_POLYGON);

    glVertex3f(-2,0,0);
    glVertex3f(2,0,0);
    glVertex3f(2,0,-4);
    glVertex3f(-2,0,-4);

    glEnd();

    ////////////top part of car////////////////////
    //front rectangle
    glBegin(GL_POLYGON);
    glColor3f(0.545, 0.000, 0.000);

    glVertex3f(-2,2,-1);
    glVertex3f(2,2,-1);
    glVertex3f(2,1,-1);
    glVertex3f(-2,1,-1);

    glEnd();

    //back rectangle

    glBegin(GL_POLYGON);

    glVertex3f(-2,2,-3.5);
    glVertex3f(2,2,-3.5);
    glVertex3f(2,1,-3.5);
    glVertex3f(-2,1,-3.5);

    glEnd();


    //right rectangle
    glBegin(GL_POLYGON);
    glColor3f(0.698, 0.133, 0.133);

    glVertex3f(2,2,-1);
    glVertex3f(2,2,-3.5);
    glVertex3f(2,1,-3.5);
    glVertex3f(2,1,-1);

    glEnd();

    //left rectangle

    glBegin(GL_POLYGON);

    glVertex3f(-2,2,-1);
    glVertex3f(-2,2,-3.5);
    glVertex3f(-2,1,-3.5);
    glVertex3f(-2,1,-1);

    glEnd();

    //top rectangle
    glBegin(GL_POLYGON);
    glColor3f(0.863, 0.078, 0.235);

    glVertex3f(-2,2,-1);
    glVertex3f(2,2,-1);
    glVertex3f(2,2,-3.5);
    glVertex3f(-2,2,-3.5);


    //bottom rectangle
    glBegin(GL_POLYGON);

    glVertex3f(-2,1,-1);
    glVertex3f(2,1,-1);
    glVertex3f(2,1,-3.5);
    glVertex3f(-2,1,-3.5);

    glEnd();

////////////wheels/////////////////////

    glColor3f(0.439, 0.502, 0.565);
    //back right tire
    glPushMatrix();
    //angle,Z,Y,X
    glTranslatef(-2,-0.3,-1);
    glRotatef(90,0,1,0);

    glutSolidTorus(0.2,0.3,100,100);

    glPopMatrix();

    //front right tire
    glPushMatrix();
    //angle,Z,Y,X
    glTranslatef(-2,-0.3,-3);
    glRotatef(90,0,1,0);

    glutSolidTorus(0.2,0.3,100,100);

    glPopMatrix();

    //back left tire
    glPushMatrix();
    //angle,Z,Y,X
    glTranslatef(2,-0.3,-1);
    glRotatef(90,0,1,0);

    glutSolidTorus(0.2,0.3,100,100);

    glPopMatrix();

    //front left tire
    glPushMatrix();
    //angle,Z,Y,X
    glTranslatef(2,-0.3,-3);
    glRotatef(90,0,1,0);

    glutSolidTorus(0.2,0.3,100,100);

    glPopMatrix();

    //////////backlights////////////////////////////

    //right red backlight
    glPushMatrix();
    glColor3f(0.647, 0.165, 0.165);

    glTranslatef(1.4,0.7,0.1);
    glRotatef(180,1,0,0);

    glutSolidCone(0.2,0.1,100,100);

    glPopMatrix();


    //left red backlight
    glPushMatrix();
    glColor3f(0.647, 0.165, 0.165);

    glTranslatef(-1.4,0.7,0.1);
    glRotatef(180,1,0,0);

    glutSolidCone(0.2,0.1,100,100);

    glPopMatrix();


    glPopMatrix();


}

//function to draw purple car
car2()
{
    glPushMatrix();
    glTranslatef(4,-7.5,yy+10);
    //glRotatef(270,0,1,0);


////////////bottom part of car////////////////////
    //front rectangle
    glBegin(GL_POLYGON);
    glColor3f(0.580, 0.000, 0.827);

    glVertex3f(-2,1,0);
    glVertex3f(2,1,0);
    glVertex3f(2,0,0);
    glVertex3f(-2,0,0);

    glEnd();

    //back rectangle

    glBegin(GL_POLYGON);

    glVertex3f(-2,1,-4);
    glVertex3f(2,1,-4);
    glVertex3f(2,0,-4);
    glVertex3f(-2,0,-4);

    glEnd();


    //right rectangle
    glBegin(GL_POLYGON);
    glColor3f( 	0.541, 0.169, 0.886);

    glVertex3f(2,1,0);
    glVertex3f(2,1,-4);
    glVertex3f(2,0,-4);
    glVertex3f(2,0,0);

    glEnd();

    //left rectangle

    glBegin(GL_POLYGON);

    glVertex3f(-2,1,0);
    glVertex3f(-2,1,-4);
    glVertex3f(-2,0,-4);
    glVertex3f(-2,0,0);

    glEnd();

    //top rectangle
    glBegin(GL_POLYGON);
    glColor3f(0.576, 0.439, 0.859);

    glVertex3f(-2,1,0);
    glVertex3f(2,1,0);
    glVertex3f(2,1,-4);
    glVertex3f(-2,1,-4);


    //bottom rectangle
    glBegin(GL_POLYGON);

    glVertex3f(-2,0,0);
    glVertex3f(2,0,0);
    glVertex3f(2,0,-4);
    glVertex3f(-2,0,-4);

    glEnd();

    ////////////top part of car////////////////////
    //front rectangle
    glBegin(GL_POLYGON);
    glColor3f(0.580, 0.000, 0.827);

    glVertex3f(-2,2,-1);
    glVertex3f(2,2,-1);
    glVertex3f(2,1,-1);
    glVertex3f(-2,1,-1);

    glEnd();

    //back rectangle

    glBegin(GL_POLYGON);

    glVertex3f(-2,2,-3.5);
    glVertex3f(2,2,-3.5);
    glVertex3f(2,1,-3.5);
    glVertex3f(-2,1,-3.5);

    glEnd();


    //right rectangle
    glBegin(GL_POLYGON);
    glColor3f(0.541, 0.169, 0.886);

    glVertex3f(2,2,-1);
    glVertex3f(2,2,-3.5);
    glVertex3f(2,1,-3.5);
    glVertex3f(2,1,-1);

    glEnd();

    //left rectangle

    glBegin(GL_POLYGON);

    glVertex3f(-2,2,-1);
    glVertex3f(-2,2,-3.5);
    glVertex3f(-2,1,-3.5);
    glVertex3f(-2,1,-1);

    glEnd();

    //top rectangle
    glBegin(GL_POLYGON);
    glColor3f(0.576, 0.439, 0.859);

    glVertex3f(-2,2,-1);
    glVertex3f(2,2,-1);
    glVertex3f(2,2,-3.5);
    glVertex3f(-2,2,-3.5);


    //bottom rectangle
    glBegin(GL_POLYGON);

    glVertex3f(-2,1,-1);
    glVertex3f(2,1,-1);
    glVertex3f(2,1,-3.5);
    glVertex3f(-2,1,-3.5);

    glEnd();

////////////wheels/////////////////////

    glColor3f(0.439, 0.502, 0.565);
    //back right tire
    glPushMatrix();
    //angle,Z,Y,X
    glTranslatef(-2,-0.3,-1);
    glRotatef(90,0,1,0);

    glutSolidTorus(0.2,0.3,100,100);

    glPopMatrix();

    //front right tire
    glPushMatrix();
    //angle,Z,Y,X
    glTranslatef(-2,-0.3,-3);
    glRotatef(90,0,1,0);

    glutSolidTorus(0.2,0.3,100,100);

    glPopMatrix();

    //back left tire
    glPushMatrix();
    //angle,Z,Y,X
    glTranslatef(2,-0.3,-1);
    glRotatef(90,0,1,0);

    glutSolidTorus(0.2,0.3,100,100);

    glPopMatrix();

    //front left tire
    glPushMatrix();
    //angle,Z,Y,X
    glTranslatef(2,-0.3,-3);
    glRotatef(90,0,1,0);

    glutSolidTorus(0.2,0.3,100,100);

    glPopMatrix();

    //////////backlights////////////////////////////

    //right red backlight
    glPushMatrix();
    glColor3f(0.647, 0.165, 0.165);

    glTranslatef(1.4,0.7,0.1);
    glRotatef(180,1,0,0);

    glutSolidCone(0.2,0.1,100,100);

    glPopMatrix();


    //left red backlight
    glPushMatrix();
    glColor3f(0.647, 0.165, 0.165);

    glTranslatef(-1.4,0.7,0.1);
    glRotatef(180,1,0,0);

    glutSolidCone(0.2,0.1,100,100);

    glPopMatrix();


    glPopMatrix();


}

void rock_cactus()
{

    //for loop to draw the same 3d cactus and rock multiple times
    for(int i=-25;i>=-100;i-=25){


////////////draws a rock/////////////////////////
    glColor3f(0.737, 0.561, 0.561);
    glPushMatrix();


    glTranslatef(-15,-10,i);
    glutSolidIcosahedron();

    glPopMatrix();

////////////draws a cactus by stacking same shape on top of each other/////////////////////////

    glColor3f(0.180, 0.545, 0.341);

    glPushMatrix();
    glTranslatef(-13,-8,i);
    glutSolidIcosahedron();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-13,-7,i);
    glutSolidIcosahedron();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-13,-6,i);
    glutSolidIcosahedron();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-13,-5,i);
    glutSolidIcosahedron();
    glPopMatrix();


    }

}


//draws a sphere to act as the background by being inside of it
void sky()
{
    glColor3f(0.000, 0.749, 1.000);
    glutSolidSphere(150,60,60);

}

//draws pyramids
void pyramids()
{
    glColor3f(1.000, 0.627, 0.478);

    glPushMatrix();
    glTranslatef(15,-5,-25);

    //bottom rectangle
    glBegin(GL_QUADS);

    glVertex3f(-5,0,-5);
    glVertex3f(5,0,-5);
    glVertex3f(5,0,5);
    glVertex3f(-5,0,5);
    glEnd();

    //front triangle
    glBegin(GL_POLYGON);

    glVertex3f(-5,0,5);
    glVertex3f(0,6,0);
    glVertex3f(5,0,5);
    glEnd();

    glColor3f(1.000, 0.855, 0.725);
    //left triangle
    glBegin(GL_POLYGON);

    glVertex3f(-5,0,-5);
    glVertex3f(0,6,0);
    glVertex3f(-5,0,5);
    glEnd();

    //back triangle
    glBegin(GL_POLYGON);

    glVertex3f(-5,0,-5);
    glVertex3f(0,6,0);
    glVertex3f(5,0,-5);
    glEnd();

    //right triangle
    glBegin(GL_POLYGON);

    glVertex3f(5,0,-5);
    glVertex3f(0,6,0);
    glVertex3f(5,0,5);
    glEnd();

    glPopMatrix();

}

//for keyUp function
void keyboard2(unsigned char Key, int x, int y)
{
        //stops playing audio of car when you stop using the W key
        PlaySound(NULL,0,0);


        if(Key=='w' || Key=='W')
        {
            //adds a slowing down animation for when you let go of the W key
            glutTimerFunc(0,anim,0);

            glutSwapBuffers();
        }

         if(Key=='i' || Key=='I')
        {
            //adds a slowing down animation for when you let go of the W key
            glutTimerFunc(0,anim2,0);

            glutSwapBuffers();
        }


}

//keydown function
void keyboard(unsigned char Key, int x, int y)
{
    //state==1 means that the game has started (state==0 means you're at the start menu)
    if(state==1)
    {
        //red car
        if(GetAsyncKeyState('W'))
        {
            //if condition to check if car is in view
            if(xx>=-100)
            {
                //decrement the the xx for animation
                xx-=1;
                //used for the slowing down animation
                slow_down1=100;
                //to play car sound
                PlaySound(TEXT("car.wav"),NULL,SND_FILENAME|SND_ASYNC|SND_NOSTOP);
            }
            //when car has reached the end or finished a lap
            else
            {
                //resets the car location to add the long distance effect
                xx=-1;
                //increments lap, game is based on 3 laps
                lap++;
            }

        }

        //purple car
        if(GetAsyncKeyState('I'))
        {
            //if condition to check if car is in view
            if(yy>=-100)
            {
                //decrement the the yy for animation
                yy-=1;
                //used for the slowing down animation
                slow_down2=100;
                //to play car sound
                PlaySound(TEXT("car.wav"),NULL,SND_FILENAME|SND_ASYNC|SND_NOSTOP);
            }
            //when car has reached the end or finished a lap
            else
            {
                //resets the car location to add the long distance effect
                yy=-1;
                //increments lap, game is based on 3 laps
                lap2++;

            }
            }


    }
    //main menu state
    else if(state==0)
    {
        //start game by changing display when clicking M
        if(GetAsyncKeyState('M')){glutDisplayFunc(display);state=1;}
        //exits game when X is clicked
        if(GetAsyncKeyState('X')){exit(0);}
    }
    //when player finishes the game and sees the result, he's prompted with
    //an option to exit the game
    else
    {
        //when X is clicked, the game is closed
        if(GetAsyncKeyState('X')){exit(0);}
    }

    glutPostRedisplay();

}

//initialize
void init(){
    glClearColor(0,0,0,0);
    glEnable(GL_DEPTH_TEST);
}
void reshape(int,int);

//draws the stoplight
void realStopLight()
{

    glPushMatrix();
    glTranslatef(-5.5,-7.5,-9);
    glRotatef(45,0,1,0);

    glBegin(GL_QUADS);

    //bottom rectangle
    glColor3f(0,0,0);

    glVertex3f(-0.5,0,-8);
    glVertex3f(0.5,0,-8);
    glVertex3f(0.5,0,-7);
    glVertex3f(-0.5,0,-7);
    glEnd();


    glBegin(GL_POLYGON);
    glColor3f(0.412, 0.412, 0.412);

    //front  rectangle
    glVertex3f(-0.5,0,-7);
    glVertex3f(0.5,0,-7);
    glVertex3f(0.5,10,-7);
    glVertex3f(-0.5,10,-7);

    glEnd();

    glBegin(GL_POLYGON);

    //right rectangle
    glColor3f(0.502, 0.502, 0.502);

    glVertex3f(0.5,0,-7);
    glVertex3f(0.5,0,-8);
    glVertex3f(0.5,10,-8);
    glVertex3f(0.5,10,-7);
    glEnd();

        glBegin(GL_POLYGON);

    //left rectangle
    glColor3f(0.502, 0.502, 0.502);

    glVertex3f(-0.5,0,-7);
    glVertex3f(-0.5,0,-8);
    glVertex3f(-0.5,10,-8);
    glVertex3f(-0.5,10,-7);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0.412, 0.412, 0.412);

    //back rectangle
    glVertex3f(-0.5,0,-8);
    glVertex3f(0.5,0,-8);
    glVertex3f(0.5,10,-8);
    glVertex3f(-0.5,10,-8);

    glEnd();


    glBegin(GL_POLYGON);

    //top rectangle
    glColor3f(0.412, 0.412, 0.412);

    glVertex3f(-0.5,10,-8);
    glVertex3f(0.5,10,-8);
    glVertex3f(0.5,10,-7);
    glVertex3f(-0.5,10,-7);
    glEnd();


    //right top line
    glBegin(GL_POLYGON);

    glColor3f(0.412, 0.412, 0.412);

    glVertex3f(0.5,8.5,-7.5);
    glVertex3f(2,8.5,-7.5);
    glVertex3f(2,8,-7.5);
    glVertex3f(0.5,8,-7.5);
    glEnd();

    //right red light
    glPushMatrix();

    //check if flag is 0 or to change colors to animate countdown stoplight
    if(color_red==0){glColor3f(0.863, 0.078, 0.235);}
    else{glColor3f(1, 0, 0);}

    glTranslatef(1.75,8.25,-7.45);
    glRotatef(180,1,0,0);

    glutSolidCone(0.5,0.1,100,100);

    glPopMatrix();



    //left top line
    glBegin(GL_POLYGON);

    glColor3f(0.412, 0.412, 0.412);

    glVertex3f(-0.5,8.5,-7.5);
    glVertex3f(-2,8.5,-7.5);
    glVertex3f(-2,8,-7.5);
    glVertex3f(-0.5,8,-7.5);
    glEnd();

    //left red light
    glPushMatrix();
    //check if flag is 0 or to change colors to animate countdown stoplight
    if(color_red==0){glColor3f(0.863, 0.078, 0.235);}
    else{glColor3f(1, 0, 0);}

    glTranslatef(-1.75,8.25,-7.45);
    glRotatef(180,1,0,0);

    glutSolidCone(0.5,0.1,100,100);

    glPopMatrix();

///////////////middle line/////////////////
    //right middle line
    glBegin(GL_POLYGON);

    glColor3f(0.412, 0.412, 0.412);

    glVertex3f(0.5,6.5,-7.5);
    glVertex3f(2,6.5,-7.5);
    glVertex3f(2,6,-7.5);
    glVertex3f(0.5,6,-7.5);
    glEnd();

    //right yellow light
    glPushMatrix();
    //check if flag is 0 or to change colors to animate countdown stoplight
    if(color_yellow==0){glColor3f(1.000, 0.549, 0.000);}
    else{glColor3f(1.000, 1.000, 0.000);}

    glTranslatef(1.75,6.25,-7.45);
    glRotatef(180,1,0,0);

    glutSolidCone(0.5,0.1,100,100);

    glPopMatrix();



    //left middle line
    glBegin(GL_POLYGON);

    glColor3f(0.412, 0.412, 0.412);

    glVertex3f(-0.5,6.5,-7.5);
    glVertex3f(-2,6.5,-7.5);
    glVertex3f(-2,6,-7.5);
    glVertex3f(-0.5,6,-7.5);
    glEnd();

    //left yellow light
    glPushMatrix();
    //check if flag is 0 or to change colors to animate countdown stoplight
    if(color_yellow==0){glColor3f(1.000, 0.549, 0.000);}
    else{glColor3f(1.000, 1.000, 0.000);}

    glTranslatef(-1.75,6.25,-7.45);
    glRotatef(180,1,0,0);

    glutSolidCone(0.5,0.1,100,100);

    glPopMatrix();



    ///////////////bottom line/////////////////
    //right bottom
    glBegin(GL_POLYGON);

    glColor3f(0.412, 0.412, 0.412);

    glVertex3f(0.5,4.5,-7.5);
    glVertex3f(2,4.5,-7.5);
    glVertex3f(2,4,-7.5);
    glVertex3f(0.5,4,-7.5);
    glEnd();

    //right green light
    glPushMatrix();
    //check if flag is 0 or to change colors to animate countdown stoplight
    if(color_green==0){glColor3f(0.000, 0.502, 0.000);}
    else{glColor3f(0.000, 1.000, 0.000);}

    glTranslatef(1.75,4.25,-7.45);
    glRotatef(180,1,0,0);

    glutSolidCone(0.5,0.1,100,100);

    glPopMatrix();



    //left bottom line
    glBegin(GL_POLYGON);

    glColor3f(0.412, 0.412, 0.412);

    glVertex3f(-0.5,4.5,-7.5);
    glVertex3f(-2,4.5,-7.5);
    glVertex3f(-2,4,-7.5);
    glVertex3f(-0.5,4,-7.5);
    glEnd();

    //left green light
    glPushMatrix();
    //check if flag is 0 or to change colors to animate countdown stoplight
    if(color_green==0){glColor3f(0.000, 0.502, 0.000);}
    else{glColor3f(0.000, 1.000, 0.000);}

    glTranslatef(-1.75,4.25,-7.45);
    glRotatef(180,1,0,0);

    glutSolidCone(0.5,0.1,100,100);

    glPopMatrix();

    glPopMatrix();


}


lap_scores()
{
    //checks if any of the cars are still racing
    if(lap<=3 && lap2<=3){
        char plr1[64]="Red's Lap: ";
        char plr2[64]="Purples's Lap: ";
        char integer_string1[10];
        char integer_string2[10];


        //used to change the integer array to string array
        sprintf(integer_string1, "%d", lap);
        sprintf(integer_string2, "%d", lap2);


        //adds the value of lap to either plr1/plr2
        strcat(plr1, integer_string1);
        strcat(plr1, "/3");

        //adds the value of lap to either plr1/plr2
        strcat(plr2, integer_string2);
        strcat(plr2, "/3");


        //used to print text
        glColor3f(1,0,0);
        glRasterPos3f(-6,6,-10);
        for(int i=0;i<strlen(plr1);i++){glutBitmapCharacter(GLUT_BITMAP_9_BY_15,plr1[i]);}

        //used to print text
        glColor3f(0.502, 0.000, 0.502);
        glRasterPos3f(6,6,-10);
        for(int i=0;i<strlen(plr2);i++){glutBitmapCharacter(GLUT_BITMAP_9_BY_15,plr2[i]);}
    }
    //one of the cars has won
    else
        {
            //stops car audio
            PlaySound(NULL,0,0);
            //plays victory audio
            PlaySound(TEXT("victory.wav"),NULL,SND_FILENAME|SND_ASYNC);
            //delay 2 seconds
            Sleep(2000);
            //shows the winner in a new display
            glutDisplayFunc(winDisplay);

            //state 2 is for winner's page
            state=2;

            glutSwapBuffers();


        }


}


int main (int argc, char** argv) {
glutInit(&argc,argv);
glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH);

glutInitWindowPosition(200,0);
glutInitWindowSize(1200,800);
glutCreateWindow("19100499, 19101168, 19100369");


glutDisplayFunc(welcomeDisplay);
glutReshapeFunc(reshape);
glutKeyboardUpFunc(keyboard2);
glutKeyboardFunc(keyboard);
glutTimerFunc(0,cloudAnim,0);


init();

glutMainLoop();


return 0;


}


void clouds()
{
    glPushMatrix();
    glTranslatef(2,14,cloudz1);
    glRotatef(90,0,0,1);

    glPushMatrix();
    glColor3f( 	0.902, 0.902, 0.980);
    glTranslatef(0,10,-40);

    glutSolidSphere(4,100,100);

    glPopMatrix();

    glPushMatrix();
    glColor3f( 	0.902, 0.902, 0.980);
    glTranslatef(2,14,-40);

    glutSolidSphere(5,100,100);

    glPopMatrix();

    glPushMatrix();
    glColor3f(0.902, 0.902, 0.980);
    glTranslatef(0,18,-40);

    glutSolidSphere(4,100,100);

    glPopMatrix();
    glPopMatrix();

////////////////////////////////////////////

    glPushMatrix();
    glTranslatef(25,14,cloudz2);
    glRotatef(90,0,0,1);

    glPushMatrix();
    glColor3f( 	0.902, 0.902, 0.980);
    glTranslatef(0,10,-40);

    glutSolidSphere(4,100,100);

    glPopMatrix();

    glPushMatrix();
    glColor3f( 	0.902, 0.902, 0.980);
    glTranslatef(2,14,-40);

    glutSolidSphere(5,100,100);

    glPopMatrix();

    glPushMatrix();
    glColor3f( 	0.902, 0.902, 0.980);
    glTranslatef(0,18,-40);

    glutSolidSphere(4,100,100);

    glPopMatrix();
    glPopMatrix();



}

void cloudAnim(int)
{
    glutTimerFunc(1000/60,cloudAnim,0);
    glutPostRedisplay();

    cloudz1+=0.5;cloudz2+=0.5;

    if(cloudz1==70){cloudz1=-120;}
    if(cloudz2==70){cloudz2=-160;}

}

void display(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLoadIdentity();

    glutTimerFunc(0,animStopLight,0);


    clouds();

    road();
    leftSand();
    rightSand();

    sky();

    pyramids();

    //to move the pyramid
    glPushMatrix();
    glTranslatef(15,-5,-70);
    pyramids();
    glPopMatrix();

    //to move the pyramid
    glPushMatrix();
    glTranslatef(6,-8,0);
    pyramids();
    glPopMatrix();




    lap_scores();

    realStopLight();


    rock_cactus();

    car1();
    car2();


    finish_sign();

    //checks who reached the end AND lap 3
    //winner=0 --> RED CAR
    //winner=1 --> PURPLE CAR
    if(lap==3 && xx<=-100){winner=0;}
    if(lap2==3 && yy<=-100){winner=1;}


    glFlush();
}


void reshape(int w, int h ){
    glViewport(0,0,(GLsizei)w,(GLsizei)h);

    glMatrixMode(GL_PROJECTION);

    glLoadIdentity();

    gluPerspective(75,(GLdouble)w / (GLdouble)h,5,150);



    glMatrixMode(GL_MODELVIEW);
}

//slowing down animation for red car
void anim(int)
{

    if(slow_down1>=0)
        {
        glutTimerFunc(1000/120,anim,0);
        glutPostRedisplay();

        //decrement to move car slights as if it's slowing
        xx-=0.09;
        //decrement the variable so we can use it to check in the above if condition
        slow_down1--;
        }
}
//slow down animation for purple car
void anim2(int)
{
    if(slow_down2>=0)
        {
        glutTimerFunc(1000/120,anim2,0);
        glutPostRedisplay();
        //decrement to move car slights as if it's slowing
        yy-=0.09;
        //decrement the variable so we can use it to check in the above if condition
        slow_down2--;
        }
}

//changes colors of stoplight animation
void animStopLight(int)
{
//checks if the step is either red,green, or yellow
    if(step_animLight<=3)
    {
        glutTimerFunc(1000/60,animStopLight,0);
        glutPostRedisplay();

        //all these if conditions turns on the needed color while delaying and playing an audio
        if(step_animLight==0){PlaySound(TEXT("count_down_stopped.wav"),NULL, SND_FILENAME || SND_ASYNC);step_animLight++;}
        else if(step_animLight==1){Sleep(1000);color_red=0;color_yellow=1;color_green=0;step_animLight++;}
        else if(step_animLight==2){PlaySound(TEXT("count_down_stopped.wav"),NULL, SND_FILENAME || SND_ASYNC);Sleep(1000);color_red=0;color_yellow=0;color_green=1;PlaySound(TEXT("count_go.wav"),NULL, SND_FILENAME || SND_SYNC);step_animLight++;}


    }



}



