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

/*	printf("안녕하세요. 문서 관리 시스템 'InfoBlossum'입니다.\n신규 사용자라면 1을, 아니면 0을 입력해주세요.\n>");
	scanf_s("%d", &newUser);

	if (newUser == 1) {newUserInfo();}

	printf("보안키(확인키)를 입력해주세요 : ");
	scanf_s("%s", securityKey, 15);
	
	if ((fp = fopen("userInfo.json", "r")) == NULL) {
		//fprintf(stderr, "파일 %s를 열 수 없습니다.", );
		exit(1);
	}

	while (fgets(buffer, 256, fp)) {
		if (strstr(buffer, securityKey)) {
			printf("단어 %s이 발견되었습니다.\n", securityKey);
		}
	}

	fclose(fp);

	//while(strcmp(okKey, securityKey) != 0){
	////		printf("보안키가 잘못 되었습니다. 다시 입력해주세요.\nKEY : ");
	//	printf("보안키(확인키)를 입력해주세요 : ");
	//	scanf_s("%s", &securityKey);
	//	if ((fp = fopen("userInfo.json", "r")) == NULL) {
	//		fprintf(stderr, "파일 %s를 열 수 없습니다.");
	//		exit(1);
	//	}

	//system("cls");
	printf("\n인증된 회원입니다.\n\n");

	while(selectCt != 4){

		//getCtList(strFolderPath);

		printf("--카테고리 작업 목록------------------------------------------------------------------------\n");
		printf("1. 카테고리 생성\t2. 카테고리 수정\t3. 카테고리 삭제\t4. 문서 작업\n");
		printf("--------------------------------------------------------------------------------------------\n");
		printf("카테고리 작업을 선택해주세요(번호 입력) : ");
		scanf_s("%d", &selectCt);
	
		CategoryProcess(selectCt, strFolderPath);
	}
	*/
	printf("\n--문서 목록-------------------------------------------------------\n");
	printf("1. 문서 생성\t2. 문서 수정\t3. 문서 삭제\n");
	printf("----------------------------------------------------------------------\n");
	printf("문서 작업을 선택해주세요(번호 입력) : ");
	scanf_s("%d", &selectDoc);

	DocProcess(selectDoc, strFolderPath);

	return 0;
}
