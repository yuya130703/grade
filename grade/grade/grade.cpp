#include <iostream>
#include "Setting.h"
#include "Student.h"
#include "File.h"
#include <string.h>
#include <stdio.h>

void CSV2Array(const char* fileName, Student students[DATASIZE]);
void Array2CSV(const char* fileName, Student students[DATASIZE], int size);


int main()
{
	const char* fileName = "gradeData.csv"; //csvファイルのディレクトリ
	Student students[150]; //生徒の構造体のリスト

	CSV2Array(fileName, students); //csvファイルを生徒の配列に変換

	while (1) {
		int inputMode; //入力されたモード
		while (1) { //正しいモード番号が選択されるまでループ
			printf("モードを選択してください。\n1:データの追加 2:計算結果の表示 3:終了\n");

			scanf_s("%d", &inputMode); //コンソールから入力を受け取る

			if (1 <= inputMode && inputMode <= 3) { //正しいモード番号ならループを抜ける
				break;
			}
			else {
				printf("1から3の値を入力してください。");
			}
		}

		//各種モードが始まる前に配列とcsvファイルを更新
		avgGPA = average(students, size);
		maxGPA = maximum(students, size).gpa;
		rank(students, size);
		DS(students, size);

		Array2CSV(fileName, students, size);


		if (inputMode == 1) { //追加モード
			int inputID; //入力された学籍番号
			while (1) { //正しい学籍番号が入力されるまでループ
				printf("追加する学籍番号を入力してください。\n");

				scanf_s("%d", &inputID);

				int i;
				bool usedFlag = false; //学籍番号が使用済みか否か
				for (i = 0; i < size; i++) {
					if (students[i].id == inputID) {
						usedFlag = true; //使用済みならtrue
					}
				}

				if (usedFlag == true) {
					printf("この学籍番号は使用されています。\n");
				}
				else {
					break; //使用されていないならループを抜ける
				}
			}

			double inputGPA;
			while (1) { //正しい範囲のGPAが入力されるまでループ
				printf("GPAを入力してください。\n");
				scanf_s("%lf", &inputGPA);

				if (0.0 <= inputGPA && inputGPA <= 4.0) {
					break; //正しい範囲なら抜ける
				}
				else {
					printf("0から4の値を入力してください。\n");
				}
			}

			//IDとGPAを追加
			students[size].id = inputID;
			students[size].gpa = inputGPA;
			size++; //配列のサイズも更新しておく
			Array2CSV(fileName, students, size); //csvファイルを上書き
			printf("学籍番号:%d GPA:%fを追加しました。\n\n", inputID, inputGPA);

		}


		if (inputMode == 2) { //表示モード

			printf("平均GPA : %f\n", avgGPA);
			printf("最高GPA : %f\n", maxGPA);

			printf("番号\tGPA\t\t順位\t偏差値\n");
			int i;
			for (i = 0; i < size; i++) {
				printf("%d\t%f\t%d\t%f\n", students[i].id, students[i].gpa, students[i].rank, students[i].DS);
			}
			printf("\n");
		}


		if (inputMode == 3) {
			break;
		}
	}
}


//csvファイルを生徒の配列に格納する関数
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

			if (cntLINE > 3) { //3行目まではスキップ　平均・最大GPAと見出しが書き込まれているから
				while (p1 != NULL) { //1列ずつ読み込む

					if (cntROW == 0) { //ID
						students[cntLINE - 4].id = atoi(p1); //4行目から読み込んだから-4する
					}

					if (cntROW == 1) { //GPA
						students[cntLINE - 4].gpa = atof(p1);
					}

					if (cntROW == 2) { //順位
						students[cntLINE - 4].rank = atoi(p1);
					}

					p1 = strtok_s(NULL, delim, &ctx);
					cntROW += 1; //列カウント
				}
			}
			cntROW = 0; //リセット
			cntLINE += 1; //行カウント
		}
		fclose(fp); //ファイルクローズ
	}
	size = cntLINE - 4; //4行目から読み込んだから-4する
}


//生徒の配列をcsvファイルに上書き保存する関数
void Array2CSV(const char* fileName, Student students[DATASIZE], int size) {
	FILE* fp; //ファイルポインタの宣言
	errno_t error;

	error = fopen_s(&fp, fileName, "w"); //whiteモードで開く
	if (error != 0) {
		fprintf_s(stderr, "failed to open");
	}
	else { //それぞれカンマ区切りで書き込んでいく
		fprintf(fp, "平均GPA,%f\n最高GPA,%f\n\n", avgGPA, maxGPA);
		fprintf(fp, "学籍番号,GPA,順位,偏差値\n");
		int i;
		for (i = 0; i < size; i++) {
			fprintf(fp, "%d,%f,%d,%f\n", students[i].id, students[i].gpa, students[i].rank, students[i].DS);

		}
	}
	fclose(fp);
}
