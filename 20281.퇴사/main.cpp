#include <iostream>
#include <algorithm>
#include <queue>
#include <fstream>
#include <cstdio>

using namespace std;

/**
 * 초기에 생각없이 푼 버전임
 * @return
 */
int main() {

    int days = 0;
    vector < vector <int>> schedule;
    vector < vector <int>> answer;

    scanf("%d", &days);

    for(int i=0; i<days; i++) {
        int root1, root2;
        scanf("%d %d", &root1, &root2);
        vector <int> v2;

        v2.push_back(root1);
        if(i + root1 > days) {
            v2.push_back(0);
        } else {
            v2.push_back(root2);
        }
        schedule.push_back(v2);
        answer.push_back(v2);
    }

    for(int idx = 0; idx<days; idx++) {
        for(int next = idx + answer[idx][0]; next < days; next++) {

            if(answer[idx][1] + schedule[next][1] > answer[next][1]) {
                answer[next][1] = answer[idx][1] + schedule[next][1];
            }
        }

    }

    int maxValue = -1;
    for(vector<int> val : answer) {
        if(val[1] > maxValue) {
            maxValue = val[1];
        }
    }

    cout << maxValue;
}

