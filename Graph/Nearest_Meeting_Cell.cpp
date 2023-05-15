#include <bits/stdc++.h>
using namespace std;
void dfs(int node, vector<int> adj[], vector<int> &dist, vector<int> &vis)
{

      for (auto it : adj[node])
      {
            if (!vis[it])
            {
                  vis[it] = 1;
                  dist[it] = dist[node] + 1;
                  dfs(it, adj, dist, vis);
            }
      }
}
int closestMeetingNode2(vector<int> &edges, int node1, int node2)
{

      int n = edges.size();

      vector<int> adj[n];

      for (int i = 0; i < n; i++)
      {
            if (edges[i] != -1)
                  adj[i].push_back(edges[i]);
      }

      int ans = -1;
      int minDist = INT_MAX;

      vector<int> dist1(n, 0), dist2(n, 0);

      vector<int> vis1(n, 0), vis2(n, 0);
      vis1[node1] = 1;
      vis2[node2] = 1;

      dfs(node1, adj, dist1, vis1);
      dfs(node2, adj, dist2, vis2);

      for (int currNode = 0; currNode < n; currNode++)
      {
            if (vis1[currNode] == 1 && vis2[currNode] == 1 && minDist > max(dist1[currNode], dist2[currNode]))
            {
                  minDist = max(dist1[currNode], dist2[currNode]);
                  ans = currNode;
            }
      }
      return ans;
}

// Second Approach
int closestMeetingNode1(vector<int>& edges, int node1, int node2) {
        while (edges[node1] >= 0 || edges[node2] >= 0) {
            int temp;
            if (edges[node1] >= 0) {
                temp = node1;
                node1 = edges[node1];
                edges[temp] = -3;
            }
            if (edges[node2] >= 0) {
                temp = node2;
                node2 = edges[node2];
                edges[temp] = -2;
            }
            if (edges[node1] == -2 && edges[node2] == -3) return min(node1, node2);
            if (edges[node1] == -2) return node1;
            if (edges[node2] == -3) return node2;
        }
        return node1 == node2 ? node1 : -1;
    }

int main()
{
      int n;
      cin >> n;
      vector<int> edges;

      for (int i = 0; i < n; i++)
      {
            int x;
            cin >> x;
            edges.push_back(x);
      }
      int node1, node2;
      cin >> node1 >> node2;

      cout << closestMeetingNode2(edges, node1, node2);
}


