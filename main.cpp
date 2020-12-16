#include "GL/gl.h"
#include "GL/glu.h"
#include "GL/glut.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <cmath>
#include <iostream>

#define ZOOM_INCREASE 0.1
#define ROTATION 1
#define CONST 0.2

float zoom = -20;
int movementX = 0;
int movementY = 0;
float stretch = -0.6;
float stretchChange = 0.01;
unsigned int textures[2];

GLfloat x(float t, float u) {
    return cos(t) * (3 + cos(u));
}

GLfloat y(float t, float u) {
    return sin(t) * (3 + cos(u));
}

GLfloat z(float t, float u) {
    return stretch * t + sin(u) + 7;
}

void drawSpiral() {
    glBindTexture(GL_TEXTURE_2D, textures[1]);
    for (float t = 0; t < 8 * M_PI; t += CONST) {
        glBegin(GL_QUAD_STRIP);
        for (float u = 0; u < 2 * M_PI; u += 0.1) {
            glTexCoord2f(0.0, 0.0);
            glVertex3f(x(t, u), z(t, u), y(t, u));
            glTexCoord2f(0.0, 1.0);
            glVertex3f(x(t, u + CONST), z(t, u + CONST), y(t, u + CONST));
            glTexCoord2f(1.0, 1.0);
            glVertex3f(x(t + CONST, u), z(t + CONST, u), y(t + CONST, u));
            glTexCoord2f(1.0, 0.0);
            glVertex3f(x(t + CONST, u + CONST), z(t + CONST, u + CONST), y(t + CONST, u + CONST));
        }
        glEnd();
    }
}

void drawBottom() {
    GLUquadric* quad;
    quad = gluNewQuadric();
    glBindTexture(GL_TEXTURE_2D, textures[1]);
    gluQuadricTexture(quad, true);
    glPushMatrix();
    glTranslatef(x(8 * M_PI + CONST, 2 * M_PI + CONST) - 4,
                 z(8 * M_PI + CONST, 2 * M_PI + CONST),
                 y(8 * M_PI + CONST, 2 * M_PI + CONST));
    glPushMatrix(); //horizontal piece
    glRotatef(90, 0.0, 1.0, 0.0);
    gluCylinder(quad, 1, 1, 3, 50, 20);
    gluSphere(quad, 1, 100, 20); //connection
    glTranslatef(0, 0, 3);
    gluSphere(quad, 1, 100, 20); //connection
    glPopMatrix();

    glPushMatrix(); //vertical piece
    glRotatef(90, 1.0, 0.0, 0.0);
    gluCylinder(quad, 1, 1, 3, 50, 20);
    glPopMatrix();

    glPushMatrix(); //ball
    glBindTexture(GL_TEXTURE_2D, textures[0]);
    gluQuadricTexture(quad, true);
    glTranslatef(0, -5, 0);
    glRotated(90, -1, 0, 0);
    gluSphere(quad, 4, 100, 20);
    glPopMatrix();
    glPopMatrix();
}

void drawTop() {
    glBindTexture(GL_TEXTURE_2D, textures[1]);
    GLUquadric* quad;
    quad = gluNewQuadric();
    gluQuadricTexture(quad, true);
    glPushMatrix();
    glRotatef(90, 0.0, 1.0, 0.0);
    gluCylinder(quad, 1, 1, 3, 50, 20); //horizontal
    gluSphere(quad, 1, 100, 20); //connection

    glPushMatrix();
    glTranslatef(0, 0, 3);
    gluSphere(quad, 1, 100, 20); //connection
    glPopMatrix();

    glRotatef(-90, 1.0, 0.0, 0.0);
    gluCylinder(quad, 1, 1, 3, 50, 20); //vertical
    glPopMatrix();
}

