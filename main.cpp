#include <iostream>
#include <stdlib.h>
#include "Target.cpp"
#include "readlog.h"
//File IO
#include <iomanip>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
using namespace std;

void read_csv_log(Printer *ptr0, Aircon *ptr1, Door *ptr2);
void showConsole();

int main() {
	Printer printer1;
	Aircon aircon1;
	Door door1;

	cout << "Start Central Control System Program..." << endl;
	_sleep(1000);
	read_csv_log(&printer1, &aircon1, &door1);
	printer1.GPIO_CDM = 7; //7말고 다른값 넣으면 안됨 왠지 모르겠음 (해결해야함)      
	aircon1.GPIO_CDM = 7; //7말고 다른값 넣으면 안됨 왠지 모르겠음  (해결해야함)
	door1.GPIO_CDM = 7; //7말고 다른값 넣으면 안됨 왠지 모르겠음  (해결해야함)



	//showconsole
	cout << "                             자동모드  전원  권한" << endl;
	cout << "┌───────────────────┐" << endl;
	cout << "│                   │" << endl;
	cout << "│    중 앙  제 어   │" << endl;
	cout << "│                   │" << endl;
	cout << "└───────────────────┘" << endl;
	cout << " │" << endl;
	cout << " │" << endl;
	cout << " └─────────────────── 프린터    ";

	if ((*(printer1.Register[0]) & 1)) //자동모드 
	{
		if ((*(printer1.Register[0]) == 7)) { //전원O 권한 O (0b111)
			cout << "■     ■     ■" << endl;
		}
		else if ((*(printer1.Register[0]) == 3)) { //전원O 권한 x (0b101)
			cout << "■     ■     □" << endl;
		}
		else if ((*(printer1.Register[0]) == 1)) { //전원x 권한 x (0b001)
			cout << "■     □     □" << endl;
		}
	}
	else if ((*(printer1.Register[0]) & 0)) //수동모드
	{
		if ((*(printer1.Register[0]) == 6)) { //전원O 권한 O
			cout << "□     ■     ■" << endl;
		}
		else if ((*(printer1.Register[0]) == 4)) { //전원O 권한 x
			cout << "□     ■     □" << endl;
		}
		else if ((*(printer1.Register[0]) == 0)) { //전원x 권한 x
			cout << "□     □     □" << endl;
		}
	}
	cout << " │" << endl;
	cout << " │" << endl;
	cout << " └─────────────────── 에어콘    ";

	if ((*(aircon1.Register[0]) & 1)) //자동모드 
	{
		if ((*(aircon1.Register[0]) == 7)) { //전원O 권한 O (0b111)
			cout << "■     ■     ■" << endl;
		}
		else if ((*(aircon1.Register[0]) == 3)) { //전원O 권한 x (0b101)
			cout << "■     ■     □" << endl;
		}
		else if ((*(aircon1.Register[0]) == 1)) { //전원x 권한 x (0b001)
			cout << "■     □     □" << endl;
		}
	}
	else if ((*(aircon1.Register[0]) & 0)) //수동모드
	{
		if ((*(aircon1.Register[0]) == 6)) { //전원O 권한 O
			cout << "□     ■     ■" << endl;
		}
		else if ((*(aircon1.Register[0]) == 4)) { //전원O 권한 x
			cout << "□     ■     □" << endl;
		}
		else if ((*(aircon1.Register[0]) == 0)) { //전원x 권한 x
			cout << "□     □     □" << endl;
		}
	}

	cout << " │" << endl;
	cout << " │" << endl;
	cout << " └─────────────────── 문       ";

	if ((*(door1.Register[0]) & 1)) //자동모드 
	{
		if ((*(door1.Register[0]) == 7)) { //전원O 권한 O (0b111)
			cout << " ■     ■     ■" << endl;
		}
		else if ((*(door1.Register[0]) == 3)) { //전원O 권한 x (0b101)
			cout << " ■     ■     □" << endl;
		}
		else if ((*(door1.Register[0]) == 1)) { //전원x 권한 x (0b001)
			cout << " ■     □     □" << endl;
		}
	}
	else if ((*(door1.Register[0]) & 0)) //수동모드
	{
		if ((*(door1.Register[0]) == 6)) { //전원O 권한 O
			cout << " □     ■     ■" << endl;
		}
		else if ((*(door1.Register[0]) == 4)) { //전원O 권한 x
			cout << " □     ■     □" << endl;
		}
		else if ((*(door1.Register[0]) == 0)) { //전원x 권한 x
			cout << " □     □     □" << endl;
		}
	}

	cout << "======================================" << endl;
	cout << "[*] CLI" << endl;
	cout << "[>] ";
	
	//showConsole();
	//examples. 이 부분은 cin으로 select_CMD 변수로 받아서 저장한다.
	//IF selecyCDM & 4 , printer1.GPIO_CDM |= 4
	//printer1.GPIO_CDM = 7;       
	//printer1.manCtl(&printer1.GPIO_CDM, 1);
	
	//printer1.status(); 
	//printer1.autoCtl();
	_sleep(2000);
}

