#pragma once

#ifndef TRAY_H
#define TRAY_H

#include <QApplication>
#include <QSystemTrayIcon>
#include <iostream>
#include <QScreen>
#include <QCursor>
#include <QWidget>
#include <QSlider>
#include <QLabel>
#include <QVBoxLayout>
#include <QPushButton>
#include <ddcutil_c_api.h>
#include <stdlib.h>

class tray : public QObject
{
    Q_OBJECT
public:
    tray();
    void start();

private:
    QSystemTrayIcon *icon;
    QVBoxLayout *layout;
    QWidget *popup;
    QSlider *popupSlider;
    QPushButton *closeButton;
    QPushButton *exitButton;

    DDCA_Display_Handle *display;
    DDCA_Status *status;

private slots:
    void iconActivated(QSystemTrayIcon::ActivationReason reason);
    void popupSliderReleased();
    void closeButtonPressed();
    void exitButtonPressed();
};

#endif
