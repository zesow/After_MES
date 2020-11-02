import java.io.*;

public class Baekjoon_10815 {
    
    private static int N,M;
    private static int[] plusArr = new int[10000001];
    private static int[] minusArr = new int[10000001];
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));

        N = Integer.parseInt(br.readLine());
        String[] line = br.readLine().split(" ");
        for(int i = 0 ; i < N ; i++) {
            int now = Integer.parseInt(line[i]);
            if (now < 0) {
                now *= -1;
                minusArr[now] = 1;
            }
            else {
                plusArr[now] = 1;
            }
        }

        M = Integer.parseInt(br.readLine());
        
        line = br.readLine().split(" ");
        for(int i = 0 ; i < M ; i++) {
            int now = Integer.parseInt(line[i]);
            int flag = 0;
            if (now < 0) {
                now *= -1;
                if(minusArr[now] == 1) {
                    flag = 1;
                }
            }
            else {
                if(plusArr[now] == 1) {
                    flag = 1;
                }
            }

            System.out.print(flag + " ");
        }
        System.out.println();
    }
}