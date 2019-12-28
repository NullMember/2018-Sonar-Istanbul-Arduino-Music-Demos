/*  
    This library written by Malik Enes Safak
    For Sonar Istanbul Festival
    Arduino Music Workshop
*/
#ifndef SONARMPU6050_H
#define SONARMPU6050_H

#include <Arduino.h>
#include <I2Cdev.h>
#include <MPU6050_6Axis_MotionApps20.h>
#include <Wire.h>

class SonarMPU6050{
    private:
        MPU6050 *_mpu;
        bool dmpReady = false;  // set true if DMP init was successful
        uint8_t mpuIntStatus;   // holds actual interrupt status byte from MPU
        uint8_t devStatus;      // return status after each device operation (0 = success, !0 = error)
        uint16_t packetSize;    // expected DMP packet size (default is 42 bytes)
        uint16_t fifoCount;     // count of all bytes currently in FIFO
        uint8_t fifoBuffer[64]; // FIFO storage buffer
        bool connectionStatus;
        float ypr[3];
        float multiplier;
        Quaternion q;
        VectorFloat gravity;
        volatile bool mpuInterrupt;
    public:
        uint8_t interruptPin;
        void dmpDataReady();
        SonarMPU6050(MPU6050 *__mpu, uint8_t intPin = 2);
        void begin();
        bool isDataReady();
        void update();
        float yaw();
        float pitch();
        float roll();
};

inline SonarMPU6050::SonarMPU6050(MPU6050 *__mpu, uint8_t intPin){
    _mpu = __mpu;
    multiplier = 180/M_PI;
    interruptPin = intPin;
    SonarMPU6050::mpuInterrupt = false;
}

inline void SonarMPU6050::begin(){
    pinMode(interruptPin, INPUT);
    Wire.begin();
    _mpu->initialize();
    connectionStatus = _mpu->testConnection();
    devStatus = _mpu->dmpInitialize();
    if(devStatus == 0){
        _mpu->setDMPEnabled(true);
        mpuIntStatus = _mpu->getIntStatus();
        dmpReady = true;
        packetSize = _mpu->dmpGetFIFOPacketSize();
    }
}

inline void SonarMPU6050::dmpDataReady(){
    mpuInterrupt = true;
}

inline bool SonarMPU6050::isDataReady(){
    return mpuInterrupt;
}

inline void SonarMPU6050::update(){
    mpuInterrupt = false;
    mpuIntStatus = _mpu->getIntStatus();               //update interrupt status
    fifoCount = _mpu->getFIFOCount();                   //get FIFO size
    if ((mpuIntStatus & 0x10) || fifoCount == 1024) { //FIFO overflow
        _mpu->resetFIFO();
    }
    else if(mpuIntStatus & 0x02){                     //otherwise check DMP data ready
        while (fifoCount < packetSize) fifoCount = _mpu->getFIFOCount(); // wait unless we get correct size
        _mpu->getFIFOBytes(fifoBuffer, packetSize);                      // read packet from fifo
        fifoCount -= packetSize;
        _mpu->dmpGetQuaternion(&q, fifoBuffer);
        _mpu->dmpGetGravity(&gravity, &q);
        _mpu->dmpGetYawPitchRoll(ypr, &q, &gravity);
    }
}

inline float SonarMPU6050::yaw(){
    return ypr[0] * multiplier;
}

inline float SonarMPU6050::pitch(){
    return ypr[1] * multiplier;
}

inline float SonarMPU6050::roll(){
    return ypr[2] * multiplier;
}

#endif