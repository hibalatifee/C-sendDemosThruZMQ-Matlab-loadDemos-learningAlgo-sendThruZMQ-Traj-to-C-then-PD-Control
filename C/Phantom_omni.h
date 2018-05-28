/*******************************************************************************
Implementation file
***************************************************
****************************/
#include "Global.h"
		

//----------------------------Device Asynchronous Callback----------------------

HDCallbackCode HDCALLBACK Start_teleoperation(void *pUserData) //This code runs at every 1k hertz 

{

		//cout<<"callback"<<endl;
		//master_omni();	
	//	fixed_dominance();

		hdBeginFrame(SlaveHandle);

	//added for d gain
	slv.prev[0] = slv.position[0];
	slv.prev[1] = slv.position[1];
	slv.prev[2] = slv.position[2];

	hdGetDoublev(HD_CURRENT_POSITION, slv.position);

	slv.position[0] = slv.position[0] - slv.init_position[0];
	slv.position[1] = slv.position[1] - slv.init_position[1];
	slv.position[2] = slv.position[2] - slv.init_position[2];

	slv.disp[0] =  slv.position[0] - slv.prev[0];	
	slv.disp[1] =  slv.position[1] - slv.prev[1];
	slv.disp[2] =  slv.position[2] - slv.prev[2];
	//till here, for d gain

	//hdGetDoublev(HD_CURRENT_POSITION, slv.position); //initially for p gain only


	//if (!switch_b)
	//{
		//for (int i = 1;i <= 574;i++)
		//{
			//if (omni_cnt <20000)   //delay of 4 sec
			//{
			//omni_cnt++;
			//}
			//else
			//{

		if (j<=20000){
		slv.force[0] =  (Omni_Saturation(K_simul*(PX[j] - slv.position[0]) + slv_damping*slv.disp[0]))/3;
		cout<<"Slave force 1: "<<slv.force[0]<<endl;
		//Sleep(1);
		slv.force[1] =  (Omni_Saturation(K_simul*(PY[j] - slv.position[1])+ slv_damping*slv.disp[1]))/3;
		cout<<"Slave force 2: "<<slv.force[1]<<endl;
		//Sleep(1);
		slv.force[2] =  (Omni_Saturation(K_simul*(PZ[j] - slv.position[2])+ slv_damping*slv.disp[2]))/20;
		cout<<"Slave force 3: "<<slv.force[2]<<endl;
		}
		
		j++;
		//Sleep(1);
			//omni_cnt=0;
			//}
		hdMakeCurrentDevice(SlaveHandle);
		hdSetDoublev(HD_CURRENT_FORCE, slv.force);
		


	hdEndFrame(SlaveHandle);

	/*if(somecomdition)
	{
		return HD_CALLBACK_DONE;
	
	}*/

	//}


	return HD_CALLBACK_CONTINUE;
}


/*******************************************************************************
Functions
*******************************************************************************/

void omni_init(void)

{
	//MasterHandle = hdInitDevice(MASTER_DEVICE_NAME);
	//hdEnable(HD_FORCE_OUTPUT);

//#ifdef SLAVE_DEVICE_NAME
	SlaveHandle = hdInitDevice(SLAVE_DEVICE_NAME);
	hdEnable(HD_FORCE_OUTPUT);
//#endif

	hdStartScheduler();
	//hdMakeCurrentDevice(Master);

	for (int i = 0; i<3; i++)
	{
		/*for (int j = 0; j<=2; j++) //commented out by Hiba
		
		{
			force[j][i] = 0.0;
			position[j][i] = 0.0;
			angles[j][i] = 0.0;
			init_position[j][i] = 0.0;
			init_angles[j][i] = 0.0;
		}*/
		
		//mst.prev[i] = 0.0;
		//mst.position[i] = 0.0;
		//mst.force[i] = 0.0;
		//mst.disp[i] = 0.0;
		//mst.after_auth[i] = 0.0;
		//mst.angle[i] = 0.0;

		//force[i] = 0.0;
		//position[i] = 0.0;
		//angles[i] = 0.0;
		//init_position[i] = 0.0;
		//init_angles[i] = 0.0;

		slv.prev[i] = 0.0;
		slv.position[i] = 0.0;
		slv.force[i] = 0.0;
		slv.disp[i] = 0.0;
		slv.after_auth[i] = 0.0;
		slv.angle[i] = 0.0;

		slv_p.prev[i] = 0.0;
		slv_p.position[i] = 0.0;
		slv_p.force[i] = 0.0;
		slv_p.disp[i] = 0.0;
		slv_p.after_auth[i] = 0.0;
		slv_p.angle[i] = 0.0;

		simul.prev[i] = 0.0;
		simul.position[i] = 0.0;
		simul.force[i] = 0.0;
		simul.disp[i] = 0.0;
		simul.after_auth[i] = 0.0;

		order_pos[i] = 0;

		diff_e1[i] = 0.0;   prev_e1[i] = 0.0;	
		diff_e2[i] = 0.0;	prev_e2[i] = 0.0;
		
		n[i] = 0.0;
	}

	alpha[0] = 0.5;	alpha[1] = 0.5;	alpha[2] = 0.5;  // Dominance Value

	energy_user1[0] = 0.0;	energy_user1[1] = 0.0;	energy_user1[2] = 0.0;
	energy_user2[0] = 0.0;	energy_user2[1] = 0.0;	energy_user2[2] = 0.0;

	omni_cnt = 0;
	
	Phantom_Started = false;
	
}

