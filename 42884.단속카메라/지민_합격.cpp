/**
 * [ 탐욕법 ]
 * 문제: 42884 단속카메라
 *
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
    int answer = 1, carCnt = routes.size();

    // 두번째값 기준 오름치순으로 정렬
    // => x좌표를 쭉 그려보면 알수있다 (범위 나타내는 X좌표 그래프 참고)
    sort(routes.begin(), routes.end(), [] (const vector<int> &a, const vector<int> &b) {
        return a[1] < b[1];
    });

    int cctv = routes[0][1]; // CCTV위치
    for(int i = 1; i < carCnt; i++) {

        // 범위에 포함되지 않는 경우
        if(routes[i][0] > cctv) {
            // CCTV 위치변경
            cctv = routes[i][1];
            // CCTV 추가
            answer++;
        }
    }

    return answer;
}

int main() {

    vector<vector<int>> input;
    vector<int> info;

    info.push_back(-20);
    info.push_back(15);
    input.push_back(info);
    info.clear();

    info.push_back(-14);
    info.push_back(-5);
    input.push_back(info);
    info.clear();

    info.push_back(-18);
    info.push_back(-13);
    input.push_back(info);
    info.clear();

    info.push_back(-5);
    info.push_back(-3);
    input.push_back(info);
    info.clear();

//    info.push_back(0);
//    info.push_back(4);
//    input.push_back(info);
//    info.clear();

    cout << "RESULT: " << solution(input) << endl;

    return 0;
}