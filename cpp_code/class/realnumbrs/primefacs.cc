#include <iostream>
#include <vector>

using namespace std;
void prime_facts(int n, vector<int>& factors) {
    if (n<=1){
        return ;
    }
    if (n%2==0){
        factors.push_back(2);
        prime_facts(n/2,factors);
    }
    else{
        for (int i=3;i*i<=n;i+=2){
            if (n%i==0){
                factors.push_back(i);
                prime_facts(n/i,factors);
                return ;
            }
        }
        factors.push_back(n);`
    }
}

int main() {
    int n=84;
    vector<int> factors;
    prime_facts(n, factors);
    cout << "Prime factors of " << n << " are: ";
    for (int i = 0; i < factors.size(); ++i) {
        cout << factors[i] << " ";
    }
    cout << endl;
    return 0;
}