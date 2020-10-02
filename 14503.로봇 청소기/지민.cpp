/**
 * [ DFS ]
 * 문제: 14503 로봇 청소기
 *
 * https://www.acmicpc.net/problem/14503
 *
 */
#include <iostream>
#include <cstdio>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

int N, M, r, c, answer;
int map[51][51],position[4][2] = {{-1,0},{0,-1},{1,0},{0,1}}; // 북쪽(서쪽을바라봄), 서쪽(남쪽을 바라봄), 남쪽(동쪽을 바라봄), 동쪽(북쪽을바라봄)

/**
 0  0  0  0  0  0  0  0  0  0
 0 56 57 46 45 44 43 42 41  0
 0 55 48 47  0  0  0  0 40  0
 0 50 49  0  0 36 37 38 39  0
 0 51  0  0 35 34 31 30  0  0
 0 52 53 12 11 33 32 29 28  0
 0 54 14 13 10  9  0  0 27  0
 0 16 15  2  1  8  0  0 26  0
 0 17 18  3  4  7  0  0 25  0
 0 21 19 20  5  6 22 23 24  0
 0  0  0  0  0  0  0  0  0  0
 */
void dfs(int nowR, int nowC, int dir) {


    // 벽이면 끝
    if (map[nowR][nowC] == 1) return;

    // 1. 현재 위치를 청소한다.
    if(map[nowR][nowC] == 0) {
        ++answer;
        map[nowR][nowC] = answer+1;
    }


    // 2. 재 위치에서 현재 방향을 기준으로 왼쪽방향부터 차례대로 탐색을 진행
    for(int i = 1; i <= 4; i++) {

        int nR = nowR+position[(dir+1)%4][0], nC = nowC+position[(dir+1)%4][1]; // 다음 칸

        if(0<= nR && nR < N && 0<=nC && nC < M && map[nR][nC] == 0) {
            dfs(nR, nC, (dir+1)%4);
            /**
             * 다음칸으로 넘어간 경우는 나머지 방향을 탐색하지 않음
             * 이부분이 무한루프로 빠지지 않는 핵심!!
             */
            return;
        } else {
            // 청소했거나 벽이면 방향만 바꿔준다.
            dir= (dir+1)%4;
        }
    }

    // 네 방향 모두 청소했거나 벽이면 방향을 유지한채로 후진한다.
    int nR = nowR - position[dir][0], nC = nowC - position[dir][1];

    dfs(nR, nC, dir);

}

int main() {

    int dir; // 0: 북쪽, 1: 동쪽, 2: 남쪽, 3: 서쪽

    // 로봇 청소기가 있는 칸의 상태는 항상 빈 칸
    scanf("%d %d %d %d %d", &N, &M, &r, &c, &dir);
    if(dir == 1) {
        dir = 3;
    } else if(dir == 3) {
        dir = 1;
    }
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < M; j++) {
            // 빈 칸은 0, 벽은 1
            cin >> map[i][j];
        }
    }

    // 첫번째 로봇청소기 위치는 청소 처리함.
    map[r][c] = 2;
    answer++;
    dfs(r,c,dir);

    // 로봇 청소기가 청소하는 칸의 개수
    cout << answer << endl;

    return 0;
}