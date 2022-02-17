#include "rc.hpp"
float gam=0;
float R=9999;
float V=1;
float L=0.945;
float C=0.63;
uint16_t vel_period_max=502;
uint16_t vel_period_zero=385;
uint16_t dir_period_max=502;
uint16_t dir_period_zero=385;
uint16_t rx_period_zero=385;
uint16_t rx_period_max=502;
uint16_t ry_period_zero=385;
uint16_t ry_period_max=502;
float k_vel=5;
float k_dir=pi/2;
float k_gam=pi/2;
float r_wheel=0.2;

double sign(double a){
	if (a>0) return 1;
	else if (a<0) return -1;
	else return 0;
}

int16_t intSign(double a){
	if (a>0) return 1;
	else if (a<0) return -1;
	else return 0;
}

char checkDate(uint32_t date){
	if ((date>200) && (date<1000)) return 1;
	else return 0;
}

uint8_t checkLevel(uint16_t data)
{
	if(data>385)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

void normaliz(uint16_t vel_mean, uint16_t rx_mean, uint16_t dir_mean, uint16_t ry_mean, uint16_t elevdr){
	float d_vel=0;
	float d_ry=0;
	float Rg0=0;
	float d_rx=0;
	float d_dir=0;
	float vel_coef=0;
	// if (elevdr==1){
	// 	gam=0;
	// 	V=vel_mean/100;
	// 	R=L/2/tan(dir_mean/100);
	// 	if (fabs(R)<0.1) R=0.00001*sign(R);
	// 	if (fabs(R)>50) R=10000;
	// 	return;
	// }
	d_dir=(dir_mean-dir_period_zero);
	d_vel=(vel_mean-vel_period_zero);
	d_rx=(rx_mean-rx_period_zero);
	d_ry=ry_mean-ry_period_zero;
	
	if (fabs(d_dir)<20) d_dir=0;
	if (fabs(d_vel)<20) d_vel=0;
	if (fabs(d_rx)<20) d_rx=0;
	if (fabs(d_ry)<20) d_ry=0;
	
	Rg0=d_dir*k_dir/(dir_period_max-dir_period_zero);
	if (fabs(Rg0)>k_dir) Rg0=sign(Rg0)*k_dir;
	R=L/2/tan(Rg0)*10;
	if (fabs(R)<0.1) R=0.1*sign(R);//минимальный радиус поворота
	if (fabs(R)>50) R=10000;
	
	V=(d_vel)/((float)(vel_period_max-vel_period_zero));
	vel_coef=(d_rx/((float)(rx_period_max-rx_period_zero)));
	V=V*vel_coef;

	gam=(d_ry)/(ry_period_max-ry_period_zero)*k_gam;
	if (fabs(gam)<0.01) gam=0;
	if (fabs(gam)>(pi/4-0.1)) gam=pi/4*sign(gam);//предельные углы поворота
	if (gam!=0) R=100000;
}