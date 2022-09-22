#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "triangle.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT
private:
    Ui::MainWindow *ui;
    std::vector<Triangle> triangles;
    std::string filePath;
    std::string fileName;
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    std::vector<Triangle> getTriangles();
    std::string getFilePath();
    std::string getFileName();
    void setTriangles(std::vector<Triangle> triangles);
    void setFilePath(std::string filePath);
    void setFileName(std::string fileName);

    void getPathToSTL();
    void importSTL();
    void logTriangles();
    void checkDuplicates();
    void checkNeighbors();
    void checkFlipped();
private slots:
    void on_actionOpen_triggered();
    void on_logFileContentsButton_pressed();
    void on_checkDuplicateButton_pressed();
    void on_checkNeighborsButton_pressed();
    void on_checkFlippedButton_pressed();
    void on_logBox_textChanged();
};

#endif // MAINWINDOW_H
