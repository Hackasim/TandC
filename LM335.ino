#define INT_REF
const double V_ref=4.9556;
const double V_int=1.09;
const double delta_D_5= 2; 
const double delta_D_11= 2; 
const double delta_V_ref= 0.25;
const double delta_V_int= 0.1;
const double delta_T_sensor= 0;
double input;
double temp;
double error;

void setup() {
  pinMode(A0,INPUT);
  Serial.begin(9600);
  #ifdef INT_REF
    analogReference(INTERNAL);      //set the Arduino reference as INTERNAL (1.1V)
  #endif
}

void loop() {
  input=analogRead(A0);
  Serial.print("Input:");
  Serial.println(input);                      //print output of the ADC
  #ifdef INT_REF
    temp= (319.753*input*V_int)/1024;                                                                   //calibration function with the internal reference
    error= (V_int/(10.24*3.19753)*delta_D_11 + (input/(10.24*3.19753))*delta_V_int + delta_T_sensor;    //computation of the measure error
  #else
    temp= 100*input*V_ref/1024;                                                                         //calibration function with the external reference
    error= (V_ref/10.24)*delta_D_5 + (input/10.24)*delta_V_ref + delta_T_sensor;                        //computation of the correlated error
  #endif
  Serial.println(temp);
  Serial.println(error);
  delay(1000);
} 







