#include <math.h>

double Rt;
double Temp;
double ResTherm = 9990.6;     //10 kohm resistance  
double R0 = 4700;             //4.7 kohm thermistor 
double beta = 3950;           //value of beta of the sensor                      
double T0 = 298;              //kelvin --> 25°   

  
double Thermistor(int RawADC) {
  
Rt = ((1024 - (double)RawADC)/(double)RawADC)*ResTherm;       //computation of Rt, which depends on the external temperature
Temp = 1.0 /( (1.0/298) + (1.0/3950) * log(Rt/R0) );          //implementation of the temperature formula
Temp = Temp - 273.15;   //convert K to °C                     //conversion


Serial.print("ADC: ");   Serial.print(RawADC);  Serial.println("/1024");
Serial.print("Rt: ");  Serial.print(Rt);      Serial.println(" ohm");

return Temp;

}

void setup() {
  pinMode(A3,INPUT);
  Serial.begin(9600);
}

double output;
double value;

void loop() {
  output= analogRead(A3);
  value = Thermistor(output);
  Serial.print("Temperatura: "); Serial.println(value,3); 
  delay(100);
}
