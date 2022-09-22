#include <crtdbg.h>
#include <iostream>
#include "test.h"
#include "triangle.h"
#include "utility.h"

void TEST_runTest(std::string testName, bool(*test)()) {
    _CrtMemState s1;
    _CrtMemState s2;
    _CrtMemState s3;
    _CrtMemCheckpoint(&s1);
    bool pass = test();
    _CrtMemCheckpoint(&s2);
    if (_CrtMemDifference(&s3, &s2, &s1)) {
        pass = false;
        std::cout << testName << " failed: MEMORY LEAK DETECTED" << std::endl;
        _CrtMemDumpStatistics(&s3);
    }
    if (pass) {
        std::cout << testName << " passed" << std::endl;
    }
}
void TEST_runAll() {
    TEST_runTest("TEST_Triangle()", TEST_Triangle);
}
bool TEST_Triangle() {
    bool pass = true;
    Triangle tri = Triangle();
    double numsA[3] = { 1,2,3 };
    double numsB[3] = { 4,5,6 };
    double numsC[3] = { 7,8,9 };
    tri.setNormal(numsA);
    tri.setV1(numsB);
    tri.setV2(numsC);
    double* normal = tri.getNormal();
    if (normal[0] != 1) {
        std::cout << "TEST_Triangle() failed at " << __FILE__ << "::" << __LINE__ << std::endl;
        pass = false;
    }
    if (normal[1] != 2) {
        std::cout << "TEST_Triangle() failed at " << __FILE__ << "::" << __LINE__ << std::endl;
        pass = false;
    }
    if (normal[2] != 3) {
        std::cout << "TEST_Triangle() failed at " << __FILE__ << "::" << __LINE__ << std::endl;
        pass = false;
    }
    double* v1 = tri.getV1();
    if (v1[0] != 4) {
        std::cout << "TEST_Triangle() failed at " << __FILE__ << "::" << __LINE__ << std::endl;
        pass = false;
    }
    if (v1[1] != 5) {
        std::cout << "TEST_Triangle() failed at " << __FILE__ << "::" << __LINE__ << std::endl;
        pass = false;
    }
    if (v1[2] != 6) {
        std::cout << "TEST_Triangle() failed at " << __FILE__ << "::" << __LINE__ << std::endl;
        pass = false;
    }
    Triangle newTri = tri;
    normal = newTri.getNormal();
    if (normal[0] != 1) {
        std::cout << "TEST_Triangle() failed at " << __FILE__ << "::" << __LINE__ << std::endl;
        pass = false;
    }
    if (normal[1] != 2) {
        std::cout << "TEST_Triangle() failed at " << __FILE__ << "::" << __LINE__ << std::endl;
        pass = false;
    }
    if (normal[2] != 3) {
        std::cout << "TEST_Triangle() failed at " << __FILE__ << "::" << __LINE__ << std::endl;
        pass = false;
    }
    v1 = tri.getV1();
    if (v1[0] != 4) {
        std::cout << "TEST_Triangle() failed at " << __FILE__ << "::" << __LINE__ << std::endl;
        pass = false;
    }
    if (v1[1] != 5) {
        std::cout << "TEST_Triangle() failed at " << __FILE__ << "::" << __LINE__ << std::endl;
        pass = false;
    }
    if (v1[2] != 6) {
        std::cout << "TEST_Triangle() failed at " << __FILE__ << "::" << __LINE__ << std::endl;
        pass = false;
    }
    return pass;
}
