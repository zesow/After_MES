/**
 * [ 그리디 ]
 * 문제: 11047 동전 0
 *
 * https://www.acmicpc.net/problem/11047
 */
#include <iostream>
#include <cstdio>
#include <vector>
#include <queue>
#include <algorithm>
#include <set>

using namespace std;

int N, K, answer, coins[10];
vector<vector<int>> coinComb;   // i개 코인을 사용해서 만들 수 있는 금액의 list

int bfs(int value) {

    int idx = 0;
    for(;idx < N; idx++) {
        if(coins[idx] >= value) {
            if(coins[idx] > value) {
                idx--;
            }
            break;
        }
    }

    if(idx == N) idx--;

    return idx;
}

void choice() {

    // 1. 현금액보다 작은 coin 중 가장 큰 coin 선택
    int idx = bfs(K);

    // 2. 해당 coin을 몇개 사용해야하는지 조사
    int cnt = 1;
    while(1) {
        // 금액이 커지거나 같아지면 종료
        if(K <= coins[idx]*cnt) {
            // 금액이 큰경우에는 사용갯수를 줄임
            if(K < coins[idx]*cnt) {
                cnt--;
            }
            break;
        }

        cnt++;
    }


    // 사용갯수 더해줌
    answer += cnt;

    // 3. 사용한 금액만큼 K에서 제외
    K -= coins[idx]*cnt;


}
int main() {

    // N종류 , 그 가치의 합을 K로 (1 ≤ N ≤ 10, 1 ≤ K ≤ 100,000,000)
    cin >> N >> K;
    vector<int> coinList;
    for(int i = 0; i < N; i++) {
        cin >> coins[i];
        coinList.push_back(coins[i]);

        // 동전 1개로 이미 만들 수 있는 경우
        if(coins[i] == K) answer = 1;
    }

    coinComb.push_back({0});    // 0개 사용시 만들 수 있는 금액: 0
    coinComb.push_back(coinList); // 1개 사용시 만들 수 있는 금액

    // 최소 개수 탐색
    while(K > 0) {
        choice();
    }

    // 동전 개수의 최솟값
    cout << answer << endl;

    return 0;
}