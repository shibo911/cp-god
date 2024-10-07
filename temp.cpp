#include<bits/stdc++.h>
#define ll long long
#define pb push_back
#define fr(a,b) for(ll i = a; i < b; i++)
#define mod 1000000007
#define inf (1LL<<60)
#define all(x) (x).begin(), (x).end()
#define prDouble(x) cout << fixed << setprecision(10) << x
#define triplet pair<ll,pair<ll,ll>>
#define fast_io ios_base::sync_with_stdio(false);cin.tie(NULL)
using namespace std;

struct node
{
    ll sum;
    ll setAll;
    ll increment;
    bool setAllValid;
    node()
    {
       sum = 0;
       setAllValid = 0;
       increment = 0;
    }
    void Reset()
    {
       setAllValid = increment = 0;
    }
};

class segtree
{
    int range;
    vector<node> tree;
public:
    void build(vector<int>& v)
    {
        range = v.size();
        tree.assign(4*range, node());
        build_recur(v, 0, range-1, 0);
    }
    void build_recur(vector<int>& v, int l, int r, int node_no)
    {
        if(l == r){
            if(l < v.size())
                tree[node_no].sum = v[l];
            else tree[node_no].sum = 0;
            return;
        }
        int mid = (l+r)/2;
        build_recur(v, l, mid, 2*node_no + 1);
        build_recur(v, mid + 1, r, 2*node_no + 2);
        tree[node_no].sum = tree[2*node_no + 1].sum + tree[2*node_no + 2].sum;
    }
    ll range_query(int L, int R)
    {
        return range_query_recur(0, 0, range - 1, L, R);
    }

    void incUpdate_recur(int node, int l, int r, int& L, int& R, int& X)
    {
        if(r < L || R < l || l >= range)
            return;
        if(L <= l && R >= r)
        {
            tree[node].increment += X;
            return;
        }
        applyAggr(node,l,r);
        int mid = (l+r)/2;
        incUpdate_recur(2*node+1,l,mid,L,R,X);
        incUpdate_recur(2*node+2,mid+1,r,L,R,X);
        applyAggr(2*node+1, l, mid);
        applyAggr(2*node+2, mid+1, r);
        tree[node].sum = tree[2*node+1].sum + tree[2*node+2].sum;
    }

    void incUpdate(int L, int R, int X)
    {
        incUpdate_recur(0,0,range-1,L,R,X);
    }

    void setUpdate_recur(int node, int l, int r, int& L, int& R, int& X)
    {
        if(r < L || R < l || l >= range)
            return;
        if(L <= l && R >= r)
        {
            tree[node].setAllValid = 1;
            tree[node].setAll = X;
            tree[node].increment = 0;
            return;
        }
        applyAggr(node,l,r);
        int mid = (l+r)/2;
        setUpdate_recur(2*node+1,l,mid,L,R,X);
        setUpdate_recur(2*node+2,mid+1,r,L,R,X);
        applyAggr(2*node+1, l, mid);
        applyAggr(2*node+2, mid+1, r);
        tree[node].sum = tree[2*node+1].sum + tree[2*node+2].sum;
    }

    void setUpdate(int L, int R, int X)
    {
        setUpdate_recur(0,0,range-1,L,R,X);
    }

    void compose(int par, int child)
    {
        if(tree[par].setAllValid){
            tree[child].setAllValid = 1;
            tree[child].setAll = tree[par].setAll;
            tree[child].increment = tree[par].increment;
        }
        else tree[child].increment += tree[par].increment;
    }

    void applyAggr(int node, int l, int r)
    {
        if(tree[node].setAllValid)
            tree[node].sum = (r-l+1)*tree[node].setAll;

        tree[node].sum += (r-l+1)*tree[node].increment;

        if(l != r){
            compose(node, 2*node + 1);
            compose(node, 2*node + 2);
        }

        tree[node].Reset();
    }

    ll range_query_recur(int node, int l, int r, int& L, int& R)
    {
        if(r < L || R < l || l >= range)
            return 0;
        applyAggr(node, l, r);
        if(L <= l && R >= r)
            return tree[node].sum;
        int mid = (l+r)/2;
        return range_query_recur(2*node + 1, l, mid, L, R) + range_query_recur(2*node + 2, mid+1, r, L, R);
    }
};

int main() {
   fast_io;
   int n,q;
   cin >> n >> q;

   vector<int> v(n);
   for(int i = 0; i < n; i++)
        cin >> v[i];

   segtree sg;
   sg.build(v);

   while(q--)
   {
        int t;
        cin >> t;
        if(t == 1){
            int a,b,x;
            cin >> a >> b >> x;
            sg.incUpdate(a-1,b-1,x);
        }
        else if(t == 2){
            int a,b,x;
            cin >> a >> b >> x;
            sg.setUpdate(a-1,b-1,x);
        }
        else {
            int a,b;
            cin >> a >> b;
            cout << sg.range_query(a-1,b-1) <<'\n';
        }
   }
   return 0;
}
