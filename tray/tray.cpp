#include "./tray.h"

tray::tray() {}

void tray::start()
{
    if (!QSystemTrayIcon::isSystemTrayAvailable())
    {
        std::cerr << "No system tray available";
        return;
    }

    icon = new QSystemTrayIcon(nullptr);
    popup = new QWidget(nullptr, Qt::Dialog | Qt::CustomizeWindowHint | Qt::WindowTitleHint);
    QLabel *brightnessLabel = new QLabel("Brightness", popup);
    brightnessSlider = new QSlider(Qt::Horizontal, popup);
    QLabel *contrastLabel = new QLabel("Contrast", popup);
    contrastSlider = new QSlider(Qt::Horizontal, popup);
    layout = new QVBoxLayout(popup);
    closeButton = new QPushButton("Close", popup);
    exitButton = new QPushButton("Exit", popup);

    popup->setWindowTitle("Monitor Control");
    brightnessSlider->setRange(0, 100);
    contrastSlider->setRange(0, 100);
    exitButton->setStyleSheet("QPushButton { background-color: firebrick; color: white; }");

    layout->addWidget(brightnessLabel);
    layout->addWidget(brightnessSlider);
    layout->addWidget(contrastLabel);
    layout->addWidget(contrastSlider);
    layout->addWidget(closeButton);
    layout->addWidget(exitButton);

    connect(icon, &QSystemTrayIcon::activated, this, &tray::iconActivated);
    connect(brightnessSlider, &QSlider::sliderReleased, this, &tray::brightnessSliderReleased);
    connect(contrastSlider, &QSlider::sliderReleased, this, &tray::contrastSliderReleased);
    connect(closeButton, &QPushButton::released, this, &tray::closeButtonPressed);
    connect(exitButton, &QPushButton::released, this, &tray::exitButtonPressed);

    icon->setIcon(QIcon::fromTheme("display"));
    icon->show();
}

void tray::iconActivated(QSystemTrayIcon::ActivationReason reason)
{
    if (reason == QSystemTrayIcon::Trigger)
    {
        getValues();
        QPoint pos = QCursor::pos();
        popup->show();
        popup->raise();
        popup->activateWindow();
        popup->setFocus();
    }
}

void tray::getValues()
{
    DDCA_Non_Table_Vcp_Value brightness = communicator->getValue(0x10);
    brightnessSlider->setValue((brightness.sh << 8) | brightness.sl);

    DDCA_Non_Table_Vcp_Value contrast = communicator->getValue(0x12);
    contrastSlider->setValue((contrast.sh << 8) | contrast.sl);
}

void tray::brightnessSliderReleased()
{
    communicator->setValue(brightnessSlider, 0x10, "brightness");
}

void tray::contrastSliderReleased()
{
    communicator->setValue(contrastSlider, 0x12, "contrast");
}

void tray::closeButtonPressed()
{
    popup->hide();
}

void tray::exitButtonPressed()
{
    exit(EXIT_SUCCESS);
}