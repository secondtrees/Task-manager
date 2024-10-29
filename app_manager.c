#include "app.h"

/*------------------------ task list ------------------------*/
extern App_Task task_list[];

// 获取当前任务列表的长度
unsigned char ucGet_AppList_Length(void)
{
    return sizeof(task_list)/sizeof(App_Task);
}

//根据任务名称获取任务索引
unsigned char ucGet_AppIndex_ByName(App_Body_Point name)
{
    unsigned char i = 0;
    //获取任务列表长度
    unsigned char list_len = ucGet_AppList_Length();

    for (i = 0; i < list_len; i++)
    {
        if (task_list[i].app_task == name)
        {
            return i;
        }
    }
    return 0xFF;
}

// 根据任务索引获取任务名称
App_Body_Point fpGet_AppName_ByIndex(unsigned char index)
{
    unsigned char i = 0;
    //获取任务列表长度
    unsigned char list_len = ucGet_AppList_Length();

    for (i = 0;i < list_len;i++)
    {
        if (i == index)
        {
            return task_list[i].app_task;
        }
    }
    return NULL;
}

// 函数状态更新
void vApp_Change_To_Ready(void)
{
    unsigned char i = 0;
    //获取任务列表长度
    unsigned char list_len = ucGet_AppList_Length();

    for (i = 0; i < list_len; i++)
    {
        //如果延时结束并且不是挂起状态
        if ((task_list[i].task_count == 0) && (task_list[i].task_states != TASK_STOP))
        {
            //切换任务状态
            task_list[i].task_states = TASK_READY;
        }
    }
}

// 任务管理器
void vApp_Manager_Control(void)
{
    unsigned char i = 0;
    //获取任务列表长度
    unsigned char list_len = ucGet_AppList_Length();
    
    for (i = 0; i < list_len; i++)
    {
        //如果任务是就绪状态
        if (task_list[i].task_states == TASK_READY)
        {
            //任务状态变更
            task_list[i].task_states = TASK_RUNNING;
            //执行任务
            task_list[i].app_task();
            //任务延时重载
            task_list[i].task_count = task_list[i].task_delay;
            //任务挂起
            task_list[i].task_states = TASK_SUSPEND;
        }
    }
}

// 任务初始化
void vApp_Manager_Init(void)
{
    unsigned char i = 0;
    //获取任务列表长度
    unsigned char list_len = ucGet_AppList_Length();
    
    for (i = 0; i < list_len; i++)
    {
        if (task_list[i].task_init != NULL)
        {
            task_list[i].task_init();
        }
    }
}

//任务延时计数器
void vTask_Delay_Update(void)
{
    unsigned char i;
    //获取任务列表长度
    unsigned char list_len = ucGet_AppList_Length();

    for (i = 0; i < list_len; i++)
    {
        //如果任务是挂起状态
        if (task_list[i].task_states == TASK_SUSPEND)
        {
            //任务延时计数器减1
            task_list[i].task_count--;
            //更新任务状态
            vApp_Change_To_Ready();
        }
    }
}
