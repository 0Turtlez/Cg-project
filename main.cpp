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

bool pause = false;
bool nightMode = false;
int speedMultiplier = 1;

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

// Makes it easier to change alpha channel
Color NewColor(Color color, float a)
{
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

    // Upper Right
    glColor4f(color.upperRight.r, color.upperRight.g, color.upperRight.b, color.upperRight.a);
    glVertex2f(size.upperRight.x, size.upperRight.y);

    // Lower Right
    glColor4f(color.lowerRight.r, color.lowerRight.g, color.lowerRight.b, color.lowerRight.a);
    glVertex2f(size.lowerRight.x, size.lowerRight.y);

    // Lower Left
    glColor4f(color.lowerLeft.r, color.lowerLeft.g, color.lowerLeft.b, color.lowerLeft.a);
    glVertex2f(size.lowerLeft.x, size.lowerLeft.y);
    
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

// Transistion from on color to the next
void static ColorChange(Color& currentColor, Color toColor, float transitionSpeed, bool includeAlpha = false) 
{
    // Transition all colors at the same time to a single value
    currentColor.r += ((toColor.r - currentColor.r) / transitionSpeed);
    currentColor.g += ((toColor.g - currentColor.g) / transitionSpeed);
    currentColor.b += ((toColor.b - currentColor.b) / transitionSpeed);

    if (includeAlpha) {
        currentColor.a += ((toColor.a - currentColor.a) / transitionSpeed);
    }
    
}

// ------------------------------------------------------ Create New Objects ----------------------------------------------------- //

// ----------------------------- Cloud Particle ----------------------------------- //
class CloudParticle
{
private:

	// Position
    Point currentPos;
    Point initPos;
    float startYPos;
    float speed;
    float initSpeed;

    // Scale
    float radius;
    float lines = 100;

    // Color
    Color currentColor;
    Color dayColor;
    Color nightColor;

    void Draw()
    {
        drawBasicShape(currentPos, radius, lines, currentColor);
    }

public:
    CloudParticle(Point pos, float initSpeed = 0.5f)
    {
        this->initSpeed = initSpeed;

        // Control Position
		pos.y += (randf() * 200) - 100; // Random vertical offset between -100 and +100
        startYPos = randf() * pos.y;
        currentPos = pos;
        initPos = pos;

		// Control Speed and Size
		speed = 0.5f + (randf() * 0.5f); // Random speed between 0.5 and 1.0
        radius = 50 + (randf() * 25); // Random radius between 50 and 75

        // Randomize Color
        float gsColor = 0.9f + (randf() * 0.1f);
		float alpha = 0.8f + (randf() * 0.2f); // Random alpha between 0.8 and 1.0
        currentColor = NewColor(gsColor, gsColor, gsColor, alpha);

        // Day and Night Color
        dayColor = currentColor;

        float gsNight = gsColor - 0.5f;
        nightColor = NewColor(gsNight, gsNight, gsNight, 0.0f);
        
    }

    void Move()
    {
        if (!pause) 
        {
            currentPos.x += initSpeed * speed;
            currentPos.y = sinf(currentPos.x * 0.01f) * 20 + initPos.y + startYPos; // Sine wave vertical movement
        }
    }

    void NightMode() 
    {
        if (!nightMode) 
        {
            ColorChange(currentColor, dayColor, 100, true);
        }
        else 
        {
            ColorChange(currentColor, nightColor, 100, true);
        }
        
    }

    void Update()
    {
        glPushMatrix();

        Move();
        NightMode();
        Draw();

        glPopMatrix();
    }
};

// ------------------------------------ Particle Group ---------------------------------- //
// Section For Particles To Spawn

template<typename particle>
class ParticleGroup
{
    private:

        Point pos;
        float speed;
        int maxParticles;
        float spawnRate;
        
        std::vector<particle> particleList;

    public:

        ParticleGroup(Point pos, int particleNum, float spawnRate = 0.9f, float speed = 0.5f)
        {
            this->spawnRate = spawnRate;
            maxParticles = particleNum;
            this->pos = pos;
			this->speed = speed;
        }

        void SpawnParticle() 
        {
            if (randf() > spawnRate && maxParticles >= particleList.size()) // Spawn rate control
            {
                particleList.push_back(particle(pos, speed));
            }
        }
        void UpdateParticle() 
        {
            for (auto& circle : particleList)
            {
                circle.Update();
            }
        }

        void NightMode() 
        {
            if (!nightMode) 
            {
                SpawnParticle();
            }
        }

        void Update() 
        {
            glPushMatrix();

            UpdateParticle();
            NightMode();

            glPopMatrix();
        }
};

// ---------------------------------- Sun ------------------------------------ //
class Sun 
{
private:
    Point initPos;
    Point currentPos;
    float radius;

    float sunTime; // animation time
    float sunDownTime; // animation time for sun going down
    float speed;
    float movementRange;

    int rayLayers; // How many rays the sun has
    float rayGrowth;
    float rayStartGrowth;

    void Draw()
    {
        // Sun Rays
        for (int i = rayLayers; i > 0; i--) {
            drawBasicShape(currentPos, radius + i * rayGrowth, 100, NewColor(YELLOW, 1.0f/(i+1)));
        }

        // Sun Circle
        drawBasicShape(currentPos, radius, 100, YELLOW);
    }

public:
    Sun(Point pos, float radius, float speed) 
    {
        this->initPos = pos;
        this->currentPos = pos;
        this->speed = speed;
        this->radius = radius;

        sunTime = 0;
        sunDownTime = 2 * PI;
        movementRange = 5;

        // Sun Rays
        rayLayers = 5;
        rayGrowth = 1;
        rayStartGrowth = 20;
    }

    void Move() 
    {
        // Control sun animation time
        sunTime += speed;

        // Expand and Contrast Rays
        rayGrowth = (sinf(sunTime) + rayStartGrowth);
    }

    void NightMode()
    {
        if (!nightMode)
        {
            if (sunDownTime < 2 * PI) {
                sunDownTime += speed;   
            }
        }
        else
        {
            if (sunDownTime > 2 * PI) {
                sunDownTime = 0;
            }

            if (sunDownTime < PI) {
                sunDownTime += speed;
            }
        }

        currentPos.y = ((sinf(sunDownTime + (PI / 2)) - 1) * 1000) + initPos.y;
    }

    void Update() 
    {
        glPushMatrix();

        if (!pause)
        {
            NightMode();
            Move();
        }

        Draw();

        glPopMatrix();
    }
};

// ------------------------------------ Moon --------------------------------- //
class Moon
{
private:
    Point initPos;
    Point currentPos;
    float radius;

    float moonTime; // animation time
    float moonDownTime; // animation time for moon going down
    float speed;
    float movementRange;

    int rayLayers; // How many rays the sun has
    float rayGrowth;
    float rayStartGrowth;

    void Draw()
    {
        // Moon Rays
        for (int i = rayLayers; i > 0; i--) {
            drawBasicShape(currentPos, radius + i * rayGrowth, 100, NewColor(WHITE, 1.0f / (i +2)));
        }

        // Sun Circle
        drawBasicShape(currentPos, radius, 100, WHITE);
    }

public:
    Moon(Point pos, float radius, float speed)
    {
        this->initPos = pos;
        this->currentPos = pos;
        this->speed = speed;
        this->radius = radius;

        moonTime = 0;
        moonDownTime = PI;
        movementRange = 5;

        // Sun Rays
        rayLayers = 2;
        rayGrowth = 1;
        rayStartGrowth = 20;
    }

    void Move()
    {
        // Control sun animation time
        moonTime += speed;

        // Expand and Contrast Rays
        rayGrowth = (sinf(moonTime) + rayStartGrowth);
    }

    void NightMode()
    {
        if (nightMode)
        {
            if (moonDownTime < 2 * PI) {
                moonDownTime += speed;
            }
        }
        else
        {
            if (moonDownTime > 2 * PI) {
                moonDownTime = 0;
            }

            if (moonDownTime < PI) {
                moonDownTime += speed;
            }
        }

        currentPos.y = ((sinf(moonDownTime + (PI / 2)) - 1) * 1000) + initPos.y;
    }

    void Update()
    {
        glPushMatrix();

        if (!pause)
        {
            NightMode();
            Move();
        }

        Draw();

        glPopMatrix();
    }
};

// -------------------------------------- Star Particles ----------------------------------- //
class StarParticle
{
private:

    // Position
    Point currentPos;
    Point initPos;

    // Scale
    float radius;
    float lines = 100;

    // Animation Time
    float starTime = 0;
    bool switchDirectionFlag = true;
    float speed;

    // Color
    Color currentColor;
    Color dayColor;
    Color nightColor;

    void Draw()
    {
        drawBasicShape(currentPos, radius, lines, currentColor);
    }

public:
    StarParticle(Point pos, float speed)
    {
        // Glow Speed
        this->speed = (randf() * speed);

        // Control Position
        pos = NewPos(rand() % screenWidth * std::powf(-1, std::round(randf())), rand() % screenHeight * std::powf(-1, std::round(randf())));

        currentPos = pos;
        initPos = pos;

        // Control Size
        radius = 2 + (randf() * 4); // Random radius between 50 and 75

        // Randomize Color
        currentColor = NewColor(WHITE, 0.0f);

        // Day and Night Color
        dayColor = NewColor(WHITE, 0.0f);
        nightColor = WHITE;

    }

    void Animation()
    {
        if (!nightMode)
        {
            ColorChange(currentColor, dayColor, 100, true);
        }
        else
        {
            Color animationColor = WHITE;
            
            // Star Glows
            if (switchDirectionFlag) // Glow Bright
            {
                starTime += speed;
                animationColor = NewColor(animationColor, 1.0f);
            }
            else // Die Down
            {
                starTime -= speed;
                animationColor = NewColor(animationColor, 0.0f);
            }

            // Reverse Glow Direction
            if (starTime >= 1) 
            {
                switchDirectionFlag = false;
            }
            else if (starTime <= 0)
            {
                switchDirectionFlag = true;
            }
            
            ColorChange(currentColor, animationColor, 100, true);
        }
        

    }

    void Update()
    {
        glPushMatrix();

        Animation();
        Draw();

        glPopMatrix();
    }
};

// -------------------------------- Sky ------------------------------------- //
class Sky
{
private:
    Color currentColor;
    Color dayColor;
    Color nightColor;

    float transitionSpeed;

    void Draw()
    {
        Point upperLeft = NewPos(-screenWidth, screenHeight);
        Point upperRight = NewPos(screenWidth, screenHeight);
        Point lowerLeft = NewPos(-screenWidth, -screenHeight);
        Point lowerRight = NewPos(screenWidth, -screenHeight);

        QuadSize quadSize = newQuadSize(lowerLeft, lowerRight, upperLeft, upperRight);

        drawQuadGradient(quadSize, newQuadColors(SKYBOTTOM, SKYBOTTOM, currentColor, currentColor));
    }
public:

    Sky(float transitionSpeed)
    {
        currentColor = SKYTOP;
        dayColor = SKYTOP;
        nightColor = BLACK;
        this->transitionSpeed = transitionSpeed * 100;
    }

    void NightMode()
    {
        if (!pause) 
        {
            if (!nightMode)
            {
                ColorChange(currentColor, dayColor, transitionSpeed);
            }
            else
            {
                ColorChange(currentColor, nightColor, transitionSpeed);
            }
        }
    }

    void Update()
    {
        glPushMatrix();

        NightMode();
        Draw();

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
        rotation(0.0f) {}

    void rotate(float speed) {
        rotation += speed;
        if (rotation > 360.0f) rotation -= 360.0f;
    }
};

void drawHollowCenterGradient(Point pos, float radius, float thickness, Color topColor, Color bottomColor) {
    glLineWidth(thickness);
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < 100; i++) {
        float theta = 2.0f * PI * float(i) / 100.0f;
        float t = (sinf(theta) + 1.0f) / 2.0f;
        glColor4f(
            bottomColor.r + t * (topColor.r - bottomColor.r),
            bottomColor.g + t * (topColor.g - bottomColor.g),
            bottomColor.b + t * (topColor.b - bottomColor.b),
            1.0f
        );
        glVertex2f(pos.x + radius * cosf(theta), pos.y + radius * sinf(theta));
    }
    glEnd();
}

void drawCars(Point pos, float size, Color mainColor) {
    // Body
    drawQuad(newQuadSize(
        NewPos(pos.x - size, pos.y - size),
        NewPos(pos.x + size, pos.y - size),
        NewPos(pos.x - size, pos.y - (size * 0.2f)),
        NewPos(pos.x + size, pos.y - (size * 0.2f))
    ), mainColor);

    // Glass
    drawQuad(newQuadSize(
        NewPos(pos.x - size, pos.y - (size * 0.2f)),
        NewPos(pos.x + size, pos.y - (size * 0.2f)),
        NewPos(pos.x - size, pos.y + (size * 0.5f)),
        NewPos(pos.x + size, pos.y + (size * 0.5f))
    ), NewColor(0.8f, 0.95f, 1.0f, 0.8f)); // Semi-transparent glass

    // Roof
    Color roofColor = NewColor(mainColor.r * 0.8f, mainColor.g * 0.8f, mainColor.b * 0.8f);
    drawQuad(newQuadSize(
        NewPos(pos.x - (size * 1.1f), pos.y + (size * 0.5f)),
        NewPos(pos.x + (size * 1.1f), pos.y + (size * 0.5f)),
        NewPos(pos.x - size, pos.y + (size * 0.8f)),
        NewPos(pos.x + size, pos.y + (size * 0.8f))
    ), roofColor);

    // Hanger arm
    glLineWidth(3.0f);
    glBegin(GL_LINES);
    glColor4f(0.2f, 0.2f, 0.2f, 1.0f); // Dark gray metal
    glVertex2f(pos.x, pos.y + (size * 0.8f));
    glVertex2f(pos.x, pos.y + (size * 1.5f));
    glEnd();
}


void drawFerris(FerrisWheel& fw) {
    // Pallete
    Color carPalette[] = { RED, GREEN, YELLOW, CYAN };
    int numColors = 4;

    // Rims
    Color shineBlue = NewColor(0.2f, 0.6f, 1.0f);
    Color darkBlue = NewColor(0.0f, 0.1f, 0.5f);

    drawHollowCenterGradient(fw.center, fw.radius, 6.0f, shineBlue, darkBlue);
    drawHollowCenterGradient(fw.center, fw.radius * 0.94f, 4.0f, shineBlue, darkBlue);

    // Spokes and Gondolas
    for (int i = 0; i < fw.numCars; i++) {
        float angle = (2.0f * PI * i / fw.numCars) + (fw.rotation * PI / 180.0f);
        float endX = fw.center.x + fw.radius * cos(angle);
        float endY = fw.center.y + fw.radius * sin(angle);

        // Spokes
        glLineWidth(2.0f);
        glBegin(GL_LINES);
        glColor4f(0.1f, 0.1f, 0.1f, 0.5f); // Fade near center
        glVertex2f(fw.center.x, fw.center.y);
        glColor4f(0.4f, 0.4f, 0.4f, 0.8f); // Brighter near rim
        glVertex2f(endX, endY);
        glEnd();

        // Pick a color from the pallete
        Color currentColor = carPalette[i % numColors];

        // Draw Car ad make sure they hang by tip
        drawCars(NewPos(endX, endY - 45), 25, currentColor);
    }

    // Center hub
    drawBasicShape(fw.center, 35, 30, NewColor(0.15f, 0.15f, 0.15f)); // Outer casing
    drawBasicShape(fw.center, 25, 20, NewColor(0.4f, 0.4f, 0.4f));    // Metal bolt
    drawBasicShape(fw.center, 10, 15, shineBlue);                   // Center cap
}

void drawFerrisBase(Point center, float height, Color color) {
    float spread = 180.0f;

    Color lightSide = NewColor(0.3f, 0.3f, 0.3f);
    Color darkSide = NewColor(0.1f, 0.1f, 0.1f);

    // Left beam
    drawQuadGradient(
        newQuadSize(
            NewPos(center.x - spread - 10, center.y - height), // LL
            NewPos(center.x - spread + 10, center.y - height), // LR
            NewPos(center.x - 10, center.y),                   // UL
            NewPos(center.x + 10, center.y)                    // UR
        ),
        newQuadColors(darkSide, darkSide, lightSide, lightSide)
    );

    // Right beam
    drawQuadGradient(
        newQuadSize(
            NewPos(center.x + spread - 10, center.y - height), // LL
            NewPos(center.x + spread + 10, center.y - height), // LR
            NewPos(center.x - 10, center.y),                   // UL
            NewPos(center.x + 10, center.y)                    // UR
        ),
        newQuadColors(darkSide, darkSide, lightSide, lightSide)
    );
}

FerrisWheel ferris(NewPos(0, 50), 300.0f, 8, BLUE);



void animateFerris() {
    ferris.rotate(1.0f * speedMultiplier / 10.0f);
}

// ---------------------------------------- Object Creation List --------------------------------------- //
Sky mainSky(1);
ParticleGroup<CloudParticle> clouds(NewPos(-screenWidth - 100, screenHeight - 200), 10000);
ParticleGroup<StarParticle> stars(NewPos(0, 0), 1000, 0, 0.01f);
Sun sun(NewPos(1000, 500),100, 0.01f);
Moon moon(NewPos(-1000, 500), 50, 0.01f);

// ----------------------------------- Display Function --> Represent Draw Order ------------------------------------ //
void display() {
    glClear(GL_COLOR_BUFFER_BIT);

	// Draw Sky
	mainSky.Update();
    stars.Update();
    sun.Update();
    moon.Update();
    clouds.Update();

    // Create Ground
    Ground(NewPos(0, -520));

    // Create Fence and Pickets
    Fence(NewPos(4, -250));

    int picketSpread = 125;
    int picketAmount = 20;
    for (int i = 0; i < picketAmount; i++)
    {
        Pickets(NewPos(-1200 + (picketSpread * i), -250));
    }

    //Ferris Wheel
    drawFerrisBase(ferris.center, 450, BLACK);

    drawFerris(ferris);

    // Create Tree
    CreateTree(NewPos(-850, 50));

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
    
    glutSwapBuffers();
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

    glEnable(GL_LINE_SMOOTH);
    glEnable(GL_POLYGON_SMOOTH);
    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
    glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);
}

// Will run code every 60 FPS
void update() {
    if (!pause) {
        animateFerris();

    }
}

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
        case '+':
            if (speedMultiplier < 10) 
            {
                speedMultiplier += 1;
            }
            
            break;
        case '-':
            if (speedMultiplier > 1)
            {
                speedMultiplier -= 1;
            }
            break;

        case 'p':
            pause = !pause; // Reverse Pause Boolean
            break;

        case 'n':
            if (pause) return;
            nightMode = !nightMode;
            break;

        case 27:
            exit(0);
            break;
    }
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
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_MULTISAMPLE);
    glutInitWindowSize(screenWidth, screenHeight);
    glutCreateWindow("Ferris Wheel");

    // Run Graphics
    init();

    // Inputs
    glutKeyboardFunc(keyboard);

    glutDisplayFunc(display);
    glutTimerFunc(0, timer, 0);
    glutMainLoop();
    return 0;
}
