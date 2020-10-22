/**
 * [ 가중치 그래프 최소경로 : Kruskal 알고리즘 ]
 * https://programmers.co.kr/learn/courses/30/lessons/42861
 *
 *
 * cf)
 * 1. MST(최소신장트리)의 Kruskal 알고리즘
 * https://gmlwjd9405.github.io/2018/08/28/algorithm-mst.html
 *
 * 2. 그래프 사이클 존재 확인 : Union-Find 알고리즘
 * https://gmlwjd9405.github.io/2018/08/31/algorithm-union-find.html
 *
 */
#include <iostream>
#include <cstdio>
#include <vector>
#include <queue>
#include <algorithm>
#include <cstdlib>

using namespace std;


int group[101];

int findParent(int n) {

    // 1. 현 노드의 부모를 찾는다.
    if(n == group[n]) {
        return n;
    } else {
        // 부모를 찾을때까지 반복
        return findParent(group[n]);
    }
}

void unionGroup(int x, int y) {
    // x, y 의 부모를 찾는다.
    x = findParent(x);
    y = findParent(y);

    // 두개중 값이 더 적은 쪽을 root로 하여 합친다.
    if (x < y) {
        group[y] = x;
    } else {
        group[x] = y;
    }
}

int solution(int n, vector<vector<int>> costs) {

    int answer = 0;

    // group 초기화
    for(int i = 0 ; i < n; i++) {
        group[i]= i;
    }

    // 1. 최소값 정렬: 3번째 가중치값 기준으로 오름차순 정렬
    sort(costs.begin(), costs.end(), [] (vector<int> & a, vector<int> & b) {
        return a[2] < b[2];
    });

    for(int i = 0; i < costs.size(); i++) {

        int startIdx = group[costs[i][0]], endIdx = group[costs[i][1]];

        // 2. 선택 시, 사이클이 생성되는지 확인
        int root1 = findParent(startIdx), root2 = findParent(endIdx);

        // 3. 사이클이 없다면 =>  간선 선택
        if(root1 != root2) {
            // 간선선택
            unionGroup(startIdx, endIdx);
            // 가중치값 합산
            answer += costs[i][2];
        }

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
    info.push_back(4);
    info.push_back(1);
    costs.push_back(info);
    info.clear();

    info.push_back(1);
    info.push_back(2);
    info.push_back(2);
    costs.push_back(info);
    info.clear();

    info.push_back(2);
    info.push_back(3);
    info.push_back(4);
    costs.push_back(info);
    info.clear();

//    info.push_back(0);
//    info.push_back(4);
//    info.push_back(100);
//    costs.push_back(info);
//    info.clear();

    cout << "RESULT: " << solution(5, costs) << endl;

    return 0;
}