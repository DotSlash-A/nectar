// Online C compiler to run C program online
#include <stdio.h>


int add(int a , int b){
    return a+b;
}
int multiply(int x, int y){
    return x*y;
}
int divide(int x, int y){
    return x/y;
}

int main() {

    int sum = add(3,5);
    int product= multiply(3,5);
    int division = divide(6,2);
    printf("Sum is %d\n", sum);
    printf("Product is %d\n", product);
    printf("Quotient is %d\n", division);
    return 0;
}