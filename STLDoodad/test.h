#ifndef TEST_H
#define TEST_H

#include <string>

void TEST_runTest(std::string testName, bool(*test)());
void TEST_runAll();
bool TEST_Triangle();

#endif // TEST_H
