#include "app_manager.h"

/*------------------------ task Init ------------------------*/
App_Task task_list[] =
{
    {TASK_SUSPEND, 10, 10, key_scan_task,Keys_init}
};

// 获取当前任务列表的长度
uint8_t Get_AppList_Length(void)
{
    return sizeof(task_list)/sizeof(App_Task);
}

//根据任务名称获取任务索引
uint8_t Get_AppIndex_ByName(App_Callback name)
{
    uint8_t list_len = Get_AppList_Length();
    for (uint16_t i = 0; i < list_len; i++)
    {
        if (task_list[i].task_callback == name)
        {
            return i;
        }
    }
    return 0xFF;
}

// 根据任务索引获取任务名称
App_Process Get_AppName_ByIndex(uint8_t index)
{
    for (uint8_t i = 0;i < Get_AppList_Length();i++)
    {
        if (i == index)
        {
            return task_list[i].task_callback;
        }
    }
    return NULL;
}

// 函数状态更新
void App_Change_To_Running(void)
{
    uint8_t list_len = Get_AppList_Length();
    for (uint16_t i = 0; i < list_len; i++)
    {
        //如果延时结束并且不是挂起状态
        if ((task_list[i].task_count == 0) && (task_list[i].task_states != TASK_STOP))
        {
            //切换任务状态
            task_list[i].task_states = TASK_RUNNING;
        }
    }
}

// 任务管理器
void App_Manager_Control(void)
{
    //更新任务状态
    App_Change_To_Running();
    uint8_t list_len = Get_AppList_Length();
    for (uint16_t i = 0; i < list_len; i++)
    {
        if (task_list[i].task_states == TASK_RUNNING)
        {
            //执行任务
            task_list[i].task_callback();
            //任务延时重载
            task_list[i].task_count = task_list[i].task_delay;
            //任务挂起
            task_list[i].task_states = TASK_SUSPEND;
        }
    }
}

// 任务初始化
void App_Manager_Init(void)
{
    uint8_t list_len = Get_AppList_Length();
    for (uint8_t i = 0; i < list_len; i++)
    {
        if (task_list[i].task_init != NULL)
        {
            task_list[i].task_init();
        }
    }
}