#pragma once
#include "Setting.h"

//���k��\���\����
struct Student {
    //char name[BUFFLENGTH];
    int id; //�w�Дԍ�
    double gpa; //GPA
    int rank; //����
    double DS; //�΍��l
};


static double avgGPA = 0;
static double maxGPA = 0;

double average(Student students[], int size);
Student maximum(Student students[], int size);
void rank(Student students[], int size);
void DS(Student students[], int size);