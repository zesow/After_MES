import java.util.*;

class Solution {
     
    public int solution(String s) {
        
        int answer = Integer.MAX_VALUE;
        
        for(int i = 1; i <= s.length(); ++i) {
            
            String copyStr = new String(s);
            
            String compressedStr = "";
            int cnt = 0;
            String standard = copyStr.substring(0,i);
            
            while(copyStr.length() >= i) {
                
                String nowStr = copyStr.substring(0,i);
                
                if(nowStr.equals(standard)) { // 지금 기준이 되는 문자열이 또 나왔다 -> 한번 더 가
                    
                    ++cnt;
                }
                else { // 지금 기준이 되는 문자열이 안 나왔다 -> 여기서 멈추고 새걸로 바꿔
                    
                    if(cnt != 1)
                        compressedStr += String.valueOf(cnt) + standard;
                    else
                        compressedStr += standard;
                    
                    cnt = 1; // cnt 초기화
                    
                    standard = nowStr; // 다음 기준은 지금 비교한 문자열
                }
                
                copyStr = copyStr.substring(i,copyStr.length()); 
                
            }
            
            // 마지막에 찌꺼기들 처리
            if(cnt != 1)
                compressedStr += String.valueOf(cnt) + standard;
            else
                compressedStr += standard;
            
            if(copyStr.length() > 0)
                compressedStr += copyStr;
            
            if(answer > compressedStr.length())
                answer = compressedStr.length();
        }

        return answer;
    }
    
}