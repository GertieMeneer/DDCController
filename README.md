# DDCControllerWindows

Monitor Controller for Windows

## Building and installing

- `sudo apt install libddcutil-dev`
- `cmake -S . -B build`
- `cmake --build build`<br>
- Put executable file inside of `monitorcontrol/usr/bin/`
- `dpkg -b monitorcontrol`
- Install the .deb file
