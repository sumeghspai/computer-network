#include<stdio.h>

// typedef struct pcs {
//     int at,bt,tat,wt,ct,rt,status;
// }process;

int readyq[100],front=-1,rear=-1,n;

void enqueue(int index){
    if(front == -1){
        front++;
    }
    rear++;
    printf("\nQueue State : \n",index);
    for(int i =0;i<n;i++){
        printf("%d ",readyq[i]);
    }
    readyq[rear] = index;
}


int dequeue(){
    if(front == -1){
        return -1;
    }
    int index = readyq[front];
    if(front == rear){
        front = -1;
        rear = -1;
    }
    front++;
    return index;
}

void main(){
    int q,i,flag=0;
    printf("Enter the number of processes : ");
    scanf("%d",&n);
    int at[n],bt[n],tat[n],ct[n],wt[n],rt[n],status[n];
    int completed=0,time=0,expire=0;
    float ttat= 0.0,twt=0.0;
    printf("\nEnter the time quantum : ");
    scanf("%d",&q);
    i=0;
    while(i<n){
        printf("\nEnter the AT of process %d : ",i);
        scanf("%d",&at[i]);
        printf("\nEnter the BT of process %d : ",i);
        scanf("%d",&bt[i]);
        status[i] = 0;
        rt[i] = bt[i];
        i++;
    }
    for(i=0;i<n;i++){
        printf("\nAT : %d\n",(at[i]));
        printf("BT : %d\n",(bt[i]));
    }

    while(time < at[0]) 
    {
        time++;
    }

    int current = 0;
    status[0] = 1;
    flag=0;
    while(completed < n){
            for(i=0;i<n;i++){
                if(at[i] <= time){
                    if(status[i] == 0){
                            enqueue(i);
                            status[i] = 1;
                            flag = 1;
                    }
                }
            }
        if(flag == 1){
            printf("\nNew process added at time %d\n",time);
            flag = 0;
        }
        time++;

        if(current == -1){
            current = dequeue();
        }

        if(current != -1){
            rt[current] = rt[current] - 1;
            expire++;
            if(expire == q && rt[current] != 0)
            {
                enqueue(current);
                current = -1;
                expire = 0;
            }
            else if(rt[current] == 0){
                ct[current] = time;
                tat[current] =   ct[current] - at[current];
                wt[current] =   tat[current] - bt[current] ;
                ttat += tat[current];
                twt += wt[current];
                completed++;
                current = -1;
                expire = 0;
            }
        }
    }
    printf("\n\nID\tAT\tBT\tTAT\tWT\tCT");
    for(i=0;i<n;i++){
        printf("\n%d\t%d\t%d\t%d\t%d\t%d\n",i+1,at[i],bt[i],tat[i],wt[i],ct[i]);
    }

    printf("Average TAT = %f \n",(float)ttat/(float)n);
       printf("Average WT = %f \n",(float)twt/(float)n);
}