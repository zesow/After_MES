#include <iostream>
#include <algorithm>
#include <queue>
#include <fstream>
#include <cstdio>

using namespace std;

/**
 * DP
 * @return
 */

int days = 0, answer = 0;
vector < vector <int>> schedule;

void dp(int idx, int pay) {

    if(idx == days && answer < pay) {
        answer = pay;
        return;
    }

    if(idx >= days) return;
    dp(idx+schedule[idx][0], pay+schedule[idx][1]);
    dp(idx+1, pay);

}

int main() {

    scanf("%d", &days);

    for(int i=0; i<days; i++) {
        int root1, root2;
        scanf("%d %d", &root1, &root2);
        vector <int> v2;
        v2.push_back(root1);
        v2.push_back(root2);
        schedule.push_back(v2);
    }

    dp(0, 0);
    cout << answer;
}


