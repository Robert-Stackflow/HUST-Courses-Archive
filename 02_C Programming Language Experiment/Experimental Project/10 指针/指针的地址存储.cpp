#include<stdio.h>
//����ָ��ı������ֵ 
void change(int *p){
	*p=888;
}
//����ָ���ַ����������ֵ 
void swap(int *p1,int *p2){
	int temp;
	temp=*p1;
	*p1=*p2;
	*p2=temp;
}
int main(void){
	int num=10;
	int num1=20;
	char c='a';
	int *p=&num;
	//ָ��ָ���ǿ����޸ĵġ���p=&num1;
	int *p1=&num1;
	//Ҳ����ͨ����ֵ�ķ�ʽ�ı�ָ��ָ�򡪡�p=p1; 
	char*q=&c;
	//p�ǵ�ַ��*p��ָ��ı��� 
	printf("&num:%x\tp:%x\t&p:%x\tnum:%d\t*p:%d\t*q:%c\tq:%x\n",&num,p,&p,num,*p,*q,q);
	swap(p,p1);
	printf("������õ���num:%d\tnum1:%d\n",num,num1);
	*p=44;//����ͨ��ָ��ı������ֵ 
	printf("&num:%x\tp:%x\t&p:%x\tnum:%d\t*p:%d\t*q:%c\tq:%x\n",&num,p,&p,num,*p,*q,q);
	change(p);//Ҳ�������ú���ʵ�ָı�ֵ�Ĺ��� 
	printf("&num:%x\tp:%x\t&p:%x\tnum:%d\t*p:%d\t*q:%c\tq:%x\n",&num,p,&p,num,*p,*q,q);
	//char���͵�ָ��Ҳ���Ըı������ֵ 
	*q='b';
	printf("&num:%x\tp:%x\t&p:%x\tnum:%d\t*p:%d\t*q:%c\tq:%x\n",&num,p,&p,num,*p,*q,q);
	return 0;
}
