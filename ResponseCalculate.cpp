#include "stdio.h"
#include "stdlib.h"
#include "DataModel.h"
#include "global.h"
#include "ResponseCalculate.h"
#include "string.h"
int SilenceSimulate()
{
	printf("请输入仿真文件名字(不加后缀):\n");
	scanf("%s",&user_file_name[10]);
	InitSimulation();
	FILE *fp;
	char path1[200],path[200];
	strcpy(path1,&user_file_name[10]);
	strcpy(path,param_array[0].param_value);
	strcat(path1,".txt") ;
	strcat(path,path1);
	fp=fopen(path,"r");
	LoadUserCallArray(fp); 
	OutputSimulationResult();
}

int InitSimulation()
{
	RESPONSELISTNODE *p;
	int func_result=1;
	if(usercall_list!=NULL)
	free(usercall_list);
	usercall_num=0;
	finish_call_num=0;
	if(response_list!=NULL)
	{
		if(response_list->head!=NULL)
		{
			p=response_list->head;
			response_list->head=response_list->head->next_node;
			free(p);
			p=NULL; 
		}
		else
		{
			response_list->head=NULL;
			response_list->tail=NULL;
			response_list->list_num=0;
			InitElevator(&elevator_a);
			InitElevator(&elevator_b);
		}
	}

	
}

int InitElevator(ELEVATORSTATE *elevator)
{
	elevator->current_floor=1;
	elevator->run_state='S';
	elevator->serve_list=(SERVELISTNODE*)malloc(sizeof(SERVELISTNODE));
	elevator->serve_list->next_node=NULL;
	elevator->serve_list->serve_state='P';
	elevator->serve_list->user_call=NULL;
	
}

int LoadUserCallArray(FILE *fp)
{
	int result;
	fscanf(fp,"%d",&usercall_num);
	usercall_list=(USERCALL*)malloc(sizeof(USERCALL)*usercall_num);
	int item_num=0;
	while(fscanf(fp,"%d,%d,%d",&usercall_list[item_num].user_floor,&usercall_list[item_num].user_target,&usercall_list[item_num].call_time)!=EOF)
	{
		if(usercall_list[item_num].user_target-usercall_list[item_num].user_floor>0)
		usercall_list[item_num].call_type='U';
		else
		usercall_list[item_num].call_type='D';
		item_num++;
	}
	if(usercall_num==item_num)
	result=1;
	else
	result=0;
	return result;
}

int OutputSimulationResult()
{
	char path[100];
	char name[100];
	char *path_name;
	FILE *fp;
	strcpy(&name[100],&user_file_name[10]);
	if(strcmp(param_array[1].param_value,"*")==0)
	{
		strcpy(&path[100],".\\");
	}
	else
	{
		strcpy(&path[100],param_array[1].param_value);	
	}
	strcat(&name[100],"_SimResult.txt");
	strcat(&path[100],&name[100]);
	printf("%s",&path[100]);
	int fun_resulr=1;
	fp=fopen(&path[100],"w+");
	if(fp==NULL)
	int func_result=0;
	else
	{
		ImportUserCall(fp);
		ImportSimulateParam(fp);
		time=0;
		fprintf(fp,"0,A,1,S,B,1,S;\n");
		Caculate(fp);
		fclose(fp);
		} 	
}

int ImportUserCall(FILE *fp)
{
	int i=0;
	fprintf(fp,"%d\n",usercall_num);
	while(i<usercall_num)
	{
		fprintf(fp,"%d,%d,%d\n",usercall_list[i].user_floor,usercall_list[i].user_target,usercall_list[i].call_time);
		i++;	
	}
	fprintf(fp,"*****************************************************************\n");
}

int ImportSimulateParam(FILE *fp)
{
	FILE *p=fp;
	int i=0;
	fseek(p,0,SEEK_END);
	fprintf(p,"4\n");
	while(i<4)
	{
		fprintf(p,"%s=%s\n",param_array[i].param_name,param_array[i].param_value);
		i++;	
	}
	fprintf(fp,"*****************************************************************\n");
}

