/**
 * [ 탐욕법 ]
 * 문제: 42860 조이스틱
 *
 * https://programmers.co.kr/learn/courses/30/lessons/42860
 *
 */
#include <iostream>
#include <cstdio>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

int solution(string name) {

    int answer = 0, cntA = 0, length = name.length();

    for(int i = 0; i < name.length(); i++) {
        if(name[i] == 'A') cntA++;
    }

    int idx = 0;
    while(cntA < length) {

        if(name[idx] != 'A') {

            // 현자 글자에서 A로 바꿀수있는 최소한의 움직임
            int minCnt = min(name[idx]-'A', 'Z'-name[idx]+1);
            answer += minCnt;
            cntA++;
            name[idx] = 'A';
        }

        // 다음 글자위치 탐색
        if(cntA < length) {
            // 순차 탐색
            int cnt1 = 0;
            int nextIndx1 = idx+1 < length ? idx+1 : 0;
            for(; nextIndx1 < length; nextIndx1++) {
                cnt1++;
                if(name[nextIndx1] != 'A') break;

                if(nextIndx1 == length-1) {
                    nextIndx1 = -1;
                }
            }

            // 역순 탐색
            int cnt2 = 0;
            int nextIndx2 = idx-1 < 0 ? length-1 : idx-1;
            for(;nextIndx2 >= 0; nextIndx2--) {
                cnt2++;
                if(name[nextIndx2] != 'A' || cnt1 < cnt2) break;
                if(nextIndx2 == 0) {
                    nextIndx2 = length;
                }
            }

            // 둘중 더 짧은 거리에 있는 글자를 택하는데, 만약 거리가 같다면 순차 탐색 우선으로!
            if(cnt1 <= cnt2) {
                idx = nextIndx1;
                answer += cnt1;
            } else {
                idx = nextIndx2;
                answer += cnt2;
            }
        }

    }
    return answer;
}

int main() {

    string name;
    cin >> name;

    int answer = solution(name);

    cout << answer << endl;

    return 0;
}