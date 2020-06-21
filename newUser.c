#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>     // 파일 처리 함수가 선언된 헤더 파일
#include <io.h>	
#include <string.h> 
#include <direct.h>

void newUserInfo() {

	// JSON 문서에 저장할 데이터
	char fileName[] = { "userInfo.json" };
	char key[15] = {""};
	char TopPath[200] = { "C:\\InfoBlossum" };
	char FirstCt[] = {""};

	printf("키를 입력하여 주세요.\nKEY : ");
	scanf_s("%s", key, 14);
	/*printf("최상위 폴더 경로 입력 : ");
	scanf_s("%s", TopPath);*/
	//printf("최초 카테고리를 입력하여 주세요.");
	//scanf_s("%s", FirstCt, 100);
	
	int result = _access(TopPath, 00);

	if (result == -1) {

		int mkFolder = _mkdir(TopPath);
		
		if (mkFolder == 0) {
			//strncat(TopPath, FirstCt, strlen(FirstCt));
			int makeCt = _mkdir("C:\\InfoBlossum\\first");

			if (makeCt == 0) {
				FILE* fp;
				fp = fopen("userInfo.json", "w");

				if (fp != NULL) {
					fprintf(fp, "{\n");
					fprintf(fp, "  \"%s\": \"%s\",\n", key, TopPath);
					fprintf(fp, "}\n");
					fclose(fp);
				}
			}
		}else {

			FILE* fp;
			fp = fopen(fileName, "a");

			if (fp != NULL) {
				fprintf(fp, "{\n");
				fprintf(fp, "  \"%s\": \"%s\",\n", key, TopPath);
				fprintf(fp, "}\n");
				fclose(fp);
			}

		}
	}
		//사용자 정보 저장 여부
		printf("\n\n정보가 저장되었습니다.\n\n");	
}