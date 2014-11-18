#include<stdio.h>
#include<string.h>
#include<stddef.h>.
#include "str_rep.h"
   FILE *fp,*fw;
    int countdef=0;
    int c,expanding=0;
    char lbl[20],opc[20],opr[20];
    char name[10][10]={"","","","","","","","","",""},arg[10][100]={"","","","","","","","","",""},def[30][4096]={"","","","","","","","","",""},if_tab[10][40]={"","","","","","","","","",""};
	char unique_Label='A';


	
int main (){
    int test;
    int counter=99;
    int j,check_endof_macro;
    check_endof_macro=1;
    j=0;
    fp = fopen("sic_xecode.c","r");             // open input file
    fw = fopen("expanded.c","w");                      // expanded file
    while(1){
        j++;
        if( feof(fp) ){break ;                  // check end of file
        }
        fscanf(fp,"%s %s %s",lbl,opc,opr);	
        counter=search(opc);                           // search if macro name is already present 
        if(counter!=99)
        {
       	
	 write_to_file(1,counter);
   	printf("\nok\n");	
		continue; 	//Not to read same line again
        }
        write_to_file(0,0);
        if(strcmp(opc,"MACRO")==0){  
            strcat(arg[countdef], opr);
            strcat(name[countdef], lbl);
		check_endof_macro=1;
            while(check_endof_macro)     
               {          
                 fscanf(fp,"%s %s %s",lbl,opc,opr);
		 counter=search(opc);
			if(counter!=99)
			{
		
				nestmacro(counter,countdef);
				
			   	printf("\nok\n");	
					continue; 	//Not to read same line again
			}
                 write_to_file(0,0);
                 check_endof_macro=strcmp(opc,"MEND"); 
                 if(check_endof_macro!=0)
                 {

              write_to_deftab(countdef);
                     }        
            }
            	    countdef++;
           
        }
    }


    fclose(fp);
}


int search(char *macro_name)
{
	int i;

	for(i=0;i<countdef;i++)
	{
		if(strcmp(macro_name,name[i])==0)
		{
		
			return i;
		}
	}
	return 99;
}
char *split_Argtab(char str[128],int count_Split)
{
	
	char * pch=" ";

 
  if(count_Split>0)
  {
  	 pch = strtok (str,",");                // string get tokenized & it return ptr of last token
  	 
  while (pch != NULL && count_Split>1)
  {
   
    pch = strtok (NULL, ",");
   
    count_Split--;
  }	
  }
 
  return pch;

}


int write_to_file(check_Expand,counter)                         // counter = index
{
	char operands[10][128]={"","","","","","","","","",""};
	char arg_operands[10][128]={"","","","","","","","","",""};     //arg array
	char * pch;             // token ptr
	char *split_opnd=" ";
	char *token;
	int icount=0,len=0,ii=0,count_arg=0,i,count_Split;      // ii is operand index
	char *opnd_Replace;
	char dummy[128]={""};                   //duplicate of opr array that index
	char def_buffer[4096];                  // 
	if(check_Expand==1)
	{
		fprintf(fw, ";");
		fprintf(fw, lbl);
		fprintf(fw, " ");
		fprintf(fw, opc);
		fprintf(fw, " ");	
		fprintf(fw, opr);
		fprintf(fw, "\n");
		
		len=strlen(opr)-1;
		while(ii!=len)                         //Splitting Operand on the basic of ','        
		{
			if(opr[ii]==',')
				count_arg++;            // count the no. of argument in macroop
			ii++;
		}
		
		
			  
		for (i =0; i <=count_arg ; i++)
		{
			/* code */
			strcpy(dummy,opr);
			//printf("#%s\n\n",split_Argtab(dummy,i+1));
			strcat(operands[i],split_Argtab(dummy,i+1));            // store the each arg in operand 

		}
		//Splitted Opnd
		count_arg=0;
		ii=0;
		//Splitting Arguments
		len=strlen(arg[counter])-1;
		while(ii!=len)
		{
			if(arg[counter][ii]==',')
				count_arg++;
			ii++;
		}

		for (i =0; i <=count_arg ; i++)
		{
			/* code */
			strcpy(dummy,arg[counter]);
			//printf("#%s\n\n",split_Argtab(dummy,i+1));
			strcat(arg_operands[i],split_Argtab(dummy,i+1));        // storing arg token in arg operands
			
		}
		//Splitting arg done
		//Copying argtab
		i=0;
		for (i =0; i <=count_arg ; i++)
		{
			
			strcat(def_buffer,replace_str2(def[counter],arg_operands[i],operands[i]));
			def[counter][0]='\0';
			strcat(def[counter],def_buffer);
			def_buffer[0]='\0';
			printf("%s\n",def[counter] );
		}
		
		//copying done
		
		fprintf(fw, def[counter]);
		count_arg=0;//to count no. of again for different macro
		return 2;
	}
	fprintf(fw, lbl);
	fprintf(fw, " ");
	fprintf(fw, opc);
	fprintf(fw, " ");	
	fprintf(fw, opr);
	fprintf(fw, "\n");
	return 1;
}
int nestmacro(int counter,int macroCounter)
{
	 strcat( def[macroCounter],def[counter]);
}
int write_to_deftab(int deftab_Counter)
{
	     		char label[40]=" ";
	     		if(strcmp("NULL",lbl)!=0)
	     		{
	     			
	     			label[0]='$';
	     			label[1]=unique_Label;
	     			unique_Label = unique_Label + 1;
	     			strcat(label,lbl);
	     			strcat(def[deftab_Counter], label);
	     		}
	     		else
	     		{
	     			strcat(def[deftab_Counter], lbl);
	     		}
                strcat(def[deftab_Counter], " ");
                strcat(def[deftab_Counter], opc);
                strcat(def[deftab_Counter], " ");
                strcat(def[deftab_Counter], opr);
                strcat(def[deftab_Counter], "          ");
                strcat(def[deftab_Counter], "\n"); 
}
