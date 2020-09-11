#include <OneWire.h>
#include <DallasTemperature.h> //include DallasTemperature library

// Data wire is plugged into the Arduino on port ?
#define ONE_WIRE_BUS 11

// Setup a oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)
OneWire oneWire(ONE_WIRE_BUS);

// Pass our oneWire reference to Dallas Temperature.
DallasTemperature sensors(&oneWire);

//initialize variables
int heater = 12; //heating pad is connected to which pin?  ---> (no it's fed by Vin)  not 12
double temperature;
int time_passed = 0;
int UpperLimit = 40;
int LowerLimit = 36;

void setup(void)
{
  // start serial port
  Serial.begin(9600);
  Serial.println("System is active");

  // Start up the library
  sensors.begin();

  //state of component pins
  pinMode(heater, OUTPUT); //the 'heater' is an OUTPUT
}

void loop(void)
{
  // call sensors.requestTemperatures() to issue a global temperature
  // request to all devices on the bus

  sensors.requestTemperatures(); // Send the command to get temperatures

  temperature = sensors.getTempCByIndex(0);

  //print temperature to serial monitor
  Serial.print(time_passed);
  Serial.print(", ");
  Serial.print(temperature);
  Serial.println("C");
  time_passed = time_passed + 1; //increment time by 1 every loop

  //compare recorded temperature from sensor to needed temperature (37 C)
  if(temperature < LowerLimit){
  digitalWrite(heater, LOW); //turns on heater
  Serial.print("Warming hands up from ");
  Serial.print(temperature);
  Serial.print(" to 40 C");
  delay(14000); //14 seconds
  }

  else if(temperature >= UpperLimit){
  digitalWrite(heater,HIGH);
  Serial.print("Hands have reached ");
  Serial.print(temperature);
  Serial.print("Turning heater off");
  delay(81230); //81.23 seconds
  }
  else if (temperature > LowerLimit && temperature < UpperLimit){
  Serial.print("Standby");
  delay(10000); //10 seconds
  }
 
}
