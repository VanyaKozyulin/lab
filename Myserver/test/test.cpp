#include "pch.h"
#include "CppUnitTest.h"
#include <string>
#include "../Myserver/Myserver.cpp" 

using namespace std;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace YourServerTests
{
    TEST_CLASS(YourServerTests)
    {
    public:

        TEST_METHOD(TestClearDisplayCommand)
        {
            Command command = ParseCommand("clear display");

            ClearDisplay();

        }

        TEST_METHOD(TestDrawPixelCommand)
        {

            Command command = ParseCommand("draw pixel 10 20 red");

            int x = std::stoi(command.params[0]);
            int y = std::stoi(command.params[1]);
            std::string color = command.params[2];

            DrawPixel(x, y, color);

        }

        TEST_METHOD(TestDrawLineCommand)
        {
            Command command = ParseCommand("draw line 10 20 30 40 blue");

            int x1 = std::stoi(command.params[0]);
            int y1 = std::stoi(command.params[1]);
            int x2 = std::stoi(command.params[2]);
            int y2 = std::stoi(command.params[3]);
            std::string color = command.params[4];

            DrawLine(x1, y1, x2, y2, color);

        }
    };
}
