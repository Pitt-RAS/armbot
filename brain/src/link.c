#include "link.h"
#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>

/* ALL OF THE FOLLOWING CODE IS PURELY SETUP */
/* configure the usb port on the pi for serial communications */
/* credit to: https://stackoverflow.com/users/198536/wallyk */
/*int set_interface_attribs(int fd, int speed, int parity)
{
    struct termios tty;
    memset(&tty, 0, sizeof(tty));
    if (tcgetattr(fd, &tty) != 0)
    {
        error_message("error %d from tcgetattr", errno);
        return -1;
    }

    cfsetospeed(&tty, speed);
    cfsetispeed(&tty, speed);

    tty.c_cflag = (tty.c_cflag & ~CSIZE) | CS8; // 8-bit characters
    tty.c_cflag = (tty.c_cflag & ~CSIZE) | CS8;     // 8-bit chars
    // disable IGNBRK for mismatched speed tests; otherwise receive break
    // as \000 chars
    tty.c_iflag &= ~IGNBRK; // disable break processing
    tty.c_lflag = 0; // no signaling chars, no echo, no canonical processing
    tty.c_oflag = 0; // no remapping, no delays
    tty.c_cc[VMIN]  = 0; // read doesn't block
    tty.c_cc[VTIME] = 5; // 0.5 seconds read timeout
    tty.c_iflag &= ~(IXON | IXOFF | IXANY); // shut off xon/xoff ctrl
    tty.c_cflag |= (CLOCAL | CREAD); // ignore modem controls, enable reading
    tty.c_cflag &= ~(PARENB | PARODD); // shut off parity
    tty.c_cflag |= parity;
    tty.c_cflag &= ~CSTOPB;
    tty.c_cflag &= ~CRTSCTS;

    if (tcsetattr(fd, TCSANOW, &tty) != 0)
    {
        error_message("error %d from tcsetattr", errno);
        return -1;
    }
    return 0;
}*/

/*void set_blocking(int fd, int should_block)
{
    struct termios tty;
    memset(&tty, 0, sizeof(tty));
    if (tcgetattr(fd, &tty) != 0)
    {
        error_message("error %d from tcgetattr", errno);
        return;
    }

    tty.c_cc[VMIN]  = should_block ? 1 : 0;
    tty.c_cc[VTIME] = 5; // 0.5 seconds read timeout

    if (tcsetattr (fd, TCSANOW, &tty) != 0)
    {
        error_message ("error %d setting term attributes", errno);
    }
}

int open_serial_port(Packet* p)
{
    // open a serial connection
    int fd = open(SERIAL_PORT, O_RDWR | O_NOCTTY | O_SYNC);
    // check for errors
    if (fd < 0)
    {
        error_message("error %d opening %s: %s", errno, SERIAL_PORT, strerror(errno));
        return -1;
    }

    // configure the connection
    // baud rate of 9600, no parity bit, but this might change
    set_interface_attribs(fd, B9600, 0);
    // blocking is enabled, waits for entire package to arrive
    set_blocking(fd, 1);

    // tell the packet to hold on to the file pointer
    p->fd = fd;

    // return just because
    return fd;
}*/

int open_serial_port(Packet* p)
{
    // uncomment when ready to build
    /*p->fd = serialOpen("/dev/ttyAMA0", 9600);
    if (p->fd < 0)
    {
        // TODO error
    }*/

    // write the rest on https://github.com/WiringPi/WiringPi/blob/master/examples/serialTest.c
}

int packet_get_next(Packet* p)
{
    return 0;
}