/*******************************************************************************
Call Backs
*******************************************************************************/
HDCallbackCode HDCALLBACK DeviceCalibrate(void *pUserData)
{
	//hdBeginFrame(MasterHandle);
	//hdGetDoublev(HD_CURRENT_POSITION, init_position[0]);
	//hdGetDoublev(HD_CURRENT_GIMBAL_ANGLES, init_angles[0]);
	//hdEndFrame(hdGetCurrentDevice());
	
	hdBeginFrame(SlaveHandle);
	hdGetDoublev(HD_CURRENT_POSITION, slv.init_position);
	//hdGetDoublev(HD_CURRENT_GIMBAL_ANGLES, slv.init_angles);
	hdEndFrame(hdGetCurrentDevice());
	
	return HD_CALLBACK_DONE;
}


//----------------------------------------------------------------------------

void omni_calibarate(void)
{
	if (!Phantom_Started) 
	{
		hdScheduleSynchronous(DeviceCalibrate, position, HD_MIN_SCHEDULER_PRIORITY);
	}
}

//----------------------------------------------------------------------------

void omni_start(void)
{
	if (!Phantom_Started)
	{
		j=1;
		Phantom_Started = true;
		hdScheduleAsynchronous(Start_teleoperation, position, HD_DEFAULT_SCHEDULER_PRIORITY);
	}
}

//----------------------------------------------------------------------------

void close (void)
{
	// For cleanup, unschedule our callbacks and stop the servo loop.
	hdStopScheduler();
	//hdUnschedule(teleoperation);
	hdDisableDevice(MasterHandle);
	hdDisableDevice(SlaveHandle);

	file.close(); //close data.txt file
	debug.close(); //close debug.txt file
}
//----------------------------------------------------------------------------

inline void master_omni()   
{
	/*
	//hdBeginFrame(MasterHandle);

	//hdGetDoublev(HD_CURRENT_POSITION, mst.position);

	hdBeginFrame(SlaveHandle);

	//added for d gain
	slv.prev[0] = slv.position[0];
	slv.prev[1] = slv.position[1];
	slv.prev[2] = slv.position[2];

	hdGetDoublev(HD_CURRENT_POSITION, slv.position);

	slv.position[0] = slv.position[0] - slv.init_position[0];
	slv.position[1] = slv.position[1] - slv.init_position[1];
	slv.position[2] = slv.position[2] - slv.init_position[2];

	slv.disp[0] =  slv.position[0] - slv.prev[0];	
	slv.disp[1] =  slv.position[1] - slv.prev[1];
	slv.disp[2] =  slv.position[2] - slv.prev[2];
	//till here, for d gain

	//hdGetDoublev(HD_CURRENT_POSITION, slv.position); //initially for p gain only


	//if (!switch_b)
	//{
		cout<<"Entering the switch now"<<endl;
		//for (int i = 1;i <= 574;i++)
		//{
			//if (omni_cnt <20000)   //delay of 4 sec
			//{
			//omni_cnt++;
			//}
			//else
			//{


		slv.force[0] =  Omni_Saturation(K_simul*(px[i] - slv.position[0]) + slv_damping*slv.disp[0]);
		cout<<"Slave force 1: "<<i<<endl;
		//Sleep(1);
		slv.force[1] =  Omni_Saturation(K_simul*(py[i] - slv.position[1])+ slv_damping*slv.disp[1]);
		cout<<"Slave force 2: "<<i<<endl;
		//Sleep(1);
		slv.force[2] =  Omni_Saturation(K_simul*(pz[i] - slv.position[2])+ slv_damping*slv.disp[2]);
		cout<<"Slave force 3: "<<i<<endl;
		//Sleep(1);
			//omni_cnt=0;
			//}
		hdMakeCurrentDevice(SlaveHandle);
		hdSetDoublev(HD_CURRENT_FORCE, slv.force);
		
		/*if (omni_cnt <20000)   //delay of 4 sec
			{
			omni_cnt++;
			}*/
		
	//}
		
	//}
	//hdEndFrame(MasterHandle);

	
	//slv.force[0] *= -1.0;
	//slv.force[1] *= -1.0;
	//slv.force[2] *= -1.0;
	//hdMakeCurrentDevice(MasterHandle);
	//hdSetDoublev(HD_CURRENT_FORCE, slv.force);

	//hdEndFrame(SlaveHandle); */
	

 }
//----------------------------------------------------------------------------
inline void fixed_dominance()
{
	

}

//----------------------------------------------------------------------------
double Omni_Saturation(double force)
{
	if (force<-LIMIT_FORCE)

		force = -LIMIT_FORCE;

	if (force>LIMIT_FORCE)

		force = LIMIT_FORCE;

	return force;
}				

/*****************************************************************************/
