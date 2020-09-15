#include <iostream>
#include <algorithm>
#include <queue>
#include <fstream>
#include <stack>
#include <cstdio>

using namespace std;

/**
 * BFS
 *
 * 문제: 14502 연구소
 * https://www.acmicpc.net/problem/14502
 *
 * @return
 */

int N, M, answer = 0;
int map[9][9];
int position[4][2] = {{1,0}, {-1,0}, {0,1}, {0,-1}};    // 아래, 위, 오른쪽, 왼쪽
queue<pair<int,int>> virusPos;   // 바이러스 위치


void checkVir() {

    // 새로운 임시 배열 복사
    int mapTest[9][9] = {};
    for(int x =0 ; x< N; x++) {
        for(int y = 0; y<M; y++) {
            mapTest[x][y] = map[x][y];
        }
    }

    // BFS 부분
    queue<pair<int,int>> spreadVir = virusPos;
    // 바이러스로 감염되는 부분
    while(!spreadVir.empty()) {

        pair<int,int> pos = spreadVir.front();
        spreadVir.pop();

        for(int j =0; j<4;j++) {

            int xIdx = pos.first + position[j][0];
            int yIdx = pos.second + position[j][1];

            if(0 <= xIdx && xIdx < N && 0 <= yIdx && yIdx < M) {
                if(mapTest[xIdx][yIdx] == 0) {
                    mapTest[xIdx][yIdx] = 2;
                    spreadVir.push(make_pair(xIdx, yIdx));
                }
            }

        }
    }

//    cout << "=======================" << endl;
//    for(int x = 0; x < N; x++) {
//        for(int y = 0; y < M; y++) {
//            cout << mapTest[x][y] << " ";
//        }
//         cout << endl;
//    }

    // 오엽되지 않은 부분 체크
    int cnt = 0;
    for(int x = 0; x < N; x++) {
        for(int y = 0; y < M; y++) {
            if(mapTest[x][y] == 0) {
                cnt++;
            }
        }
    }

    if(cnt > answer) {
        answer = cnt;
    }
}


// 전체 벽을 세울 수 있는 부
void comb(int cnt) {

    if(cnt == 3) {
        checkVir();
        return;
    }

    // 벽을 세운다
    for(int x  = 0; x < N; x++) {
        for(int y = 0; y < M; y++) {
            if(map[x][y] == 0) {
                map[x][y] = 1;

                // 재귀호출
                comb(cnt+1);

                // 원상복귀
                map[x][y] = 0;
            }
        }
    }
}


int main() {
    fflush(stdin);

    scanf("%d %d", &N, &M);

    for(int x =0; x < N; x++) {
        for(int y = 0; y < M; y++) {
            scanf("%d", &map[x][y]);

            // 바이러스 위치 표기
            if(map[x][y] == 2) {
                virusPos.push(make_pair(x,y));
            }
        }
    }

    comb(0);
    cout << answer;
}
