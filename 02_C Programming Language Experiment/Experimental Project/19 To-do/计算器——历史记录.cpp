//����ʷ��¼������������չ��while���ѭ�� 
#include<stdio.h> 
int main(void)
{
	double x,y,z;
	int i=0,flag=1,history;
    char c,s[1000];
    printf("�밴���� ����� ���ֵĸ�ʽ����\n"); 
    while(flag)
    {
		scanf("%lf%s%lf",&x,&c,&y);
   		if (c=='+')
        z=(float)(x+y);
    	if (c=='-')
        z=(float)(x-y);
    	if (c=='*')
        z=(float)(x*y);
    	if (c=='/')  
        z=(float)(x/y); 
    	printf("%lf",z);
    	s[i]=(int)z;
    	printf("\n\n�Ƿ���Ҫ�������㣿\n����Ҫ����1����������0\n\n");
    	scanf("%d",&flag);
    	i++;
	}
	if(flag==0)
	{
		printf("\n\n�Ƿ���Ҫ������ʷ��¼��\n����Ҫ����1����������0\n\n");
		scanf("%d",&history);
		if(history)
			printf("%s",s);
	}
    return 0;
}
