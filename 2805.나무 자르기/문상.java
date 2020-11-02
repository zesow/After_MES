import java.io.*;
import java.util.*;

public class Baekjoon_2805 {

    private static long M;
    private static int N;

    private static long[] trees;
    public static void main(String[] args) throws IOException {

        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        String[] line = br.readLine().split(" ");
        N = Integer.parseInt(line[0]);
        M = Long.parseLong(line[1]);

        trees = new long[N];
        line = br.readLine().split(" ");
        for(int i = 0 ; i < N ; i++) {
            trees[i] = Long.parseLong(line[i]);
        }

        Arrays.sort(trees);

        // System.out.println(Arrays.toString(trees));

        long left = 0;
        long right = trees[trees.length - 1];
        
        long answer = 0;
        
        while(left <= right) {
            long mid = (left + right) / 2;
            
            long sum = 0;
            for(int i = 0 ; i < N ; i++) {
                if(mid >= trees[i]) {
                    continue;
                }

                sum += trees[i] - mid;
            }
            // System.out.println(mid + ", " + sum);

            if(sum < M) {
                right = mid - 1;   
            }
            else{
                if(answer < mid) {
                    answer = mid;
                }

                left = mid + 1;
            }
        
        }

        System.out.println(answer);

    }
}