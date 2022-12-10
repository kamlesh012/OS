//C Program for implementing
//Round Robin Algorithm

#include <stdio.h>
#include <stdbool.h>

void queueUpdation(int queue[],int timer,int arrival[],int n, int maxProccessIndex){
	int zeroIndex;
	for(int i = 0; i < n; i++){
		if(queue[i] == 0){
			zeroIndex = i;
			break;
		}
	}
	queue[zeroIndex] = maxProccessIndex + 1;
}

void queueMaintainence(int queue[], int n){
	for(int i = 0; (i < n-1) && (queue[i+1] != 0) ; i++){
		int temp = queue[i];
		queue[i] = queue[i+1];
		queue[i+1] = temp;
	}
}

void checkNewArrival(int timer, int arrival[], int n, int maxProccessIndex,int queue[]){
	if(timer <= arrival[n-1]){
	bool newArrival = false;
	for(int j = (maxProccessIndex+1); j < n; j++){
			if(arrival[j] <= timer){
			if(maxProccessIndex < j){
				maxProccessIndex = j;
				newArrival = true;
			}
		}
	}

	if(newArrival)
		queueUpdation(queue,timer,arrival,n, maxProccessIndex);
	}
}

int main(){
	int n,tq, timer = 0, maxProccessIndex = 0;
	float avgWait = 0, avgTT = 0;
    // tq=2;
    // n=4;
	printf("Enter Time Quanta\n");
	scanf("%d", &tq);

	printf("Enter the no. of process\n");
	scanf("%d", &n);

    int arrival[100],burst[100];
    int wait[100], turn[100], queue[100], temp_burst[100];
	bool complete[100];
  
  // int arrival[100]={0,1,2,3};
	// int burst[100]={5,4,2,1};

    for (int i = 0; i < n; i++) {
		printf("Enter Arrival Time of %dth Process",i+1);
		scanf("%d", arrival + i);
	}
    
    for (int i = 0; i < n; i++) {
		printf("Enter Burst Time of %dth Process",i+1);
		scanf("%d", burst + i);
		temp_burst[i] = burst[i];
	}

	for(int i = 0; i < n; i++){ 
		complete[i] = false;
		queue[i] = 0;
	}
	while(timer < arrival[0]) 
		timer++;
	queue[0] = 1;
	
	while(true){
		bool flag = true;
		for(int i = 0; i < n; i++){
			if(temp_burst[i] != 0){
				flag = false;
				break;
			}
		}
		if(flag)
			break;

		for(int i = 0; (i < n) && (queue[i] != 0); i++){
			int ctr = 0;
			while((ctr < tq) && (temp_burst[queue[0]-1] > 0)){
				temp_burst[queue[0]-1] -= 1;
				timer += 1;
				ctr++;

				checkNewArrival(timer, arrival, n, maxProccessIndex, queue);
			}

			if((temp_burst[queue[0]-1] == 0) && (complete[queue[0]-1] == false)){
				turn[queue[0]-1] = timer;	
				complete[queue[0]-1] = true;
			}
			
			bool idle = true;
			if(queue[n-1] == 0){
				for(int i = 0; i < n && queue[i] != 0; i++){
					if(complete[queue[i]-1] == false){
						idle = false;
					}
				}
			}
			else
				idle = false;

			if(idle){
				timer++;
				checkNewArrival(timer, arrival, n, maxProccessIndex, queue);
			}
	
			queueMaintainence(queue,n);
		}
	}

	for(int i = 0; i < n; i++){
		turn[i] = turn[i] - arrival[i];
		wait[i] = turn[i] - burst[i];
	}

    printf("arrival time\t burst time\t wait time\t tat\n");

	for(int i = 0; i < n; i++){
        printf("%d\t%d\t%d\t%d\n",arrival[i],burst[i],wait[i],turn[i]);
	}
	for(int i =0; i< n; i++){
		avgWait += wait[i];
		avgTT += turn[i];
    }
    printf("Average wait time:%f \n Average Turn Around Time%f\n",avgWait/n,avgTT/n);	

	return 0;
	
}
