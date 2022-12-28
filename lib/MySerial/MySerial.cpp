#include <Arduino.h>
#include <SoftwareSerial.h>
#include "MySerial.h"

MySerial::MySerial(bool sw) : SoftwareSerial(0, 1, false) {
  serialOUT = sw;
};

void MySerial::printFormat(String name, int val) {
  if (MySerial::serialOUT) {
    SoftwareSerial::print(name);
    if (val >= 0) {
      SoftwareSerial::print("\t");
      SoftwareSerial::print(val);
    }
  }
}

void MySerial::println(String msg) {
  if (MySerial::serialOUT)
    SoftwareSerial::println(msg);
}

void MySerial::print1(String name, int val) {
  MySerial::printFormat(name, val);
}

void MySerial::print(String name, int val) {
  MySerial::printFormat("\t" + name, val);
}
