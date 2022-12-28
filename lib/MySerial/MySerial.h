#ifndef MySerial_h
#define MySerial_h
#include <Arduino.h>
#include <SoftwareSerial.h>
class MySerial : public SoftwareSerial {
private:
  bool serialOUT;
  /* Format Serial print */
  void printFormat(String name = "", int val = 0);

public:
  MySerial(bool sw);

  void println(String msg = "");

  void print1(String name = "", int val = 0);

  void print(String name = "", int val = 0);
};
#endif