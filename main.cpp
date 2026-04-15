#include <thread>
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

struct QuadColors
{
    Color upperLeft;
    Color upperRight;
    Color lowerLeft;
    Color lowerRight;
};

struct QuadSize // Quad Size Struct
{
    Point upperLeft;
    Point upperRight;
    Point lowerLeft;
    Point lowerRight;
};
struct TriSize {
    Point top;
    Point bottomRight;
    Point bottomLeft;
};

// -------- Universally Defined Colors ------------- //

// Other Colors
const Color WHITE = { 1.0f, 1.0f, 1.0f, 1.0f };
const Color BLACK = { 0.0f, 0.0f, 0.0f, 1.0f };
const Color RED = { 1.0f, 0.0f, 0.0f, 1.0f };
const Color YELLOW = { 1.0f, 1.0f, 0.0f, 1.0f };

// Blues
const Color BLUE = { 0.0f, 0.0f, 1.0f, 1.0f };
const Color CYAN = { 0.0f, 1.0f, 1.0f, 1.0f };
const Color LIGHTBLUE = { 0.678f, 0.847f, 0.902f, 1.0f };

// Greens
const Color GREEN = { 0.0f, 1.0f, 0.0f, 1.0f };
const Color DGREEN = { 0.2823f , .5882f , 0.2941f, 1.0f };

// Browns
const Color BROWN = { 0.8745f , 0.6705f , 0.3764f, 1.0f };
const Color DBROWN = { 0.431f ,0.176f ,0.050f, 1.0f };

// Specific Colors
const Color SKYTOP = { 0.32f, 0.76f, 0.90f, 1.0f };
const Color SKYBOTTOM = { 0.27f, 0.5f, 1.0f, 1.0f };

const Color GRASSBOTTOM = { 0.0f, 0.8f, 0.0f, 1.0f };

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

QuadSize newQuadSize(Point lowerLeft, Point lowerRight, Point upperLeft, Point upperRight)
{
    QuadSize quadSize;
    quadSize.lowerLeft = lowerLeft;
    quadSize.lowerRight = lowerRight;
    quadSize.upperLeft = upperLeft;
    quadSize.upperRight = upperRight;

    return quadSize;
}

QuadColors newQuadColors(Color lowerLeft, Color lowerRight, Color upperLeft, Color upperRight) 
{
    QuadColors quadGradientColor;
    quadGradientColor.lowerLeft = lowerLeft;
    quadGradientColor.lowerRight = lowerRight;
    quadGradientColor.upperLeft = upperLeft;
    quadGradientColor.upperRight = upperRight;
    return quadGradientColor;
}