int  Caculate(FILE *fp)
{
	InitElevator(&elevator_a) ;
	InitElevator(&elevator_b) ;
	int i=0,text=0,cyl=0;
	ELEVATORSTATE *elevators[2]={&elevator_a,&elevator_b};
	response_list=(RESPONSELISTHEADNODE*)malloc(sizeof(RESPONSELISTHEADNODE));
	response_list->head=(RESPONSELISTNODE*)malloc(sizeof(RESPONSELISTNODE));
	response_list->head->next_node=NULL;
	response_list->list_num=0;
	response_list->tail=NULL;
	int t=0;
	RESPONSELISTNODE *p1,*p2; 
	SERVELISTNODE *p3,*p4;
	p2=response_list->head;
	time=usercall_list[0].call_time;
	while(finish_call_num<usercall_num)
	{
		t=0;
		index=0;
		for(;t<usercall_num;t++)
		{
			if(usercall_list[t].call_time==time)
			{
			p1=(RESPONSELISTNODE*)malloc(sizeof(RESPONSELISTNODE));
			p1->next_node=NULL; 
			p1->usercall_index=t;
			p2->next_node=p1;
			p2=p2->next_node;	
			index=1;
			}
		}
		i=0;
		for(i==0;i<=1;i++)
		{
			if(elevators[i]->run_state!='S'&&elevators[i]->serve_list->next_node!=NULL&&response_list->head->next_node!=NULL)
			{
				FindUserCallCanServe(elevators[i],elevators[i]->run_state) ;
			}
			else if(elevators[i]->serve_list->next_node==NULL)
			{
				if(response_list->head->next_node!=NULL)
				{
					p4=elevators[i]->serve_list;
					while(p4->next_node!=NULL)
					p4=p4->next_node;
					p3=(SERVELISTNODE*)malloc(sizeof(SERVELISTNODE));
					p3->next_node=NULL;
					p3->serve_state='P';
					p3->user_call=&usercall_list[response_list->head->next_node->usercall_index];
					p4->next_node=p3;
					response_list->head=response_list->head->next_node;
					index=1;
				}
				
			}
			if(elevators[i]->serve_list->next_node!=NULL)
			GetNextTimeStatus(elevators[i]);	 
		}
		if(index)
		{
			SERVELISTNODE *tp1;
			RESPONSELISTNODE *tp2=response_list->head->next_node;
			int flag=1;
			fprintf(fp, "%d,%c,%d,%c,%c,%d,%c;", time, 'A', elevator_a.current_floor, elevator_a.run_state, 'B', elevator_b.current_floor, elevator_b.run_state);
			for(text=0;text<=1;text++)
			{
				tp1=elevators[text]->serve_list->next_node; 
				do
				{
					if(tp1==NULL&&response_list->head->next_node!=NULL)
					{
						if(text==0)
						{
							fprintf(fp,"<%d,%d,%d,%c,%c>,",response_list->head->next_node->usercall_index+1,usercall_list[response_list->head->next_node->usercall_index].user_floor,usercall_list[response_list->head->next_node->usercall_index].user_target,'E','A');
							flag=0;
						}
						if(text==1&&flag==1)
							fprintf(fp,"<%d,%d,%d,%c,%c>,",response_list->head->next_node->usercall_index+1,usercall_list[response_list->head->next_node->usercall_index].user_floor,usercall_list[response_list->head->next_node->usercall_index].user_target,'E','B');
							
					}
					if(tp1==NULL) 
					break;
					for(cyl=0;cyl<usercall_num;cyl++)
					{
						if(&usercall_list[cyl]==tp1->user_call)
						break;
					}
					if(text==0)
					fprintf(fp,"<%d,%d,%d,%c,%c>,",cyl+1,usercall_list[cyl].user_floor,usercall_list[cyl].user_target,tp1->serve_state,'A');
					if(text==1)
					fprintf(fp,"<%d,%d,%d,%c,%c>,",cyl+1,usercall_list[cyl].user_floor,usercall_list[cyl].user_target,tp1->serve_state,'B');	
					tp1=tp1->next_node;				
				}
				while(tp1!=NULL);
			}
			do
				{
					if(tp2==NULL)
					break;
					if((elevators[0]->serve_list->next_node==NULL||elevators[1]->serve_list->next_node==NULL))
					{
						if(tp2->next_node==NULL)
						break;
						fprintf(fp,"<%d,%d,%d,N,N>,",tp2->next_node->usercall_index+1,usercall_list[tp2->next_node->usercall_index].user_floor,usercall_list[tp2->next_node->usercall_index].user_target); 
						break;
					}
					fprintf(fp,"<%d,%d,%d,N,N>,",tp2->usercall_index+1,usercall_list[tp2->usercall_index].user_floor,usercall_list[tp2->usercall_index].user_target); 
					tp2=tp2->next_node;
				}
				while(tp2!=NULL);
			 
			fprintf(fp, "\n");
		}
		time++;
	}
	
}

