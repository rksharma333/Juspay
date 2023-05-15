#include <bits/stdc++.h>
using namespace std;
int mx = -1;
void dfs(int node, vector<int> adj[], vector<int> &vis, vector<int> &pathvis)
{
      for (auto it : adj[node])
      {
            if (vis[it] && pathvis[it] > 0)
            {
                  mx = max(mx, pathvis[node] - pathvis[it] + 1);
            }
            else if (vis[it] == 0)
            {
                  pathvis[it] = pathvis[node] + 1;
                  vis[it] = 1;
                  dfs(it, adj, vis, pathvis);
                  pathvis[it] = 0;
            }
      }
}
int longestCycle(vector<int> &edges)
{

      int n = edges.size();

      vector<int> adj[n];

      for (int i = 0; i < n; i++)
      {
            if (edges[i] != -1)
                  adj[i].push_back(edges[i]);
      }

      vector<int> pathvis(n, 0);
      vector<int> vis(n, 0);

      for (int i = 0; i < n; i++)
      {
            if (!vis[i])
            {
                  vis[i] = 1;
                  pathvis[i] = 1;
                  dfs(i, adj, vis, pathvis);
                  pathvis[i] = 0;
            }
      }

      return mx;
}

int main()
{
      int n;
      cin >> n;

      vector<int> arr;
      for (int i = 0; i < n; i++)
      {
            int edge;
            cin >> edge;
            arr.push_back(edge);
      }

      cout << longestCycle(arr) << endl;
}