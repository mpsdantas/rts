#include <iostream>
#include "PWM/PWM.h"
#include "ADC/Adc.h"
#include "unistd.h"

int main(int argc, char * argv[]){
	ADC adc(AINx::AIN5);
	PWM pwm(P8_13);
	pwm.setState(run);
	int period = 0;
	
	while (true) {
		float dutyCycle  = adc.getPercentValue();
		// cout << "Duty Value " << dutyCycle << endl;
		period = 1000000000;
		pwm.setPeriod(period);
		pwm.setDutyCycle(dutyCycle*period/100);
	}
	
	return 0;
}
