function solution(N, number) {
    let answer = -1;
    
    const unions = new Array();
    
    if (N === number) {
        return 1;
    }
    
    unions.push(new Set());
    
    // list 에 Set 초기화 && 이어붙인 수들 넣기.
    for (let i = 1 ; i <= 8 ; i++) {
        
        const set = new Set();
        let concatedNum = '';
        
        for (let j = 0 ; j < i ; j++) {
            concatedNum += N;
        }
        
        set.add(parseInt(concatedNum));
        unions.push(set);

    }
    
    // N 1개 ~ N 8개
    for (let i = 1 ; i <= 8 ; i++) {
     
        // union[1] U union[n-1] , union[2] U union[n-2] ... 
        for (let j = 0 ; j < i ; j++) {
            
            for (let op1 of unions[j]) {
                
                for (let op2 of unions[i-j]) {
                    
                    unions[i].add(op1 + op2);
                    unions[i].add(op1 * op2);
                    unions[i].add(op1 - op2);
                    
                    if (op2 !== 0) {
                        unions[i].add(op1 / op2);
                    }
                    
                }    
                
            }
            
        }
        
        if ([...unions[i]].find(n => n === number)) {
            answer = i;
            break;
        }
        
    }
     
    return answer;
}