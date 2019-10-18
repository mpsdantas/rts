#include "PWM.h"

PWM::PWM(pwmName pinName)
{
	this->pwmPin = pinName;
	loadPWM();
	setPwmBoard();
	
}

void PWM::loadPWM()
{
	//TODO Adicionar clausula que checa se comando ja foi executado
	system("sudo sh -c \"echo 'cape-universaln' > /sys/devices/platform/bone_capemgr/slots\"");
}

void PWM::setPwmBoard(){
	std::cout << "Loading capemgr" << endl;
	generatePathPwm(getFolderName(fixPathPwm0, "pwmchip"), 
			getFolderName(fixPathPwm1, "pwmchip"), 
			getFolderName(fixPathPwm2, "pwmchip"));

	switch (this->pwmPin){
		case 0:
			if(getFolderName(this->pwm2, "pwm-6:1") == "Folder not found"){
				system(("sudo sh -c 'echo 0 > " + this->pwm2 + "/export'").c_str()); 
			}
			this->baseDir = this->pwm2 + "/pwm-6:1";
			break;
		case 1:
			if(getFolderName(this->pwm2, "pwm-6:0") == "Folder not found"){
				system(("sudo sh -c 'echo 1 > " + this->pwm2 + "/export'").c_str());	
			}
			this->baseDir = this->pwm2 + "/pwm-6:0";
			break;
		case 2:
			if(getFolderName(this->pwm1, "pwm-3:0") == "Folder not found"){
				system(("sudo sh -c 'echo 0 > " + this->pwm1 + "/export'").c_str()); 
			}
			this->baseDir = this->pwm1 + "/pwm-3:0";
			break;
		case 3:
			if(getFolderName(this->pwm1, "pwm-3:1") == "Folder not found"){
				system(("sudo sh -c 'echo 1 > " + this->pwm1 + "/export'").c_str());
			}
			this->baseDir = this->pwm1 + "/pwm-3:1";
			break;
		case 4:
			if(getFolderName(this->pwm0, "pwm-1:1") == "Folder not found"){
				system(("sudo sh -c 'echo 0 > " + this->pwm0 + "/export'").c_str()); 
			}
			this->baseDir = this->pwm0 + "/pwm-1:1";
			break;
		case 5:
			if(getFolderName(this->pwm0,  "pwm-1:0") == "Folder not found"){
				system(("sudo sh -c 'echo 1 > " + this->pwm0 + "/export'").c_str());
			}
			this->baseDir = this->pwm0 + "/pwm-1:0";
			break;
		default:
			std::cout << "Pino invalido" << endl;
		
	} 
	
	system(("config-pin " + pwmMap[pwmPin] + " pwm").c_str());
}


void PWM::setPeriod(int period)
{	
	std::fstream fs;
	fs.open(this->baseDir + "/period", fstream::out);
	fs << period;
	fs.close();	
}

int PWM::getPeriod()
{
	float period;
	std::fstream fs;
	fs.open(this->baseDir + "/period", fstream::in);
	fs >> period;
	fs.close();
	return period;
}

void PWM::setDutyCycle(int duty)
{
	std::fstream fs;
	fs.open(this->baseDir + "/duty_cycle", fstream::out);
	fs << duty;
	fs.close();
}

int PWM::getDutyCycle()
{
	int duty;
	std::fstream fs;
	fs.open(this->baseDir + "/duty_cycle", fstream::in);
	fs >> duty;
	fs.close();
	return duty;
}

void PWM::setState(statePwm state)
{
	if (state == 0 || state == 1){
		std::fstream fs;
		fs.open(this->baseDir + "/enable", fstream::out);
		fs << state;
		fs.close();
	}
}

int PWM::getState()
{
	int state;
	std::fstream fs;
	fs.open(this->baseDir + "/enable", fstream::in);
	fs >> state;
	fs.close();
	return state;
}


string PWM::getFolderName(string path, string pattern) {	
	struct dirent *entry;
	int count;	
	DIR *dir = opendir(path.c_str());
	do {
		dir = opendir(path.c_str());
	} while (dir == NULL);
	
	
	do {
		rewinddir(dir);
		count = 0;
		while ((entry = readdir(dir)) != NULL) {
			count++;
			if (count > 2){
				if (entry->d_type == DT_DIR && strstr(entry->d_name, pattern.c_str()) != NULL) {
					return entry->d_name;
				}
			}
		}
	} while (count < 3);

	closedir(dir);	
	return "Folder not found";

}

void PWM::generatePathPwm(string chipName0, string chipName1, string chipName2 ){
	this->pwm0 = fixPathPwm0 + chipName0;
	this->pwm1 = fixPathPwm1 + chipName1;
	this->pwm2 = fixPathPwm2 + chipName2;
}



