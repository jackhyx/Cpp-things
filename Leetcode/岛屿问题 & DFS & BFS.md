#### 200. 岛屿数量
给你一个由 '1'（陆地）和 '0'（水）组成的的二维网格，请你计算网格中岛屿的数量。
岛屿总是被水包围，并且每座岛屿只能由水平方向和/或竖直方向上相邻的陆地连接形成。
此外，你可以假设该网格的四条边均被水包围。
示例 1：
输入：grid = [
["1","1","1","1","0"],
["1","1","0","1","0"],
["1","1","0","0","0"],
["0","0","0","0","0"]
]
输出：1
* 这种写法比较好理解和记忆
```c++
class Solution {
    void dfs(vector<vector<char>>& grid, int i, int j) {
        int m = grid.size(), n = grid[0].size();
        if (i < 0 || j < 0 | i >= m || j >=n){
            return ;
        }
        if (grid[i][j] == '0') {
            return ;
        }

        grid[i][j] = '0';
        dfs(grid, i + 1, j);
        dfs(grid, i, j + 1);
        dfs(grid, i - 1, j);
        dfs(grid, i, j - 1);
    }
public:
    int numIslands(vector<vector<char>>& grid) {
        int res = 0;
        int m = grid.size(), n = grid[0].size();

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == '1') {
                    res ++;
                    dfs(grid, i, j);
                }
            }
        }
        return res;      
    }
};
```
```c++
class Solution {
private:
    int dir[4][2] = {0, 1, 1, 0, -1, 0, 0, -1}; // 四个方向
    void dfs(vector<vector<char>>& grid, vector<vector<bool>>& visited, int x, int y) {
        for (int i = 0; i < 4; i++) {
            int nextx = x + dir[i][0];
            int nexty = y + dir[i][1];
            if (nextx < 0 || nextx >= grid.size() || nexty < 0 || nexty >= grid[0].size()) continue;  // 越界了，直接跳过
            if (!visited[nextx][nexty] && grid[nextx][nexty] == '1') { // 没有访问过的 同时 是陆地的

                visited[nextx][nexty] = true; 
                dfs(grid, visited, nextx, nexty);
            } 
        }
    }
public:
    int numIslands(vector<vector<char>>& grid) {
        int n = grid.size(), m = grid[0].size();
        vector<vector<bool>> visited = vector<vector<bool>>(n, vector<bool>(m, false)); 
        int result = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (!visited[i][j] && grid[i][j] == '1') { 
                    result++; // 遇到没访问过的陆地，+1
                    dfs(grid, visited, i, j); // 将与其链接的陆地都标记上 true
                }
            }
        }
        return result;
    }
};
```

