#include "petscmat.h"
#include <time.h>

int main(int argc, char ** argv){

PetscInitialize(&argc,&argv,(char *)0,NULL);

PetscInt xstart, xend;
PetscInt dim, j;
PetscScalar xvalue, sum, dot;
Vec x;
char* xType;
PetscBool dim_flg,sum_flg,dot_flg;
double cost_time;
clock_t start, end;

PetscOptionsGetInt(NULL,NULL,"-dim",&dim,&dim_flg);

if(!dim_flg){
	dim = 100;
	PetscPrintf(PETSC_COMM_WORLD, "Unset the vector dimension, use the default value dim = %d \n", dim);
}

VecCreate(PETSC_COMM_WORLD,&x);
VecSetSizes(x, PETSC_DECIDE, dim);
VecSetFromOptions(x);
VecGetOwnershipRange(x, &xstart, &xend);

for(j = xstart; j< xend; j++){
    xvalue = (PetscScalar)1;
    VecSetValues(x, 1, &j, &xvalue, INSERT_VALUES);
}

VecAssemblyBegin(x);
VecAssemblyEnd(x);
//VecView(x, PETSC_VIEWER_STDOUT_WORLD);
VecGetType(x,&xType);

PetscOptionsHasName(NULL,NULL,"-sum_test", &sum_flg);
PetscOptionsHasName(NULL,NULL,"-dot_test", &dot_flg);

/*
start = clock();
if(sum_flg){
	VecSum(x, &sum);
	PetscPrintf(PETSC_COMM_WORLD, "Vector sum test = %f \n",sum);
}
if(dot_flg){
	VecDot(x,x,&dot);
        PetscPrintf(PETSC_COMM_WORLD, "Vector dot test \n");
}
end = clock();

cost_time = (double)(end - start)/CLOCKS_PER_SEC;

PetscPrintf(PETSC_COMM_WORLD, "Execution Time is %.6f \n",cost_time);
*/

start = clock();
VecSum(x, &sum);
end = clock();
cost_time = (double)(end - start)/CLOCKS_PER_SEC;
PetscPrintf(PETSC_COMM_WORLD, "Vector sum test = %f \n",sum);
PetscPrintf(PETSC_COMM_WORLD, "Execution Time is %.6f \n",cost_time);
PetscPrintf(PETSC_COMM_WORLD, "Vector type is %s \n",xType);
PetscPrintf(PETSC_COMM_WORLD, "Finish \n");
PetscFinalize();

return 0;
}
