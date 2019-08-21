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
		printf("系统自检有误找不到SysConf目录\n");
		if(check_result==-1)
		printf("系统自检有误，找不到SysConf目录下的SysParam.txt文件\n");
		if(check_result==-2)
		printf("SysParam.txt文件打开失败\n");
		if(check_result==-3)
		printf("用户自定义的存放用户指令文件的目录不存在\n");
		if(check_result==-4)
		printf("用户自定义的存放用户历史仿真文件的目录不存在\n"); 
		if(check_result==-5)
		printf("电梯楼层参数有误\n");
		if(check_result==-6)
		printf("电梯动画仿真延迟参数有误\n");
		if(check_result==-7)
			printf("实际读出的系统参数个数与文件第一行声明的参数个数不符\n");
		if(check_result==-8)
		printf("从参数文件中没有找到任何系统定义的参数\n");
		exit(0);
	}
	
	return check_result;
}

void ShowMenu()
{
	int op=0;
	printf("本程序为一个电梯仿真程序，仿真两部电梯的联动运行，提供如下功能：\n1. 指定用户指令文件，静默仿真（只输出仿真结果文件）\n2. 指定用户指令文件，动画仿真（不输出仿真结果文件 暂未实装）\n3. 指定用户指令文件，全面仿真（即显示动画，又输出结果文件 暂未实装）\n4.指定历史仿真文件，动画形式回放（暂未实装）\n5.修改系统参数\n0. 退出\n请输入您要执行的功能序号：\n");
	scanf("%d",&op);
	if(op==1)
	{
		printf("您当前处于“静默仿真”模块，请选择要进行的操作：\n1. 输入用户指令文件名称，开始静默仿真\n0. 返回上级菜单\n请输入您需要进行的操作序号：\n");	
		scanf("%d",&op);
		if(op==1)
		SilenceSimulate();
		if(op==0)
		ShowMenu();
		
	} 
	if(op>1&&op<5)
	{
		printf("此项功能暂未实装！\n0. 返回上级菜单\n输入您需要进行的操作序号：\n") ;
		scanf("%d",&op);
		if(op==0)
		ShowMenu();
	} 
	if(op==5)
	{
			printf("您当前处于“系统参数配置”模块，请选择要配置的参数：\n1. 配置用户指令文件存放目录\n2. 配置历史仿真文件存放目录\n3. 配置电梯总层数\n4. 配置电梯动画仿真时的延迟系数\n0. 返回上级菜单\n请输入您需要重新配置的参数序号：\n");
		scanf("%d",&op);
		if(op==1)
		{
			printf("请输入文件目录\n");
			scanf("%s",&param_array[0].param_value);
			ShowMenu(); 
			
		}
		if(op==2)
		{
			printf("请输入文件目录\n");
			scanf("%s",&param_array[1].param_value);
			ShowMenu();
		}
		if(op==3)
		{
			printf("请输入电梯总层数\n");
			scanf("%s",&param_array[2].param_value);
			ShowMenu();
		}
		if(op==4)
		{
			printf("请输入延迟系数\n");
			scanf("%s",&param_array[3].param_value);
			ShowMenu();
		} 
	}
		

}
