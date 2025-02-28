import pystray
from pystray import MenuItem as item
import PIL.Image
from monitorcontrol import get_monitors

def create_icon(image_path):
    return PIL.Image.open(image_path)

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
