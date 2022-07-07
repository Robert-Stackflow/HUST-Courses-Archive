int main(void)
{	int i;
	for(i=0;i<2;i++){
		printf("%s\t",registration_form1[i].num);
		printf("%s\t",registration_form1[i].name);
		printf("%c\t",registration_form1[i].sex);
		printf("%s ",registration_form1[i].birthday.month);
		printf("%d ",registration_form1[i].birthday.day);
		printf("%d\n",registration_form1[i].birthday.year);
		printf("%s\t",registration_form1[i].address);
		printf("%8.2lf\t",registration_form1[i].income);
		printf("%s\t",registration_form1[i].phone_number);
		printf("%s\n",registration_form1[i].email);
	}
	return 0;
}
