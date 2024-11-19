#include <stdio.h>
int A[30],A2[30];
int num,temp,head,start,pause,diff;

void sort()
{
    for(int i=0;i<num-1;i++)
    {
        for(int j=0;j<num-i-1;j++)
        {
            if(A2[j]>A2[j+1])
            {
                temp=A2[j];
                A2[j]=A2[j+1];
                A2[j+1]=temp;
            }
        }
    }
}

int dif(int a,int b)
{
    if(a>=b)
    {
        return a-b;
    }
    else
    {
        return b-a;
    }
}

void fcfs()
{
    printf("\nFCFS DISK SCHEDULING\n");
    diff=0;
    start=head;
    printf("%d",start);
    for(int i=0;i<num;i++)
    {
        diff+=dif(start,A[i]);
        start=A[i];
        printf("->%d",start);
    }
    printf("\nTotal head movements:%d\n",diff);
}

void scan()
{
    printf("\nSCAN DISK SCHEDULING\n");
    diff=0;
    start=head;
    printf("%d",start);
    for(int i=0;i<num;i++)
    {
        if(A2[i]>=head)
        {
            pause=i;
            break;
        }
    }
    for(int i=pause;i<num;i++)
    {
        diff+=dif(start,A2[i]);
        start=A2[i];
        printf("->%d",start);
    }
    printf("->199");
    diff+=dif(start,199);
    start=199;
    for(int i=pause-1;i>=0;i--)
    {
        diff+=dif(start,A2[i]);
        start=A2[i];
        printf("->%d",start);
    }
    printf("\nTotal head movements:%d\n",diff);
}

void cscan()
{
    printf("\nCSCAN DISK SCHEDULING\n");
    diff=0;
    start=head;
    printf("%d",start);
    for(int i=0;i<num;i++)
    {
        if(A2[i]>=head)
        {
            pause=i;
            break;
        }
    }
    for(int i=pause;i<num;i++)
    {
        diff+=dif(start,A2[i]);
        start=A2[i];
        printf("->%d",start);
    }
    printf("->199");
    diff+=dif(start,199);
    start=199;
    printf("->0");
    diff+=dif(start,0);
    start=0;
    for(int i=0;i<=pause-1;i++)
    {
        diff+=dif(start,A2[i]);
        start=A2[i];
        printf("->%d",start);
    }
    printf("\nTotal head movements:%d\n",diff);
}

void main()
{
    printf("Maximum disk size:200\n");
    printf("Enter no.of requests:");
    scanf("%d",&num);
    printf("Enter the requests:\n");
    for(int i=0;i<num;i++)
    {
        scanf("%d",&A[i]);
        A2[i]=A[i];
    }
    printf("Enter head:");
    scanf("%d",&head);
    sort();

    fcfs();
    scan();
    cscan();
}