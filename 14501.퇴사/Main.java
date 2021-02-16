import java.util.*;
import java.io.*;

class Main {
	
	private static int[] T;
	private static int[] P;
	private static int N;
	private static int max;

    public static void main(String[] args) throws IOException{

        // input
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        N = Integer.parseInt(br.readLine());
        
        T = new int[N];
        P = new int[N];

        String[] str;
        for(int i = 0 ; i < N ; ++i) {
            str = br.readLine().split(" ");
            T[i] = Integer.parseInt(str[0]);
            P[i] = Integer.parseInt(str[1]);
        }
        

        dfs(0,0);

       
        System.out.println(max);
        
    }

    private static void dfs(int idx,int sum) {
    	
    	if(sum > max)
    		max = sum;
    	
    	if(idx >= N)
    		return;
    	
    	// 이번 상담 한다
    	if(idx + T[idx] <= N)
    		dfs(idx + T[idx], sum + P[idx]);
    	
    	// 이번 상담 안한다.
    	dfs(idx + 1, sum);
    }
}