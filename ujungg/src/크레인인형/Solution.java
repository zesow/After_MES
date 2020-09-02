package 크레인인형;



class Solution {
	 public static void main(String[] args) {
	  int[][] board = {{1,1,1,1,1},{1,1,1,1,1},{1,1,1,1,1},{1,1,1,1,1},{1,1,1,1,1}};
	  int[] moves ={1,1,1,1,1,1,1,1};
	  
	  solution(board, moves);
		}
	
	 public static int solution(int[][] board, int[] moves) {
		 int[] visit = new int[1001];
		 int visitPoint = 0;
		 int answer =0;
		 
		 for(int i=0 ; i<moves.length ; i++){
			 int point = moves[i];
			 
			 int a=0;
			 while( a<board.length && board[a][point-1]==0 ){
				 a++;
			 }
			 
			 if(a < board.length) {
				 visit[visitPoint] = board[a][point-1];
				 board[a][point-1]=0;
			 }
			 
			 if(visitPoint > 0){
				 if(visit[visitPoint-1] == visit[visitPoint] && visit[visitPoint-1]!=0 && visit[visitPoint]!=0 ){
					 //삭제
					 visit[visitPoint-1] =0;
					 visit[visitPoint] = 0 ;
					 visitPoint-=1;
					 answer +=2;
				 }else{
					 visitPoint+=1;
				 }
			 }else{
				 visitPoint+=1;
			 }
		 }
		 System.out.println(answer);
		 return answer;
    	
    }
   
}