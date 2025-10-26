#include<bits/stdc++.h>
#include "../../testlib.h"

#define REP(i, n) for (int (i) = 0; (i) < (n); (i)++)
#define st first
#define nd second
#define pii pair<int, int>

using namespace std;

int testCaseNumber;

void fail(const string &message) {
	quitf(_wa, message.c_str());
}

void failIf(bool failCondition, const string &message) {
    if(failCondition)
        fail(message);
}

void failAssert(bool assertCondition, const string &message) {
    failIf(!assertCondition, message);
}

auto YES = "TAK";
auto NO = "NIE";

void verifyYesNo(const string& solStr, const string& outStr) {
    failIf(outStr != YES && outStr != NO, "No TAK/NIE in the contestant output");
    failIf(solStr != YES && solStr != NO, "Unexpected error: No TAK/NIE in the model output");

    failIf(solStr == YES && outStr == NO, "Contestant didn't find the solution.");
    failIf(solStr == NO && outStr == YES, "Contestant claims to have a found a solution on a NO input");
}

int readInt(InStream& in, bool eol = false) {
    int u = in.readInt();
    return u;
}

int readIntAndDecrement(InStream& in, bool eol = false) {
    int u = readInt(in, eol);
    return u - 1;
}

string readString(InStream& sc, int len) {
    string res = sc.readWord();
	failIf(res.length() != len, "wrong length");
    return res;
}

class Solution {
public:

	InStream& in;
    InStream& sol;
    InStream& out;
    string SOL_ANS, SOL_S;
    string OUT_ANS, OUT_S;

    int n, k;
    vector<pii> meet;
    vector<bool> shouldDie;
    vector<bool> alive;

    bool verifyResult() {
        for (int i = 0; i < n; i++)
            if(shouldDie[i] && alive[i])
                return false;
        return true;
    }

    void kill(int i) {
        auto [winner, loser] = meet[i];
        if(!alive[winner]) {
            return; // The encounter doesn't happen, so doesn't matter if the letter is T or F
        }

        alive[loser] = false;
    }

    Solution(InStream &in, InStream &sol, InStream &out) : in(in), sol(sol), out(out) {
        n = readInt(in);
        k = readInt(in, true);

        meet.resize(k);
        shouldDie.resize(n, false);
        alive.resize(n, true);

        REP(i, k) {
            int a = readIntAndDecrement(in);
            int b = readIntAndDecrement(in, true);
            meet[i] = make_pair(a, b);
        }

        int deaths;
        deaths = readInt(in, true);
        REP(i, deaths)
            shouldDie[readIntAndDecrement(in, (i + 1 == deaths))] = true;
    }


    void solput(){
        SOL_ANS = readString(sol, 3);

        if(SOL_ANS == YES)
            SOL_S = readString(sol, k);
    }

    void output() {
        OUT_ANS = readString(out, 3);

        if(OUT_ANS == YES)
            OUT_S = readString(out, k);
    }

    void check() {
        verifyYesNo(SOL_ANS, OUT_ANS);
        if(OUT_ANS == NO)
            return;

        failAssert(OUT_S.length() == k, "Incorrect length of the output string");
        for (int i = 0; i < k; i++) {
            auto c = OUT_S[i];
            if(c == 'T')
                kill(i);
            else
                failAssert(c == 'N', "Output string contains a character different than T and N.");
        }

        failAssert(verifyResult(), "Some poeple who should be dead are alive.");
    }
};


int main(int argc, char** argv){
	registerTestlibCmd(argc, argv);

    int T = inf.readInt();

    for(testCaseNumber = 0; testCaseNumber < T; testCaseNumber++){
        setTestCase(testCaseNumber + 1);
		Solution s(inf, ans, ouf);
        s.solput();
        s.output();
        s.check();
    }
	quitf(_ok, "correct");

	return 0;
}
