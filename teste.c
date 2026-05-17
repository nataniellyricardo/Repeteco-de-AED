#include <stdio.h>
#include <stdlib.h>

int main() {
    int n = 5; 
    int i, j;

    int *nums = (int *)malloc(n * sizeof(int));
    //nums[0] = 1; 
	//nums[1] = 2; 
	//nums[2] = 1;
   
    nums[0] = 1; 
	nums[1] = 2; 
	nums[2] = 3; 
	nums[3] = 4; 
	nums[4] = 3;

    printf("teste:");

    for (i = 0; i < n; i++) {
        int cont = -1; 

        for (j = i + 1; j < n; j++) {
            if (nums[j] > nums[i]) {
                cont = nums[j];
                break;
            }
        }

        if (cont == -1) {
            for (j = 0; j < i; j++) {
                if (nums[j] > nums[i]) {
                    cont = nums[j];
                    break;
                }
            }
        }

        printf(" %d", cont);
    }

    printf("\n");
    free(nums);
    return 0;
}
