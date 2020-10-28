/**
 * [ 이분탐색(BST) ]
 * 문제: 43238 입국심사
 *
 * https://www.acmicpc.net/problem/43238
 *
 */
#include <iostream>
#include <cstdio>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

long long solution(int n, vector<int> times) {
    long long answer = 0;

    int timeSize = times.size();

    // 오름차순 정렬
    sort(times.begin(), times.end());


    long long maxTime = times[timeSize-1]*n, minTime = 0;
    answer = maxTime/2; // 중앙값 선택

    while(1) {

        if(maxTime == minTime) {
            answer = minTime;
            break;
        }

//        cout << "시간: " << answer << endl;
        long long cnt = 0;
        for(int time: times) {
            if(time > answer && cnt > 0) break;
            cnt += answer/time;
        }

        if(cnt >= n) { // 더 작은값 선택
            maxTime = answer;
            answer /= 2;
        }
        else if(cnt < n) { // 더 큰 시간 선택
            minTime = answer;
            if((maxTime+answer)/2 == answer) {
                answer = (maxTime+answer)/2 +1;
                minTime = answer;
            } else {
                answer = (maxTime+answer)/2;
            }
        } else {
            break;
        }
    }

    if(n == 1) {
        answer--;
    }
    return answer;
}

int main() {

//    cout << "RESULT: " << solution(2,{1, 2, 2, 2, 100}) << endl;
    cout << "RESULT: " << solution(1, {2,2}) << endl;
    return 0;
}