#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

int main(int argc, char **argv){
    FILE *fp = fopen("./ciphertext", "r"); // first we open the ciphertext using readonly mod
    int c = 0; // store tmp char 
    int num = 0; // count the char
    // create a vector to store the count of each char and init it
    vector<int> c_count;
    for (int i = 0; i < 26; i++){
        c_count.emplace_back(0);
    }

    // statistic
    while((c = fgetc(fp)) != EOF){
        c_count[c-'A']++;
        num++;
    }

    // print the output
    cout << "The Possible Table" << endl;
    for (int j = 0; j < 26; j++){
        cout << char(j+'A') << " : " << fixed << setprecision(4) << double(c_count[j])/num << '\t';
        if (j % 5 == 4){
            cout << endl;
        }
    }
    cout << endl;
    exit(0);
}