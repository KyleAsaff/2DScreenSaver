
/************************************************************************************

    File:           assignment1_kyleasaff.c
    
    Description:    Assignment 1 for CSCI 3161

    Author:         Kyle Asaff
    Banner ID:      B00562352
    CS ID:          asaff

*************************************************************************************/


/* include the library header files */
#include <windows.h>   
#include <gl/Gl.h>
#include <gl/freeglut.h>
#include <assert.h>
#include <stdio.h>
#include <math.h>

/************************************************************************

    Speed Variables to adjust the speeds of the interp values

 ***CHANGE THESE IF YOU NEED THE ANIMATIONS TO SLOW DOWN OR SPEED UP***

   
    
*************************************************************************/

float interpSpeed = 1.00;
float rotationSpeed = 1.00;

/************************************************************************

    Global Variables

   
    
*************************************************************************/

// Interp values for the speeds of the morphing, sparkle, and sparks
GLfloat interp = 0.0;
GLfloat interpSparkle = 0.0;
GLfloat interpSparkle_2 = 0.0;
GLfloat interpSparkle_3 = 0.0;
GLfloat interpSparkle_4 = 0.0;
GLfloat interpSparkle_5 = 0.0;
GLfloat interpSparkle_6 = 0.0;
GLfloat interpSparkle_7 = 0.0;
GLfloat interpSparkle_8 = 0.0;
GLfloat theta = 0.0;
GLfloat interpTrace = 0.0;
GLfloat interpTranslation = 0.0;
int count = 0;
int interpTranslationCountUP = 1;
int interpCountUP = 1;
float translate = 0;

// Random variables for the spark speeds, colors, and direction
float randomColor1;
float randomColor2;
float randomColor3;
float randomX;
float randomY;
int spark = 0;


float randomColor1_2;
float randomColor2_2;
float randomColor3_2;
float randomX_2;
float randomY_2;
int spark_2 = 0;

float randomColor1_3;
float randomColor2_3;
float randomColor3_3;
float randomX_3;
float randomY_3;
int spark_3 = 0;

float randomColor1_4;
float randomColor2_4;
float randomColor3_4;
float randomX_4;
float randomY_4;
int spark_4 = 0;

float randomColor1_5;
float randomColor2_5;
float randomColor3_5;
float randomX_5;
float randomY_5;
int spark_5 = 0;

float randomColor1_6;
float randomColor2_6;
float randomColor3_6;
float randomX_6;
float randomY_6;
int spark_6 = 0;

float randomColor1_7;
float randomColor2_7;
float randomColor3_7;
float randomX_7;
float randomY_7;
int spark_7 = 0;

float randomColor1_8;
float randomColor2_8;
float randomColor3_8;
float randomX_8;
float randomY_8;
int spark_8 = 0;


// The x and y cordinates for the letter K
float xcoordK[] =    {120, 120, 200, 200, 120, 200, 200, 260, 340, 340, 380, 260,260,380,300,300,260,200,200, 200,120,120,200,120,120,200,200,200,200,260};
float ycoordK[] =    {140, 40,  40,  40,  140, 140, 140, 190, 40,  40,  100, 190,190,340,340,340,190,240,240, 340,340,340,240,140,140,240,140,140,240,190};

// The x and y cordinates for the morphing star
float xcoordStar[] = {120, 80,  180, 180, 260, 260, 260, 260, 340, 340, 440, 360,360,440,260,260,160,160,160, 80, 160,160 ,180,120,180,160,340,340,160,360};
float ycoordStar[] = {180, 120, 120, 120, 120, 20,  20, 120, 120, 120, 120,  240,240,360,240,240,240,310,310,  360,240,240,120,180,120,240,120,120,240,240};

// Holds the x and y cordinates for the sparkle midpoint
GLfloat xcoordSparkle[] = {0};
GLfloat ycoordSparkle[] = {0};

// Holds values to check if a button is clicked, 0 = off -> 1 = on
int sparkleON = 0;
int sparksON = 0;
int morphON = 0;
int bonusON = 0;



// Mouse structure to represent the user's mouse
struct mouse
{
    float xcoord;
    float ycoord;
    float leftclick;
    float xpress;
    float ypress;
};

// Button structure to represent the buttons in the UI
typedef void (*buttonPressed)();
struct button
{
    int id;       // button id 
    float xcoord;  // button x coord 
    float ycoord;  // button y coord 
    float height;   // button height
    float width;    // button width
    float status;   // 1 = the botton is clicked, 0 = button is not clicked
    char* name;    // the name of the button */
    buttonPressed buttonPressed;
    struct button* next; // pointer data for the next node in the link listed
};


