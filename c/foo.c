#include <stdio.h>
#include <stdlib.h>

struct layer {
    int r_count; // row
    int c_count; // column
    int index;
    int *arr;
    int arrLen;
};
typedef struct layer layer_t;

inline int **create_matrix(int R, int C)
{
    int **M = 0;
    M = malloc(R*sizeof(int*));
    for (i = 0; i < R; i++) {
        M[i] = malloc(C*sizeof(int));
    }
    return M;
}

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

inline int get_layer(layer_t *l, int R, int C, int i)
{
    l->index = i;
    l->r_count = R - (i*2);
    l->c_count = C - (i*2);
	l->arrLen = (2 * l->r_count) + 
                (2 * l->c_count) - 4;
	l->arr = (int*)malloc(l->arrLen*sizeof(int));
    return 0;
}

int prepare_array(int **M, layer_t *l)
{
    int ri = 0, ci = 0;
    int ei = 0;
    int *A = l->arr;
    int i = l->index;
    int c = l->c_count;
    int r = l->r_count;

	// get element array
    // right
    for (ci = i; ci < c - 1; ci++) {
        A[ei++] = M[i][ci];
    }
    // down
    for (ri = i; ri < r - 1; ri++) {
        A[ei++] = M[ri][ci];
    }
    // left
    for (ci = c - 1; ci > 0; ci--) {
        A[ei++] = M[r-1][ci];
    }
    // up
    for (ri = r - 1; ri > 0; ri--) {
        A[ei++] = M[ri][i];
    }

    return 0;
}

void rotate_array(layer_t *l, int S)
{
    int i = 0, x = 0;
    int *A = l->arr;
    int ec = l->arrLen;

    // following is 1 step rotation
    x = A[0];
    for (i = 0; i < ec - 1; i++) {
        A[i] = A[i+1];
    }
    A[i] = x;

    return;
}

void restore_array(int **M, layer_t *l)
{
    int ei = 0;
    int ri = 0, ci = 0;
    int *A = l->arr;
    int i = l->index;
    int c = l->c_count;
    int r = l->r_count;

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

    free(l->arr);
    l->arr = 0;
    l->arrLen = 0;
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
    int **M = 0; // matrix
    int i = 0, j = 0;
    int R = 0, C = 0, S = 0; // row, col, steps
    layer_t l;

    scanf("%d %d %d", &R, &C, &S);
    M = create_matrix(R, C);

    for (i = 0; i < R; i++) {
        for (j = 0; j < C; j++) {
            scanf("%d", &M[i][j]);
        }
    }

    printf("--- before ---\n");
    print_matrix(M, R, C);

	int lc = layer_count(R, C);
	
	for (i = 0; i < lc; i++) {
        // get row column
        get_layer(&l, R, C, i);
		prepare_array(M, &l);
		rotate_array(&l, S);
		restore_array(M, &l);
	}

    printf("--- after ---\n");
    print_matrix(M, R, C);

    delete_matrix(M, R, C);

    return 0;
}

