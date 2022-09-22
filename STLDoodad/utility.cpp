#include <iostream>
#include <math.h>
#include <sstream>
#include <string>
#include <vector>
#include "triangle.h"
#include "utility.h"

void normalizeAngle(int &angle) {
    while (angle < 0)
        angle += 360 * 16;
    while (angle > 360)
        angle -= 360 * 16;
}
std::vector<std::string> tokenize(std::string str, char delimiter) {
    std::vector<std::string> tokens;
    std::stringstream ss(str);
    std::string inter;
    while(getline(ss, inter, delimiter)) {
        if (inter != "")
            tokens.push_back(inter);
    }
    return tokens;
}
double mantissaExpToDouble(std::string str) {
    for (int i = 0; i < str.size(); i++) {
        if (str[i] == 'E')
            str[i] = 'e';
    }
    std::vector<std::string> tokens = tokenize(str, 'e');
    double mantissa = std::stod(tokens[0]);
    double exponent = std::stod(tokens[1]);
    return mantissa * std::pow(10, exponent);
}
bool essentiallyEqual(double a, double b, double epsilon) {
    double difference = std::fabs(a - b);
    bool equal = difference < epsilon? true : false;
    return equal;
}
bool essentiallyEqual(double* a, double* b, double epsilon) {
    bool equal = true;
    for (int i = 0; i < 3; i++) {
        double difference = std::fabs(a[i] - b[i]);
        if (difference > epsilon)
            equal = false;
    }
    return equal;
}
void calculateCrossProduct(double* v1, double* v2, double* cp) {
    cp[0] = v1[1] * v2[2] - v1[2] * v2[1];
    cp[1] = v1[2] * v2[0] - v1[0] * v2[2];
    cp[2] = v1[0] * v2[1] - v1[1] * v2[0];
}
double calculateVectorMagnitude(double* v) {
    return std::sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
}
void normalizeVector(double* v) {
    double magnitude = calculateVectorMagnitude(v);
    v[0] = v[0] / magnitude;
    v[1] = v[1] / magnitude;
    v[2] = v[2] / magnitude;
}
void calculateNormal(double* p1, double* p2, double* p3, double* vn) {
    double v1[3] = { p2[0] - p1[0], p2[1] - p1[1], p2[2] - p1[2] };
    double v2[3] = { p3[0] - p1[0], p3[1] - p1[1], p3[2] - p1[2] };
    calculateCrossProduct(v1, v2, vn);
    normalizeVector(vn);
}
