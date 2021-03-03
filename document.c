#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include <io.h>
#include <conio.h>
#include <malloc.h>
#include <direct.h>
#include <time.h>
#include "category.h"
#include "document.h"

extern void getCtList(void);
extern char* findCtData(int num, char strFolderPath[]);

typedef struct {
	char title[50];
	char content[1000];
}Doc;

typedef struct _finddata_t fileDate;
void getCtList(char strFolderPath[]);

void DocProcess(int selectDocNum, char projectPath[], char folderPath[]) {
	
	switch (selectDocNum) {
	case 1: insertDoc(folderPath); break;
	case 2: updateDoc(projectPath, folderPath); break;
	case 3: deleteDoc(projectPath, folderPath); break;
	case 4: selectDoc(-1, folderPath); break;
	}
}

void selectDoc(int docNum, char folderPath[]) {
	FILE *fp;
	char *line = (char*)calloc(200, sizeof(char));
	int selectDocNum = 0;

	if (docNum == -1) {
		printf("��ȸ�� ���ϴ� ������ ��ȣ�� �Է��Ͽ� �ּ��� : ");
		scanf_s("%d", &docNum);
		selectDocNum = -1;
	}

	char* selectDocPath = (char*)calloc(60, sizeof(char));
	strcpy(selectDocPath, folderPath);
	strcat(selectDocPath, "\\");
	strcat(selectDocPath, findDocData(docNum, folderPath));

	fp = fopen(selectDocPath, "r");

	if (fp == NULL) {
		perror("���� ���⸦ �����Ͽ����ϴ�.\n");
		exit(1);
	}
	printf("----------------------------------------------------------------------\n");

	printf("���� ���� : %s\n", findDocData(docNum, folderPath));
	printf("���� ���� : ");
	
	while (!feof(fp)) {
		fscanf_s(fp, "%s", line, sizeof(line));
		printf("%s\n", line);
	}

	char* copyFolderPath = folderPath;
	copyFolderPath = strrchr(copyFolderPath, '\\');
	copyFolderPath = strtok(copyFolderPath, "\\");

	printf("���� ���� ī�װ� : %s\n", copyFolderPath);

	printf("----------------------------------------------------------------------\n");

	if (selectDocNum == -1) {
		printf("��ȸ ���Ḧ ���ϸ� 'exit'�� ��������.");
		char key[5];
		scanf_s("%s", key, 4);
		if (strcmp(key, "exit")) {
			system("cls");
		}
	}

	fclose(fp);
}

void insertDoc(char* folderPath) {

	FILE* fp;
	Doc doc;
	time_t t = time(NULL);
	struct tm tm = *localtime(&t);

	printf("\n���� ������ �Է����ּ��� : ");
	while (getchar() != '\n');
	gets_s(doc.title, sizeof(doc.title));
	printf("���� ������ �Է����ּ��� : ");
	gets_s(doc.content, sizeof(doc.content));

	char* newDoc = malloc(sizeof(char) * 100);

	char* year = (char*)malloc(sizeof(int));
	sprintf(year, "%d", tm.tm_year + 1900);
	char* month = (char*)malloc(sizeof(int));
	sprintf(month, "%d", tm.tm_mon + 1);
	char* day = (char*)malloc(sizeof(int));
	sprintf(day, "%d", tm.tm_mday);

	strcpy(newDoc, folderPath);
	strcat(newDoc, "\\");
	strcat(newDoc, year);
	strcat(newDoc, month);
	strcat(newDoc, day);
	strcat(newDoc, "_");
	//writeLog(1, newDoc, doc.title);
	strcat(newDoc, doc.title);
	strcat(newDoc, ".txt");

	fp = fopen(newDoc, "w");

	if (fp == NULL) {
		perror("���� ���� ����");
		return 0;
	}

	fprintf(fp, "%s\n", doc.content);

	free(newDoc);
	fclose(fp);
	system("cls");
}

