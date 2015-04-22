/*
  adxl345_demo.ino
  Demo FW untuk Accelerometer gyro GY-521
 
  Author: eprasetio
  Date: 1/31/15
 */

 #define MPU6050 0x68

 #define DBG_LED 13

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


void setup() {
	pinMode(DBG_LED, OUTPUT);
	
}

void loop() {
	digitalWrite(DBG_LED, HIGH);
	delay(1000);
	digitalWrite(DBG_LED, LOW);
	delay(1000);

}

