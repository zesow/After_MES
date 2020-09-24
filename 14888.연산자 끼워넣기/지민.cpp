#include <iostream>
#include <cstdio>
#include <vector>
#include <queue>
#include <algorithm>
#include <ctime>

using namespace std;

/**
 * [ 순열 ]
 * 문제: 14888 연산자 끼워넣기
 *
 * https://www.acmicpc.net/problem/14888
 *
 * @return
 */
int N, minAns = 1000000000, maxAns = -1000000000;
int map[12]; // map: A1~AN
vector<vector<int>> operList;  // 순열 경우의수

void calculation() {

    for(int k = 0; k < operList.size(); k++) {
        vector<int> oper = operList[k];
        int sum = map[0];

        for(int i = 0; i< N-1; i++) {
            switch (oper[i]) {
                case 0:
                    sum += map[i+1];
                    break;
                case 1:
                    sum -= map[i+1];
                    break;
                case 2:
                    sum *= map[i+1];
                    break;
                case 3:
                    sum /= map[i+1];
                    break;
            }
        }

        maxAns = max(sum, maxAns);
        minAns = min(sum, minAns);

    }

}

int main() {

    vector<int> operP;  // 연산자 개수대로 연산자들을 모두 풀어서 넣는 것. + , -, *, /

    scanf("%d", &N);
    for(int i = 0; i< N; i++) {
        cin >> map[i];
    }
    for(int i = 0; i < 4; i++) {
        int cnt;
        cin >> cnt;
        for(int j = 0; j < cnt; j++) {
            if(i == 0) {    // +
                operP.push_back(0);
            } else if(i == 1) { // -
                operP.push_back(1);
            } else if(i == 2) { // *
                operP.push_back(2);
            } else if(i == 3) { // /
                operP.push_back(3);
            }
        }
    }


    // 순열 탐색(모든 경우의수를 넣는다)
    do {

        vector<int> list;
        for(int i = 0; i< N-1; i++) {
            list.push_back(operP[i]);
        }
        operList.push_back(list);

    } while(next_permutation(operP.begin(), operP.end()));


    calculation();
    cout << maxAns << endl << minAns << endl;
}