struct mouse userMouse;

typedef struct button button;

//Set the buttonList to NULL
button* buttonList = NULL;

// Initate pointer reference for the button linked list
int reference=0;


/************************************************************************

    Function:      CreateButton

    Description:    Inializes the creation of each button in the linked list

*************************************************************************/
int CreateButton(char *name,buttonPressed callbackfunc,float xcoord,float ycoord,float height,float width)
{
    button* p = (button*)malloc(sizeof(button));
    assert(p);
    memset(p,0,sizeof(button));
    p->xcoord = xcoord; // button xcoord 
    p->ycoord = ycoord; // button ycoord 
    p->height = height; // the height of the button
    p->width = width; // the width of the button
    p->name = (char*)malloc( strlen(name)+1 ); // the name of the button 
    if(p->name)
        sprintf(p->name,name);
    p->next = buttonList; // pointer to the next button in the linked list
    p->buttonPressed = callbackfunc; // the call back function
    buttonList = p;
    return p->id = ++reference;
}

/************************************************************************

    Function:      isButtonPressed

    Description:    Return if pressed

*************************************************************************/
static void isButtonPressed()
{
    printf("pressed");
}

/************************************************************************

    Function:      Font

    Description:   Prints out font using the built in bitmap

*************************************************************************/
void Font(void *font,char *txt,float xcoord,float ycoord)
{
    glRasterPos2i(xcoord, ycoord);
    while(*txt != '\0' )
    {
        glutBitmapCharacter(font, *txt);
        ++txt;
    }
}

/************************************************************************

    Function:       ButtonDraw

    Description:    Draws the button in the window and also checks the status
                    of the buttons

*************************************************************************/
void ButtonDraw()
{
    float fontx;
    float fonty;

    button* b = buttonList;

    while(b) 
    {
        // Color the buttons and change color if the button is clicked
        if(b->status)
            glColor3f(0.63,0.63,0.63);
        else
            glColor3f(0.60,0.60,0.60);

        // use GL_QUADS to draw the background of the button
        glBegin(GL_QUADS);
            glVertex2i( b->xcoord, b->ycoord);
            glVertex2i( b->xcoord, b->ycoord+b->height);
            glVertex2i( b->xcoord+b->width, b->ycoord+b->height);
            glVertex2i( b->xcoord+b->width, b->ycoord);
        glEnd();

        glLineWidth(2);


        // Change the color of the outline of the button when clicked

        if (b->status)
            glColor3f(0.41,0.41,0.41);
        else 
            glColor3f(0.81,0.81,0.81);

        glBegin(GL_LINE_STRIP);
            glVertex2i( b->xcoord+b->width, b->ycoord);
            glVertex2i( b->xcoord, b->ycoord);
            glVertex2i( b->xcoord, b->ycoord+b->height);
        glEnd();

    
        // Change the color of the outline of the button when clicked
        if (b->status) 
            glColor3f(0.81,0.81,0.81);
        else 
            glColor3f(0.41,0.41,0.41);


        glBegin(GL_LINE_STRIP);
            glVertex2i( b->xcoord, b->ycoord+b->height);
            glVertex2i( b->xcoord+b->width, b->ycoord+b->height);
            glVertex2i( b->xcoord+b->width, b->ycoord);
        glEnd();

        glLineWidth(1);

        // Calculate the center to inset text around
        fontx = b->xcoord + (b->width - glutBitmapLength(GLUT_BITMAP_HELVETICA_18,b->name)) / 2 ;
        fonty = b->ycoord + (b->height+10)/2;

        // Pop the font up or down depending if the button has been clicked
        if (b->status) {
            fontx+=2;
            fonty+=2;
        }

        // Color and insert the text for the buttons
        glColor3f(0,0,0);
        Font(GLUT_BITMAP_HELVETICA_18,b->name,fontx,fonty);

        // If a button is clicked, mark that it is clicked in a global variable
        if(b->status && b->id==1)
            sparkleON = 1;
        // Turn off sparks when sparkle gets turned off
        else if(b->status && !sparkleON && b->id==2)
            b->status = 0;
        else if(!b->status && b->id==1)
            sparkleON = 0;
        else if(b->status && b->id==2)
            sparksON = 1;
        else if(!b->status && b->id==2)
            sparksON = 0;
        else if(b->status && b->id==3)
            morphON = 1;
        else if(!b->status && b->id==3)
            morphON = 0;
        else if(b->status && b->id==4)
            bonusON = 1;
        else if(!b->status && b->id==4)
            bonusON = 0;

        // A call to the functions method that performs the tasks of the different buttons
        functions();

        // Check the next button in the linked list
        b = b->next;
    }
        
}


