#define RXD2 16
#define TXD2 17


void setup() {
  Serial2.begin(9600, SERIAL_8N1, RXD2, TXD2);
}

void loop() {
  while (Serial2.available() == 0){}
  String received = Serial2.readString();
  received.trim();
  Serial2.print("Ich hab erhalten: " + received);

}
