#include<stdio.h>

int num=0;
int timing=0;
int curser=9999;
int curser_indi=-1;
int rr_indi=0;
int i;
int j;

struct working
{
    int proc_id;
    int avi_time;
    int burst_time;
    int prio;
    int start_time[100];
    int start_indi = 0;
	int status = -1;
    int wait_time = 0;
    int next_proc_indi = 0;
    int my_indi = 0;
    int visited = 0;
}work[2][50];

int que = 0;
int q1_proc,q2_proc;

void sort_arival(int num)
{
    struct working w;
    int min,pos;

    for(int i=0;i<num-1;i++)
    {
        min = work[que][i].avi_time;
        pos = i;
        for(int i=0;i<num-1;i++)
        {
            if(min>work[que][j].avi_time)
            {
                min = work[que][j].avi_time;
                pos = j;
            }
        }

        if(i!=pos)
        {
            w=work[que][i];
            work[que][i] = work[que][pos];
            work[que][pos] = w;
        }
    }
}

int get_next(int index)
{
    int num=0;
    for(int i = 0; i < q1_proc; i++)
    {
        if(work[que][i].avi_time<=timing && work[que][i].burst_time!=0)
    {
        work[que][i].my_indi=i;
        if(work[que][i].prio<curser)
        {
            work[que][index].next_proc_indi=i;
            curser =work[que][i].prio;
            num = 1;
		
        }

    }
	
    }
    return num;
}

void move_to_last()
{
    struct working w;
    int i=0;
    w = work[que][0];

    while(i<q2_proc-1)
    {
        work[que][i]=work[que][i+1];
        i++;
    }
    work[que][i]=w;
}

void pop()
{
    int i=0;
    while(i<q2_proc-1)
    {
        work[que][i]=work[que][i+1];
        i++;
    }
    q2_proc--;
}

int main()
{
    int value,res_index,w;
	printf("Enter the number of processes : ");
	scanf("%d",&num);
	struct working result[num];
	q1_proc = num;
	q2_proc = 0;
	res_index = 0;

    for(int i=0;i<num;i++){
		printf("\nEnter the process information for the process %d :",i+1);
		printf("\nprocess Id : ");
		scanf("%d",&value);
		work[que][i].proc_id=value;
		printf("\nprocess arival time :");
		scanf("%d",&value);
		work[que][i].avi_time=value;
		printf("\nprocess burst time :");
		scanf("%d",&value);
		work[que][i].burst_time=value;
		printf("\nprocess priority :");
		scanf("%d",&value);
		work[que][i].prio=value;
	}

    sort_arival(q1_proc);
	
	get_next(0);
	curser_indi = work[que][curser_indi].next_proc_indi;
	
	while(q1_proc!=0 || q2_proc!=0){
		if(q1_proc!=0){
			
			que=0;
			if((work[que][curser_indi].status!=0) && (work[que][curser_indi].avi_time<=timing)){
				work[que][curser_indi].start_time[work[que][curser_indi].start_indi]=timing;
				work[que][curser_indi].start_indi++;
				timing++;
				work[que][curser_indi].burst_time--;
				w=curser_indi;
				if(work[que][curser_indi].burst_time==0){
					q1_proc--;
					curser=9999;
					get_next(curser_indi);
					curser_indi = work[que][curser_indi].next_proc_indi;
					work[que][w].status=0;
					result[res_index]=work[que][w];
					res_index++;
					for(int i=w;i<q1_proc;i++){
						work[que][i]=work[que][i+1];
					}
				}
				if(get_next(curser_indi)){
					get_next(curser_indi);
					curser_indi = work[que][curser_indi].next_proc_indi;
					work[que+1][rr_indi]=work[que][w];
					rr_indi++;
					q2_proc++;
					q1_proc--;
					for(int i=w;i<q1_proc;i++){
						work[que][i]=work[que][i+1];
					}
				}
			}
            else
            {
                timing++;
            }
            
        }
        else if (q2_proc!=0) {
            que=1;
			value=1;
			if(work[que][curser_indi].status!=0){
				for(int i=0;i<2;i++){
					work[que][0].start_time[work[que][0].start_indi]=timing;
					work[que][0].start_indi++;
					timing++;
					work[que][0].burst_time--;
					if(work[que][0].burst_time==0){
						q2_proc--;
						work[que][0].status=0;
						result[res_index]=work[que][0];
						res_index++;
						value=0;
						pop();
						break;
					}
				}
				if(value){
					move_to_last();
				}
			}	
		}
		else{
			timing++;
		}
	}
       for(int i=0;i<=res_index;i++){
		for(int j=0;j<=result[i].start_indi;j++){
			printf("\nThe process %d was running avi_time time %d sec.",result[i].proc_id,result[i].start_time[j]);
		}
	} 
}    
