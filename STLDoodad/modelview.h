#ifndef MODELVIEW_H
#define MODELVIEW_H

#include <QGLWidget>
#include <QOpenGLFunctions>
#include <vector>
#include "mainwindow.h"
#include "triangle.h"

class ModelView : public QGLWidget, protected QOpenGLFunctions {
    Q_OBJECT
private:
    void draw();
    int xRot;
    int yRot;
    int zRot;
    QPoint lastPos;
public:
    explicit ModelView(QWidget *parent = 0);
    MainWindow* parent;
protected:
    void initializeGL() override;
    void paintGL() override;
    void resizeGL(int width, int height) override;

    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;

    void setXRotation(int angle);
    void setYRotation(int angle);
    void setZRotation(int angle);
};

#endif // MODELVIEW_H
