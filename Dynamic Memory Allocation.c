#include <stdio.h>
#include <stdlib.h>

int main() {
    int n;
    int *arr;
    
    printf("Enter the size of array (n >= 1): ");
    scanf("%d", &n);
    
    arr = (int *)malloc(n * sizeof(int));
    if (arr == NULL) {
        printf("Memory allocation failed\n");
        return 1;
    }
    
    printf("Enter %d integers:\n", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", (arr + i));    // Using pointer dereferencing
    }
    
    printf("Elements in reverse order:\n");
    for (int i = n - 1; i >= 0; i--) {
        printf("%d ", *(arr + i));  // Using pointer dereferencing
    }
    printf("\n");
    
    free(arr);
    return 0;
}