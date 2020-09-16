#include <iostream>
#include <algorithm>
#include <queue>
#include <fstream>
#include <stack>
#include <cstdio>

using namespace std;

/**
 * 문제: 13460 구슬 탈출 2
 * https://www.acmicpc.net/problem/13460
 *
 * @return
 */

int N, M, answer = 987654321;
char map[15][15];
int visited[15][15];
int visitedB[15][15];
int pos[4][4] = {{0,1}, {0,-1}, {1,0}, {-1,0}}; // 오른쪽, 왼쪽, 아래, 위

void dfs(int xR, int yR, int xB, int yB, int posIdx, int cnt, char copyMap[15][15], int copyVisitR[15][15], int copyVisitB[15][15]) {

    // 중요한 포인트! 10이상이면 의미없기 때문에, 여기넣어주면 시간 빠짐
    if(cnt > 10) {
        return;
    }
//    cout << " \nDFS 탐색 시작 / 위치: " << posIdx << " / cnt : "  << cnt << endl;
//    cout << "지금있는 VALUE"<< endl;
//    cout << "xR : " << xR << " / yR : "<< yR << " / xB : " <<  xB << " / yB : " << yB << endl;

    // 배열의 경우 이전꺼를 그대로 가져오게됨(재귀호출 종료후에도 이전것을 들고옴).. 따라서 복사본 떠줌
    char moveMap[15][15];
    int ckVisit[15][15];
    int ckVisitB[15][15];
    for(int x=0; x<N; x++) {
        for (int y = 0; y < M; y++) {
            moveMap[x][y] = copyMap[x][y];
            ckVisit[x][y] = copyVisitR[x][y];
            ckVisitB[x][y] = copyVisitB[x][y];
//            cout << moveMap[x][y];
        }
//        cout << endl;
    }

    // 더이상 가지 못할때까지 구슬을 굴린다.
    do {

        int nextXR = xR + pos[posIdx][0], nextYR = yR + pos[posIdx][1];
        // 빨간공
        if(moveMap[xR][yR] != 'O' && moveMap[xR + pos[posIdx][0]][yR + pos[posIdx][1]] == '.') {
            // R 공 위치를 옮긴다.
            moveMap[xR][yR] = '.';
            xR = nextXR; yR = nextYR; // position 변경
            moveMap[nextXR][nextYR] = 'R';
        } else if(moveMap[nextXR][nextYR] == 'O') {
            moveMap[xR][yR] = '.';
            xR = nextXR; yR = nextYR; // position 변경
//            break; => 반례에 걸림.
        }

        int nextXB = xB + pos[posIdx][0], nextYB = yB + pos[posIdx][1];
        // 파란공
        if(moveMap[nextXB][nextYB] == '.') {
            // B공 위치를 옮긴다.
            moveMap[xB][yB] = '.';
            xB = nextXB; yB = nextYB; // position 변경
            moveMap[nextXB][nextYB] = 'B';

        } else if(moveMap[nextXB][nextYB] == 'O') {
//            moveMap[xB][yB] = '.';
            xB = nextXB; yB = nextYB; // position 변경
            break;
        }
    } while((moveMap[xR][yR] != 'O' && moveMap[xR+ pos[posIdx][0]][yR + pos[posIdx][1]] == '.') || moveMap[xR+ pos[posIdx][0]][yR + pos[posIdx][1]] == 'O'
            || moveMap[xB+ pos[posIdx][0]][yB + pos[posIdx][1]] == '.' || moveMap[xB+ pos[posIdx][0]][yB + pos[posIdx][1]] == 'O');



//    cout << "\n=========굴린후!==========" << posIdx <<endl;
//    for(int x=0; x<N; x++) {
//        for (int y = 0; y < M; y++) {
//            cout << moveMap[x][y];
//        }
//        cout << endl;
//    }

    // 파란공이 먼저 들어가는 경우 : 종료
    if(moveMap[xB][yB] == 'O') {
//        cout << " 파란공이 먼저 빠짐!" << endl;
        return;
    }

    // 빨강공 방문 check
    if(ckVisit[xR][yR] != 1) {
        cnt++;
        ckVisit[xR][yR] = 1;    // 방문으로 체크

        // 도착인지 확인한다.
        if(moveMap[xR][yR] == 'O') {
            if(cnt <= 10 && cnt < answer) {
                answer = cnt;
            }
            return;
        }

    } else {
        if(ckVisitB[xB][yB] == 1) {
            return;
        } else {
            cnt++;
            ckVisitB[xB][yB] = 1;
        }
    }

    // 다음방문할 곳을 넣는다. 왼오른쪽, 왼쪽, 아래, 위
    // 하지 않았다면 DFS실행
    for(int i = 0; i < 4; i++ ){
//        cout << "\n========DFS들어가기전===========" << posIdx <<endl;
//        cout << "xR : " << xR << " / yR : "<< yR << " / xB : " <<  xB << " / yB : " << yB << endl;
//        for(int x=0; x<N; x++) {
//            for (int y = 0; y < M; y++) {
//                cout << moveMap[x][y];
//            }
//            cout << endl;
//        }
        dfs(xR, yR, xB, yB, i, cnt, moveMap, ckVisit, ckVisitB);
    }
}

int main() {
    int xR, yR, xB, yB;
    // 입력값 받는 부분
    scanf("%d %d ", &N, &M);
    for(int x=0; x < N; x++) {
        for(int y=0; y < M; y++) {
//            scanf("%c", &map[x][y]);
            cin >> map[x][y];
            // R, B 위치
            if(map[x][y] == 'R') {
                xR = x; yR = y;
            } else if(map[x][y] == 'B') {
                xB = x; yB = y;
            }
        }
    }

//    vector<int> visPos = {xR, yR};
//    stackPos.push_back(visPos);
//    visited[xR][yR] = 1;    // 방문으로 체크


    visited[xR][yR] = 1;
    visitedB[xB][yB] = 1;
    for(int i = 0; i < 4; i++) {
//        cout << "MAIN 에서 시작합니다" << endl;
        dfs(xR, yR, xB, yB, i, 0, map, visited, visitedB);
    }
    if(answer == 987654321) {
        answer = -1;
    }
    cout << answer;
}