#ifdef GLOBAL_VAR  
#define GLOBAL_EXTERN  
#include "DataModel.h"  
#else  
#define GLOBAL_EXTERN extern  
#endif  
/************************************************************************
此文件用来定义全局变量
************************************************************************/ 
GLOBAL_EXTERN USERCALL *usercall_list;
GLOBAL_EXTERN int index,usercall_num,finish_call_num,time,status_change_flag;
GLOBAL_EXTERN SYSPARAM param_array[4];
GLOBAL_EXTERN char user_file_name[10];
GLOBAL_EXTERN ELEVATORSTATE elevator_a,elevator_b;
GLOBAL_EXTERN RESPONSELISTHEADNODE *response_list;
