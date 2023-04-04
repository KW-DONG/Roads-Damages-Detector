#include "serial_win.h"
#include <Windows.h>

SerialPort::SerialPort()
{

}

SerialPort::~SerialPort()
{

}

bool SerialPort::open(const char* portname, int baudrate, char parity, char databit, char stopbit, char synchronizeflag)
{
    this->synchronizeflag = synchronizeflag;
    HANDLE hCom = NULL;
    if (this->synchronizeflag)
    {
        hCom = CreateFileA(portname,
                           GENERIC_READ | GENERIC_WRITE,
                           0,
                           NULL,
                           OPEN_EXISTING,
                           0,
                           NULL);
    }
    else
    {
        hCom = CreateFileA(portname,
                           GENERIC_READ | GENERIC_WRITE,
                           0,
                           NULL,
                           OPEN_EXISTING,
                           FILE_FLAG_OVERLAPPED,
                           NULL);
    }

    if (hCom == (HANDLE)-1)
    {
        return false;
    }

    if (!SetupComm(hCom, 1024, 1024))
    {
        return false;
    }

    DCB p;
    memset(&p, 0, sizeof(p));
    p.DCBlength = sizeof(p);
    p.BaudRate = baudrate;
    p.ByteSize = databit;

    switch (parity)
    {
    case 0:
        p.Parity = NOPARITY;
        break;
    case 1:
        p.Parity = ODDPARITY;
        break;
    case 2:
        p.Parity = EVENPARITY;
        break;
    case 3:
        p.Parity = MARKPARITY;
        break;
    }

    switch (stopbit)
    {
    case 1:
        p.StopBits = ONESTOPBIT;
        break;
    case 2:
        p.StopBits = TWOSTOPBITS;
        break;
    case 3:
        p.StopBits = ONE5STOPBITS;
        break;
    }

    if (!SetCommState(hCom, &p))
    {
        return false;
    }

    COMMTIMEOUTS TimeOuts;
    TimeOuts.ReadIntervalTimeout = 1000;
    TimeOuts.ReadTotalTimeoutMultiplier = 500;
    TimeOuts.ReadTotalTimeoutConstant = 5000;
    TimeOuts.WriteTotalTimeoutMultiplier = 500;
    TimeOuts.WriteTotalTimeoutConstant = 2000;
    SetCommTimeouts(hCom, &TimeOuts);

    PurgeComm(hCom, PURGE_TXCLEAR | PURGE_RXCLEAR);

    memcpy(pHandle, &hCom, sizeof(hCom));

    return true;
}

bool SerialPort::close()
{
    HANDLE hCom = *(HANDLE*)pHandle;
    CloseHandle(hCom);
    return true;
}

int SerialPort::send(std::string dat)
{
    HANDLE hCom = *(HANDLE*)pHandle;

    if (this->synchronizeflag)
    {
        DWORD dwBytesWrite = dat.length();
        BOOL bWriteStat = WriteFile(hCom,
                                    (char*)dat.c_str(),
                                    dwBytesWrite,
                                    &dwBytesWrite,
                                    NULL);
        if (!bWriteStat)
        {
            return 0;
        }
        return dwBytesWrite;
    }
    else
    {
        DWORD dwBytesWrite = dat.length();
        DWORD dwErrorFlags;
        COMSTAT comStat;
        OVERLAPPED m_osWrite;

        memset(&m_osWrite, 0, sizeof(m_osWrite));
        m_osWrite.hEvent = CreateEvent(NULL, TRUE, FALSE, "WriteEvent");

        ClearCommError(hCom, &dwErrorFlags, &comStat);
        BOOL bWriteStat = WriteFile(hCom,
                                    (char*)dat.c_str(),
                                    dwBytesWrite,
                                    &dwBytesWrite,
                                    &m_osWrite);
        if (!bWriteStat)
        {
            if (GetLastError() == ERROR_IO_PENDING)
            {
                WaitForSingleObject(m_osWrite.hEvent, 1000);
            }
            else
            {
                ClearCommError(hCom, &dwErrorFlags, &comStat);
                CloseHandle(m_osWrite.hEvent);
                return 0;
            }
        }
        return dwBytesWrite;
    }
}

std::string SerialPort::receive()
{
    HANDLE hCom = *(HANDLE*)pHandle;
    std::string rec_str = "";
    char buf[1024];
    if (this->synchronizeflag)
    {
        DWORD wCount = 1024;
        BOOL bReadStat = ReadFile(hCom,
                                  buf,
                                  wCount,
                                  &wCount,
                                  NULL);
        for (int i = 0; i < 1024; i++)
        {
            if (buf[i] != -52)
                rec_str += buf[i];
            else
                break;
        }
        return rec_str;
    }
    else
    {
        DWORD wCount = 1024;
        DWORD dwErrorFlags;
        COMSTAT comStat;
        OVERLAPPED m_osRead;

        memset(&m_osRead, 0, sizeof(m_osRead));
        m_osRead.hEvent = CreateEvent(NULL, TRUE, FALSE, "ReadEvent");

        ClearCommError(hCom, &dwErrorFlags, &comStat);
        if (!comStat.cbInQue)return 0;
        BOOL bReadStat = ReadFile(hCom,
                                  buf,
                                  wCount,
                                  &wCount,
                                  &m_osRead);
        if (!bReadStat)
        {
            if (GetLastError() == ERROR_IO_PENDING)
            {
                GetOverlappedResult(hCom, &m_osRead, &wCount, TRUE);
            }
            else
            {
                ClearCommError(hCom, &dwErrorFlags, &comStat);
                CloseHandle(m_osRead.hEvent);
                return 0;
            }
        }
        for (int i = 0; i<1024; i++)
        {
            if (buf[i] != -52)
                rec_str += buf[i];
            else
                break;
        }
        return rec_str;
    }
}

