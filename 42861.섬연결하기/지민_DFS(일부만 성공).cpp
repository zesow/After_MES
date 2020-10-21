/**
 * [ 가중치 그래프 최소경로 : DFS ]
 * 문제: 42861 섬연결하기
 *
 * https://programmers.co.kr/learn/courses/30/lessons/42861
 *
 */
#include <iostream>
#include <cstdio>
#include <vector>
#include <queue>
#include <algorithm>
#include <cstdlib>

using namespace std;


int map[101][101], N, answer = 987654321, visit[101];

int checkVisit() {
    int cnt = 0;
    for(int i = 0; i< N; i++) {
        if(visit[i] != 0) cnt++;
    }
    return cnt;
}
void dfs(int idx, int sum) {

    if(sum > answer) { // 최소값을 넘어서면 그대로 종료
        return;
    }

    // 시작점으로 되돌아왔다면 종료
    int cnt = checkVisit();
    if(cnt == N) {
        answer = min(answer,sum);
//        cout << "최소값: " << answer << endl;
        return;
    }

    for(int j = 0; j < N; j++) {

        // 이미 방문했거나 or 길이 없는 경우는 PASS
        if(visit[j] != 0 || map[idx][j] == 0) continue;

        visit[j] = 1;
//        cout << idx << " => " << j << " / SUM: " << sum+map[idx][j] << endl;
        dfs(j, sum+map[idx][j]);
        visit[j] = 0;
    }

    if(cnt == N-1) {
        for(int i = 0; i< N; i++) {
            if(visit[i] == 0) {
                int k;
                for(k = 0; k < N; k++) {
                    if(map[i][k] > 0) {
                        break;
                    }
                }
//                cout << i << " => " << k << " / SUM: " << sum+map[i][k] << endl;
                visit[i] = 1;
                dfs(i, sum+map[i][k]);
                visit[i] = 0;
            }
        }
    }

}
int solution(int n, vector<vector<int>> costs) {

    N = n;
    // 경로 표기
    for(int i = 0; i < costs.size(); i++) {
        map[costs[i][0]][costs[i][1]] = map[costs[i][1]][costs[i][0]] = costs[i][2];
    }

    for(int i = 0; i < n; i++) {
        visit[i] = 1;
//        cout << "여기 시작 : " << i << endl;
        dfs(i, 0);
        visit[i] = 0;
    }

    return answer;
}

int main() {

    vector<vector<int>> costs;
    vector<int> info;

    info.push_back(0);
    info.push_back(1);
    info.push_back(1);
    costs.push_back(info);
    info.clear();

    info.push_back(3);
    info.push_back(1);
    info.push_back(1);
    costs.push_back(info);
    info.clear();

    info.push_back(0);
    info.push_back(2);
    info.push_back(2);
    costs.push_back(info);
    info.clear();

    info.push_back(0);
    info.push_back(3);
    info.push_back(2);
    costs.push_back(info);
    info.clear();

    info.push_back(0);
    info.push_back(4);
    info.push_back(100);
    costs.push_back(info);
    info.clear();

    cout << "RESULT: " << solution(5, costs) << endl;

    return 0;
}