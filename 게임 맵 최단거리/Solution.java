import java.util.*;

class Solution {
    public int solution(int[][] board, int[] moves) {
        int answer = 0;
        
        List<Integer> bucket = new ArrayList<Integer>();
        
        int depth = board.length;
        int width = board[0].length;
        
        for(int move : moves) {
            int craw = move - 1;
            
            for(int i = 0 ; i < depth; ++i) {
                int nowCraw = board[i][craw];
                
                if(nowCraw != 0) {
                    
                    bucket.add(nowCraw);
                    board[i][craw] = 0;
                    break;
                }
            }
            
            if(bucket.size() > 1) {
                
                int size = bucket.size();
                int now = bucket.get(size - 1);
                int before = bucket.get(size - 2);
                
                if(now == before) {
                    answer++;
                    bucket.remove(size - 1);
                    bucket.remove(size - 2);
                }
            }
        }
        
        return answer * 2;
    }
}