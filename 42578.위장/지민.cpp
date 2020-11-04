/**
 * [ 해시 ]
 * 문제: 42578 위장
 *
 * https://programmers.co.kr/learn/courses/30/lessons/42578
 */
#include <iostream>
#include <cstdio>
#include <vector>
#include <queue>
#include <map>
#include <algorithm>

using namespace std;

int solution(vector<vector<string>> clothes) {

    map<string, int> clothesMap; // string: 옷 종류, int: 옷 개수
    int answer = 1;

    for(vector<string> clothe : clothes) {

        auto idx = clothesMap.find(clothe[1]);

        // key값이 존재하는 경우
        if(idx != clothesMap.end()) {
            idx->second++;
        }
        // 존재하지 않는 경우: 값이 없으면 clothesMap.end() 끝을 가리킨다
        else {
            clothesMap.insert({clothe[1], 1});
        }
    }

    // (한 옷의 종류수 + 1(안입는경우의수))* (한 옷의 종류수 + 1(안입는경우의수)) * ..... * (한 옷의 종류수 + 1(안입는경우의수)) -(아무것도 안 입는경우의수)
    for(auto value : clothesMap) {
        answer *= (value.second+1);
    }

    // 모두 입지 않는 경우 1 제외
    return answer-1;
}

int main() {

    cout << solution({{"crow_mask", "face"}, {"blue_sunglasses", "face"}, {"smoky_makeup", "face"}}) << endl;

    return 0;
}