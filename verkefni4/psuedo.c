bool pause = false;
bool reversing = false;
Timer turnTimer;
Timer driveTimer;
unsigned int maxTurnTime = 10;
unsigned int maxDriveTime = 5;
unsigned int minDist = 20;

void drive(speed=80, key, reversed=false)
{
	//Drive forwards(backwards if reversed) with a given speed
}

void turn(angle, key, speed=80)
{
	//Turn a given amount of degrees with a given speed
}

task button
{
	if(pauseSwitch)
		stopAllTasks();
	if(pauseButton)
		pause = !pause;
	if(lightSensor < minLightValue)
		pause = true;
}

task main
{
	startTask(button);
	while(true)
	{
		if(!pause)
		{
			if(sonicSensorDistance <= minDist)
			{
				restart driveTimer with maxDriveTime as milli
				if(turnTime >= maxTurnTime)
				{
					if(!reversing)
					{
						reversing = true;
						minDist += 5;
					}
					if(drive(1, reversed=true))
					{
						restart turnTimer with maxTurnTime as milli
						reversing = false;
					}
				}
				else
				{
					reversing = false;
					turn(1);
				}
			}
			else
			{
				reversing = false;
				drive();
				restart turnTimer with maxTurnTime as milli
			}
		}
	}
}