#include "stdio.h"
struct motion{ 
		double size;
		char dimension[12];
};
struct motion get_motion(void); /*�Խṹ������Ϊ�����ķ���ֵ*/
struct motion add_motion(struct motion u,struct motion v);/*�Խṹ������Ϊ�βκͷ���ֵ*/
double get_motion_size(struct motion u);/*�Խṹ������Ϊ�βΣ��Խṹ��Ա��Ϊ����ֵ*/
double add_motion_size(double,double);/*double�����βκͷ���ֵ */ 
int cmp_dimension(char *,char *);
void mystrcpy(char *,char *);
int main(void)
{	struct motion b={12.5,"m/s"},c={26.7,"m/s"},d;
	b=get_motion();
	printf("b.size=%lf\t",b.size);
	printf("b.dimension is %s\n",b.dimension);
	d=add_motion(b,c);
	printf("d.size=%lf\t",d.size);
	printf("d.dimension is %s\n",d.dimension);
	d.size=get_motion_size(b);
	printf("d is %lf%s\n",d.size,d.dimension);
	d.size=add_motion_size(d.size,c.size);
	printf("d is %lf%s\n",d.size,d.dimension);
	return 0;
}
struct motion get_motion(void)/*�Խṹ������Ϊ�����ķ���ֵ */ 
{	struct motion a;
	printf("input the value of member size and dimension\n");
	scanf("%lf",&a.size);
	scanf("%s",a.dimension);
	return a;
}
struct motion add_motion(struct motion u,struct motion v)/*�Խṹ������Ϊ�βκͷ���ֵ */
{	struct motion a;
	if(!cmp_dimension(u.dimension,v.dimension)){
		a.size=u.size+v.size;
		mystrcpy(a.dimension,u.dimension);
	}
	else{
		printf("dimension of the member is conflicting! can't adding ...  \n");
		a.size=0;
		mystrcpy(a.dimension,"");
	}
	return a;
}
double get_motion_size(struct motion u)
{	/* get_motion_size�����Խṹ������Ϊ�βΣ��Խṹ��Ա��Ϊ����ֵ */
		return u.size;
}
double add_motion_size(double x,double y)
{	/* add_motion_size���������ýṹ��Ա��Ϊ�βκͷ���ֵ��Ҳ����������double�����βκͷ���ֵ */
		return x+y;
}
int cmp_dimension(char *s,char *t)/*�Ƚ�����������������,��ͬ������0�����򷵻ط�0*/
{	while(*s==*t && *s!='\0')
		s++,t++;
	return *s-*t;
}
void mystrcpy(char *s,char *t)/* mystrcpy��t��������s�� */
{	char *p=s;
	while(*p++=*t++);
}

