#include <cstdlib>
#include <vector>
#include <math.h>
#include <iostream>

#ifdef __APPLE__
#include <GLUT/glut.h>

#else
#include <GL/glut.h>
#include <windows.h>
#endif
#define PI 3.1415926535898

// -------- Global Variables ---------- //

const int screenWidth = 1280;
const int screenHeight = 720;

// -------- Structs Defined ----------- //

struct Point
{
    float x;
    float y;
};

struct Color
{
    float r;
    float g;
    float b;
    float a;
};

struct RecSize // Rectangle Size Struct
{
    Point upperLeft;
    Point upperRight;
    Point lowerLeft;
    Point lowerRight;
};
struct TriSize{
    Point top;
    Point bottomRight;
    Point bottomLeft;


};

// -------- Universally Defined Colors ------------- //

const Color WHITE = { 1.0f, 1.0f, 1.0f };
const Color BLACK = { 0.0f, 0.0f, 0.0f };
const Color RED = { 1.0f, 0.0f, 0.0f };
const Color BLUE = { 0.0f, 0.0f, 1.0f };
const Color GREEN = { 0.0f, 1.0f, 0.0f };
const Color BROWN = {0.823f , 0.705f , 0.549f};
const Color DBROWN = {0.431f ,0.176 ,0.050};
const Color DGREEN = {0.509f , .431f , 0.070f};
// -------------- Ease Struct Creation --------------- //

// Makes it easier to create positions
Point NewPos(float x, float y)
{
    Point pos;
    pos.x = x;
    pos.y = y;
    return pos;
}

// Makes it easier to create colors
Color NewColor(float r, float g, float b, float a = 1.0)
{
    Color color;
    color.r = r;
    color.g = g;
    color.b = b;
    color.a = a;
    return color;
}

RecSize newRecSize(Point lowerLeft, Point lowerRight, Point upperLeft, Point upperRight)
{
    RecSize recSize;
    recSize.lowerLeft = lowerLeft;
    recSize.lowerRight = lowerRight;
    recSize.upperLeft = upperLeft;
    recSize.upperRight = upperRight;

    return recSize;
}
TriSize newTriSize(Point top, Point bottomRight , Point bottomLeft){
    TriSize triSize;
    triSize.top = top;
    triSize.bottomRight = bottomRight;
    triSize.bottomLeft = bottomLeft;
    return triSize;

}
// ------------------- Shape Drawing Functionalities ------------------ //

// Draws Basic Shapes --> Equal sides
void drawBasicShape(Point pos, float radius, int lines, Color color = WHITE)
{
    glBegin(GL_POLYGON);

    glColor4f(color.r, color.g, color.b, color.a);  // Purple

    // Generate points around the circle
    for (int i = 0; i < lines; i++)
    {
        // theta goes from 0 to 2PI in steps
        float theta = 2.0f * (float)PI * (float)i / (float)lines;

        // Parametric circle equation
        float x = radius * cosf(theta);
        float y = radius * sinf(theta);

        // Place the circle lower by subtracting 0.6 from y
        glVertex2f(x + pos.x, y + pos.y);
    }

    glEnd();
}

// Draw Rectangle of desired size
void drawRectangle(RecSize size, Color color = WHITE)
{
    glBegin(GL_QUADS);
    glColor4f(color.r, color.g, color.b, color.a);
    glVertex2f(size.upperLeft.x, size.upperLeft.y);
    glVertex2f(size.lowerLeft.x, size.lowerLeft.y);
    glVertex2f(size.lowerRight.x, size.lowerRight.y);
    glVertex2f(size.upperRight.x, size.upperRight.y);
    glEnd();
}

// ---------------- Create New Objects ---------------- //

void CreateCloud(Point pos)
{
    // Commonality variable
    float radius = 100;
    float lines = 100;

    // Position Child Shapes
    Point leftCirclePos = NewPos(pos.x - 100, pos.y);
    Point rightCirclePos = NewPos(pos.x + 100, pos.y);
    Point topCirclePos = NewPos(pos.x, pos.y - 75);
    Point bottomCirclePos = NewPos(pos.x, pos.y + 75);

    // Draw Shapes
    drawBasicShape(leftCirclePos, radius, lines);
    drawBasicShape(rightCirclePos, radius, lines);
    drawBasicShape(topCirclePos, radius, lines);
    drawBasicShape(bottomCirclePos, radius, lines);
}
void CreateTree(Point pos)
{
    // Commonality variable
    float radius = 100;
    float lines = 100;

    // Position Child Shapes
    Point leftCirclePos = NewPos(pos.x - 55, pos.y);
    Point rightCirclePos = NewPos(pos.x + 55, pos.y);
    Point topCirclePos = NewPos(pos.x, pos.y - 45);
    Point bottomCirclePos = NewPos(pos.x, pos.y + 45);

    // Draw Shapes
    drawBasicShape(leftCirclePos, radius, lines , DGREEN);
    drawBasicShape(rightCirclePos, radius, lines , DGREEN);
    drawBasicShape(topCirclePos, radius, lines , DGREEN);
    drawBasicShape(bottomCirclePos, radius, lines , DGREEN);
    //Draws the main trunk
    Point upperLeft = NewPos(pos.x + 50 , pos.y - 125);
    Point upperRight = NewPos(pos.x - 50 , pos.y - 125);
    Point lowerLeft = NewPos(pos.x + 50 , pos.y - 370);
    Point lowerRight = NewPos(pos.x - 50 , pos.y - 370);
    RecSize recSize = newRecSize(lowerLeft , lowerRight , upperLeft , upperRight);
    drawRectangle(recSize , DBROWN);
}
void drawTriangle(TriSize size ,Color color = WHITE) {
    // Start describing a primitive where each group of 3 vertices is a triangle
    glBegin(GL_TRIANGLES);

        // Vertex 1: set current color to RED, then set its position
      //  glColor3f(1.0f, 0.0f, 0.0f);      // Red
        glVertex2f(size.top.x,size.top.y );         // Bottom-left area

        // Vertex 2: set current color to GREEN, then set its position
     //   glColor3f(0.0f, 1.0f, 0.0f);      // Green
        glVertex2f(size.bottomRight.x, size.bottomRight.y);          // Bottom-right area

        // Vertex 3: set current color to BLUE, then set its position
    //    glColor3f(0.0f, 0.0f, 1.0f);      // Blue
        glVertex2f(size.bottomLeft.x, size.bottomLeft.y);
                   // Top-center area


    // End primitive description

    glEnd();
}

