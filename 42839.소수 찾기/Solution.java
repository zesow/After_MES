import java.util.*;

class Solution {
    public int solution(String numbers) {
        
        char[] numArr = numbers.toCharArray();
        boolean[] check = new boolean[numArr.length];
        HashSet<Integer> set = new HashSet<Integer>();
        
        for(int i = 0 ; i < numArr.length; ++i) {
            check[i] = true;
            dfs(numArr,check, i, "",set);
            check[i] = false;
        }
        
        return set.size();
    }
    
    private void dfs(char[] numArr,boolean[] check,int idx, String numStr,HashSet<Integer> set) {
        
        numStr += numArr[idx];
        
        int num = Integer.parseInt(numStr);
        
        if(isPrime(num)) {
            set.add(num);
        }
        
        for(int i = 0 ; i < numArr.length; ++i) {
            if(!check[i]) {
                check[i] = true;
                dfs(numArr,check,i,numStr,set);
                check[i] = false;
            }
        }
        
        numStr = numStr.substring(0,numStr.length() - 1);
    }
    
    
    private boolean isPrime(int num) {
        
        if(num < 2) return false;
        
        int n = 2;
        
        while(n < num) {
            if(num % n == 0) 
                return false;
            
            ++n;
        }
        
        return true;
            
    }
}