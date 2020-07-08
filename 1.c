#include <REGX52.H>

typedef unsigned char uchar;
typedef unsigned int uint;

sbit dula = P1 ^ 3;
sbit wei1 = P2 ^ 4;
sbit wei2 = P2 ^ 5;
sbit wei3 = P2 ^ 6;
sbit wei4 = P2 ^ 7;

sbit nr = P1 ^ 0;  // ����
sbit ny = P1 ^ 1;  // ����
sbit ng = P1 ^ 2;  // ����

sbit wr = P3 ^ 0;  // ����
sbit wy = P3 ^ 1;  // ����
sbit wg = P3 ^ 2;  // ����

sbit sr = P3 ^ 5;  // �Ϻ�
sbit sy = P3 ^ 6;  // �ϻ�
sbit sg = P3 ^ 7;  // ����

sbit er = P2 ^ 0;  // ����
sbit ey = P2 ^ 1;  // ����
sbit eg = P2 ^ 2;  // ����

sbit north = P1 ^ 4;   // ��
sbit west = P1 ^ 5;   // ��
sbit south = P1 ^ 6;    // ��
sbit east = P1 ^ 7;    // ��


uchar code table[] = {   // �����Զ�����С
	// code ����� 0 - 15��  �������code����RAM�У� ����ROM�У� 51��RAM���٣� RAM�Ƚϱ���
	0x3f, 0x06, 0x5b, 0x4f, 0x66,
	0x6d, 0x7d, 0x07, 0x7f, 0x6f,
	0x77, 0x7c, 0x39, 0x5e, 0x79,
	0x71};

uchar count1, count2, i, num1, num2;
uchar direct;  // ��ʾ��ʱʮ��·��ͨ�еķ���

void display(uchar, uchar);
void delay(uint);
void init_timer();
void init();

void main() {
	init();
	
	// �̻ƺ�
	while(1){
		// �ϱ������̵���
		north = south = 0;
		
		ng = 1;
		sg = 1;
		// ������������
		er = 1;
		wr = 1;
		// ��ʱ50��
		num1 = 50;
		num2 = 60;
		init_timer();  // ��ʱ��������ʼ��
		while(1) {
			display(num1, num2);
			if(num1 == 0) {
				num1 = 10;
				break;
			}
		}
		// �ص�
		ng = 0;
		sg = 0;
		// �ϱ���Ϊ�Ƶ�
		north = south = 1;
		ny = 1;
		sy = 1;
		while(1) {
			display(num1, num2);
			if(num1 == 1 && num2 == 1)
				break;
			
		}
		ny = 0;
		sy = 0;
		er = 0;
		wr = 0;
		east = west = 0;
		// �ϱ����50�룬 �����̵�50��
		nr = 1;
		sr = 1;
		eg = 1;
		wg = 1;
		num1 = 60;
		num2 = 50;
		init_timer();
		while(1) {
			display(num1, num2);
			if(num2 == 0) {
				num2 = 10;
				break;
			}
			
		}
		eg = 0;
		wg = 0;
		// �������̱��
		east = west = 1;
		ey = 1;
		wy = 1;
		while(1) {
			display(num1, num2);
			if(num1 == 1 && num2 == 1)
				break;
			
		}
		nr = 0;
		sr = 0;
		ey = 0;
		wy = 0;
		
	};
	
	
}
void init_timer() {
	// ��ʱ��������ʼ��
	count1 = count2 = 0;
	TR0 = 1;
	TR1 = 1;
}
void init() {
	P1 = 0xf8;
	P2 = 0xf8;
	P3 = 0x00;
	
	TMOD = 0x11;
	EA = 1;
	ET0 = 1;
	ET1 = 1;
	
	TH0 = (65536 - 50000) >> 8;
	TL0 = (65536 - 50000) & 0x00ff;
	
	TH1 = (65536 - 50000) >> 8;
	TL1 = (65536 - 50000) & 0x00ff;
}

void display(uchar num1, uchar num2) {
	wei1 = 0;
	P0 = table[num1 / 10];
	delay(5);
	wei1 = 1;
	
	wei2 = 0;
	P0 = table[num1 % 10];
	delay(5);
	wei2 = 1;
	
	wei3 = 0;
	P0 = table[num2 / 10];
	delay(5);
	wei3 = 1;
	
	wei4 = 0;
	P0 = table[num2 % 10];
	delay(5);
	wei4 = 1;
}

void delay(uint z) {
	uint x, y;
	for(x = z; x; x--)
		for(y = 110; y; y--);
}

void timer0() interrupt 1 {
	TH0 = (65536 - 50000) >> 8;
	TL0 = (65536 - 50000) & 0x00ff;
	count1++;
	if(count1 == 20) {
			count1 = 0;
			num1--;
	}
}

void timer1() interrupt 3 {
	TH1 = (65536 - 50000) >> 8;
	TL1 = (65536 - 50000) & 0x00ff;
	count2++;
	if(count2 == 20) {
		num2--;
		count2 = 0;
	}
}