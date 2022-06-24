#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#define SIZE 200
#define w 1.5
#define n 1.0
typedef struct{
    long x;
    long y;
}VirusPlace;

int nVirus = 0;
int nCandidates = 0;
void writeFile(double C[SIZE][SIZE]){
    char filename[] = "VirusPlace.txt";
    FILE *f = fopen(filename, "w");
    if(f == NULL){
        printf("Can not open %s", filename);
    }
    int i, j;
    for(i=0; i<SIZE; i++){
        for(j=0; j<SIZE; j++){
            fprintf(f, "%.2lf\t", C[i][j]);
        }
        fprintf(f, "\n");
    }
}

void addVirus(u,v,x){
    virus[x]=1;
    if(u == 1){
        if(v == 1){    
            Grow[u+1][v]=1;
            Grow[u][v+1]=1;
            nCandidates+=2;
        }
        else if(v == SIZE){
            Grow[u+1][v]=1;
            Grow[u][v-1]=1;
            nCandidates+=2;
        }
        else{
            Grow[u+1][v]=1;
            Grow[u][v-1]=1;
            Grow[u][v+1]=1;
            nCandidates+=3;
        }
    }
    else if(u == SIZE){
        if(v == 1){    
            Grow[u-1][v]=1;
            Grow[u][v+1]=1;
            nCandidates+=2;
        }
        else if(v == SIZE){
            Grow[u-1][v]=1;
            Grow[u][v-1]=1;
            nCandidates+=2;
        }
        else{
            Grow[u-1][v]=1;
            Grow[u][v-1]=1;
            Grow[u][v+1]=1;
            nCandidates+=3;
        }
    }
    else{
        Grow[u][v+1]=1;
        Grow[u][v-1]=1;
        Grow[u-1][v]=1;
        Grow[u+1][v]=1;
        nCandidates+=4;
    }
}


void init(double C[SIZE+2][SIZE+2], int grow[SIZE+2][SIZE+2], VirusPlace virus[], int candidates[], double chance[]){
    // int i, j;
    // for(i = 0; i<SIZE+2; i++){
    //     for(j = 0; j<SIZE+2; j++){
    //         if(i == 0 || j == 0 || i == SIZE + 1 || j == SIZE + 1){
    //             C[i][j] = 0;
    //         }else C[i][j] = 1;
    //         grow[i][j] = 0;
    //         candidates[i*(SIZE+1) + j] = 0;
    //         chance[i*(SIZE+1) + j] = 0.0;
    //     }
    // }
    // C[1][SIZE/2 + 1] = 0;
    // grow[1][SIZE/2 + 1] = 1;
    // virus[0].u = 1;
    // virus[0].v = SIZE/2 + 1;
    // candidates[SIZE/2 + 1] = 1;
    // nVirus = 1;
    int i,j;
    for(i=1;i<SIZE+1;i++){
        for(j=1;j<SIZE+1;j++){
            Grow[i][j]=0;
            C[i][j] = 1;
    }
    addVirus(SIZE,SIZE/2 +1,x);
}

void sor(double C[SIZE+2][SIZE+2], int grow[SIZE+2][SIZE+2]){
    int i, j;
    for(i = 1; i < SIZE + 1;i++){
        for(j = 1; j = SIZE + 1; j++){
            C[i][j] = w*(C[i-1][j] + C[i+1][j] + C[i][j-1] + C[i][j+1])/4 + (1-w)* C[i][j];
        }
    }
}

void eat(double C[SIZE+2][SIZE+2], int grow[SIZE+2][SIZE+2]){
    int i, j;
    for(i = 1; i < SIZE + 1; i++){
        for(j = 1; j < SIZE + 1; j++){
            if(grow[i][j] == 1)
                C[i][j] = 0;
        }
    }
}
void computeProbability(double C[SIZE+2][SIZE+2], int grow[SIZE+2][SIZE+2],int candidates[], double chance[]){
    int i, j;
    nCandidates = 0;
    for(i = 1; i < SIZE + 1; i++){
        for(j = 1; j < SIZE + 1; j++){
            if(grow[i][j] == 1){
                double c_up = pow(C[i-1][j],n);
                double c_down = pow(C[i+1][j],n);
                double c_left = pow(C[i][j-1],n);
                double c_right = pow(C[i][j+1],n);
                double sum = c_up + c_down + c_left + c_right;
                c_up /= sum;
                c_down /= sum;
                c_left /= sum;
                c_right /= sum;
                chance[(i-1)*SIZE + j] = c_up > chance[(i-1)*SIZE + j] ? c_up : chance[(i-1)*SIZE + j];
                chance[(i+1)*SIZE + j] = c_down > chance[(i+1)*SIZE + j] ? c_down : chance[(i+1)*SIZE + j];
                chance[i*SIZE + j-1] = c_left > chance[i*SIZE + j-1] ? c_left : chance[i*SIZE + j-1];
                chance[i*SIZE + j+1] = c_right > chance[i*SIZE + j+1] ? c_right : chance[i*SIZE + j+1];
            }
            if(chance[i*(SIZE + 1) + j] != 0){
                nCandidates++;
            }
        }
    }
}

void growth(double C[SIZE+2][SIZE+2], int Grow[SIZE+2][SIZE+2],VirusPlace virus[],int candidates[], double chance[]){
    int i, j;
    for(i = 1; i <= SIZE + 1; i++){
        for(j = 1; j <= SIZE + 1; j++){
            if((rand() % 101)/100.0 < chance[i*SIZE + j]){
                virus[nVirus].u = i;
                virus[nVirus].v = j;
                nVirus++;
                candidates[i* (SIZE + 1) + j] = 0;
            }
        }
    }
}

int main(){
    int N = (SIZE+2)*(SIZE+2);
    double C[SIZE+2][SIZE+2];
    int Grow[SIZE+2][SIZE+2];
    VirusPlace virus[N];
    int candidates[N];
    double chance[N];
    init(C, Grow, virus,candidates, chance);



    int i;
    for(i = 0; i < 5; i++){
        sor(C, Grow);
        eat(C, Grow);
        computeProbability(C, Grow,candidates,chance);
        growth(C, Grow,virus,candidates, chance);
    }
    writeFile(C);
}