#include <iostream>
#include <vector>
#include "triangle.h"
#include "utility.h"

Triangle::Triangle() {
    normal = new double[3];
    v1 = new double[3];
    v2 = new double[3];
    v3 = new double[3];
}
Triangle::Triangle(const Triangle& triangle) {
    normal = new double[3];
    v1 = new double[3];
    v2 = new double[3];
    v3 = new double[3];
    for (int i = 0; i < 3; i++) {
        normal[i] = triangle.normal[i];
        v1[i] = triangle.v1[i];
        v2[i] = triangle.v2[i];
        v3[i] = triangle.v3[i];
    }
}
Triangle::~Triangle() {
    delete[] normal;
    delete[] v1;
    delete[] v2;
    delete[] v3;
}
Triangle& Triangle::operator=(const Triangle& triangle) {
    if (this == &triangle)
        return *this;
    for (int i = 0; i < 3; i++) {
        normal[i] = triangle.normal[i];
        v1[i] = triangle.v1[i];
        v2[i] = triangle.v2[i];
        v3[i] = triangle.v3[i];
    }
    return *this;
}
bool Triangle::operator==(const Triangle& triangle) {
    bool identical = true;
    double epsilon = 0.001;
    if (!essentiallyEqual(normal, triangle.normal, epsilon))
        identical = false;
    if (!essentiallyEqual(v1, triangle.v1, epsilon))
        identical = false;
    if (!essentiallyEqual(v2, triangle.v2, epsilon))
        identical = false;
    if (!essentiallyEqual(v2, triangle.v3, epsilon))
        identical = false;
    return identical;
}
bool Triangle::operator!=(const Triangle& triangle) {
    bool identical = true;
    double epsilon = 0.001;
    if (!essentiallyEqual(normal, triangle.normal, epsilon))
        identical = false;
    if (!essentiallyEqual(v1, triangle.v1, epsilon))
        identical = false;
    if (!essentiallyEqual(v2, triangle.v2, epsilon))
        identical = false;
    if (!essentiallyEqual(v2, triangle.v3, epsilon))
        identical = false;
    return !identical;
}
double* Triangle::getNormal() {
    return normal;
}

double* Triangle::getV1() {
    return v1;
}

double* Triangle::getV2() {
    return v2;
}

double* Triangle::getV3() {
    return v3;
}

void Triangle::setNormal(double* normal) {
    for (int i = 0; i < 3; i++) {
        this->normal[i] = normal[i];
    }
}

void Triangle::setV1(double* v1) {
    for (int i = 0; i < 3; i++) {
        this->v1[i] = v1[i];
    }
}

void Triangle::setV2(double* v2) {
    for (int i = 0; i < 3; i++) {
        this->v2[i] = v2[i];
    }
}

void Triangle::setV3(double* v3) {
    for (int i = 0; i < 3; i++) {
        this->v3[i] = v3[i];
    }
}
void Triangle::print() {
    std::cout << "Facet Normal: ";
    for (int i = 0; i < 3; i++) {
        std::cout << normal[i] << " ";
    }
    std::cout << "\n";
    std::cout << "V1: ";
    for (int i = 0; i < 3; i++) {
        std::cout << v1[i] << " ";
    }
    std::cout << "\n";
    std::cout << "V2: ";
    for (int i = 0; i < 3; i++) {
        std::cout << v2[i] << " ";
    }
    std::cout << "\n";
    std::cout << "V3: ";
    for (int i = 0; i < 3; i++) {
        std::cout << v3[i] << " ";
    }
    std::cout << "\n";
}
