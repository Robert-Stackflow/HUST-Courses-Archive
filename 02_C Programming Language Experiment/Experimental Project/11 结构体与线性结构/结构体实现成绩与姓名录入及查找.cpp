#include<stdio.h>
struct student{
	char name[20];
	int score;
};
int main(){
	struct student stu[40];
	int i,j,menu,flag1=0,flag=0,n,p=0,q=0;
	int front =0,back=n-1,middle,x;
	while(scanf("%d",&menu)!=0){
		switch(menu){
			case 1:
				scanf("%d",&n);
				for(i=0;i<n;i++){
					scanf("%s",stu[i].name);
					scanf("%d",&stu[i].score);
				}
				break;
			case 2:
				for(i=0;i<n-1;i++){
					for(j=i+1;j<n;j++){
						if(stu[i].score<stu[j].score||stu[i].score==stu[j].score&&stu[i].name[0]>stu[j].name[0]||stu[i].score==stu[j].score&&stu[i].name[0]==stu[j].name[0]&&stu[i].name[1]>stu[j].name[1]){
							struct student temp=stu[i];
							stu[i]=stu[j];
							stu[j]=temp;
						}
					}
				}
				break;
			case 3:
				for(i=0;i<n;i++){
					printf("%s ",stu[i].name);
					printf("%d\n",stu[i].score);
				}
				break;
			case 4:
				//int front =0,back=n-1,middle,x;
				scanf("%d",&x);
				//flag= -1;
				front=0;
				back=n-1;
				while(front<=back){
					middle=(front+back)/2;
					if(x<stu[middle].score)
						back=middle-1;
					if(x>stu[middle].score)
						front=middle+1;
					if(x==stu[middle].score) {
						q=p=middle;
						while(stu[--p].score==x);
						while(stu[++q].score==x);
						flag=1;
						break;
					}
				}
				if(flag==0) printf("not found");
				else{
					for(i=p+1;i<q;i++){
						printf("%s %d\n",stu[i].name,stu[i].score);
					}
				} 
				flag1=1; 
				break;
		}
		if(flag1) break;
		//;	
	}
	return 0;
}

