#include <stdio.h>
int i,j,k,numh=0,numpf=0;
float hit=0,miss=0;

void fifo(int rs[],int num,int frame[],int numf)
{
    j=0;
    printf("ref\t");
    for(i=0;i<numf;i++)
    {
        printf("f%d\t",i+1);
    }
    printf("\n");
    for(i=0;i<num;i++)
    {
        printf("%d\t",rs[i]);
        int avail=0;
        for(k=0;k<numf;k++)
        {
            if(frame[k]==rs[i])
            {
                numh++;
                avail=1;
            }
        }
        if(avail==0)
        {
            frame[j]=rs[i];
            j=(j+1)%numf;
            numpf++;
            for(k=0;k<numf;k++)
            {
                printf("%d\t",frame[k]);
            }
        }
        printf("\n");
    }
    hit=(float)numh/num;
    miss=(float)numpf/num;
    printf("no.of page faults:%d\n",numpf);
    printf("Hit ratio:%.2f\nMiss ratio:%.2f\n",hit*100,miss*100);
}

void main()
{
    int rs[100],numf,num=0;
    printf("Enter the reference string(enter -1 to quit):\n");
    for(i=0;i<100;i++)
    {
        scanf("%d",&rs[i]);
        if(rs[i]==-1)
        {
            break;
        }
        num++;
    }
    printf("Enter the no.of frames:");
    scanf("%d",&numf);
    int frame[numf];
    for(i=0;i<numf;i++)
    {
        frame[i]=-1;
    }
    fifo(rs,num,frame,numf);
}