void Ground(Point pos)
{
    Point upperLeft = NewPos(pos.x + screenWidth, pos.y + 200);
    Point upperRight = NewPos(pos.x - screenWidth, pos.y + 200);
    Point lowerLeft = NewPos(pos.x + screenWidth, pos.y - 200);
    Point lowerRight = NewPos(pos.x - screenWidth, pos.y - 200);

    RecSize recSize = newRecSize(lowerLeft, lowerRight, upperLeft, upperRight);

    drawRectangle(recSize, GREEN);
}


void Pickets (Point pos){
 Point upperLeft = NewPos(pos.x + 30 , pos.y + 100);
    Point upperRight = NewPos(pos.x - 30 , pos.y + 100);
    Point lowerLeft = NewPos(pos.x + 30 , pos.y - 100);
    Point lowerRight = NewPos(pos.x - 30 , pos.y - 100);
    RecSize recSize = newRecSize(lowerLeft , lowerRight , upperLeft , upperRight);
    drawRectangle(recSize , BROWN);
    Point top = NewPos(pos.x + 0 , pos.y + 120 );
    Point bottomRight = NewPos(pos.x - 30 , pos.y + 100);
    Point bottomLeft = NewPos(pos.x + 30 , pos.y + 100);
    TriSize triSize = newTriSize( top , bottomRight , bottomLeft);
    drawTriangle(triSize , WHITE);



}
void Fence (Point pos) {

    Point upperLeft = NewPos(pos.x + screenWidth, pos.y + 20);
    Point upperRight = NewPos(pos.x - screenWidth, pos.y + 20);
    Point lowerLeft = NewPos(pos.x + screenWidth, pos.y - 30);
    Point lowerRight = NewPos(pos.x - screenWidth, pos.y - 30);


    RecSize recSize = newRecSize(lowerLeft, lowerRight, upperLeft, upperRight);

    drawRectangle(recSize, BROWN);



};
// ------ Ferris Wheel -------
struct FerrisWheel {
    Point center;
    float radius;
    float rotation;

    int numCars;
    Color color;

    FerrisWheel(Point _p, float _r, int _cars, Color _c) :
        center(_p),
        radius(_r),
        numCars(_cars),
        color(_c),
        rotation(0.0f)
    {}

    void rotate(float speed) {
        rotation += speed;
        if (rotation > 360.0f) rotation -= 360.0f;
    }
};

// TODO: Isolate cars and Wheel draw
void drawFerris(FerrisWheel &fw) {
    // Draw Wheel
    drawBasicShape(fw.center, fw.radius, 100, fw.color);
    drawBasicShape(fw.center, 290, 30, WHITE);

    // Draw spokes and cars
    for (int i = 0; i < fw.numCars; i++) {
        float angle = (2.0f *  PI * i / fw.numCars) + (fw.rotation * PI / 180.0f);

        float carX = fw.center.x + fw.radius * cos(angle);
        float carY = fw.center.y + fw.radius * sin(angle);

        glBegin(GL_LINES);
            glColor4f(BLACK.r, BLACK.g, BLACK.b, 1.0);
            glVertex2f(fw.center.x, fw.center.y);
            glVertex2f(carX, carY);
        glEnd();

        drawBasicShape(NewPos(carX, carY), 30, 4, RED);
    }

}

FerrisWheel ferris(NewPos(0, 0), 300.0f, 8, BLUE);

void animateFerris() {
    // TODO: uncomment this after first submission
    // ferris.rotate(1.0f);
}

// ------ Display Function --> Represent Draw Order ------ //
void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    // Create Ground
    Ground(NewPos(0, -520));
    Fence(NewPos (4 , -250));
    Pickets(NewPos( -700 , -250));
    Pickets(NewPos(-575 , -250));
    Pickets(NewPos(-450 , -250));
    Pickets(NewPos(-325 , -250));
    CreateTree(NewPos(-850 ,50));
    CreateTree(NewPos(750 ,35));
    //Ferris Wheel
    drawFerris(ferris);
    // Create Clouds
    CreateCloud(NewPos(700, 400));
    CreateCloud(NewPos(-600, 500));

    glFlush();
}

// --------- Main ---------- //

// Initialize OpenGL settings
void init() {
    glClearColor(0.0, 0.4, 1.0, 1.0); // Background Color
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-screenWidth, screenWidth, -screenHeight, screenHeight);
}

// Will run code every 60 FPS
void update() {
    animateFerris();
}

// Timer func for animation timing
void timer(int value) {
    update();
    // Triggers redraw
    glutPostRedisplay();
    // Waits 16ms per update
    glutTimerFunc(16, timer, value);
}

int main(int argc, char** argv) {

    // Initialize Display
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(screenWidth, screenHeight);
    glutCreateWindow("Ferris Wheel");

    // Run Graphics
    init();
    glutDisplayFunc(display);
    glutTimerFunc(0, timer, 0);
    glutMainLoop();
    return 0;
}
