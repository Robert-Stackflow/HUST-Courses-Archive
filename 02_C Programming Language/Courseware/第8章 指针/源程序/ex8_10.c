int strlen(char *p)	/* p指向被测字符串 */
{	char *q=p; 	/* 声明q,q指向被测字符串 */
	while(*p) 	/* *p等于'\0'时结束循环 */
		p++; 	/* p指向下一个字符 */
	return (p-q); 	/* p-q就是字符串的长度 */
}
