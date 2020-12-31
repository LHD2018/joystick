#pragma once
#include "myjoystick.hpp"

class PLCJoystick : public MyJoyStick {

public:

	PLCJoystick(UINT joy_id);

	bool getDetectLane();

	double* getSpeed();

	virtual void listenJs();

	virtual ~PLCJoystick();


private:
	// �����ڰ�ѭ��
	bool detect_lane;
	double xy_maxspeed;
	// ����x��y�����ٶ��Լ�z����ת���ٶȣ����û�������������ϵ��
	double* speed = new double[3];


};