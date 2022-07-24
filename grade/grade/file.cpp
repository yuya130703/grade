#include "Setting.h"
#include "Student.h"
#include "File.h"
#include <string.h>
#include <iostream>


void CSV2Array(const char* fileName, Student students[DATASIZE]) {
	char c1; //�ϊ���̎擾�n
	char* p1, * p2; //char�^�|�C���^���[�N
	char delim[] = ","; //�f���~�^�@�����ł̓J���}
	char* ctx;
	int cntLINE = 0; //�z��̉��Ԗڂ����J�E���g
	int cntROW = 0; //����

	FILE* fp; //�t�@�C���|�C���^�̐錾
	char s[BUFFSIZE];
	errno_t error;
	error = fopen_s(&fp, fileName, "r"); //�t�@�C���I�[�v��
	if (error != 0) { //�J���Ȃ������ꍇ
		fprintf_s(stderr, "failed to open");
	}
	else {
		while (fgets(s, BUFFSIZE, fp) != NULL) { //1�s���ǂݍ���
			p1 = strtok_s(s, delim, &ctx);

			if (cntLINE > 3) { //3�s�ڂ̓X�L�b�v
				while (p1 != NULL) { //1�񂸂ǂݍ���

					if (cntROW == 0) { //ID
						students[cntLINE - 4].id = atoi(p1);
						//printf("abc");
					}

					if (cntROW == 1) { //GPA
						students[cntLINE - 4].gpa = atof(p1);
					}

					if (cntROW == 2) { //����
						students[cntLINE - 4].rank = atoi(p1);
					}

					p1 = strtok_s(NULL, delim, &ctx);
					cntROW += 1;
				}
			}
			cntROW = 0;
			cntLINE += 1;
		}
		fclose(fp); //�t�@�C���N���[�Y
	}

	//printf("%d\n", cntLINE-1);
	size = cntLINE - 4;
}


void Array2CSV(const char* fileName, Student students[DATASIZE], int size) {
	FILE* fp; //�t�@�C���|�C���^�̐錾
	errno_t error;

	error = fopen_s(&fp, fileName, "w");
	if (error != 0) {
		fprintf_s(stderr, "failed to open");
	}
	else {
		fprintf(fp, "����GPA,%f\n�ō�GPA,%f\n\n", avgGPA, maxGPA);
		fprintf(fp, "�w�Дԍ�,GPA,����,�΍��l\n");
		int i;
		for (i = 0; i < size; i++) {
			fprintf(fp, "%d,%f,%d,%f\n", students[i].id, students[i].gpa, students[i].rank, students[i].DS);

		}
	}
	fclose(fp);
}
