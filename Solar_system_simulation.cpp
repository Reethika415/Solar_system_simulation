#include <GL/glut.h>
#include <math.h>
#include <stdlib.h>

// GLOBAL VARIABLES
float angle = 0.0;
float speed = 0.5;
float meteorX = -1.0;

// PLANET STRUCT
struct Planet {
    float distance;
    float size;
    float speed;
    float r, g, b;
};

Planet planets[8];

// INITIALIZE PLANETS
void initPlanets() {
    planets[0] = {0.2, 0.02, 2.5, 0.7, 0.7, 0.7}; // Mercury
    planets[1] = {0.3, 0.03, 2.0, 1.0, 0.5, 0.2}; // Venus
    planets[2] = {0.4, 0.04, 1.6, 0.0, 0.5, 1.0}; // Earth
    planets[3] = {0.5, 0.03, 1.3, 1.0, 0.3, 0.0}; // Mars
    planets[4] = {0.65, 0.06, 1.0, 1.0, 0.8, 0.5}; // Jupiter
    planets[5] = {0.8, 0.05, 0.8, 1.0, 1.0, 0.6}; // Saturn
    planets[6] = {0.95, 0.04, 0.6, 0.5, 1.0, 1.0}; // Uranus
    planets[7] = {1.1, 0.04, 0.5, 0.2, 0.2, 1.0}; // Neptune
}

// DRAW CIRCLE
void drawCircle(float r) {
    glBegin(GL_POLYGON);
    for (int i = 0; i < 100; i++) {
        float theta = 2 * 3.1416 * i / 100;
        glVertex2f(r * cos(theta), r * sin(theta));
    }
    glEnd();
}

// DRAW ORBIT
void drawOrbit(float r) {
    glColor3f(1, 1, 1);
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < 100; i++) {
        float theta = 2 * 3.1416 * i / 100;
        glVertex2f(r * cos(theta), r * sin(theta));
    }
    glEnd();
}

// DRAW STARS
void drawStars() {
    glPointSize(2);
    glBegin(GL_POINTS);
    for (int i = 0; i < 150; i++) {
        float x = (rand() % 200 - 100) / 100.0;
        float y = (rand() % 200 - 100) / 100.0;
        glVertex2f(x, y);
    }
    glEnd();
}

// COMET
void drawComet() {
    float x = cos(angle * 0.02);
    float y = sin(angle * 0.02) * 0.5;

    glPushMatrix();
    glTranslatef(x, y, 0);

    glColor3f(1, 1, 1);
    drawCircle(0.025);

    for (int i = 0; i < 4; i++) {
        glTranslatef(-0.02, 0, 0);
        drawCircle(0.008);
    }

    glPopMatrix();
}

// DRAW PLANETS
void drawPlanets() {
    for (int i = 0; i < 8; i++) {
        glPushMatrix();

        glRotatef(angle * planets[i].speed, 0, 0, 1);
        glTranslatef(planets[i].distance, 0, 0);

        // EARTH
        if (i == 2) {
            glColor3f(0.0, 0.5, 1.0);
            drawCircle(planets[i].size);

            glColor3f(0.0, 0.8, 0.0);
            glBegin(GL_POLYGON);
            for (int j = 0; j < 30; j++) {
                float theta = 2 * 3.1416 * j / 30;
                glVertex2f(0.015 * cos(theta), 0.015 * sin(theta));
            }
            glEnd();
        }
        else {
            glColor3f(planets[i].r, planets[i].g, planets[i].b);
            drawCircle(planets[i].size);
        }

        // SATURN RINGS
        if (i == 5) {
            glColor3f(1, 1, 1);
            glBegin(GL_LINE_LOOP);
            for (int k = 0; k < 100; k++) {
                float theta = 2 * 3.1416 * k / 100;
                glVertex2f(0.09 * cos(theta), 0.04 * sin(theta));
            }
            glEnd();
        }

        // MOON + SATELLITES
        if (i == 2) {
            // Moon
            glPushMatrix();
            glRotatef(angle * 3, 0, 0, 1);
            glTranslatef(0.07, 0, 0);
            glColor3f(1, 1, 1);
            drawCircle(0.015);
            glPopMatrix();

            // Satellites
            for (int s = 0; s < 3; s++) {
                glPushMatrix();
                glRotatef(angle * (4 + s), 0, 0, 1);
                glTranslatef(0.1 + 0.03 * s, 0, 0);
                glColor3f(0.8, 0.8, 0.8);
                drawCircle(0.01);
                glPopMatrix();
            }
        }

        glPopMatrix();
    }
}

// DISPLAY
void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    drawStars();

    // SUN
    glColor3f(1, 1, 0);
    drawCircle(0.12);

    // ORBITS
    for (int i = 0; i < 8; i++) {
        drawOrbit(planets[i].distance);
    }

    drawPlanets();
    drawComet();

    glutSwapBuffers();
}

// UPDATE
void update(int value) {
    angle += speed;
    if (angle > 360) angle = 0;

    glutPostRedisplay();
    glutTimerFunc(16, update, 0);
}

// KEYBOARD
void keyboard(unsigned char key, int x, int y) {
    if (key == '+') speed += 0.2;
    if (key == '-') speed -= 0.2;
    if (key == 's') speed = 0;
    if (key == 'r') speed = 0.5;
    if (key == 27) exit(0);
}

// RESHAPE (IMPORTANT)
void reshape(int w, int h) {
    glViewport(0, 0, w, h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    float aspect = (float)w / h;

    if (aspect >= 1.0)
        gluOrtho2D(-1.5 * aspect, 1.5 * aspect, -1.5, 1.5);
    else
        gluOrtho2D(-1.5, 1.5, -1.5 / aspect, 1.5 / aspect);

    glMatrixMode(GL_MODELVIEW);
}

// INIT
void init() {
    glClearColor(0, 0, 0, 1);
    initPlanets();
}

// MAIN
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(800, 800);
    glutCreateWindow("Space Simulation");

    init();

    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutTimerFunc(0, update, 0);
    glutReshapeFunc(reshape);

    glutMainLoop();
    return 0;
}