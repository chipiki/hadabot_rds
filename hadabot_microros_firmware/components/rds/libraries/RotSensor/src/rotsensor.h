#ifndef __ROTSENSOR_H
#define __ROTSENSOR_H

#include "motor.h"
#include "Arduino.h"


enum ERotSensorMode {FRONT_CHANGE, FRONT_HIGH};


class RotationSensor {
public:
	RotationSensor(char* _sensor_name, uint32_t _sensor_pin, uint8_t _timer_num, Motor* _pMotor, int _disk_holes_count = 20, ERotSensorMode _mode = FRONT_CHANGE, double _hole_width_ratio = 0.5);
	~RotationSensor();
	
	inline float getAngularVelocity() {return angular_velocity;};
	inline void setAngularVelocity(float _angular_velocity) {angular_velocity = _angular_velocity;};
	
	inline uint32_t getSensorPIN() {return sensor_pin;};
	inline hw_timer_t* getHwTimer() {return timer;}
	
	inline int getSensorLevel() {return sensor_level;}
	inline void setSensorLevel(int _sensor_level) { sensor_level = _sensor_level;}
	
	inline void setLastMeasuredTime(double _last_measured_time) {last_measured_time = _last_measured_time;}
	inline double getLastMeasuredTime() {return last_measured_time;}
	
	inline xQueueHandle getSensorEvtQueue() {return sensor_evt_queue;}
	inline Motor* getMotor() {return pMotor;}
	
	inline portMUX_TYPE& getTimerMux() {return timerMux;}
	inline ERotSensorMode getSensorMode() {return mode;}
	inline int getDiskHolesCount() {return disk_holes_count;}
	inline double getHoleWidthRatio() {return hole_width_ratio;}
	
protected:
	char* sensor_name;
	uint32_t sensor_pin;
	uint8_t timer_num;
	hw_timer_t * timer = NULL;
	Motor* pMotor;
	
	int disk_holes_count;
	ERotSensorMode mode;
	double hole_width_ratio; // in percent
	
	
	int sensor_level;
	double last_measured_time; // in seconds
	float angular_velocity;
	volatile SemaphoreHandle_t timerSemaphore;
	portMUX_TYPE timerMux;
	
	xQueueHandle sensor_evt_queue = NULL;
};

#endif 