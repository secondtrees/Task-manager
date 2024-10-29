#include "app_manager.h"

//任务延时计数器
void Task_Delay_Update(void)
{
    uint8_t list_len = Get_AppList_Length();
    for (uint8_t i = 0; i < list_len; i++)
    {
        //如果任务不是挂起状态
        if (task_list[i].task_states == TASK_SUSPEND)
        {
            //任务为挂起延时状态
            task_list[i].task_count--;
        }
    }
}