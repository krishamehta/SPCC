// NOTE: Each line of the expected input must be having 3 tokens!!


#include <stdio.h>
#include <string.h>

void main()
{
	FILE *finput,*fmdt,*fmnt,*fpala,*fcala;
	char t1[20],t2[20],t3[20];

	int count = 0;

	finput = fopen("inputmacro.txt","r");
	fmdt = fopen("MDT.txt","w");
	fmnt = fopen("MNT.txt","w");
	fpala = fopen("PALA.txt","w");
	fcala = fopen("CALA.txt","w");

	fscanf(finput,"%s%s%s",t1,t2,t3); 

	while(count != 2)   // Hardcoded to find only two macros
	{
		if(strcmp(t1,"MACRO")==0) // Beginning of the macro	
		{
			fprintf(fmdt, "\t%s\t%s\n",t2,t3); // Insert into MDT	 
			fprintf(fmnt, "%s\n",t2); // Insert name in MNT	
			fprintf(fpala, "%s\n",t3);
			fscanf(finput,"%s%s%s",t1,t2,t3); // Read the next line
		}

		else if(strcmp(t1,"MEND")==0) // When we reach the end of the macro
		{
			count++; // Change the counter to signify we've found one
			fprintf(fmdt, "%s\n",t1); 
			strcpy(t1,t2); // This is done because when we read the line before MEND and read the next two tokens,
					// It reads the first two tokens of the line after MEND. 
			strcpy(t2,t3);
			fscanf(finput,"%s",t3);
		}

		else
		{
			fprintf(fmdt, "%s\t%s\t%s\n",t1,t2,t3); // Inside the macro, put everything in MDT
			fscanf(finput,"%s%s%s",t1,t2,t3); // Read next line
		}
	}

	
	while(count != 0){
		fprintf(fcala, "%s\n",t2); // Insert data into CALA
		fscanf(finput,"%s%s",t1,t2);
		count--; // Can use any counter which has a value of 2.
	}


	fclose(finput);
	fclose(fmnt);
	fclose(fmdt);
	fclose(fpala);
	fclose(fcala);
}

/* inputmacro.txt

MACRO M1 &ARG1,&ARG2,&ARG3
LOAD A, &ARG1
ADD B, &ARG2
STORE C, &ARG3
MEND 
MACRO M2 &ARG1,&ARG2,&ARG3
STORE A, &ARG1
ADD B, &ARG2
SUB C, &ARG3
MEND
M1 2,3,4
M2 A1,A2,A3

*/
