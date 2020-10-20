/**
 * [ 탐욕법 ]
 * 문제: 42885 구명보트
 *
 * https://programmers.co.kr/learn/courses/30/lessons/42885
 *
 */
#include <iostream>
#include <cstdio>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;


int solution(vector<int> people, int limit) {
    // 한 번에 최대 2명
    int totalSize = people.size(), answer = 0;

    // 오름차순 정렬
    sort(people.begin(), people.end());

    int i = 0, j = totalSize-1;
    for(; i <= j; i++) {

        for(; j >= i; j--) {

            if(j == i) {
                answer++;
            }
            else if(people[i] + people[j] <= limit) {
                answer++;
                j--;
                break;
            } else {
                answer++;
            }
        }
    }
    return answer;
}

int main() {

    vector<int> people;
//    people.push_back(10);
//    people.push_back(20);
//    people.push_back(30);
//    people.push_back(40);
//    people.push_back(50);
    people.push_back(50);
//    people.push_back(60);
    people.push_back(70);
    people.push_back(80);
//    people.push_back(90);

    cout << "RESULT: " << solution(people, 100) << endl;

    return 0;
}