/************************************************************************

    Function:      buttonPress

    Description:    Changes the status of a button to click if a click has 
                    happend within the area

*************************************************************************/
void buttonPress(int xcoord,int ycoord)
{
    button* b = buttonList;
    while(b) 
    {
        // DO NOT let sparks be turned on without sparkle turned on
        if(testButton(b,xcoord,ycoord) && b->id == 2 && !sparkleON)
            b->status = 0;
        else if(testButton(b,xcoord,ycoord) && b->id == 1 && sparksON) {
            sparksON = 0;
            b->status = 0;
        }
        // IF a click happens within the area, set true -> else false  
        else if( testButton(b,xcoord,ycoord) && b->status == 0)
        {
            b->status = 1;
        }
        else if (testButton(b,xcoord,ycoord) && b->status == 1)
        {
            b->status = 0;
        }
        b=b->next;
    }
}

/************************************************************************

    Function:      testButton

    Description:    Checks if a mouse click has happend within the area of a 
                    button

*************************************************************************/
int testButton(button* b,int x,int y) 
{
    if(b) 
    {
        // If button clicks happens within the area of a button, return true
        if( x > b->xcoord && x < b->xcoord+b->width && y > b->ycoord && y < b->ycoord+b->height ) {
            return 1;
        }
    }
    // If not, return false
    return 0;
}


/************************************************************************

    Function:      MouseButton

    Description:    Keeps track of where a mouse click has happened

*************************************************************************/
void MouseButton(int button,int state,int x, int y)
{
    // Change mouse position
    userMouse.xcoord = x;
    userMouse.ycoord = y;

    // If mouse has been clicked
    if (state == GLUT_DOWN) 
    {
    // Hold cordinates where the mouse has been clicked
            userMouse.xpress = x;
            userMouse.ypress = y;

    // Check if left button has been clicked
        switch(button) 
        {
        case GLUT_LEFT_BUTTON:
            userMouse.leftclick = 1;
            buttonPress(x,y);
        }
    }

    glutPostRedisplay();
}

/************************************************************************

    Function:      randomNumber

    Description:    Generates a random float number between 0.0 and a given max

*************************************************************************/

float randomNumber(float max) {
    float x = ((float)rand()/(float)(RAND_MAX)) * max;
    return x;
}

/************************************************************************

    Function:      myIdle

    Description:    The Idle function to update the interp values

*************************************************************************/

