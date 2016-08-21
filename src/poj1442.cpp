// *** ADDED BY HEADER FIXUP ***
#include <istream>
// *** END ***
/**
 * Problem: 1442		User: wangchangbao
 * Memory: 2288K		Time: 1000MS
 * Language: C++		Result: Accepted
 * Solution: BIT
 */

#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <vector>
#include <map>
#include <algorithm>
#include <cassert>
using namespace std;
typedef pair<int,int> P;
const int M = 80000;
vector<P> op;
vector<int> val, seq;
vector<int> get;
map<int, int> mp;
int C[M];
void add(int x, int dx) {
    for (++x; x < M; x += x&(-x))
        C[x] += dx;
}
int getKth(int k) {
    assert(k > 0);
    int x = 0;
    for(int i = 16; i >= 0; --i)
    if (x + (1<<i) < M && C[x + (1<<i)] < k) {
        x += 1 << i;
        k -= C[x];
    }
    return x + 1;
}

int main(){
//    freopen("in.txt", "r", stdin);
    int n, m;
    cin >> m >> n;
    for (int i = 0; i < m; ++i) {
        int x;
        scanf("%d", &x);
        seq.push_back(x);
        val.push_back(x);
    }
    for (int i = 0; i < n; ++i) {
        int x;
        scanf("%d", &x);
        get.push_back(x);
    }
    sort(val.begin(), val.end());
    val.erase(unique(val.begin(), val.end()), val.end());
    for (int i = 0; i < (int)val.size(); ++i) {
        mp[val[i]] = i;
    }
    int ask = 0;
    for (int i = 0; i < m; ++i) {
        add(mp[seq[i]], 1);
        while(ask < (int)get.size() && i + 1 == get[ask]) {
            printf("%d\n", val[getKth(++ask)-1]);
        }
    }

    return 0;
}
