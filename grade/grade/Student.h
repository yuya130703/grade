#pragma once
#include "Setting.h"

//生徒を表す構造体
struct Student {
    //char name[BUFFLENGTH];
    int id; //学籍番号
    double gpa; //GPA
    int rank; //順位
    double DS; //偏差値
};


static double avgGPA = 0;
static double maxGPA = 0;

double average(Student students[], int size);
Student maximum(Student students[], int size);
void rank(Student students[], int size);
void DS(Student students[], int size);