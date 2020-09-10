import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;
import java.util.LinkedList;

class Solution {
	
	public static void main(String[] args) {
//	 String[][] tickets = {{"ICN", "JFK"}, {"HND", "IAD"}, {"JFK", "HND"}};	
	String[][] tickets ={{"ICN", "SFO"}, {"ICN", "ATL"}, {"SFO", "ATL"}, {"ATL", "ICN"}, {"ATL","SFO"}};
	 solution(tickets);
	}
	static int[] visit;
    static String[][] tickets;
    static String temp = "";
    static LinkedList<String> link = new LinkedList<>();
    public static void solve(int point, String start, int cnt,String[][] tickets){
        
    	 temp += (start+","); //마지막단어까지 모두 temp에 넣기위해 여기서 단어를 
        if(cnt == tickets.length){
            link.add(temp);
        }else{
            for(int i=0;i<tickets.length;i++){
            	
                if(tickets[i][0].equals(start) && visit[i]==0){ // tickets[i][0]이 이전의 단어랑 일치하고, 처리한적이 없으면
                    visit[i]=1;
                    solve(i,tickets[i][1],cnt+1,tickets);
                    temp = temp.substring(0,temp.length()-4);
                    visit[i] =0;
                }
            }
        }
    }
    public static String[] solution(String[][] tickets) {
        
        visit = new int[tickets.length];
       
        for(int i=0;i<tickets.length;i++){
            if(tickets[i][0].equals("ICN")){
                visit[i] = 1; 
                temp = ("ICN"+","); //temp에 만들어질 문자열을 넣는다
                solve(i,tickets[i][1],1,tickets);
                temp = temp.substring(0,temp.length()-4); //이전에 temp에 추가했던 단어를 제외하고 다시 temp에 넣음
                visit[i]=0;
            }
        }
        String[] answer = new String[link.get(0).length()];
        Collections.sort(link);
        answer =  link.get(0).split(",");
      
        return answer;
    }
   
}
