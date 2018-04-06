#pragma config(Sensor, dgtl4,  leftEncoder,    sensorQuadEncoder)
#pragma config(Sensor, dgtl6,  rightEncoder,   sensorQuadEncoder)
#pragma config(Motor,  port3,           leftMotor,     tmotorServoContinuousRotation, openLoop, reversed)
#pragma config(Motor,  port2,           rightMotor,    tmotorServoContinuousRotation, openLoop)

#define BIG_D 32.4
#define LITTLE_D 10.4
#define LITTLE_D_C 32.67
#define CORRECTION_CONSTANT 1.02


struct
{
	unsigned int milli;
	unsigned int tStart;
	bool set;
} Timer;

/*Timer createTimer()
{
	Timer tim;
	tim.set = false;
	return tim;
}*/

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

Timer tim;//createTimer();

void stopMotors()
{
	motor[rightMotor] = 0;
	motor[leftMotor]  = 0;
}

void resetEncoders()
{
	SensorValue[rightEncoder] = 0;
	SensorValue[leftEncoder]  = 0;
}

void reset(unsigned int sleepMilli = 0)
{
	stopMotors();
	resetEncoders();
	Sleep(sleepMilli);
}

string moveKey = "";
bool moveForward(unsigned int distance, const string key, unsigned int waitTime = 0)
{
	int amount = ((float)distance/LITTLE_D_C)*300.0;
	if(moveKey != key)
	{
		reset(waitTime);
		moveKey = key;
	}
	if(SensorValue[leftEncoder] > -amount && SensorValue[rightEncoder] > -amount)
	{
		motor[rightMotor] = 80;
		motor[leftMotor]  = 80;
		return false;
	}
	return true;
}

string turnKey = "";
bool turn(int degs, const string key, signed char speed=80, unsigned int waitTime = 0)
{
	int amount = ((BIG_D/LITTLE_D)*(float)abs(degs))*CORRECTION_CONSTANT;
	if(turnKey != key)
	{
		reset(waitTime);
		turnKey = key;
	}
	if(degs > 0)
	{
		if(SensorValue[leftEncoder] > -amount && SensorValue[rightEncoder] < amount)
		{
			motor[rightMotor] = -speed;
			motor[leftMotor]  = speed;
			return false;
		}
		return true;
	}
	else if(degs < 0)
	{
		if(SensorValue[leftEncoder] < amount && SensorValue[rightEncoder] > -amount)
		{
			motor[rightMotor] = speed;
			motor[leftMotor]  = -speed;
			return false;
		}
		return true;
	}
	return true;
}

task main()
{
	resetEncoders();
	tim.set=false;
	while(!moveForward(50, "move1", 500)){}
	while(!turn(90, "turn1", 80, 500)){}
	while(!moveForward(50, "move2", 500)){}
	while(!turn(-90, "turn2", 80, 500)){}
	while(!moveForward(50, "move3", 500)){}
	while(!turn(-90, "turn3", 80, 500)){}
	while(!moveForward(50, "move4", 500)){}
}
