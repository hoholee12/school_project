/*20154078 이정호*/

package test2;

import java.util.*;

public class test {

	public static void main(String[] args) {
		String x; //입력받을곳
		int i, j = 0; //루프
		int xlen; //자릿수
		int buffer = 20; //화면에 표시할 허용된 길이
		char[] xinput = new char[buffer]; //x를 청소하고 넘겨받을곳
		char[] y= new char[buffer]; //출력할때 쓸거
		char[] count = {' ', '십', '백', '천', '만'};
		char[] number = {' ', '일', '이', '삼', '사', '오', '육', '칠', '팔', '구'}; //뒤 구문에 쓰일 배열
		char[] xnumber = {' ', ' ', '이', '삼', '사', '오', '육', '칠', '팔', '구'}; //앞,중간구문에 쓰일 배열
		Scanner input = new Scanner(System.in); //입력초기화
		
		/*입력받기*/
		x = input.nextLine();
		input.close();
		
		
		/*x에서 xinput으로*/
		xlen = x.length();
		for(i=0, j=0;i<xlen;i++){
			if(Character.isDigit(x.charAt(i))){
				xinput[j++] = x.charAt(i);
			}
			else{
				if(x.charAt(xlen-1)!='원'){
					System.out.println("에러!\n");
					System.exit(1);
				}
				xlen--; //'원'을 길이에서 빼야지
			}
		}
		if(xlen>5){
			System.out.println("너무 크다.\n");
			System.exit(1);
		}
		if(xinput[0]=='0'){
			System.out.println("빵원\n"); //핸들
			System.exit(0);
			
		}


		
		
		/*앞구문*/
		/*
		y[j++] = number[xinput[xlen-1-i]-'0'];
		y[j++] = count[i];
		y[j++] = ' ';

		i--;
		*/
		
		
		/*앞,중간구문*/
		for(j=0, i=xlen-1; i>0; i--){
			y[j++] = xnumber[xinput[xlen-1-i]-'0']; //'일'이 없는거
			if(xinput[xlen-1-i]!= '0'){ //중간에 0인데 단위들어가면 안됨
				y[j++] = count[i];
				y[j++] = ' ';
			}
		}
		
		
		
		
		/*뒷구문*/
		y[j++] = number[xinput[xlen-1-i]-'0'];
		y[j++] = count[i];
		y[j++] = ' ';
		
		
		
		
		
		/*마무리*/
		//i는 이제 안쓰므로
		for(;j<buffer; j++) y[j]=' '; //먼저 빈칸 스페이스로 채우기
		
		//j도 이제 안씀
		for(i=0;i<buffer;i++){
			if(!Character.isSpaceChar(y[i])){
				j=i; //마지막 글자가 있는 곳
			}
		}
		y[j+1]='원'; //그 앞에 집어넣기
		
		
		
		
		System.out.println(y);
		

	}

}
