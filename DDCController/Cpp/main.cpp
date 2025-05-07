#include "tray/tray.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    tray icon;
    icon.start();

    return app.exec();
}
