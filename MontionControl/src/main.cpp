#include <U8g2lib.h>
#include <Wire.h>
/************************************FOR TEST************************************/
#include <Arduino.h>
#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>
#include "common.h"
/************************************FOR TEST************************************/
#include "PinConfig.h"
#include "Scurve.h"
#include "Encoder.h"
#include "TIM.h"
#include "Motor.h"
#include "PID.h"
#include "OLED.h"
#include "StateControl.h"
#include "LED.h"

extern double Timeclock; // s

/************************************FOR TEST************************************/
extern double velocity_angle;
extern double position_angle;
extern double PID_output;
extern BarStateClass BarState;
extern bool OpenFlag;
extern bool CloseFlag;
extern CurveSelectClass CurveSelect;

uint8_t txValue = 0;
BLEServer *pServer = NULL;                   //BLEServer指针 pServer
BLECharacteristic *pTxCharacteristic = NULL; //BLECharacteristic指针 pTxCharacteristic
bool deviceConnected = false;                //本次连接状态
bool oldDeviceConnected = false;             //上次连接状态

// See the following for generating UUIDs: https://www.uuidgenerator.net/
#define SERVICE_UUID "5d9f680d-aa9a-43d7-9d88-34049e7663e0" // UART service UUID
#define CHARACTERISTIC_UUID_RX "b1c2e973-65d0-4349-8dbe-fa4093747d65"
#define CHARACTERISTIC_UUID_TX "bcf0e6da-9d88-4497-bad3-2fc93acb2f78"

class MyServerCallbacks : public BLEServerCallbacks
{
  void onConnect(BLEServer *pServer)
  {
    deviceConnected = true;
  };

  void onDisconnect(BLEServer *pServer)
  {
    deviceConnected = false;
  }
};

class MyCallbacks : public BLECharacteristicCallbacks
{
  void onWrite(BLECharacteristic *pCharacteristic)
  {
    std::string rxValue = pCharacteristic->getValue(); //接收信息

    if (rxValue.length() > 0)
    { //向串口输出收到的值
      Serial.print("RX: ");
      for (int i = 0; i < rxValue.length(); i++)
        Serial.print(rxValue[i]);
      Serial.println();
    }
    if(rxValue=="open/close")
    {
      if(BarState == Closed) OpenFlag = true;
      else if(BarState == Opened) CloseFlag = true;
    }
    else if(rxValue=="SCurve")
    {
      CurveSelect = useScurve;
      LED_ShowCurve();
    }
    else if(rxValue=="TraCurve")
    {
      CurveSelect = useTrapezoidalCurve;
      LED_ShowCurve();
    }
   }
};
/************************************FOR TEST************************************/

void setup()
{
  // Initialize the USART
  Serial.begin(115200);

  TIM_Init(); 
  Encoder_Init();
  Motor_Init();
  OLED_Init();
  
  /************************************FOR TEST************************************/
  CurveSelect = useTrapezoidalCurve;

  //Motor_Rotate(Backward, 100);
  LED_Init();
  Button_Init();
  PID_Velocity_Init(0, 0, 0);
  PID_Position_Init(2.0, 0.005, 1.4);//1.8 0.005 0  // 2.0, 0.000, 1 //2, 0.005, 1.4//1.5, 0.005, 1.3//2.0, 0.005, 1.4//2.2, 0.0065, 1.4

  // 创建一个 BLE 设备
  BLEDevice::init("ESP32S3_BLE");

  // 创建一个 BLE 服务
  pServer = BLEDevice::createServer();
  pServer->setCallbacks(new MyServerCallbacks()); //设置回调
  BLEService *pService = pServer->createService(SERVICE_UUID);

  // 创建一个 BLE 特征
  pTxCharacteristic = pService->createCharacteristic(CHARACTERISTIC_UUID_TX, BLECharacteristic::PROPERTY_NOTIFY);
  pTxCharacteristic->addDescriptor(new BLE2902());
  BLECharacteristic *pRxCharacteristic = pService->createCharacteristic(CHARACTERISTIC_UUID_RX, BLECharacteristic::PROPERTY_WRITE);
  pRxCharacteristic->setCallbacks(new MyCallbacks()); //设置回调

  pService->start();                  // 开始服务
  pServer->getAdvertising()->start(); // 开始广播//
  Serial.println(" 等待一个客户端连接，且发送通知... ");
  /************************************FOR TEST************************************/
}

void loop()  
{
  //Serial.println(BarState);
  LED_ShowState();
  OLED_DrawChart();
  /************************************FOR TEST************************************/
   Serial.println("position_angle");
   Serial.println(position_angle);
   Serial.println("Scurve_position");
   Serial.println(Scurve_position(Timeclock));
  // Serial.println(velocity_angle);
  // else
  // {
  //   position_angle = 0;
  //   Timeclock_Clear();
  // }

  // deviceConnected 已连接
  // if (deviceConnected)
  // {
  //   pTxCharacteristic->setValue(&txValue, 1); // 设置要发送的值为1
  //   pTxCharacteristic->notify();              // 广播
  //   txValue++;                                // txvalue的值自加1
  //   delay(2000);                              // 如果有太多包要发送，蓝牙会堵塞
  // }

  // disconnecting  断开连接
  if (!deviceConnected && oldDeviceConnected)
  {
    delay(500);                  // 留时间给蓝牙缓冲
    pServer->startAdvertising(); // 重新广播
    Serial.println(" 开始广播 ");
    oldDeviceConnected = deviceConnected;
  }

  // connecting  正在连接
  if (deviceConnected && !oldDeviceConnected)
  {
    // do stuff here on connecting
    oldDeviceConnected = deviceConnected;
  }
  /************************************FOR TEST************************************/
}
 


