/*
Original code from http://jimspage.co.nz
Massive modifications made by Zakk Atkinson
http://ZakkBlog.com

*/


int CodeIn; //int to store incoming characters
String gearN,gearL,gearR; // incoming Gear string
int gearNi,gearLi,gearRi; //Gear string converted to Integer
int gearTot; // sum of gearNi, gearLi, and gearRi, added together 


void setup()
{
	Serial.begin(115200);
	pinMode(2, OUTPUT); // gear nose green LED
  pinMode(3, OUTPUT); // gear nose in transition LED
  pinMode(5, OUTPUT); // gear left in transition red LED
  pinMode(6, OUTPUT); // gear left green LED
   pinMode(7, OUTPUT); // gear right in transition red LED
    pinMode(8, OUTPUT); // gear right green red LED

    //set gear pins LOW to start
      digitalWrite(2, LOW);
    digitalWrite(3, LOW);
    digitalWrite(5, LOW);
    digitalWrite(6, LOW);
    digitalWrite(7, LOW);
    digitalWrite(8, LOW);
}

void loop()
{

 {OTHER();}// Check for "Other" things to do. (Non extraction stuff)
 
 
  if (Serial.available()) {
    CodeIn = getChar();
    if (CodeIn == '<') {LESSTHAN();}// The first identifier is "<"
     }

}

char getChar()// Get a character from the serial buffer
{
  while(Serial.available() == 0);// wait for data
  return((char)Serial.read());// Thanks Doug

 }

void LESSTHAN(){    // The first identifier was "<"
CodeIn = getChar(); // Get the second identifier
  switch(CodeIn) {// Now lets find what to do with it
    case 'A'://Found the second identifier "GearN"
      gearN = "";
      gearN += getChar(); //get the three digits that represent nose Gear location
      gearN += getChar();
      gearN += getChar();
      gearNi = gearN.toInt(); // convert it to an integer (Thanks Phill)
      if (gearNi > 99){ //if gear is fully down 
        digitalWrite(2, HIGH); //turn Nose green on
        digitalWrite(3, LOW); // turn Nose red off
      }
      else{ //if any other case (see 'other' function for refinement) 
        digitalWrite(2, LOW); //turn nose green off
        digitalWrite(3, HIGH); //turn nose red on
      }
      // See "OTHER" for more uses of gearni
    break;
     
    case 'B':
      gearL = "";
      gearL += getChar(); //get the three digits that represent left Gear location
      gearL += getChar();
      gearL += getChar();
      gearLi = gearL.toInt(); // convert it to an integer (Thanks Phill)
      if (gearLi > 99){//if gear is fully down 
        digitalWrite(6, HIGH); // turn left green on
        digitalWrite(5, LOW); //turn left red off
        }
        else{//if any other case (see 'other' function for refinement)
          digitalWrite(6, LOW); //turn left green off
          digitalWrite(5, HIGH);//turn left red on
        }
      // See "OTHER" for more uses of gearLi
    break;
     
    case 'C':
        gearR = "";
      gearR += getChar(); //get the three digits that represent right Gear location
      gearR += getChar();
      gearR += getChar();
      gearRi = gearR.toInt(); // convert it to an integer (Thanks Phill)
      if (gearRi > 99){//if gear is fully down 
        digitalWrite(8, HIGH); //turn right green on 
        digitalWrite(7, LOW); //turn right red off
      }
        else{//if any other case (see 'other' function for refinement)
          digitalWrite(8, LOW); //turn right green off
          digitalWrite(7, HIGH); // turn right red on
        }
      // See "OTHER" for more uses of gearRi
    break;
}
}

void OTHER(){
/* In here you would put code that uses other data that
cant be put into an "extraction void" that references something else.
Also in here you would put code to do something that was not
relying on a current extraction trigger.

*/
//Sort out the gear "in transition" LED (redundancy to make sure it turns off when it's supposed to)
int gearTot = (gearNi + gearLi + gearRi);
if (gearTot == 300){
  digitalWrite(3, LOW); //turn all three red gear LEDs off
  digitalWrite(5, LOW);
  digitalWrite(7, LOW);
} 
else if (gearTot < 1){
  digitalWrite(3, LOW); //turn all three red gear LEDs off
  digitalWrite(5, LOW);
  digitalWrite(7, LOW);
}

}
