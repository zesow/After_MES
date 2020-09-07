class Solution {
    
    public int[] solution(int brown, int yellow) {
        int[] answer = new int[2];
        
        for(int yellowHeight = 1 ; yellowHeight <= yellow; ++yellowHeight) {
            
            if(yellow % yellowHeight == 0) {
                
                if((yellowHeight + 2) * ((yellow / yellowHeight) + 2) == brown + yellow) {
                    answer[0] = (yellow / yellowHeight) + 2;
                    answer[1] = yellowHeight + 2;
                    
                    break;
                }
            }
        }
        
        return answer;
    }
}