#### 695. 岛屿的最大面积
给你一个大小为 m x n 的二进制矩阵 grid 。
岛屿 是由一些相邻的 1 (代表土地) 构成的组合，这里的「相邻」要求两个 1 必须在 水平或者竖直的四个方向上 相邻。你可以假设 grid 的四个边缘都被 0（代表水）包围着。
岛屿的面积是岛上值为 1 的单元格的数目。
计算并返回 grid 中最大的岛屿面积。如果没有岛屿，则返回面积为 0 。
```c++
class Solution {
    int dfs(vector<vector<int>>& grid, int i, int j) {
        int m = grid.size(), n = grid[0].size();
        if (i < 0 || j < 0 | i >= m || j >=n){
            return 0;
        }
        if (grid[i][j] == 0) {
            return 0;
        }

        grid[i][j] = 0;
        int count = 1;
        count += dfs(grid, i + 1, j);
        count += dfs(grid, i, j + 1);
        count += dfs(grid, i - 1, j);
        count += dfs(grid, i, j - 1);
        return count;
    }
   
public:
    int maxAreaOfIsland(vector<vector<int>>& grid) {
        int res = 0;
        int m = grid.size(), n = grid[0].size();

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == 1) {
                    res = max(res, dfs(grid, i, j));
                }
            }
        }
        return res;   
    }
};
```
```c++
class Solution {
private:
    int count;
    int dir[4][2] = {0, 1, 1, 0, -1, 0, 0, -1}; // 四个方向
    void dfs(vector<vector<int>>& grid, vector<vector<bool>>& visited, int x, int y) {
        for (int i = 0; i < 4; i++) {
            int nextx = x + dir[i][0];
            int nexty = y + dir[i][1];
            if (nextx < 0 || nextx >= grid.size() || nexty < 0 || nexty >= grid[0].size()) continue;  // 越界了，直接跳过
            if (!visited[nextx][nexty] && grid[nextx][nexty] == 1) { // 没有访问过的 同时 是陆地的

                visited[nextx][nexty] = true;
                count++;
                dfs(grid, visited, nextx, nexty);
            }
        }
    }

public:
    int maxAreaOfIsland(vector<vector<int>>& grid) {
        int n = grid.size(), m = grid[0].size();
        vector<vector<bool>> visited = vector<vector<bool>>(n, vector<bool>(m, false));

        int result = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (!visited[i][j] && grid[i][j] == 1) {
                    count = 1;
                    visited[i][j] = true;
                    dfs(grid, visited, i, j); // 将与其链接的陆地都标记上 true
                    result = max(result, count);
                }
            }
        }
        return result;
    }
};
```
#### 463. 岛屿的周长
给定一个 row x col 的二维网格地图 grid ，其中：grid[i][j] = 1 表示陆地， grid[i][j] = 0 表示水域。
网格中的格子 水平和垂直 方向相连（对角线方向不相连）。整个网格被水完全包围，但其中恰好有一个岛屿（或者说，一个或多个表示陆地的格子相连组成的岛屿）。
岛屿中没有“湖”（“湖” 指水域在岛屿内部且不和岛屿周围的水相连）。格子是边长为 1 的正方形。网格为长方形，且宽度和高度均不超过 100 。计算这个岛屿的周长。

示例 1：

