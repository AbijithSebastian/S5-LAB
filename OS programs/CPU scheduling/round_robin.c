#include <stdio.h>
struct process
{
    int id,at,bt,btr,state,ct,tat,wt;
};
int front=-1,rear=-1,times[100],tf=0;

void enqueue(struct process queue[],struct process temp)
{
    if(rear==-1)
    {
        rear=0;
        front=0;
    }
    else
    {
        rear++;
    }
    queue[rear]=temp;
}

struct process dequeue(struct process queue[])
{
    int f=front;
    if(front==rear)
    {
        front=-1;
        rear=-1;
    }
    else
    {
        front++;
    }
    return queue[f];
}

int isEmpty(struct process queue[])
{
    if(front==-1)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int allCompleted(struct process p[],int num)
{
    for(int i=0;i<num;i++)
    {
        if(p[i].state==0)
        {
            return 0;
        }
    }
    return 1;
}

void display(struct process p[],int num)
{
    int sumtat=0,sumwt=0;
    printf("PID\tAT\tBT\tCT\tTAT\tWT\n");
    for(int i=0;i<num;i++)
    {
        p[i].tat=p[i].ct-p[i].at;
        p[i].wt=p[i].tat-p[i].bt;
        sumtat+=p[i].tat;
        sumwt+=p[i].wt;
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n",p[i].id,p[i].at,p[i].bt,p[i].ct,p[i].tat,p[i].wt);
    }
    printf("Avg TAT:%.2f\nAvg WT:%.2f\n",(float)sumtat/num,(float)sumwt/num);
}

void main()
{
    int previousProcessCompleted;
    int num,current=-1,prev=-1,ts,tsr;
    printf("Enter no.of processes:");
    scanf("%d",&num);
    struct process p[num],queue[150];
    printf("Enter respective details:\n");
    for(int i=0;i<num;i++)
    {
        p[i].id=i+1;
        printf("Enter AT of P%d:",i+1);
        scanf("%d",&p[i].at);
        printf("Enter BT of P%d:",i+1);
        scanf("%d",&p[i].bt);
        p[i].btr=p[i].bt;
        p[i].state=0;
    }
    printf("Enter time slice:");
    scanf("%d",&ts);
    tsr=ts;
    int time=0;

    while(1)
    {
        for(int i=0;i<num;i++)
        {
            if(p[i].at==time)
            {
                struct process temp;
                temp=p[i];
                enqueue(queue,temp);
            }
        }
        if(tsr==0)
        {
            struct process temp=dequeue(queue);
            enqueue(queue,temp);
            previousProcessCompleted=1;
            tsr=ts;
        }

        if(!isEmpty(queue))
        {
            prev=current;
            current=queue[front].id;
            queue[front].btr=queue[front].btr-1;
            tsr-=1;
            if(queue[front].btr==0)
            {
                struct process temp=dequeue(queue);
                previousProcessCompleted=1;
                tsr=ts;
                for(int i=0;i<num;i++)
                {
                    if(p[i].id==temp.id)
                    {
                        p[i].ct=time+1;
                        p[i].state=1;
                    }
                }
            }
            else
            {
                previousProcessCompleted=0;
            }
            if(prev!=current)
            {
                printf("|P%d",current);
                if(time==0)
                {
                    times[tf]=0;
                    tf++;
                }
                else
                {
                    times[tf]=time;
                    tf++;
                }
            }
            else
            {
                printf("-");
            }
        }
        else
        {
            if(time==0)
            {
                printf("|");
                times[tf]=0;
                tf++;
            }
            if(prev!=current)
            {
                printf("|");
                times[tf]=time;
                tf++;
            }
            else
            {
                printf("-");
            }
            prev=current;
            current=-1;
        }
        time++;

        if(allCompleted(p,num))
        {
            printf("|\n");
            int lastTime=time;
            times[tf]=time;
            tf=0;
            int curtime=times[tf];
            for(int i=0;i<=lastTime;i++)
            {
                if(i==curtime)
                {
                    printf(" %d",curtime);
                    tf++;
                    curtime=times[tf];
                }
                else
                {
                    printf(" ");
                }
            }
            printf("\n");
            display(p,num);
            return;
        }
    }
}