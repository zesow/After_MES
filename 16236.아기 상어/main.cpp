#include <iostream>
#include <cstdio>
#include <algorithm>
#include <queue>
#include <vector>

using namespace std;

/**
 * 문제: 16236 아기 상어
 * https://www.acmicpc.net/problem/16236
 *
 * @return
 */

int N, answer = 0, shark = 2, eat = 0, fish = 0, minCnt=987654321, minX = 24, minY = 24, sharkX, sharkY;
int map[25][25];
int pos[4][2] = {{0,1}, {0,-1}, {1,0}, {-1,0}}; // 우, 좌, 위, 아래

void eatFish() {

    answer += minCnt;   // 걸린시간 더해줌

    // 물고기 잡아 먹은 위치를, 현 상어 위치로 변경처리
    sharkX = minX;
    sharkY = minY;

    // 초기화
    map[minX][minY] = 0; // 물고기 잡아먹음
    minCnt = 987654321;
    minX = 24;
    minY = 24;
    eat++;

    // 물고기수 감소
    fish--;

    // 아기 상어는 자신의 크기와 같은 수의 물고기를 먹을 때 마다 크기가 1 증가
    if(eat == shark) {
        shark++;
        eat = 0;
    }

}

/**
 * 현재 상어위치로부터 잡아먹을 수 있는 최단거리에 있는 물고기까지의 시간을 구한다.
 *
 * @param posX 현재 상어위치 X
 * @param posY 현재 상어위치 Y
 */
void bfs(int posX, int posY) {

    queue<pair<int,int>> que;
    que.push({posX, posY});
    int visit[25][25] = {0,};   // 방문여부
    int mapDist[25][25] = {0, };  // 방문여부, 해당 위치까지의 최소 이동 시
    visit[posX][posY] = 1;

    while(!que.empty()) {
        // 현위
        int x = que.front().first;
        int y = que.front().second;
        que.pop();

        /**
         * 이부분이 중요한데,
         * 큐에서 pop하는 경우 방문처리를 해버리면, 같은 원소가 큐에 여러번 들어갈 수 있어 TLE나 MLE 발생함!
         * => 왜냐, 그 원소는 탐색할 에정으로 이미 queue에 넣었는데
         *   방문처리를 안했기 때문에 아직 미방문한것으로 판단하여 계속 queue에 넣어버림.
         */
//        visit[x][y] = 1;

        // 4방위 탐색
        for(int i = 0; i < 4; i++) {

            int nextX = x + pos[i][0], nextY = y + pos[i][1];

            // 갈수 없는 경로는 포기
            if (nextX < 0 || nextX >= N || nextY < 0 || nextY >= N) {   // 지정범위초과
                continue;
            } else if(map[nextX][nextY] > shark) {  // 상어보다 큰경우
                continue;
            }

            // 지나갈 수 있는 경우
            else if(map[nextX][nextY] <= shark) {

                // 아직 지나간 이력이 없거나, 걸린 시간 값이 작은경우 값을 거리계산값(mapDist)을 바꿔준다.
                if(mapDist[nextX][nextY] == 0 || mapDist[x][y] + 1 < mapDist[nextX][nextY]) {
                    mapDist[nextX][nextY] = mapDist[x][y] + 1;
                }

                // 먹을 수 있는 경우 & 걸린시간이 적은 경우
                if (map[nextX][nextY] > 0 && map[nextX][nextY] < shark && mapDist[x][y] + 1 <= minCnt) {

                    // 해당 위치까지 오는데 걸린 시간 저장
                    if (mapDist[x][y] + 1 < minCnt) {  // 더 작은 경우는 확정
                        minX = nextX, minY = nextY;
                        minCnt = mapDist[nextX][nextY];
                    } else {    // 걸린시간이 동일한 경우의 우선순위를 따진다.
                        if (nextX < minX) {   // 1. 가장 위에 있는 물고기위
                            minX = nextX, minY = nextY;
                            minCnt = mapDist[nextX][nextY];
                        } else if (nextX == minX && nextY < minY) {    // 2. 가장 왼쪽에 있는 물고기
                            minX = nextX, minY = nextY;
                            minCnt = mapDist[nextX][nextY];
                        }
                    }

                }

                if(visit[nextX][nextY] != 1) {
                    que.push({nextX, nextY});

                    /**
                     * push하는 경우 방문처리를 해서,
                     * 다음 push시에 중복하여 queue에 들어가지 않도록 설정해야함.
                     */
                    visit[nextX][nextY] = 1;
                }
            }
        } // 4방위 탐색 종료
    }

}

int main() {

    scanf("%d", &N);

    for(int i = 0 ; i <N; i++) {
        for(int j = 0; j < N; j++) {
            cin >> map[i][j];
            if(map[i][j] == 9) {    // 아기상어 위치 저장
                sharkX = i; sharkY = j;
                map[i][j] = 0;
            } else if(map[i][j] < 7 && map[i][j] > 0) { // 물고기위치 저장
                fish++;
            }
        }
    }

    while(fish > 0) {

        // 아기상어보다 작은 물고기에 대해 루트 탐색을 한다.
        bfs(sharkX, sharkY);

        // 최단경로 찾은 후, 물고기를 먹는다.
        if(minCnt != 987654321) {
            eatFish();
        } else {    // 더이상 찾을 수 없는 경우는 종료처리한다.
            break;
        }
    }
    cout << answer;
}