#include <bits/stdc++.h>
using namespace std;

class StreamCipher {
private:
    vector<int> state;  
    int index1, index2; 

    void swap(int& a, int& b) {
        int temp = a;
        a = b;
        b = temp;
    }

public:
    StreamCipher(vector<int>& key) {
        state.resize(256);
        for (int i = 0; i < 256; i++) {
            state[i] = i;
        }

        int index2 = 0;
        for (int index1 = 0; index1 < 256; index1++) {
            index2 = (index2 + state[index1] + key[index1 % key.size()]) % 256;
            swap(state[index1], state[index2]);
        }

        index1 = 0;
        index2 = 0;
    }

    int NextByte() {
        index1 = (index1 + 1) % 256;
        index2 = (index2 + state[index1]) % 256;
        swap(state[index1], state[index2]);
        return state[(state[index1] + state[index2]) % 256];
    }
};

int main() {
    vector<int> key = {1, 2, 3, 4, 5, 6};
    StreamCipher cipher(key);  
    cout << "First 20 elements of the key stream:" << endl;
    for (int k = 0; k < 20; k++) {
        cout << cipher.NextByte() << " ";
    }
    cout << endl;
    return 0;
}
