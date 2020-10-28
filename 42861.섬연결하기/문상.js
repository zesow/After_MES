let group;

function solution(n, costs) {
    
    let answer = 0;

    // group 초기화
    group = Array.from({length : 101},(v,i) => i);
    
    // 1. 최소값 정렬: 3번째 가중치값 기준으로 오름차순 정렬
    costs.sort((a,b) => a[2] - b[2]);
    
    
    for (let cost of costs) {
        const startIdx = cost[0];
        const endIdx = cost[1];
        
        // 2. 선택 시, 사이클이 생성되는지 확인(부모 동일 여부)
        const root1 = findParent(startIdx);
        const root2 = findParent(endIdx);
        
        // 3. 사이클이 없다면 간선 선택
        if (root1 !== root2) {
            unionGroup(startIdx, endIdx);
            answer += cost[2];
        }
    }
    
    return answer;
}

function findParent(idx) {
    
    // 1. 현 노드의 부모를 찾는다.
    if (idx === group[idx])
        return idx;
    
    // 부모를 찾을때까지 반복
    return findParent(group[idx]);
}

function unionGroup(x, y) {
    // x, y의 부모를 찾는다.
    x = findParent(x);
    y = findParent(y);
    
    // 두 개중 값이 더 적은 쪽을 root 로 하여 합친다.
    if (x < y) {
        group[y] = x;
    }
    else {
        group[x] = y;
    }
}