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

    popupWidget = new QWidget(nullptr, Qt::Popup);
    popupSlider = new QSlider(Qt::Horizontal, popupWidget);
    popupSlider->setRange(0, 100);

    QVBoxLayout *layout = new QVBoxLayout(popupWidget);
    layout->addWidget(new QLabel("Montor brightness control"));
    layout->addWidget(popupSlider);

    connect(icon, &QSystemTrayIcon::activated, this, &tray::iconActivated);
    connect(popupSlider, &QSlider::sliderReleased, this, &tray::popupSliderReleased);

    icon->setIcon(QIcon::fromTheme("application-exit"));
    icon->show();
}

void tray::iconActivated(QSystemTrayIcon::ActivationReason reason)
{
    if (reason == QSystemTrayIcon::Trigger)
    {
        QPoint pos = QCursor::pos();
        popupWidget->move(pos + QPoint(0, -50));
        popupWidget->show();
        popupWidget->raise();
        popupWidget->activateWindow();
        popupWidget->setFocus();
    }
}

void tray::popupSliderReleased()
{
    int value = popupSlider->value();
    std::cout << "Slider value: " << value << std::endl;

    DDCA_Display_Info_List *info_list = nullptr;
    DDCA_Status rc = ddca_get_display_info_list2(false, &info_list);

    if (rc != 0 || !info_list || info_list->ct == 0)
    {
        std::cerr << "Failed to get display info list." << std::endl;
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
            std::cerr << "  Failed to open display handle for display " << i << std::endl;
            continue;
        }

        DDCA_Vcp_Feature_Code code = 0x10;
        DDCA_Non_Table_Vcp_Value old_value;
        ddca_get_non_table_vcp_value(disp_handle, code, &old_value);
        std::cout << "mh: " << static_cast<int>(old_value.mh) << "\n"
                  << "ml: " << static_cast<int>(old_value.ml) << "\n"
                  << "sh: " << static_cast<int>(old_value.sh) << "\n"
                  << "sl: " << static_cast<int>(old_value.sl) << std::endl;
        uint8_t brightnessValue = static_cast<uint8_t>(value);
        rc = ddca_set_non_table_vcp_value(disp_handle, code, 0, value);
        if (rc != 0)
        {
            std::cerr << "  Failed to set brightness for display " << i << ". Error code: " << rc << std::endl;
        }

        ddca_close_display(disp_handle);
    }

    ddca_free_display_info_list(info_list);
}
