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

// -------- Universally Defined Colors ------------- //

const Color WHITE = { 1.0f, 1.0f, 1.0f };
const Color BLACK = { 0.0f, 0.0f, 0.0f };
const Color RED = { 1.0f, 0.0f, 0.0f };
const Color BLUE = { 0.0f, 1.0f, 0.0f };
const Color GREEN = { 0.0f, 0.0f, 1.0f };

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
    glColor4f(color.r, color.b, color.g, color.a);
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

void Ground(Point pos)
{
    Point upperLeft = NewPos(pos.x + screenWidth, pos.y + 200);
    Point upperRight = NewPos(pos.x - screenWidth, pos.y + 200);
    Point lowerLeft = NewPos(pos.x + screenWidth, pos.y - 200);
    Point lowerRight = NewPos(pos.x - screenWidth, pos.y - 200);

    RecSize recSize = newRecSize(lowerLeft, lowerRight, upperLeft, upperRight);

    drawRectangle(recSize, GREEN);
}

// ------ Display Function --> Represent Draw Order ------ //
void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    // Create Ground
    Ground(NewPos(0, -520));

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

int main(int argc, char** argv) {

    // Initialize Display
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(screenWidth, screenHeight);
    glutCreateWindow("Ferris Wheel");

    // Run Graphics
    init();
    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}
