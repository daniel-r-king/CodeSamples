#ifndef TRIANGLE_H
#define TRIANGLE_H

class Triangle {
private:
    double* normal;
    double* v1;
    double* v2;
    double* v3;
public:
    Triangle();
    Triangle(const Triangle& triangle);
    ~Triangle();

    Triangle& operator=(const Triangle& triangle);
    bool operator==(const Triangle& triangle);
    bool operator!=(const Triangle& triangle);

    double* getNormal();
    double* getV1();
    double* getV2();
    double* getV3();

    void setNormal(double* normal);
    void setV1(double* v1);
    void setV2(double* v2);
    void setV3(double* v3);

    void print();
};

#endif // TRIANGLE_H
