#include <stdio.h>
#include <time.h>

void before_optimise()
{
    float r,pi=3.14;
    clock_t start,end;
    double cpuTimeUsed;

    printf("\nEnter the value of radius:\n");
    scanf("%f",&r);

    start = clock();

    printf("\nThe Circumference of circle is:%f\n",(2*pi*r));
    printf("\nThe Area of circle is:%f\n",(pi*r*r));

    end = clock();

    cpuTimeUsed = ((double)(end-start))/CLOCKS_PER_SEC;

    printf("\nTime taken = %f\n",cpuTimeUsed);
}

void after_optimise()
{
    float r,pi=3.14,temp;
    clock_t start,end;
    double cpuTimeUsed;
    
    printf("\nEnter the value of radius:\n");
    scanf("%f",&r);
    
    start = clock();

    temp=pi*r;
    
    printf("\nThe Circumference of circle is:%f\n",(2*temp));
    printf("\nThe Area of circle is:%f\n",(temp*r));

    end = clock();

    cpuTimeUsed = ((double)(end-start))/CLOCKS_PER_SEC;

    printf("\nTime taken = %f\n",cpuTimeUsed);
}

void main()
{
    before_optimise();
    after_optimise();
}
