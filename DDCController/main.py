import pystray
from pystray import MenuItem as item
from PIL import Image
from monitorcontrol import get_monitors
import os
import sys

current_luminance = None

def resource_path(relative_path):
    try:
        base_path = sys._MEIPASS
    except AttributeError:
        base_path = os.path.abspath(".")
    return os.path.join(base_path, relative_path)

def create_icon(icon_path):
    full_path = resource_path(icon_path)
    if not os.path.exists(full_path):
        raise FileNotFoundError(f"Icon file not found: {full_path}")
    return Image.open(full_path)

def run_icon():
    global icon
    icon = pystray.Icon("DDCControl", image, menu=create_menu())
    icon.run()

def set_brightness(luminance):
    global current_luminance
    for monitor in get_monitors():
        try:
            with monitor:
                monitor.set_luminance(luminance)
                print(f"Set brightness to {luminance}% for a monitor")
                current_luminance = luminance  # Update the global variable
        except Exception as e:
            print(f"Failed to set brightness for a monitor: {e}")
    icon.update_menu()  # Refresh the menu to update checkmarks

def create_brightness_item(percentage):
    return item(
        f"{percentage}%",
        lambda _: set_brightness(percentage),
        checked=lambda item: current_luminance == percentage
    )

def create_menu():
    brightness_menu = [create_brightness_item(i) for i in range(0, 101, 10)]

    return pystray.Menu(
        item("Brightness", pystray.Menu(*brightness_menu)),
        item("Exit", lambda icon, _: icon.stop())
    )

if __name__ == "__main__":
    for monitor in get_monitors():
        try:
            with monitor:
                current_luminance = monitor.get_luminance()
        except Exception as e:
            print(f"Issue with monitor: {e}")

    icon_path = "res\monitorIcon.png"
    image = create_icon(icon_path)
    run_icon()