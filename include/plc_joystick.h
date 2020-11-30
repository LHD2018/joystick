#pragma once
#include "myjoystick.hpp"

class PLCJoystick : public MyJoyStick {

public:

	PLCJoystick(UINT joy_id);

	void setSpeed(double* speed);

	double* getSpeed();

	virtual void listenJs();

	virtual ~PLCJoystick();


private:
	// ������ǰ�֡���ǰ�֡�����֡��Һ���ת��
	double* speed = new double[4];
	
};

