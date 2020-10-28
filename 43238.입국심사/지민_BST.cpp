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

        /**
         * long long 타입으로 안해주니까 범위를 벗어나게 되면서 실패뜸
         */
        long long cnt = 0;
        for(int time: times) {
            // 어차피 나눠지는 값이 더 작은 경우는 의미없다.
            // 다만, 아직 한번도 선택하지 않은 경우는 무조건 선택하도록 한다.
            // 반례 ) 1, [2, 2] 답: 1
            if(time > answer && cnt > 0) break;
            cnt += answer/time;
        }

        /**
         * cnt == n인경우에 빠져나가면 반례에 걸림
         * 6, [6, 10] 답:24
         * 그치만 26인경우에 걸려버리게 됨.
         */
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
        }
    }

    /**
     * 1명인경우는 -1 해줘야함
     */
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