#include <stdio.h>
int i,j,k,numh=0,numpf=0,max;
float hit=0,miss=0;

void reset(int count[],int numf)
{
    for(int i=0;i<numf;i++)
    {
        count[i]=0;
    }
}

void lru(int rs[],int num,int frame[],int numf)
{
    int count[numf],index;
    reset(count,numf);
    printf("ref\t");
    for(i=0;i<numf;i++)
    {
        printf("f%d\t",i+1);
    }
    printf("\n");
    for(i=0;i<3;i++)
    {
        printf("%d\t",rs[i]);
        frame[i]=rs[i];
        numpf++;
        for(k=0;k<numf;k++)
        {
            printf("%d\t",frame[k]);
        }
        printf("\n");
    }
    for(i=3;i<num;i++)
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
            for(k=0;k<numf;k++)
            {
                for(j=i-1;j>=0;j--)
                {
                    if(frame[k]!=rs[j])
                    {
                        count[k]++;
                    }
                    else
                    {
                        break;
                    }
                }
            }
            max=0;
            for(k=0;k<numf;k++)
            {
                if(max<count[k])
                {
                    max=count[k];
                    index=k;
                }
            }
            frame[index]=rs[i];
            numpf++;
            for(k=0;k<numf;k++)
            {
                printf("%d\t",frame[k]);
            }
            reset(count,numf);
        }
        printf("\n");
    }
    hit=(float)numh/num;
    miss=(float)numpf/num;
    printf("No.of page faults:%d\n",numpf);
    printf("Hit ratio:%.2f\nMiss ratio:%.2f\n",hit*100,miss*100);
}

void main()
{
    int rs[100],num=0,numf;
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
    printf("Enter no.of frames:");
    scanf("%d",&numf);
    int frame[numf];
    for(i=0;i<numf;i++)
    {
        frame[i]=-1;
    }
    lru(rs,num,frame,numf);
}