#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>     // ���� ó�� �Լ��� ����� ��� ����
#include <io.h>	
#include <string.h> 
#include <direct.h>

void newUserInfo() {

	// JSON ������ ������ ������
	char fileName[] = { "userInfo.json" };
	char key[15] = {""};
	char TopPath[200] = { "C:\\InfoBlossum" };
	char FirstCt[] = {""};

	printf("Ű�� �Է��Ͽ� �ּ���.\nKEY : ");
	scanf_s("%s", key, 14);
	/*printf("�ֻ��� ���� ��� �Է� : ");
	scanf_s("%s", TopPath);*/
	//printf("���� ī�װ��� �Է��Ͽ� �ּ���.");
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
		//����� ���� ���� ����
		printf("\n\n������ ����Ǿ����ϴ�.\n\n");	
}