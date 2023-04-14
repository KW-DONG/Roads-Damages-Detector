#ifndef GTEST_SERIAL_H
#define GTEST_SERIAL_H
#include <gtest/gtest.h>
#include "serial.h"

class Test_SerialPort
{
public:
    bool checkIsOpen()
    {
        // Check if the serial port is open
                SerialPort port;
                if (port.open("COM1")) {
                    port.close();
                    return true;
                } else {
                    return false;
                }

    }

    bool checkIsClose()
    {
        SerialPort port;
                if (!port.open("COM5")) {
                    return true;
                } else {
                    return false;
                }

    }

    bool checkIsReceive()
    {
        // 要和GPS合并还需查GPS说明书；Check if the serial port can receive data
        SerialPort port;
        bool result = false;
        if (port.open("COM5")) {
            std::string str = port.receive();
            result = str.find("$GPRMC");
            port.close();
        }
        return result;
    }
};

TEST(serial_test, checkIsOpen)
{
    Test_SerialPort test;
    EXPECT_EQ(test.checkIsOpen(), true);
}
TEST(serial_test, checkIsClose)
{
    Test_SerialPort test;
    EXPECT_EQ(test.checkIsClose(), true);
}
TEST(serial_test, checkIsReceive)
{
    Test_SerialPort test;
    EXPECT_EQ(test.checkIsReceive(), true);
}


#endif