输入：grid = [[0,1,0,0],[1,1,1,0],[0,1,0,0],[1,1,0,0]]
输出：16
解释：它的周长是上面图片中的 16 个黄色的边
```c++
class Solution {
    int dfs(vector<vector<int>>& grid, int i, int j) {
         int m = grid.size(), n = grid[0].size();
        if (i < 0 || j < 0 | i >= m || j >=n){
            return 1;
        }
        if (grid[i][j] == 0) {
            return 1;
        }
        if(grid[i][j] == 2) return 0;
        grid[i][j] = 2;
        return  dfs(grid, i + 1, j) + dfs(grid, i, j + 1) + dfs(grid, i - 1, j)+ dfs(grid, i, j - 1);
        
    }
public:
    int islandPerimeter(vector<vector<int>>& grid) {
        
        int m = grid.size(), n = grid[0].size();

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == 1) {
                    return dfs(grid, i, j);
                }
            }
        }
        return 0;   
    }
};
```
```c++
class Solution {
public:
    int direction[4][2] = {0, 1, 1, 0, -1, 0, 0, -1};
    int islandPerimeter(vector<vector<int>>& grid) {
        int result = 0;
        for (int i = 0; i < grid.size(); i++) {
            for (int j = 0; j < grid[0].size(); j++) {
                if (grid[i][j] == 1) {
                    for (int k = 0; k < 4; k++) {       // 上下左右四个方向
                        int x = i + direction[k][0];
                        int y = j + direction[k][1];    // 计算周边坐标x,y
                        if (x < 0                       // i在边界上
                                || x >= grid.size()     // i在边界上
                                || y < 0                // j在边界上
                                || y >= grid[0].size()  // j在边界上
                                || grid[x][y] == 0) {   // x,y位置是水域
                            result++;
                        }
                    }
                }
            }
        }
        return result;
    }
};
```
#### 797. 所有可能的路径
给你一个有 n 个节点的 有向无环图（DAG），请你找出所有从节点 0 到节点 n-1 的路径并输出（不要求按特定顺序）
graph[i] 是一个从节点 i 可以访问的所有节点的列表（即从节点 i 到节点 graph[i][j]存在一条有向边）。
* DFS & 回溯
```c++
class Solution {
private:
    vector<vector<int>> result; // 收集符合条件的路径
    vector<int> path; // 0节点到终点的路径
    // x：目前遍历的节点
    // graph：存当前的图
    void dfs (vector<vector<int>>& graph, int x) {
        // 要求从节点 0 到节点 n-1 的路径并输出，所以是 graph.size() - 1
        if (x == graph.size() - 1) { // 找到符合条件的一条路径
            result.push_back(path);
            return;
        }
        for (int i = 0; i < graph[x].size(); i++) { // 遍历节点n链接的所有节点
            path.push_back(graph[x][i]); // 遍历到的节点加入到路径中来
            dfs(graph, graph[x][i]); // 进入下一层递归
            path.pop_back(); // 回溯，撤销本节点
        }
    }
public:
    vector<vector<int>> allPathsSourceTarget(vector<vector<int>>& graph) {
        path.push_back(0); // 无论什么路径已经是从0节点出发
        dfs(graph, 0); // 开始遍历
        return result;
    }
};
```
* BFS
```c++
class Solution {
public:
    vector<vector<int>> ans;
    vector<vector<int>> allPathsSourceTarget(vector<vector<int>>& graph) {
        queue<vector<int>> q;
        vector<int> v;
        v.push_back(0);
        q.push(v);
        while(!q.empty()){
            int size = q.size();
            for(int i =0; i < size; i++){
                vector<int> cur = q.front();
                q.pop();
                int id = cur[cur.size() - 1];
                if(id == graph.size() - 1){
                    ans.push_back(cur);
                    continue;
                }
                for(int next : graph[id]){
                    vector<int> tmp = cur;
                    tmp.push_back(next);
                    q.push(tmp);
                }
            }
        }
        return ans;
    }
};
```
```c++
class Solution {
    vector<int> path;
    vector<vector<int>> result;
    void dfs(vector<vector<int>>& graph, int x) {
        if(x == graph.size() - 1) {
            result.push_back(path);
            return ;
        }
        for(int i = 0; i < graph[x].size(); i++) {
            path.push_back(graph[x][i]);
            dfs(graph, graph[x][i]);
            path.pop_back();
        }
    }
public:
    vector<vector<int>> allPathsSourceTarget(vector<vector<int>>& graph) {
        path.clear();
        result.clear();
        path.push_back(0);
        dfs(graph, 0);
        return result;
    }
};
```
#### 542. 01 矩阵
给定一个由 0 和 1 组成的矩阵 mat ，请输出一个大小相同的矩阵，其中每一个格子是 mat 中对应位置元素到最近的 0 的距离。
两个相邻元素间的距离为 1 。
示例 1：

输入：mat = [[0,0,0],[0,1,0],[0,0,0]]
输出：[[0,0,0],[0,1,0],[0,0,0]]
示例 2：

