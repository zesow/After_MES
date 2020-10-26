/**
 * [ 동적계획법 ]
 * 문제: 42898 등굣길
 *
 * https://programmers.co.kr/learn/courses/30/lessons/42898
 *
 */
#include <iostream>
#include <cstdio>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

int visit[101][101], map[101][101], position[4][2] ={{-1,0},{0,-1},{1,0},{0,1}}; // 위->아래, 왼->오른쪽, 아래, 오른쪽

int bfs(int m, int n) {

    queue<vector<int>> que;
    que.push({1,1,0});
    map[1][1] = visit[1][1] = 1;

    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= m; j++) {
            if(map[i][j] == -1) continue;
            int prev1 = map[i-1][j] == -1 ? 0 : map[i-1][j];
            int prev2 = map[i][j-1] == -1 ? 0 : map[i][j-1];

            /**
             * MAP에 저장해줄때마다 나머지값으로 계산해줘야함!
             */
            map[i][j] += (prev1+prev2)%1000000007;
        }
    }

    /**
     * BFS로 풀려 했으나 잘 안풀림..
     */
//    while(!que.empty()) {
//        int x = que.front()[0], y = que.front()[1];
//        que.pop();
//
//        if(map[x][y] > 1) continue;
//        for(int pos = 0; pos < 2; pos++) {
//
//            int prevX = x+position[pos][0], prevY = y+position[pos][1];
//
//            // 범위안에 존재 AND 웅덩이가 아닌 경우 ( AND 방문하지 않는 곳 => 이거 처리하면 루트가 겹치는 곳은 처리가 안됨)
//            if(prevX > 0 && prevX <= n && prevY > 0 && prevY <= m && map[prevX][prevY] != -1) { // && visit[prevX][prevY] == 0
//                map[x][y] += (map[prevX][prevY]%1000000007);
//            }
//        }
//
//        for(int pos = 2; pos < 4; pos++) {
//
//            int nX = x+position[pos][0], nY = y+position[pos][1];
//
//            if(nX > 0 && nX <= n && nY > 0 && nY <= m && map[nX][nY] == 0) {
//                que.push({nX, nY});
//                visit[nX][nY] = 1;
//            }
//
//        }
//
//    }

//    cout << "===============" << endl;
//    for(int i = 1; i <= n; i++) {
//        for(int j = 1; j <= m; j++) {
//            cout << map[i][j] << " ";
//        }
//        cout << endl;
//    }
//    cout << endl;
    return map[n][m];

}

int solution(int m, int n, vector<vector<int>> puddles) {
    int answer = 0;

    for(vector<int> puddle: puddles) {
        // 물웅덩이 표시
        map[puddle[1]][puddle[0]] = -1;
    }

    answer = bfs(m,n);

    return answer;
}

int main() {

    vector<vector<int>> input;
    vector<int> info;

    info.push_back(3);
    info.push_back(1);
    input.push_back(info);
    info.clear();

    info.push_back(1);
    info.push_back(3);
    input.push_back(info);
    info.clear();
//
//    info.push_back(-18);
//    info.push_back(-13);
//    input.push_back(info);
//    info.clear();
//
//    info.push_back(-5);
//    info.push_back(-3);
//    input.push_back(info);
//    info.clear();
//
//    info.push_back(0);
//    info.push_back(4);
//    input.push_back(info);
//    info.clear();

    cout << "RESULT: " << solution(4,3,input) << endl;

    return 0;
}