#include <string>

#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    string source = inf.readString();
    int sourceLen = source.length();
    string target = inf.readString();
    int targetLen = target.length();

    int left = ouf.readInt();
    int right = ouf.readInt();
    int right2 = right - (sourceLen - targetLen);

    if (left <= 0) {
        quit(_wa, "Left position is less than or equal to zero, specifically " + toString(left));
    }

    if (right > sourceLen) {
        quit(_wa, "Right position (" + toString(right) + ") is greater than string length (" +
                      toString(sourceLen) + ")");
    }

    if (right < left) {
        quit(_wa,
             "Right position is less than left position (" + toString(right) + " < " + toString(left) + ")");
    }

    if (right2 < left) {
        quit(_wa, "Too many digits that were not replaced by sum");
    }

    for (int i = 0; i < left - 1; i++) {
        if (source[i] != target[i]) {
            quit(_wa, "Result character at position " + toString(i + 1) + " does not match expected: " +
                          string(1, source[i]) + " <> " + string(1, target[i]) +
                          ", this position is before the digits that were replaced by sum");
        }
    }

    for (int i = right; i < sourceLen; i++) {
        int j = targetLen - (sourceLen - i);
        if (source[i] != target[j]) {
            quit(_wa, "Result character at position " + toString(j + 1) + " does not match expected: " +
                          string(1, source[i]) + " <> " + string(1, target[j]) +
                          ", this position is after the digits that were replaced by sum");
        }
    }

    int sum = 0;
    for (int i = left - 1; i < right; i++) {
        sum += source[i] - '0';
    }

    string sumStr = toString(sum);

    if (right2 - left + 1 != (int)sumStr.length()) {
        quit(_wa, "After replacement, got a number of different length");
    }

    for (int i = 0; i < (int)sumStr.length(); i++) {
        if (target[left + i - 1] != sumStr[i]) {
            quit(_wa, "Result character at position " + toString(left + i) +
                          " does not match expected: " + string(1, target[left + i - 1]) + " <> " +
                          string(1, sumStr[i]) + ", and this is one of the digits obtained as sum");
        }
    }

    quit(_ok, "OK, from " + toString(sourceLen) + " digits got " + toString(targetLen));

    return 0;
}
