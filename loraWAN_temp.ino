#include <KashiwaGeeks.h>
#include <Wire.h>

#define ECHO true

ADB922S LoRa;

//================================
// Initialize Device Function
//================================
#define BPS_9600      9600
#define BPS_57600     57600

void start()
{
    ConsoleBegin(BPS_57600);

    // 割り込みを有効にする
    EnableInt0();

    ConsolePrint(F("\n**** LoRaWAN Sample PG *****\n"));
    Wire.begin();

    /*  setup ADB922S  */
    if ( LoRa.begin(BPS_9600, DR3) == false )
    {
        while(true)
        {
            LedOn();
            delay(300);
            LedOff();
            delay(300);
        }
    }
    LoRa.join();
}

//================================
// Power save functions
//================================
void sleep(void)
{
    LoRa.sleep();
    DebugPrint(F("LoRa sleep.\n"));
}

void wakeup(void)
{
    LoRa.wakeup();
    DebugPrint(F("LoRa wakeup.\n"));
}

//================================
// INT0 callbaks
//================================
void int0D2(void)
{
  ConsolePrint(F("\nINT0で割り込み発生!!!\n"));
  taskTemp();
}

//================================
// Functions to be executed periodically
//================================
#define LoRa_Port_COMP  13
int I2CAdrs = 0x48;

void taskTemp(void)
{
  uint16_t val;
  float tmp;
  int ival;

  // 温度センサーでデータ取得
  Wire.requestFrom(I2CAdrs, 2);
  val = (uint16_t)Wire.read() << 8;
  val |= Wire.read();
  val >>= 3;
  ival = (int)val;
 
  if(val & (0x8000 >> 3)) {
    ival = ival  - 8192;
  }

  // 摂氏温度換算
  tmp = (float)ival / 16.0;
  int16_t uplinktmp = tmp * 100;
  int rc = LoRa.sendData(LoRa_Port_COMP, ECHO, F("%04x"), uplinktmp);
  checkResult(rc);
  Serial.println(tmp, 2);
}

/*-------------------------------------------------------------*/
void checkResult(int rc )
{
    if ( rc == LORA_RC_SUCCESS )
    {
        ConsolePrint(F("\n SUCCESS\n"));
    }
    else if ( rc == LORA_RC_DATA_TOO_LONG )
    {
      ConsolePrint(F("\n !!!DATA_TOO_LONG\n"));
    }
    else if ( rc == LORA_RC_NO_FREE_CH )
    {
      ConsolePrint(F("\n !!!No free CH\n"));
    }
    else if ( rc == LORA_RC_BUSY )
    {
      ConsolePrint(F("\n !!!Busy\n"));
    }
    else if ( rc ==LORA_RC_NOT_JOINED )
    {
      ConsolePrint(F("\n !!!Not Joined\n"));
    }
    else if ( rc == LORA_RC_ERROR )
    {
     ConsolePrint(F("\n !!!UNSUCCESS\n"));
    }
}

//===============================
// Execution interval
// ASK( function, initial offset, interval by minute )
//===============================

TASK_LIST = {
        TASK(taskTemp, 0, 1),
        END_OF_TASK_LIST
};
