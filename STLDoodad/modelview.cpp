#include <QOpenGLFunctions>
#include <QOpenGLWidget>
#include <QtWidgets>
#include "mainwindow.h"
#include "modelview.h"
#include "utility.h"

ModelView::ModelView(QWidget *parent) : QGLWidget(QGLFormat(QGL::SampleBuffers), parent), QOpenGLFunctions() {
}
void ModelView::initializeGL() {
    initializeOpenGLFunctions();
    qglClearColor(Qt::black);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    static GLfloat lightPosition[4] = { 0, 0, 10, 1.0 };
    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
}
void ModelView::paintGL() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glTranslatef(0.0, 0.0, -10.0);
    glRotatef(xRot / 10.0, 1.0, 0.0, 0.0);
    glRotatef(yRot / 10.0, 0.0, 1.0, 0.0);
    glRotatef(zRot / 10.0, 0.0, 0.0, 1.0);
    draw();
}
void ModelView::resizeGL(int width, int height) {
    int side = qMin(width, height);
    glViewport((width - side) / 2, (height - side) / 2, side, side);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-100.0, 100.0, -100.0, 100.0, -200.0, 200.0);
    glMatrixMode(GL_MODELVIEW);
}
void ModelView::mousePressEvent(QMouseEvent *event) {
    lastPos = event->pos();
}
void ModelView::mouseMoveEvent(QMouseEvent *event) {
    int dx = event->x() - lastPos.x();
    int dy = event->y() - lastPos.y();

    if (event->buttons() &Qt::LeftButton) {
        setXRotation(xRot + 8 * dy);
        setYRotation(yRot + 8 * dx);
    } else if (event->buttons() &Qt::RightButton) {
        setXRotation(xRot + 8 * dy);
        setZRotation(zRot + 8 * dx);
    }
    lastPos = event->pos();
}
void ModelView::setXRotation(int angle) {
    normalizeAngle(angle);
    if (angle != xRot) {
        xRot = angle;
        updateGL();
    }
}
void ModelView::setYRotation(int angle) {
    normalizeAngle(angle);
    if (angle != yRot) {
        yRot = angle;
        updateGL();
    }
}
void ModelView::setZRotation(int angle) {
    normalizeAngle(angle);
    if (angle != zRot) {
        zRot = angle;
        updateGL();
    }
}
void ModelView::draw() {
    std::vector<Triangle> triangles = parent->getTriangles();
    for (int i = 0; i < triangles.size(); i++) {
        double* fn = triangles[i].getNormal();
        double* v1 = triangles[i].getV1();
        double* v2 = triangles[i].getV2();
        double* v3 = triangles[i].getV3();
        qglColor(Qt::red);
        glBegin(GL_TRIANGLES);
            glNormal3f(fn[0], fn[1], fn[2]);
            glVertex3f(v1[0], v1[1], v1[2]);
            glVertex3f(v2[0], v2[1], v2[2]);
            glVertex3f(v3[0], v3[1], v3[2]);
        glEnd();
    }
}
