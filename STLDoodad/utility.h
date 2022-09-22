#ifndef UTILITY_H
#define UTILITY_H

#include <string>
#include <vector>
#include "triangle.h";

void normalizeAngle(int &angle);
Triangle normalizeTriangle(Triangle triangle);
std::vector<std::string> tokenize(std::string str, char delimiter);
double mantissaExpToDouble(std::string str);
bool essentiallyEqual(double a, double b, double epsilon);
bool essentiallyEqual(double* a, double* b, double epsilon);
void calculateCrossProduct(double* v1, double* v2, double* cp);
double calculateVectorMagnitude(double* v);
void normalizeVector(double* v);
void calculateNormal(double* v1, double* v2, double* v3, double* vn);

#endif // UTILITY_H
