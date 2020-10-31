function solution(n, times) {
    let answer = times[times.length - 1] * n;
    
    times.sort((a,b) => a - b);
    
    let left = 0;
    let right = times[times.length - 1] * n;    
    let guessedTime;
    let doneJob;
    
    // left와 right를 조절하면서 추정 시간을 최소로 만들어 나간다.
    while (left <= right) {
        
        guessedTime = Math.floor((left + right) / 2);
        doneJob = 0;
        
        // 해당 추정 시간에 할수 있는 일의 총 양.
        for (let time of times) {
            doneJob += Math.floor(guessedTime / time);
        }
        
        // 할수 있는 일의 총 양이 사람 수보다 적으면 추정 시간을 너무 작게 잡았다는 뜻이므로 더 늘려준다 === left를 오른쪽으로
        if (doneJob < n) {
            left = guessedTime + 1;
        }
        else {
            
            // 현재까지 추정 시간 중 가장 작은것보다 더 작으면 이거를 답으로 해 줌.
            if(answer > guessedTime) {
                answer = guessedTime;
            }
            
            // 만족하지 않고, 더 작은 시간을 찾기 위해 추정 시간을 줄여본다 === right를 왼쪽으로
            right = guessedTime - 1;
        }
        
    }
    
    return answer;
}