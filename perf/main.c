#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void swap(const void* a, const void* b, int size);
void quicksort(void* base, int left, int right, int size, int (*cmp)(const void* a, const void* b));
int cmp_string(const void* a, const void* b);
int cmp_int(const void* a, const void* b);

int comp(const void *j, const void *i);
void show_card(int b[], char n[]);
void shuffle(void);

int main (void)
{
	int i = 0;
	while(i < 100000){
		shuffle();
		i++;
	}
	return 0;
}

void shuffle(void)
{
	static char n[] = {'2','3','4','5','6','7','8','9','T','J','Q','K','A'};
	int *a = (int *)malloc(sizeof(int)*53);
	int *b1 = (int *)malloc(sizeof(int)*13);
	int *b2 = (int *)malloc(sizeof(int)*13);
	int *b3 = (int *)malloc(sizeof(int)*13);
	int *b4 = (int *)malloc(sizeof(int)*13);
	memset(a,0,sizeof(int)*53);
	memset(b1,0,sizeof(int)*13);
	memset(b2,0,sizeof(int)*13);
	memset(b3,0,sizeof(int)*13);
	memset(b4,0,sizeof(int)*13);
	int b11=0,b22=0,b33=0,b44=0,t=1,m,flag,i;
	while(t<52)
	{
		m=rand()%52;
		for(flag=1,i=1;i<=t&&flag;i++)
			if(m==a[i])
				flag=0;

		if(flag)
		{
			a[t++]=m;
			if(t%4==0)
				b1[b11++]=a[t-1];
			else
				if(t%4==1)
					b2[b22++]=a[t-1];
				else
					if(t%4==2)
						b3[b33++]=a[t-1];
					else
						if(t%4==3)
							b4[b44++]=a[t-1];
		}
	}

	/*
	qsort(b1, 13, sizeof(int), comp);
	qsort(b2, 13, sizeof(int), comp);
	qsort(b3, 13, sizeof(int), comp);
	qsort(b4, 13, sizeof(int), comp);
	*/
	quicksort(b1, 0, 12, sizeof(int), cmp_int);
	quicksort(b2, 0, 12, sizeof(int), cmp_int);
	quicksort(b3, 0, 12, sizeof(int), cmp_int);
	quicksort(b4, 0, 12, sizeof(int), cmp_int);

	show_card(b1,n);
	show_card(b2,n);
	show_card(b3,n);
	show_card(b4,n);
}

void show_card(int b[], char n[])
{
	int i;
	printf("\n\006 ");
	for(i=0;i<13;i++){
		if(b[i]/13==0)
			printf("%c ",n[b[i]%13]);
	}

	printf("\n\003 ");
	for(i=0;i<13;i++){
		if(b[i]/13==1)
			printf("%c ",n[b[i]%13]);
	}

	printf("\n\004 ");
	for(i=0;i<13;i++){
		if(b[i]/13==2)
			printf("%c ",n[b[i]%13]);
	}

	printf("\n\005 ");
	for(i=0;i<13;i++){
		if(b[i]/13==3 || b[i]/13==4)
			printf("%c ",n[b[i]%13]);
	}

	printf("\n");
}

int comp(const void*j, const void*i)
{
	return (*(int*)i-*(int*)j);
}

void swap(const void* a, const void* b, int size)
{
	char tmp = 0;
	int i = 0;
	while (size > 0) {
		tmp = *((char*)a + i);
		*((char*)a + i) = *((char*)b + i);
		*((char*)b + i) = tmp;
		++i;
		--size;
	}
}

void quicksort(void* base, int left, int right, int size, int (*cmp)(const void* a, const void* b))
{
	if (left >= right) return;
	char* pleft = (char*)base + left * size;
	char* pkey = (char*)base + (left + (right - left) / 2) * size;
	swap(pleft, pkey, size);
	int last = left;
	char* plast = (char*)base + last * size;
	for (int i = left + 1; i <= right; ++i) {
		char* pi = (char*)base + i * size;
		if (cmp(pi, pleft) < 0) {
			++last;
			plast = (char*)base + last * size;
			swap(pi, plast, size);
		}
	}
	swap(pleft, plast, size);
	quicksort(base, left, last - 1, size, cmp);
	quicksort(base, last + 1, right, size, cmp);
}

int cmp_string(const void* a, const void* b)
{
	const char** lhs = (const char**)a;
	const char** rhs = (const char**)b;
	return strcmp(*lhs, *rhs);
}

int cmp_int(const void* a, const void* b)
{
	const int* lhs = (const int*)a;
	const int* rhs = (const int*)b;
	if (*lhs < *rhs) {
		return -1;
	} else if (*lhs == *rhs) {
		return 0;
	} else {
		return 1;
	}
}




