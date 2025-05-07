#pragma once

#ifndef TRAY_H
#define TRAY_H

#include <QApplication>
#include <QSystemTrayIcon>
#include <QMenu>
#include <QAction>
#include <iostream>
#include <QThread>
#include <QActionGroup>
#include <QScreen>
#include <QCursor>
#include <QWidget>
#include <QSlider>
#include <QVBoxLayout>
#include <QLabel>
#include <ddcutil_c_api.h>
#include <ddcutil_types.h>
#include <ddcutil_status_codes.h>
#include <ddcutil_macros.h>

class tray : public QObject
{
    Q_OBJECT
public:
    tray();
    void start();

private:
    QSystemTrayIcon *icon;
    QWidget *popupWidget;
    QSlider *popupSlider;

    DDCA_Display_Handle *display;
    DDCA_Status *status;

private slots:
    void iconActivated(QSystemTrayIcon::ActivationReason reason);
    void popupSliderReleased();
};

#endif
