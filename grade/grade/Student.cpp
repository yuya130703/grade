#define BUFFLENGTH 128
#include <iostream>
#include <string.h>
#include <math.h>
#include "Setting.h"
#include "Student.h"


//生徒のリストを受け取り、GPAの平均を返す関数
double average(Student students[], int size) {
    double average = 0;
    int i;
    for (i = 0; i < size; i++) {
        average += students[i].gpa;
    }
    average /= size;

    return average;
}


//生徒のリストを受け取り、最もGPAの高い生徒を返す関数
Student maximum(Student students[], int size) {
    double max = 0;
    int n = 0;
    int i;
    for (i = 0; i < size; i++) {
        if (max < students[i].gpa) { //よりGPAの高い生徒がいれば更新
            max = students[i].gpa;
            n = i;
        }
    }

    return students[n];
}


//生徒のリストを受け取り、各生徒の順位を計算する関数
void rank(Student students[], int size) {
    int cnt = 0; //自分より高いGPAの数

    int i;
    int j;
    for (i = 0; i < size; i++) {
        cnt = 0;
        for (j = 0; j < size; j++) {
            if (students[i].gpa < students[j].gpa) {
                cnt++;
            }
        }
        students[i].rank = cnt + 1; //自分よりGPAの高い生徒の数+1が順位となる　タイが発生しても同様
    }
}


//偏差値を計算する関数
void DS(Student students[], int size) {
    double avgGPA = average(students, size);
    double num = 0; //計算用
    
    int i;
    for (i = 0; i < size; i++) { //各生徒のデータに対して計算
        num += (students[i].gpa - avgGPA) * (students[i].gpa - avgGPA); //各データと平均の差の二乗
    }
    num /= size; //これで分散が求まる
    num = sqrt(num); //これで標準偏差が求まる

    //偏差値の計算
    for (i = 0; i < size; i++) {
        students[i].DS = (students[i].gpa - avgGPA) / num * 10 + 50;
    }
}