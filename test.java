/*20154078 ����ȣ*/

package test2;

import java.util.*;

public class test {

	public static void main(String[] args) {
		String x; //�Է¹�����
		int i, j = 0; //����
		int xlen; //�ڸ���
		int buffer = 20; //ȭ�鿡 ǥ���� ���� ����
		char[] xinput = new char[buffer]; //x�� û���ϰ� �Ѱܹ�����
		char[] y= new char[buffer]; //����Ҷ� ����
		char[] count = {' ', '��', '��', 'õ', '��'};
		char[] number = {' ', '��', '��', '��', '��', '��', '��', 'ĥ', '��', '��'}; //�� ������ ���� �迭
		char[] xnumber = {' ', ' ', '��', '��', '��', '��', '��', 'ĥ', '��', '��'}; //��,�߰������� ���� �迭
		Scanner input = new Scanner(System.in); //�Է��ʱ�ȭ
		
		/*�Է¹ޱ�*/
		x = input.nextLine();
		input.close();
		
		
		/*x���� xinput����*/
		xlen = x.length();
		for(i=0, j=0;i<xlen;i++){
			if(Character.isDigit(x.charAt(i))){
				xinput[j++] = x.charAt(i);
			}
			else{
				if(x.charAt(xlen-1)!='��'){
					System.out.println("����!\n");
					System.exit(1);
				}
				xlen--; //'��'�� ���̿��� ������
			}
		}
		if(xlen>5){
			System.out.println("�ʹ� ũ��.\n");
			System.exit(1);
		}
		if(xinput[0]=='0'){
			System.out.println("����\n"); //�ڵ�
			System.exit(0);
			
		}


		
		
		/*�ձ���*/
		/*
		y[j++] = number[xinput[xlen-1-i]-'0'];
		y[j++] = count[i];
		y[j++] = ' ';

		i--;
		*/
		
		
		/*��,�߰�����*/
		for(j=0, i=xlen-1; i>0; i--){
			y[j++] = xnumber[xinput[xlen-1-i]-'0']; //'��'�� ���°�
			if(xinput[xlen-1-i]!= '0'){ //�߰��� 0�ε� �������� �ȵ�
				y[j++] = count[i];
				y[j++] = ' ';
			}
		}
		
		
		
		
		/*�ޱ���*/
		y[j++] = number[xinput[xlen-1-i]-'0'];
		y[j++] = count[i];
		y[j++] = ' ';
		
		
		
		
		
		/*������*/
		//i�� ���� �Ⱦ��Ƿ�
		for(;j<buffer; j++) y[j]=' '; //���� ��ĭ �����̽��� ä���
		
		//j�� ���� �Ⱦ�
		for(i=0;i<buffer;i++){
			if(!Character.isSpaceChar(y[i])){
				j=i; //������ ���ڰ� �ִ� ��
			}
		}
		y[j+1]='��'; //�� �տ� ����ֱ�
		
		
		
		
		System.out.println(y);
		

	}

}
