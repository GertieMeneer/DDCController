import pystray
import PIL.Image
from monitorcontrol import get_monitors

image = PIL.Image.open("./DDCController/res/monitorIcon.png")

def on_clicked(icon, item):
    if str(item) == "Exit":
        icon.stop()
    elif str(item) == "Test":
        pystray.Icon.notify(image, "Hello World", "Test")
        print("Hello World")
    elif str(item) == "100%":
        for monitor in get_monitors():
            with monitor:
                monitor.set_luminance(100)
    # elif str(item) == "90%":
    # elif str(item) == "80%":
    # elif str(item) == "70%":
    # elif str(item) == "60%":
    # elif str(item) == "50%":
    # elif str(item) == "40%":
    # elif str(item) == "30%":
    # elif str(item) == "20%":
    # elif str(item) == "10%":
    # elif str(item) == "0%":
    

icon = pystray.Icon("DDCControl", image, menu=pystray.Menu(
    pystray.MenuItem("Brightness", pystray.Menu(
        pystray.MenuItem("100%", on_clicked),
        pystray.MenuItem("90%", on_clicked),
        pystray.MenuItem("80%", on_clicked),
        pystray.MenuItem("70%", on_clicked),
        pystray.MenuItem("60%", on_clicked),
        pystray.MenuItem("50%", on_clicked),
        pystray.MenuItem("40%", on_clicked),
        pystray.MenuItem("30%", on_clicked),
        pystray.MenuItem("20%", on_clicked),
        pystray.MenuItem("10%", on_clicked),
        pystray.MenuItem("0%", on_clicked),
    )),
    pystray.MenuItem("Exit", on_clicked)
))

icon.run()
