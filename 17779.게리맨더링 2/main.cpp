#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

/**
 * [ 부르트포스 / 시뮬레이션 ]

 X: 3 / Y: 3 / d1: 1 / d2: 1

 * 문제: 17779 게리맨더링 2
 *
 * https://www.acmicpc.net/problem/17779
 *
 * @return
 */

int N, answer = 987654321;
int map[25][25];

void countPerson(int x, int y, int d1, int d2) {

    int population[5] = {0, };

    for(int r = 1; r <= N; r++) {
        for(int c = 1; c <= N; c++) {

            // 1번 선거구: 1 ≤ r < x+d1, 1 ≤ c ≤ y
            // (x, y), (x+1, y-1), ..., (x+d1, y-d1)
            if(r < x+d1 && c <= y && !(r >= x && c >= y-(r - x))) {
                population[0] += map[r][c];
            }
            // 2번 선거구: 1 ≤ r ≤ x+d2, y < c ≤ N
            // (x, y), (x+1, y+1), ..., (x+d2, y+d2)
            else if(r <= x+d2 && y < c && !(r >= x && c <= y+(r-x))) {
                population[1] += map[r][c];
            }
            // 3번 선거구: x+d1 ≤ r ≤ N, 1 ≤ c < y-d1+d2
            // (x+d1, y-d1), (x+d1+1, y-d1+1), ... (x+d1+d2, y-d1+d2)
            else if(x+d1 <= r && c < y-d1+d2 && !(r <= x+d1+d2 && c>= y-d1+d2-(x+d1+d2-r))) {
                population[2] += map[r][c];
            }
            // 4번 선거구: x+d2 < r ≤ N, y-d1+d2 ≤ c ≤ N
            // (x+d2, y+d2), (x+d2+1, y+d2-1), ..., (x+d2+d1, y+d2-d1)
            else if(x+d2 < r && y-d1+d2 <= c && !(r <= x+d2+d1 && c <= y-d1+d2+(x+d1+d2-r))) {
                population[3] += map[r][c];
            }
            // 5번 선거구
            else {
                population[4] += map[r][c];
            }
        }
    }



    int minVal = 987654321, maxVal = -1;
    for(int i = 0; i < 5; i++) {
        minVal = min(minVal, population[i]);
        maxVal = max(maxVal, population[i]);
    }

    if(answer > maxVal-minVal) {
        answer = maxVal-minVal;
    }
}

int main() {
    scanf("%d", &N);

    for(int i = 1; i <= N; i++) {
        for(int j = 1; j <= N; j++) {
            cin >> map[i][j];
        }
    }

    // d1, d2 ≥ 1
    for(int d1 = 1; d1 <= N; d1++) { // d1
        for(int d2 = 1; d2 <= N; d2++) {   // d2
            // 1 ≤ x < x+d1+d2 ≤ N
            for(int x = 1; x+d1+d2 <= N; x++) {   // x
                // 1 ≤ y-d1 < y < y+d2 ≤ N
                for(int y = 1; y+d2 <= N; y++) {  // y
                    if(1 <= y-d1) {
                        countPerson(x, y, d1, d2);
                    }
                }
            }
        }
    }

    cout << answer;
}