#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void createfile();
void editfile();
void readfile();
void deletefile();
void displaymenu();

int main()
{
	int chioce;

	do {
		displaymenu();
		printf("请选择操作系统\n");
		scanf("%d", &chioce);
		while (getchar() != '\n');

		switch (chioce) {
			case 1:
				createfile();	
				break;
			case 2:
				editfile();
				break;
			case 3:
				readfile();
				break;
			case 4:
				deletefile();
				break;
			case 5:
				printf("\n再见\n");
				break;
			default:
				printf("输入无效");
				
		}

	} while (chioce != 5);



	return 0;
}


void displaymenu() {
	printf("\n=======================\n");
	printf("1----创建文本\n");
	printf("2----编辑文本\n");
	printf("3----阅读文本\n");
	printf("4----删除文本\n");
	printf("5----退出系统\n");
	printf("=======================\n");
}



void createfile() {
	char filename[100];
	char content[1024];
	FILE* fp;

	printf("\n请输入要创建的文件名 :");
	fgets(filename, sizeof(filename), stdin);
	filename[strcspn(filename, "\n")] = '\0';

	fp = fopen(filename, "r");
	if (fp != NULL) {
		fclose(fp);
		printf("\n文件已存在，是否要覆盖？");
		char response;
		scanf("%c", &response);
		while (getchar() != '\n');
		if (response != 'y' && response != 'Y') {
			return;
		}
	}

	fp = fopen(filename, "w");
	if (fp == NULL) {
		perror("\n文件创建失败");
		return;
	}

	printf("\n请输入要写入文件的内容 (输入完按两次回车): ");
	while (1) {
		fgets(content, sizeof(content), stdin);
		content[strcspn(content, "\n")] = '\0';

		if (strlen(content) == 0) {
			break;
		}

		fprintf(fp, "%s\n", content);
	}
	fclose(fp);
	printf("\n文件创建成功: %s", filename);
}


void editfile() {
	char filename[100];
	char content[1024];
	FILE* fp;

	printf("\n请输入要编辑的文件名:");
	fgets(filename, sizeof(filename), stdin);
	filename[strcspn(filename, "\n")] = '\0';

	fp = fopen(filename, "r");
	if (fp == NULL) {
		perror("\n该文件不存在");
		return;
	}

	fclose(fp);

	fp = fopen(filename, "a");
	if (fp == NULL) {
		perror("\n文件打开失败");
		return;
	}

	printf("\n请输入要追加的内容 (输入完按两次回车): ");
	while (1) {
		fgets(content, sizeof(content), stdin);
		content[strcspn(content, "\n")] = '\0';

		if (strlen(content) == 0) {
			break;
		}

		fprintf(fp, "%s\n", content);
	}

	fclose(fp);

	printf("\n内容已成功追加到文件: %s", filename);

}


void readfile() {
	char filename[100];
	char buffer[1024];
	FILE* fp;

	printf("\n请输入要读取的文件名 : ");
	fgets(filename, sizeof(filename), stdin);
	filename[strcspn(filename, "\n")] = '\0';
	fp = fopen(filename, "r");
	if (fp == NULL) {
		perror("文件打开失败");
		return;
	}

	printf("\n-——文件内容如下——-\n");
	while (fgets(buffer, sizeof(buffer), fp) != NULL) {
		printf("%s", buffer);
	}
	printf("\n——————————————\n");

	fclose(fp);
}


void deletefile() {
	char filename[100];
	FILE* fp;

	printf("\n请输入要删除的文件:");
	fgets(filename, sizeof(filename), stdin);
	filename[strcspn(filename, "\n")] = '\0';

	fp = fopen(filename, "r");
	if (fp == NULL) {
		printf("\n文件不存在");
		return;
	}
	fclose(fp);

	if (remove(filename) == 0) {
		printf("\n文件删除成功");
	}
	else {
		perror("\n删除失败");
	}
}