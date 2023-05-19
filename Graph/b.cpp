#include <bits/stdc++.h>
using namespace std;

class Node
{
public:
      Node *parent = nullptr; // for keeping track of par
      int data;               // value for node
      vector<Node *> childs;  // childs of node
      Node(int val)
      {
            data = val;
      }
};
class NArrTree
{
public:
      Node *root = nullptr;
      stack<Node *> st; // to keep track of recent node of previous node
      unordered_map<Node *, int> lockCheck;
      unordered_map<Node *, int> checkforDescendMap;

      NArrTree(int val)
      {
            root = new Node(val);
            st.push(root);
      }

      Node *insertNode(int val)
      {
            if (val == -1 && !st.empty())
            {
                  st.pop();
                  return nullptr;
            }
            else
            {
                  Node *child = new Node(val);

                  if (st.size() > 0)
                  {
                        Node *par = st.top();
                        child->parent = par; //

                        par->childs.push_back(child);
                  }
                  st.push(child);

                  return child;
            }
      }

      void printTree()
      {
            string levelOderTraversal = "This is levelOderTraversal for only you ";
            queue<Node *> q;
            q.push(root);

            while (!q.empty())
            {
                  auto it = q.front();
                  q.pop();
                  levelOderTraversal += to_string(it->data) + " ";

                  for (auto child : it->childs)
                  {
                        q.push(child);
                  }
            }

            cout << levelOderTraversal << endl;
      }

      bool isLock(Node *node)
      {
            if(lockCheck.find(node) == lockCheck.end())
                  return false;
            return true;

            // Time Complexity O(1);
      }

      string lock(Node *node)
      {
            // Now first we have to check if all descendeds and all ancestors are locked or not
            bool checkAncestors = true;
            bool checkDescendeds = true;

            // lets check first for ancestors
            Node *temp = node;
            // cout<<temp->data<<endl;
            while (temp != nullptr)
            {
                  if (isLock(temp))
                  {
                        checkAncestors = false;
                        break;
                  }
                  else
                  {
                        temp = temp->parent;
                  }
            }

            // lets check for descendes
            if (checkforDescendMap.find(node) != checkforDescendMap.end())
            {
                  checkDescendeds = false;
            }

            if (checkAncestors && checkDescendeds)
            {
                  // We can lock the node so here we will update the neccessary information
                  lockCheck[node]++;

                  // we will also inform that they will not able to lock in future beacuse of their descendes
                  temp = node;
                  while (temp != nullptr)
                  {
                        checkforDescendMap[temp]++;
                        temp = temp->parent;
                  }

                  // Now we will return a message that we locked successfully
                  return "Locked Successafully";
            }
            else
            {
                  return "Not Able to Lock Sorry";
            }

            // Time Complexity

            // O(logN) + O(logN);
      }
};

int main()
{
      vector<int> arr = {10, 20, 50, -1, 60, -1, -1, 30, 70, -1, 80, 110, -1, 100, -1, -1, 90, -1, -1, 40, 100, -1, -1, -1};
      NArrTree *head = nullptr;

      unordered_map<int, Node *> mp;

      for (int i = 0; i < arr.size(); i++)
      {
            if (i == 0 && arr[i] != -1)
            {
                  head = new NArrTree(arr[i]);
                  mp[arr[i]] = head->root;
            }
            else
            {
                  Node *t = head->insertNode(arr[i]);
                  if (t != nullptr)
                        mp[arr[i]] = t;
            }
      }

      cout << head->isLock(mp[30]) << endl;
      cout << head->lock(mp[30]) << endl;
      cout << head->lock(mp[80]) << endl;
      cout << head->isLock(mp[80]) << endl;
      // cout << mp[30] << endl;
}