/*
  adxl345_demo
  Demo FW untuk Accelerometer sensor ADXL345
 
  Author: eprasetio
  Date: 1/31/15
 */
 
#include <Wire.h>

#define ADXL345 0x53  // define sensor address here

#define REG_DEVID  0x00
#define REG_THRESH_TAP  0x1D
#define REG_OFSX  0x1E
#define REG_OFSY  0x1F
#define REG_OFSZ  0x20
#define REG_DUR  0x21
#define REG_LATENT  0x22
#define REG_WINDOW  0x23
#define REG_THRESH_ACT  0x24
#define REG_THRESH_INACT  0x25
#define REG_TIME_INACT  0x26
#define REG_ACT_INACT_CTL 0x27
#define REG_THRESH_FF 0x28
#define REG_TIME_FF 0x29
#define REG_TAP_AXES  0x2A
#define REG_ACT_TAP_STATUS  0x2B
#define REG_BW_RATE 0x2C
#define REG_POWER_CTL 0x2D
#define REG_INT_ENABLE  0x2E
#define REG_INT_MAP 0x2F
#define REG_INT_SOURCE  0x30
#define REG_DATA_FORMAT 0x31
#define REG_DATAX0  0x32
#define REG_DATAX1  0x33
#define REG_DATAY0  0x34
#define REG_DATAY1  0x35
#define REG_DATAZ0  0x36
#define REG_DATAZ1  0x37
#define REG_FIFO_CTL  0x38
#define REG_FIFO_STATUS  0x39

#define DBG_LED 13

// variables to store sensor values
int data_x;
int data_y;
int data_z;

// Function untuk mengirim data ke sensor
void write_data(int device, byte reg_addr, byte data){
  Wire.beginTransmission(device);
  Wire.write(reg_addr);
  Wire.write(data);
  Wire.endTransmission();
} 

// Function untuk membaca data dari device
unsigned char read_data(int device, byte reg_addr, int data_len){
 unsigned char buffer; 
  
 Wire.beginTransmission(device);
 Wire.write(reg_addr);
 Wire.endTransmission();
 
 Wire.beginTransmission(device);
 Wire.requestFrom(device, data_len);
 while(Wire.available()){ 
  buffer = Wire.read();
 }

 return buffer;
}


// function setup di bawah akan di jalankan sekali dan
// pertama kali ketika program mulai berjalan
void setup() {               
  // initialize the digital pin nomor 13 sebagai output
  pinMode(DBG_LED, OUTPUT); 
  Wire.begin();  // initialize wire transmission
  Serial.begin(9600);
  
  Serial.println("ADXL345 demo firmware");

  write_data(ADXL345, REG_POWER_CTL, 0); // clear up registers value
  write_data(ADXL345, REG_POWER_CTL, 16); // enables auto sleep
  write_data(ADXL345, REG_POWER_CTL, 8);  // enable measurements

  // initialize temp data buffer
  data_x = 0;
  data_y = 0;
  data_z = 0;

}


// function loop di bawah akan berjalan terus menerus dan diulang kembali:
void loop() {
  
  data_x = (int) ( read_data(ADXL345, REG_DATAX0, 1) | (read_data(ADXL345, REG_DATAX1, 1) << 8) );
  data_y = (int) ( read_data(ADXL345, REG_DATAY0, 1) | (read_data(ADXL345, REG_DATAY1, 1) << 8) );
  data_z = (int) ( read_data(ADXL345, REG_DATAZ0, 1) | (read_data(ADXL345, REG_DATAZ1, 1) << 8) );
  
  Serial.print("DATA X:");
  Serial.print(data_x);
  Serial.print("\tDATA Y:");
  Serial.print(data_y);
  Serial.print("\tDATA Z:");
  Serial.println(data_z);
  Serial.println();
  
  digitalWrite(DBG_LED, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);               // wait for a second
  digitalWrite(DBG_LED, LOW);    // turn the LED off by making the voltage LOW
  delay(1000);               // wait for a second
}
