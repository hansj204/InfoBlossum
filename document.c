#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <direct.h>
#include "category.h"
#include "document.h"
#include <io.h>
#include <conio.h>
#include <stdlib.h> 
#include <string.h>
#include <malloc.h>

extern void getCtList();
extern char* findCtData(int num, char strFolderPath[]);

void DocProcess(int selectDoc, char folderPath[]) {

	switch (selectDoc) {
	case 1: insertDoc(folderPath); break;
	//case 2: updateDoc(folderPath); break;
	//case 3: deleteDoc(folderPath); break;
	default:            break;
	}

}

typedef struct {
	char title[50];
	char content[1000];
}Doc;


void insertDoc(char *folderPath) {

	FILE* fp;
	int ctNum;
	Doc doc;

	getCtList(folderPath);
	printf("\n문서 제목을 입력해주세요 : ");
	scanf_s("%s", doc.title, sizeof(doc.title));
	printf("문서 내용을 입력해주세요 : \n");
	scanf_s("%s", doc.content, sizeof(doc.content));
	printf("문서 상위 카테고리 번호를 입력해주세요 : ");
	scanf_s("%d", &ctNum);

	char* newDoc = malloc(sizeof(char) * 100);

	strcpy(newDoc, folderPath);
	strcat(newDoc, "\\");
	strcat(newDoc, findCtData(ctNum, folderPath));
	strcat(newDoc, "\\");
	strcat(newDoc, doc.title);
	strcat(newDoc, ".txt");
	printf("%s", newDoc);

	
	printf("%s", newDoc);

	fp = fopen(newDoc, "w");

	if (fp == NULL) {
		perror("파일 열기 실패");//에러 출력
		return 0;//프로그램 종료
	}

	fprintf(fp, "%s\n", doc.content);

	free(newDoc);
	fclose(fp);

}
