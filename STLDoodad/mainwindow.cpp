#include <fstream>
#include <iostream>
#include <QFileDialog>
#include "mainwindow.h"
#include "triangle.h"
#include "ui_mainwindow.h"
#include "utility.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    ui->modelView->parent = this;
}
MainWindow::~MainWindow() {
    delete ui;
}
std::vector<Triangle> MainWindow::getTriangles() {
    return triangles;
}
std::string MainWindow::getFilePath() {
    return filePath;
}
std::string MainWindow::getFileName() {
    return fileName;
}
void MainWindow::setTriangles(std::vector<Triangle> triangles) {
    this->triangles = triangles;
}
void MainWindow::setFilePath(std::string filePath) {
    this->filePath = filePath;
}
void MainWindow::setFileName(std::string fileName) {
    this->fileName = fileName;
}
void MainWindow::getPathToSTL() {
    QString path = QFileDialog::getOpenFileName(this, tr("Open STL"), "/home/", tr("STL Files (*.stl)"));
    if (path != NULL) {
        QFileInfo info(path);
        filePath = path.toStdString();
        fileName = info.baseName().toStdString();
    }
}
void MainWindow::importSTL() {
    std::ifstream input;
    input.open(filePath);
    if (input.is_open()) {
        Triangle tri = Triangle();
        int counter = 0;
        std::string str;
        while (std::getline(input, str)) {
            if (str.find("facet normal") != std::string::npos) {
                std::vector<std::string> tokens = tokenize(str, ' ');
                double n1 = tokens[2].find("e") == std::string::npos ? std::stod(tokens[2]) : mantissaExpToDouble(tokens[2]);
                double n2 = tokens[3].find("e") == std::string::npos ? std::stod(tokens[3]) : mantissaExpToDouble(tokens[3]);
                double n3 = tokens[4].find("e") == std::string::npos ? std::stod(tokens[4]) : mantissaExpToDouble(tokens[4]);
                double normal[3] = { n1, n2, n3 };
                tri.setNormal(normal);
            }
            if (str.find("vertex") != std::string::npos) {
                std::vector<std::string> tokens = tokenize(str, ' ');
                double vx = tokens[1].find("e") == std::string::npos ? std::stod(tokens[1]) : mantissaExpToDouble(tokens[1]);
                double vy = tokens[2].find("e") == std::string::npos ? std::stod(tokens[2]) : mantissaExpToDouble(tokens[2]);
                double vz = tokens[3].find("e") == std::string::npos ? std::stod(tokens[3]) : mantissaExpToDouble(tokens[3]);
                double v[3] = { vx, vy, vz };
                switch (counter) {
                case 0:
                    tri.setV1(v);
                    counter++;
                    break;
                case 1:
                    tri.setV2(v);
                    counter++;
                    break;
                case 2:
                    tri.setV3(v);
                    counter = 0;
                    triangles.push_back(tri);
                    break;
                }
            }
        }
    }
    if (filePath != "")
        ui->logBox->insertPlainText(QString::fromStdString(filePath) + " loaded successfully.\n");
}
void MainWindow::logTriangles() {
    for (int i = 0; i < triangles.size(); i++) {
        ui->logBox->insertPlainText("#" + QString::number(i) + "\n");
        ui->logBox->insertPlainText("\tFacet Normal: ");
        for (int j = 0; j < 3; j++) {
            ui->logBox->insertPlainText(QString::number(triangles[i].getNormal()[j]) + " ");
        }
        ui->logBox->insertPlainText("\n\tV1: ");
        for (int j = 0; j < 3; j++) {
            ui->logBox->insertPlainText(QString::number(triangles[i].getV1()[j]) + " ");
        }
        ui->logBox->insertPlainText("\n\tV2: ");
        for (int j = 0; j < 3; j++) {
            ui->logBox->insertPlainText(QString::number(triangles[i].getV2()[j]) + " ");
        }
        ui->logBox->insertPlainText("\n\tV3: ");
        for (int j = 0; j < 3; j++) {
            ui->logBox->insertPlainText(QString::number(triangles[i].getV3()[j]) + " ");
        }
        ui->logBox->insertPlainText("\n");
    }
}
void MainWindow::checkDuplicates() {
    int nDuplicatesFound = 0;
    std::vector<Triangle> duplicates;
    for (int i = 0; i < triangles.size(); i++) {
        for (int j = 0; j < triangles.size(); j++) {
            if (i != j && triangles[i] == triangles[j]) {
                ui->logBox->insertPlainText("The triangle at index " + QString::number(i) + " has a duplicate at index " + QString::number(j) + ".\n");
                triangles.erase(triangles.begin() + j);
                nDuplicatesFound++;
            }
        }
    }
    if (nDuplicatesFound == 0) {
        ui->logBox->insertPlainText(QString::fromStdString(fileName) + ".stl does not contain any duplicate triangles.\n");
    } else {
        ui->logBox->insertPlainText(QString::number(nDuplicatesFound) + " duplicate triangles were found in" + QString::fromStdString(fileName) + ".stl.\n");
    }
}
void MainWindow::checkNeighbors() {
    int nLoners = 0;
    for (int i = 0; i < triangles.size(); i++) {
        int nNeighbors = 0;
        for (int j = 0; j < triangles.size(); j++) {
            if (i != j) {
                bool v1v1Match = true;
                bool v1v2Match = true;
                bool v1v3Match = true;
                double epsilon = 0.001;
                for (int k = 0; k < 3; k++) {
                    if (!essentiallyEqual(triangles[i].getV1()[k], triangles[j].getV1()[k], epsilon))
                        v1v1Match = false;
                    if (!essentiallyEqual(triangles[i].getV1()[k], triangles[j].getV2()[k], epsilon))
                        v1v2Match = false;
                    if (!essentiallyEqual(triangles[i].getV1()[k], triangles[j].getV3()[k], epsilon))
                        v1v3Match = false;
                }
                bool v1Results[3] = { v1v1Match, v1v2Match, v1v3Match };
                int nV1Matches = 0;
                for (int k = 0; k < 3; k++) {
                    if (v1Results[k])
                        nV1Matches++;
                }

                bool v2v1Match = true;
                bool v2v2Match = true;
                bool v2v3Match = true;
                for (int k = 0; k < 3; k++) {
                    if (!essentiallyEqual(triangles[i].getV2()[k], triangles[j].getV1()[k], epsilon))
                        v2v1Match = false;
                    if (!essentiallyEqual(triangles[i].getV2()[k], triangles[j].getV2()[k], epsilon))
                        v2v2Match = false;
                    if (!essentiallyEqual(triangles[i].getV2()[k], triangles[j].getV3()[k], epsilon))
                        v2v3Match = false;
                }
                bool v2Results[3] = { v2v1Match, v2v2Match, v2v3Match };
                int nV2Matches = 0;
                for (int k = 0; k < 3; k++) {
                    if (v2Results[k])
                        nV2Matches++;
                }

                bool v3v1Match = true;
                bool v3v2Match = true;
                bool v3v3Match = true;
                for (int k = 0; k < 3; k++) {
                    if (!essentiallyEqual(triangles[i].getV3()[k], triangles[j].getV1()[k], epsilon))
                        v3v1Match = false;
                    if (!essentiallyEqual(triangles[i].getV3()[k], triangles[j].getV2()[k], epsilon))
                        v3v2Match = false;
                    if (!essentiallyEqual(triangles[i].getV3()[k], triangles[j].getV3()[k], epsilon))
                        v3v3Match = false;
                }
                bool v3Results[3] = { v3v1Match, v3v2Match, v3v3Match };
                int nV3Matches = 0;
                for (int k = 0; k < 3; k++) {
                    if (v3Results[k])
                        nV3Matches++;
                }
                int finalResults[3] = { nV1Matches, nV2Matches, nV3Matches };
                int nSharedVertices = 0;
                for (int k = 0; k < 3; k++) {
                    if (finalResults[k] > 0)
                        nSharedVertices++;
                }
                if (nSharedVertices > 1) {
                    nNeighbors++;
                }
                //ui->logBox->insertPlainText("#" + QString::number(i) + " shares " + QString::number(nSharedVertices) + " vertices with #" + QString::number(j) + ".\n");
            }
        }
        if (nNeighbors == 0) {
            //ui->logBox->insertPlainText("#" + QString::number(i) + " has " + QString::number(nNeighbors) + " neighbors.\n");
            nLoners++;
        }
    }
    if (nLoners == 0) {
        ui->logBox->insertPlainText("All triangles in " + QString::fromStdString(fileName) + ".stl share at least two vertices with another triangle.\n");
    } else {
        ui->logBox->insertPlainText(QString::fromStdString(fileName) + ".stl contains " + QString::number(nLoners) + " triangles which do not share at least two vertices with other triangles.\n");
    }
}
void MainWindow::checkFlipped() {
    int nFlipped = 0;
    for (int i = 0; i < triangles.size(); i++) {
        double* p1 = triangles[i].getV1();
        double* p2 = triangles[i].getV2();
        double* p3 = triangles[i].getV3();
        double* fn = triangles[i].getNormal();
        double cfn[3];
        calculateNormal(p1, p2, p3, cfn);
        bool match = true;
        double epsilon = 0.001;
        for (int j = 0; j < 3; j++) {
            if (!essentiallyEqual(cfn[j], fn[j], epsilon))
                match = false;
        }
        if (!match) {
            nFlipped++;
            //ui->logBox->insertPlainText("Triangle #" + QString::number(i) + " calculated facet normal: " + QString::number(cfn[0]) + ", " + QString::number(cfn[1]) + ", " + QString::number(cfn[2]) + ".\n");
            //ui->logBox->insertPlainText("Triangle #" + QString::number(i) + " actual facet normal: " + QString::number(fn[0]) + ", " + QString::number(fn[1]) + ", " + QString::number(fn[2]) + ".\n");
        }
    }
    if (nFlipped == 0) {
        ui->logBox->insertPlainText(QString::fromStdString(fileName) + ".stl does not contain any flipped triangles.\n");
    } else {
        ui->logBox->insertPlainText(QString::fromStdString(fileName) + ".stl contains " + QString::number(nFlipped) + " flipped triangles.\n");
    }
}
void MainWindow::on_actionOpen_triggered() {
    triangles.clear();
    getPathToSTL();
    importSTL();
}
void MainWindow::on_logFileContentsButton_pressed() {
    logTriangles();
}
void MainWindow::on_checkDuplicateButton_pressed() {
    checkDuplicates();
}
void MainWindow::on_checkNeighborsButton_pressed() {
    checkNeighbors();
}
void MainWindow::on_checkFlippedButton_pressed() {
    checkFlipped();
}
void MainWindow::on_logBox_textChanged() {
    QTextCursor tc = ui->logBox->textCursor();
    tc.setPosition(ui->logBox->document()->characterCount() - 1);
    ui->logBox->setTextCursor(tc);
}

