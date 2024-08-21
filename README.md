# Monitor Switch
Allows to switch between inputs of Dell U3223QE monitor on Linux platform.

## Switching monitor input from a command line
First, I had to find a way to switch monitor inputs from a command line. After googling I found an interesing post by _just-passing-by_ on https://www.dell.com/community/en/conversations/monitors/u2723qe-kvm-using-a-keyboard-shortcut-to-switch-in-linux/647fa06af4ccf8a8de56ccc8 where he described the solution he used to switch inpits in his U2723QE. It's the same series monitor, just sized 27" instead of 32". 
His solution uses '_ddcutil_' to extract I2C interface data from his monitor and to write a valid value to property with id=60 (input source). Quite simple solution but not for me. The standard '_ddcutil_' utility doesn't work with my monitor and does not allow to switch inputs. '_ddcutil_' provides the following information for the external display connected to my laptop by DisplayPort over USB-C:
```
Display 1
   I2C bus:  /dev/i2c-10
   DRM connector:           card0-DP-1
   EDID synopsis:
      Mfg id:               DEL - Dell Inc.
      Model:                DELL U3223QE
      Product code:         17020  (0x427c)
      Serial number:        XXXXXXX
      Binary serial number: 1112625740 (0x4251524c)
      Manufacture year:     2023,  Week: 41
   VCP version:         Detection failed
```
I tried to use values from the post I found but it didn't work. So I had to find an alternative to '_ddcutil_'.

## Input settings discovery
While searching for alternatives to '_ddcutil_', I found '_ddccontrol_' application. I decided to give it a try. I installed and launched with '_ddccontrol_' application. It was able to properly detect the external monitor and provided some usefull informartion regarding the input source management:
```
= VESA standard monitor
...
> Others
        ...
        > Input settings
                > id=inputsource, name=Input Source Select, address=0x60, delay=-1ms, type=2
                  Possible values:
                        > id=analog - name=Analog, value=1
                        > id=digital - name=Digital, value=3
                  supported, value=6939, maximum=6939
```
As seen from the output above, the current value of input is set to **6939**. It had no use for me as it was a value for DisplayPort input setting for my extenal monitor. I needed to find a value that I need to send to the monitor to switch to another input. In my case, I needed to switch the monitor to the plain DisplayPort input. The solution was quite simple. I switched the monitor to DP input and ran '_ddccontrol_' application again. To my surprise the monitor responded (even it was switched to another input) and provided valid input setting values. It was **6927**. These numbers, **6939** and **6927** do not make any sense but it works for my purpose. I was able to switch the input using the following command:
```
sudo ddccontrol -r 0x60 -w 6927 dev:/dev/i2c-10
```

## The utility
The solution was found but not without hiccups. It did reqiure inputing admin password every time I use this command. And it output additional information to console while switching the input. The latter problem was easy to solve:
```
sudo ddccontrol -r 0x60 -w 6927 dev:/dev/i2c-10 > /dev/null 2> /dev/null
```

This application/hack is partially based the forum post by  and the post by Ashark here https://unix.stackexchange.com/questions/703048/how-do-i-run-a-sudo-command-from-kde-shortcuts-command 
