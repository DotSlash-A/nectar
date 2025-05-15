

#include <stdio.h>

// Print the first n terms of an AP
void write_ap(double a, double d, int n) {
    printf("The AP is: ");
    for (int i = 0; i < n; i++) {
        double term = a + (i * d);
        printf("%d", (int)term);
        if (i < n - 1) printf(", ");
    }
    printf("\n");
}

// Print the nth term of an AP
void nth_term(double a, int n, double d) {
    double an = a + ((n - 1) * d);
    printf("%dth term is %d\n", n, (int)an);
}

// Check which term (if any) a value is in the AP
void which_term_is_x(double a, double d, double x) {
    double n = ((x - a) / d) + 1;
    if (n == (int)n && n > 0) {
        printf("%.2f is the %dth term in the AP\n", x, (int)n);
    } else {
        printf("%.2f is not a term in the AP.\n", x);
    }
}

// Print the nth term from the end of the AP
void nth_term_from_end(double last_term, int n, double d) {
    double term = last_term - ((n - 1) * d);
    printf("%dth term from end is: %d\n", n, (int)term);
}

// Calculate number of terms in AP given first term, common difference, and last term
void how_many_term_are_there_in_ap(double a, double d, double an) {
    int n = ((an - a) / d) + 1;
    printf("There are %d terms in the AP\n", n);
}

// Print the middle term(s) of the AP
void middle_term_of_ap(double a, double d, double an, int n) {
    // If n is not provided (0), calculate it
    if (n == 0) {
        n = ((an - a) / d) + 1;
    }
    if (n % 2 == 1) {
        int term_number = (n + 1) / 2;
        double term = a + ((term_number - 1) * d);
        printf("There is only one middle term: term #%d = %d\n", term_number, (int)term);
    } else {
        int term_num1 = n / 2;
        int term_num2 = term_num1 + 1;
        double term1 = a + ((term_num1 - 1) * d);
        double term2 = a + ((term_num2 - 1) * d);
        printf("There are two middle terms: term #%d = %d and term #%d = %d\n",
               term_num1, (int)term1, term_num2, (int)term2);
    }
}

// Print the sum of the first n terms of the AP
void sum_of_n_terms(double a, double d, int n) {
    double sn = (n / 2.0) * (2 * a + (n - 1) * d);
    printf("Sum of first %d terms is: %.2f\n", n, sn);
}

int main() {
    // Example calls to all functions
    write_ap(4, -3, 4);                // AP: 4, 1, -2, -5
    nth_term(2, 5, 3);                 // 5th term
    which_term_is_x(-1, 4, 95);        // Which term is 95?
    nth_term_from_end(-40, 6, -3);     // 6th term from end
    how_many_term_are_there_in_ap(2, 3, 20); // Number of terms from a to an
    middle_term_of_ap(2, 3, 20, 0);    // Middle term(s), n calculated
    sum_of_n_terms(2, 3, 5);           // Sum of first 5 terms

    return 0;
}


// // Online C compiler to run C program online
// #include <stdio.h>
// void write_ap(double a, double d, int n){
//     printf("the AP is:");
//     for (int i=0;i<n;i++){
//         double term=a+(i*d);
//         printf("%d,", (int)term);
//     }
//     printf("\n");
// }

// void nth_term(double a, int n, double d){
//     double an=a+((n-1)*d);
//     printf("%dth term is %d", n, (int)an);
// }


// void which_term_is_x(double a, double d, double x){
//     double an=95;
//     double n = ((an-a)/d)+1;
    
//     if (n==(int)n){
//         printf("it is %dth term in the ap", (int)n);
//     }
//     else{
//         printf("it is not a term in the ap.");
//     }
    
// }

// void nth_term_from_end(double last_term,int n, double d){
//     double term=last_term-((n-1)*d);
//     printf("last term from end is: %d \n", (int)term);
// }

// void how_many_term_are_there_in_ap(double a, double d, double an){
//     int n = ((an-a)/d)+1;
//     printf("there are %d terms in ap",n );
// }

// void middle_term_of_ap(double a, double d, double an, int n){
//     if n=0{
//     int n =((an-a)/d)+1;
//     }
//     if (n%2==1){
//         printf("there is only one middle term");
//         int term_number= ((n+1)/2);
//         double term = a+((term_number-1)*d);
//     }
//     if(n%2==0){
//         printf("there are two middle terms");
//         int term_num1 =(n/2);
//         int term_num2= term_num+1;
//         double term1=a+((term_num1-1)*d);
//         double term1=a+((term_num2-1)*d);
//         printf("there are two middle terms and they are %d and %d ",term_num1,term_num1);
//     }
// }

// void sum_of_n_terms(double a, double d, double n){
//     double sn=((n/2)*((2*a)+((n-1)*d)));
// }

// int main() {
//     // Write C code here
//     write_ap(4,-3,4);
//     nth_term_from_end(-40,6,-3);
//     which_term_is_x(-1,4,95);
    


//     return 0;
// }