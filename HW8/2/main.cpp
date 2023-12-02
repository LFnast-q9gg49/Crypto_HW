#include <iostream>
#include <unistd.h>

using namespace std;

const int p     = 263819;
const int q     = 131909;
const int g     = 3; // generator 
const int ha    = 36832;
const int hb    = 102879;

int find_x_of_a(){
    // g^x mod p = ha
    int h_tmp = g;
    for (int i = 2; i < q; i++){
        h_tmp *= g;
        h_tmp %= p;
        if (h_tmp == ha){
            return i;
        }
    }
    return 1;
}

int main(){
    // first is to find x
    int x_of_a = find_x_of_a();
    cout << "the x of a is " << x_of_a << endl;

    // next is to calculate the k
    long k = 1;
    for (int i = 1; i <= x_of_a; i++){
        k *= hb;
        k %= p;
    }
    cout << "final key is " << k << endl;
}