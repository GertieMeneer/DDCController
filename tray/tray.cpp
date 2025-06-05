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
        QPoint pos = QCursor::pos();
        popup->move(pos + QPoint(0, -50));
        popup->show();
        popup->raise();
        popup->activateWindow();
        popup->setFocus();
    }
}

void tray::sliderReleased(QSlider *slider, DDCA_Vcp_Feature_Code code, const QString &errorLabel)
{
    int value = slider->value();

    DDCA_Display_Info_List *info_list = nullptr;
    DDCA_Status rc = ddca_get_display_info_list2(false, &info_list);

    if (rc != 0 || !info_list || info_list->ct == 0)
    {
        icon->showMessage("Error", "Failed to get display info list", QSystemTrayIcon::Warning, 5000);
        return;
    }

    for (int i = 0; i < info_list->ct; ++i)
    {
        const DDCA_Display_Info &info = info_list->info[i];
        DDCA_Display_Ref display = info.dref;
        DDCA_Display_Handle disp_handle;
        rc = ddca_open_display2(display, true, &disp_handle);
        if (rc != 0)
        {
            icon->showMessage("Error", "Failed to open display handle for display", QSystemTrayIcon::Warning, 5000);
            continue;
        }

        DDCA_Non_Table_Vcp_Value old_value;
        ddca_get_non_table_vcp_value(disp_handle, code, &old_value);
        rc = ddca_set_non_table_vcp_value(disp_handle, code, 0, value);
        if (rc != 0)
        {
            QString message = QString("Failed to set %1 for display %2.\nError code: %3")
                                  .arg(errorLabel)
                                  .arg(i)
                                  .arg(rc);
            icon->showMessage("Error", message, QSystemTrayIcon::Warning, 5000);
        }

        ddca_close_display(disp_handle);
    }

    ddca_free_display_info_list(info_list);
}

void tray::brightnessSliderReleased()
{
    sliderReleased(brightnessSlider, 0x10, "brightness");
}

void tray::contrastSliderReleased()
{
    sliderReleased(contrastSlider, 0x12, "contrast");
}

void tray::closeButtonPressed()
{
    popup->hide();
}

void tray::exitButtonPressed()
{
    exit(EXIT_SUCCESS);
}