#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>     // 파일 처리 함수가 선언된 헤더 파일
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

	printf("키를 입력하여 주세요.\nKEY : ");
	scanf_s("%s", newUser.key, 14);
	printf("최상위 폴더 경로 입력하여 주세요 : ");
	scanf_s("%s", newUser.TopPath, 49);
	printf("최초 카테고리를 입력하여 주세요 : ");
	scanf_s("%s", FirstCt, 20);
	
/*	int result = _access(newUser.TopPath, 00);


	if(result != -1) {
		printf("해당 경로에 같은 이름의 최상위 폴더가 있습니다.\n이미 있는 폴더에 접근하는 신규 사용자라면 ok를, 아니면 다시 입력해주세요.");
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

	////사용자 정보 저장 여부
	printf("\n\n정보가 저장되었습니다.\n\n");	
}