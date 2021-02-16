class Solution {
    
    public int solution(String skill, String[] skill_trees) {
       int answer = 0;
	        for(int i=0;i<skill_trees.length;i++){
	            String words = skill_trees[i];
	            
	            int before = -1 ; //이전의 숫자 비교
	            boolean check = true;
	            
	            for(int b=0;b<skill.length();b++){  //주어진 문자열
	            	if(check){
	            		
	            		check = false;
	            		 for( int a=0;a<words.length();a++){ 
	 	                    if(a> before && skill.charAt(b) == (words.charAt(a))){ // 이전 point보다 크고 문자가 같을때
	 	                    	 check = true;
	 	                    	 before = a;
	 	                    	 break;
	 	                    }else if(a<before && skill.charAt(b) == (words.charAt(a))){ //문자는 같지만 이전 point 보다 작을때 멈춤
	 	                    	break;
	 	                    }
	 	                    if(a==words.length()-1){ //단어 안에 맞는 문자가 없을때 그냥 넘어가고 point를 가장 큰 숫자로 
	 	                    	check = true;
	 	                    	before = words.length();
	 	                    }
	 	                }
	            	}
	            }
	            if(check){
	            	answer ++;
	            }
	            
	        }
	        System.out.println(answer);
	        return answer;
    }
}
