/** Source Code
 *
 * Problem: 2761		User: wangchangbao
 * Memory: 3984K		Time: 2829MS
 * Language: C++		Result: Accepted
 * Solution: Treap
 */

#include <iostream>
#include <cstdio>
#include <string>
#include <cstring>
#include <algorithm>
#include <set>
#include <map>
#include <vector>
#include <stack>
#include <cmath>
using namespace std;
typedef long long LL;
#define N 200005
#define M 200005
int n , m , a[M];
template <class T> struct Treap {
    int nodecnt , prior[M];
    int cnt[M] , size[M] , c[M][2];
    int root;
    T key[M];
    void clear() {
        root = nodecnt = 1;
        prior[0] = -1 << 30;
        c[0][0] = c[0][1] = 0;
        key[0] = cnt[0] = size[0] = 0;
    }
    Treap () {
        clear();
    }
    inline void pushup(int p) {
        size[p] = size[c[p][0]] + size[c[p][1]] + cnt[p];
    }
    inline void rotate (int& x , int t) {
        int y = c[x][t];
        c[x][t] = c[y][!t] , c[y][!t] = x;
        pushup(x) , pushup(y) , x = y;
    }
    inline void newnode(int& p , T w) {
        p = nodecnt ++;
        key[p] = w , cnt[p] = size[p] = 1;
        prior[p] = rand() << 15 | rand(), c[p][0] = c[p][1] = 0;
    }
    void insert(int& p , T w) {
        if (!p) {
            newnode(p , w);
            return;
        }
        if (key[p] == w)
            ++ cnt[p];
        else {
            int t = key[p] < w;
            insert(c[p][t] , w);
            if (prior[c[p][t]] > prior[p])
                rotate(p , t);
        }
        pushup(p);
    }
    void erase(int& p , T w) {
        if (!p) return;
        if (key[p] == w) {
            if (cnt[p] == 1) {
                if (!c[p][0] && !c[p][1])
                    p = 0;
                else {
                    rotate(p , prior[c[p][0]] < prior[c[p][1]]);
                    erase(p , w);
                }
            } else
                -- cnt[p];
        } else
            erase(c[p][key[p] < w] , w);
        pushup(p);
    }
    T getKth(int p , int K) {
        if (K <= size[c[p][0]])
            return getKth(c[p][0] , K);
        K -= size[c[p][0]] + cnt[p];
        if (K <= 0) return key[p];
        return getKth(c[p][1] , K);
    }
    T lower_bound(int p , T w) {
        if (!p) return 1 << 30;
        if (key[p] >= w)
            return min(lower_bound(c[p][0] , w) , key[p]);
        else
            return lower_bound(c[p][1] , w);
    }
    T range(int p , int l , int r) {
        if (!p || l > r) return 0;
        if (l <= key[p] && key[p] <= r) {
            int ans = key[p];
            return ans;
        }
        if (r < key[p])
            return range(c[p][0] , l , r);
        else
            return range(c[p][1] , l , r);
    }
    void merge(int& p , int& q) {
        if (!p) return;
        merge(c[p][0] , q);
        merge(c[p][1] , q);
        insert(q , key[p]);
        erase(p , key[p]);
    }
};
Treap<int> T;
struct query{
    int id, l, r, k;
    query(int _id, int _l, int _r, int _k):id(_id),l(_l),r(_r),k(_k){}

};
    bool operator <(const query &q, const query &p) {
        if (q.l != p.l) return q.l < p.l;
        return q.r < p.r;
    }

vector<query> q;
int ans[M];

void work() {
    scanf("%d%d",&n,&m);
    T.clear();
    for (int i = 1 ; i <= n ; ++ i) {
        scanf("%d" , &a[i]);
    }
    for (int i = 0; i < m; ++i) {
        int l, r, k;
        scanf("%d%d%d", &l, &r, &k);
        q.push_back(query(i, l, r, k));
    }
    sort(q.begin(), q.end());
    int b = 1, e = 0;
    for (int i = 0; i < q.size(); ++i) {
        while(e <= q[i].r) T.insert(T.root, a[e++]);
        while(b < q[i].l) T.erase(T.root, a[b++]);
        ans[q[i].id] = T.getKth(T.root, q[i].k);
    }
    for (int i = 0; i < m; ++i) {
        printf("%d\n", ans[i]);
    }
}

int main()
{
//    freopen("in.txt" , "r" , stdin);
//    freopen("2.txt" , "w" , stdout);
        work();
    return 0;
}
