#include "headers.h"

configuration setConfig(char* config){
	FILE* fp;
	configuration c;
	char ch;
	int flag = 0;
	char temp[SIZEofBUFF];
	char number[SIZEofBUFF];
	char str[SIZEofBUFF];
	fp = fopen(config,"r");
	c.Clasters = -1;
	c.HashFunctions = -1;
	c.HashTables = -1;
	c.ClaransFraction = -1;
	c.ClaransIterations = -1;
	if(fp == NULL){
		return c;
	}
	while(!feof(fp)){
		ch = fgetc(fp);
		if(ch == ' '){
			ch = fgetc(fp);
			while (ch != '\n'){
				if(ch >= 0 || ch <= 9){
					sprintf(str,"%c",ch);
					strcat(number,str);
					flag = 1;	
				}
				ch = fgetc(fp);
			}
			if(flag == 1){
				if(strcmp(temp,"number_of_clusters:"))
					c.Clasters = atoi(number);
				if(strcmp(temp,"number_of_hash_functions:"))
					c.HashFunctions = atoi(number);
				if(strcmp(temp,"number_of_hash_tables:"))
					c.HashTables = atoi(number);
				if(strcmp(temp,"clarans_set_fraction:"))
					c.ClaransFraction = atoi(number);
				if(strcmp(temp,"clarans_iterations:"))
					c.ClaransIterations = atoi(number);
			}
			strcpy(temp,"");
			strcpy(number,"");
		}
		sprintf(str,"%c",ch);
		strcat(temp,str);
		flag = 0;
	}
	if(c.HashFunctions == -1)
		c.HashFunctions = 4;
	if(c.HashTables == -1)
		c.HashTables = 5;
	if(c.ClaransFraction == -1)
		c.ClaransFraction = c.Clasters;
	if(c.ClaransIterations == -1)
		c.ClaransIterations = 2;
	return c;
}

int readData(char* data,char* config){
	FILE* fp;
	int flag = -1; // 1 for ham, 2 for euc, 3 for matrix 
	char XXX[SIZEofBUFF];
	char type[SIZEofBUFF];
	fp = fopen(data,"r");
	if(fp == NULL){
		perror("read data");
		exit(1);
	}
	fscanf(fp,"%s %s",XXX,type);			
	if( strcmp(XXX,"@metric_space") != 0){
		printf("Error... Incorect data file\n");
		exit(1);
	}
	if( strcmp(type,"vector") == 0){			
		printf("\nvector\n");
		flag = 2;
		//VecMain(data,query,k,L);
	}
	else if(strcmp(type,"hamming") == 0){		
		printf("hamming\n");
		flag = 1;
		//	HamMain(data,query,k,L);
	}
	else if(strcmp(type,"matrix") == 0){
		printf("matrix\n");
		flag = 3;
		//MatMain(data,query,k,L);
	}
	if(flag == -1){
		printf("wrong data file\n");
		exit(1);
	}
	fclose(fp);
	//printData(data,flag);
	//point c = lloyd(data,flag,k);
	return flag;
}

int numberOfitems(char* data,int flag){
	FILE* fp;
	char c;
	int n = 0;
	int dim = 0;
	char XXX[SIZEofBUFF];
	char binary[SIZE];
	char line [SIZE];
	fp = fopen(data,"r");
	if(fp == NULL){
		perror("print data:");
		exit(4);
	}
	if(flag == 1){//hamming
		n = -1;
		while( (c = fgetc( fp )) != EOF )
			if( c == '\n' ) n++;
		rewind(fp);
		fscanf(fp, "%s %s", XXX, XXX);
		while ( fgets ( line, sizeof line, fp ) != NULL ) { /* read a line */
			fscanf(fp, "%s %s", XXX, binary);    
		}
	}
	else if(flag == 2){//euclidean
		/*while(c != '\n'){
			if(c == '\t' || c == ' ')
				dim++;//diastasi
			c = getc(fp);
		}
		rewind(fp);*/
		while( (c = fgetc( fp )) != EOF ){
			if( c == '\n' ) 
				n++;//ypologizoume to n
			}
		rewind(fp);
		n = n-2;
	}
	else if(flag == 3){//matrix
		while( (c = fgetc( fp )) != EOF ){
			if( c == '\n' ) 
				n++;//ypologizoume to n			
		}
		rewind(fp);
		n = n-2;
		n = 0;
		fscanf(fp, "%s %s",XXX,XXX);
		fscanf(fp,"%s",XXX);
		while( (c = fgetc( fp )) != '\n' ){
			if( c == ',') 
				n++;//ypologizoume to n		
		}
		rewind(fp);
		n = n+1;
	}
	return n;
}

