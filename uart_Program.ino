unsigned char val; //decalring the variable

void setup() {
  Serial.begin(9600); //begining with 9600 baudrate  
  pinMode(5,OUTPUT);  //configuring pin 5 as OUTPUT
  pinMode(4,OUTPUT);  //configuring pin 4 as OUTPUT
}

void loop() {
  if(Serial.available()>0)    //checking data received or not 
  {
    val = Serial.read();    //storing the data in val
    if(val == 'A')   //checking data is A or not
    {
      //if yes, making LED1 as HIGH, LED2 as LOW
      digitalWrite(5,HIGH);
      digitalWrite(4,LOW);
    }
    if(val == 'B')   //checking data is B or not
    {
      //if yes, making LED1 as HIGH, LED2 as HIGH
      digitalWrite(5,HIGH);
      digitalWrite(4,HIGH);
    }
    if(val == 'C')   //checking data is C or not
    {
      //if yes, making LED1 as LOW, LED2 as LOW
      digitalWrite(5,LOW);
      digitalWrite(4,LOW);
    }
    else if(val == 'D')  //checking data is D or not
    {
      //if yes, making LED1 as LOW, LED2 as HIGH
      digitalWrite(5,LOW);
      digitalWrite(4,HIGH);
    }
  }

}