void myIdle(void)
{
    // Hold the speeds for the interpolations
    interpSparkle += (0.0003*interpSpeed);
    interpSparkle_2 += (0.0003*interpSpeed);
    interpSparkle_3 += (0.0005*interpSpeed);
    interpSparkle_4 += (0.0005*interpSpeed);
    interpSparkle_5 += (0.0007*interpSpeed);
    interpSparkle_6 += (0.0007*interpSpeed);
    interpSparkle_7 += (0.0009*interpSpeed);
    interpSparkle_8 += (0.0009*interpSpeed);
    interpTrace += (0.0001*interpSpeed);
    theta += (0.1*rotationSpeed);

    // Don't morph K if morph isn't on
    if (!morphON)
        interp = 0.0;
    else if(interpCountUP == 1)
        interp += (0.0001*interpSpeed);
    else if(interpCountUP == 0)
        interp -= (0.0001*interpSpeed);
    if(interp >= 1.0 && interpCountUP == 1) {
        interp = 0.9999;
        interpCountUP = 0;
    }
    else if(interp <= 0.0 && interpCountUP == 0) {
        interp = 0.0001;
        interpCountUP = 1;
    }

    // Dont't translate the K if bonus isn't on
    if(!bonusON)
        interpTranslation = 0.0;
    else if(interpTranslationCountUP == 1)
        interpTranslation += (0.0001*interpSpeed);
    else if(interpTranslationCountUP == 0)
        interpTranslation -= (0.0001*interpSpeed);
    if(interpTranslation >= 1.0 && interpTranslationCountUP == 1) {
        interpTranslation = 0.9999;
        interpTranslationCountUP = 0;
    }
    else if(interpTranslation <= -1.0 && interpTranslationCountUP == 0) {
        interpTranslation = -0.9999;
        interpTranslationCountUP = 1;
    }

    // Generate random speeds, colors, and directions for the sparks
    if(interpSparkle >= 1.0) {
        randomColor1 = randomNumber(1.0);
        randomColor2 = randomNumber(1.0);
        randomColor3 = randomNumber(1.0);
        randomX =  (((rand() % 1000)+ 500) * ((rand() % 3) - 1));
        randomY =  (((rand() % 1000)+ 500) * ((rand() % 3) - 1));
        spark = rand() % 2;
        interpSparkle = 0.0;
    }
        if(interpSparkle_2 >= 1.0) {
         randomColor1_2 = randomNumber(1.0);
         randomColor2_2 = randomNumber(1.0);
         randomColor3_2 = randomNumber(1.0);
         randomX_2 =  (((rand() % 1000)+ 500) * ((rand() % 3) - 1));
         randomY_2 =  (((rand() % 1000)+ 500) * ((rand() % 3) - 1));
        spark_2 = rand() % 2;
        interpSparkle_2 = 0.0;
    }
        if(interpSparkle_3 >= 1.0) {
         randomColor1_3 = randomNumber(1.0);
         randomColor2_3 = randomNumber(1.0);
         randomColor3_3 = randomNumber(1.0);
         randomX_3 =  (((rand() % 1000)+ 500) * ((rand() % 3) - 1));
         randomY_3 =  (((rand() % 1000)+ 500) * ((rand() % 3) - 1));
        spark_3 = rand() % 2;
        interpSparkle_3 = 0.0;
    }
        if(interpSparkle_4 >= 1.0) {
         randomColor1_4 = randomNumber(1.0);
         randomColor2_4 = randomNumber(1.0);
         randomColor3_4 = randomNumber(1.0);
         randomX_4 =  (((rand() % 1000)+ 500) * ((rand() % 3) - 1));
         randomY_4 =  (((rand() % 1000)+ 500) * ((rand() % 3) - 1));
        spark_4 = rand() % 2;
        interpSparkle_4 = 0.0;
    }
        if(interpSparkle_5 >= 1.0) {
         randomColor1_5 = randomNumber(1.0);
         randomColor2_5 = randomNumber(1.0);
         randomColor3_5 = randomNumber(1.0);
         randomX_5 =  (((rand() % 1000)+ 500) * ((rand() % 3) - 1));
         randomY_5 =  (((rand() % 1000)+ 500) * ((rand() % 3) - 1));
        spark_5 = rand() % 2;
        interpSparkle_5 = 0.0;
    }
        if(interpSparkle_6 >= 1.0) {
         randomColor1_6 = randomNumber(1.0);
         randomColor2_6 = randomNumber(1.0);
         randomColor3_6 = randomNumber(1.0);
         randomX_6 =  (((rand() % 1000)+ 500) * ((rand() % 3) - 1));
         randomY_6 =  (((rand() % 1000)+ 500) * ((rand() % 3) - 1));
        spark_6 = rand() % 2;
        interpSparkle_6 = 0.0;
    }
        if(interpSparkle_7 >= 1.0) {
         randomColor1_7 = randomNumber(1.0);
         randomColor2_7 = randomNumber(1.0);
         randomColor3_7 = randomNumber(1.0);
         randomX_7 =  (((rand() % 1000)+ 500) * ((rand() % 3) - 1));
         randomY_7 =  (((rand() % 1000)+ 500) * ((rand() % 3) - 1));
        spark_7 = rand() % 2;
        interpSparkle_7 = 0.0;
    }
        if(interpSparkle_8 >= 1.0) {
         randomColor1_8 = randomNumber(1.0);
         randomColor2_8 = randomNumber(1.0);
         randomColor3_8 = randomNumber(1.0);
         randomX_8 =  (((rand() % 1000)+ 500) * ((rand() % 3) - 1));
         randomY_8 =  (((rand() % 1000)+ 500) * ((rand() % 3) - 1));
        spark_8 = rand() % 2;
        interpSparkle_8 = 0.0;
    }

    // Hold the order of which the star or K should be traced
    if (interpTrace >= 1.0 && count == 11) {
        interpTrace = 0.0;
        count=0;
    }
    else if (interpTrace >= 1.0) {
        interpTrace = 0.0;
        count++;
    }
    // Rotation for the sparkle
    if (theta >= 360.0) 
        theta -= (360.0*rotationSpeed);

    glutPostRedisplay();
};

