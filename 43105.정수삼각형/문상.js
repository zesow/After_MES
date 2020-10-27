// top-down
const memos = new Array();

function solution(triangle) {
    
    let answer = 0;
    
    for(let i = 0 ; i < triangle.length; i++) {
        const temp = new Array();
        for(let j = 0 ; j <= i ; j++ ) {
            temp.push(0);
        }   
        memos.push(temp);
    }
    
    memos[0][0] = triangle[0][0];
    for(let i = 1 ; i < triangle.length; i++) {
        
        for (let j = 0 ; j <= i ; j++) {
            
            const nowNumber = triangle[i][j];
            
            if(j === 0) {
                memos[i][0] = memos[i-1][0] + nowNumber;    
            }
            else if(j === i) {
                memos[i][j] = memos[i - 1][j - 1] + nowNumber;    
            }
            else {
                memos[i][j] = Math.max(memos[i-1][j-1],memos[i-1][j]) + nowNumber;
            }
            
            answer = Math.max(answer,memos[i][j]);
        }
          
    }
    
    return answer;
}

// bottom - up
const memos = new Array();

function solution(triangle) {
    
    let answer = 0;
    
    for(let i = 0 ; i < triangle.length; i++) {
        const temp = new Array();
        for(let j = 0 ; j <= i ; j++ ) {
            temp.push(0);
        }   
        memos.push(temp);
    }
    
    for(let i = 0 ; i < triangle[triangle.length - 1].length ; i++) {
        
        const temp = dfs(triangle.length - 1, i, triangle);
        
        if (temp > answer) {
            answer = temp;
        }
        
    }
    
    return answer;
}

function dfs(level, idx, triangle) {
    
    if(level === 0) {
        return triangle[0][0];
    }
    
    if(memos[level][idx] > 0) {
        return memos[level][idx];
    }
    
    const nowNumber = triangle[level][idx];
    
    if (idx === 0) {
        memos[level][idx] = dfs(level-1, idx, triangle) + nowNumber;
    }
    else if (idx === triangle[level].length - 1) {
        memos[level][idx] = dfs(level-1, idx-1, triangle) + nowNumber;
    }
    else {
        const left = dfs(level-1, idx-1, triangle);
        const right = dfs(level-1, idx, triangle);
        memos[level][idx] = Math.max(left, right) + nowNumber;
    }
    
    return memos[level][idx];
    
}