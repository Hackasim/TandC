#define C150
//#define C1

double R;             //expressed in kOhm
double C;             //expressed in nF
double C_computed;
double tau;           //expressed in seconds
double tau_computed;

int stopsample;
double readings[256];       //array to store samples
int index;
double timestart;
double timepassed;

void setup()
{
  Serial.begin(9600);
  pinMode(A0, INPUT);       //pin A0 is an input
  pinMode(8, OUTPUT);       //pin D8 is an output
  digitalWrite(8,HIGH);     //digitalOutput is set to HIGH
  /****************************************************************************
  ***TO UNDERSTAND BETTER THIS PART, READ THE REPORT ABOUT THE C MEASUREMENT***
  ***BASICALLY, THE INTERNAL REGISTERS OF THE BOARD ARE SET AS THE NEEDS OF****
  ***THIS TASK*****************************************************************
  ****************************************************************************/
  ADMUX  = 0b01000000;
  ADCSRA = 0b10111100;      //interrupts are enabled, the prescaler is set to 16 and autotriggering mode
  ADCSRB = 0x00;


  R=2.14832;                //value of the resistor
  #ifdef C1
    C=1000;                 //theoretical value of the capacitance
    stopsample=169;         //real number of the samples to be taken
  #else
    C=150;
    stopsample=25;
  #endif
  
  index=0;
  Serial.println("Setup completed");
  delay(2000);
}

void loop(){
  
  if(index==0){
    bitSet(ADCSRA,ADEN);      //switches on the ADC
    bitSet(ADCSRA,ADSC);      //starts ADC measurements
    digitalWrite(8,LOW);      //start of the C discharging process
    timestart=millis();      
  } 
  
  if(index==stopsample){
    timepassed=1.0/(16.0e6/16.0/13.0)*1e3*(stopsample-1);             //millis()-timestart;
    Serial.println("Acquisition finished...computing the result");
    Serial.println("READING 0");
    Serial.println(readings[0]);
    Serial.println("LAST READING");
    Serial.println(readings[stopsample-1]);
    Serial.println("TIMEPASSED");
    Serial.println(timepassed,5);
    
    tau_computed=timepassed/log(readings[0]/readings[stopsample-1]);  //computation of the TAU
    C_computed=tau_computed/R;                                        //computation of C
    Serial.println(C_computed,5);
    
    for(int i=0; i<stopsample; i++)                                   //print of each sample for 
      Serial.println(readings[i]);                                    //the linear regression

    delay(2000);
    index=0;
  }
}

//INTERRUPT SERVICE ROUTINE
ISR(ADC_vect){
 
  readings[index]=ADCW;
  index++;
  if(index==stopsample){
    bitClear(ADCSRA,ADEN);      //switches off the ADC
    digitalWrite(8,HIGH);       //set the board output HIGH
  }
  
  
    
}
