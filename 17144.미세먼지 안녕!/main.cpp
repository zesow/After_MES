#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <queue>

using namespace std;

/**
 * [구현 / 시뮬레이션]
 * 문제: 17144 미세먼지 안녕!
 *
 * https://www.acmicpc.net/problem/17144
 *
 * @return
 */
int R, C, T;
int map[55][55];
int afterSpread[55][55] = {0, }; // 퍼진미세먼지
int pos[4][2] = {{1,0}, {-1,0}, {0,1}, {0,-1}}; // 아래, 위, 오른쪽, 왼쪽
vector<pair<int,int>> cleaner;  // 청소기 위치
vector<pair<int,int>> dust;  // 미세먼저 위치

void initValues() {
    dust.clear(); // 미세먼지 위치 초기화
    for(int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) {

            afterSpread[i][j] = 0;  // 퍼진 미세먼지 초기화
            if(map[i][j] >= 5) {   // 퍼질수있는 미세먼지 위치
                dust.push_back({i,j});
            }
        }
    }
}
/**
 * 미세먼지 확장
 * @param x 미세먼지 위치 X
 * @param y 미세먼지 위치 Y
 */
void spreadDust(int x, int y) {

    int cnt = 0 ;   // 퍼진 미세먼지 개수
    int dustVal = map[x][y]/5;  // 퍼진 미세먼지 양
    for(int i = 0; i < 4; i++) {

        int nextX = x+pos[i][0], nextY = y+pos[i][1];

        // 1. 위치값이 map 범위 안에 드는지 확인
        // 2. 해당 위치에 공기청정기가 있는지 확인
        if(nextX >= 0 && nextX < R && nextY >=0 && nextY < C && map[nextX][nextY] != -1) {
            // 퍼진 미세먼지 양 저장
            afterSpread[nextX][nextY] += dustVal;
            cnt++;
        }
    }
    // 현위치의 미세먼지양 변경
    if(cnt > 0) {
        map[x][y] = map[x][y] - (dustVal * cnt);
    }
}


void cleanDust() {

    int upX = cleaner[0].first;
    // 위쪽: 우-위-좌-아래 (로직은 반대로 탐색한다)
    for(int i = upX-1; i > 0; i--) { // 아래로 오는경우
        map[i][0] = map[i-1][0];
    }
    for(int i = 0; i < C-1; i++) {  // 좌로 오는 경우
        map[0][i] = map[0][i+1];
    }
    for(int i = 0; i < upX; i++) { // 위로 오는경우
        map[i][C-1] = map[i+1][C-1];
    }
    for(int i = C-1; i > 0; i--) {  // 우로 오는 경우
        map[upX][i] = map[upX][i-1] == -1 ? 0 : map[upX][i-1];
    }

    int downX = cleaner[1].first;
    // 아래쪽: 우-아래-좌-위 (로직은 반대로 탐색한다)
    for(int i = downX+1; i < R-1; i++) { // 위로 오는경우
        map[i][0] = map[i+1][0];
    }
    for(int i = 0; i < C-1; i++) {  // 좌로 오는 경우
        map[R-1][i] = map[R-1][i+1];
    }
    for(int i = R-1; i > downX; i--) { // 아래로 오는경우
        map[i][C-1] = map[i-1][C-1];
    }
    for(int i = C-1; i > 0; i--) {  // 우로 오는 경우
        map[downX][i] = map[downX][i-1] == -1 ? 0 : map[downX][i-1];
    }

}

int main() {
    int answer = 0;

    scanf("%d %d %d", &R, &C, &T);

    for(int i = 0; i < R; i++) {
        for(int j = 0; j < C; j++) {
            cin >> map[i][j];
            if(map[i][j] == -1) {   // 청소기 위치 저장
                cleaner.push_back({i,j});
            }
        }
    }

    // T 시간까지 미세먼지확산 후, 진공청소기를 작동시킨다. (위: 우-위-좌-아래 / 아래: 우-아래-좌-위)
    for(int i = 0 ; i < T; i++) {

        // 변수 저장값 초기화 및 미세먼지 위치 추적
        initValues();

        // 미세먼지를 확산시킨다.
        for(pair<int,int> dustPos : dust) {
            spreadDust(dustPos.first, dustPos.second);
        }
        // 확산시킨후의 최종 값을 map에 저장한다.
        for(int i = 0; i < R; i++) {
            for (int j = 0; j < C; j++) {
                map[i][j] += afterSpread[i][j];
            }
        }

        // 진공청소기를 돌린다.
        cleanDust();
    }

    // 남은 미세먼지 개수를 센다.
    for(int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) {
            if(map[i][j] > 0) {
                answer += map[i][j];
            }
        }
    }
    cout << answer;
}