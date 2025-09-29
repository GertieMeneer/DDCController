#pragma once

#ifndef DISPLAY_COMMUNICATOR_H
#define DISPLAY_COMMUNICATOR_H

#include <ddcutil_c_api.h>

class display_communicator
{
public:
    display_communicator();
    void setValue(DDCA_Vcp_Feature_Code code, int value);
};

#endif
