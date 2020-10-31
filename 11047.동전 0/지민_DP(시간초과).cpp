/**
 * [  ]
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

void dp() {

    int cnt = 1;
    while(answer == 0) {

        // cnt개수로 만들 수 있는 동전의 합 구하기
        set<int> coinList;
        for(int i = N-1; i >= 0; i--) {
            int size = coinComb[cnt].size();

            for(int j = 0; j < size; j++) {
                coinList.insert(coinComb[cnt][j]+coins[i]);

                // 정답이 나왔다면 -> 탈출
                if(coinComb[cnt][j]+coins[i] == K) {
                    answer = cnt+1;
                    break;
                }
            }
            if(answer != 0) break;
        }

        /**
         * vector의 원속 중복제거 방벙
         *
         * 1. 오름차순 정렬
         * 2. 중복제거 => unique
         */
//        sort(coinList.begin(), coinList.end());
//        coinList.erase(unique(coinList.begin(), coinList.end()),coinList.end());
        vector<int> v;
        v.assign(coinList.begin(), coinList.end());
        coinComb.push_back(v);

        cnt++;
    }
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

    // 최소개수 탐색
    if(answer == 0) {
        dp();
    }

    // 동전 개수의 최솟값
    cout << answer << endl;

    return 0;
}