TriSize newTriSize(Point top, Point bottomRight, Point bottomLeft) {
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

    glColor4f(color.r, color.g, color.b, color.a);  

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

// Draw Quad of desired size
void drawQuad(QuadSize size, Color color = WHITE)
{
    glBegin(GL_QUADS);
    glColor4f(color.r, color.g, color.b, color.a);
    glVertex2f(size.upperLeft.x, size.upperLeft.y);
    glVertex2f(size.lowerLeft.x, size.lowerLeft.y);
    glVertex2f(size.lowerRight.x, size.lowerRight.y);
    glVertex2f(size.upperRight.x, size.upperRight.y);
    glEnd();
}

// Draw Quad of desired size
void drawQuadGradient(QuadSize size, QuadColors color = newQuadColors(WHITE, WHITE, WHITE, WHITE))
{
    glBegin(GL_QUADS);

    // Upper Left
    glColor4f(color.upperLeft.r, color.upperLeft.g, color.upperLeft.b, color.upperLeft.a);
    glVertex2f(size.upperLeft.x, size.upperLeft.y);

    // Lower Left
    glColor4f(color.lowerLeft.r, color.lowerLeft.g, color.lowerLeft.b, color.lowerLeft.a);
    glVertex2f(size.lowerLeft.x, size.lowerLeft.y);

    // Lower Right
    glColor4f(color.lowerRight.r, color.lowerRight.g, color.lowerRight.b, color.lowerRight.a);
    glVertex2f(size.lowerRight.x, size.lowerRight.y);

    // Upper Right
    glColor4f(color.upperRight.r, color.upperRight.g, color.upperRight.b, color.upperRight.a);
    glVertex2f(size.upperRight.x, size.upperRight.y);
    glEnd();
}

void drawTriangle(TriSize size, Color color = WHITE) {
    // Start describing a primitive where each group of 3 vertices is a triangle
    glBegin(GL_TRIANGLES);
    glColor4f(color.r, color.g, color.b, color.a);

    // Vertex 1: set current color to RED, then set its position
  //  glColor3f(1.0f, 0.0f, 0.0f);      // Red
    glVertex2f(size.top.x, size.top.y);         // Bottom-left area

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

// -------------------------------------------------------- Other Funtionalities ------------------------------------------------------- //

//Function to compute float random values
float randf() 
{
    float decimalValue = (rand() / 100.0f);
    return decimalValue - std::floorf(decimalValue);
}

// Timer
int frameCount;
float elapsedSeconds;
int lifeTimeTimer;
const int FPS = 60;

static bool Timer()
{
    frameCount++;
    elapsedSeconds = (float)frameCount / FPS;

    // Example: print every second
    if (frameCount % FPS == 0)
    {
        return true;
    }

	return false;
    
}

// ------------------------------------------------------ Create New Objects ----------------------------------------------------- //

// Physical Particle
class CloudParticle
{
private:

	// Position
    Point currentPos;
    Point initPos;
    float startYPos;
    float speed;

    // Scale
    float radius = 100;
    float lines = 100;

    // Color
    Color color;

    void Draw()
    {
        drawBasicShape(currentPos, radius, lines, color);
    }

public:
    CloudParticle(Point pos)
    {
        // Control Position
		pos.y += (randf() * 200) - 100; // Random vertical offset between -100 and +100
        startYPos = randf() * pos.y;
        currentPos = pos;
        initPos = pos;

		// Control Speed and Size
		speed = randf(); // Random speed between 0.5 and 1.5
        radius = 50 + (randf() * 25); // Random radius between 50 and 75

        // Randomize Color
        float gsColor = 0.8f + (randf() * 0.5f);
		float alpha = 0.8f + (randf() * 0.5f); // Random alpha between 0.5 and 1.0
        color = NewColor(gsColor, gsColor, gsColor, alpha);
    }

    void Move()
    {
        currentPos.x += 0.5f * speed;
		currentPos.y = sinf(currentPos.x * 0.01f) * 20 + initPos.y + startYPos; // Sine wave vertical movement
    }

    void Update()
    {
        glPushMatrix();

        Move();
        Draw();

        glPopMatrix();
    }
};

// Cloud Section For Particles To Spawn

class CloudGroup
{
    private:

        Point pos;
        std::vector<CloudParticle> particleList;
    public:

        CloudGroup(Point pos)
        {
            this->pos = pos;
        }

        void SpawnParticle() 
        {
            if (randf() > 0.9f)
            {
                particleList.push_back(CloudParticle(pos));
            }
        }
        void UpdateParticle() {
            for (auto& circle : particleList)
            {
                circle.Update();
            }
        }

        void Update() 
        {
            glPushMatrix();

            SpawnParticle();
            UpdateParticle();

            glPopMatrix();
        }
};

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
    drawBasicShape(leftCirclePos, radius, lines, DGREEN);
    drawBasicShape(rightCirclePos, radius, lines, DGREEN);
    drawBasicShape(topCirclePos, radius, lines, DGREEN);
    drawBasicShape(bottomCirclePos, radius, lines, DGREEN);
    //Draws the main trunk
    Point upperLeft = NewPos(pos.x + 50, pos.y - 125);
    Point upperRight = NewPos(pos.x - 50, pos.y - 125);
    Point lowerLeft = NewPos(pos.x + 50, pos.y - 370);
    Point lowerRight = NewPos(pos.x - 50, pos.y - 370);
    QuadSize quadSize = newQuadSize(lowerLeft, lowerRight, upperLeft, upperRight);
    drawQuad(quadSize, DBROWN);
}

void Ground(Point pos)
{
    Point upperLeft = NewPos(pos.x + screenWidth, pos.y + 200);
    Point upperRight = NewPos(pos.x - screenWidth, pos.y + 200);
    Point lowerLeft = NewPos(pos.x + screenWidth, pos.y - 200);
    Point lowerRight = NewPos(pos.x - screenWidth, pos.y - 200);

    QuadSize quadSize = newQuadSize(lowerLeft, lowerRight, upperLeft, upperRight);

    drawQuadGradient(quadSize, newQuadColors(GRASSBOTTOM, GRASSBOTTOM, GREEN, GREEN));
}

void Sky() 
{
    Point upperLeft = NewPos(screenWidth, screenHeight);
    Point upperRight = NewPos(-screenWidth, screenHeight);
    Point lowerLeft = NewPos(screenWidth, -screenHeight);
    Point lowerRight = NewPos(-screenWidth, -screenHeight);

    QuadSize quadSize = newQuadSize(lowerLeft, lowerRight, upperLeft, upperRight);

    drawQuadGradient(quadSize, newQuadColors(SKYBOTTOM, SKYBOTTOM, SKYTOP, SKYTOP));
}


void Pickets(Point pos) {
    Point upperLeft = NewPos(pos.x + 30, pos.y + 100);
    Point upperRight = NewPos(pos.x - 30, pos.y + 100);
    Point lowerLeft = NewPos(pos.x + 30, pos.y - 100);
    Point lowerRight = NewPos(pos.x - 30, pos.y - 100);
    QuadSize quadSize = newQuadSize(lowerLeft, lowerRight, upperLeft, upperRight);
    drawQuad(quadSize, BROWN);
    Point top = NewPos(pos.x + 0, pos.y + 120);
    Point bottomRight = NewPos(pos.x - 30, pos.y + 100);
    Point bottomLeft = NewPos(pos.x + 30, pos.y + 100);
    TriSize triSize = newTriSize(top, bottomRight, bottomLeft);
    drawTriangle(triSize, WHITE);



}
void Fence(Point pos) {

    Point upperLeft = NewPos(pos.x + screenWidth, pos.y + 20);
    Point upperRight = NewPos(pos.x - screenWidth, pos.y + 20);
    Point lowerLeft = NewPos(pos.x + screenWidth, pos.y - 30);
    Point lowerRight = NewPos(pos.x - screenWidth, pos.y - 30);

    QuadSize quadSize = newQuadSize(lowerLeft, lowerRight, upperLeft, upperRight);

    drawQuad(quadSize, BROWN);
};

// Booth and Path Drawings
void drawBooth(Point pos) {

    // Booth base (rectangle)
    glColor3f(0.8, 0.2, 0.2); // red
    glBegin(GL_POLYGON);
    glVertex2f((-0.9 * screenWidth / 2) + pos.x, (-0.3 * screenHeight) + pos.y);
    glVertex2f((-0.6 * screenWidth / 2) + pos.x, (-0.3 * screenHeight) + pos.y);
    glVertex2f((-0.6 * screenWidth / 2) + pos.x, (0.0 * screenHeight) + pos.y);
    glVertex2f((-0.9 * screenWidth / 2) + pos.x, (0.0 * screenHeight) + pos.y);
    glEnd();

    // Roof (triangle)
    glColor3f(0.5, 0.1, 0.1);
    glBegin(GL_TRIANGLES);
    glVertex2f((-0.95 * screenWidth / 2) + pos.x, (0.0 * screenHeight) + pos.y);
    glVertex2f((-0.55 * screenWidth / 2) + pos.x, (0.0 * screenHeight) + pos.y);
    glVertex2f((-0.75 * screenWidth / 2) + pos.x, (0.2 * screenHeight) + pos.y);
    glEnd();

    // Window
    glColor3f(0.9, 0.9, 1.0); // light blue
    glBegin(GL_POLYGON);
    glVertex2f((-0.82 * screenWidth / 2) + pos.x, (-0.15 * screenHeight) + pos.y);
    glVertex2f((-0.68 * screenWidth / 2) + pos.x, (-0.15 * screenHeight) + pos.y);
    glVertex2f((-0.68 * screenWidth / 2) + pos.x, (-0.05 * screenHeight) + pos.y);
    glVertex2f((-0.82 * screenWidth / 2) + pos.x, (-0.05 * screenHeight) + pos.y);
    glEnd();

    // Sign (Ticket)
    glColor3f(1.0, 1.0, 0.0); // yellow
    glBegin(GL_POLYGON);
    glVertex2f((-0.85 * screenWidth / 2) + pos.x, (0.05 * screenHeight) + pos.y);
    glVertex2f((-0.65 * screenWidth / 2) + pos.x, (0.05 * screenHeight) + pos.y);
    glVertex2f((-0.65 * screenWidth / 2) + pos.x, (0.12 * screenHeight) + pos.y);
    glVertex2f((-0.85 * screenWidth / 2) + pos.x, (0.12 * screenHeight) + pos.y);
    glEnd();
}

void drawPath(Point pos) {
    // Main path
    glColor3f(0.6, 0.6, 0.6); // gray
    glBegin(GL_POLYGON);
    glVertex2f((-1.0 * screenWidth) + pos.x, (-0.6 * screenHeight) + pos.y);
    glVertex2f((1.0 * screenWidth) + pos.x, (-0.6 * screenHeight) + pos.y);
    glVertex2f((1.0 * screenWidth) + pos.x, (-0.4 * screenHeight) + pos.y);
    glVertex2f((-1.0 * screenWidth) + pos.x, (-0.4 * screenHeight) + pos.y);
    glEnd();

    // Path lines (decorative stripes)
    glColor3f(1.0, 1.0, 1.0); // white

    for (float x = -0.9; x < 1.0; x += 0.3) {
        glBegin(GL_POLYGON);
        glVertex2f((x * screenWidth) + pos.x, (-0.52 * screenHeight) + pos.y);
        glVertex2f(((x + 0.15) * screenWidth) + pos.x, (-0.52 * screenHeight) + pos.y);
        glVertex2f(((x + 0.15) * screenWidth) + pos.x, (-0.48 * screenHeight) + pos.y);
        glVertex2f((x * screenWidth) + pos.x, (-0.48 * screenHeight) + pos.y);
        glEnd();
    }
}

// Draw a single vertical post/pole
void drawPost(Point base, float height, float width, Color color = WHITE) {
    QuadSize post = newQuadSize(
        NewPos(base.x - width / 2, base.y),                    // lower left
        NewPos(base.x + width / 2, base.y),                    // lower right
        NewPos(base.x - width / 2, base.y + height),           // upper left
        NewPos(base.x + width / 2, base.y + height)            // upper right
    );
    drawQuad(post, color);
}

// Draw the light string + colored bulbs
void drawLightString(Point leftPostTop, Point rightPostTop, int numBulbs, Color bulbColors[]) {
    // Draw black wire
    glBegin(GL_LINE_STRIP);
    glColor4f(BLACK.r, BLACK.g, BLACK.b, 1.0f);

    const int segments = 40;  // curved
    for (int i = 0; i <= segments; i++) {
        float t = (float)i / segments;
        float x = leftPostTop.x + t * (rightPostTop.x - leftPostTop.x);

        // string curve
        float sag = 30.0f * sinf(PI * t);  // max sag = 30 pixels
        float y = leftPostTop.y - sag;

        glVertex2f(x, y);
    }
    glEnd();

    // Place the colored bulbs
    float bulbRadius = 22.0f;
    for (int i = 0; i < numBulbs; i++) {
        float t = (float)(i + 1) / (numBulbs + 1);  // space evenly
        float x = leftPostTop.x + t * (rightPostTop.x - leftPostTop.x);
        float sag = 30.0f * sinf(PI * t);
        float y = leftPostTop.y - sag;

        Color bulbColor = bulbColors[i % 3];  // cycle through yellow/red/blue
        drawBasicShape(NewPos(x, y), bulbRadius, 12, bulbColor);
    }
}

// ------ Ferris Wheel ------- //
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
    {
    }

    void rotate(float speed) {
        rotation += speed;
        if (rotation > 360.0f) rotation -= 360.0f;
    }
};

