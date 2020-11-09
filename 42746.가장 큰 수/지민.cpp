/**
 * [ 정렬 ]
 * 문제: 42746 가장 큰 수
 *
 * https://programmers.co.kr/learn/courses/30/lessons/42746
 */
#include <iostream>
#include <cstdio>
#include <vector>
#include <queue>
#include <algorithm>


using namespace std;

string solution(vector<int> numbers) {

    string answer = "";

    sort(numbers.begin(), numbers.end(), [] (const int a, const int b) {

        string aStr = to_string(a), bStr = to_string(b);
        int aLth = aStr.size(), bLth = bStr.size();
        int lth = aLth > bLth ? aLth : bLth;
        for(int idx = 0; idx < lth; idx++) {
            if(aLth <= idx){
                return aStr+bStr > bStr+aStr ? true : false;
            }
            else if(bLth <= idx) {
                return bStr+aStr > aStr+bStr ? false : true;
            }
            else if(aLth > idx && bLth > idx) {
                if(aStr[idx] > bStr[idx]) return true;
                else if(aStr[idx] < bStr[idx]) return false;
            }
        }
    });

    int size = numbers.size();
    for(int i = 0; i < size; i++) {
        answer += to_string(numbers[i]);
    }

    if(answer[0] == '0') answer = "0";

    return answer;
}

int main() {

    // 최소 이동 횟수, 이동할 수 없는 경우에는 -1을 출력
    cout << solution({40, 403}) << endl;

    return 0;
}