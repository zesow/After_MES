import java.util.*;
import java.io.*;

public class Baekjoon_11047 {

    private static int N,K;
    private static int[] coins;
    public static void main(String[] args) throws IOException{
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));

        String[] line = br.readLine().split(" ");

        N = Integer.parseInt(line[0]);
        K = Integer.parseInt(line[1]);

        coins = new int[N];
        for(int i = 0 ; i < N ; i++) {
            coins[i] = Integer.parseInt(br.readLine());
        }

        int answer = 0;
        while (K > 0) {
            int max = 0;
            for(int i = 0 ; i < N ; i++) {
                if(K < coins[i]) {
                    break;
                }
                max = coins[i];   
            }

            K -= max;
            answer++;
        }

        System.out.println(answer);
    }
}
