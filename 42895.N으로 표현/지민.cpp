/**
 * [ 동적계획법 ]
 * 문제: 42895 N으로표현
 *
 * https://programmers.co.kr/learn/courses/30/lessons/42895
 *
 */
#include <iostream>
#include <cstdio>
#include <vector>
#include <queue>
#include <algorithm>
#include <cstdlib>
#include <map>

using namespace std;


int solution(int N, int number) {
    int answer = -1;

    vector<int> dp[10]; // i개로 만들수 있는 숫자리스트 vector
    dp[1] = {N};
    dp[2] = {1, N, N+N, N*N, (N*10+N)};


    // 1~2 개 사용시 미리 처리해줌
    for(int cnt = 1; cnt <= 2; cnt++) {

        // 정답찾기
        for(int num : dp[cnt]) {
            if(num == number) {
                answer = cnt;
                break;
            }
        }
        if(answer != -1) {
            break;
        }
    }

    // N의 사용 개수
    for(int cnt = 3; cnt < 10; cnt++) {

        // 최소값으로 만들 수 있는 경우 탈출
        if(answer != -1) {
            break;
        }

        vector<int> cal;
        // N이 cnt번 반복되는 경우
        int ns = 0, mul10 = 1;
        for(int mul = 1; mul <= cnt; mul++) {
            ns += mul10*N;
            mul10 *= 10;
        }
        cal.push_back(ns);

        // 이전 숫자에서 사칙연산을 해준다.
        for(int idx = 1; idx < cnt; idx++) {

            // 예) 1개로 만들 수 있는 수 @연산@ 3개로 만들수 있는 수 => 4개로 만들 수 있는 수
            for(int i = 0; i  < dp[cnt-idx].size(); i++) {
                if(dp[cnt-idx][i] == 0) continue;
                for(int j = 0; j < dp[idx].size(); j++) {
                    if(dp[idx][j] == 0) continue;

                    // +
                    cal.push_back(dp[idx][j] + dp[cnt-idx][i]);
                    // *
                    cal.push_back(dp[idx][j] * dp[cnt-idx][i]);
                    // -
//                    if(dp[idx][j] > dp[cnt-idx][i]) {
//                        cal.push_back(dp[idx][j] - dp[cnt-idx][i]);
//                    } else
                    if(dp[idx][j] < dp[cnt-idx][i]) {
                        cal.push_back(dp[cnt-idx][i] - dp[idx][j]);
                    }
                    // /
                    if(dp[cnt-idx][i] / dp[idx][j ]> 0) {
//                        cal.push_back(dp[idx][j] / dp[cnt-idx][i]);
                        cal.push_back(dp[cnt-idx][i] / dp[idx][j]);
                    }
                }
            }
        }


        // 사칙연산 결과값의 중복 제거
        sort(cal.begin(), cal.end());
        cal.erase(unique(cal.begin(),cal.end()),cal.end());

        // 정답찾기
        for(int num : cal) {
            if(num == number) {
                answer = cnt;
                break;
            }
        }
        dp[cnt] = cal;
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

    cout << "RESULT: " << solution(5, 5) << endl;

    return 0;
}