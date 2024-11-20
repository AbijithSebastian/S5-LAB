#include <stdio.h>
struct frame{
    int content,freq,cnt;
}frame[100];

void main(){
    int i,j,nump,numf,numpf,min,cnt,page[100],id=0;
    float hit=0,miss=0;
    printf("Enter the no.of pages:");
    scanf("%d",&nump);
    printf("Enter the pages:\n");
    for(i=0;i<nump;i++){
        scanf("%d",&page[i]);
    }
    printf("Enter the no.of frames:");
    scanf("%d",&numf);
    for(i=0;i<numf;i++){
        frame[i].content=-1;
        frame[i].freq=0;
        frame[i].cnt=0;
    }

    printf("ref\tf1\tf2\tf3\n");
    for(numpf=0,cnt=1,i=0;i<nump;i++){
        printf("%d\t",page[i]);
        for(j=0;j<numf;j++){
            if(frame[j].content==page[i]){
                frame[j].freq++;
                break;
            }
        }
        if(j==numf){
            if(id<numf){
                frame[id].content=page[i];
                frame[id].freq++;
                frame[id].cnt=cnt++;
                id++;
            }
            else{
                for(min=0,j=0;j<numf;j++){
                    if(frame[j].freq<frame[min].freq){
                        min=j;
                    }
                    else if(frame[j].freq==frame[min].freq && frame[j].cnt<frame[min].cnt){
                        min=j;
                    }
                }
                frame[min].content = page[i];
                frame[min].freq = 1;
                frame[min].cnt = cnt++;
            }
            numpf++;
        }
        for (j=0;j<numf;j++) {
            if (frame[j].content!= -1) {
                printf("%d\t",frame[j].content);
            }
        }
        printf("\n");
    }
    hit=(float)(nump-numpf)/nump;
    miss=(float)numpf/nump;
    printf("no.of page faults:%d\n",numpf);
    printf("Hit ratio:%.2f\nMiss Ratio:%.2f\n",hit*100,miss*100);
}