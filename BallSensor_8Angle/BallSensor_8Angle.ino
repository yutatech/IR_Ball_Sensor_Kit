int ball_pins[8] = {2, 3, 4, 5, 6, 7, 8, A0};
int distance_pin = 10;
int direction_pin = 9;

void setup() {
  Serial.begin(9600);
  for (int i = 0; i < 8; i++){
    pinMode(ball_pins[i], INPUT);
  }
  pinMode(distance_pin, OUTPUT);
  pinMode(direction_pin, OUTPUT);
}

void loop() {
  int data[8];
  for (int i = 0; i < 8; i++) {
    data[i] = pulseIn(ball_pins[i], LOW, 2000);
  }

  int max_index = 0;
  for (int i = 1; i < 8; i++) {
    if (data[i] > data[max_index]) {
      max_index = i;
    }
  }
  if (data[max_index] == 0) {
    max_index = UINT16_MAX;
    Serial.println("None");
    analogWrite(distance_pin, 255);
    analogWrite(direction_pin, 255);
  }
  else {
    int distance = data[max_index];
    int direction = max_index * 45 + 22.5;
    
    Serial.print(distance);
    Serial.print("\t");
    Serial.println(direction);
    analogWrite(distance_pin, map(distance, 0, 500, 0, 255));
    analogWrite(direction_pin, map(direction, 0, 360, 0, 255));
  }

}
