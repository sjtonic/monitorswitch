# Monitor Switch
Allows to switch between inputs of Dell U3223QE monitor on Linux platform. The standard 'ddcutil' doesn't work with the monitor and does not allow to switch inputs. I had to use 'ddccontrol' application to investigate the issue and find a way to change an input. 

This application/hack is partially based the forum post by just-passing-by on https://www.dell.com/community/en/conversations/monitors/u2723qe-kvm-using-a-keyboard-shortcut-to-switch-in-linux/647fa06af4ccf8a8de56ccc8 and the post by Ashark here https://unix.stackexchange.com/questions/703048/how-do-i-run-a-sudo-command-from-kde-shortcuts-command 
