#include "stdio.h"
#include "stdlib.h"
#include "DataModel.h"
#include "global.h"
#include <io.h>
#include "string.h"
#include "ElevatorSimulation.h"
#include "ResponseCalculate.h"
#include "DataExport.h"

int main()
{
	SystemInit();
	ShowMenu();	
}


int SystemInit()
{
	int check_result=1;
	int param_num=0;
	char num[100];
	char ex[1000];
	char *ed=NULL;
	char *op=NULL;
	
	SYSPARAM test[3];
	int i=0;
	int p=0;
	FILE *fp;
	if(_access("SysConf",0)==-1)
	check_result=0;
	else
	{
		if(_access(".\\SysConf\\SysParam.txt",0)==-1) 
		check_result=-1;
		else
		{
			if((fp=fopen(".\\SysConf\\SysParam.txt","r"))==NULL)
			check_result=-2;
			else
			{
				fscanf(fp,"%s",num);
				while(fscanf(fp,"%s",ex)!=EOF)
				{
					op=strtok(ex,"=");
					ed=strtok(NULL,"=");
					strcpy(test[i].param_name,op);
					strcpy(test[i].param_value,ed);
					if(strcmp(test[i].param_name,"UserRequestFilePath")==0)
					{
						p=1;
						if(strcmp(test[i].param_value,"*")!=0)
							if(_access(test[i].param_value,0)!=0)
							check_result=-3; 	 
					}
					else if(strcmp(test[i].param_name,"SimulationFilesPath")==0)
					{
						p=1;
						if(strcmp(test[i].param_value,"*")!=0)
							if(_access(test[i].param_value,0)!=0)
							check_result=-4; 
					}
					else if(strcmp(test[i].param_name,"ElevatorHeight")==0)
					{
						p=1;
						if(atoi(test[i].param_value)<=2)
							check_result=-5;
					}
					else if(strcmp(test[i].param_name,"DelayTime")==0)
					{
						p=1;
						if(atoi(test[i].param_value)<=0)
							check_result=-6;	
					}
					strcpy(param_array[i].param_name,test[i].param_name);
					strcpy(param_array[i].param_value,test[i].param_value);
					i++;
				}
				if(p==0)
				check_result=-8;
				if(atoi(num)!=i)
				check_result=-7;
			}
		}
	}
	if(check_result<=0)
	{
		if(check_result==0)
		printf("ϵͳ�Լ������Ҳ���SysConfĿ¼\n");
		if(check_result==-1)
		printf("ϵͳ�Լ������Ҳ���SysConfĿ¼�µ�SysParam.txt�ļ�\n");
		if(check_result==-2)
		printf("SysParam.txt�ļ���ʧ��\n");
		if(check_result==-3)
		printf("�û��Զ���Ĵ���û�ָ���ļ���Ŀ¼������\n");
		if(check_result==-4)
		printf("�û��Զ���Ĵ���û���ʷ�����ļ���Ŀ¼������\n"); 
		if(check_result==-5)
		printf("����¥���������\n");
		if(check_result==-6)
		printf("���ݶ��������ӳٲ�������\n");
		if(check_result==-7)
			printf("ʵ�ʶ�����ϵͳ�����������ļ���һ�������Ĳ�����������\n");
		if(check_result==-8)
		printf("�Ӳ����ļ���û���ҵ��κ�ϵͳ����Ĳ���\n");
		exit(0);
	}
	
	return check_result;
}

void ShowMenu()
{
	int op=0;
	printf("������Ϊһ�����ݷ�����򣬷����������ݵ��������У��ṩ���¹��ܣ�\n1. ָ���û�ָ���ļ�����Ĭ���棨ֻ����������ļ���\n2. ָ���û�ָ���ļ����������棨������������ļ� ��δʵװ��\n3. ָ���û�ָ���ļ���ȫ����棨����ʾ���������������ļ� ��δʵװ��\n4.ָ����ʷ�����ļ���������ʽ�طţ���δʵװ��\n5.�޸�ϵͳ����\n0. �˳�\n��������Ҫִ�еĹ�����ţ�\n");
	scanf("%d",&op);
	if(op==1)
	{
		printf("����ǰ���ڡ���Ĭ���桱ģ�飬��ѡ��Ҫ���еĲ�����\n1. �����û�ָ���ļ����ƣ���ʼ��Ĭ����\n0. �����ϼ��˵�\n����������Ҫ���еĲ�����ţ�\n");	
		scanf("%d",&op);
		if(op==1)
		SilenceSimulate();
		if(op==0)
		ShowMenu();
		
	} 
	if(op>1&&op<5)
	{
		printf("�������δʵװ��\n0. �����ϼ��˵�\n��������Ҫ���еĲ�����ţ�\n") ;
		scanf("%d",&op);
		if(op==0)
		ShowMenu();
	} 
	if(op==5)
	{
			printf("����ǰ���ڡ�ϵͳ�������á�ģ�飬��ѡ��Ҫ���õĲ�����\n1. �����û�ָ���ļ����Ŀ¼\n2. ������ʷ�����ļ����Ŀ¼\n3. ���õ����ܲ���\n4. ���õ��ݶ�������ʱ���ӳ�ϵ��\n0. �����ϼ��˵�\n����������Ҫ�������õĲ�����ţ�\n");
		scanf("%d",&op);
		if(op==1)
		{
			printf("�������ļ�Ŀ¼\n");
			scanf("%s",&param_array[0].param_value);
			ShowMenu(); 
			
		}
		if(op==2)
		{
			printf("�������ļ�Ŀ¼\n");
			scanf("%s",&param_array[1].param_value);
			ShowMenu();
		}
		if(op==3)
		{
			printf("����������ܲ���\n");
			scanf("%s",&param_array[2].param_value);
			ShowMenu();
		}
		if(op==4)
		{
			printf("�������ӳ�ϵ��\n");
			scanf("%s",&param_array[3].param_value);
			ShowMenu();
		} 
	}
		

}