void showConsole() {
	int automode = 1; //자동모드
	int onoff = 1; //전원
	int digital_enable = 0; //권한
	cout << "                             자동모드  전원  권한" << endl;
	cout << "┌───────────────────┐" << endl;
	cout << "│                   │" << endl;
	cout << "│    중 앙  제 어   │" << endl;
	cout << "│                   │" << endl;
	cout << "└───────────────────┘" << endl;
	cout << " │" << endl;
	cout << " │" << endl;
	cout << " └─────────────────── 프린터 ";

	cout << " │" << endl;
	cout << " │" << endl;
	cout << " └─────────────────── 에어콘 ";
	cout << " │" << endl;
	cout << " │" << endl;
	cout << " └─────────────────── 문 ";
	cout << "======================================" << endl;
	cout << "[*] CLI" << endl;
	cout << "[>] ";
}


// readlog file 


int row = 3; //배열의 인덱스를 세기위한 변수
int col = 5; //배열의 인덱스를 세기위한 변수
string log_GPIO_CDM[3]; 
vector <vector < unsigned int > > log_CDM_reg;
string log_CDM_time[3][2];

void read_csv_log(Printer *ptr0, Aircon *ptr1, Door *ptr2) { // 실행과 동시에 과거에 저장된 로그로부터 데이터를 수집하도록 한다.

	std::ifstream csv("./log.csv");
	csv.ignore(500, '\n'); //첫 줄(세로 index)을 무시한다.
	std::string line;


	if (csv.is_open()) {
		
		log_CDM_reg.assign(row, vector<unsigned int>(col, 1));

		int i = 0; //i는 각종 장치들. 0번:printer 1번:aircon 2번:door. 
		for (std::string row_line; std::getline(csv, row_line);) {
			//첫 열(가로 index)을 무시한다.
			const auto pos = row_line.find(',');
			if (pos != string::npos)
				row_line.erase(0, pos + 1);

			std::istringstream row_stream(row_line);
			int j = 0; //j는 각종 장치들의 레지스터들.
			for (std::string column; std::getline(row_stream, column, ',');) {
				if (j == 0) //hex
				{
					log_GPIO_CDM[i] = column;
					//cout << log_GPIO_CDM[i] << endl; //확인용
				}
				else if (j == 3)
				{
					log_CDM_time[i][j - 3] = column; //시간은 string data에 저장
				}
				else if (j == 4)
				{
					log_CDM_time[i][j - 3] = column;
					//cout << "레지스터" << i << "의 최근 수정 시간 : " << log_CDM_time[i][j - 4] + " " + log_CDM_time[i][j-3] << endl; //확인용
				}
				else {
					log_CDM_reg[i][j] = stoi(column.c_str());
					//cout << stof(column.c_str()) << endl; //확인용
				}
				j++;
			}
			i++;
		}
		cout << "loading log success\n" << endl;

	}
	else {
		cout << "Unable to open file";
	}


	//nogada
	//csv파일로 부터 읽은 정보를 클래스이 레지스터에 저장하는 코드
	*(ptr0->Register[0]) = stoi(log_GPIO_CDM[0]);
	*(ptr0->Register[1]) = log_CDM_reg[0][0];
	*(ptr0->Register[2]) = log_CDM_reg[0][1];
	*(ptr0->Register[3]) = stoi(log_CDM_time[0][0]);

	*(ptr1->Register[0]) = stoi(log_GPIO_CDM[1]);
	*(ptr1->Register[1]) = log_CDM_reg[1][0];
	*(ptr1->Register[2]) = log_CDM_reg[1][1];
	*(ptr1->Register[3]) = stoi(log_CDM_time[1][0]);

	*(ptr2->Register[0]) = stoi(log_GPIO_CDM[2]);
	*(ptr2->Register[1]) = log_CDM_reg[2][0];
	*(ptr2->Register[2]) = log_CDM_reg[2][1];
	*(ptr2->Register[3]) = stoi(log_CDM_time[2][0]);

}
void showdata() {
	/***showing. if i=0 : printer , i=1 : aircon , i=2 : door***/
	char target_name[3][10] = { "printer","aircon","door" };
	cout << "\treg0\treg1 \treg2 \tlast" << endl;

	for (int i = 0; i < row; i++) {
		cout << target_name[i] << "\t";
		for (int j = 0; j < col; j++) {
			if (j >= 3)
			{
				cout << log_CDM_time[i][j - 3] << "\t";
			}

			else if (j == 0) {
				cout << "0b" << bitset<3>(stoi(log_GPIO_CDM[i])) << "\t";
			}
			else
				cout << log_CDM_reg[i][j] << "\t";
		}
		cout << endl;
	}
	cout << endl;
}