int  ImportSimulateResult(FILE  *fp)
{
	FILE *p=fp;
	fseek(p,0,SEEK_END);
	fprintf(p,"%d,A,%d,%s,B,%d,%s;",time,elevator_a.current_floor,elevator_a.run_state,elevator_b.current_floor,elevator_b.run_state);
}
int  GetNextTimeStatus(ELEVATORSTATE *elevator)
{
	SERVELISTNODE *p1;
	p1=elevator->serve_list->next_node;
	switch(elevator->run_state)
	{
		case 'U':
			{
				do
				{
					if(p1->serve_state=='P')
					{
						if(p1->user_call->user_floor==elevator->current_floor+1)
						{
							elevator->run_state='S';
							p1->serve_state='E';
							index=1;
						}
					}
					else
					{
						if(p1->user_call->user_target==elevator->current_floor+1)
						{
							elevator->run_state='S';
							elevator->serve_list=elevator->serve_list->next_node;
							finish_call_num++;
							index=1;
						}
						
					}
					p1=p1->next_node;
				}
				while(p1!=NULL);
				elevator->current_floor++;
			}
			break;
		case 'D':
			{
				do
				{
					if(p1->serve_state=='P')
					{
						if(p1->user_call->user_floor==elevator->current_floor-1)
						{
							elevator->run_state='S';
							p1->serve_state='E';
							index=1;
						}
					}
					else
					{
						if(p1->user_call->user_target==elevator->current_floor-1)
						{
							elevator->run_state='S';
							elevator->serve_list=elevator->serve_list->next_node;
							finish_call_num++; 
							index=1;
						}
					}
					
					p1=p1->next_node;
				}
				while(p1!=NULL);
				elevator->current_floor--;
			}
			break;
		case 'S':
			{
					if(elevator->serve_list->next_node->serve_state=='P')
				{
					if(elevator->serve_list->next_node->user_call->user_floor>elevator->current_floor)
					elevator->run_state='U';
					else if(elevator->serve_list->next_node->user_call->user_floor<elevator->current_floor)
					elevator->run_state='D';
					else if(elevator->serve_list->next_node->user_call->user_floor=elevator->current_floor)
					{
						elevator->run_state=elevator->serve_list->next_node->user_call->call_type;
						elevator->serve_list->next_node->serve_state='E';
					}
					index=1;
				} 
				else
				{
					if(elevator->serve_list->next_node->user_call->user_target>elevator->current_floor)
					elevator->run_state='U';
					else
					elevator->run_state='D';
					index=1;
				}
				
			} 
			break;
			
			
	}
}

char  GetElevatorDirection(ELEVATORSTATE  *elevator)
{
	
}

int  FindUserCallCanServe(ELEVATORSTATE  *elevator , char r_state) 
{
	USERCALL  *p1=elevator->serve_list->next_node->user_call;
	RESPONSELISTNODE *p2=response_list->head->next_node;
	SERVELISTNODE *p3=elevator->serve_list->next_node,*p4;
		switch(r_state)
	{
		case 'U':
part1:		{
				if(p1->call_type==elevator->run_state)
				{
				do
				{
					if(usercall_list[p2->usercall_index].call_type=='U'&&usercall_list[p2->usercall_index].user_floor>elevator->current_floor)
					{
						p4=(SERVELISTNODE*)malloc(sizeof(SERVELISTNODE));
						p4->next_node=NULL;
						p4->user_call=&usercall_list[p2->usercall_index];
						p4->serve_state='P';
						while(p3->next_node!=NULL)
						p3=p3->next_node;
						p3->next_node=p4;
						response_list->head=response_list->head->next_node;
						
					}
					p2=p2->next_node;
				}
				while(p2!=NULL);
				}
			else
				{
				do
				{
					if(usercall_list[p2->usercall_index].call_type=='U'&&usercall_list[p2->usercall_index].user_floor>elevator->current_floor&&usercall_list[p2->usercall_index].user_target<p3->user_call->user_floor)
					{
						p4=(SERVELISTNODE*)malloc(sizeof(SERVELISTNODE));
						p4->next_node=NULL;
						p4->user_call=&usercall_list[p2->usercall_index];
						p4->serve_state='P';
						while(p3->next_node!=NULL)
						p3=p3->next_node;
						p3->next_node=p4;
						response_list->head=response_list->head->next_node;
						
					}
					p2=p2->next_node;
				}
				while(p2!=NULL);
				}	
			
			}
			break;
			case 'D':
part2:				{
					if(p1->call_type==elevator->run_state)
				{
				do
				{
					if(usercall_list[p2->usercall_index].call_type=='D'&&usercall_list[p2->usercall_index].user_floor<elevator->current_floor)
					{
						p4=(SERVELISTNODE*)malloc(sizeof(SERVELISTNODE));
						p4->next_node=NULL;
						p4->user_call=&usercall_list[p2->usercall_index];
						p4->serve_state='P';
						while(p3->next_node!=NULL)
						p3=p3->next_node;
						p3->next_node=p4;
						response_list->head=response_list->head->next_node;
						
					}
					p2=p2->next_node;
				}
				while(p2!=NULL);
				}
			else
				{
				do
				{
					if(usercall_list[p2->usercall_index].call_type=='D'&&usercall_list[p2->usercall_index].user_floor<elevator->current_floor&&usercall_list[p2->usercall_index].user_target>p3->user_call->user_floor)
					{
						p4=(SERVELISTNODE*)malloc(sizeof(SERVELISTNODE));
						p4->next_node=NULL;
						p4->user_call=&usercall_list[p2->usercall_index];
						p4->serve_state='P';
						while(p3->next_node!=NULL)
						p3=p3->next_node;
						p3->next_node=p4;
						response_list->head=response_list->head->next_node;
						
					}
					p2=p2->next_node;
				}
				while(p2!=NULL);
				}
				}
			break;
			case 'S':
			{
				if(p3->serve_state=='P')
				{
					if(p3->user_call->user_floor>elevator->current_floor)
					goto part1;
					else
					goto part2;
				}
				else
				{
					if(p3->user_call->user_target>elevator->current_floor)
					goto part1;
					else
					goto part2;
				}
				
			} 
			
	}
}

int  SetElevatorState(ELEVATORSTATE  *elevator)
{
	
}
