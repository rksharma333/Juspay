#include <bits/stdc++.h>
using namespace std;

// Code for BFS

void bfs(int n, int node, vector<int> adj[], vector<int> &ans)
{
      vector<int> vis(n, 0);
      queue<int> q;
      q.push(node);
      vis[node] = 1;

      while (!q.empty())
      {
            int it = q.front();
            q.pop();
            ans.push_back(it);

            for (auto child : adj[it])
            {
                  if (!vis[child])
                  {
                        vis[child] = 1;
                        q.push(child);
                  }
            }
      }
}

int main()
{
      int n;
      cin >> n;

      vector<int> adj[n];
      for (int i = 0; i < n; i++)
      {
            int e;
            cin >> e;

            if (e != -1)
                  adj[i].push_back(e);
      }

      int u, v;
      cin >> u >> v;

      vector<int> path1, path2;

      bfs(n, u, adj, path1);
      bfs(n, v, adj, path2);

      for (auto it : path1)
            cout << it << " ";
      cout << endl;

      for (auto it : path2)
            cout << it << " ";
}