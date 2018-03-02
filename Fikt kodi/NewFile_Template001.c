#pragma config(Sensor, dgtl4,  leftEncoder,    sensorQuadEncoder)
#pragma config(Sensor, dgtl6,  rightEncoder,   sensorQuadEncoder)
#pragma config(Motor,  port3,           leftMotor,     tmotorServoContinuousRotation, openLoop, reversed)
#pragma config(Motor,  port2,           rightMotor,    tmotorServoContinuousRotation, openLoop)

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

void moveForward()
{
	if(SensorValue[rightEncoder] == SensorValue[leftEncoder]) // If rightEncoder has counted the same amount as leftEncoder:
	{
		// Move Forward
		motor[rightMotor] = 80;		    // Right Motor is run at power level 80
		motor[leftMotor]  = 80;		    // Left Motor is run at power level 80
	}
	else if(SensorValue[leftEncoder] > SensorValue[rightEncoder])	// If rightEncoder has counted more encoder counts
	{
		// Turn slightly right
		motor[rightMotor] = 60;		    // Right Motor is run at power level 60
		motor[leftMotor]  = 80;		    // Left Motor is run at power level 80
	}
	else	// Only runs if leftEncoder has counted more encoder counts
	{
		// Turn slightly left
		motor[rightMotor] = 80;		    // Right Motor is run at power level 80
		motor[leftMotor]  = 60;		    // Left Motor is run at power level 60
	}
}

void turnRight()
{
	motor[rightMotor] = 0;
	motor[leftMotor]  = 80;
}


task main()
{
	SensorValue[rightEncoder] = 0;
	SensorValue[leftEncoder]  = 0;
	tim.set=false;
	while (SensorValue[leftEncoder] > -509)
	{
		moveForward();
	}
	SensorValue[rightEncoder] = 0;
	SensorValue[leftEncoder]  = 0;
	while (SensorValue[leftEncoder] > -1074)
	{
		turnRight();
	}
}
