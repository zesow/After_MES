function solution(name) {
    let answer = 0;
    
    let candidateName = '';
    
    for(let i = 0 ; i < name.length; i++) {
        candidateName += 'A';
    }
    
    let idx = 0;
    while(true) {
        let leftDiffDistance = 1;
        let leftDiffIdx = idx - 1 < 0 ? name.length - 1 : idx - 1;
        let rightDiffDistance = 1;
        let rightDiffIdx = idx + 1;
        
        const upperGap = name[idx].charCodeAt() - candidateName[idx].charCodeAt();
        const downGap = 1 + ('Z'.charCodeAt() - name[idx].charCodeAt());
        answer += upperGap > downGap ? downGap : upperGap;
        candidateName = candidateName.substring(0, idx) + name[idx] + candidateName.substring(idx + 1);
        
        if (name === candidateName)
            break;
        
        while (leftDiffIdx !== idx) {
            if (name[leftDiffIdx] !== candidateName[leftDiffIdx]) {  
                break;
            }
            
            leftDiffIdx = leftDiffIdx - 1 < 0 ? name.length - 1 : leftDiffIdx - 1;
            leftDiffDistance += 1;
        }
           
        while (rightDiffIdx < name.length) {
            if (name[rightDiffIdx] !== candidateName[rightDiffIdx]) {
                break;
            }
            
            rightDiffIdx += 1;
            rightDiffDistance += 1;
        }
        
        if (rightDiffIdx === name.length) {
            idx = leftDiffIdx;
            answer += leftDiffDistance;
            continue;
        }
               
        if (leftDiffDistance < rightDiffDistance) {
            idx = leftDiffIdx;
            answer += leftDiffDistance;
        }
        else {
            idx = rightDiffIdx;
            answer += rightDiffDistance;
        }
             
    }
    
    return answer;
}