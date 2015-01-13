#include <LCD5110_Basic.h>

LCD5110 myGLCD(8,9,10,11,12);

extern uint8_t SmallFont[];

#include <Wire.h>
float sicaklik;
float gerilim;

void setup()
{ myGLCD.InitLCD();
  myGLCD.setFont(SmallFont);
  Wire.begin();                // join i2c bus (address optional for master)
  Serial.begin(9600);    
pinMode(7, OUTPUT);  // start serial communication at 9600bps
pinMode(6, OUTPUT);
pinMode(5, OUTPUT);
}

int reading = 0;
int reading2 = 0;
int reading3 = 0;
double sonuc;
double sonuc2;
double sonuc3;

void loop()
{
  gerilim=analogRead(0);
  gerilim=(gerilim/1023)*5000;
  sicaklik=gerilim/10.0;
//  Serial.print("sicaklik : ");
//  Serial.println(sicaklik);
  digitalWrite(7, HIGH);
  // step 1: instruct sensor to read echoes
   delay(30);  
  Wire.beginTransmission(0x40); // transmit to device #112 (0x70)
                               // the address specified in the datasheet is 224 (0xE0)
                               // but i2c adressing uses the high 7 bits so it's 112
  Wire.write(byte(0xF1));      // sets register pointer to the command register (0x00)  
  Wire.write(byte(0x80));      // command sensor to measure in "inches" (0x50) 
                               // use 0x51 for centimeters
                               // use 0x52 for ping microseconds
  Wire.endTransmission();      // stop transmitting

  // step 2: wait for readings to happen
  delay(50);                   // datasheet suggests at least 65 milliseconds

  Wire.requestFrom(0x40, 2);    // request 2 bytes from slave device #112

  // step 5: receive reading from sensor
  if(2 <= Wire.available())    // if two bytes were received
  {
    reading = Wire.read();  // receive high byte (overwrites previous reading)
    reading = reading << 8;    // shift high byte to be high 8 bits
    reading |= Wire.read(); // receive low byte as lower 8 bits
    sonuc=(double)reading/60.0;
//    Serial.print("sensor 1 :");
 //   Serial.println(sonuc);   // print the reading

  }
digitalWrite(7, LOW);
 delay(30);  
digitalWrite(6, HIGH);
 delay(30);  
  // step 1: instruct sensor to read echoes
  Wire.beginTransmission(0x40); // transmit to device #112 (0x70)
                               // the address specified in the datasheet is 224 (0xE0)
                               // but i2c adressing uses the high 7 bits so it's 112
  Wire.write(byte(0xF1));      // sets register pointer to the command register (0x00)  
  Wire.write(byte(0x80));      // command sensor to measure in "inches" (0x50) 
                               // use 0x51 for centimeters
                               // use 0x52 for ping microseconds
  Wire.endTransmission();      // stop transmitting

  // step 2: wait for readings to happen
  delay(50);                   // datasheet suggests at least 65 milliseconds

  Wire.requestFrom(0x40, 2);    // request 2 bytes from slave device #112

  // step 5: receive reading from sensor
  if(2 <= Wire.available())    // if two bytes were received
  {
    reading2 = Wire.read();  // receive high byte (overwrites previous reading)
    reading2 = reading2 << 8;    // shift high byte to be high 8 bits
    reading2 |= Wire.read(); // receive low byte as lower 8 bits
    sonuc2=(double)reading2/60.0;
 //   Serial.print("sensor 2 :" );
 //  Serial.println(sonuc2);   // print the reading
 
  }
digitalWrite(6, LOW);
 delay(30);  
digitalWrite(5, HIGH);
 delay(30);  
  // step 1: instruct sensor to read echoes
  Wire.beginTransmission(0x40); // transmit to device #112 (0x70)
                               // the address specified in the datasheet is 224 (0xE0)
                               // but i2c adressing uses the high 7 bits so it's 112
  Wire.write(byte(0xF1));      // sets register pointer to the command register (0x00)  
  Wire.write(byte(0x80));      // command sensor to measure in "inches" (0x50) 
                               // use 0x51 for centimeters
                               // use 0x52 for ping microseconds
  Wire.endTransmission();      // stop transmitting

  // step 2: wait for readings to happen
  delay(50);                   // datasheet suggests at least 65 milliseconds

  Wire.requestFrom(0x40, 2);    // request 2 bytes from slave device #112

  // step 5: receive reading from sensor
  if(2 <= Wire.available())    // if two bytes were received
  {
    reading3 = Wire.read();  // receive high byte (overwrites previous reading)
    reading3 = reading3 << 8;    // shift high byte to be high 8 bits
    reading3 |= Wire.read(); // receive low byte as lower 8 bits
    sonuc3=(double)reading3/60.0;
 //   Serial.print("sensor 2 :" );
 //  Serial.println(sonuc2);   // print the reading
 
  }
digitalWrite(5, LOW);
  myGLCD.clrScr();
  myGLCD.print("Temp :", LEFT, 0);
  myGLCD.printNumF(sicaklik,2, RIGHT, 0);
  myGLCD.print("D.P-1 :", LEFT, 16);
  myGLCD.printNumF(sonuc,2, RIGHT, 16);
  myGLCD.print("D.P-2 :", LEFT, 24);
  myGLCD.printNumF(sonuc2,2, RIGHT, 24);
  myGLCD.print("D.P-3 :", LEFT, 32);
  myGLCD.printNumF(sonuc3,2, RIGHT, 32);
  Serial.print(sicaklik);
  Serial.print(";");
  Serial.print(sonuc);
  Serial.print(";");
  Serial.print(sonuc2);
  Serial.print(";");
  Serial.println(sonuc3);
  
  delay(30);                  // wait a bit since people have to read the output :)
}


