#include <Arduino.h>
// Thu vien RTC Thoi gian thuc
#include "virtuabotixRTC.h"

// Gọi thư viện DHT11
#include <Adafruit_Sensor.h>
#include <DHT.h> 

//Thu vien LCD
#include <Wire.h>;
#include <LiquidCrystal_I2C.h>;

// Khai bao Doi Tuong Thoi gian thuc
virtuabotixRTC myRTC(6, 7, 8);

const int DHTPIN = A3; //Đọc dữ liệu từ DHT22 ở chân A3 trên mạch Arduino
const int DHTTYPE = DHT11; //Khai báo loại cảm biến, có 2 loại là DHT11 và DHT22
DHT dht(DHTPIN, DHTTYPE);

LiquidCrystal_I2C lcd(0x27,16,2);
//0x27 là địa chỉ màn hình trong bus I2C. Phần này chúng ta không cần phải quá bận tâm vì hầu hết màn hình (20x4,...) đều như thế này!
//16 là số cột của màn hình (nếu dùng loại màn hình 20x4) thì thay bằng 20
//2 là số dòng của màn hình (nếu dùng loại màn hình 20x4) thì thay bằng 4

void setup(){
  // Cai dat thoi gian (giay, phut, gio, thu, ngay, thang, nam)
  myRTC.setDS1302Time(00, 56, 1, 6, 4, 8, 2023);

  //Khoi dong Đo độ ẩm DHT11
  dht.begin();

  lcd.init();       //Khởi động màn hình. Bắt đầu cho phép Arduino sử dụng màn hình
  lcd.backlight();   //Bật đèn nền
}
void loop()
{
  // Cap nhat thoi gian thuc
  myRTC.updateTime();
  // đặt con trỏ vào cột 0, dòng 0
  // Lưu ý: dòng 1 là dòng thứ 2, lòng 0 là dòng thứ 1. Nôm na, nó đếm từ 0 từ không phải từ 1
  lcd.setCursor(0, 0);
  // In ra dong chu
  lcd.print(myRTC.year);
  lcd.print("/");
  lcd.print(myRTC.month);
  lcd.print("/");
  lcd.print(myRTC.dayofmonth);

  lcd.setCursor(0, 1);
  lcd.print(" ");
  lcd.print(myRTC.hours);
  lcd.print(":");
  lcd.print(myRTC.minutes);
  lcd.print(":");
  lcd.print(myRTC.seconds);
  delay(3000);

  float h = dht.readHumidity(); //Đọc độ ẩm
  float t = dht.readTemperature(); //Đọc nhiệt độ
  lcd.setCursor(0, 0);
  lcd.print("Nhiet do: ");
  lcd.print(t);

  lcd.setCursor(0, 1);
  lcd.print("Do am: ");
  lcd.print(h);
  delay(5000);
}