输入：mat = [[0,0,0],[0,1,0],[1,1,1]]
输出：[[0,0,0],[0,1,0],[1,2,1]]
```c++
class Solution {
public:
    vector<vector<int>> updateMatrix(vector<vector<int>>& mat) {

    }
};  
```
```c++
class Solution {
public:
    vector<vector<int>> updateMatrix(vector<vector<int>>& mat) {
        int m=mat.size(),n=mat[0].size();
        queue<pair<int,int>>que;
        vector<vector<int>>direction{{-1,0},{1,0},{0,-1},{0,1}};//定义四个方向
        for(int i=0;i<m;++i){//将所有的0放入队列
            for(int j=0;j<n;++j){
                if(mat[i][j]==0){
                    que.push(make_pair(i,j));
                }else {
                    mat[i][j]=-1;//将所有的1设置为-1
                }
            }
        }

        int level=1;//类似于二叉树中的第几层
     //这里的层数不要被矩阵限制住了思维，所有的0都是第一层，被赋值过的元素是第二层，接着是第三层，第n层。。。   一层一层的剥洋葱   直至把矩阵的元素都遍历完
        while(!que.empty()){
            int size=que.size();
            while(size--){
                pair<int,int>cur=que.front();
                que.pop();
                for(int i=0;i<4;++i){//对四个方向进行遍历
                    int x=cur.first+direction[i][0];
                    int y=cur.second+direction[i][1];

                    if(x<0||x>=m||y<0||y>=n||mat[x][y]>=0){//对于大于等于0的数或越界进行跳过
                        continue;
                    }
                    mat[x][y]=level;//对于非0数进行赋值
                    que.push(make_pair(x,y));//开始生成新的洋葱皮
                }
            }
            ++level;
        }
        return mat;
    }
};

```
```c++
class Solution {
public:
    vector<vector<int>> updateMatrix(vector<vector<int>>& mat) {
        int m = mat.size(), n = mat[0].size();
        queue<pair<int, int>> que;
        vector<vector<int>> direction{{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
        for(int i = 0; i < m; i++) {
            for(int j = 0; j < n; j++) {
                if(mat[i][j] == 0) {
                    que.push({i, j});
                } else {
                    mat[i][j] = -1;
                }
            }
        }
        while(!que.empty()) {
            auto cur = que.front();
            que.pop();
            for(int j = 0; j < 4; j++) {
                int x = cur.first + direction[j][0];
                int y = cur.second + direction[j][1];
                if(x < 0 || x >= m || y < 0 || y >= n || mat[x][y] >= 0) continue;
                mat[x][y] = mat[cur.first][cur.second] + 1;
                que.push({x, y});
            }  
        }
        return mat;
    }
};
```
#### 752. 打开转盘锁
你有一个带有四个圆形拨轮的转盘锁。每个拨轮都有10个数字： '0', '1', '2', '3', '4', '5', '6', '7', '8', '9' 。每个拨轮可以自由旋转：例如把 '9' 变为 '0'，'0' 变为 '9' 。每次旋转都只能旋转一个拨轮的一位数字。
锁的初始数字为 '0000' ，一个代表四个拨轮的数字的字符串。
列表 deadends 包含了一组死亡数字，一旦拨轮的数字和列表里的任何一个元素相同，这个锁将会被永久锁定，无法再被旋转。
字符串 target 代表可以解锁的数字，你需要给出解锁需要的最小旋转次数，如果无论如何不能解锁，返回 -1 。

