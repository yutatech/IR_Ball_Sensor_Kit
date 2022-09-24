int ball_pins[8] = {2, 3, 4, 5, 6, 7, 8, A0};   // U1 ~ U8 のセンサーにつながっているピン番号を格納した配列
int distance_pin = 10;    // DISTANCE コネクタに接続されたピン
int direction_pin = 9;    // DIRECTION コネクタに接続されたピン

void setup() {
  Serial.begin(9600);
  for (int i = 0; i < 8; i++){
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

  int max_index = 0;    // 最終的に最も大きい値を示すセンサーの番号を 0 ~ 7 で表す。初めは0番目にセットしておく
  for (int i = 1; i < 8; i++) {
    if (data[i] > data[max_index]) {    // 0番目から(i-1)番目までのセンサーの中で最も大きい値とi番目のセンサーの値を比較
      max_index = i;    //  0番目から(i-1)番目までのセンサーの中で最も大きい値よりもi番目のセンサーの値が大きければ max_index に i を代入
    }
  }
  
  Serial.print("result : ");
  if (data[max_index] == 0) {   // 最も大きい値を示すセンサーの値が0の時 (つまりボールが見えていない時)
    max_index = UINT16_MAX;
    Serial.println("None");
    analogWrite(distance_pin, 255);
    analogWrite(direction_pin, 255);
  }
  else {
    int distance = data[max_index];   // ボールまでの距離は最も大きい値を示すセンサーの値
    int direction = max_index * 45 + 22.5;    // ボールの角度を計算
    
    Serial.print(distance);
    Serial.print("\t");
    Serial.println(direction);
    analogWrite(distance_pin, map(distance, 0, 500, 0, 255));
    analogWrite(direction_pin, map(direction, 0, 360, 0, 255));
  }

}
