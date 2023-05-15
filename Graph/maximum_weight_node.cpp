#include <bits/stdc++.h>
using namespace std;

int main()
{

      int n;
      cin >> n;

      int arr[n];

      int ans = INT_MIN;
      int result = -1;

      unordered_map<int, int> mp;
      for (int i = 0; i < n; i++)
      {
            int e;
            cin >> e;

            if (e != -1)
            {
                  mp[e]++;
                  if (mp[e] > ans)
                  {
                        ans = mp[e];
                        result = e;
                  }
            }
      }
      cout << result << endl;
}
