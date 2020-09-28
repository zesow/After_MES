/**
 * [ DFS & BFS ]
 * 문제: 19236 청소년 상어
 *
 * https://www.acmicpc.net/problem/19236
 */

#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <queue>
#include <list>

using namespace std;

int answer, firstFish;
int map[4][4], eatFish[17], position[9][2]={{0,0},{-1,0},{-1,-1},{0,-1},{1,-1},{1,0},{1,1},{0,1},{-1,1}};  // 위, 북서, 좌, 남서, 아래, 남동, 우, 북동
vector<vector<int>> fish;

vector<vector<int>> moveFish(int sharkX, int sharkY, vector<vector<int>> movedFish) {

//    vector<vector<int>> movedFish = copyFish;

//    cout << "물고기 이동 ======>  상어X: " << sharkX << " / 상어 Y : " << sharkY<< endl;
    // 번호가 작은 물고기부터 순서대로 이동 : 물고기들 한 칸을 이동
    for(int i = 1; i <= 16; i++) {

        vector<int> fishInfo = movedFish[i];

        int x = fishInfo[1], y = fishInfo[2], pos = fishInfo[3];
        if(eatFish[i] == 1) continue;   // 먹은 물고기는 PASS


        int nX = x + position[pos][0], nY = y+position[pos][1];

        // 이동 O : 빈 칸과 다른 물고기가 있는 칸
        if((nX != sharkX || nY != sharkY) && 0 <= nX && nX < 4 && 0 <= nY && nY < 4) {

            // 물고기가 다른 물고기가 있는 칸으로 이동할 때는 서로의 위치를 바꾸는 방식으로 이동
            if(map[nX][nY] != 0) { // 다른 물고기가 있는 경우

                int nextNumber = map[nX][nY];

                // 원래 있던 물고기 위치 변경
                movedFish[nextNumber][1] = x;
                movedFish[nextNumber][2] = y;

                // 현재 물고기 정보 변경
                movedFish[i][1] = nX;
                movedFish[i][2] = nY;

                // map 물고기 정보 변경
                map[nX][nY] = i;
                map[x][y] = nextNumber;

            } else { // 빈칸인 경우
                // 현재 물고기 정보 변경
                movedFish[i][1] = nX;
                movedFish[i][2] = nY;
                map[x][y] = 0;

                map[nX][nY] = i;
            }

        }
        // 이동 X: 상어가 있거나 OR 공간의 경계를 넘는 칸
        else {
            int beforePos = movedFish[i][3];
            // 이동방향: 이동할 수 있는 칸을 향할 때까지 방향을 45도 반시계 회전
            if(pos < 8) {   // 8 이하인 경우
                int j;
                for(j = pos+1; j < 9; j++) {

                    int newX = x + position[j][0], newY = y+position[j][1] ;
                    if(0 <= newX && newX < 4 && 0 <= newY && newY < 4) {
                        movedFish[i][3] = j;
                        break;
                    }
                }

                // 여전히 방향을 찾지 못한경우 앞에서부터 다시 돈다
                if(j >= 9) {
                    for(j = 1; j < pos; j++) {

                        int newX = x + position[j][0], newY = y+position[j][1] ;
                        if(0 <= newX && newX < 4 && 0 <= newY && newY < 4) {
                            movedFish[i][3] = j;
                            break;
                        }
                    }
                }

            } else { // 8인경우

                for(int j = 1; j < 9; j++) {

                    int newX = x + position[j][0], newY = y+position[j][1] ;
                    if(0 <= newX && newX < 4 && 0 <= newY && newY < 4) {
                        movedFish[i][3] = j;
                        break;
                    }
                }

            }

            // 이동방향이 변경되었을 경우
            if(beforePos != movedFish[i][3]) {
                i--;
                continue;   // 다시 for문 돌아서 물고기를 움직이도록 만듬
            }

            // if move불가: 이동할 수 있는 칸이 없으면 이동을 하지 않는다.

        }


    }


//    cout << "====물고기 이동 후 =====" <<  endl;
//    for(int x = 0; x < 4; x++) {
//        for (int y = 0; y < 4; y++) {
//
//            cout << map[x][y] << " ";
//        }
//        cout << endl;
//    }
//    cout << endl;
    return movedFish;
}

