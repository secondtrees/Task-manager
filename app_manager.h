#ifndef __APP_MANAGER_H__
#define __APP_MANAGER_H__

#include "string.h"

//函数指针
typedef void (*App_Body_Point)(void);

/**
 * @brief 任务延时计数器
 * @note 需要放在定时器中断中调用
 * @note 每次调用所有挂起的任务的延时计数减1，并将计数器为零的任务状态更改为就绪
 * */
void vTask_Delay_Update(void);

/**
 * @brief 根据任务名称获取任务索引
 * @param name 任务名称
 * @return 任务索引
 * */
unsigned char ucGet_AppIndex_ByName(App_Body_Point name);

/**
 * @brief 根据任务索引获取任务名称
 * @param index 任务索引
 * @return 任务函数指针
 * */
App_Body_Point fpGet_AppName_ByIndex(unsigned char index);

/**
 * @brief 获取任务列表长度
 * @return 任务列表长度
 */
unsigned char ucGet_AppList_Length(void);

/**
 * @brief 函数状态更新
 * @note 该函数再主循环调用，当延时计数为零时，自动更改任务状态为就绪
 * @note 但是该函数并不能运行任务，需要在这之后调用(App_Manager_Control)函数
 */
void vApp_Change_To_Ready(void);

/**
 * @brief 任务管理器控制函数
 * @note 该函数在主循环中调用，运行所有就绪状态的函数，同时更改状态
 * @note 运行完任务后，会自动重载延时计数器，同时将状态更改为挂起
 */
void vApp_Manager_Control(void);

/**
 * @brief 任务初始化
 * @brief 初始化所有需要初始化的任务
 */
void vApp_Manager_Init(void);

/*----------------------- task States -----------------------*/
//任务状态枚举
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
// @such as: App_Task task_list[] = {
//    {TouchKeyInit,TASK_SUSPEND,40,40,TouchKey_Scan},
//    {NULL,TASK_SUSPEND,6,6,Uart1_Echo},
//     ...,
//}
//任务结构体
typedef struct{
    //初始化函数
    App_Body_Point task_init;
    //任务状态
    Task_States task_states;
    //延时计数(开始时 == 任务延时)
    unsigned int task_count;
    //任务延时
    unsigned int task_delay;
    //任务需要的函数体
    App_Body_Point app_task;
}App_Task;

#endif
