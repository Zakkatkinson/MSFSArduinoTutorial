/* 
Inputs for Links2FSCode by Zakk Atkinson 
http://Zakkblog.com 
https://www.youtube.com/c/ZakkAtkinson

See "SimConnect Inputs" tab on Link2FS for more Inputs
----Switches----
Pin 12 - C41x - Nav Lights (C411 is On, C410 is Off)
Pin 11 - C43x - Landing Lights (C431 is On, C430 is Off)
Pin 10 - A43x - Avionics Master (A431 is On, A430 is Off)
----Buttons----
Pin 9 - C01 - Set Gear Handle Up
Pin 4 - C02 - Set Gear Handle Down
----potentiometer
Pin A0 - C17xxx - Set flap handle to closest increment (0-100% Eg: C17100) 

*/

int FlapRead = 0; // variable to store potentiometer value
int FlapMap = 0; // Mapped potentiometer value

void setup()
{
	Serial.begin(115200); //begin serial at 115200 Baud
		
	pinMode(12, INPUT_PULLUP); // set all switches and buttons to input with internal pullups
	pinMode(11, INPUT_PULLUP); 
	pinMode(10, INPUT_PULLUP);
	pinMode(9, INPUT_PULLUP);
	pinMode(4, INPUT_PULLUP);
}

void loop()
{
 

    //----Flaps----

  FlapRead = analogRead(0); //read potentiometer and store value in "FlapRead"
  FlapMap = map(FlapRead, 0, 1023, 0, 100); //Map the value in FlapRead to a value between 0 and 100

    Serial.print("C17"); // print C17 to Link2FS whith no line ending
    Serial.println(FlapMap); //print the current potentiometer value to Link2FS with line ending

  //----Gear Up----

	  while (digitalRead(9) == LOW){ //while button on pin 9 is pressed (Gear up button) 
    Serial.println("C01"); //print "C01" to Link2FS to raise gear
    
  }
  

    //----Gear Down----

   while (digitalRead(4) == LOW){//while button on pin 4 is pressed (Gear down button)
    Serial.println("C02");//print "C02" to Link2FS to lower gear

  }
  

  //----Nav Lights----

  if(digitalRead(12) == LOW){ //if switch on pin 12 is in "on" position
  	Serial.println("C411"); //turn nav lights on
  	
  }else{Serial.println("C410"); } //else turn nav lights off

  //----Landing Lights----

  if(digitalRead(11) == LOW){//if switch on pin 11 is in "on" position
    Serial.println("C431"); // turn Landing lights on
    
  }else{Serial.println("C430"); }//else turn landing lights off

  //----Avionics Master----

  if(digitalRead(10)== LOW){//if switch on pin 10 is in "on" position
    Serial.println("A431"); // turn Avionics Master on
    
  }else{Serial.println("A430"); }//else Avionics Master lights off


}//End loop
