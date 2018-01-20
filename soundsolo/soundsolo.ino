/*
* This file is generated by the Marvin Booster
* The following sensors are available:
* A3 - Unused
* A5 - Unused
* D4 - Unused
* A0 - Sound Sensor
* D3 - Unused
*
* If you find whitespaces within this document, it is due to empty templates.
* Have fun playing with your new Marvin!
*/
//Include libraries and non-static variables needed for different sensors
#include <math.h>         //by default included in Arduino
#include <Wire.h>         //by default included in Arduinozip






// Port to assign the type of lora data (any port can be used between 1 and 223)
int     set_port  = 1;

// Some standard ports that depend on the layout of the Marvin
long    defaultBaudRate = 57600;
int     reset_port = 5;
int     RN2483_power_port = 6;
int     led_port = 13;
unsigned long start;
//*** Generated parameters here, please do not edit---->
String  set_as_key = ""; // Put your 32 hex char here
String  set_as_id = ""; // Put your value here
String  set_descriptivename = "MARVIN01"; // Put your value here
String  set_displayname = "700E8B14162DB298 - MARVIN01"; // Put your value here
String  set_endpoint_url = "https://mansystemsiotapp.mendixcloud.com/lora"; // Put your value here
String  set_deveui = "700E8B14162DB298"; // Put your 32 hex char here
String  set_devsaddr = "0181B416"; // Put your 32 hex char here
String  set_nwkskey = "775AEB0EAD7F963F5C9853A47BBD8845"; // Put your 32 hex char here
String  set_appskey = "775AEB0EAD7F963F5C9853A47BBD8845"; // Put your 32 hex char here
String  set_devaddr = "0181B416"; // Put your 8 hex char here
String  set_devicestatus = ""; // Put your value here
//*** <---- END Set parameters here

// Some global items
String reader = "";

//*** Define in which port the sensor is plugged in ---->



const int pinAdc = A0;


/*
 * Setup() function is called when board is started. Marvin uses a serial connection to talk to your pc and a serial
 * connection to talk to the RN2483, these are both initialized in seperate functions. Also some Arduino port are 
 * initialized and a LED is called to blink when everything is done. 
 */
void setup() {
 InitializeSerials(defaultBaudRate);
  initializeRN2483(RN2483_power_port, reset_port);
  Wire.begin();
  pinMode(led_port, OUTPUT); // Initialize LED port  
  blinky();
  pinMode(A3, INPUT);
  pinMode(A5, INPUT);
  start = millis();
 
 
 
 
 
}











void loop() {
    String payload = "1";
    int A = 0;          //Assigned to port 1 (A3)
    int B = 0;          //Assigned to port 1 (A3)-for humidity value
    int C = 0;          //Assigned to port 2 (A5)
    int D = 0;          //Assigned to port 3 (D4)
    int E = 0;          //Assigned to part 4 (A0)
    int F = 0;          //Assigned to port 5 (D3)
                        //Port 5 is also the serial I2C port. Make sure you check an example on the Seeed wiki
                        //to know what the exact output of your sensor is and how you want to send it   

  
  
  
  
  
  
   //Sound sensor  
long sound = 0;
    for(int soundLevel=0; soundLevel<32; soundLevel++)
    {
        sound += analogRead(pinAdc);
    }

    sound >>= 5;
    E = sound;
  
  

  delay(500);
  
  if(millis() - start > 30000){
    payload = payload+ "A" + String(A)+ "B" + String(B)+ "C" + String(C)+ "D" + String(D)+ "E" + String(E) + "F" + String(F);
    send_LoRa_data(set_port, payload); //4 bytes 
    blinky();
    delay(1000);
    read_data_from_LoRa_Mod();
    delay(1000);
    start = millis();
  }
}

void InitializeSerials(long baudrate)
{
  Serial.begin(baudrate);
  Serial1.begin(baudrate);
  delay(1000);
  print_to_console("Serial ports initialised");
}

void initializeRN2483(int pwr_port, int rst_port)
{
  //Enable power to the RN2483
  pinMode(pwr_port, OUTPUT);
  digitalWrite(pwr_port, HIGH);
  print_to_console("RN2483 Powered up");
  delay(1000);
  
  //Disable reset pin
  pinMode(rst_port, OUTPUT);
  digitalWrite(rst_port, HIGH);

  //Configure LoRa module
  send_LoRa_Command("sys reset");
  read_data_from_LoRa_Mod();

  send_LoRa_Command("mac set nwkskey " + set_nwkskey);
  read_data_from_LoRa_Mod();

  send_LoRa_Command("mac set appskey " + set_appskey);
  read_data_from_LoRa_Mod();

  send_LoRa_Command("mac set devaddr " + set_devaddr);
  read_data_from_LoRa_Mod();

  //For this commands some extra delay is needed.
  send_LoRa_Command("mac set adr on");
  //send_LoRa_Command("mac set dr 0"); //uncomment this line to fix the RN2483 on SF12 (dr=DataRate)
  delay(1000);
  read_data_from_LoRa_Mod();

  send_LoRa_Command("mac save");
  delay(1000);
  read_data_from_LoRa_Mod();

  send_LoRa_Command("mac join abp");
  delay(1000);
  read_data_from_LoRa_Mod();

  send_LoRa_Command("radio set crc off");
  delay(1000);
  read_data_from_LoRa_Mod();

}

void print_to_console(String message)
{
  Serial.println(message);
}

void read_data_from_LoRa_Mod()
{
  if (Serial1.available()) {
    String inByte = Serial1.readString();
    Serial.println(inByte);
  }

}

void send_LoRa_Command(String cmd)
{
  print_to_console("Now sending: " + cmd);
  Serial1.println(cmd);
  delay(500);
}

void send_LoRa_data(int tx_port, String rawdata)
{
  send_LoRa_Command("mac tx uncnf " + String(tx_port) + String(" ") + rawdata);
}


void blinky()
{
  digitalWrite(led_port, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(500);              // wait for a second
  digitalWrite(led_port, LOW);    // turn the LED off by making the voltage LOW
  delay(500);              // wait for a second
  digitalWrite(led_port, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(500);              // wait for a second
  digitalWrite(led_port, LOW);    // turn the LED off by making the voltage LOW
  delay(500);              // wait for a second

}
