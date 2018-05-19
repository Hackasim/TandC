#define CALIBRATED
//#define FIND_CALIBRATION_OFFSET
//#define FIND_CALIBRATION_K

double V_ref = 5.0283;      //real value of the theorical 5V provided by Arduino
int N_bits = 10;            //bits of the ADC
double S = 2e-7;            //1 uVolt with Vcc=5V
double output;        
double G = 5 + (80000/17.808);  
double mass;
double ref_mass = 461.0;    //value of the reference mass, used to find the calibration offset

double D_offset = 69.0;     //found after the "FIND_CALIBRATION_OFFSET" piece of code
double K = 0.95;            //found after the "FIND_CALIBRATION_K" piece of code

void setup() {
  Serial.begin(9600);
  analogReference(DEFAULT);   //not necessary
  pinMode(A3,INPUT);          //input for the amplifier
  Serial.println("Setup completed");
}

void loop() {

  output= analogRead(A3); 
  Serial.println(output);
  #ifndef CALIBRATED
    mass = output/(pow(2,N_bits)*S*G);      //computation of the mass when the sensor is not calibrated
  #else
    mass = (output - D_offset)/K;           //computation of the mass at the end of the calibration
  #endif
  Serial.print("The measured mass is:");
  Serial.println(mass);
  delay(2000);

  //the following segment is about the determination of the real calibration function
  //the first piece of code that must be executed
  #ifdef FIND_CALIBRATION_OFFSET
  {
  D_offset = output;                        //computed with m=0;
  Serial.print("The offset is:");
  Serial.println(D_offset);
  delay(2000);
  }
  #endif
  //the last part of the calibration offset
  #ifdef FIND_CALIBRATION_K
  {
  K = (output - D_offset)/ref_mass;         //after the D_offset computation
  Serial.print("The measured K is:");
  Serial.println(K);
  delay(2000);
  }
  #endif
}


