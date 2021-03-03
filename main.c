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

	printf("안녕하세요. 문서 관리 시스템 'InfoBlossum'입니다.\n신규 사용자라면 1을, 아니면 0을 입력해주세요.\n>");
	scanf_s("%d", &newUser);

	if (newUser == 1) {newUserInfo();}

	printf("보안키를 입력해주세요 : ");
	scanf_s("%s", securityKey, 15);

	if ((fp = fopen("userInfo.json", "r")) == NULL) {
		printf("사용자 인증 과정에서 오류가 발생하였습니다.");
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
			printf("사용자 인증 과정에서 오류가 발생하였습니다.");
			newUserInfo();
		}
		printf("해당 보안키는 존재하지 않습니다. 다시 보안키를 입력해주세요 : ");
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

	printf("\n인증된 회원입니다.\n\n");
	

	while (true){
		selectCt = 0, selectDoc = 0;
		system("cls");
		
		while (CategoryProcess(selectCt, strFolderPath) == 0) {

			getCtList(strFolderPath);

			printf("--카테고리 작업 목록-----------------------------------------------------------------------\n");
			printf("1. 카테고리 생성\t2. 카테고리 수정\t3. 카테고리 삭제\t4. 문서 or 문서 로그 조회\n(프로그램 종료를 원한다면 -1을 입력하세요)\n");
			printf("-------------------------------------------------------------------------------------------\n");
			printf("카테고리 작업을 선택해주세요(번호 입력) : ");
			scanf_s("%d", &selectCt);
			if (selectCt == -1) exit(1);
		}

		system("cls");

		getCtList(strFolderPath);

		printf("문서나 문서 로그를 조회할 카테고리 번호를 입력해주세요 : ");
		scanf_s("%d", &selectCt);

		char copyPath[sizeof(strFolderPath)];
		strcpy(copyPath, strFolderPath);
		strcat(copyPath, "\\");
		strcat(copyPath, findCtData(selectCt, strFolderPath));

		system("cls");

		while (selectDoc != 5) {
			
			getDocList(copyPath);

			printf("\n--문서 작업 목록---------------------------------------------------------------------------\n");
			printf("1. 문서 생성\t2. 문서 수정\t3. 문서 삭제\t4. 문서 조회\t5. 카테고리 작업\n(프로그램 종료를 원한다면 -1을 입력하세요)\n");
			printf("-------------------------------------------------------------------------------------------- \n");
			printf("문서 작업을 선택해주세요(번호 입력) : ");
			scanf_s("%d", &selectDoc);
			if (selectDoc == -1) exit(1);

			DocProcess(selectDoc, strFolderPath, copyPath);
		}

	}

	return 0;
}
