#include <stdio.h>

// #define PROTO void NeonTest(float * __restrict a, float * __restrict b, float * __restrict z)
#define PROTO void NeonTest(float *            a, float *            b, float *            z)

PROTO 
 {
    int i,j;
    for (j=0; j<200000; j++) {
        for(i=0;i<200;i++) {
            z[i] = a[i] * b[i];
        }
    }
 }

int main () {
    float a[200], b[200], z[200];
    int i,j;

    a[0] = 0.05;
    b[0] = 0.07;
    for(i=1;i<200;i++) {
        a[i] = a[i-1] + a[i-1];
        b[i] = b[i-1] + b[i-1];
    }

    printf("Begin Test\n");
    NeonTest(a, b, z);
    printf("Test Complete z[0]=%d\n", (int)z[0]);
}
