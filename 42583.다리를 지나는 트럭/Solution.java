import java.util.*;

class Solution {
    public int solution(int bridge_length, int weight, int[] truck_weights) {
        int answer = 0;
        
        Queue<Integer> truckQueue = new LinkedList<Integer>();
        Queue<Integer> timeQueue = new LinkedList<Integer>();
        
        truckQueue.add(truck_weights[0]);
        timeQueue.add(0);
        
        int nowTrucksWeight = truck_weights[0];
        int truckIdx = 1;
        
        while(!truckQueue.isEmpty()) {
            
            ++answer;
            
            int queueSize = 0;
            // 빼준다
            while(!timeQueue.isEmpty()) {
                
                if(timeQueue.peek() + 1 == bridge_length) {
                    timeQueue.poll();
                    nowTrucksWeight -= truckQueue.poll();
                }
                else{
                    queueSize = timeQueue.size();
                    for(int i = 0 ; i < queueSize; ++i) {
                        timeQueue.add(timeQueue.poll() + 1);
                    }
                    break;
                }
            }
            
            // 넣어준다       
            if(truckIdx < truck_weights.length && nowTrucksWeight + truck_weights[truckIdx] <= weight) {
                truckQueue.add(truck_weights[truckIdx]);
                nowTrucksWeight += truck_weights[truckIdx];
                timeQueue.add(0);
                    
                truckIdx++;
                
            }
            
        }
        
        
        return answer + 1;
    }
}