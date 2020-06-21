#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <direct.h>
#include "category.h"
#include "document.h"
#include <io.h>
#include <conio.h>
#include <stdlib.h> 
#include <string.h>

extern void DocProcess(char projectPath[]);
typedef struct _finddata_t fileDate;

void CategoryProcess(int selectCt, char projectPath[]) {

	switch (selectCt) {
	case 1: insertCt(projectPath); break;
	case 2: updateCt(projectPath); break;
	case 3: deleteCt(projectPath); break;
	case 4: goDoc(projectPath);	   break;
	default:            break;
	}

}

void getCtList(char *strFolderPath) {
	fileDate file_search;
	long handle;
	int result = 1;
	int i = 0;

	char *projectPath = (char*)malloc(sizeof(strFolderPath));
	projectPath = " ";

	strncpy(projectPath, strFolderPath, sizeof(projectPath));
	strncat(projectPath, "\\*.*", sizeof(projectPath));

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
	free(projectPath);
}

char *findCtData(int num, char strFolderPath[]) {
	fileDate file_search;
	long handle;
	int result = 1;
	int i = 0;

	char* copyPath = (char*)malloc(sizeof(strFolderPath));

	strncat(copyPath, "\\*.*", strlen(copyPath));
	handle = _findfirst(copyPath, &file_search);

	char *nameList = (char*)malloc(sizeof(fileDate));
	
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
}


void insertCt(char strFolderPath[]) {

	char newCategory[20] = {" "};
	char middle[100] = { "\\" };

	printf("�߰��� ī�װ��� �̸��� �Է��ϼ��� : ");
	scanf_s("%s", newCategory, 19);

	strncat(middle, newCategory, 88);
	strncat(strFolderPath, middle, sizeof(middle));

	int makeCt = _mkdir(strFolderPath);

	if (makeCt == 0) {
		printf("ī�װ� ������ �����Ͽ����ϴ�.");
		system("cls");
		getCtList(strFolderPath);
	}
	else {
		printf("ī�װ� ������ �����Ͽ����ϴ�.");
	}
}

void updateCt(char strFolderPath[]) {

	char strOldFolder[200] = " ";
	char chaneCategory[] = { " " };
	int chageCt;

	printf("%s", strFolderPath);
	getCtList(strFolderPath);

	printf("������ ī�װ��� ��ȣ�� �Է��ϼ��� : ");
	scanf_s("%d", &chageCt);

	printf("������ ī�װ��� �̸��� �Է��ϼ��� : ");
	scanf_s("%s", chaneCategory, 30);

	strcpy(strOldFolder, strFolderPath);
	strncat(strOldFolder, "\\", sizeof(strFolderPath) + 2);
	strncat(strOldFolder, findCtData(chageCt, strFolderPath), sizeof(strFolderPath) + 2 + sizeof(findCtData(chageCt, strFolderPath)));

	strncat(strFolderPath, "\\", sizeof(strFolderPath) + 2);
	strncat(strFolderPath, chaneCategory, sizeof(strFolderPath) + sizeof(chaneCategory));

	printf("%s\n", strOldFolder);
	printf("%s\n", strFolderPath);

	//ī�װ� �̸� ����(rename)
	int result = rename(strOldFolder, strFolderPath);

	if (result == 0) {
		printf("ī�װ� ������ �����Ͽ����ϴ�.");
		system("cls");
		getCtList(strFolderPath);
	}
	else if (result == -1) {
		printf("ī�װ� ������ �����Ͽ����ϴ�.");
	}

}

void deleteCt(char strFolderPath[]) {

	int deleteCtCt;

	getCtList(strFolderPath);

	printf("������ ī�װ��� ��ȣ�� �Է��ϼ��� : ");
	scanf_s("%d", &deleteCtCt);

	//strFolderPath = (char*)realloc(strFolderPath, 2 * sizeof(deleteCtCt));

	strncat(strFolderPath, "\\", sizeof(strFolderPath) + 10);
	strncat(strFolderPath, findCtData(deleteCtCt, strFolderPath), sizeof(strFolderPath) + 20);

	//ī�װ� ����(rmdir)
	printf("%s\n", strFolderPath);
	int nResult = _rmdir(strFolderPath);

	if (nResult == 0) {
		printf("���� ���� ����");
	}
	else if (nResult == -1){
		printf("���� �ȿ� ������ ���� �� �ֽ��ϴ�. ���� �����Ͻðڽ��ϱ�?\n");
	}
}

void goDoc(char *strFolderPath) {
	int goDoc;
	printf("���� �۾��� ���ϸ� 0, ���� �α� ��ȸ�� ���ϸ� 1�� �Է����ּ���.\n");
	scanf_s("%d", &goDoc);
	if (goDoc == 0) { DocProcess(strFolderPath); }
}