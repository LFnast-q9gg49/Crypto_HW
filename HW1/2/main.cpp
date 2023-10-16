#include <iostream>
#include <vector>
#include <iomanip>
#include <algorithm>

using namespace std;

// normal english words posibility
const std::vector<double> expected_freq = {
                                            0.08167, 0.01492, 0.02782, 0.04253, 0.12702,
                                            0.02228, 0.02015, 0.06094, 0.06966, 0.00153,
                                            0.00772, 0.04025, 0.02406, 0.06749, 0.07507,
                                            0.01929, 0.00095, 0.05987, 0.06327, 0.09056,
                                            0.02758, 0.00978, 0.02360, 0.00150, 0.01974,
                                            0.00074
                                            };

class Cipher{
public:
    void find_length(vector<int> c_text);
    int find_key(vector<int> c_text, int k_s);
};

void Cipher::find_length(vector<int> c_text){
    vector<double> tmp_team;
    for (int i = 0; i < 26; i++){
        tmp_team.emplace_back(0);
    }

    for (int t = 1; t < 10; t++){ // range the length of key, guess the length is below 10
        double team_sum = 0;
        cout << "tau is " << t << " and posibility is ";
        for (int j = 0; j < t; j++){ // group start with 0, 1, ... t
            double sum = 0;
            int team_cnt = 0;
            for (int i = 0; i < 26; i++){
                tmp_team[i] = 0;
            }
            // divide the cipher text by the tau
            for (int i = j; i < c_text.size(); i += t){
                tmp_team[c_text[i]]++;
                team_cnt++;
            }
            // calculate
            for (int i = 0; i < 26; i++){
                sum += tmp_team[i] * (tmp_team[i] - 1);
            }
            sum /= (team_cnt * (team_cnt-1));
            cout << fixed << setprecision(3) << sum << ' ';
        }
        cout << endl;
    }

}

int Cipher::find_key(vector<int> c_text, int k_s){
    // we have know the length is 3, so we can divide the c_text to three parts
    vector<double> team_ci;
    vector<double> key_s;
    int team_cnt = 0;
    for (int j = 0 ; j < 26; j++){
        team_ci.emplace_back(0);
    }
    for (int i = k_s; i < c_text.size(); i += 6){        
        team_ci[c_text[i]]++;
        team_cnt++;
    }
    // caculate the frequency
    for (int j = 0 ; j < 26; j++){
        team_ci[j] /= team_cnt;
    }

    for (int k = 0; k < 26; k++){ // k is step
        double sum = 0;
        for (int m = 0; m < 26; m++){ // m is range
            sum += team_ci[(m+k) % 26] * expected_freq[m];
        }
        key_s.emplace_back(abs(sum-0.065));
    }
    auto minap = min_element(key_s.begin(), key_s.end());
    return minap - key_s.begin();
}

int main(int argc, char **argv){
    FILE *fp = fopen("./ciphertext", "r"); // first we open the ciphertext using readonly mod
    int c = 0; // store tmp char 
    // create a vector to store the count of each char and init it
    vector<int> c_text;

    // store the ciphertext to the vector c_text
    while((c = fgetc(fp)) != EOF){
        c_text.emplace_back(c-'A');
    }

    Cipher ci;
    ci.find_length(c_text); // this function is to get the length of key

    // then we try to get the key
    vector<int> ret;
    for (int i = 0; i < 6; i++){
        ret.emplace_back(ci.find_key(c_text, i));
        cout << "the " << i+1 << " position of key is " << ret[i] + 1 << endl;
    }

    for (int i = 0; i < 6; i++){
        cout << char (ret[i] + 'A');
    }
    cout << endl;

    for (int i = 0; i < c_text.size(); i++){
        c_text[i] -= ret[i%6];
        if (c_text[i] < 0){
            c_text[i] += 26; // maybe we will get a negative number 
        }
        cout << char (c_text[i] + 'A');
    }
    cout << endl;
    exit(0);
}

