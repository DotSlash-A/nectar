// Online C compiler to run C program online
#include <stdio.h>
#include <math.h>


double all_ratios_given_two_sided(double perp, double base){
    double hyp=sqrt((perp+base)*(perp-base));
}

int main() {
    // Write C code here
    double res;
    res=all_ratios_given_two_sided(3,4);
    printf("%d", res);
    
    

    return 0;
}
