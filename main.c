#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h> 

extern void newUserInfo(void);
extern void CategoryProcess(int selectCt, char* folderPath);
extern void DocProcess(int selectDoc, char* folderPath);
extern void getCtList();

int main() {
	int newUser = 0, selectCt = 0, selectDoc;
	char securityKey[16] = {""}, * docLink = " ", * okKey = " ";
	char strFolderPath[] = { "C:\\InfoBlossum" };
	char buffer[256];
	FILE *fp = NULL;

/*	printf("�ȳ��ϼ���. ���� ���� �ý��� 'InfoBlossum'�Դϴ�.\n�ű� ����ڶ�� 1��, �ƴϸ� 0�� �Է����ּ���.\n>");
	scanf_s("%d", &newUser);

	if (newUser == 1) {newUserInfo();}

	printf("����Ű(Ȯ��Ű)�� �Է����ּ��� : ");
	scanf_s("%s", securityKey, 15);
	
	if ((fp = fopen("userInfo.json", "r")) == NULL) {
		//fprintf(stderr, "���� %s�� �� �� �����ϴ�.", );
		exit(1);
	}

	while (fgets(buffer, 256, fp)) {
		if (strstr(buffer, securityKey)) {
			printf("�ܾ� %s�� �߰ߵǾ����ϴ�.\n", securityKey);
		}
	}

	fclose(fp);

	//while(strcmp(okKey, securityKey) != 0){
	////		printf("����Ű�� �߸� �Ǿ����ϴ�. �ٽ� �Է����ּ���.\nKEY : ");
	//	printf("����Ű(Ȯ��Ű)�� �Է����ּ��� : ");
	//	scanf_s("%s", &securityKey);
	//	if ((fp = fopen("userInfo.json", "r")) == NULL) {
	//		fprintf(stderr, "���� %s�� �� �� �����ϴ�.");
	//		exit(1);
	//	}

	//system("cls");
	printf("\n������ ȸ���Դϴ�.\n\n");

	while(selectCt != 4){

		//getCtList(strFolderPath);

		printf("--ī�װ� �۾� ���------------------------------------------------------------------------\n");
		printf("1. ī�װ� ����\t2. ī�װ� ����\t3. ī�װ� ����\t4. ���� �۾�\n");
		printf("--------------------------------------------------------------------------------------------\n");
		printf("ī�װ� �۾��� �������ּ���(��ȣ �Է�) : ");
		scanf_s("%d", &selectCt);
	
		CategoryProcess(selectCt, strFolderPath);
	}
	*/
	printf("\n--���� ���-------------------------------------------------------\n");
	printf("1. ���� ����\t2. ���� ����\t3. ���� ����\n");
	printf("----------------------------------------------------------------------\n");
	printf("���� �۾��� �������ּ���(��ȣ �Է�) : ");
	scanf_s("%d", &selectDoc);

	DocProcess(selectDoc, strFolderPath);

	return 0;
}
