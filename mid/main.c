#include <stdio.h>
#include <string.h>

void swap(int* a,int* b){
	int temp = *a;
	*a = *b;
	*b = temp;
}

//printf("You're plastic");

int main(){
	//printf("YOURE SPECIAL\n");
	
	//int i;
	//char *a[] = {"happen","to","make","stop","\"fetch\" ", "tryin",};
	//int o[]= {3,5,1,2,4,0};

	//for(i = 0; i < 6; i++){
	//	printf("%s",a[o[i]]);
	//}
//printf("You're plastic");	
	char s[] = "On wednesdays we wear pink!";
	*(s+1) = 'O';
	*(s+2) = 'n';
	*(s+3) = ' ';
	*(s+4) = 'S';
	*(s+5) = 'a';
	*(s+6) = 't';
	*(s+7) = 'u';
	*(s+8) = 'r';
	*(s+26) = '.';
	printf("%s\n",  s+1);

	int j = 0;
	for(int i = 0; i < 101; i++){
		j += i;
	}
	printf("%d",j);

	char* str = "Heyllo!";
	char str2[8] = "Helloyo!";

	strcpy(str2,str);
	printf("%s\n", str);
	

	//char *s = "I just moved here from Africa.";
	//s[17] = '.';
	//s[18] = '\0';
	//printf("%s",s);

	//char* p, s[] = "!ocoC nnelG ,og uoY  !ocoC nnelG ,uoy rof ruoF";
	//for(p = s + strlen(s)-1; *p; p--)
		//putchar(*p);

	//int a = 3, b = 5;
	//swap(&a,&b);
	//printf("a:%d\n",a);
	//printf("b:%d\n",b);

	//void freeplusplus(void ** a){
	//	free(*a);
	//	a = NULL;
	//
	//}
	//
	//char* strndup(const char* s, size_t n){
	//	char * sec =n*  malloc(sizeof(char));
	//	for(int i = 0; i < n; i++)
	//		sec[i] = s[i];
	//	sec[i] '\0';
	//     return sec;	
	//}
	
	//int i;
	//unsigned long long int prod;
	//unsigned long long r =1, oo =2, Ke = 5, in = 5, n = 5,
	//	      v = 3251, a = 3371, p =51287, G = 52027;
	//prod = Ke * v * in * (G * n * a * p * oo + r);

	//for (i = 0; i < 8; i++)
	//	putchar(((char *) &prod)[i]);
	//putchar('\n');

	return 0;
}


