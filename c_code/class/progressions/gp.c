
#include <stdio.h>
#include <math.h>

void write_gp(int a, int r, int n) {
    for(int i = 0; i < n; i++) {
        double term = a * pow(r, i);
        printf("%d ", (int)term); // prints as integer
    }
    printf("\n");
}

void nth_term_of_gp(double a, double r, int n){
    double term = (a*(pow(r,(n-1))));
    printf("term is ", term);
}

void is_term_in_gp(double a, double r, double x){
    if (x==0 ? a==0){
        printf("woops");
    }
    else{
        double n=log(x/a)/log(r)+1;
        if (n==(int)n){
            printf("it is the nt term");
        }
        else{
            printf("x is ot a term inthe gp");
        }
    }
}




int main() {
    write_gp(2, 3, 5);
    return 0;
}
