/**
 * [ 탐욕법 ]
 * 42884 단속카메라
 * https://programmers.co.kr/learn/courses/30/lessons/42884
 *
 */
#include <iostream>
#include <cstdio>
#include <vector>
#include <queue>
#include <algorithm>
#include <cstdlib>

using namespace std;

int solution(vector<vector<int>> routes) {
    int answer = 0, cover[10001] = {0,}, coverCnt = 0, carCnt = routes.size();

    for(int i = 0; i < carCnt; i++) {
        // 거리 = 진출 지점 - 진입 지점
        routes[i].push_back(routes[i][1]-routes[i][0]);
    }

    // 거리 차이의 오름차순으로 정렬
    sort(routes.begin(), routes.end(), [](const vector<int> &a, const vector<int> &b) {
        return abs(a[2]) < abs(b[2]);
    });


    for (int idx = 0; idx < carCnt && coverCnt < carCnt; idx++) {
        int start = routes[idx][0], end = routes[idx][1];

        if (cover[idx] == 1) continue;
        for (int k = idx + 1; k < carCnt && coverCnt < carCnt; k++) {

            if (cover[k] == 1) continue;
            if ((start <= routes[k][0] && routes[k][0] <= end) || (start <= routes[k][1] && routes[k][1] <= end)
                || (routes[k][0] <= start && start <= routes[k][1]) || (routes[k][0] <= end && end <= routes[k][1])) {
                coverCnt++;
                cover[k] = 1;
            }
        }

        cover[idx] = 1;
        coverCnt++;
        answer++;
    }


    return answer;
}

int main() {

    vector<vector<int>> input;
    vector<int> info;

    info.push_back(0);
    info.push_back(1);
    input.push_back(info);
    info.clear();

    info.push_back(0);
    info.push_back(1);
    input.push_back(info);
    info.clear();

    info.push_back(1);
    info.push_back(2);
    input.push_back(info);
    info.clear();

//    info.push_back(-5);
//    info.push_back(-3);
//    input.push_back(info);
//    info.clear();

//    info.push_back(0);
//    info.push_back(4);
//    input.push_back(info);
//    info.clear();

    cout << "RESULT: " << solution(input) << endl;

    return 0;
}