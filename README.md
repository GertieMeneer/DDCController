# DDCControllerWindows

Monitor Controller for Linux

## Building and installing

- `sudo apt install libddcutil-dev`
- `cmake -S . -B build`
- `cmake --build build`
- Put executable file inside of `monitorcontrol/usr/bin/`
- Build dpkg package `dpkg -b monitorcontrol`
- Install .deb file `sudo dpkg -i monitorcontrol.deb`
