# DDCControllerWindows
Monitor Controller for Windows

## Building and installing
- ```sudo apt install libddcutil-dev```
- ```cmake -S . -B build```
- ```cmake --build build```<br>
- Put executable file inside of ```monitor_control/DEBIAN/usr/bin/
- ```dpkg -b monitor_control```
- Install the .deb file