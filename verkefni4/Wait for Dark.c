#pragma config(Sensor, in2,    lightSensor,    sensorReflection)
#pragma config(Sensor, dgtl12, BreakSwitch,    sensorTouch)
#pragma config(Motor,  port2,           rightMotor,    tmotorServoContinuousRotation, openLoop, reversed)
#pragma config(Motor,  port3,           leftMotor,     tmotorServoContinuousRotation, openLoop)








task BREAKS()
{
	while(true)
	{
		if (SensorValue[BreakSwitch] || vexRT[Btn8U])
			StopAllTasks();
	}
}



task main()
{
	StartTask(BREAKS);
	while(true)
		{
		if(SensorValue(lightSensor) > 230)
		{
			motor[rightMotor] = -63;
			motor[leftMotor]  = -63;
		}
		else
		{
			motor[rightMotor] = 0;
			motor[leftMotor]  = 0;
		}
	}
}
