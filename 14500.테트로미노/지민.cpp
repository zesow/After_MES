/**
 * [ 노가다 ]
 * 문제: 14500 테트로미노
 *
 * https://www.acmicpc.net/problem/14500
 */

#include <iostream>
#include <cstdio>
#include <vector>
#include <queue>
#include <algorithm>
#include <ctime>

using namespace std;

int N, M, answer = 0;
int map[505][505];
vector<vector<pair<int,int>>> tetri[5];

void ckMaxVal(int shapeNum) {

    vector<vector<pair<int,int>>> shape = tetri[shapeNum];

    int typeSize = shape.size();

    for(int x = 0 ; x < N; x++) {
        for(int y = 0; y < M; y++) {
            for(int i = 0; i< typeSize; i++) {

                vector<pair<int,int>> pos = shape[i];

                int x1 = x+pos[0].first, x2 = x+pos[1].first, x3 = x+pos[2].first, x4 = x+pos[3].first;
                int y1 = y+pos[0].second, y2 = y+pos[1].second, y3 = y+pos[2].second, y4 = y+pos[3].second;

                if(x1 >= 0 && x2 >= 0 && x3 >= 0 && x4 >= 0 && x1 < N && x2 < N && x3 < N && x4 < N
                   && y1 >= 0 && y2 >= 0 && y3 >= 0 && y4 >= 0 && y1 < M && y2 < M && y3 < M && y4 < M) {
                    answer = max(map[x1][y1]+map[x2][y2]+map[x3][y3]+map[x4][y4], answer);
                }
            }
        }
    }


}

int main() {

    scanf("%d %d", &N, &M);

    for(int i = 0; i< N; i++) {
        for(int j = 0; j < M; j++) {
            cin >> map[i][j];
        }
    }

    vector<vector<pair<int,int>>> shape;
    vector<pair<int,int>> list;
    // ㅁ
    list.push_back({0,0});
    list.push_back({0,1});
    list.push_back({1,0});
    list.push_back({1,1});
    shape.push_back(list);
    list.clear();

    tetri[0] = shape;
    shape.clear();


    // -
    list.push_back({0,0});
    list.push_back({1,0});
    list.push_back({2,0});
    list.push_back({3,0});
    shape.push_back(list);
    list.clear();

    list.push_back({0,0});
    list.push_back({0,1});
    list.push_back({0,2});
    list.push_back({0,3});
    shape.push_back(list);
    list.clear();

    tetri[1] = shape;
    shape.clear();

    // L
    list.push_back({0,0});
    list.push_back({1,0});
    list.push_back({2,0});
    list.push_back({2,1});
    shape.push_back(list);  // L
    list.clear();

    list.push_back({0,1});
    list.push_back({1,1});
    list.push_back({2,1});
    list.push_back({2,0}); // L반대
    shape.push_back(list);
    list.clear();

    list.push_back({0,0});
    list.push_back({1,0});
    list.push_back({1,1});
    list.push_back({1,2}); // 긴 ㄴ
    shape.push_back(list);
    list.clear();

    list.push_back({0,2});
    list.push_back({1,2});
    list.push_back({1,1});
    list.push_back({1,0});  // 긴 ㄴ반대
    shape.push_back(list);
    list.clear();

    list.push_back({0,0});
    list.push_back({0,1});
    list.push_back({0,2});
    list.push_back({1,2});  // 긴 ㄱ
    shape.push_back(list);
    list.clear();

    list.push_back({0,0});
    list.push_back({0,1});
    list.push_back({0,2});
    list.push_back({1,0});
    shape.push_back(list);  // 긴 ㄱ반대
    list.clear();

    list.push_back({0,0});
    list.push_back({0,1});
    list.push_back({1,1});
    list.push_back({2,1});  // 짧은 ㄱ
    shape.push_back(list);
    list.clear();

    list.push_back({0,0});
    list.push_back({0,1});
    list.push_back({1,0});
    list.push_back({2,0});
    shape.push_back(list);  // 짧은 ㄱ반대
    list.clear();

    tetri[2] = shape;
    shape.clear();

    // ㄹ
    list.push_back({0,0});
    list.push_back({1,0});
    list.push_back({1,1});
    list.push_back({2,1});
    shape.push_back(list);  // 원상태
    list.clear();

    list.push_back({0,1});
    list.push_back({0,2});
    list.push_back({1,0});
    list.push_back({1,1});
    shape.push_back(list);  // Z반대
    list.clear();

    list.push_back({0,1});
    list.push_back({1,1});
    list.push_back({1,0});
    list.push_back({2,0});
    shape.push_back(list);  // 원상태 반대
    list.clear();

    list.push_back({0,0});
    list.push_back({0,1});
    list.push_back({1,1});
    list.push_back({1,2});
    shape.push_back(list);  //  Z
    list.clear();

    tetri[3] = shape;
    shape.clear();

    // ㅜ
    list.push_back({0,0});
    list.push_back({0,1});
    list.push_back({0,2});
    list.push_back({1,1});
    shape.push_back(list);
    list.clear();

    list.push_back({1,0});
    list.push_back({1,1});
    list.push_back({1,2});
    list.push_back({0,1});
    shape.push_back(list); // ㅗ
    list.clear();

    list.push_back({0,1});
    list.push_back({1,0});
    list.push_back({1,1});
    list.push_back({2,1});
    shape.push_back(list); // ㅓ
    list.clear();

    list.push_back({0,0});
    list.push_back({1,0});
    list.push_back({2,0});
    list.push_back({1,1});
    shape.push_back(list); // ㅏ
    list.clear();

    tetri[4] = shape;
    shape.clear();

    for(int i = 0;i <5; i++) {
        ckMaxVal(i);
    }
    cout << answer << endl;
}
