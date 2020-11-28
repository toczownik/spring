#include "GL/gl.h"
#include "GL/glu.h"
#include "GL/glut.h"
#include <cmath>

#define ZOOM_INCREASE 0.1
#define ROTATION 1
#define CONST 0.2

int currentColor = 0;
float zoom = -20;
int movementX = 0;
int movementY = 0;

void nextColor() {
    currentColor += 1;
    currentColor = currentColor % 6;
    switch (currentColor) {
        case 0:
            glColor4f(1.0f, 0.0f, 0.0f, 1.0f);
            break;
        case 1:
            glColor4f(0.0f, 1.0f, 0.0f, 1.0f);
            break;
        case 2:
            glColor4f(0.0f, 0.0f, 1.0f, 1.0f);
            break;
        case 3:
            glColor4f(0.0f, 1.0f, 1.0f, 1.0f);
            break;
        case 4:
            glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
            break;
        case 5:
            glColor4f(1.0f, 1.0f, 0.0f, 1.0f);
            break;
        default:
            break;
    }
}

GLfloat x(float t, float u) {
    return cos(t) * (3 + cos(u));
}

GLfloat y(float t, float u) {
    return sin(t) * (3 + cos(u));
}

GLfloat z(float t, float u) {
    return 0.6 * t + sin(u) - 6;
}

void drawSpiral() {
    for (float t = 0; t < 8 * M_PI; t += CONST) {
        glBegin(GL_QUAD_STRIP);
        for (float u = 0; u < 2 * M_PI; u += 0.1) {
            //nextColor();
            glVertex3f(x(t, u), z(t, u), y(t, u));
            glVertex3f(x(t, u + CONST), z(t, u + CONST), y(t, u + CONST));
            glVertex3f(x(t + CONST, u), z(t + CONST, u), y(t + CONST, u));
            glVertex3f(x(t + CONST, u + CONST), z(t + CONST, u + CONST), y(t + CONST, u + CONST));
        }
        glEnd();
    }
}

void timer(int) {
    glutPostRedisplay();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0.0f, 0.0f, zoom);
    glRotatef(movementX, 1.0, 0.0, 0.0);
    glRotatef(movementY, 0.0, 1.0, 0.0);
    drawSpiral();
    glFlush();
    glutTimerFunc(10, timer, 0);
}

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
        case 'a':
            movementY -= ROTATION;
            break;
        case 'w':
            movementX -= ROTATION;
            break;
        case 'd':
            movementY += ROTATION;
            break;
        case 's':
            movementX += ROTATION;
            break;
        case 'z':
            zoom -= ZOOM_INCREASE;
            break;
        case 'x':
            if (zoom < -1) {
                zoom += ZOOM_INCREASE;
            }
            break;
        default:
            break;
    }
    movementX = movementX % 360;
    movementY = movementY % 360;
}

void init() {
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glViewport(0, 500, 500, 500);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60, 1, 1, 40.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glDrawBuffer(GL_BACK);
    glEnable(GL_DEPTH_TEST);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("My window");
    init();
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}