void updateDoc(char projectPath[], char* folderPath) {
	Doc doc;
	time_t t = time(NULL);
	struct tm tm = *localtime(&t);
	int docNum, ctNum;
	FILE* fp;

	printf("������ ������ ��ȣ�� �Է����ּ��� : ");
	scanf_s("%d", &docNum);
	selectDoc(docNum, folderPath);

	printf("\n������ ���� ������ �Է����ּ���(�ش� �׸� ������ ������ ������ 0�� �Է��ϼ���) : ");
	while (getchar() != '\n');
	gets_s(doc.title, sizeof(doc.title));
	printf("������ ���� ������ �Է����ּ���(�ش� �׸� ������ ������ ������ 0�� �Է��ϼ���) : ");
	gets_s(doc.content, sizeof(doc.content));
	getCtList(projectPath);
	printf("���� ���� ī�װ� ��ȣ�� �Է����ּ���(�ش� �׸� ������ ������ ������ 0�� �Է��ϼ���) : ");
	scanf_s("%d", &ctNum);

	char *updateDocPath = (char*)calloc(60, sizeof(char));
	
	if (ctNum != 0) {
		strcpy(updateDocPath, projectPath);
		strcat(updateDocPath, "\\");
		strcat(updateDocPath, findCtData(ctNum, projectPath));
	}else {
		strcpy(updateDocPath, folderPath);
	}

	strcat(updateDocPath, "\\");
	
	if (strcmp(doc.title, "0")) strcat(updateDocPath, doc.title);
	else						 strcat(updateDocPath, findDocData(docNum, folderPath));
	
	printf("%s", updateDocPath);

	if (!strcmp(doc.content, "0")) {
		FILE* src = fopen(folderPath, "r");
		FILE* dest = fopen(updateDocPath, "w");
		if (src == NULL || dest == NULL) printf("���� ���� �߿� ������ �߻��Ͽ����ϴ�.");
		int count;
		char *buffer = (char)calloc(50, sizeof(char));

		while (feof(src) == 0){
			count = fread(buffer, sizeof(char), 4, src);
			fwrite(buffer, sizeof(char), count, dest);
			memset(buffer, 0, 5);
		}

		fclose(dest);
		fclose(src);
	}else {
		fp = fopen(updateDocPath, "w");
		if(fp == NULL) printf("���� ���� �߿� ������ �߻��Ͽ����ϴ�.");
		fprintf(fp, "%s", doc.content);
		fclose(fp);
	}


	

	char* updateDocLog = malloc(sizeof(char) * 100);
	char* year = (char*)malloc(sizeof(int));
	sprintf(year, "%d", tm.tm_year + 1900);
	char* month = (char*)malloc(sizeof(int));
	sprintf(month, "%d", tm.tm_mon + 1);
	char* day = (char*)malloc(sizeof(int));
	sprintf(day, "%d", tm.tm_mday);

	strcpy(updateDocLog, folderPath);
	strcat(updateDocLog, "\\");
	strcat(updateDocLog, year);
	strcat(updateDocLog, month);
	strcat(updateDocLog, day);
	strcat(updateDocLog, "_");
	writeLog(2, updateDocLog, strtok(findDocData(docNum, folderPath), ".txt"));

	system("cls");
	printf("������ �����Ͽ����ϴ�.");
}

