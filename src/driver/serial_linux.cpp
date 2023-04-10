#include "serial.h"
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <cstdlib>
#include <fcntl.h>
#include <termios.h>
#include <errno.h>
#include <map>
#include <iostream>

SerialPort::SerialPort()
{

}

SerialPort::~SerialPort()
{

}

static std::map<int,speed_t> baudmap = {
    {300, B300},
    {1200, B1200},
    {2400, B2400},
    {4800, B4800},
    {9600, B9600},
    {19200, B19200},
    {115200, B115200}
};

bool SerialPort::open(const char* portName, int baudrate, char parity, char databit, char stopbit, char synchronizeflag)
{
    std::string name = portName;
    name = "/dev/" + name;

    fd = ::open(name.c_str(), O_RDWR | O_NOCTTY | O_NDELAY);
    if (fd == -1)
    {
        perror("open COM error");
        return false;
    }

    //set baudrate
    {
        struct termios opt = {0};
        tcgetattr(fd, &opt);
        tcflush(fd, TCIOFLUSH);
        cfsetispeed(&opt, baudmap[baudrate]);
        cfsetospeed(&opt, baudmap[baudrate]);

        if (tcsetattr(fd, TCSANOW, &opt) != 0)
        {
            perror("tcsetattr COM error");
            return -1;
        }

        tcflush(fd, TCIOFLUSH);
    }

    //set stop and parity
    {
        struct termios opt = {0};

        if (tcgetattr(fd, &opt) != 0)
        {
            perror("tcgetattr COM error");
            return -1;
        }

        opt.c_cflag &= ~CSIZE;
        switch(databit)
        {
        case 7:
            opt.c_cflag |= CS7;
            break;
        case 8:
            opt.c_cflag |= CS8;
            break;
        default:
            fprintf(stderr, "Unsupport data size\n");
            return -1;
            break;
        }

        switch(stopbit)
        {
        case 1:
            opt.c_cflag &= ~CSTOPB;
            break;
        case 2:
            opt.c_cflag |= CSTOPB;
            break;
        default:
            fprintf(stderr, "Unsupport stopbit\n");
            break;
        }

        switch(parity)
        {
        case 0:
            opt.c_cflag &= ~PARENB;
            opt.c_cflag &= ~CSTOPB;
            break;
        case 1:
            opt.c_cflag |= PARENB; /*Enable parity*/
            opt.c_cflag &= ~PARODD; /*转换为偶效验*/
            opt.c_iflag |= INPCK; /*Disnable parity checking*/
            break;
        case 2:
            opt.c_cflag |= (PARODD | PARENB); /*设置为奇效验*/
            opt.c_iflag |= INPCK; /*Disnable parity checking*/
            break;
        default:
            fprintf(stderr, "Unsupported parity\n");
            return -1;
            break;
        }
    }
}

bool SerialPort::close()
{
    ::close(fd);
}

int SerialPort::send(std::string dat)
{
    ::write(fd, dat.c_str(), dat.size());
}

std::string SerialPort::receive()
{
    std::string data(1024, '\0');
    ::read(fd, &data[0], 1024);
    return data;
}


