#include<stdio.h>
#include<conio.h>
#include<stdlib.h>

struct patientData{
	int no; 
	char name[50];
	char dinfo[50];
	int age;
	
};
typedef struct patientData patient;

void create(){
	
	FILE *fp;
	int i;
	

	fp=fopen("patients.txt", "w");
	
	patient p = {0, "", "", 0};


     for (i=0;i<100;i++){
        fwrite (&p, sizeof (patient), 1, fp);
    } 
	fclose(fp);
	printf("\n\n");
	
	
}

void display(){
	patient p;
	FILE *fp;
	printf("\n%-6s%-16s%-11s%10s\n", "No", "Name", "Desease Info", "Age");
	fp=fopen("patients.txt", "r");
	while(fread(&p, sizeof(patient), 1, fp)){
		printf("\n%-5d%-20s%-20s%-5d", p.no, p.name, p.dinfo, p.age);
	}
	printf("\n\n");
}


void append(){
	patient *p;
	FILE *fp;
	int n, i;
	
	printf("Enter number of patients: ");
	scanf("%d", &n);
	
	p = (patient*)calloc(n, sizeof(patient));
	fp=fopen("patients.txt", "a");
	
	for(i=0; i<n; i++){
		printf("\nType enter after each record\n");
		printf("%s", "Enter Patient: No, Name, Desease-info, Age\n?");
		
		scanf("%d%14s%9s%d", &p[i].no, &p[i].name, &p[i].dinfo, &p[i].age);
		
		fwrite(&p[i], sizeof(patient), 1, fp);
		
	}
	fclose(fp);
	printf("\n\n");
}

void search(){
	patient p;
	FILE *fp;
	int pNo;
	int found =0;
	
	fp=fopen("patients.txt", "r");
	printf("Enter Patient Number to search: ");
	scanf("%d", &pNo);
	while(fread(&p, sizeof(patient), 1, fp)){
		if(p.no==pNo){
			found=1;
			printf("\n%-6s%-16s%-11s%10s\n", "No", "Name", "Desease Info", "Age");
			printf("%-5d%-20s%-20s%-5d", p.no, p.name, p.dinfo, p.age);
		}
	}
	if(!found){
		printf("\nRecord Not Found\n");
	}
	printf("\n\n");
}


void update(){
	patient p;
	FILE *fp, *writeData;
	int pNo;
	int found =0;

	
	fp=fopen("patients.txt", "r");
	
	writeData=fopen("temp.txt", "w");
	
	printf("Enter Patient Number to update: ");
	scanf("%d", &pNo);
	while(fread(&p, sizeof(patient), 1, fp)){
		if(p.no==pNo){
			found=1;
			
			printf("\nType enter after each record\n");
			printf("%s", "Enter Patient New: Name, Desease-info, Age\n?");
			
			scanf("%14s%9s%d", &p.name, &p.dinfo, &p.age);
			
		}
		fwrite(&p, sizeof(patient), 1, writeData);
	}
	fclose(fp);
	fclose(writeData);
	if(found){
		writeData=fopen("temp.txt", "r");
		fp=fopen("patients.txt", "w");
		
		while(fread(&p, sizeof(patient), 1, writeData)){
			fwrite(&p, sizeof(patient), 1, fp);
		}
		
		fclose(fp);
		fclose(writeData);
	}
	else{
		printf("\nRecord Not Found\n");
	}
	printf("\n\n");
}


void deletePatient(){
	patient p;
	FILE *fp, *writeData;
	int pNo;
	int found =0;
	
	
	fp=fopen("patients.txt", "r");
	
	writeData=fopen("temp.txt", "w");
	
	printf("Enter Patient Number to delete: ");
	scanf("%d", &pNo);
	while(fread(&p, sizeof(patient), 1, fp)){
		if(p.no==pNo){	
			found=1;		
		}
		else
			fwrite(&p, sizeof(patient), 1, writeData);
	}
	fclose(fp);
	fclose(writeData);
	if(found){
		writeData=fopen("temp.txt", "r");
		fp=fopen("patients.txt", "w");
		
		while(fread(&p, sizeof(patient), 1, writeData)){
			fwrite(&p, sizeof(patient), 1, fp);
		}
		
		fclose(fp);
		fclose(writeData);
	}
	else{
		printf("\nRecord Not Found\n");
	}
	printf("\n\n");
}

int main(){
	
	int choice;
	
	do{
		printf("\n==============PATIENT CRUD SYSTEM USING FILEs and STRUCT====================\n");
		printf("\n\n***************Main Menu****************\n");
		printf("\n Choose one option from the following list  ......\n");
		printf("\n1.CREATE A PATIENT FILE WITH 100 EMPTY RECORD");
		printf("\n2.INSERT A NEW PATIENT RECORD");
		printf("\n3.FIND AND RETRIEVE PATIENT INFORMATION");
		printf("\n4.DELETE A PATIENT RECORD");
		printf("\n5.MODIFY A PATIENT RECORD");
		printf("\n6.DISPLAY ALL PATIENTS");
		printf("\n0.EXIT");
		
		printf("\nEnter your choice: ");
		scanf("%d", &choice);
		
		switch(choice){
			case 1: 
				create();
			break;
			case 2: 
				append();
			break;
			case 3: 
				search();
			break;
			case 4: 
				deletePatient();
			break;
			case 5: 
				update();
			break;
			case 6: 
				display();
			break;
			
			case 0:
				exit(0);
		}
	}while(1);
	
	
	return 0;
}
