#include <HardwareSerial.h>

#include <SPI.h>

#include <SD.h>

 

HardwareSerial sim800(2);

 

// SD Card CS pin

#define SD_CS 5

 

bool callDone = false;

bool smsDone = false;

int smsCount = 0;

 

File file;

 

// ---------- TIME FUNCTION ----------

String getTime() {

  unsigned long sec = millis() / 1000;

  int min = sec / 60;

  int s = sec % 60;

 

  char buf[10];

  sprintf(buf, "%02d:%02d", min, s);

  return String(buf);

}

 

// ---------- WRITE LOG ----------

void writeLog(String msg) {

  file = SD.open("/gsm.txt", FILE_APPEND);

 

  if (file) {

    file.println(msg);

    file.close();

    Serial.println("Logged: " + msg);

  } else {

    Serial.println("SD Write Error!");

  }

}

 

void setup() {

  Serial.begin(115200);

  sim800.begin(9600, SERIAL_8N1, 16, 17);

 

  delay(5000);

 

  Serial.println("System Ready");

 

  // ---------- SD INIT ----------

  if (!SD.begin(SD_CS)) {

    Serial.println("SD Card Failed!");

    while (1);

  }

  Serial.println("SD Card Ready");

 

  // Create file if not exists

  if (!SD.exists("/gsm.txt")) {

    file = SD.open("/gsm.txt", FILE_WRITE);

    if (file) {

      file.println("GSM Log Started");

      file.close();

    }

  }

 

  // ---------- GSM SETUP ----------

  sim800.println("AT+CLIP=1");       // caller ID

  delay(1000);

 

  sim800.println("AT+CMGF=1");       // SMS text mode

  delay(1000);

 

  sim800.println("AT+CNMI=2,2,0,0,0"); // direct SMS receive

  delay(1000);

}

 

void loop() {

 

  // ---------- OUTGOING CALL (ONCE) ----------

  if (!callDone) {

    Serial.println("Calling...");

 

    sim800.println("ATD+918921860673;");

    writeLog("Outgoing call " + getTime());

 

    delay(20000);   // ring 20 sec

 

    sim800.println("ATH");

    Serial.println("Call Done");

 

    callDone = true;


      sim800.print("hai");

  }

      delay(500);




  }



    String data = sim800.readString();
    Serial.println(data);

 

    // Incoming call

      Serial.println("Incoming Call");


    }


    // Caller number

    if (data.indexOf("+CLIP") != -1) {

      writeLog("Caller detected " + getTime());

    }

 

    // SMS received

    if (data.indexOf("+CMT") != -1) {

      Serial.println("SMS Received");

      writeLog("Message received " + getTime());

    }

  }

} 
      writeLog("Incoming call " + getTime());

    if (data.indexOf("RING") != -1) {


  if (sim800.available()) {
  // ----------  INCOMING EVENTS ----------
 

      Serial.println("All SMS Sent");

    }
    } else {

      smsDone = true;
      delay(5000);

 
 

 

      Serial.print("SMS Sent: ");

      Serial.println(smsCount);

 
      sim800.write(26); // CTRL+Z

 
      smsCount++;



 
 

      delay(1000);
      sim800.println("AT+CMGS=\"+91000000000\"");


      Serial.println("Sending SMS...");

    if (smsCount < 5) {

 
 

  if (callDone && !smsDone) {

 

  // ----------  SEND SMS (5 TIMES) ----------
