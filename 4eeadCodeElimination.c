#include <stdio.h>
#include <time.h>

int global;

int before_optimize()
{
	int i;
	i=1;
	global=1;
	global=2;
	return global;
	global=3;
}

int after_optimize()
{
	global=2;
	return global;
}

void main()
{
	int a,b;
	clock_t start, end;
	
	start = clock();
	a=before_optimize();
	end = clock();
	printf("\nValue of global variable before optimization %d",a);
	printf("\nTime taken: %f", ((double)(end-start))/CLOCKS_PER_SEC );
	start = clock();
	b=after_optimize();
	end = clock();
	printf("\nValue of global variable after optimization %d",b);
	printf("\nTime taken: %f", ((double)(end-start))/CLOCKS_PER_SEC );
}
