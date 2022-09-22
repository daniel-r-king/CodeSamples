#pragma once
void TEST_runTest(std::string testName, bool(*test)());
void TEST_runAll();
bool TEST_Location();
bool TEST_Tile();
bool TEST_Word();
bool TEST_Board();
bool TEST_Game();
