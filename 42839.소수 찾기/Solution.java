class Solution {
    static int[] visit;
    static int[] checkArr = new int[100000000]; //중복제거를 위한 배열
    static String numbers ="";
    static int finals=0;
    
    public static void main(String[] args) {
		String numbers = "17";
		solution(numbers);
	}
    public static boolean check(String temp){
        int number = Integer.parseInt(temp);
        boolean flag = true;
        int a =2;
        System.out.println("number"+number);
        if(number <= 1) flag = false; 
        while(a<number){
            if(number % a ==0){
                flag = false; // 소수가 아님 -> 나눠떨어지는게 있어서
                break;
            }
            a++;
        }
        return flag;
    }
    public static void solve(String temp, int cnt){
        if(cnt<=numbers.length()){
            if(checkArr[Integer.parseInt(temp)]==0){ //중복제거를 위한 배열
            	checkArr[Integer.parseInt(temp)] =1;
            	if(check(temp)){ //true로 리턴되면 소수라는 뜻 
                    finals++; 
            	}
            	
            }
//            return;
        }
        for(int i=0;i<numbers.length();i++){
            if(visit[i]==0){
                visit[i]=1;
                temp +=numbers.charAt(i);
                solve(temp, cnt+1);
                visit[i]=0;
                temp = temp.substring(0,temp.length()-1);
            }
        }
    }
    public static int solution(String number) {
        visit = new int[number.length()];
        numbers = number;
        String temp ="";
        for(int i=0;i<numbers.length();i++){
            if(visit[i]==0){
                visit[i]=1;
                temp += numbers.charAt(i);
                solve(temp, 1);
                temp = numbers.substring(0,temp.length()-1);
                visit[i]=0;
            }
        }
        
        int answer = finals;
        System.out.println(answer);
        return answer;
    }
}