void deleteDoc(char projectPath[], char* folderPath) {
	Doc doc;
	time_t t = time(NULL);
	struct tm tm = *localtime(&t);
	int DocNum;

	printf("\n������ ���� ��ȣ�� �Է��ϼ��� : ");
	scanf_s("%d", &DocNum);

	char* deleteDoc = (char*)calloc(60, sizeof(char));
	char* deleteDocData = findDocData(DocNum, folderPath);
	char* deleteDocLog = malloc(sizeof(char) * 100);
	char* year = (char*)malloc(sizeof(int));
	sprintf(year, "%d", tm.tm_year + 1900);
	char* month = (char*)malloc(sizeof(int));
	sprintf(month, "%d", tm.tm_mon + 1);
	char* day = (char*)malloc(sizeof(int));
	sprintf(day, "%d", tm.tm_mday);

	strcpy(deleteDocLog, folderPath);
	strcat(deleteDocLog, "\\");
	strcat(deleteDocLog, year);
	strcat(deleteDocLog, month);
	strcat(deleteDocLog, day);
	strcat(deleteDocLog, "_");
	writeLog(3, deleteDocLog, strtok(deleteDocData, ".txt"));

	strcpy(deleteDoc, folderPath);
	strcat(deleteDoc, "\\");
	strcat(deleteDoc, findDocData(DocNum, folderPath));

	int nResult = remove(deleteDoc);

	system("cls");

	if (nResult == 0) {
		system("cls");
		printf("���� ������ �����Ͽ����ϴ�.\n");
		
	}
	else if (nResult == -1) {
		printf("���� ������ �����Ͽ����ϴ�.\n");
	}

	//free(deleteDocLog);
	//free(deleteDocData); 
	//free(deleteDoc);

}

void writeLog(int logNum, char* folderPath, char* folderNm) {

	FILE* fp;
	time_t t = time(NULL);
	struct tm tm = *localtime(&t);
	char* logContent = malloc(sizeof(char) * 100);
	char* logFile = malloc(sizeof(char) * 100);

	strcpy(logFile, folderPath);
	strcat(logFile, "Log.log");

	fp = fopen(logFile, "a");

	if (fp == NULL) {
		perror("���� ���� ����");
		return 0;
	}

	strcpy(logContent, folderNm);

	switch (logNum) {
	case 1: strcat(logContent, " ���� ����"); break;
	case 2: strcat(logContent, " ���� ����"); break;
	case 3: strcat(logContent, " ���� ����"); break;
	}

	fprintf(fp, "[%d-%d-%d %d:%d:%d] %s\n", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec, logContent);

	free(logFile);
	free(logContent);
	fclose(fp);
}

void getDocList(char strFolderPath[]) {
	fileDate file_search;
	long handle;
	int result = 1;
	int i = 0;

	char projectPath[100];

	strcpy(projectPath, strFolderPath, sizeof(projectPath));
	strcat(projectPath, "\\*.txt", sizeof(strFolderPath));

	handle = _findfirst(projectPath, &file_search);

	if (handle == -1) {
		printf("\n--���� ���-------------------------------------------------------\n");
		printf("�ش� ī�װ��� ������ �����ϴ�.\n");
		printf("----------------------------------------------------------------------\n\n");
		return;
	}
	int count = 0;

	printf("\n--���� ���-------------------------------------------------------\n");
	while (result != -1) {
		printf("%d. %s\n", ++count, file_search.name);
		result = _findnext(handle, &file_search);
		i++;
	}
	printf("----------------------------------------------------------------------\n\n");

	_findclose(handle);
}

char* findDocData(int selectDoc, char strFolderPath[]) {
	fileDate file_search;
	
	long handle;
	int result = 1;
	int i = 0;

	char *projectPath = (char*)calloc(80, sizeof(char));
	strcpy(projectPath, strFolderPath, sizeof(projectPath));
	strcat(projectPath, "\\*.txt", sizeof(strFolderPath));

	char *searchLogFile = (char *)calloc(50, sizeof(char));
	handle = _findfirst(projectPath, &file_search);
	if (handle == -1) {
		printf("������ ã�� ���߿� ������ �߻��Ͽ����ϴ�.\n");
		return;
	}
	int count = 0;

	while (result != -1) {
		if (selectDoc == i + 1) {
			strcpy(searchLogFile, file_search.name);
			break;
		}
		result = _findnext(handle, &file_search);
		i++;
	}

	_findclose(handle);
	return searchLogFile;
}