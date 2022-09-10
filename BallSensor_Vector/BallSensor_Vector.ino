int ball_pins[8] = {2, 3, 4, 5, 6, 7, 8, A0};
int distance_pin = 10;
int direction_pin = 9;

void setup() {
  Serial.begin(9600);
  for (int i = 0; i < 8; i++) {
    pinMode(ball_pins[i], INPUT);
  }
  pinMode(distance_pin, OUTPUT);
  pinMode(direction_pin, OUTPUT);
}

void loop() {
  int data[8];
  Serial.print("sensor values : ");
  for (int i = 0; i < 8; i++) {
    data[i] = pulseIn(ball_pins[i], LOW, 2000);
    Serial.print(data[i]);
    Serial.print("\t");
  }

  double x = 0, y = 0;
  for (int i = 0; i < 8; i++) {
    x += data[i] * sin((i * 45 + 22.5) * DEG_TO_RAD);
    y += data[i] * cos((i * 45 + 22.5) * DEG_TO_RAD);
  }

  Serial.print("angle : ");
  if (x != 0 || y != 0) {
    int distance = sqrt(x*x + y*y);
    int direction = atan2(x, y) * RAD_TO_DEG;
    
    Serial.print(distance);
    Serial.print("\t");
    Serial.println(direction);
    analogWrite(distance_pin, map(distance, 0, 500, 0, 255));
    analogWrite(direction_pin, map(direction, 0, 360, 0, 255));
  }
  else {
    Serial.println("None");
    analogWrite(distance_pin, 255);
    analogWrite(direction_pin, 255);
  }

}
