#include <REGX52.H>

typedef unsigned char uchar;
typedef unsigned int uint;

sbit dula = P1 ^ 3;
sbit wei1 = P2 ^ 4;
sbit wei2 = P2 ^ 5;
sbit wei3 = P2 ^ 6;
sbit wei4 = P2 ^ 7;

sbit nr = P1 ^ 0;  // 北红
sbit ny = P1 ^ 1;  // 北黄
sbit ng = P1 ^ 2;  // 北绿

sbit wr = P3 ^ 0;  // 西红
sbit wy = P3 ^ 1;  // 西黄
sbit wg = P3 ^ 2;  // 西绿

sbit sr = P3 ^ 5;  // 南红
sbit sy = P3 ^ 6;  // 南黄
sbit sg = P3 ^ 7;  // 南绿

sbit er = P2 ^ 0;  // 东红
sbit ey = P2 ^ 1;  // 东黄
sbit eg = P2 ^ 2;  // 东绿

sbit north = P1 ^ 4;   // 北
sbit west = P1 ^ 5;   // 西
sbit south = P1 ^ 6;    // 南
sbit east = P1 ^ 7;    // 东


uchar code table[] = {   // 编译自动检测大小
	// code 编码表， 0 - 15；  如果不用code放在RAM中， 用在ROM中， 51中RAM较少， RAM比较宝贵
	0x3f, 0x06, 0x5b, 0x4f, 0x66,
	0x6d, 0x7d, 0x07, 0x7f, 0x6f,
	0x77, 0x7c, 0x39, 0x5e, 0x79,
	0x71};

uchar count1, count2, i, num1, num2;
uchar direct;  // 表示此时十字路口通行的方向

void display(uchar, uchar);
void delay(uint);
void init_timer();
void init();

void main() {
	init();
	
	// 绿黄红
	while(1){
		// 南北方向绿灯亮
		north = south = 0;
		
		ng = 1;
		sg = 1;
		// 东西方向红灯亮
		er = 1;
		wr = 1;
		// 定时50秒
		num1 = 50;
		num2 = 60;
		init_timer();  // 定时器启动初始化
		while(1) {
			display(num1, num2);
			if(num1 == 0) {
				num1 = 10;
				break;
			}
		}
		// 关灯
		ng = 0;
		sg = 0;
		// 南北变为黄灯
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
		// 南北红灯50秒， 东西绿灯50秒
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
		// 东西由绿变黄
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
	// 定时器启动初始化
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