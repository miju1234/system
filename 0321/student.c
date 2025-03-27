#include <stdio.h>

int main(){
	char name[50];
	char student_id[20];

	printf("학번 : ");
	scanf("%s",student_id);

	printf("이름 : ");
	scanf("%s",name);

	printf("\n학번은: %s\n",student_id);
	printf("\n이름은: %s\n",name);

	return 0;
}
