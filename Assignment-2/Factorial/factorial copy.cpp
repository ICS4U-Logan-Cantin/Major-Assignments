#include <vector>
#include <map>
#include <unordered_map>
#include <iostream>
#include <array>
#include <set>
#include <unordered_set>

#include <chrono>
#include <thread>

using namespace std;

typedef long long ll;
typedef unsigned long long ull;

map<ull, vector<ull> > hasht;

inline bool is_factor(ull number, ull factor) {
    return number / factor == (long double)number / (long double)factor;
}

/*
void prime_factorize(vector<ull> &v, ull n) {
    assert(n > 1);
    bool prime = true;
    for (ull i = 2; i <= n/2; i++) {
        if (is_factor(n, i)) {
            prime = false;
            v.push_back(i);
            prime_factorize(v, n / i);
            break;
        }
    }
    if (prime) {
        v.push_back(n);
    }
}

vector<ull> prime_factorize(ull n) {
    vector<ull> v;
    prime_factorize(v, n);
    return v;
}*/

vector<ull> prime_factorize_dp(ull n) {
    //this_thread::sleep_for(chrono::duration<int, milli>(100));
    cout << "Prime factorize " << n << endl;
    auto iter = hasht.find(n);
    if (iter == hasht.end()) {
        //cout << "non hash table" << endl; 
        vector<ull> v;
        for (ull i = 2; i <= n/2; i++) {
            if (is_factor(n, i)) {
                //prime = false;
                v = prime_factorize_dp(n / i);
                v.push_back(i);
                hasht[n] = v;
                return v;
            }
        }
        
        v.push_back(n);
        hasht[n] = v;
        return v;
    }
    else {
        //cout << "Hashtable! " << n  << ' ' << hasht.size() << endl;
        return hasht[n];
    }
}

set<ull> primes;

void prime_factorize_one_pass(ull n, unordered_map<ull, ull> &m) {
    
    if (primes.find(n) != primes.end()) {
        m[n] += 1;
        return;
    }

    for (ull i = 2; i <= n/2; i++) {
        if (is_factor(n, i)) {
            primes.insert(i);
            m[i] += 1;
            prime_factorize_one_pass(n / i, m);
            return;
        }
    }
    
    primes.insert(n);
    m[n] += 1;
    return;
}

bool factor_checker(unordered_map<ull, ull> &one, const unordered_map<ull, ull> &two) {
    for (auto p : one) {
        if (two.find(p.first) == two.end() || p.second > two.at(p.first)) {
            return false;
        }
    }
    return true;
}

void pf_to_table(ull n, unordered_map<ull, ull> &m, ull multiplier = 1) {
    for (ull f : prime_factorize_dp(n)) {
        if (m.find(f) == m.end()) {
            m.insert(make_pair(f, multiplier));
        }
        else {
            m.at(f) += multiplier;
        }
    }
}


int main() {
    
    for (int CASENUM = 0; CASENUM < 10; CASENUM++) {
        ull k, m;
        cin >> k >> m;

        unordered_map<ull, ull> k_map;
        pf_to_table(k, k_map, m);

        unordered_map<ull, ull> nfac_map;
        ull n = 1;
        while (!factor_checker(k_map, nfac_map)) {
            n++;
            pf_to_table(n, nfac_map);
        }
        cout << n << endl;

    }
}
