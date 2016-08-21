// *** ADDED BY HEADER FIXUP ***
#include <istream>
// *** END ***
#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <vector>
#include <map>
#include <algorithm>
#include <cassert>
#include <cstdlib>
#include <cstring>

using namespace std;
typedef pair<int,int> P;
const int M = 50000;

int a[M];
int b[M];
int n,m,L;
int check(int k) {
    int s = 0;
    while(a[s] >= k && s < n) ++s;
    if (s >= n) return true;
    for (int p = 0; p < L; ++p) {
        int t = (s-p+n) % n;
        int avl = m;
        for (int i = 0; i < n; ++i)
        b[i] = a[(t+i) % n];
        for (int j = 0; j < n; ) {
            if (b[j] >= k){
                j++;
                continue;
            }
            avl--;
            j += L;
        }
        if (avl >= 0) return true;
    }
    return false;
}

int main() {
    freopen("in.txt", "r", stdin);
    cin >> n >> m >> L;
    L = min(n, L);
    for (int i = 0; i < n; ++i) {
        scanf("%d", a+i);
    }
    int l = *min_element(a, a+n), r = *max_element(a, a+n);
    int ans = 0;
    while (l <= r) {
        int ms = (l+r) >> 1;
        if (check(ms)) ans = ms, l = ms + 1;
        else r = ms - 1;
    }
    cout << ans << std::endl;
    return 0;
}
