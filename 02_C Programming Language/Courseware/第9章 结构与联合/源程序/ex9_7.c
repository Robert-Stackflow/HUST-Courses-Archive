#include "stdio.h"
struct motion{ 
		double size;
		char dimension[12];
};
struct motion get_motion(void); /*以结构变量作为函数的返回值*/
struct motion add_motion(struct motion u,struct motion v);/*以结构变量作为形参和返回值*/
double get_motion_size(struct motion u);/*以结构变量作为形参，以结构成员作为返回值*/
double add_motion_size(double,double);/*double类型形参和返回值 */ 
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
struct motion get_motion(void)/*以结构变量作为函数的返回值 */ 
{	struct motion a;
	printf("input the value of member size and dimension\n");
	scanf("%lf",&a.size);
	scanf("%s",a.dimension);
	return a;
}
struct motion add_motion(struct motion u,struct motion v)/*以结构变量作为形参和返回值 */
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
{	/* get_motion_size函数以结构变量作为形参，以结构成员作为返回值 */
		return u.size;
}
double add_motion_size(double x,double y)
{	/* add_motion_size函数可以用结构成员作为形参和返回值，也可用于其他double类型形参和返回值 */
		return x+y;
}
int cmp_dimension(char *s,char *t)/*比较两个物理量的量纲,相同，返回0；否则返回非0*/
{	while(*s==*t && *s!='\0')
		s++,t++;
	return *s-*t;
}
void mystrcpy(char *s,char *t)/* mystrcpy将t串拷贝到s串 */
{	char *p=s;
	while(*p++=*t++);
}

