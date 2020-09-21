#include <iostream>
#include <cstdio>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;


/**
 * [ 조합(DFS) & BFS ]
 * 문제: 17142 연구소 3
 *
 * https://www.acmicpc.net/problem/17142
 *
 * @return
 */

int N, M, virusSize, answer = 987654321;
int map[55][55], check[15];
int position[4][2] = {{1,0}, {-1,0}, {0,1}, {0,-1}};    // 우, 좌 , 위, 아래
vector<pair<int,int>> virus;

void spreadVirus() {

    int virusMap[55][55] = {0, };
    int visited[55][55] = {0, };

    queue<pair<int,int>> que;
    for(int i = 0; i < virusSize; i++) {
        if(check[i] == 1) {
            que.push(virus[i]);
            visited[virus[i].first][virus[i].second] = 1;
        }
    }

    int cnt = 0;

    while(!que.empty()) {
        int x = que.front().first, y = que.front().second;
        que.pop();

        /**
         * 이미 최소값 보다 큰경우는 더 계산해볼 필요가 없음
         * BFS빠져나가야 시간이 줄어든다!!!!!!!
         */
        if(cnt >= answer) {
            break;
        }

        for(int i = 0; i < 4; i++) {

            int nextX = x+position[i][0], nextY = y+position[i][1];

            // 갈 수 없는 경우는 제외
            if(nextX < 0 || nextX >= N || nextY < 0 || nextY >= N || visited[nextX][nextY] == 1) continue;
            // 빈공간인것을 확인(바이러스가 퍼질 수 있는 공간인 경우), 굳이 의미없는 비활성 바이러스는 활성바이러스로 만들 필요없다
            if(map[nextX][nextY] == 0 || map[nextX][nextY] == 2) {

                if(map[nextX][nextY] == 2) {
                    int ckCnt = 0;
                    for(int j = 0; j < 4; j++) {
                        int nextPosX = position[j][0], nextPosY = position[j][1];
                        int ckX = nextX, ckY = nextY;
                        while(1) {
                            ckX += nextPosX;
                            ckY += nextPosY;
                            if(ckX < 0 || ckX >= N || ckY < 0 || ckY >= N || (nextX == ckX && nextY == ckY) || visited[ckX][ckY] == 1) break;
                            else if(map[ckX][ckY] == 0) {
                                ckCnt++;
                                break;
                            }
                        }
                        if(ckCnt > 0) {
                            break;
                        }
                    }

                    if(ckCnt == 0) continue;
                }

                virusMap[nextX][nextY] = virusMap[x][y] + 1;
                visited[nextX][nextY] = 1;
                que.push({nextX, nextY});

                if(virusMap[nextX][nextY] > cnt) {
                    cnt = virusMap[nextX][nextY];
                }
            }

        }
    }

    // 빈공간이 모두 바이러스가 퍼졌는지 체크
//    cout << "\n=========AFTER===========" << endl;
//    for(int i = 0; i < N; i++) {
//        for (int j = 0; j < N; j++) {
//            cout << virusMap[i][j] << " ";
//        }
//        cout << endl;
//    }
    for(int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if(map[i][j] == 0 && virusMap[i][j] == 0) {
                cnt = -1; break;
            }
        }
    }

    if(cnt != -1 && cnt < answer) {
        answer = cnt;
    }
//    cout <<"지금까지 개수: " << answer << endl;
}

void chooseVirus(int cnt, int startIdx) {

    if(cnt > M) {
        return;
    }
    // 바이러스를 M개만큼 선택한 경우 logic 수행
    if(cnt == M) {
        spreadVirus();
        return;
    }

    /**
     * i의 시작점을 지정하는 것이 시간초과의 핵심!!!!!
     */
    for(int i = startIdx; i < virusSize; i++) {
        if(check[i] == 0) {
            check[i] = 1;
            chooseVirus(cnt+1, i+1);
            check[i] = 0;
        }
    }
}

int main() {
    scanf("%d %d" ,&N, &M);

    int empty = 0;
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
            cin >> map[i][j];

            // 바이러스 위치 저장
            if(map[i][j] == 2) {
                virus.push_back({i,j});
            }
            if(map[i][j] == 0) {
                empty++;
            }
        }
    }

    virusSize = virus.size();

    if(empty == 0){
        cout << 0;
    } else {
        // 바이러스 선택 경우의수 탐색: 조합탐색
        chooseVirus(0, 0);

        if(987654321 == answer) {
            answer = -1;
        }
        cout << answer;
    }

}