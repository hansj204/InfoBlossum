#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h> 

extern void newUserInfo(void);
extern int CategoryProcess(int selectCt, char projectPath[]);
extern void DocProcess(int selectDoc, char projectPath[], char folderPath[]);
extern void getCtList(void);
extern void getDocList(char strFolderPath[]);

char* findCtData(int num, char strFolderPath[]);

typedef struct {
	char* key;
	char* TopPath;
}User;

int main() {
	int newUser = 0, selectCt = 0, selectDoc = 0;
	char *securityKey = (char*)calloc(15, sizeof(char));
	char *strFolderPath = (char*)calloc(80, sizeof(char));
	char buffer[256];
	FILE *fp = NULL;

	printf("�ȳ��ϼ���. ���� ���� �ý��� 'InfoBlossum'�Դϴ�.\n�ű� ����ڶ�� 1��, �ƴϸ� 0�� �Է����ּ���.\n>");
	scanf_s("%d", &newUser);

	if (newUser == 1) {newUserInfo();}

	printf("����Ű�� �Է����ּ��� : ");
	scanf_s("%s", securityKey, 15);

	if ((fp = fopen("userInfo.json", "r")) == NULL) {
		printf("����� ���� �������� ������ �߻��Ͽ����ϴ�.");
		newUserInfo();
	}

	int i = 0, ok =  1;
	User user;
	user.key = (char*)calloc(15, sizeof(char));
	user.TopPath = (char*)calloc(30, sizeof(char));

	while (!feof(fp)) {
		fscanf(fp, "%s %s", user.key, user.TopPath);
		if (strcmp(securityKey, user.key) == 0) {
			printf("%s", user.key);
			strFolderPath = user.TopPath;
			strcpy(strFolderPath ,user.TopPath);
			ok = 0;
		}
		i++;
	}
	while (ok != 0){
		fclose(fp);
		if ((fp = fopen("userInfo.json", "r")) == NULL) {
			printf("����� ���� �������� ������ �߻��Ͽ����ϴ�.");
			newUserInfo();
		}
		printf("�ش� ����Ű�� �������� �ʽ��ϴ�. �ٽ� ����Ű�� �Է����ּ��� : ");
		scanf_s("%s", securityKey, 15);
		while (!feof(fp)) {
			fscanf(fp, "%s %s", user.key, user.TopPath);
			if (strcmp(securityKey, user.key) == 0) {
				printf("%s", user.key);
				strFolderPath = user.TopPath;
				strcpy(strFolderPath, user.TopPath);
				ok = 0;
			}
			i++;
		}
	}

	fclose(fp);
	
	system("cls");

	printf("\n������ ȸ���Դϴ�.\n\n");
	

	while (true){
		selectCt = 0, selectDoc = 0;
		system("cls");
		
		while (CategoryProcess(selectCt, strFolderPath) == 0) {

			getCtList(strFolderPath);

			printf("--ī�װ� �۾� ���-----------------------------------------------------------------------\n");
			printf("1. ī�װ� ����\t2. ī�װ� ����\t3. ī�װ� ����\t4. ���� or ���� �α� ��ȸ\n(���α׷� ���Ḧ ���Ѵٸ� -1�� �Է��ϼ���)\n");
			printf("-------------------------------------------------------------------------------------------\n");
			printf("ī�װ� �۾��� �������ּ���(��ȣ �Է�) : ");
			scanf_s("%d", &selectCt);
			if (selectCt == -1) exit(1);
		}

		system("cls");

		getCtList(strFolderPath);

		printf("������ ���� �α׸� ��ȸ�� ī�װ� ��ȣ�� �Է����ּ��� : ");
		scanf_s("%d", &selectCt);

		char copyPath[sizeof(strFolderPath)];
		strcpy(copyPath, strFolderPath);
		strcat(copyPath, "\\");
		strcat(copyPath, findCtData(selectCt, strFolderPath));

		system("cls");

		while (selectDoc != 5) {
			
			getDocList(copyPath);

			printf("\n--���� �۾� ���---------------------------------------------------------------------------\n");
			printf("1. ���� ����\t2. ���� ����\t3. ���� ����\t4. ���� ��ȸ\t5. ī�װ� �۾�\n(���α׷� ���Ḧ ���Ѵٸ� -1�� �Է��ϼ���)\n");
			printf("-------------------------------------------------------------------------------------------- \n");
			printf("���� �۾��� �������ּ���(��ȣ �Է�) : ");
			scanf_s("%d", &selectDoc);
			if (selectDoc == -1) exit(1);

			DocProcess(selectDoc, strFolderPath, copyPath);
		}

	}

	return 0;
}
