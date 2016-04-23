#include <bits/stdc++.h>
#define INF 9999999
using namespace std;
int N;
vector <int> unroot[10001], root[10001];
int dp[10001][3];
//bool leaf[10001];
void dfs(int cur, int pa) // convert unrooted tree to rooted tree
{
    for (int i = 0 ; i < unroot[cur].size(); i++)
    {
        const int &next = unroot[cur][i];
        if (next!=pa)
        {
            //leaf[cur] = false;
            root[cur].push_back(next);
            dfs(next,cur);
        }
    }
}
int MVC(int cur, int stat)
{
    if (~dp[cur][stat]) return dp[cur][stat];
    int &ans = dp[cur][stat];
    if (stat == 0) // cur is not a server and parent is a server
    {
        ans = 0;
        for (int i = 0 ;i < root[cur].size(); i++)
            ans += MVC(root[cur][i], 1);
    }
    else if (stat == 1) // cur is not a server and parent is not a server
    {
        ans = INF;
        for (int i = 0; i < root[cur].size(); i++)
            ans = min(ans, MVC(cur,0) - MVC(root[cur][i], 1) + MVC(root[cur][i],2));
            /*
                This part is confusing as you can see. Notice that the only difference between
                state 1 and state 0 is that there is only one child server in state 1, while in
                state 0 you cannot have any child server. So simply take current node's state 0
                and then subtract child node's state 1(because this belongs to the original state 1)
                and plus state 2.
            */
    }
    else if (stat == 2) // cur is a server
    {
        ans = 1;
        for (int i = 0 ; i < root[cur].size(); i++)
            ans += min(MVC(root[cur][i],0),MVC(root[cur][i],2)); // server can connect to server
    }
    return ans;
}
int main()
{
    while(cin>>N)
    {
        if (N==-1) break;
        if (N==0) cin>>N;
        memset(dp,-1,sizeof dp);
        for (int i = 0 ; i <= N; i++)
        {
           //leaf[i] = true;
            unroot[i].clear();
            root[i].clear();
        }
        for (int i = 0, a, b; i < N-1; i++)
        {
            cin>>a>>b;
            unroot[a].push_back(b);
            unroot[b].push_back(a);
        }
        dfs(1,0);
        /*for (int i = 1; i <= N; i++)
        {
            cout<<i<<" : "<<root[i].size()<<" "<<leaf[i]<<endl;
            for (int j = 0; j < root[i].size(); j++)
                cout<<root[i][j]<<" ";
            cout<<endl;
        }*/
        int ans = min(MVC(1,2),MVC(1,1));
        cout<<ans<<endl;
    }
}