示例 1:
输入：deadends = ["0201","0101","0102","1212","2002"], target = "0202"
输出：6
解释：
可能的移动序列为 "0000" -> "1000" -> "1100" -> "1200" -> "1201" -> "1202" -> "0202"。
注意 "0000" -> "0001" -> "0002" -> "0102" -> "0202" 这样的序列是不能解锁的，
因为当拨动到 "0102" 时这个锁就会被锁定。
```c++
class Solution {
public:
    int openLock(vector<string>& deadends, string target) {
        // 哈希表vis中存储不可能入队的结点，包括deadends和已访问过的结点
        unordered_set<string> vis;
        vis.insert(deadends.begin(), deadends.end()); 
        if(vis.count("0000")) 
            return -1;
        int step = 0;
        queue<string> st;
        st.push("0000");
        while(!st.empty()){            
            int length = st.size();
            for(int i = 0; i < length; i++){
                string curr = st.front();
                st.pop();
                // 找到目标元素，直接返回答案
                if(curr == target)
                    return step;
                // 处理curr周围的八个相邻结点
                for(int j = 0; j < 4; ++j){
                    // 自增1与自减1
                    for(int t = -1; t < 2; t += 2){
                        // 完美的字符处理方式，利用ascⅡ码之差之后加上t并取余作为新得到的整型，然后再加上0的ascⅡ码值返回字符
                        char a = (curr[j] -'0' + 10 + t) % 10 + '0';
                        string newOne = curr;
                        newOne[j] = a;
                        // 若哈希集中找不到此状态，则加入哈希集同时入队
                        if(!vis.count(newOne)){
                            st.push(newOne);
                            vis.emplace(newOne);
                        }
                    }                 
                }
            }
            // 本层队列中元素处理完成，到达下一转动步数，步数加1
            step++;
        }
        return -1;
    }
};
class Solution {
public:
    struct node{
        string status;
        int step;
    };
    int openLock(vector<string>& deadends, string target) {
        unordered_set<string> s;
        for(auto &str : deadends){
            s.insert(str);
        }
        //如果终点是起点，返回0
        if(target == "0000") return 0;
        //被0000卡住了，出发不了
        if(s.count("0000") == 1) return -1;
        queue<node> que;
        //将起点入队
        que.push((node){"0000",0});
        while(!que.empty()){
            //拿出队首元素并弹出
            node temp = que.front();
            que.pop();
            //找到目标返回步数
            if(temp.status == target){
                return temp.step;
            }
            for(int i = 0; i <= 4; i++){
                string t = temp.status;
                t[i]--;
                //<0改为9
                if(t[i] < '0') t[i] = '9';
                if(s.count(t) == 0){
                    que.push((node){t, temp.step + 1});
                    //插入到集合中，去重
                    s.insert(t);            
                }
                t = temp.status;
                t[i]++;
                //>9 改为0
                if(t[i] > '9') t[i] = '0';
                if(s.count(t) == 0){
                    que.push((node){t,temp.step + 1});
                    //插入到集合中，去重
                    s.insert(t);
                }
            }
        }
        return -1;
    }
};

```
```c++
class Solution {
public:
    int openLock(vector<string>& deadends, string target) {
        queue<string> q;
        unordered_map<string,int> deadends_hash;
        unordered_map<string,int> visit;
        for(string a:deadends){
            deadends_hash[a] = 1;
        }
        int step = 0;
        q.emplace("0000");

        while(q.size()){
            int sz = q.size();
            for(int i = 0;i<sz;i++){
                string this_string = q.front();
                q.pop();

                if(deadends_hash[this_string]){
                    continue;
                }

                if(this_string==target){
                    return step;
                }

                

                for(int j = 0;j<4;j++){
                    string a = plusone(this_string,j);
                    if(!visit[a]){
                        q.emplace(a);
                        visit[a]=1;
                    }
                    

                    a = minuone(this_string,j);
                    if(!visit[a]){
                        q.emplace(a);
                        visit[a]=1;
                    }
                }
            }
            step = step + 1;
        }
        return -1;

    }

    string plusone(string this_string, int j){
        if(this_string[j]=='9'){
            this_string[j] = '0';
        }else{
            this_string[j] = this_string[j] + 1;
        }
        return this_string;
    }

    string minuone(string this_string, int j){
        if(this_string[j]=='0'){
            this_string[j] = '9';
        }else{
            this_string[j] = this_string[j] - 1;
        }
        return this_string;
    }


};

class Solution {
public:
    int openLock(vector<string>& deadends, string target) {
        queue<pair<string, int>> q;
        unordered_map<string, bool> vis; // 记录数字是否访问过或为死亡数字
        for(auto& s: deadends)
            vis[s] = true;
        string s = "0000", ss;
        if(vis[s]) // 若初始数字为死亡数字，直接返回-1
            return -1;
        vis[s] = true; // 标记初始数字已访问
        q.emplace(s, 0); // 初始数字入队，旋转次数为0
        while(!q.empty()){
            auto [s, t] = q.front();
            q.pop();
            if(s == target) // 当前数字为目标数字，返回当前旋转次数
                return t;
            for(int i=0;i<4;i++){ // 遍历4位数字
                ss = s;
                ss[i] = ss[i]=='9' ? '0' : ss[i]+1; // 当前位+1
                if(!vis[ss]){ // 新数字未访问且不为死亡数字
                    vis[ss] = true; // 标记新数字已访问
                    q.emplace(ss, t+1); // 新数字入队，旋转次数+1
                }
                ss = s;
                ss[i] = ss[i]=='0' ? '9' : ss[i]-1; // 当前位-1
                if(!vis[ss]){ // 新数字未访问且不为死亡数字
                    vis[ss] = true; // 标记新数字已访问
                    q.emplace(ss, t+1); // 新数字入队，旋转次数+1
                }
            }
        }
        return -1; // 无法变为目标数字，直接返回-1
    }
};
class Solution {
public:
    int openLock(vector<string>& deadends, string target) {
        queue<pair<string, int>> process;
        process.push({"0000", 0});
        unordered_set<string> passby;
        passby.insert("0000");
        unordered_set<string> deadendset;
       
        for(const string& deadend : deadends){
            deadendset.insert(deadend);
        }
        if(deadendset.count("0000")){
            return -1;
        }
        if(target == "0000"){
            return 0;
        }

        while(!process.empty()){
            int levelsize = process.size();
            for(int i = 0; i < levelsize; i++){
                string cur_string = process.front().first;
                int steps = process.front().second;
                process.pop();
                for(int i = 0; i < 4; i++){
                    string forward_string = forward_rotation(cur_string , i);
                    if(forward_string == target){
                        return 1 + steps;
                    }
                    if(!deadendset.count(forward_string) && !passby.count(forward_string)){
                        process.push({forward_string, steps + 1});
                        passby.insert(forward_string);
                    }
                }
                for(int j = 0; j < 4; j++){
                    string backward_string = backward_rotation(cur_string, j);
                    if(backward_string == target){
                        return 1 + steps;
                    }
                    if(!deadendset.count(backward_string) && !passby.count(backward_string)){
                        process.push({backward_string, steps + 1});
                        passby.insert(backward_string);
                    }
                }
            }

        } 
        return -1;
    }

    string forward_rotation(string password, int i){
        if(i >= password.length()){
            cerr << "index beyond boundary" << endl;
            abort();
        }
        string res = password;
        if(res[i] != '9'){
            res[i] += 1;
        }else{
            res[i] = '0';
        }
        return res;
    }

    string backward_rotation(string password, int i){
        if(i >= password.length()){
            cerr << "index beyond boundary" << endl;
            abort();
        }
        string res = password;
        if(res[i] != '0'){
            res[i] -= 1;
        }else{
            res[i] = '9';
        }
        return res;
    }
};


```
```c++
class Solution {
public:
    int openLock(vector<string>& deadends, string target) {
        queue<pair<string, int>> q;
        unordered_map<string, bool> vis; // 记录数字是否访问过或为死亡数字
        for(auto& s: deadends)
            vis[s] = true;
        string s = "0000";
        if(vis[s]) // 若初始数字为死亡数字，直接返回-1
            return -1;
        vis[s] = true; // 标记初始数字已访问
        q.emplace(s, 0); // 初始数字入队，旋转次数为0
        while(!q.empty()){
            auto node = q.front();
            q.pop();
            if(node.first == target) // 当前数字为目标数字，返回当前旋转次数
                return node.second;
            for(int i = 0; i < 4; i++){ // 遍历4位数字
                auto temp = node.first;
                temp[i] = temp[i] == '9' ? '0' : temp[i] + 1; // 当前位+1
                if(!vis[temp]){ // 新数字未访问且不为死亡数字
                    vis[temp] = true; // 标记新数字已访问
                    q.emplace(temp, node.second + 1); // 新数字入队，旋转次数+1
                }
                temp = node.first;
                temp[i] = temp[i]=='0' ? '9' : temp[i] - 1; // 当前位-1
                if(!vis[temp]){ // 新数字未访问且不为死亡数字
                    vis[temp] = true; // 标记新数字已访问
                    q.emplace(temp, node.second + 1); // 新数字入队，旋转次数+1
                }
            }
        }
        return -1; // 无法变为目标数字，直接返回-1
    }
};
```