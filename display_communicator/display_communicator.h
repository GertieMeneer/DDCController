#pragma once

#ifndef DISPLAY_COMMUNICATOR_H
#define DISPLAY_COMMUNICATOR_H

#include <ddcutil_c_api.h>
#include <QApplication>
#include <QSlider>
#include <QSystemTrayIcon>

class display_communicator
{
public:
    display_communicator();
    void setValue(QSlider *slider, DDCA_Vcp_Feature_Code code, const QString &errorLabel);
    DDCA_Non_Table_Vcp_Value getValue(DDCA_Vcp_Feature_Code code);
};

#endif