#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include <list>
#include <cmath>
#include <map>

using namespace std;

typedef vector<long> vec_l;



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
                    int one = (*i1 + *i2) + *i3;
                    int two = (*i1 * *i2) + *i3;
                    int three = (*i1 + *i2) * *i3;
                    int four = (*i1 * *i2) * *i3;
                    for (vpi t = targets.begin(); t != targets.end(); t++) {
                        if (one == t->first ||
                            two == t->first ||
                            three == t->first ||
                            four == t->first) {
                            
                            t->second = true;
                        }
                            
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