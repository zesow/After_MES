import java.util.*;
class Solution {
    static int[][] picture;
    static int[][] visit;
    static int[][] dir = {{0,1},{0,-1},{1,0},{-1,0}};
    static int max =0;  static int cnt=0;
        
    static void solve(int startX, int startY, int color,int m , int n){
       for(int d=0;d<4;d++){ //4방향 돌면서 같은것이 있나 확인
           int x = startX + dir[d][0];
           int y = startY + dir[d][1];
          
           if(x<0 || y<0 || x>=m || y>=n) continue; 
           if(visit[x][y]==0 && picture[x][y]== color){
        	   visit[x][y]=1;
        	   cnt++;
               solve(x,y,color,m,n);
           }
       }
    }
    
    
    public int[] solution(int m, int n, int[][] picture) {
        
    	this.max =0; this.cnt= 0;
        this.picture = picture;
        this.visit = new int[m][n];
          for(int i=0;i<m;i++){
        	for(int j=0;j<n;j++){
        		visit[i][j]=0;
        	}
        } // 이상하게 여기서 초기화 해줘야함,, 프로그래머스상의 문제인듯..
        
        int numberOfArea = 0;
        int maxSizeOfOneArea = 0;

        for(int i=0;i<m;i++){
            for(int j=0; j<n;j++){
                if(visit[i][j]==0 && picture[i][j]!=0){
                    numberOfArea ++; //영역
                    visit[i][j]=1; //이미 방문했던곳 표시
                    cnt=1;
                    solve(i,j,picture[i][j],m,n); //시적X, 시작Y, 색, 영역
                    
                    max = Math.max(cnt,max);
                }        
            }
        }
    
        maxSizeOfOneArea = max;
        int[] answer = new int[2];
        answer[0] = numberOfArea;
        answer[1] = maxSizeOfOneArea;
        return answer;
    
    }
}
