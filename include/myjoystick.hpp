#pragma once

#include <iostream>
#include <string>
#include <iostream>
#include <Windows.h>
#include <joystickapi.h>

#pragma comment(lib, "Winmm.lib")


using namespace std;

class Point {
public:
	double x, y;

	void init() {
		x = 0.0;
		y = 0.0;
	}

};

class MyJoyStick
{
protected:
	//�ֱ�ID
	UINT joy_id;
	//�ֱ���Ϣ
	JOYCAPS joy_caps;
	//�ֱ�״̬
	JOYINFOEX* joy_info = new JOYINFOEX();
	//����״̬��
	int ret_code;
	//������ʶ��
	bool listen_flag;
	//֮ǰ����ť
	int pre_dire_btn;
	//��ǰ����ť
	int cur_dire_btn;
	//��ҡ��
	Point xy_point;
	//��ҡ��
	Point uv_point;
	//֮ǰ�İ�ť��
	int pre_btn;
	//��ǰ��ť��
	int cur_btn;

public:

	MyJoyStick(UINT joy_id) {
		this->joy_id = joy_id;
		ret_code = 0;
		listen_flag = false;
		pre_dire_btn = 65535;
		cur_dire_btn = 65535;
		xy_point.init();
		uv_point.init();
		pre_btn = 0;
		cur_btn = 0;

		joy_info->dwSize = sizeof(JOYINFOEX);
		joy_info->dwFlags = (int)JOY_RETURNBUTTONS;
	}

	//��ȡ�ֱ���Ϣ
	bool getJsCaps() {
		ret_code = joyGetDevCaps(joy_id, &joy_caps, sizeof JOYCAPS);
		if (ret_code) {
			cout << "error code:  " << ret_code << endl;
			return false;
		}
		
		cout << "��Ʒ��ʶ����" << joy_caps.wPid << endl;
		cout << "��Ʒ���ƣ�" << joy_caps.szPname << endl;
		cout << "��Сx���꣺" << joy_caps.wXmin << endl;
		cout << "���x���꣺" << joy_caps.wXmax << endl;
		cout << "��Сy���꣺" << joy_caps.wYmin << endl;
		cout << "���y���꣺" << joy_caps.wYmax << endl;
		cout << "��Сz���꣺" << joy_caps.wZmin << endl;
		cout << "���z���꣺" << joy_caps.wZmax << endl;
		cout << "��ť������" << joy_caps.wNumButtons << endl;
		cout << "����joySetCapture��������֧�ֵ���С��ѯƵ�ʣ�" << joy_caps.wPeriodMin << endl;
		cout << "����joySetCapture��������֧�ֵ������ѯƵ�ʣ�" << joy_caps.wPeriodMax << endl;
		cout << "��С��ֵ�������ᣩ��" << joy_caps.wRmin << endl;
		cout << "����ֵ�������ᣩ��" << joy_caps.wRmax << endl;
		cout << "��Сu���꣨�����ᣩ��" << joy_caps.wUmin << endl;
		cout << "���u���꣨�����ᣩ��" << joy_caps.wUmax << endl;
		cout << "��Сv���꣨�����ᣩ��" << joy_caps.wVmin << endl;
		cout << "���v���꣨�����ᣩ��" << joy_caps.wVmax << endl;
		cout << "�ֱ����ܣ�" << int(joy_caps.wCaps) << endl;
		cout << "�ֱ�֧�����������" << joy_caps.wMaxAxes << endl;
		cout << "��ǰʹ��������" << joy_caps.wNumAxes << endl;
		cout << "֧����󰴼�����" << joy_caps.wMaxButtons << endl;
		cout << "������" << joy_caps.szOEMVxD << endl;
		cout << endl;
		return true;
	}

	//�����ֱ�״̬
	bool updateStatus() {

		ret_code = joyGetPosEx(joy_id, joy_info);
		if (ret_code) {
			cout << "error code:  " << ret_code << endl;
			return false;
		}
		
		cur_dire_btn = joy_info->dwPOV;

		xy_point.x = (joy_info->dwXpos - 32767.0) / 33024.0;
		xy_point.y = (32511.0 - joy_info->dwYpos) / 33024.0;

		uv_point.x = (32767.0 - joy_info->dwZpos) / 33024.0;
		uv_point.y = (32511.0 - joy_info->dwRpos) / 33024.0;

		cur_btn = joy_info->dwButtons;
		if (cur_btn == 512){
			listen_flag = true;
		}
		else if (cur_btn == 256){
			listen_flag = false;
		}
		return true;
	}

	//�����ֱ�
	virtual void listenJs() {
		if (!listen_flag) return;
		
		if (cur_dire_btn != pre_dire_btn){
			switch (cur_dire_btn){
			case 0:
				cout << "�������" << endl;
				break;
			case 18000:
				cout << "�������" << endl;
				break;
			case 27000:
				cout << "�������" << endl;
				break;
			case 9000:
				cout << "�������" << endl;
				break;
			default:
				break;
			}
			pre_dire_btn = cur_dire_btn;
		}

		cout << "xy���꣺��" << xy_point.x << "," << xy_point.y << "��" << endl;
		cout << "uv���꣺��" << uv_point.x << "," << uv_point.y << "��" << endl;

		if (cur_btn != pre_btn){
			switch (cur_btn) {
			case 2:
				cout << "A" << endl;
				break;
			case 4:
				cout << "B" << endl;
				break;
			case 1:
				cout << "X" << endl;
				break;
			case 8:
				cout << "Y" << endl;
				break;
			case 16:
				cout << "LB" << endl;
				break;
			case 32:
				cout << "LR" << endl;
				break;
			case 64:
				cout << "LT" << endl;
				break;
			case 128:
				cout << "RT" << endl;
				break;
			case 256:
				cout << "Back" << endl;
				break;
			case 512:
				cout << "Start" << endl;
				break;
			default:
				break;
			}
			pre_btn = cur_btn;
		}

		cout << endl;
	}

	virtual ~MyJoyStick() {
		if (joy_info != NULL){
			delete joy_info;
			joy_info = NULL;
		}
	}
};
