/**
 * [ 동적계획법 ]
 * 문제: 43105 정수삼각형
 *
 * https://programmers.co.kr/learn/courses/30/lessons/43105
 *
 */
#include <iostream>
#include <cstdio>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;
int map[501][501];
int solution(vector<vector<int>> triangle) {
    int answer = 0, lasRow = triangle.size();

    map[0][0] = triangle[0][0];

    for(int x = 1; x < lasRow; x++) {
        for(int y = 0; y < triangle[x].size(); y++) {
            // [x][y] 에서 접근가능한 수 : [x-1][y-1], [x-1][y]
            if(y == 0) {
                map[x][y] = triangle[x][y] + map[x-1][y];
            } else {
                map[x][y] = triangle[x][y] + max(map[x-1][y-1], map[x-1][y]);
            }
        }
    }

    // 거쳐간 숫자의 최댓값
    for(int y = 0; y < lasRow; y++) {
        answer = max(answer, map[lasRow-1][y]);
    }
    return answer;
}

int main() {

    vector<vector<int>> input;
    vector<int> info;

    info.push_back(7);
    input.push_back(info);
    info.clear();

    info.push_back(3);
    info.push_back(8);
    input.push_back(info);
    info.clear();

    info.push_back(8);
    info.push_back(1);
    info.push_back(0);
    input.push_back(info);
    info.clear();

    info.push_back(2);
    info.push_back(7);
    info.push_back(4);
    info.push_back(4);
    input.push_back(info);
    info.clear();

    info.push_back(4);
    info.push_back(5);
    info.push_back(2);
    info.push_back(6);
    info.push_back(5);
    input.push_back(info);
    info.clear();

    cout << "RESULT: " << solution(input) << endl;

    return 0;
}