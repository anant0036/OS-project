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
