#ifndef CODEFORLAB7_H_  


#define CODEFORLAB7_H_
//�û�ָ��ṹ�� 
typedef  struct  UserCall{
int  user_floor ;     	//�û�����¥��
int  user_target ;     //�û�Ŀ��¥��
int  call_time ;         //�û�����ʱ��
char  call_type ;       //�û�ָ�����ͣ���U���ʾ����ָ���D���ʾ����ָ��
}USERCALL;
//�û������ṹ�� 
typedef  struct  SysParam{
char  param_name[100] ;     	//������
char  param_value[100] ;     //����ֵ
}SYSPARAM;
//���ݷ������ ����ͷ�ṹ�� 
typedef  struct  ServeListNode{
char  serve_state ;       //���ݷ���״̬
USERCALL  *user_call ;//���ݵ�ǰ��Ӧ�û�ָ��ʱ��ָ��ָ�������ĳһ��Ԫ��
struct ServeListNode  *next_node ;//�洢��һ�����ĵ�ַ
}SERVELISTNODE;
//����״̬���ݽṹ�� 
typedef  struct  elevatorstate{
int  current_floor ;     	//���ݵ�ǰ����¥��
char  run_state ;          //��������״̬
SERVELISTNODE  *serve_list ;//������Ӧ���û�ָ�����
}ELEVATORSTATE;
//���ݴ���Ӧ�������� 
typedef  struct  ResponseListNode{
int  usercall_index;       //�û�ָ����ָ�������ж�Ӧ�����
struct  ResponseListNode  *next_node;//�洢��һ�����ĵ�ַ
}RESPONSELISTNODE;
//�����ͷ 
typedef  struct  ResponseListHeadNode{
int  list_num ;       //����Ӧ�û�ָ�����������ݽ��ĸ���
RESPONSELISTNODE  *head ;//�����е�һ�����ݽ���ָ��
RESPONSELISTNODE  *tail ;//���������һ�����ݽ���ָ��
}RESPONSELISTHEADNODE;
//ȫ�ֱ�������

#endif 
