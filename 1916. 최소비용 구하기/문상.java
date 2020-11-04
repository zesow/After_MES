import java.io.*;
import java.util.*;

class Node implements Comparable<Node>{

    int end;
    int weight;

    Node(int end,int weight) {
        this.end = end;
        this.weight = weight;
    }

    // 우선순위 큐에서 Min-Heap 을 위해서 compareTo를 만들어줘야 한다.
    @Override
    public int compareTo(Node o) {
        return weight - o.weight;
    }
} 

public class Baekjoon_1916 {

    private static int N,M,start,end;
    private static ArrayList<ArrayList<Node>> adjacentList = new ArrayList<>();
    private static int[] minDistancesFromStart;
    private static boolean[] isVisited;
    
    public static void main(String[] args) throws IOException {

        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        N = Integer.parseInt(br.readLine());
        M = Integer.parseInt(br.readLine());

        minDistancesFromStart = new int[N+1];
        isVisited = new boolean[N+1];

        Arrays.fill(minDistancesFromStart,Integer.MAX_VALUE);

        // 리스트 안에 리스트를 쓰기 위해서는, 내가 필요한 만큼 리스트 안에 리스트를 추가해줘야 한다.
        for (int i = 0 ; i <= N ; i++) {
            adjacentList.add(new ArrayList<>());
        }

        for (int i = 0 ; i < M ; i++) {
            String[] line = br.readLine().split(" ");
            int s = Integer.parseInt(line[0]);
            int e = Integer.parseInt(line[1]);
            int w = Integer.parseInt(line[2]);

            adjacentList.get(s).add(new Node(e,w));
        }

        String[] line = br.readLine().split(" ");
        start = Integer.parseInt(line[0]);
        end = Integer.parseInt(line[1]);

        dijkstra(start);

        System.out.println(minDistancesFromStart[end]);

    }

    private static void dijkstra(int start) {

        PriorityQueue<Node> pq = new PriorityQueue<>();
        pq.add(new Node(start,0));
        minDistancesFromStart[start] = 0;

        while (!pq.isEmpty()) {
            Node nowNode = pq.poll();
            
            // 아직 방문하지 않은 것만 체크해준다. 방문한건 이미 확정된다.
            if (!isVisited[nowNode.end]) {

                isVisited[nowNode.end] = true;

                for (Node nextNode : adjacentList.get(nowNode.end)) {

                    // 다음 노드가 아직 방문 안 했고, 지금 최소 거리라고 기록된 값 보다 지금 노드에서 다음 노드로 갈 때 더 짧은 경우
                    // 최소 거리로 표시해 주고 우선순위 큐에 넣어준다.
                    if (!isVisited[nextNode.end]
                     && minDistancesFromStart[nextNode.end] > minDistancesFromStart[nowNode.end] + nextNode.weight) {
                        minDistancesFromStart[nextNode.end] = minDistancesFromStart[nowNode.end] + nextNode.weight;
                        pq.add(new Node(nextNode.end, minDistancesFromStart[nextNode.end]));
                     }
                }
            }

        }
    }
    
}