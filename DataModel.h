#ifndef CODEFORLAB7_H_  


#define CODEFORLAB7_H_
//用户指令结构体 
typedef  struct  UserCall{
int  user_floor ;     	//用户所在楼层
int  user_target ;     //用户目标楼层
int  call_time ;         //用户请求时刻
char  call_type ;       //用户指令类型，′U′表示上行指令，′D′表示下行指令
}USERCALL;
//用户参数结构体 
typedef  struct  SysParam{
char  param_name[100] ;     	//参数名
char  param_value[100] ;     //参数值
}SYSPARAM;
//电梯服务队列 链表头结构体 
typedef  struct  ServeListNode{
char  serve_state ;       //电梯服务状态
USERCALL  *user_call ;//电梯当前响应用户指令时，指向指令数组的某一个元素
struct ServeListNode  *next_node ;//存储下一个结点的地址
}SERVELISTNODE;
//电梯状态数据结构体 
typedef  struct  elevatorstate{
int  current_floor ;     	//电梯当前所处楼层
char  run_state ;          //电梯运行状态
SERVELISTNODE  *serve_list ;//电梯响应的用户指令队列
}ELEVATORSTATE;
//电梯待响应数据链表 
typedef  struct  ResponseListNode{
int  usercall_index;       //用户指令在指令数组中对应的序号
struct  ResponseListNode  *next_node;//存储下一个结点的地址
}RESPONSELISTNODE;
//链表表头 
typedef  struct  ResponseListHeadNode{
int  list_num ;       //待响应用户指令链表中数据结点的个数
RESPONSELISTNODE  *head ;//链表中第一个数据结点的指针
RESPONSELISTNODE  *tail ;//链表中最后一个数据结点的指针
}RESPONSELISTHEADNODE;
//全局变量声明

#endif 