/************************************************************************

    Function:      functions

    Description:    Holds all the functions for the buttons

*************************************************************************/
void functions(void)
{
    // Generate rainbow colors and translate the shape back and forth if bonus is on
    if(bonusON) {
        glPushMatrix();
        glTranslatef((GLfloat)((1-interpTranslation)*0 + (interpTranslation)*80), (GLfloat)((1-interpTranslation)*0 + (interpTranslation)*0), 0);
        glBegin(GL_TRIANGLES);
        glColor3f(randomNumber(1), randomNumber(1), randomNumber(1));
        translate = (GLfloat)((1-interpTranslation)*0 + (interpTranslation)*80);
    }
    // If bonus is not on don't translate or generate rainbow colors
    else {
        glPushMatrix();
        glBegin(GL_TRIANGLES);
        glColor3f(0.4,0.698,1);
        translate = 0;
        }
    int i;
    // For loop to draw the K or the star depending if the morph button is clicked
    for(i = 0; i<30; i++) {
        glVertex2f((GLfloat)((1-interp)*xcoordK[i] + (interp)*xcoordStar[i]), (GLfloat)((1-interp)*ycoordK[i] + (interp)*ycoordStar[i]));
    }
    glEnd();
    glPopMatrix();

    // Trace the interpolating path of the K or star with a sparkle if the button is checked
    if(sparkleON == 1) {
        if(count == 0) {
            xcoordSparkle[0] = (GLfloat) ((1-interpTrace)*((1-interp)*xcoordK[0] + (interp)*xcoordStar[0])) + (interpTrace*((1-interp)*xcoordK[1] + (interp)*xcoordStar[1]))+translate;
            ycoordSparkle[0] = (GLfloat) ((1-interpTrace)*(((1-interp)*ycoordK[0] + (interp)*ycoordStar[0]))) + (interpTrace*(((1-interp)*ycoordK[1] + (interp)*ycoordStar[1])));
        }
        if(count == 1) {
            xcoordSparkle[0] = (GLfloat) ((1-interpTrace)*((1-interp)*xcoordK[1] + (interp)*xcoordStar[1])) + (interpTrace*((1-interp)*xcoordK[2] + (interp)*xcoordStar[2]))+translate;
            ycoordSparkle[0] = (GLfloat) ((1-interpTrace)*(((1-interp)*ycoordK[1] + (interp)*ycoordStar[1]))) + (interpTrace*(((1-interp)*ycoordK[2] + (interp)*ycoordStar[2])));
        }
        if(count == 2) {
            xcoordSparkle[0] = (GLfloat) ((1-interpTrace)*((1-interp)*xcoordK[3] + (interp)*xcoordStar[3])) + (interpTrace*((1-interp)*xcoordK[5] + (interp)*xcoordStar[5]))+translate;
            ycoordSparkle[0] = (GLfloat) ((1-interpTrace)*(((1-interp)*ycoordK[3] + (interp)*ycoordStar[3]))) + (interpTrace*(((1-interp)*ycoordK[5] + (interp)*ycoordStar[5])));
        }
        if(count == 3) {
            xcoordSparkle[0] = (GLfloat) ((1-interpTrace)*((1-interp)*xcoordK[6] + (interp)*xcoordStar[6])) + (interpTrace*((1-interp)*xcoordK[8] + (interp)*xcoordStar[8]))+translate;
            ycoordSparkle[0] = (GLfloat) ((1-interpTrace)*(((1-interp)*ycoordK[6] + (interp)*ycoordStar[6]))) + (interpTrace*(((1-interp)*ycoordK[8] + (interp)*ycoordStar[8])));
        }
        if(count == 4) {
            xcoordSparkle[0] = (GLfloat) ((1-interpTrace)*((1-interp)*xcoordK[9] + (interp)*xcoordStar[9])) + (interpTrace*((1-interp)*xcoordK[10] + (interp)*xcoordStar[10]))+translate;
            ycoordSparkle[0] = (GLfloat) ((1-interpTrace)*(((1-interp)*ycoordK[9] + (interp)*ycoordStar[9]))) + (interpTrace*(((1-interp)*ycoordK[10] + (interp)*ycoordStar[10])));
        }
        if(count == 5) {
            xcoordSparkle[0] = (GLfloat) ((1-interpTrace)*((1-interp)*xcoordK[10] + (interp)*xcoordStar[10])) + (interpTrace*((1-interp)*xcoordK[11] + (interp)*xcoordStar[11]))+translate;
            ycoordSparkle[0] = (GLfloat) ((1-interpTrace)*(((1-interp)*ycoordK[10] + (interp)*ycoordStar[10]))) + (interpTrace*(((1-interp)*ycoordK[11] + (interp)*ycoordStar[11])));
        }
        if(count == 6) {
            xcoordSparkle[0] = (GLfloat) ((1-interpTrace)*((1-interp)*xcoordK[12] + (interp)*xcoordStar[12])) + (interpTrace*((1-interp)*xcoordK[13] + (interp)*xcoordStar[13]))+translate;
            ycoordSparkle[0] = (GLfloat) ((1-interpTrace)*(((1-interp)*ycoordK[12] + (interp)*ycoordStar[12]))) + (interpTrace*(((1-interp)*ycoordK[13] + (interp)*ycoordStar[13])));
        }
        if(count == 7) {
            xcoordSparkle[0] = (GLfloat) ((1-interpTrace)*((1-interp)*xcoordK[13] + (interp)*xcoordStar[13])) + (interpTrace*((1-interp)*xcoordK[14] + (interp)*xcoordStar[14]))+translate;
            ycoordSparkle[0] = (GLfloat) ((1-interpTrace)*(((1-interp)*ycoordK[13] + (interp)*ycoordStar[13]))) + (interpTrace*(((1-interp)*ycoordK[14] + (interp)*ycoordStar[14])));
        }
        if(count == 8) {
            xcoordSparkle[0] = (GLfloat) ((1-interpTrace)*((1-interp)*xcoordK[15] + (interp)*xcoordStar[15])) + (interpTrace*((1-interp)*xcoordK[17] + (interp)*xcoordStar[17]))+translate;
            ycoordSparkle[0] = (GLfloat) ((1-interpTrace)*(((1-interp)*ycoordK[15] + (interp)*ycoordStar[15]))) + (interpTrace*(((1-interp)*ycoordK[17] + (interp)*ycoordStar[17])));
        }
        if(count == 9) {
            xcoordSparkle[0] = (GLfloat) ((1-interpTrace)*((1-interp)*xcoordK[18] + (interp)*xcoordStar[18])) + (interpTrace*((1-interp)*xcoordK[19] + (interp)*xcoordStar[19]))+translate;
            ycoordSparkle[0] = (GLfloat) ((1-interpTrace)*(((1-interp)*ycoordK[18] + (interp)*ycoordStar[18]))) + (interpTrace*(((1-interp)*ycoordK[19] + (interp)*ycoordStar[19])));
        }
        if(count == 10) {
            xcoordSparkle[0] = (GLfloat) ((1-interpTrace)*((1-interp)*xcoordK[19] + (interp)*xcoordStar[19])) + (interpTrace*((1-interp)*xcoordK[20] + (interp)*xcoordStar[20]))+translate;
            ycoordSparkle[0] = (GLfloat) ((1-interpTrace)*(((1-interp)*ycoordK[19] + (interp)*ycoordStar[19]))) + (interpTrace*(((1-interp)*ycoordK[20] + (interp)*ycoordStar[20])));
        }
        if(count == 11) {
            xcoordSparkle[0] = (GLfloat) ((1-interpTrace)*((1-interp)*xcoordK[21] + (interp)*xcoordStar[21])) + (interpTrace*((1-interp)*xcoordK[23] + (interp)*xcoordStar[23]))+translate;
            ycoordSparkle[0] = (GLfloat) ((1-interpTrace)*(((1-interp)*ycoordK[21] + (interp)*ycoordStar[21]))) + (interpTrace*(((1-interp)*ycoordK[23] + (interp)*ycoordStar[23])));
        }


        // Create lines for the sparkle effect from the center of the sparkle and uses glRotatef to rotate it around the z axis
        glPushMatrix();
        glTranslatef(xcoordSparkle[0],ycoordSparkle[0],0);
        glRotatef(theta, 0.0f, 0.0f, 1.0f);
        glBegin(GL_LINES);
        glColor4f(1.0, 1.0, 1.0, 1.0); 
        glVertex2f(0, 0);
        glColor4f(1.0, 1.0, 1.0, 0.01); 
        glVertex2f((1-interpSparkle)*0+(interpSparkle)*13, (1-interpSparkle)*0 + (interpSparkle)*13);      
        glEnd();

        glBegin(GL_LINES);
        glColor4f(1.0, 1.0, 1.0, 1.0); 
        glVertex2f(0, 0);
        glColor4f(1.0, 1.0, 1.0, 0.01); 
        glVertex2f((1-interpSparkle_2)*0+(interpSparkle_2)*-13, (1-interpSparkle_2)*0 + (interpSparkle_2)*-13);      
        glEnd();

        glBegin(GL_LINES);
        glColor4f(1.0, 1.0, 1.0, 1.0); 
        glVertex2f(0, 0);
        glColor4f(1.0, 1.0, 1.0, 0.01); 
        glVertex2f((1-interpSparkle_3)*0+(interpSparkle_3)*-13, (1-interpSparkle_3)*0 + (interpSparkle_3)*+13);      
        glEnd();

        glBegin(GL_LINES);
        glColor4f(1.0, 1.0, 1.0, 1.0); 
        glVertex2f(0, 0);
        glColor4f(1.0, 1.0, 1.0, 0.01); 
        glVertex2f((1-interpSparkle_4)*0+(interpSparkle_4)*+13, (1-interpSparkle_4)*0 + (interpSparkle_4)*-13);      
        glEnd();


        glBegin(GL_LINES);
        glColor4f(1.0, 1.0, 1.0, 1.0); 
        glVertex2f(0, 0);
        glColor4f(1.0, 1.0, 1.0, 0.01); 
        glVertex2f((1-interpSparkle_5)*0+(interpSparkle_5)*+0, (1-interpSparkle_5)*0 + (interpSparkle_5)*+13);      
        glEnd();


        glBegin(GL_LINES);
        glColor4f(1.0, 1.0, 1.0, 1.0); 
        glVertex2f(0, 0);
        glColor4f(1.0, 1.0, 1.0, 0.01); 
        glVertex2f((1-interpSparkle_6)*0+(interpSparkle_6)*+0, (1-interpSparkle_6)*0 + (interpSparkle_6)*-13);      
        glEnd();


        glBegin(GL_LINES);
        glColor4f(1.0, 1.0, 1.0, 1.0); 
        glVertex2f(0, 0);
        glColor4f(1.0, 1.0, 1.0, 0.01); 
        glVertex2f((1-interpSparkle_7)*0+(interpSparkle_7)*+13, (1-interpSparkle_7)*0 + (interpSparkle_7)*0);      
        glEnd();


        glBegin(GL_LINES);
        glColor4f(1.0, 1.0, 1.0, 1.0); 
        glVertex2f(0, 0);
        glColor4f(1.0, 1.0, 1.0, 0.01); 
        glVertex2f((1-interpSparkle_8)*0+(interpSparkle_8)*-13, (1-interpSparkle_8)*0 + (interpSparkle_8)*0);      
        glEnd();
        glPopMatrix();

        // Randomly generate spark color, spark speeds, and the amount of sparks at one time
        if(sparksON) {

            if(spark) {
                glPushMatrix();
                glTranslatef(xcoordSparkle[0],ycoordSparkle[0],0);
                glBegin(GL_LINES);
                glColor4f(randomColor1, randomColor2, randomColor3, 0.00001); 
                glVertex2f(0, 0);
                glColor4f(randomColor1, randomColor2, randomColor3, 1.0); 
                glVertex2f((1-interpSparkle)*0+(interpSparkle)*randomX, (1-interpSparkle)*0 + (interpSparkle)*randomY);     
                glEnd();
                glPopMatrix();
            }
            if(spark_2) {
                glPushMatrix();
                glTranslatef(xcoordSparkle[0],ycoordSparkle[0],0);
                glBegin(GL_LINES);
                glColor4f(randomColor1_2, randomColor2_2, randomColor3_2, 0.00001); 
                glVertex2f(0, 0);
                glColor4f(randomColor1_2, randomColor2_2, randomColor3_2, 1.0); 
                glVertex2f((1-interpSparkle_2)*0+(interpSparkle_2)*randomX_2, (1-interpSparkle_2)*0 + (interpSparkle_2)*randomY_2);     
                glEnd();
                glPopMatrix();
            }
            if(spark_3) {
                glPushMatrix();
                glTranslatef(xcoordSparkle[0],ycoordSparkle[0],0);
                glBegin(GL_LINES);
                glColor4f(randomColor1_3, randomColor2_3, randomColor3_3, 0.00001); 
                glVertex2f(0, 0);
                glColor4f(randomColor1_3, randomColor2_3, randomColor3_3, 1.0); 
                glVertex2f((1-interpSparkle_3)*0+(interpSparkle_3)*randomX_3, (1-interpSparkle_3)*0 + (interpSparkle_3)*randomY_3);     
                glEnd();
                glPopMatrix();
            }
            if(spark_4) {
                glPushMatrix();
                glTranslatef(xcoordSparkle[0],ycoordSparkle[0],0);
                glBegin(GL_LINES);
                glColor4f(randomColor1_4, randomColor2_4, randomColor3_4, 0.00001); 
                glVertex2f(0, 0);
                glColor4f(randomColor1_4, randomColor2_4, randomColor3_4, 1.0); 
                glVertex2f((1-interpSparkle_4)*0+(interpSparkle_4)*randomX_4, (1-interpSparkle_4)*0 + (interpSparkle_4)*randomY_4);     
                glEnd();
                glPopMatrix();            
            }
            if(spark_5) {
                glPushMatrix();
                glTranslatef(xcoordSparkle[0],ycoordSparkle[0],0);
                glBegin(GL_LINES);
                glColor4f(randomColor1_5, randomColor2_5, randomColor3_5, 0.00001); 
                glVertex2f(0, 0);
                glColor4f(randomColor1_5, randomColor2_5, randomColor3_5, 1.0); 
                glVertex2f((1-interpSparkle_5)*0+(interpSparkle_5)*randomX_5, (1-interpSparkle_5)*0 + (interpSparkle_5)*randomY_5);     
                glEnd();
                glPopMatrix();
            }
            if(spark_6) {
                glPushMatrix();
                glTranslatef(xcoordSparkle[0],ycoordSparkle[0],0);
                glBegin(GL_LINES);
                glColor4f(randomColor1_6, randomColor2_6, randomColor3_6, 0.00001); 
                glVertex2f(0, 0);
                glColor4f(randomColor1_6, randomColor2_6, randomColor3_6, 1.0); 
                glVertex2f((1-interpSparkle_6)*0+(interpSparkle_6)*randomX_6, (1-interpSparkle_6)*0 + (interpSparkle_6)*randomY_6);     
                glEnd();
                glPopMatrix();           
            }
            if(spark_7) {
                glPushMatrix();
                glTranslatef(xcoordSparkle[0],ycoordSparkle[0],0);
                glBegin(GL_LINES);
                glColor4f(randomColor1_7, randomColor2_7, randomColor3_7, 0.00001); 
                glVertex2f(0, 0);
                glColor4f(randomColor1_7, randomColor2_7, randomColor3_7, 1.0); 
                glVertex2f((1-interpSparkle_7)*0+(interpSparkle_7)*randomX_7, (1-interpSparkle_7)*0 + (interpSparkle_7)*randomY_7);     
                glEnd();
                glPopMatrix();
            }
            if(spark_8) {
                glPushMatrix();
                glTranslatef(xcoordSparkle[0],ycoordSparkle[0],0);
                glBegin(GL_LINES);
                glColor4f(randomColor1_8, randomColor2_8, randomColor3_8, 0.00001); 
                glVertex2f(0, 0);
                glColor4f(randomColor1_8, randomColor2_8, randomColor3_8, 1.0); 
                glVertex2f((1-interpSparkle_8)*0+(interpSparkle_8)*randomX_8, (1-interpSparkle_8)*0 + (interpSparkle_8)*randomY_8);     
                glEnd();
                glPopMatrix();
            }
        }

    }
}


