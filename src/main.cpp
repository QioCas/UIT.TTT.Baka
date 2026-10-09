#include "bits/stdc++.h"
using namespace std;

#include "template/debug.h"

void subset(int x) {
    for(int ms = x; ms > 0; ms = (ms - 1) & x) {
        // ms is the subset
        debug(bitset<10>(ms));
    }
    // not include empty.
}

int main() {
    subset(1000);
}