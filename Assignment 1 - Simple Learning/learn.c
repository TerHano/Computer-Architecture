#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

int rows;
int col;
double* multiplyFinal(double** matrix, int matrow, int matcol, double*prices){
    double *result = malloc(sizeof(double)*rows);
    int i;
    int j;
    double sum = 0;
    for(i = 0;i< matrow;i++){
        for(j = 0;j<matcol;j++){
            sum+= (matrix[i][j]*prices[j]);
        }
        result[i] = sum;
        sum = 0;
    }
    return result;
}

double** multiply(double** matrix, int matrow, int matcol, double** Tmax, int trow, int tcol){
    double **mul = (double**)malloc(sizeof(double*)*matrow);
    int i;
    for(i = 0;i<matrow;i++){
        mul[i] = (double*)malloc(sizeof(double)*tcol);
    }
    for(i = 0;i<matrow;i++){
        int j;
        double a = 0;
        int k;
        for(k = 0;k<tcol;k++) {
            for (j = 0; j < trow; j++) {
                a += (matrix[i][j] * Tmax[j][k]);
            }
            mul[i][k] = a;
            a = 0;
        }
    }
    return mul;
}
double** inverse(double **matrix,double** identity){

    double **inv = (double**)malloc(sizeof(double*)*col);
    int i;
    for(i = 0;i<col;i++){
        inv[i] = (double*)malloc(sizeof(double)*col);
    }
    for (i = 0;i<col;i++){
        int j;
        for(j = 0;j<col;j++){
            inv[i][j] = matrix[i][j];
        }
    }
    i = 0;
    int j = 0;
    while(i<col){
        if(inv[i][i] != 1){
            double temp = 1/(inv[i][i]);
            int k;
            for(k = 0;k<col;k++){
                inv[i][k] *= temp;
                identity[i][k] *= temp;
            }
        }
        for(j = i+1;j<col;j++){
            if(inv[j][i] != 0){
                int z;
                double matmakezero = inv[j][i];
                for(z = 0;z<col;z++){
                    inv[j][z] -= ((inv[i][z])*matmakezero);
                    identity[j][z] -= ((identity[i][z])*matmakezero);
                }
            }
        }
        i++;

    }
    i = col-1;
    while(i > -1){
        for(j = i-1; j > -1;j--) {
            if (inv[j][i] != 0) {
                double matmakezero = inv[j][i];
                int z;
                for (z = 0; z < col; z++) {
                    inv[j][z] -= ((inv[i][z]) * matmakezero);
                    identity[j][z] -= ((identity[i][z])*matmakezero);
                }
            }
        }
        i--;
    }
    return identity;
}
double** transpose(double **matrix){
    double **matrixT = (double**)malloc(sizeof(double*)*col);
    int i;
    for(i = 0;i<col;i++){
        matrixT[i] = (double*)malloc(sizeof(double)*rows);
    }
    for(i = 0;i<col;i++){
        int j;
        for(j = 0;j<rows;j++){
            matrixT[i][j] = matrix[j][i];
        }
    }
    return matrixT;
}
int main(int argc, char*argv[]) {
    FILE *file;
    file = fopen(argv[1],"r");
    char line[1000];
    col = atoi(fgets(line, sizeof(line),file))+1;
    rows = atoi(fgets(line, sizeof(line),file));
    double **matrix = (double**)malloc(sizeof(double*)*rows);
    int i;
    for(i = 0;i<rows;i++){
        matrix[i] = (double*)malloc(sizeof(double)*(col));
    }
    double **identity = (double**)malloc(sizeof(double*)*col);
    for(i = 0;i<col;i++){
        int j;
        for(j = 0;j<col;j++){
            identity[i] = (double*)malloc(sizeof(double)*(col));
            identity[i][j] = 0;
        }
    }
    for(i = 0;i<col;i++){
        identity[i][i] = 1;
    }
    double *houseprice = (double*)malloc(sizeof(double)*(rows));
    for(i = 0;i<rows;i++){
        fgets(line, sizeof(line),file);
        char* tok = strtok(line,",\n");
        int j;
        for(j = 0;j<col;j++){
            if(j == 0){
                matrix[i][j] = 1;
                continue;
            }
            matrix[i][j] = strtof(tok,NULL);
            tok = strtok(NULL,",\n");
        }
       houseprice[i] = strtof(tok,NULL);
    }
    double** matT = transpose(matrix);
    double** readyforInverse = multiply(matT, col, rows,matrix, rows, col);
    double** inversed = inverse(readyforInverse,identity);
    double **almost = multiply(inversed,col,col,matT,col,rows);
    double* done = multiplyFinal(almost,col,rows,houseprice);
    file = fopen(argv[2],"r");
    rows = atoi(fgets(line, sizeof(line),file));
    double *attrib = (double*)malloc(sizeof(double)*col);
    double sum = 0;
    for(i = 0;i<rows;i++){
        fgets(line, sizeof(line),file);
        int j;
        char *tok = strtok(line, ",\n");
        for(j = 0;j<col;j++) {
            if (j == 0) {
                attrib[j] = 1;
            } else {
                attrib[j] = strtof(tok, NULL);
                tok = strtok(NULL, ",\n");
            }
        }
        sum = 0;
        int x;
        for(x = 0;x<col;x++){
            sum += (done[x]*attrib[x]);
        }
        printf("%0.0f\n",sum);
    }
    return 0;
}
