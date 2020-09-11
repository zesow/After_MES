class Solution {
    public String solution(int n) {
        String answer = "";
        
        while(n > 0) {
            if(n % 3 == 0) {
                answer += "4";
                n -= 1;
            }
            else {
                answer += String.valueOf(n % 3);
            }
            
            n /= 3;
        }
        
        return new StringBuffer(answer).reverse().toString();
    }
}