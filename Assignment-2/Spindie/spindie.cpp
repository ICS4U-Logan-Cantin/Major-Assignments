#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include <list>
#include <cmath>
#include <map>

using namespace std;

typedef vector<long> vec_l;

/*
vector<long> spinnerValues;


bool SpindieRecursive(long target, int recursionLevel) {
    //cout << target << ", " << recursionLevel << endl;
    if (recursionLevel == 0) {
        if (binary_search(spinnerValues.begin(), spinnerValues.end(), target)) {
            return true;
        }
        else return false;
    }
    else {
        for (vector<long>::iterator iter = spinnerValues.begin(); iter != spinnerValues.end(); iter++) {
            int value = *iter;

            if (SpindieRecursive(target - value, recursionLevel - 1)) {
                return true;
            }

            double quotient = (double)target / (double)value;
            if (floor(quotient) != quotient) {
                continue;
            }

            else if (SpindieRecursive((long)quotient, recursionLevel - 1)) {
                return true;
            }
        }
        return false;
    }
}



void recursive() {
    int n;
    long temp;

    for (int CASE = 0; CASE < 10; CASE++) {
        scanf("%d", &n);

        for (int i = 0; i < n; i++) {
            scanf("%ld", &temp);
            spinnerValues.push_back(temp);
        }

        cout << "Finished all reading of values";
        cout.flush();

        vec_l targets;
        for (int i = 0; i < 5; i++) {
            scanf("%ld", &temp);
            bool answer = SpindieRecursive(temp, 2);
            cout << ((answer) ? "T" : "F");
            cout.flush();
        }

        cout << endl;

        spinnerValues.clear();
        targets.clear();
    }
}
*/

vector<pair<vector<int>::iterator, vector<int>::iterator> > sum2(int k, vector<int> v) {
    vector<int>::iterator f, s;
    f = v.begin();
    s = v.end();
    vector<pair<vector<int>::iterator, vector<int>::iterator> > values;

    // Making sure there are at least two values to check
    if (v.size() < 2) {
        return values;
    }

    // Decrementing s
    s--;

    while (true) {
        long sum = *f + *s;
        if (sum == k) {
            values.push_back(make_pair(f, s));
            f++;
        }
        else if (sum < k) {
            f++;
        }
        else {
            s--;
        }
        
        if (f == s) {
            return values;
        }
    }


}

bool sum2b(int k, vector<int> v) {
    vector<int>::iterator f, s;
    f = v.begin();
    s = v.end();

    // Making sure there are at least two values to check
    if (v.size() < 2) {
        return false;
    }

    // Decrementing s
    s--;

    while (true) {
        long sum = *f + *s;
        if (sum == k) {
            return true;
        }
        else if (sum < k) {
            f++;
        }
        else {
            s--;
        }
        
        if (f == s) {
            return false;
        }
    }


}


void naive() {
    int n;
    long temp;

    for (int CASE = 0; CASE < 10; CASE++) {

        set<long> spinnerValues;

        scanf("%d", &n);

        for (int i = 0; i < n; i++) {
            scanf("%ld", &temp);
            spinnerValues.insert(temp);
        }

        vector<pair<int, bool> > targets;
        for (int i = 0; i < 5; i++) {
            scanf("%ld", &temp);
            targets.push_back(make_pair(temp, false));
        }

        typedef set<long>::iterator vi;
        typedef vector<pair<int, bool> >::iterator vpi;
        for (vi i1 = spinnerValues.begin(); i1 != spinnerValues.end(); i1++){
            for (vi i2 = spinnerValues.begin(); i2 != spinnerValues.end(); i2++){
                for (vi i3 = spinnerValues.begin(); i3 != spinnerValues.end(); i3++){
                    for (vpi t = targets.begin(); t != targets.end(); t++) {
                        if ((*i1 + *i2) + *i3 == t->first ||
                            (*i1 * *i2) + *i3 == t->first ||
                            (*i1 + *i2) * *i3 == t->first ||
                            (*i1 * *i2) * *i3 == t->first)
                            t->second = true;
                    }

                }
            }
        }
        for (vpi i = targets.begin(); i != targets.end(); i++) {
            printf("%s", (i->second) ? "T" : "F");
        }
        printf("\n");

        spinnerValues.clear();
        targets.clear();
    }
}

int main() {
    naive();
}