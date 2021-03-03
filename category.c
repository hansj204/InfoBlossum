#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include <io.h>
#include <conio.h>
#include <malloc.h>
#include <direct.h>
#include "category.h"
#include "document.h"

typedef struct _finddata_t fileDate;

extern char* findDocData(int selectDoc, char strFolderPath[]);
void getCtList(char strFolderPath[]);
char* findCtData(int num, char strFolderPath[]);

int CategoryProcess(int selectCt, char projectPath[]) {

	switch (selectCt) {
		case 1: insertCt(projectPath); break;
		case 2: updateCt(projectPath); break;
		case 3: deleteCt(projectPath); break;
		case 4: if (goDoc(projectPath) == 1) return 1; break;
		default:					   break;
	}
	return 0;
}

void insertCt(char strFolderPath[]) {

	char newCategory[20];

	printf("�߰��� ī�װ��� �̸��� �Է��ϼ��� : ");
	scanf_s("%s", newCategory, sizeof(newCategory));

	char projectPath[100];

	strcpy(projectPath, strFolderPath, sizeof(projectPath));
	strcat(projectPath, "\\", sizeof(strFolderPath));
	strcat(projectPath, newCategory, sizeof(newCategory));

	int makeCt = _mkdir(projectPath);

	if (makeCt == 0) {
		system("cls");
		printf("ī�װ� ������ �����Ͽ����ϴ�.\n");
	}
	else {
		printf("ī�װ� ������ �����Ͽ����ϴ�.");
	}
}

void updateCt(char strFolderPath[]) {

	char strOldFolder[50];
	char strNewFolder[70];
	char chaneCategory[10];
	int chageCt;

	printf("������ ī�װ��� ��ȣ�� �Է��ϼ��� : ");
	scanf_s("%d", &chageCt);

	printf("������ ī�װ��� �̸��� �Է��ϼ��� : ");
	scanf_s("%s", chaneCategory, 9);

	strcpy(strOldFolder, strFolderPath);
	strcat(strOldFolder, "\\");
	strcat(strOldFolder, findCtData(chageCt, strFolderPath));

	strcpy(strNewFolder, strFolderPath);
	strcat(strNewFolder, "\\");
	strcat(strNewFolder, chaneCategory);

	//ī�װ� �̸� ����(rename)
	int result = rename(strOldFolder, strNewFolder);

	if (result == 0) {
		system("cls");
		printf("ī�װ� ������ �����Ͽ����ϴ�.\n");
	}
	else if (result == -1) {
		printf("ī�װ� ������ �����Ͽ����ϴ�.");
	}

}

void deleteCt(char strFolderPath[]) {

	int deleteCtCt;

	printf("������ ī�װ��� ��ȣ�� �Է��ϼ��� : ");
	scanf_s("%d", &deleteCtCt);

	char projectPath[100];

	strcpy(projectPath, strFolderPath, sizeof(projectPath));
	strncat(projectPath, "\\", sizeof(strFolderPath) + 10);
	strncat(projectPath, findCtData(deleteCtCt, strFolderPath), sizeof(strFolderPath) + 20);

	//ī�װ� ����(rmdir)
	int nResult = _rmdir(projectPath);

	if (nResult == 0) {
		system("cls");
		printf("���� ������ �����Ͽ����ϴ�.\n");
	}
	else if (nResult == -1) {
		printf("���� �ȿ� ������ ���� �� �ֽ��ϴ�. ���� �����Ͻðڽ��ϱ�?\n");
	}
}

int goDoc(char* strFolderPath) {
	int goDoc;
	printf("���� �۾��� ���ϸ� 0, ���� �α� ��ȸ�� ���ϸ� 1�� �Է����ּ��� : ");
	scanf_s("%d", &goDoc);
	if (goDoc == 1) {
		getLog(strFolderPath);
		return 0;
	}
	return 1;
}

