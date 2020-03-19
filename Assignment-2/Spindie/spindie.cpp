#include <iostream>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

int main() {
    // Declaring variables
    int n;
    long temp;

    for (int CASE = 0; CASE < 10; CASE++) {

        // Using set for spinner values so there is no duplicates
        set<int> spinnerValues;

        // Reading spinner values
        scanf("%d", &n);
        for (int i = 0; i < n; i++) {
            scanf("%ld", &temp);
            spinnerValues.insert(temp);
        }

        // Reading targets
        vector<pair<long, bool> > targets;
        for (int i = 0; i < 5; i++) {
            scanf("%ld", &temp);
            targets.push_back(make_pair(temp, false));
        }

        // Looping through all permutations of the spinner values
        typedef set<int>::iterator vi;
        typedef vector<pair<long, bool> >::iterator vpi;
        for (vi i1 = spinnerValues.begin(); i1 != spinnerValues.end(); i1++){
            for (vi i2 = spinnerValues.begin(); i2 != spinnerValues.end(); i2++){
                for (vi i3 = spinnerValues.begin(); i3 != spinnerValues.end(); i3++){

                    // Calculating possible target values from this permutation
                    long one = (*i1 + *i2) + *i3;
                    long two = (*i1 * *i2) + *i3;
                    long three = (*i1 + *i2) * *i3;
                    long four = (*i1 * *i2) * *i3;

                    // Iterating through all the targets to see if there is a match
                    for (vpi t = targets.begin(); t != targets.end(); t++) {
                        if (one == t->first ||
                            two == t->first ||
                            three == t->first ||
                            four == t->first)

                            // There a match, so set this target to true
                            t->second = true;
                    }

                }
            }
        }

        // Print if each target is possible
        for (vpi i = targets.begin(); i != targets.end(); i++) {
            printf("%s", (i->second) ? "T" : "F");
        }
        printf("\n");

        // Cleanup
        spinnerValues.clear();
        targets.clear();
    }
}