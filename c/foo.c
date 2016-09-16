#include <stdio.h>

inline int layer_count(int R, int C)
{
	int count = 0;
	count = R > C ? 
		C/2 + C%2 : 
		R/2 + R%2;
	return count;
}

inline int element_count(int R, int C, int i)
{
	// get row column
	int r = R - (i*2);
	int c = C - (i*2);

	// get element count
	return 2*r + 2*c - 4;
}

int *prepare_array(int **M, int R, int C, int i)
{
    int ei = 0;
	int *ea = 0;

	ec = element_count(R, C, i);
	ea = (int*)malloc(ec*sizeof(int));

	// get element array
    // right
    for (ci = i; ci < c - 1; ci++) {
        ea[ei++] = M[i][ci];
    }
    // down
    for (ri = i; ri < r - 1; ri++) {
        ea[ei++] = M[ri][ci];
    }
    // left
    for (ci = c - 1; ci > 0; ci--) {
        ea[ei++] = M[r-1][ci];
    }
    // up
    for (ri = r - 1; ri > 0; ri--) {
        ea[ei++] = M[ri][i];
    }

    return ea;
}

void rotate_array(int *A, int R, int C, int i, int S)
{
    int i = 0, x = 0;
    int ec = element_count(R, C, i);

    // following is 1 step rotation
    x = A[0];
    for (i = 0; i < ec - 1; i++) {
        A[i] = A[i+1];
    }
    A[i] = x;

    return;
}

void restore_array(int *A, int **M, int R, int C, int i)
{
    int ei = 0;

    // right
    for (ci = i; ci < c - 1; ci++) {
        M[i][ci] = A[ei++];
    }
    // down
    for (ri = i; ri < r - 1; ri++) {
        M[ri][ci] = A[ei++];
    }
    // left
    for (ci = c - 1; ci > 0; ci--) {
        M[r-1][ci] = A[ei++];
    }
    // up
    for (ri = r - 1; ri > 0; ri--) {
        M[ri][i] = A[ei++];
    }

    free(A);
    return;
}

void print_matrix(int **M, int R, int C)
{
    int i = 0, j = 0;
    for (i = 0; i < R; i++) {
        for (j=0; j < C; j++) {
            printf("%d\t", M[i][j]);
        }
        printf("\n");
    }
    return;
}

int main ()
{
	// read matrix M, 
	// R - row
	// C - column
	// S - steps

	int* A = 0;
	int i = 0, j = 0;
	int c = layer_count(R, C);
	
	for (i = 0; i < c; i++) {
		A = prepare_array(M, R, C, i);
		rotate_array(A, R, C, i, S);
		restore_array(A, M, R, C, i);
	}
    print_matrix(M, R, C);
}

