import java.util.*;

class Solution {
    public int[] solution(int[] progresses, int[] speeds) {
 
       
		// 지금까지의 진행률을 저장할 큐        
        Queue<Integer> mainQueue = new LinkedList<>();
        for(int i = 0; i < progresses.length ; ++i) {
            mainQueue.add(progresses[i]);
        }
        
		// 진행률 넣어졌다 빼졌다 맞추기 위해서 speed 가 들어갈 큐        
        Queue<Integer> speedQueue = new LinkedList<>();
        for(int i = 0 ; i < speeds.length; ++i) {
            speedQueue.add(speeds[i]);
        }
        
		// 정답이 들어갈 리스트
        List<Integer> ans = new LinkedList<>();

		// 다들 일 끝낼 때 까지 반복
        while(mainQueue.size() > 0) {
            
            int todayFinish = 0;
            int todayMainQueueSize = mainQueue.size();
            
			// 앞에 사람이 남아있는지 아닌지 기록할 flag
            int flag = 0;

			// 오늘 남은 사람들 일 시작
            for(int i = 0 ; i < todayMainQueueSize ; ++i) {
                
                int todayNow = mainQueue.peek() + speedQueue.peek();
                
                // 진도 끝냈고 앞에 못나간 사람 없으니까 넌 나가
                if(todayNow >= 100 && flag == 0) { 
                    
                        todayFinish++;
                        mainQueue.poll();
                        speedQueue.poll();
                    
                }
                else { // 안끝냈거나 앞에 사람 있으니까 뒤로 갔다가 내일 또 해
                    int mainNum = mainQueue.poll();
                    int speedNum = speedQueue.poll();
                    
                    mainQueue.add(mainNum + speedNum);
                    speedQueue.add(speedNum);
                    
                    flag = 1;
                }
                
            }
            
            if(todayFinish != 0) { // 오늘 한거 있으면 몇건 했어?
                ans.add(todayFinish);
            }
        }
        
        return ans.stream().mapToInt(i->i).toArray();
    }
}