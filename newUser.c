#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>     // ���� ó�� �Լ��� ����� ��� ����
#include <io.h>	
#include <string.h> 
#include <direct.h>
#include <stdlib.h>

typedef struct {
	char *key;
	char *TopPath;
}User;

void newUserInfo() {
	char *fileName[] = { "userInfo.json" };	
	char *FirstCt = (char*)calloc(21, sizeof(char));
	FILE* fp;
	User newUser;
	newUser.key = (char*)calloc(15, sizeof(char));
	newUser.TopPath = (char*)calloc(65, sizeof(char));

	printf("Ű�� �Է��Ͽ� �ּ���.\nKEY : ");
	scanf_s("%s", newUser.key, 14);
	printf("�ֻ��� ���� ��� �Է��Ͽ� �ּ��� : ");
	scanf_s("%s", newUser.TopPath, 49);
	printf("���� ī�װ��� �Է��Ͽ� �ּ��� : ");
	scanf_s("%s", FirstCt, 20);
	
/*	int result = _access(newUser.TopPath, 00);


	if(result != -1) {
		printf("�ش� ��ο� ���� �̸��� �ֻ��� ������ �ֽ��ϴ�.\n�̹� �ִ� ������ �����ϴ� �ű� ����ڶ�� ok��, �ƴϸ� �ٽ� �Է����ּ���.");
		scanf_s("%s", FirstCt, 20);
		if (!strcmp(FirstCt, "ok")) {
			char* mkCt = (char*)calloc(65, sizeof(char));
			strcat(mkCt, "\\");
			strcat(mkCt, FirstCt);
			int makeCt = _mkdir(mkCt);
		}
	} */

	int mkFolder = _mkdir(newUser.TopPath);

	if (mkFolder == 0) {
		char* mkCt = (char*)calloc(65, sizeof(char));
		strcpy(mkCt, newUser.TopPath);
		strcat(mkCt, "\\");
		strcat(mkCt, FirstCt);
		int makeCt = _mkdir(mkCt);
	}

	fp = fopen("userInfo.json", "a");
	if (fp != NULL) fprintf(fp,"%s %s\n", newUser.key, newUser.TopPath);
	fclose(fp);

	////����� ���� ���� ����
	printf("\n\n������ ����Ǿ����ϴ�.\n\n");	
}