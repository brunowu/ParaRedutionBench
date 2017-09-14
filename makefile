ALL: blib exec

#compilation and various flags
DIRS    = 
EXEC    = vector.exe
CFLAGS	= 
FFLAGS	= 
CPPFLAGS	= 
FPPFLAGS	=
CLEANFILES  = ${EXEC}
OFILES= ${wildcard ./*.o}
NBLOCK = 2
DEBUG_VALGRIND = valgrind
DIM = 1000000000
TEST_TYPE = -sum_test
#TEST_TYPE = -dot_test
MPI_NODE = 128


include ${PETSC_DIR}/lib/petsc/conf/variables
include ${PETSC_DIR}/lib/petsc/conf/rules

blib :
	-@echo "BEGINNING TO COMPILE LIBRARIES "
	-@echo "========================================="
	-@${OMAKE}  PETSC_ARCH=${PETSC_ARCH} PETSC_DIR=${PETSC_DIR} ACTION=libfast tree
	-@echo "Completed building libraries"
	-@echo "========================================="

distclean :
	-@echo "Cleaning application and libraries"
	-@echo "========================================="
	-@${OMAKE} PETSC_ARCH=${PETSC_ARCH}  PETSC_DIR=${PETSC_DIR} clean
	-${RM} ${OFILES}
	-@echo "Finised cleaning application and libraries"
	-@echo "========================================="	

exec: vec_test.o
	-@echo "BEGINNING TO COMPILE APPLICATION "
	-@echo "========================================="
	-@${CLINKER} -o ${EXEC} vec_test.o ${PETSC_LIB}
	-@echo "Completed building application"
	-@echo "========================================="


runa:
	-@${MPIEXEC} -np ${MPI_NODE} ./vector.exe -dim ${DIM} ${TEST_TYPE}\

#	-mat_type aijcusparse -vec_type cuda

runb:
	./matgen.exe -mat_type aijcusparse -vec_type cuda