// TODO: Isolate cars and Wheel draw
void drawFerris(FerrisWheel& fw) {
    // Draw Wheel
    drawBasicShape(fw.center, fw.radius, 100, fw.color);
    drawBasicShape(fw.center, 290, 30, NewColor(0.0, 0.6, 1.0, 1.0));

    // Make spokes thicker
    glLineWidth(3.0f);
    // Draw spokes and cars
    for (int i = 0; i < fw.numCars; i++) {
        float angle = (2.0f * PI * i / fw.numCars) + (fw.rotation * PI / 180.0f);


        float carX = fw.center.x + fw.radius * cos(angle);
        float carY = fw.center.y + fw.radius * sin(angle);

        // TODO: Rotate cars 45 deg
        glBegin(GL_LINES);
        glColor4f(BLACK.r, BLACK.g, BLACK.b, 1.0);
        glVertex2f(fw.center.x, fw.center.y);
        glVertex2f(carX, carY);
        glEnd();

        drawBasicShape(NewPos(carX, carY), 30, 4, YELLOW);
    }
}

void drawFerrisBase(Point center, float height, Color color) {
    TriSize baseTri = newTriSize(
        center,
        NewPos(center.x + 200, center.y - height),
        NewPos(center.x - 200, center.y - height)
    );


    drawTriangle(baseTri, color);

    // second thinner triangle
    drawTriangle(newTriSize(center, NewPos(center.x + 180, center.y - height), NewPos(center.x - 180, center.y - height)), BLACK);
    drawTriangle(newTriSize(NewPos(center.x, center.y - 20), NewPos(center.x + 170, center.y - height), NewPos(center.x - 170, center.y - height)), color);
}

