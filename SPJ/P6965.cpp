#include "testlib.h"
#include <vector>
#include <string>
#include <algorithm>
#include <cstdio>
#include <cstring>

using namespace std;

void wa(const string &comment) {
    quitf(_wa, "%s", comment.c_str());
}

int main(int argc, char *argv[]) {
    registerTestlibCmd(argc, argv);

    int n = inf.readInt();
    string jY = ans.readToken();
    string pY = ouf.readToken();

    if (pY != "YES" && pY != "NO") {
        wa("YES or NO expected on the first line");
    }

    vector<string> words(n);
    vector<string> inputWords(n);

    for (int i = 0; i < n; ++i) {
        inputWords[i] = inf.readToken();
    }

    if (pY == "YES") {
        for (int i = 0; i < n; ++i) {
            words[i] = ouf.readToken();
        }

        for (int i = 0; i < n; ++i) {
            string iWord = inputWords[i];
            int length = iWord.length();
            string pWord = words[i];
            if (pWord.length() != length) {
                wa(format("Word of length %d expected, but of length %ld found at line %d",
                    length, pWord.length(), i + 1));
            }
            for (int j = 0; j < length; ++j) {
                if (pWord[j] != '0' && pWord[j] != '1') {
                    wa(format("Invalid character at position %d in line %d", j + 1, i + 1));
                }
                if (pWord[j] != iWord[j] && iWord[j] != '?') {
                    wa(format("Code word doesn't correspond to input code word at line %d", i + 1));
                }
            }
        }

        sort(words.begin(), words.end());

        for (int i = 0; i + 1 < n; ++i) {
            if (words[i + 1].find(words[i]) == 0) { 
                wa("Participant's code is not prefix code");
            }
        }

        if (jY == "NO") {
            quitf(_fail, "Participant found solution");
        }
    } else {
        if (jY == "YES") {
            wa("No solution found, but it exists");
        } else {
            quitf(_ok, "No solution");
        }
    }

    quitf(_ok, "%d lines", n);
}
