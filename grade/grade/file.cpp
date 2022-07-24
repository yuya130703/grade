#include "Setting.h"
#include "Student.h"
#include "File.h"
#include <string.h>
#include <iostream>


void CSV2Array(const char* fileName, Student students[DATASIZE]) {
	char c1; //変換後の取得地
	char* p1, * p2; //char型ポインタワーク
	char delim[] = ","; //デリミタ　ここではカンマ
	char* ctx;
	int cntLINE = 0; //配列の何番目かをカウント
	int cntROW = 0; //同上

	FILE* fp; //ファイルポインタの宣言
	char s[BUFFSIZE];
	errno_t error;
	error = fopen_s(&fp, fileName, "r"); //ファイルオープン
	if (error != 0) { //開けなかった場合
		fprintf_s(stderr, "failed to open");
	}
	else {
		while (fgets(s, BUFFSIZE, fp) != NULL) { //1行ずつ読み込む
			p1 = strtok_s(s, delim, &ctx);

			if (cntLINE > 3) { //3行目はスキップ
				while (p1 != NULL) { //1列ずつ読み込む

					if (cntROW == 0) { //ID
						students[cntLINE - 4].id = atoi(p1);
						//printf("abc");
					}

					if (cntROW == 1) { //GPA
						students[cntLINE - 4].gpa = atof(p1);
					}

					if (cntROW == 2) { //順位
						students[cntLINE - 4].rank = atoi(p1);
					}

					p1 = strtok_s(NULL, delim, &ctx);
					cntROW += 1;
				}
			}
			cntROW = 0;
			cntLINE += 1;
		}
		fclose(fp); //ファイルクローズ
	}

	//printf("%d\n", cntLINE-1);
	size = cntLINE - 4;
}


void Array2CSV(const char* fileName, Student students[DATASIZE], int size) {
	FILE* fp; //ファイルポインタの宣言
	errno_t error;

	error = fopen_s(&fp, fileName, "w");
	if (error != 0) {
		fprintf_s(stderr, "failed to open");
	}
	else {
		fprintf(fp, "平均GPA,%f\n最高GPA,%f\n\n", avgGPA, maxGPA);
		fprintf(fp, "学籍番号,GPA,順位,偏差値\n");
		int i;
		for (i = 0; i < size; i++) {
			fprintf(fp, "%d,%f,%d,%f\n", students[i].id, students[i].gpa, students[i].rank, students[i].DS);

		}
	}
	fclose(fp);
}