void moveShark(int x, int y, int sPos, int sumVal, vector<vector<int>> movedFish) {


    // 물고기 위치 이동
    vector<vector<int>> copyFish = moveFish(x, y, movedFish);  // 물고기 위치 변화

    // 배열 복사
    int copyMap[4][4];
    for(int i = 0; i < 4; i++) {
        for(int j = 0 ; j <4; j++) {
            copyMap[i][j] = map[i][j];
        }
    }

    // if 물고기 있음 THEN  물고기를 먹고, 그 물고기의 방향을 가지게 된다
    // 이동하는 중에 지나가는 칸에 있는 물고기는 먹지 않는다
    for(int i = 1; i <= 4; i++) {
        int nX = x + (position[sPos][0]*i) , nY = y+(position[sPos][1]*i);

        // 이동 X: 물고기가 없는 칸으로는 이동 불가
        if(0 <= nX && nX < 4 && 0<= nY && nY < 4) {

            /**
             * 문제 이해력..ㅠㅠ
             */
            if(map[nX][nY] == 0) continue;

            vector<int> fishInfo = copyFish[map[nX][nY]];

            // 물고기를 먹는다.
            sumVal += fishInfo[0];  // 물고기 번호 더함
            eatFish[fishInfo[0]] = 1;
            map[nX][nY] = 0; // 먹은것으로 표기
            copyMap[nX][nY] = 0;
//            cout << "먹은것 ~~~~~~~ X : " << nX << " / Y: " << nY << " / 물고기: " << fishInfo[0] << " / 방향 :" << fishInfo[3] << endl;
//            cout << "====물고기  EAT 후!!!! =====" <<  endl;
//            for(int k = 0; k < 4; k++) {
//                for (int l = 0; l < 4; l++) {
//
//                    cout << map[k][l] << " ";
//                }
//                cout << endl;
//            }
//            cout << endl;

            // DFS탐색
            moveShark(nX, nY, fishInfo[3], sumVal, copyFish);

            // 탐색했던것 초기화
            sumVal -= fishInfo[0];  // 물고기 번호 제외
            eatFish[fishInfo[0]] = 0;
            copyMap[nX][nY] = fishInfo[0];// 안먹은것으로 표기

            /**
             * 복사본 배열을 여기서 초기화 시켜주는 것이 중요
             */
            for(int k = 0; k < 4; k++) {
                for (int l = 0; l < 4; l++) {
                    map[k][l] = copyMap[k][l];
                }
            }

//cout << "==========복구============= " << endl;
////            cout << "복규 먹은것 ~~~~~~~ X : " << nX << " / Y: " << nY << " / 물고기: " << fishInfo[0] << endl;
//            for(int k = 0; k < 4; k++) {
//                for (int l = 0; l < 4; l++) {
//
//                    cout << map[k][l] << " ";
//                }
//                cout << endl;
//            }
//            cout << endl;


        } else {
//            cout << "@@@@@@@@@탐색종료@@@@@@@@@@" << endl;
//            cout << "sumVal : " << sumVal+firstFish << " / answer : " << answer << endl;
            // 탐색 종료 시, max값 확인
            answer = max(answer, sumVal+firstFish);
            return;
        }
    }

}

void sortFish() {
    // 물고기 번호 순으로 정렬
    sort(fish.begin(), fish.end(), [](const vector<int> &a, const vector<int> &b) {
        return a[0] < b[0];
    });
}

int main() {

    fish.push_back({0}); // 0 번째 인덱스 비우둔다

    for(int x = 0; x < 4; x++){
        for(int y = 0; y < 4; y++) {
//            if(x == 0 && y == 0) continue;
            int number, pos;
//            scanf("%d %d ", &number, &pos);
            cin >> number >> pos;
            // 정보 저장
            // 0: 물고기번호, 1: x, 2: y, 3: 방향
            fish.push_back({number, x, y, pos});

        }
    }

    // 물고기 번호 순으로 정렬
    sortFish();
    // map에 표기
    for(int i = 1; i < 17; i++) {
        map[fish[i][1]][fish[i][2]] = fish[i][0];   // map에 fish 벡터의 index값을 저장 시킴
    }

    // 청소년 상어는 (0, 0)에 있는 물고기를 먹고, (0, 0)에 들어가게 된다
    firstFish = fish[map[0][0]][0];
    answer = fish[map[0][0]][0];
    int sharkPos = fish[map[0][0]][3];
    map[0][0] = 0;
    eatFish[answer] = 1;

    // 시작
    moveShark(0,0,sharkPos,0, fish);

    cout << answer;

}