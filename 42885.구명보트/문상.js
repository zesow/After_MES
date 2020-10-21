function solution(people, limit) {
    let answer = 0;
    
    people.sort((a,b) => b - a);
    
    let lIdx = 0;
    let rIdx = people.length - 1;
    while (lIdx < rIdx) {
        if (people[lIdx] + people[rIdx] <= limit) {
            lIdx++;
            rIdx--;
        }
        else {
            lIdx++;
        }
        
        answer++;
    }
    
    // 교차되었으면 끝까지 처리 된 것, 같으면 한 명 남은 것.
    if (lIdx === rIdx)
        answer++;
    
    return answer;
}