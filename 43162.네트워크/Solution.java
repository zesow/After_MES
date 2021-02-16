class Solution {
    public int solution(int n, int[][] computers) {
        int answer = 0;
        
        boolean[] check = new boolean[computers.length];
        for(int i = 0 ; i < computers.length; ++i) {
            if(!check[i]) {
                dfs(computers,check,i);
                answer++;
            }
        }
        return answer;
    }
    
    private void dfs(int[][] computers, boolean[] check, int idx) {
        
        check[idx] = true;
        
        for(int i = 0 ; i < computers[idx].length; ++i) {
            if(!check[i] && computers[idx][i] == 1) {
                dfs(computers,check,i);
            }
        }
    }
}