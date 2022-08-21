```
#include<bits/stdc++.h>
using namespace std;

    void dfs( string a ){
        if(a.length() == 3){
            cout<< a <<endl;
            return ;
        }
        for(int i = 0 ;i<=9;i++){
            dfs(a + char (i+'0'));
        }
    } 
    
    int main(){
        string a ="";
        dfs(a);
        return 0;
    }
```