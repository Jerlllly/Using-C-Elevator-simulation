#ifndef RESPONSECACULATE_H
#define RESPONSECACULATE_H
int  SilenceSimulate() ;//静默仿真模块函数
int  InitSimulation() ;//初始化仿真变量函数
int  InitElevator(ELEVATORSTATE   *elevator) ;//初始化电梯状态变量函数
int  LoadUserCallArray(FILE  *fp) ;//用户指令数组加载数据函数
int  OutputSimulationResult() ;//计算仿真结果并输出为结果文件的函数
int  ImportUserCall(FILE  *fp) ;//将用户指令写入仿真结果文件的函数
int  ImportSimulateParam(FILE  *fp) ;//将仿真参数写入仿真结果文件的函数
int  GetNextTimeStatus(ELEVATORSTATE *elevator) ;//计算电梯下一时刻状态的函数
int  ImportSimulateResult(FILE  *fp) ;//将电梯当前时刻状态写入仿真结果文件的函数
int  FindUserCallCanServe(ELEVATORSTATE  *elevator , char r_state) ;//处理当前电梯是否可以同时响应其它用户指令的函数
char  GetElevatorDirection(ELEVATORSTATE  *elevator) ;//电梯在服务过程中处于停止状态时判断其上下行状态的函数
int  SetElevatorState(ELEVATORSTATE  *elevator) ;//将电梯状态修改为下一时刻状态的函数
int Caculate(FILE *fp);


























#endif 
