#include <bits/stdc++.h>
using namespace std;

void showFile(const char* name) {
    ifstream file(name);
    cout << file.rdbuf() << '\n';
}

int stressTest() {
    if (system("g++ main.cpp -DSTRESS -O2 -std=c++17 -o stress_main.exe") != 0 ||
        system("g++ brute.cpp -DSTRESS -O2 -std=c++17 -o stress_brute.exe") != 0 ||
        system("g++ gen.cpp -DSTRESS -O2 -std=c++17 -o stress_gen.exe") != 0) {
        cerr << "Compilation failed.\n";
        return 1;
    }

    for (int i = 1; i <= 1000; ++i) {
        if (system(".\\stress_gen.exe > test.in") != 0 ||
            system(".\\stress_main.exe < test.in > test.out") != 0 ||
            system(".\\stress_brute.exe < test.in > test.ans") != 0) {
            cerr << "Program failed on test " << i << ".\n";
            return 1;
        }

        if (system("fc /B test.out test.ans > nul") != 0) {
            cout << "WA on test " << i << ":" << endl;
            cout << "Input:" << endl;
            showFile("test.in");
            cout << "Your answer:" << endl;
            showFile("test.out");
            cout << "Correct answer:" << endl;
            showFile("test.ans");
            return 1;
        }
        cout << "Passed test: " << i << endl;
    }
    return 0;
}

int main() {
    int result = stressTest();
    remove("stress_main.exe");
    remove("stress_brute.exe");
    remove("stress_gen.exe");
    return result;
}
