int ball_pins[8] = {2, 3, 4, 5, 6, 7, 8, A0};   // U1 ~ U8 のセンサーにつながっているピン番号を格納した配列
int distance_pin = 10;    // DISTANCE コネクタに接続されたピン
int direction_pin = 9;    // DIRECTION コネクタに接続されたピン

void setup() {
  Serial.begin(9600);
  for (int i = 0; i < 8; i++) {
    pinMode(ball_pins[i], INPUT);
  }
  pinMode(distance_pin, OUTPUT);
  pinMode(direction_pin, OUTPUT);
}

void loop() {
  int data[8];    // 各センサーの値を格納する変数
  Serial.print("sensor values : ");
  for (int i = 0; i < 8; i++) {
    data[i] = pulseIn(ball_pins[i], LOW, 2000);   // 各センサーの値を変数に格納
    Serial.print(data[i]);
    Serial.print("\t");
  }

  double x = 0, y = 0;    // 最終的にボールの向きと距離を表すベクトルのx成分、y成分を表す変数
  for (int i = 0; i < 8; i++) {
    x += data[i] * sin((i * 45 + 22.5) * DEG_TO_RAD);   // 各センサー向きと値を表すのベクトルのx成分を取り出して x に足す
    y += data[i] * cos((i * 45 + 22.5) * DEG_TO_RAD);   // 各センサー向きと値を表すのベクトルのy成分を取り出して y に足す
  }

  Serial.print("result : ");
  if (x != 0 || y != 0) {   // xとyのどちらかが0でない値であればベクトルの大きさは0ではない (つまりボールが見えている)
    int distance = sqrt(x*x + y*y);   // ボールの距離は x と y の2乗の和の平方根で計算できる
    int direction = atan2(x, y) * RAD_TO_DEG;   // ボールの角度はx成分とy成分から atan2 で計算できる
    
    Serial.print(distance);
    Serial.print("\t");
    Serial.println(direction);
    analogWrite(distance_pin, map(distance, 0, 500, 0, 255));
    analogWrite(direction_pin, map(direction, -180, 180, 0, 255));
  }
  else {
    Serial.println("None");
    analogWrite(distance_pin, 255);
    analogWrite(direction_pin, 255);
  }

}
