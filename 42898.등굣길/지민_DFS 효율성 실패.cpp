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

int visit[101][101], map[101][101], position[2][2] ={{1,0},{0,1}}; // 아래, 오른쪽

int bfs(int m, int n) {

    int minDist = 987654321, minCnt = 0;
    queue<vector<int>> que;
    que.push({1,1,0});

    while(!que.empty()) {
        int x = que.front()[0], y = que.front()[1], dist = que.front()[2];
        que.pop();

        // 학교에 도착한 경우
        if(x == m && y == n && dist <= minDist) {

            // 더 작은경우는 count값 초기화
            if(dist < minDist) {
                minCnt = 1;
                minDist = dist;
            } else if(dist == minDist) {
                minCnt++;
            }
        }


        for(int pos = 0; pos < 2; pos++) {

            int nX = x+position[pos][0], nY = y+position[pos][1];

            // 범위안에 존재 AND 웅덩이가 아닌 경우 ( AND 방문하지 않는 곳 => 이거 처리하면 루트가 겹치는 곳은 처리가 안됨)
            if(nX > 0 && nX <= m && nY > 0 && nY <= n && map[nX][nY] == 0) { // && visit[nX][nY] == 0
                que.push({nX, nY, dist+1});
                visit[nX][nY] = 1;
            }
        }

    }

    return minCnt;

}

int solution(int m, int n, vector<vector<int>> puddles) {
    int answer = 0;

    for(vector<int> puddle: puddles) {
        // 물웅덩이 표시
        map[puddle[0]][puddle[1]] = 1;
    }

    answer = bfs(m,n);

    return answer%1000000007;
}

int main() {

    vector<vector<int>> input;
    vector<int> info;

    info.push_back(2);
    info.push_back(2);
    input.push_back(info);
    info.clear();

//    info.push_back(-14);
//    info.push_back(-5);
//    input.push_back(info);
//    info.clear();
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