void getLog(char strFolderPath[]) {

	fileDate file_search;
	long handle;
	int result = 1, selectCt = 0, selectLog = 0;
	int i = 0, count = 0;
	FILE* fp;
	char line[100];

	printf("�α׸� ��ȸ�� ī�װ� ��ȣ�� �Է����ּ��� : ");
	scanf_s("%d", &selectCt);

	system("cls");

	char copyPath[100];
	strcpy(copyPath, strFolderPath);
	strcat(copyPath, "\\");
	strcat(copyPath, findCtData(selectCt, strFolderPath));
	strcat(copyPath, "\\*.log", strlen(copyPath));

	handle = _findfirst(copyPath, &file_search);

	if (handle == -1) {
		printf("�ش� ī�װ��� ���� �αװ� �����ϴ�.\n");
	}

	printf("--�α� ���-------------------------------------------------------\n");
	while (result != -1) {
		printf("%d. %s\n", ++count, file_search.name);
		result = _findnext(handle, &file_search);
		i++;
	}
	printf("----------------------------------------------------------------------\n\n");

	printf("��ȸ�� ���ϴ� �α� ���� ��ȣ�� �Է����ּ��� : ");
	scanf_s("%d", &selectLog);

	char logPath[100];
	strcpy(logPath, strFolderPath);
	strcat(logPath, "\\");
	strcat(logPath, findCtData(selectCt, strFolderPath));
	strcat(logPath, "\\");
	strcat(logPath, findDocLogData(selectLog, logPath));

	fp = fopen(logPath, "r");

	if (fp == NULL) {
		system("cls");
		perror("�α� ���� ���⸦ �����Ͽ����ϴ�.");
	
	}
	printf("----------------------------------------------------------------------\n");
	while (fgets(line, 100, fp) != NULL) {
		fputs(line, stdout);
	}
	printf("----------------------------------------------------------------------\n\n");
	printf("��ȸ ���Ḧ ���ϸ� 'exit'�� ��������.");
	char key[5];
	scanf_s("%s", key, 4);
	if (strcmp(key, "exit")) {
		system("cls");
	}

	fclose(fp);
	_findclose(handle);

}

char* findDocLogData(int selectDoc, char strFolderPath[]) {
	fileDate file_search;

	long handle;
	int result = 1;
	int i = 0;

	char projectPath[100];
	strcpy(projectPath, strFolderPath, sizeof(projectPath));
	strcat(projectPath, "*.log", sizeof(strFolderPath));

	char* searchLogFile = (char*)calloc(50, sizeof(char));
	handle = _findfirst(projectPath, &file_search);

	if (handle == -1) {
		printf("���� �α׸� ã�� ���߿� ������ �߻��Ͽ����ϴ�.\n");
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

void getCtList(char strFolderPath[]) {
	fileDate file_search;
	long handle;
	int result = 1;
	int i = 0;

	char projectPath[100];

	strcpy(projectPath, strFolderPath, sizeof(projectPath));
	strcat(projectPath, "\\*.*", sizeof(strFolderPath));

	handle = _findfirst(projectPath, &file_search);

	if (handle == -1) {
		printf("There were no files.\n");
		return;
	}

	printf("--ī�װ� ���-------------------------------------------------------\n");
	while (result != -1) {
		printf("%d. %s\n", i + 1, file_search.name);
		result = _findnext(handle, &file_search);
		i++;
	}
	printf("----------------------------------------------------------------------\n\n");

	_findclose(handle);
}

char* findCtData(int num, char strFolderPath[]) {
	fileDate file_search;
	long handle;
	int result = 1;
	int i = 0;

	char copyPath[100];

	strcpy(copyPath, strFolderPath, strlen(strFolderPath));
	strcat(copyPath, "\\*.*", strlen(copyPath));
	handle = _findfirst(copyPath, &file_search);

	char* nameList = (char*)malloc(sizeof(fileDate));

	if (handle == -1) {
		printf("There were no files.\n");
		return;
	}

	if (nameList != NULL) {
		while (result != -1) {
			if (i == num - 1) {
				strcpy(nameList, file_search.name);
				break;
			}
			result = _findnext(handle, &file_search);
			i++;

		}
	}

	_findclose(handle);

	return nameList;

	free(nameList);
}