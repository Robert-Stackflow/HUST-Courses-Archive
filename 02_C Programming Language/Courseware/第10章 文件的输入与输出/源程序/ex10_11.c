#include <stdio.h>
#include <stdarg.h>
void error_msg(char *format,char *str0,char *str1,char *str2);
int main(void)
{	error_msg("caonot open file %s,%s,%s\n","test","test1","test2");
	error_msg("caonot receive %s,%s,%s\n","message","message1","message2");
	return 0;
}
void error_msg(char *format,char *str0,char *str1,char *str2)
{	va_list ptr;
	va_start(ptr,format);
	fprintf(stderr, "ERROR in %s: ", str0);
	vfprintf(stderr,format,ptr);
	va_end(ptr);
}

