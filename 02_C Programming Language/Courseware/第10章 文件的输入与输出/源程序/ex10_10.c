int main(void)
{	char str[80],a[20] = "c:\\data.dat",b[30];
	int x=123;
	sprintf(str,"%s %s %d ","input code and price please!\n",a,x);
	printf("in str :%s\n",str);
	sscanf(str,"%s %s %d ",b,a,&x);
	printf("in var: %s\t%s\t%d\n",b,a,x);
	return 0;
}