void drawFerrisHub(Point center, float radius, Color color) {
    drawBasicShape(center, radius, 30, color);
    drawBasicShape(center, radius * 0.5, 20, color);
}
FerrisWheel ferris(NewPos(0, 100), 300.0f, 8, BLUE);



void animateFerris() {
    // TODO: uncomment this after first submission
    // ferris.rotate(1.0f);
}

// ---------------------------------------- Object Group Creation List --------------------------------------- //
CloudGroup cloud1(NewPos(-screenWidth - 100, screenHeight - 200));

// ----------------------------------- Display Function --> Represent Draw Order ------------------------------------ //
void display() {
    glClear(GL_COLOR_BUFFER_BIT);

	// Draw Sky
	Sky();

    // Create Ground
    Ground(NewPos(0, -520));

    //Ferris Wheel
    drawFerrisBase(ferris.center, 450, BLACK);

    drawFerris(ferris);

    drawFerrisHub(ferris.center, 40, BLUE);
    // Create Tree
    CreateTree(NewPos(-850, 50));

    // Create Fence and Pickets
    Fence(NewPos(4, -250));

    int picketSpread = 125;
    int picketAmount = 20;
    for (int i = 0; i < picketAmount; i++) 
    {
        Pickets(NewPos(-1200 + (picketSpread * i), -250));
    }

    // Light strings and poles:
    drawPost(NewPos(-950, -420), 400, 30); // Pole 1
    drawPost(NewPos(-650, -420), 400, 30); // Pole 2
    drawPost(NewPos(-400, -420), 400, 30); // Pole 3

    // First light string
    Color leftBulbColors[3] = { YELLOW, RED, BLUE };
    drawLightString(NewPos(-950, -20), NewPos(-650, -20), 3, leftBulbColors);

    // Second light string
    Color rightBulbColors[3] = { YELLOW, BLUE, RED };
    drawLightString(NewPos(-650, -20), NewPos(-400, -20), 3, rightBulbColors);

    // Create Trees
    CreateTree(NewPos(750, 35));

    // Booth and Path
    drawBooth(NewPos(1000, -300));
    drawPath(NewPos(0, -200));

    // Create Clouds
    cloud1.Update();
    //CloudGroup.Update(NewPos(-600, 500));

    glFlush();
}

// --------- Main ---------- //

// Initialize OpenGL settings
void init() {
	glClearColor(0.0, 0.4, 1.0, 1.0); // Does not work with gradient sky --> Deprcated
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-screenWidth, screenWidth, -screenHeight, screenHeight);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
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
