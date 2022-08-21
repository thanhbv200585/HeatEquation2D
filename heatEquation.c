#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define m 20
#define n 20
#define T 10
#define dt 0.01
#define dx 0.1
#define dy 0.1
#define D 0.1
#define M 200
#define N 200
void init(double C[M+2][N+2]){
    for(int i = 0; i < M+2; i++){
        for(int j = 0; j < N+2; j++){
            if(i > 0 && i < M+1 && j > 0 && j < N+1){
                C[i][j] = 80.0;
            }else{
                C[i][j] = 25.0;
            }
        }
    }
}

void printData(double C[M+2][N+2]){
    char filename[] = "data.txt";
    FILE *f = fopen(filename, "w+");

    for(int i = 0; i < M+2; i++){
        for(int j = 0; j < N+2; j++){
            fprintf(f, "%lf   ",C[i][j]);
        }
        fprintf(f,"\n");
    }
}

void truyenNhiet(double C[M+2][N+2], double FD[M+2][N+2]){
    for(int i = 1; i <=M; i++){
        for(int j = 1; j <= N; j++){
            FD[i][j] = (C[i+1][j] - 2*C[i][j] + C[i-1][j])/(dx*dx) + (C[i][j+1] - 2*C[i][j] + C[i][j-1])/(dy*dy);
            C[i][j] = C[i][j] +D*dt*FD[i][j];
        }
    }

void dieuKienBien(double C[M+2][N+2]){
    for(int i = 0; i < M+2; i++){
        for(int j = 0; j < N+2; j++){
            if(i > 0 && i < M+1 && j > 0 && j < N+1){}else{
                C[i][j] = 25.0;
            }
        }
    }
}
int main(){
    double C[M+2][N+2];
    double FD[M+2][N+2];
    init(C);
    double t = 0;
    while(t < T){
        truyenNhiet(C,FD);
        dieuKienBien(C);
        t +=0.01;
    }
    printData(C);
}