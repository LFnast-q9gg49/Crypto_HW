#include <iostream>
#include <unistd.h>
#include <vector>
#include <bitset>

using namespace std;

const int mod = 0B100011011; // here we use x8+x4+x3+x+1

const vector<vector<int>> s = {
    {0x33, 0xD2, 0x04, 0x96},
    {0xF1, 0xC4, 0xD0, 0x0C},
    {0x8C, 0xE7, 0xDE, 0x48},
    {0xD3, 0xA4, 0x2C, 0xB5}
};

const vector<vector<int>> mix_mat = {
    {0x2, 0x3, 0x1, 0x1},
    {0x1, 0x2, 0x3, 0x1},
    {0x1, 0x1, 0x2, 0x3},
    {0x3, 0x1, 0x1, 0x2}
};

void print_mat(const vector<vector<int>> s){
    for (auto &i : s){
        for (auto &j : i){
            cout << hex << static_cast<int>(j) <<'\t' ;
        }
        cout << endl;
    }
}

int get_value(int m, int s){
    switch(m){
        case 1:
            return s;
        case 2:
            return (s << 1);
        case 3:
            return (s << 1) ^ s;
    }
    return 0;
}

int calculate(int i, int j){
    // to calculate S_{i,j} 
    // S_{i,j} = \sum ( mix_mat_{i} * s_{j} )

    int sum = 0;
    for (int k = 0; k < 4; k++){
        sum ^= get_value(mix_mat[i][k], s[k][j]);
    }
    // judge sum is 8-bits or 9-bits, if the sum is 9-bits
    if (sum > 0xFF){
        sum ^= mod;
    }

    return sum;
}

int main(int argc, char **argv){
    // create a 4*4 matrix to store the output of mix_mat * s
    vector<vector<int>> out_mat(4, vector<int>(4, 0));
    for (int row = 0; row < 4; row++){
        for (int col = 0; col < 4; col++){
            out_mat[row][col] = calculate(row, col);
        }
    }
    cout << "the original mat is like : " << endl;
    print_mat(s);
    cout << endl;
    cout << "the mix-column mat is like : " << endl;
    print_mat(out_mat);
    exit(0);
}