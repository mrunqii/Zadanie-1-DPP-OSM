const int led1 = 5; 
const int led2 = 6; 

void setup() {
  Serial.begin(9600);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
}

void loop() {
  if (Serial.available() > 0) {
    String cmd = Serial.readStringUntil('#');
    parseCmd(cmd);
  }
}


void setBrightINT(int led, int bright) {
  analogWrite(led == 1 ? led1 : led2, bright);
}

void setBrightFLOAT(int led, float bright) {
  analogWrite(led == 1 ? led1 : led2, bright * 255);
}

void launchAnim(String anim, int dur) {
  int interval = dur / 10;
  if (anim == "separately") {
    for (int i = 0; i < 5; i++) {
      digitalWrite(led1, HIGH);
      delay(interval);
      digitalWrite(led1, LOW);
      delay(interval);
      digitalWrite(led2, HIGH);
      delay(interval);
      digitalWrite(led2, LOW);
      delay(interval);
    }
  } else if (anim == "together") {
    for (int i = 0; i < 5; i++) {
      digitalWrite(led1, HIGH);
      digitalWrite(led2, HIGH);
      delay(interval);
      digitalWrite(led1, LOW);
      digitalWrite(led2, LOW);
      delay(interval);
    }
  }
}

void parseCmd(String cmd) {
  int sepIdx = cmd.indexOf(';');
  String c = cmd.substring(0, sepIdx);
  String args = cmd.substring(sepIdx + 1);

  if (c == "setBrightINT") {
    int led = args.substring(0, args.indexOf(';')).toInt();
    int bright = args.substring(args.indexOf(';') + 1).toInt();
    setBrightINT(led, bright);
  } else if (c == "setBrightFLOAT") {
    int led = args.substring(0, args.indexOf(':')).toInt();
    float bright = args.substring(args.indexOf(':') + 1).toFloat();
    setBrightFLOAT(led, bright);
  } else if (c == "launchAnimation") {
    String anim = args.substring(0, args.indexOf(';'));
    int dur = args.substring(args.indexOf(';') + 1).toInt();
    launchAnim(anim, dur);
  }
}