#pragma config(UART_Usage, UART1, uartVEXLCD, baudRate19200, IOPins, None, None)
#pragma config(UART_Usage, UART2, uartNotUsed, baudRate4800, IOPins, None, None)
#pragma config(Sensor, in3,    lineFollowerLEFT, sensorLineFollower)
#pragma config(Sensor, in4,    lineFollowerCENTER, sensorLineFollower)
#pragma config(Sensor, in5,    lineFollowerRIGHT, sensorLineFollower)
#pragma config(Sensor, dgtl12, breakSwitch,    sensorTouch)
#pragma config(Motor,  port2,           rightMotor,    tmotorServoContinuousRotation, openLoop, reversed)
#pragma config(Motor,  port3,           leftMotor,     tmotorServoContinuousRotation, openLoop)


/*
			|Analog ----------------------------------|
			|1|...|PM1-Potentiometer Arm							|
			|2|...|LS1-Light sensor 1-Photon sensor		|
			|3|...|LFL-Line Follower Left							|
			|4|...|LFM-Line Follower Middle						|
			|5|...|LFR-Line Follower Right						|
			|Digital ---------------------------------|
			|1 |..|SS1-Sonar Sensor 1									|
			|2 |..|SS2-Sonar Sensor 2									|
			|3 |..|T1 -Touch 1-Að framan							|
			|4 |..|LE1-Left Encoder 1									|
			|5 |..|LE2-Left Encoder 2									|
			|6 |..|RE1-Right Encoder 1								|
			|7 |..|RE2-Right Encoder 2								|
			|11|..|G1 -Gyroscope 1										|
			|12|..|BRS-Break Switch										|
			|Motor -----------------------------------|
			|2|...|RWM-Right Wheel Motor							|
			|3|...|LWM-Left Wheel Motor								|
			|5|...|CLM-M3-Claw Motor									|
			|6|...|ARM-Arm Motor											|
			|UART ------------------------------------|
			|1|...|LCD-LCD Display										|
			|-----------------------------------------|
*/


task stopper
{
	while(true)
	{
		if(vexRT[Btn8U] || SensorValue[breakSwitch])
			StopAllTasks();
	}
}


//+++++++++++++++++++++++++++++++++++++++++++++| MAIN |+++++++++++++++++++++++++++++++++++++++++++++++
task main()
{
	StartTask(stopper);

  int threshold = 2500;      /* found by taking a reading on both DARK and LIGHT    */
                            /* surfaces, adding them together, then dividing by 2. */
  while(true)
  {
    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -+
  	bLCDBacklight = true;
  	displayLCDCenteredString(0, "LEFT  CNTR  RGHT");        //  Display   |
    displayLCDPos(1,0);                                     //  Sensor    |
    displayNextLCDNumber(SensorValue(lineFollowerLEFT));    //  Readings  |
    displayLCDPos(1,6);                                     //  to LCD.   |
    displayNextLCDNumber(SensorValue(lineFollowerCENTER));  //            |
    displayLCDPos(1,12);                                    //  L  C  R   |
    displayNextLCDNumber(SensorValue(lineFollowerRIGHT));   //  x  x  x   |
    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -+

    if(SensorValue(lineFollowerCENTER) > threshold)
    {
      motor[leftMotor]  = -50;
      motor[rightMotor] = -50;
    }
    else if(SensorValue(lineFollowerRIGHT) > threshold)
    {
      motor[leftMotor]  = -50;
      motor[rightMotor] = 0;
    }
    else if(SensorValue(lineFollowerLEFT) > threshold)
    {
      motor[leftMotor]  = 0;
      motor[rightMotor] = -50;
    }
    writeDebugStreamLine("Left: %d; Right: %d;", motor[leftMotor], motor[rightMotor]);
  }
}
