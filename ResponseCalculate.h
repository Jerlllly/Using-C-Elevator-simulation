#ifndef RESPONSECACULATE_H
#define RESPONSECACULATE_H
int  SilenceSimulate() ;//��Ĭ����ģ�麯��
int  InitSimulation() ;//��ʼ�������������
int  InitElevator(ELEVATORSTATE   *elevator) ;//��ʼ������״̬��������
int  LoadUserCallArray(FILE  *fp) ;//�û�ָ������������ݺ���
int  OutputSimulationResult() ;//��������������Ϊ����ļ��ĺ���
int  ImportUserCall(FILE  *fp) ;//���û�ָ��д��������ļ��ĺ���
int  ImportSimulateParam(FILE  *fp) ;//���������д��������ļ��ĺ���
int  GetNextTimeStatus(ELEVATORSTATE *elevator) ;//���������һʱ��״̬�ĺ���
int  ImportSimulateResult(FILE  *fp) ;//�����ݵ�ǰʱ��״̬д��������ļ��ĺ���
int  FindUserCallCanServe(ELEVATORSTATE  *elevator , char r_state) ;//����ǰ�����Ƿ����ͬʱ��Ӧ�����û�ָ��ĺ���
char  GetElevatorDirection(ELEVATORSTATE  *elevator) ;//�����ڷ�������д���ֹͣ״̬ʱ�ж���������״̬�ĺ���
int  SetElevatorState(ELEVATORSTATE  *elevator) ;//������״̬�޸�Ϊ��һʱ��״̬�ĺ���
int Caculate(FILE *fp);


























#endif 
