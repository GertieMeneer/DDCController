#include "./display_communicator.h"
#include <cstdlib>
#include <iostream>

display_communicator::display_communicator() {}

void display_communicator::setValue(DDCA_Vcp_Feature_Code code, int value)
{
    DDCA_Display_Info_List *info_list = nullptr;
    DDCA_Status rc = ddca_get_display_info_list2(false, &info_list);

    if (rc != 0 || !info_list || info_list->ct == 0)
    {
        std::cout << "Failed to get display info list" << std::endl;
        exit(1);
    }

    for (int i = 0; i < info_list->ct; ++i)
    {
        const DDCA_Display_Info &info = info_list->info[i];
        DDCA_Display_Ref display = info.dref;
        DDCA_Display_Handle disp_handle;
        rc = ddca_open_display2(display, true, &disp_handle);
        if (rc != 0)
        {
            std::cout << "Failed to open display handle for display" << std::endl;
            continue;
        }

        DDCA_Non_Table_Vcp_Value old_value;
        ddca_get_non_table_vcp_value(disp_handle, code, &old_value);
        rc = ddca_set_non_table_vcp_value(disp_handle, code, 0, value);
        if (rc != 0)
        {
            std::cout << "rc is not 0" << std::endl;
        }

        ddca_close_display(disp_handle);
    }

    ddca_free_display_info_list(info_list);
}

DDCA_Non_Table_Vcp_Value display_communicator::getValue(DDCA_Vcp_Feature_Code code)
{
    DDCA_Display_Info_List *info_list = nullptr;
    DDCA_Status rc = ddca_get_display_info_list2(false, &info_list);

    if (rc != 0 || !info_list || info_list->ct == 0)
    {
        std::cout << "Failed to get display info list" << std::endl;
        exit(1);
    }

    const DDCA_Display_Info &info = info_list->info[1];
    DDCA_Display_Ref display = info.dref;
    DDCA_Display_Handle disp_handle;
    rc = ddca_open_display2(display, true, &disp_handle);
    if (rc != 0)
    {
        std::cout << "Failed to open display handle for display" << std::endl;
        ddca_free_display_info_list(info_list);
        exit(1);
    }

    DDCA_Non_Table_Vcp_Value value;
    rc = ddca_get_non_table_vcp_value(disp_handle, code, &value);
    ddca_close_display(disp_handle);
    ddca_free_display_info_list(info_list);
    if (rc != 0)
    {
        std::cout << "Failed to get value for display" << std::endl;
        exit(1);
    }

    return value;
}