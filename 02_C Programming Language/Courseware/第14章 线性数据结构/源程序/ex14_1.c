#include <stdio.h>
struct u{
	char name[9];	
	int age;
};
struct v{
	char name[9];	
	short age;	
	int wage;
};
int main(void)
{	
	struct u a;	
	struct v b;
	printf("sizeof a=%d\t",sizeof a); 	
	printf("a.name=%p\t",a.name); 
	printf("&a.age=%p\n",&a.age);	
	printf("sizeof b=%d\t",sizeof b);
	printf("b.name=%p\t",b.name);	
	printf("&b.age=%p\t",&b.age);
	printf("&b.wage=%p\n",&b.wage);
	return 0;
}
