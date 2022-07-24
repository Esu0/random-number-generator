#include<random.h>
#include<stdio.h>
#include<time.h>

int main()
{
	mt19937 mt;
	mt_init(&mt, (unsigned long long)time(NULL));
	clock_t start, end;
	start = clock();
	for(int i = 0; i < 100000000; i++)
	{
		mt_gen(&mt);
	}
	end = clock();
	printf("%ldms", end - start);
}
