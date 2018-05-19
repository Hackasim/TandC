const double R_f = 989.23;                //fixed R expressed in Ohm...theoretical value=1kOhm
const double Vcc = 4.9556;                //real value of the 5V provided by the board     
const double R_0 = 100;
const double A = 3.9083E-3;               //
const double B = -5.775E-7;               //constants proper of the employed sensor
const double C = -4.183E-12;              //
const double R_thermal = 100;             //thermal resistance...it's value is °C/W
const int n_bits = 10;                    //#bits of the internal ADC
double analog_in;
double temp;
double S_Dout_teta;

void setup() {

  pinMode(A3,INPUT);
  Serial.begin(9600);
  analogReference(EXTERNAL);
  delay(1000);
}

void loop() {

  analog_in = analogRead(A3);
  Serial.println("analog_in");
  Serial.println(analog_in);                                                    //read and print of the analog value capted by the board
  double bracket_term = (R_0 + R_f - (R_f*pow(2,n_bits)/analog_in))/(R_0*B);
  double first_sqrt_term = pow(A,2)/(4*pow(B,2));
  temp = - A/(2*B) - sqrt(first_sqrt_term - bracket_term);                      //computation of the temperature...the entire formula has been 
                                                                                //split in order to make the code more readable
  //S_Dout_teta = (1/temp)*(1/(R_0*B)*(pow(2,n_bits)/pow(2,analog_in));
  
  
  Serial.println("TEMP:");
  Serial.println(temp);
  delay(100);
}
