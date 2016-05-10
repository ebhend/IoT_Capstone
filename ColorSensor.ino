const int s0 = 3; //YELLOW CORD 
const int s1 = 4; // GREEN CORD
const int s2 = 5; //BLUE CORD
const int s3 = 6;  //WHITE CORD
const int bat = 7; //RED CORD
const int out = 0;//BROWN GREEN CORD

// Variables  
int red=0;      //counts on the red sensor
int blue =0;    //counts on the blue sensor
int green=0;    //counts on the green sensor
int value=0;    //the current dice roll
int toSend= 0;  //the value to be sent over the web
int i=0;        //counter function
//int test =0;    //testing for code
    
void setup()   
{  
    Serial.begin(9600); 
    pinMode(s0, OUTPUT);  
    pinMode(s1, OUTPUT);  
    pinMode(s2, OUTPUT);  
    pinMode(s3, OUTPUT);  
    pinMode(out, INPUT);
    pinMode(bat, OUTPUT);
    digitalWrite(s0, HIGH);  
    digitalWrite(s1, HIGH);
    Particle.variable("DiceRoll", toSend);
}  

void loop() 
{ 
    //turn on device 
    digitalWrite(bat, HIGH);
    
    //functions to detect color convert it to a number and then send to the internet if new
    color(); 
    number();
    toInternet();

    //serial print section for manual verification
    Serial.print("R:");  
    Serial.print(red, DEC);  
    Serial.print(" G: ");  
    Serial.print(green, DEC);  
    Serial.print(" B: ");  
    Serial.print(blue, DEC);
    Serial.print("  -Number:");
    Serial.print(value);
    Serial.print(" i =");
    Serial.print( i);
    //Serial.print( " Test is");    //code to serial print test function
    //Serial.print( test);
    ///Serial.print ( toSend);      //code to serial print the toSend function
    Serial.println();  
    
    
    //delay and reset funciotns
    delay(1000);
}

void color()  
{    
    digitalWrite(s2, LOW);  
    digitalWrite(s3, LOW);  
  //count OUT, pRed, RED  
    red = pulseIn(out, digitalRead(out) == HIGH ? LOW : HIGH);  
    digitalWrite(s3, HIGH);  
  //count OUT, pBLUE, BLUE  
    blue = pulseIn(out, digitalRead(out) == HIGH ? LOW : HIGH);  
    digitalWrite(s2, HIGH);  
  //count OUT, pGreen, GREEN  
    green = pulseIn(out, digitalRead(out) == HIGH ? LOW : HIGH);  
}

void number(){
    
    if(150<red && red <1000 && 150<green && green<1760 && 100<blue && blue<1500)
        value=1;
    else if(831<red && red<947 && 1354<green && green<1536 && 1200<blue && blue<1354)
        value =2;
    else if(760<red && red<848 && 1134<green && green<1265 && 1041<blue && blue<1161)
        value =3;
    else if(743<red && red<885  && 1245<green&& green<1489 && 1126<blue && blue<1324)
        value =4;
    else if(825<red && red <935 && 1266<green && green<1459 && 1114<blue&& blue<1259)
        value =5;
    else if(1050<red && 1799<green && 1537<blue)
        value =6;
    else
        value=0;
}

void toInternet()
{
    // test to see if no dice detected and reset
    if(value==0)
    {
        toSend =0;
        i=0;
        //test =1;
    }
    //test to see if there is a new value
    else if(value != toSend)
        {
        toSend = value;
        //test =2;
        i=0;
        }
    
    //start the count up to remove stray values
    else
    {
        i=i+1;
        //test =3;
        if (i==5)
        {
            //publish results if a new result is detemined
            String NewRoll= String(toSend);
            Particle.publish("NewRoll", NewRoll);
            Serial.print("Published!!!");
            //test =4;
        }
    }
}
