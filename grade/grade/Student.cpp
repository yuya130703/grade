#define BUFFLENGTH 128
#include <iostream>
#include <string.h>
#include <math.h>
#include "Setting.h"
#include "Student.h"


//���k�̃��X�g���󂯎��AGPA�̕��ς�Ԃ��֐�
double average(Student students[], int size) {
    double average = 0;
    int i;
    for (i = 0; i < size; i++) {
        average += students[i].gpa;
    }
    average /= size;

    return average;
}


//���k�̃��X�g���󂯎��A�ł�GPA�̍������k��Ԃ��֐�
Student maximum(Student students[], int size) {
    double max = 0;
    int n = 0;
    int i;
    for (i = 0; i < size; i++) {
        if (max < students[i].gpa) { //���GPA�̍������k������΍X�V
            max = students[i].gpa;
            n = i;
        }
    }

    return students[n];
}


//���k�̃��X�g���󂯎��A�e���k�̏��ʂ��v�Z����֐�
void rank(Student students[], int size) {
    int cnt = 0; //������荂��GPA�̐�

    int i;
    int j;
    for (i = 0; i < size; i++) {
        cnt = 0;
        for (j = 0; j < size; j++) {
            if (students[i].gpa < students[j].gpa) {
                cnt++;
            }
        }
        students[i].rank = cnt + 1; //�������GPA�̍������k�̐�+1�����ʂƂȂ�@�^�C���������Ă����l
    }
}


//�΍��l���v�Z����֐�
void DS(Student students[], int size) {
    double avgGPA = average(students, size);
    double num = 0; //�v�Z�p
    
    int i;
    for (i = 0; i < size; i++) { //�e���k�̃f�[�^�ɑ΂��Čv�Z
        num += (students[i].gpa - avgGPA) * (students[i].gpa - avgGPA); //�e�f�[�^�ƕ��ς̍��̓��
    }
    num /= size; //����ŕ��U�����܂�
    num = sqrt(num); //����ŕW���΍������܂�

    //�΍��l�̌v�Z
    for (i = 0; i < size; i++) {
        students[i].DS = (students[i].gpa - avgGPA) / num * 10 + 50;
    }
}