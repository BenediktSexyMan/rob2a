#ifndef _CONSTANTS_H
#define _CONSTANTS_H

#define BIG_D 32.4
#define LITTLE_D 10.4
#define LITTLE_D_C 32.67
#define CORRECTION_CONSTANT 1.02
unsigned int GRAB_DIST = 15;
unsigned int DROP_DIST = 7;
unsigned int OPEN_CLOSE_TIME = 700;
unsigned int LIFT_TIME = 1200;

int speedArr[2];
unsigned short taskID = 1;
unsigned int minDist = 35;
bool turned = true;
int threshold = 2500;
int followSpeed = 50;

struct
{
	unsigned int milli;
	unsigned int tStart;
	bool set;
} Timer;

bool timerPassed( Timer* pThis )
{
	if (nPgmTime >= pThis->tStart + pThis->milli)
	{
		pThis->set = false;
		return true;
	}
	 return false;
}

void startTimer( Timer* pThis, unsigned int milli )
{
	pThis->tStart = nPgmTime;
	pThis->milli = milli;
	pThis->set = true;
}

#endif //_CONSTANTS_H
