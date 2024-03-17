#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
    
int main() {
    setuid(0);
    // Use ddccontrol to determine the valid value of the monitor you want to switch to
    // In my case it is 6927. Replace it with an appropriate value
    system("sudo ddccontrol -r 0x60 -w 6927 dev:/dev/i2c-10 > /dev/null 2> /dev/null");
    return 0;
}
