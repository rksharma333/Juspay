#include <bits/stdc++.h>
using namespace std;

struct Node
{
      /*
      This node will be storing the following details
      1.- value of node
      2.- Address of parent of node
      3. - list of childs
      4. - count of locked descendants(initialy 0)
      5. - uid that has locked the node(if not locked then -1)
      */

      string data;
      Node *par = nullptr;
      vector<Node *> childs;
      int count = 0;
      int uid = -1;

      Node(string value)
      {
            data = value;
      }
};

// tree
class Tree
{
      /*
      Details for Tree class
      1.- Root node
      2.- unordered map for mapping node data with their node address
      3.- An insert function to insert node in thir parent
      4.- Function for traversing the tree
      5.- islockedAnchestors function for checking if there any anchestor is locked or not
      6.- updateAnchestors function for updating count value (+1, node is locked, -1 node is unlocked in descendents)
      7.- lock function
      8.- unlock function
      9.- unlock function
      */

public:
      Node *root = nullptr;
      unordered_map<string, Node *> nodeAdress;
      unordered_map<Node *, vector<pair<Node *, int>>> lockedDescendends;

      void insert(int n, int m, vector<string> &arr)
      {
            root = new Node(arr[0]);
            nodeAdress[arr[0]] = root;

            queue<Node *> q;
            q.push(root);

            int cnt = m;

            for (int i = 1; i < n; i++)
            {
                  string val = arr[i];
                  Node *node = new Node(val);
                  nodeAdress[val] = node;

                  node->par = q.front();
                  q.front()->childs.push_back(node);
                  q.push(node);

                  cnt--;
                  if (cnt == 0)
                  {
                        q.pop();
                        cnt = m;
                  }
            }
      }

      void printTree()
      {
            queue<Node *> q;
            q.push(root);

            while (!q.empty())
            {
                  Node *node = q.front();
                  q.pop();

                  cout << node->data << " ";

                  for (auto it : node->childs)
                  {
                        q.push(it);
                  }
            }

            cout << endl;
      }

      //----------------------Lock function & it functions-------------------

      bool islockedAnchestors(Node *node)
      {
            Node *temp = node->par;
            while (temp != nullptr)
            {
                  if (node->uid != -1)
                        return true;
                  temp = temp->par;
            }
            return false;
      }

      void updateAnchestors(Node *node, int val)
      {
            Node *temp = node->par;

            while (temp != nullptr)
            {
                  temp->count += val;
                  temp = temp->par;
            }
      }
      bool lock(Node *node, int uid)
      {
            /*
                I have to check for three condition before locking the node
                1. - if the node if locked or not
                2. - if any decendends is locked or no
                3. - if any anchestors is locked or not
            */

            if (node->uid != -1)
                  return false;
            if (islockedAnchestors(node))
                  return false;
            if (node->count > 0)
                  return false;

            node->uid = uid;

            updateAnchestors(node, 1);
            return true;
      }

      // TC - O(LogN) + O(LogN)

      //----------------------------Lock function ends here------------------

      //--------------------------unlock function start---------------------------
      bool unlock(Node *node, int uid)
      {

            if (node->uid == uid)
            {

                  node->uid = -1;
                  updateAnchestors(node, -1);
                  //cout << node->data << " " << node->uid << endl;
                  return true;
            }

            return false;
      }
      // TC - O(LogN)
      //-----------------------------------------unlock function end here----------
      bool checkDescends(Node *node, int uid)
      {
            /*
            for checking if there is any child that is locked by any other uid
            */
            bool flag = false;
            for (auto child : node->childs)
            {
                  //cout<<child->data<<" "<<child->uid<<endl;
                  if (child->uid != -1 && child->uid != uid)
                        return true;
                  flag |= checkDescends(child, uid);
            }
            return flag;
      }
      void upadateDescendants(Node *node, int uid)
      {
            for (auto child : node->childs)
            {
                  if (child->uid != -1)
                  {
                        //cout<<child->data<<endl;
                        unlock(child, uid);
                  }
                  upadateDescendants(child, uid);
            }
      }

      //------------- upgrade function start here -------------------------
      bool upgrade(Node *node, int uid)
      {
            /*
            Conditions -
            1. - Current node Should be unlocked
            2. - Anchestors should be unlocked
            3. - Has atleast one locked Descendends and everylocked decedends has same uid
            */

            if (node->uid != -1)
                  return false;
            if (islockedAnchestors(node))
                  return false;
            if (node->count == 0)
                  return false;
            if (checkDescends(node, uid))
            {
                  // cout<<"Rahul"<<endl;
                  return false;
            }

            upadateDescendants(node, uid);
            lock(node, uid);

            // cout<<"Test "<<nodeAdress["Beijing"]->uid<<endl;
            return true;
      }
      // TC - O(N) + O(N)
      //-----------------Upgrade Function ends here--------------------------
};

// Main Function
int main()
{
      // input number of nodes, pre node child, no of queries
      int n, m, q;
      cin >> n >> m >> q;

      // input of node
      vector<string> nodes;
      for (int i = 0; i < n; i++)
      {
            string str;
            cin >> str;

            nodes.push_back(str);
      }

      // inserting the node of making the tree
      Tree root;
      root.insert(n, m, nodes);

      // root.printTree();
      int i = 1;
      while (q--)
      {

            int choice;
            string data;
            int uid;

            cin >> choice >> data >> uid;
            Node *node = root.nodeAdress[data];

            switch (choice)
            {
            case 1:
                  cout << root.lock(node, uid) << endl;
                  break;
            case 2:
                  cout << root.unlock(node, uid) << endl;
                  break;

            case 3:
                  cout << root.upgrade(node, uid) << endl;
                  break;
            }
      }
}