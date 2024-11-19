#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int available[100],allocation[100][100],max[100][100],need[100][100];
bool isFinished[100];
int sequence[100];

void isSafe(int p,int r)
{
    int i,j,work[100],count=0;
    for(i=0;i<r;i++)
    {
        work[i]=available[i];
    }
    for(i=0;i<100;i++)
    {
        isFinished[i]=false;
    }
    while(count<p)
    {
        bool canAllot=false;
        for(i=0;i<p;i++)
        {
            if(!isFinished[i])
            {
                for(j=0;j<r;j++)
                {
                    if(work[j]<need[i][j])
                    {
                        break;
                    }
                }
                if(j==r)
                {
                    for(j=0;j<r;j++)
                    {
                        work[j]+=allocation[i][j];
                    }
                    sequence[count++]=i;
                    isFinished[i]=true;
                    canAllot=true;
                }
            }
        }
        if(canAllot==false)
        {
            printf("System is not safe\n");
            return;
        }
    }
    printf("System is in safe state\n");
    printf("safe sequence:");
    for(i=0;i<p;i++)
    {
        printf("P%d,",sequence[i]);
    }
    printf("\n");
}

void request(int p,int r)
{
    int index,arr[100],i=0;
    printf("Enter the process no. for resource request:");
    scanf("%d",&index);
    printf("Enter the requested instances for each:\n");
    for(i=0;i<r;i++)
    {
        scanf("%d",&arr[i]);
    }
    for(i=0;i<r;i++)
    {
        if(need[index][i]<arr[i] || arr[i]>available[i])
        {
            printf("Cannot request\n");
            return;
        }
    }
    if(i==r)
    {
        for(i=0;i<r;i++)
        {
            allocation[index][i]+=arr[i];
            need[index][i]-=arr[i];
            available[i]-=arr[i];
        }
        isSafe(p,r);
    }
}

void main()
{
    int i,j,p,r;
    printf("Enter the no.of processes:");
    scanf("%d",&p);
    printf("Enter the no.of resources:");
    scanf("%d",&r);
    printf("Enter the available resources:\n");
    for(i=0;i<r;i++)
    {
        scanf("%d",&available[i]);
    }
    printf("Enter allocation matrix:\n");
    for(i=0;i<p;i++)
    {
        for(j=0;j<r;j++)
        {
            scanf("%d",&allocation[i][j]);
        }
    }
    printf("Enter max matrix:\n");
    for(i=0;i<p;i++)
    {
        for(j=0;j<r;j++)
        {
            scanf("%d",&max[i][j]);
        }
    }
    for(i=0;i<p;i++)
    {
        for(j=0;j<r;j++)
        {
            need[i][j]=max[i][j]-allocation[i][j];
        }
    }
    isSafe(p,r);

    int choice;
    printf("Is there any request[yes=1/no=0]:");
    scanf("%d",&choice);
    if(choice==1)
    {
        request(p,r);
    }
}