#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
	char *str;
	str = (char *)malloc(sizeof(char) * 5);		//5개의 공간을 만들고 12문자 할당
	strcpy(str, "Hello World\n");

	return 0;
}
