#include<bits/stdc++.h>
using namespace std;

int main()
{
    long long int i,j,k,a,b,c,q,uid,N,M,Q,flag;
    cin>>N>>M>>Q;
    string str,x;
    map<string,int> mp;
    for(i=0;i<N;i++)
    {
        cin>>str;
        mp[str]=i;
    }
    j=0;
    vector<vector<long long int>> A(N);
    i=1;
    k=0;
    while(i<N)
    {
        A[j].push_back(i);
        k++;
        if(k==M)
        {
            k=0;
            j++;
        }
        i++;
    }
    map<int,int> Hash;
    for(i=0;i<N;i++)
        Hash[i]=-1;
    for(i=0;i<Q;i++)
    {
        cin>>q>>x>>uid;
        a=mp[x];
        flag=1;
        if(q==1)
        {
            vector<long long int> st;
            b=ceil(float(a)/float(M))-1;
            st.push_back(b);
            while(b!=0)
            {
                b=ceil(float(b)/float(M))-1;
                st.push_back(b);
            }
            for(k=0;k<st.size();k++)
            {
                if(Hash[st[k]]!=-1)
                {
                    flag=0;
                    break;
                }
            }
            vector<long long int> temp;
            temp.push_back(a);
            i=0;
            j=1;
            while(i!=j)
            {
                for(auto p: A[temp[i]])
                {
                    if(Hash[p]!=-1)
                    {
                        flag=0;
                        break;
                    }
                    else
                    {
                        temp.push_back(p);
                        j++;
                    }
                }
                i++;
            }
            if(flag==1)
            {
                Hash[a]=uid;
            }
        }
        else if(q==2)
        {
            flag=0;
            if(Hash[a]==uid)
            {
                Hash[a]=-1;
                flag=1;
            }
        }
        else
        {
            for(auto p: A[a])
            {
                if(Hash[p]!=uid)
                {
                    flag=0;
                    break;
                }
            }
            if(flag==1)
            {
                for(auto p: A[a])
                    Hash[p]=-1;
                Hash[a]=uid;
            }
        }
        if(flag==1)
            cout<<"true";
        else
            cout<<"false";
        cout<<"\n";
    }
    return 0;
}