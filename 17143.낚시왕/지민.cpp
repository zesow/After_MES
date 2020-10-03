/**
 * [  ]
 * 문제: 17143 낚시왕
 *
 * https://www.acmicpc.net/problem/17143
 *
 */
#include <iostream>
#include <cstdio>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

int R,C,M, answer, position[5][2] = {{0,0},{-1,0},{1,0},{0,1},{0,-1}}; // 1: 위, 2: 아래, 3: 오른쪽, 4: 왼쪽
vector<int> map[105][105];


void moveShark() {

    // 복사본
    vector<int> copyMap[105][105];

    // 상어 이동
    for(int r = 1; r <= R; r++) {
        for(int c = 1;c <= C; c++) {

            // 상어가 없는 칸은 PASS
            if(map[r][c].size() == 0) continue;

            // 다음 좌표 위치
            int nextX = r, nextY = c, pos = map[r][c][1], cnt = map[r][c][0];

            while(cnt > 0) {

                int nR = nextX + position[pos][0]*cnt, nC = nextY + position[pos][1]*cnt;

                // 좌표안의 범위인 경우, 좌표위치 변경
                if(1 <= nR && nR <= R && 1 <= nC && nC <= C) {
                    nextX = nR; nextY = nC;
                    cnt = 0;
                } else {    // 방향 및 위치 변경

                    if(pos == 1) { // 방향: 위
                        cnt -= (nextX-1);
                        nextX = 1;
                        pos = 2;
                    } else if(pos == 2) { // 방향: 아래
                        cnt -= (R-nextX);
                        nextX = R;
                        pos = 1;
                    } else if(pos == 3) { // 방향: 오른쪽
                        cnt  -= (C-nextY);
                        nextY = C;
                        pos = 4;
                    } else if(pos == 4) { // 방향: 왼쪽
                        cnt -= (nextY-1);
                        nextY = 1;
                        pos = 3;
                    }
                }

            }

            // 이미 상어가 존재하는 경우, 큰 상어를 냅둔다.
            if(copyMap[nextX][nextY].size() == 0 || copyMap[nextX][nextY][2] < map[r][c][2]) {
                copyMap[nextX][nextY].clear();  // 이전값이 남아있을 수 있기에, 비워주고 시작한다.

                copyMap[nextX][nextY].push_back(map[r][c][0]);
                copyMap[nextX][nextY].push_back(pos);
                copyMap[nextX][nextY].push_back(map[r][c][2]);
            }

        }
    }

    // 원본에 이동한 상어 엎어침
//    cout << "\n==========AFTER==========" << endl;
    for(int r = 1; r <= R; r++) {
        for(int c = 1;c <= C; c++) {
            map[r][c] = copyMap[r][c];

//            if(map[r][c].size() == 0) {
//                cout << "0 ";
//            } else {
//                cout << map[r][c][2] << " ";
//            }
        }
//        cout << endl;
    }

}

int main() {

    scanf("%d %d %d", &R, &C, &M);

    for(int i = 0; i<M; i++) {

        int r, c, s, d, z; // s는 속력, d는 이동 방향, z는 크기

        scanf("%d %d %d %d %d", &r, &c, &s, &d, &z);

        map[r][c].push_back(s); // 움직이는 칸의 갯수
        map[r][c].push_back(d); // d가 1인 경우는 위, 2인 경우는 아래, 3인 경우는 오른쪽, 4인 경우는 왼쪽
        map[r][c].push_back(z); // 상어크기
    }

    // 1. 낚시왕이 오른쪽으로 한 칸 이동한다.
    for(int person = 1; person <= C; person++) {

        // 먹을 상어가 없는 경우는 종료한다.
        if(M == 0) break;

        // 2. 낚시왕이 있는 열에 있는 상어 중에서 땅과 제일 가까운 상어를 잡는다. 상어를 잡으면 격자판에서 잡은 상어가 사라진다.
        for(int i = 1; i <= R; i++) {
            if(map[i][person].size() > 0) {
                M--;
                answer += map[i][person][2]; // 상어크기를 더해줌
                map[i][person].clear();


//                // 원본에 이동한 상어 엎어침
//                cout << "\n==========상어 먹은 후==========" << endl;
//                for(int r = 1; r <= R; r++) {
//                    for(int c = 1;c <= C; c++) {
//                        if(map[r][c].size() == 0) {
//                            cout << "0 ";
//                        } else {
//                            cout << map[r][c][2] << " ";
//                        }
//                    }
//                    cout << endl;
//                }

                break;
            }
        }


        // 3. 상어가 이동한다.
        moveShark();
    }

    cout << answer << endl;

    return 0;
}