#include <stdio.h>

struct  process
{
    int id,at,bt,ct,tat,wt;
}p[30],temp;

void ganttchart(int num)
{
    for(int i=1;i<=2*p[num].ct-4;i++)
    {
        printf("-");
    }
    printf("\n");
    for(int i=1;i<=num;i++)
    {
        printf("|");
        for(int j=1;j<=p[i].bt/2;j++)
        {
            printf(" ");
        }
        printf("P%d",p[i].id);
        for(int j=1;j<=p[i].bt/2;j++)
        {
            printf(" ");
        }
    }
    printf("|\n");
    for(int i=1;i<=2*p[num].ct-4;i++)
    {
        printf("-");
    }

    printf("\n0");
    for(int i=1;i<=num;i++)
    {
        for(int j=1;j<=p[i].bt/2;j++)
        {
            printf(" ");
        }
        if(p[i].ct<=9)
        {
            printf("  ");
        }
        else
        {
            printf(" ");
        }
        for(int j=1;j<=p[i].bt/2;j++)
        {
            printf(" ");
        }
        printf("%d",p[i].ct);
    }

}

void main()
{
    int num,sumtat=0,sumwt=0;
    printf("Enter the no.of processes:");
    scanf("%d",&num);
    printf("Enter the processes:\n");
    for(int i=1;i<=num;i++)
    {
        p[i].id=i;
        printf("Enter the AT of P%d:",i);
        scanf("%d",&p[i].at);
        printf("Enter the BT of P%d:",i);
        scanf("%d",&p[i].bt);
    }
    for(int i=1;i<=num-1;i++)
    {
        for(int j=1;j<=num-i-1;j++)
        {
            if(p[j].at>p[j+1].at)
            {
                temp=p[j];
                p[j]=p[j+1];
                p[j+1]=temp;
            }
        }
    }
    p[1].ct=p[1].bt;
    for(int i=2;i<=num;i++)
    {
        int min=i;
        for(int j=i+1;j<=num;j++)
        {
            if(p[j].at<=p[i-1].ct  && p[j].bt<p[min].bt)
            {
                min=j;
            }
        }
        temp=p[i];
        p[i]=p[min];
        p[min]=temp;
        p[i].ct=p[i-1].ct+p[i].bt;
        if(p[i].at>p[i-1].ct)
        {
            printf("idle time fron %d to %d\n",p[i-1].ct,p[i].at);
            p[i].ct+=p[i].at-p[i-1].ct;
        }
    }

    for(int i=1;i<=num;i++)
    {
        p[i].tat=p[i].ct-p[i].at;
        p[i].wt=p[i].tat-p[i].bt;
        sumtat+=p[i].tat;
        sumwt+=p[i].wt;
    }
    printf("Average TAT:%.2f\nAverage WT:%.2f\n",(float)sumtat/num,(float)sumwt/num);

    printf("PID\tAT\tBT\tCT\tTAT\tWT\n");
    for(int i=1;i<=num;i++)
    {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n",p[i].id,p[i].at,p[i].bt,p[i].ct,p[i].tat,p[i].wt);
    }
    ganttchart(num);
}