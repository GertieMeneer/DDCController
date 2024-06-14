import pystray
import PIL.Image

image = PIL.Image.open("./DDCController/res/monitorIcon.png")

def on_clicked(icon, item):
    print("Hello World")

icon = pystray.Icon("DDCControl", image, menu=pystray.Menu(
    pystray.MenuItem("Test", on_clicked)
))

icon.run()
