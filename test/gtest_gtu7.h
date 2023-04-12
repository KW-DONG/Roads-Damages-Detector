#ifndef GTEST_GTU7_H
#define GTEST_GTU7_H
#include <gtest/gtest.h>
#include "gtu7.h"

class Test_GTU7
{
 public:
    bool GpsIsOpen()
    {
        // Check if the serial port is open
                SerialPort port;
                if (port.open("COM5")) {
                    port.close();
                    return true;
                } else {
                    return false;
                }

    }
    bool GpsIsClose()
    {
        SerialPort port;
                if (!port.open("COM5")) {
                    return true;
                } else {
                    return false;
                }

    }
}
TEST(gtu7_test, GpsIsOpen)
{
    Test_GTU7 test;
    EXPECT_EQ(test.GpsIsOpen(), true);
}
TEST(gtu7_test, GpsIsClose)
{
    Test_GTU7 test;
    EXPECT_EQ(test.GpsIsClose(), true);
}
#endif
