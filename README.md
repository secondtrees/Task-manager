#### **app_manager.h : 包含了2个 “.c” 文件的所有函数的声明以及结构体等变量的声明和线程或者任务的信息句柄等**

**app_manager.c : 包含了关于状态机钟线程处理的函数实现**



**2024-10-29 // 15:04** :: 进行修改，精简了文件。同时任务结构体不再事先声明，现在所保留的两个文件都是无需修改直接使用的

**//任务列表示例**

App_Task task_list[] = {

  */\* tOUCH KEY TASK \*/*

  *{TouchKeyInit, TASK_SUSPEND, 40, 40, TouchKey_Scan},

  */\* UART1 ECHO TASK \*/*

  {NULL, TASK_SUSPEND, 6, 6, Uart1_Echo},

};

函数前缀: 

v -> void 

uc -> unsigned char

fp -> 泛指函数指针