/************************************************************************

    Function:      initalize

    Description:    Setup cordinate system and inialize display

*************************************************************************/
void initalize(void)
{ 
    // clear the screen 
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    // glOrtho changes the cordinate system to match the mouse
    glOrtho(0,500,500,0,-1,1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    // Set the background to black
    glColor3f(1.0, 1.0, 1.0); 
    glEnd();

    ButtonDraw();

    glutSwapBuffers();                   
}

/************************************************************************

    Function:      initalizeButtons

    Description:    Creates the buttons

*************************************************************************/

void initializeButtons(void) {
    CreateButton("Sparkle",isButtonPressed, 40,420,40,80);
    CreateButton("Sparks",isButtonPressed, 150,420,40,80);
    CreateButton("Morph",isButtonPressed, 270,420,40,80);
    CreateButton("BONUS",isButtonPressed, 380,420,40,80);

}


/************************************************************************

    Function:       main

    Description:    Sets up the openGL and begin to render content

*************************************************************************/
void main(int argc, char** argv)
{
    // initialize the toolkit
    glutInit(&argc, argv);          
    // set display mode
    glutInitDisplayMode(GLUT_RGB|GLUT_DOUBLE); 
    // set window size
    glutInitWindowSize(500,500);     
    // set window position on screen
    glutInitWindowPosition(100, 150); 
    // open the screen window
    glutCreateWindow("Assignment 1 - Kyle Asaff");
    // Initalize Blending for transparency of sparks
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable( GL_BLEND );
    // Initalize Button Creation
    initializeButtons();
    // Initalize Display
    glutDisplayFunc(initalize);     
    //initialize the rendering context               
    glutMouseFunc(MouseButton);
    // Call Idle Function
    glutIdleFunc(myIdle);
    // Go into a perpetual loop
    glutMainLoop();              
}            