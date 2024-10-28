#ifndef __APP_MANAGER_H__
#define __APP_MANAGER_H__

#include "app.h"
#include "string.h"

//函数指针
typedef void (*App_Process)(void);

//任务延时计数器
void Task_Delay_Update(void);
//根据任务名称获取任务索引
uint8_t Get_AppIndex_ByName(App_Callback name);
// 获取当前任务列表的长度
uint8_t Get_AppList_Length(void);
// 根据任务索引获取任务名称
App_Process Get_AppName_ByIndex(uint8_t index);
//根据任务名称获取任务索引
uint8_t Get_AppIndex_ByName(App_Callback name);
// 函数状态更新
void App_Change_To_Running(void);
// 任务管理器
void App_Manager_Control(void);
// 任务初始化
void App_Manager_Init(void);
/*----------------------- task States -----------------------*/
typedef enum{
    /*任务就绪*/
    TASK_READY = 0,
    /*任务挂起*/
    TASK_SUSPEND,
    /*任务运行*/
    TASK_RUNNING,
    /*任务停止*/
    TASK_STOP,
    /*任务错误*/
    TASK_ERROR
}Task_States;
/*---------------------- task struct ------------------------*/
typedef struct{
    App_Process task_init;
    Task_States task_states;
    uint16_t task_count;
    uint16_t task_delay;
    App_Process task_callback;
}App_Task;
extern App_Task task_list[];

#endif