/**
 * [ BFS ]
 * 문제: 16234 인구이동
 *
 * https://www.acmicpc.net/problem/16234
 */

#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

int N, L, R, answer;
int map[55][55], position[4][2] = {{1,0},{-1,0},{0,1},{0,-1}};  // 아래, 위, 우, 좌
int visit[55][55];
vector<vector<pair<int,int>>> groupList;    // 경계선을 열 나라 그룹화
vector<pair<int,int>> group;

void findGroup(int x, int y) {

    // 방문했을면 Back
    if(visit[x][y] == 1) return;

    queue<pair<int,int>> que;
    que.push({x,y});
    visit[x][y] = 1;

    while(!que.empty()) {
        int nowX = que.front().first, nowY = que.front().second;
        que.pop();

        for(int i = 0; i < 4; i++) {
            int nextX = nowX + position[i][0], nextY = nowY + position[i][1];

            if(nextX >= 0 && nextX < N && nextY >= 0 && nextY < N && visit[nextX][nextY] != 1) {
                int value1 = map[nowX][nowY] - map[nextX][nextY];
                int value2 = map[nextX][nextY] - map[nowX][nowY];

                if((value1 >= L && value1 <= R) || (value2 >= L && value2 <= R)) {
                    if(group.size() == 0) { // 최초로 그룹에 넣는 경우, 현재 좌표값도 넣어줌
                        group.push_back({nowX, nowY});
                    }
                    visit[nextX][nextY] = 1;    // 그룹에 넣어진 좌표는 표기해준다.
                    group.push_back({nextX,nextY});
                    que.push({nextX,nextY});
                }
            }
        }

    }


    if(group.size() > 0)
        groupList.push_back(group);
//    for(int r = 0 ; r < N; r++) {
//        for (int c = 0; c < N; c++) {
//            if(groupMap[r][c] == 1) {
//                group.push_back({r,c});
//            }
//        }
//    }
}

void movePopulation() {

    for(int i = 0; i < groupList.size(); i++) {

        int sum = 0;
        for(int j = 0; j < groupList[i].size(); j++) {
            sum += map[groupList[i][j].first][groupList[i][j].second];
        }

        sum /= groupList[i].size();
        for(int j = 0; j < groupList[i].size(); j++) {
            map[groupList[i][j].first][groupList[i][j].second] = sum;
        }

    }

}

int main() {

    scanf("%d %d %d", &N, &L, &R);

    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
            // 0 ≤ map[i][j] ≤ 100
            cin >> map[i][j];
        }
    }

    while(1) {

        // 초기화
        groupList.clear();
        for(int r = 0; r < N; r++) {
            for (int c = 0; c < N; c++) {
                visit[r][c] = 0;
            }
        }

        // 경계선 open
        for(int r = 0; r < N; r++) {

            for(int c = 0; c < N; c++) {
                // 초기화
                group.clear();

                // BFS: 그룹 탐색
                findGroup(r, c);
            }
        }

        // 더이상 경계선 open할 것이 없다면 종료
        if(groupList.size() == 0) {
            break;
        }

        // 인구 이동 : 계산해주는 부분
        movePopulation();

        // count 올린다.
        answer++;

    }

    cout << answer << endl;
}
