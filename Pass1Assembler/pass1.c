#include<stdio.h>
#include<string.h>

int main()
{
    char id[10],str[10],
    mot[][50]={{"L"},{"ST"},{"A"}},
    pot[][50]={{"START"},{"END"},{"DC"},{"DS"},{"USING"}},
    st[][50]={{"PRG"},{"FOUR"},{"FIVE"},{"TEMP"}},
    lt[][50]={{"=F'4'"},{"=F'5'"}},
    test[][50]={{""},{""}};
    char ch[10]={0};
    int x,i,j,k,parsed,motlen,potlen,stlen,ltlen,oc=0;
    FILE *fp1,*fpmot,*fppot,*fpst,*fplt;
    fp1=fopen("pass1File.txt","r");
    fpmot=fopen("mot.txt","a");
    fppot=fopen("pot.txt","a");
    fpst=fopen("symbol.txt","a");
    fplt=fopen("literal.txt","a");
    motlen=sizeof(mot)/sizeof(mot[0]);
    potlen=sizeof(pot)/sizeof(pot[0]);
    stlen=sizeof(st)/sizeof(st[0]);
    ltlen=sizeof(lt)/sizeof(lt[0]);
    //printf("%d %d %d %d\n",motlen,potlen,stlen,ltlen);
    for(k=0;fgets(str,50,fp1)!=NULL;k+=2);       //to find address of END
    k-=2;

    fclose(fp1);
    fp1=fopen("pass1File.txt","r");
    for(x=0;fgets(ch,50,fp1)!=NULL;x+=2)
    {
        parsed=0;
        printf("%d %s",x,ch);

        for(i=0;i<motlen&&parsed==0;i++)
        {
            if(strstr(ch,mot[i]))
            {
                strcpy(str,strstr(ch,mot[i]));
                oc=0;
                for(j=0;j<strlen(str);j++)
                {
                    if(str[j]==' ')
                        oc++;                                   //calc operands
                }
                //printf("\n1. %d %s",oc,mot[i]);
                fprintf(fpmot,"\n%s\t\t2\t\t%d",mot[i],oc);
                parsed=1;
                break;
            }
        }

        for(i=0;i<potlen&&parsed==0;i++)
        {
            if(strstr(ch,pot[i]))
            {
               // printf("\n2. %d %s",x,pot[i]);
                fprintf(fppot,"\n%s\t\t%d",pot[i],x);
                parsed=1;
                break;
            }
       }

        //symbols are followed by pseudo-opcodes
        for(i=0;i<stlen;i++)
        {
            parsed=0;
            for(j=0;j<potlen&&parsed==0;j++)
            {
                //printf("\n %s",pot[j]);
                if((strstr(ch,":")&&strstr(ch,st[i])) || (strstr(ch,pot[j])&&strstr(ch,st[i])))
                {
                    //printf("\n3. %d %s",x,st[i]);
                    fprintf(fpst,"\n%s\t%d\t2\tR",st[i],x);
                    parsed=1;
                    break;
                }
           }
           if(parsed==1)
            i++;                            //to not let N1 twice
        }
         for(i=0;i<ltlen&&parsed==0;i++)
            {
                if((strstr(ch,"=")&&strstr(ch,lt[i])))
                {
                    //printf("\n4. %d %s",k,lt[i]);
                    fprintf(fplt,"\n%s\t%d\t2\tR",lt[i],k);
                    parsed=1;
                    break;
                }
           }
    }
    fclose(fp1);
    fclose(fpmot);
    fclose(fppot);
    fclose(fpst);
    fclose(fplt);

    printf("\nPass 1 Complete...Tables updated...");
    return 0;
}
/*pass1File.txt
PRG START 0
USING *,15
L 1,FIVE
A 1,FOUR
ST 1,TEMP
FOUR DC =F'4'
FIVE DC =F'5'
TEMP DS 1F
END
*/
