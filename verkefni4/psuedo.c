unsigned int minDist = 35;

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
		if(sensorValue(sonarSensor) > minDist)
		{
			
		}
	}
}