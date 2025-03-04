import pystray
from pystray import MenuItem as item
import PIL.Image
from PIL import Image
from monitorcontrol import get_monitors
import os
import sys

def resource_path(relative_path):
    if hasattr(sys, '_MEIPASS'):
        return os.path.join(sys._MEIPASS, relative_path)
    return os.path.join(os.path.abspath("."), relative_path)

def create_icon(icon_path):
    return Image.open(resource_path(icon_path))

def set_brightness(luminance):
    for monitor in get_monitors():
        try:
            with monitor:
                monitor.set_luminance(luminance)
                print(f"Set brightness to {luminance}% for a monitor")
        except Exception as e:
            print(f"Failed to set brightness for a monitor: {e}")

def create_brightness_item(percentage):
    return item(f"{percentage}%", lambda _: set_brightness(percentage))

def create_menu():
    brightness_menu = [create_brightness_item(i) for i in range(0, 101, 10)]

    return pystray.Menu(
        item("Brightness", pystray.Menu(*brightness_menu)),
        item("Exit", lambda icon, _: icon.stop())
    )

def run_icon():
    icon.run()

if __name__ == "__main__":
    image = create_icon("./res/monitorIcon.png")
    icon = pystray.Icon("DDCControl", image, menu=create_menu())
    run_icon()