void drawCuboid() {
    glBindTexture(GL_TEXTURE_2D, textures[0]);
    glPushMatrix();
    glBegin(GL_POLYGON); // Top face (y = 1.0f)
    glTexCoord2f(0.0, 0.0);
    glVertex3f(3.0f, 3.0f, -3.0f);
    glTexCoord2f(0.0, 1.0);
    glVertex3f(-3.0f, 3.0f, -3.0f);
    glTexCoord2f(1.0, 1.0);
    glVertex3f(-3.0f, 3.0f, 3.0f);
    glTexCoord2f(1.0, 0.0);
    glVertex3f(3.0f, 3.0f, 3.0f);
    glEnd();

    glBegin(GL_POLYGON); // Bottom face (y = -1.0f)
    glTexCoord2f(0.0, 0.0);
    glVertex3f(3.0f, 2.0f, -3.0f);
    glTexCoord2f(0.0, 1.0);
    glVertex3f(-3.0f, 2.0f, -3.0f);
    glTexCoord2f(1.0, 1.0);
    glVertex3f(-3.0f, 2.0f, 3.0f);
    glTexCoord2f(1.0, 0.0);
    glVertex3f(3.0f, 2.0f, 3.0f);
    glEnd();

    glBegin(GL_POLYGON); // Front face  (z = 1.0f)
    glTexCoord2f(0.0, 0.0);
    glVertex3f(3.0f, 3.0f, 3.0f);
    glTexCoord2f(0.0, 1.0);
    glVertex3f(-3.0f, 3.0f, 3.0f);
    glTexCoord2f(1.0, 1.0);
    glVertex3f(-3.0f, 2.0f, 3.0f);
    glTexCoord2f(1.0, 0.0);
    glVertex3f(3.0f, 2.0f, 3.0f);
    glEnd();

    glBegin(GL_POLYGON); // Back face (z = -1.0f)
    glTexCoord2f(0.0, 0.0);
    glVertex3f(3.0f, 2.0f, -3.0f);
    glTexCoord2f(0.0, 1.0);
    glVertex3f(-3.0f, 2.0f, -3.0f);
    glTexCoord2f(1.0, 1.0);
    glVertex3f(-3.0f, 3.0f, -3.0f);
    glTexCoord2f(1.0, 0.0);
    glVertex3f(3.0f, 3.0f, -3.0f);
    glEnd();

    glBegin(GL_POLYGON); // Left face (x = -1.0f)
    glTexCoord2f(0.0, 0.0);
    glVertex3f(-3.0f, 3.0f, 3.0f);
    glTexCoord2f(0.0, 1.0);
    glVertex3f(-3.0f, 3.0f, -3.0f);
    glTexCoord2f(1.0, 1.0);
    glVertex3f(-3.0f, 2.0f, -3.0f);
    glTexCoord2f(1.0, 0.0);
    glVertex3f(-3.0f, 2.0f, 3.0f);
    glEnd();

    glBegin(GL_POLYGON); // Right face (x = 1.0f)
    glTexCoord2f(0.0, 0.0);
    glVertex3f(3.0f, 3.0f, -3.0f);
    glTexCoord2f(0.0, 1.0);
    glVertex3f(3.0f, 3.0f, 3.0f);
    glTexCoord2f(1.0, 1.0);
    glVertex3f(3.0f, 2.0f, 3.0f);
    glTexCoord2f(1.0, 0.0);
    glVertex3f(3.0f, 2.0f, -3.0f);
    glEnd();
    glPopMatrix();
}

void timer(int) {
    stretch -= stretchChange;
    if (stretch < -0.7 || stretch > -0.4) {
        stretchChange = -stretchChange;
    }
    glutPostRedisplay();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0.0f, 0.0f, zoom);
    glRotatef(movementX, 1.0, 0.0, 0.0);
    glRotatef(movementY, 0.0, 1.0, 0.0);
    glPushMatrix();
    glTranslatef(0, 7, 0);
    drawCuboid();
    drawTop();
    glPopMatrix();
    drawSpiral();
    drawBottom();

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

void initTexture(const char* imagePath) {
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    int width;
    int height;
    int nrChannels;
    unsigned char* image = stbi_load(imagePath, &width, &height, &nrChannels, 0);
    if (image) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
        gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, width, height, GL_RGB, GL_UNSIGNED_BYTE, image);
    }
    else {
        std::cout << "Failed to load the texture: " << imagePath << std::endl;
    }
    stbi_image_free(image);
}

void initTextures() {
    glBindTexture(GL_TEXTURE_2D, textures[0]);
    initTexture("../textures/wood.jpg");
    glBindTexture(GL_TEXTURE_2D, textures[1]);
    initTexture("../textures/metal.jpeg");
}

void init() {
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glViewport(0, 500, 500, 500);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60, 1, 1, 100.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glDrawBuffer(GL_BACK);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);
    glGenTextures(2, textures);
    initTextures();
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