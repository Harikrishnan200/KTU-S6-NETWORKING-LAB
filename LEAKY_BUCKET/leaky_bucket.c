
#include <stdio.h>
#include <stdlib.h>
#define min(x,y) (x<y)?x:y

int main()
{
	int outrate,drop=0,bsize,rem=0,nsec;
	int input[20]={0},i=0,ch,x,flag;
	
	printf("Enter Bucket(Bytes) Size : ");
	scanf("%d",&bsize);
	printf("Enter output rate(Bytes/sec) : ");
	scanf("%d",&outrate);
	
	do
	{
		printf("Enter the size(Bytes) of packet coming at sec %d : ",i+1);	
		scanf("%d",&input[i]);
		i++;
		printf("Enter 1 to continue/ 0 to quit :");
		scanf("%d",&ch);
	}while(ch);
	
	nsec=i;
	
	
	printf("\nTime Received\t Sent \t Dropped \t Remaining\n");
	for(i=0;i<nsec ||rem ;i++)
	{	
		flag=0;
		printf("%d",i+1);
		printf(" \t%d",input[i]);

		if(input[i]+rem>bsize){
			flag=input[i];
			printf("\t%3d",min(rem,outrate));
			if(rem-outrate>0)
				rem=rem-outrate;
			else
				rem=0;
			printf("%10d%15d\n",flag,rem);
			continue;
		}	
        
		printf("\t%3d",min(input[i]+rem,outrate));
		
		if((x=input[i]+rem-outrate)>0)
		{
			if(x>bsize)
			{
				rem=bsize;
				drop=x-bsize;
			}
			else
			{
				rem=x;
				drop=0;
			}
		}
		else
		{
			drop=0;
			rem=0;
		}
		
		/*
		if(flag!=0)
		{
			rem -= (flag+outrate);
			printf("%10d%15d\n",flag,rem);
			flag=0;
		}

		else
				
		*/
			printf("%10d%15d\n",drop,rem);
	}
	return 0;
}
