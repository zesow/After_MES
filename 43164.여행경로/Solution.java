import java.util.*;

class Solution {
    
    public String[] solution(String[][] tickets) {
        String[] answer = {};
        boolean[] check = new boolean[tickets.length];
        List<String> answerList = new LinkedList<String>();
        
        for(int i = 0 ; i < tickets.length; ++i) {
            if("ICN".equals(tickets[i][0])) {
                check[i] = true;
                dfs(tickets,check,1,tickets[i][0] + "," + tickets[i][1],answerList,tickets[i][1]);
                check[i] = false;
            }
        }
        
        Collections.sort(answerList);
        
        answer = answerList.get(0).split(",");
        
        return answer;
        
    }
    
    private void dfs(String[][] tickets,boolean[] check, int cnt, String routes, List<String> answerList,String end) {
    
        
        if(cnt == tickets.length) {
            answerList.add(routes);
            return;
        }
        
        for(int i = 0 ; i < tickets.length; ++i) {
            if(!check[i] && end.equals(tickets[i][0])) {
                check[i] = true;
                dfs(tickets,check,cnt+1,routes + "," + tickets[i][1],answerList,tickets[i][1]);
                check[i] = false;
            }
        }
    }
}