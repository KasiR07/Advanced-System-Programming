#include <stdio.h>

// 1) Function to find the minimum of three numbers
int minimum(int num1, int num2, int num3) {
    int min = num1;
    if (num2 < min) min = num2;
    if (num3 < min) min = num3;
    return min;
}

// 2) Function to find the maximum of three numbers
int maximum(int num1, int num2, int num3) {
    int max = num1;
    if (num2 > max) max = num2;
    if (num3 > max) max = num3;
    return max;
}

// 3) Function to return the product of two numbers
int product(int num1, int num2) {
    return num1 * num2;
}
// 4) Function 'compute' which accepts function pointers and integers
int compute(int (*fmin)(int, int, int),
            int (*fmax)(int, int, int),
            int (*fprod)(int, int),
            int num1, int num2, int num3) {
    
    int mn = fmin(num1, num2, num3);  // minimum of the three
    int mx = fmax(num1, num2, num3);  // maximum of the three
    
    // Return the product of the minimum and maximum
    return fprod(mn, mx);
}

int main() {
    int num1, num2, num3;
    
    // Ask the user for input
    printf("Enter three integers: ");
    scanf("%d %d %d", &num1, &num2, &num3);
    
    // Call 'compute' by passing in the function pointers and the integers
    int result = compute(minimum, maximum, product, num1, num2, num3);
    
    // Print the result
    printf("Product of the minimum and maximum of (%d, %d, %d) is: %d\n",
           num1, num2, num3, result);
    
    return 0;
}