#include <bits/stdc++.h>
using namespace std;

class Node
{
public:
      Node *parent;          //for keeping track of par
      int data;              //value for node
      vector<Node *> childs; //childs of node
      Node(int val)
      {
            data = val;
      }
};

void printTree(Node * node)
{
      string str = to_string(node->data) + "->>";
      for(auto child : node->childs)
      {
            str += to_string(child->data) + " ";
      }
      cout<<str<<endl;
      for(auto child : node->childs)
      {
            printTree(child);
      }
}

int main()
{
      vector<int> arr = {10, 20, 50, -1, 60, -1, -1, 30, 70, -1, 80, 110, -1, 100, -1, -1, 90, -1, -1, 40, 100, -1, -1, -1};
      stack<Node *> st;
      Node *root = nullptr;

      for (int i = 0; i < arr.size(); i++)
      {
            if (arr[i] == -1 && !st.empty())
                  st.pop();
            else
            {
                  Node *child = new Node(arr[i]); // making of child node

                  if (st.size() > 0)
                  {
                        Node *par = st.top();
                        child->parent = par; //

                        par->childs.push_back(child);
                  }
                  else
                  {
                        root = child;
                  }
                  st.push(child);
            }
      }
      printTree(root);
}