#include <device.h>
#include<stdio.h>
#include<stdint.h>
#include<math.h>

float fminf(float a, float b){
	float res;
	if (a>b){
		res=b;}
	else{
		res=a;}
	return res;
}
float fmaxf(float a, float b){
	float res;
	if (a<b){
		res=b;}
	else{
		res=a;}
	return res;
}

//When sending packets, all the numbers should be converted into integer numbers by thefollowing functions and then sent to the motor.
int float_to_uint(float x, float x_min, float x_max, unsigned int bits)
{
	/// Converts a float to an unsigned int, given range and number of bits ///
	float span = x_max - x_min;
	
	if(x < x_min) x = x_min;	
	else if(x > x_max) x = x_max;
	
	return (unsigned int) ((x- x_min)*((float)((1<<bits)/span)));
}

uint8 msg_send[8] = {0,0,0,0,0,0,0,0};

// send routine code
void pack_cmd(uint8* msg, float p_des, float v_des, float kp, float kd, float t_ff){

	/// limit data to be within bounds ///
	float P_MIN =-12.5;
	float P_MAX =12.5;
	float V_MIN =-50;
	float V_MAX =50;
	float T_MIN =-25;
	float T_MAX =25;
	float Kp_MIN =0;
	float Kp_MAX =500;
	float Kd_MIN =0;
	float Kd_MAX =5;
	float Test_Pos=0.0;
    
	p_des = fminf(fmaxf(P_MIN, p_des), P_MAX);
	v_des = fminf(fmaxf(V_MIN, v_des), V_MAX);
	kp = fminf(fmaxf(Kp_MIN, kp), Kp_MAX);
	kd = fminf(fmaxf(Kd_MIN, kd), Kd_MAX);
	t_ff = fminf(fmaxf(T_MIN, t_ff), T_MAX);
	
	/// convert floats to unsigned ints ///
	int p_int = float_to_uint(p_des, P_MIN, P_MAX, 16);
	int v_int = float_to_uint(v_des, V_MIN, V_MAX, 12);
	int kp_int = float_to_uint(kp, Kp_MIN, Kp_MAX, 12);
	int kd_int = float_to_uint(kd, Kd_MIN, Kd_MAX, 12);
	int t_int = float_to_uint(t_ff, T_MIN, T_MAX, 12);
	
	/// pack ints into the can buffer ///
	msg[0] = p_int>>8; // Position 8 higher
	msg[1] = p_int&0xFF; // Position 8 lower
	msg[2] = v_int>>4; // Speed 8 higher
	msg[3] = ((v_int&0xF)<<4)|(kp_int>>8); //Speed 4 bit lower KP 4bit higher
	msg[4] = kp_int&0xFF; // KP 8 bit lower
	msg[5] = kd_int>>4; // Kd 8 bit higher
	msg[6] = ((kd_int&0xF)<<4)|(t_int>>8); //K 4 bit lower torque 4 bit higher
	msg[7] = t_int&0xff; // torque 4 bit lower
}


CAN_TX_MSG data_tx; //can data type def
CAN_TX_MSG* data_tx_ptr = &data_tx;

void main()
{	CyGlobalIntEnable;
	CAN_GlobalIntEnable();
	CAN_Start();
	
	int i = 0;
	data_tx.id = 1;  //default id
	data_tx.rtr = 0; //standard message
	data_tx.ide = 0; //standard message
	data_tx.dlc = 8; //8 bytes
	data_tx.irq = 0; //interrupt disable
	
	
	
	//send motor control cmd
	float p_des = 0;
	float v_des = 0;
	float kp = 5;       // for position control, keep kp = 5, kd = 0.5
	float kd = 1;
	float t_ff = 0;
	int count = 1;
	float P_step = 0.01;  // step size can be even 0.001
	float t = 0;
	float r = 0;
	
	float freq = 5;                  // we need 1Hzs, f = 1Hz,
	float w = 2*3.141*freq;       // wt = 2*pi*f*t, and t = counter/45.5Hzs  
	
	uint8 set_controlMode_bits[8] = {0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xfc};
	uint8 exit_controlMode_bits[8] = {0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xfd};
	
	//set motor in mit mode
		data_tx_ptr->msg = set_controlMode_bits;
		CAN_SendMsg(data_tx_ptr);
		CyDelay(1500);
		
	//set the current position as zero position
	uint8 set_zeroPos_bits[8] = {0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xfe};
	data_tx_ptr->msg = set_zeroPos_bits;
	CAN_SendMsg(data_tx_ptr);
	CyDelay(500);
	
	
/*
		uint8 cw_bits[8] = {0x7f,0xff,0xf4,0x40,0x00,0x33,0x37,0xff};
		uint8 ccw_bits[8] = {0x7f,0xff,0x0b,0x90,0x00,0x33,0x37,0xff};
*/
/*
		data_tx_ptr->msg = cw_bits;
		CAN_SendMsg(data_tx_ptr);
		CyDelay(1500);
*/
/*
		//exit motor mode in mit mode
		data_tx_ptr->msg = exit_controlMode_bits;
		CAN_SendMsg(data_tx_ptr);
*/

		

	
	for (;;){
	

		/*
		// Velocity only mode(keep p_des = 0, kp = 0, kd = 1)
		data_tx_ptr->msg = ccw_bits;
		CAN_SendMsg(data_tx_ptr);
		CyDelay(1500);
	
		//pack_cmd(msg_send, p_des, v_des, kp, kd, t_ff);
		data_tx_ptr->msg = cw_bits;
		CAN_SendMsg(data_tx_ptr);
		CyDelay(1500);
		*/
		
		/*
		if(count>1000)
			{
			p_des = p_des - P_step;
			}
			else
			{
			p_des = p_des + P_step;
			}
		
		count = count +1;
		
		if(count==2000)
		{
		count = 1;
		}
		*/
	
		
		
		/*
		if(count<50)
		{
		r = -180;
		}
		else
		{
		r = 180;
		}
		*/
		
		
		t = count;
        r = 180*sin(w*t);
		p_des = r*3.141/180;
		count = count +1;
	   
	   pack_cmd(msg_send, p_des, v_des, kp, kd, t_ff);
	   data_tx_ptr->msg = msg_send;
	   CAN_SendMsg(data_tx_ptr);
	   CyDelay(5);   // Delay should be there otherwise large vibrations will occur
		
	}
}
