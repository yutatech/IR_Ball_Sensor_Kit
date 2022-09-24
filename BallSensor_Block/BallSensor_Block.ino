int data1;

int data2;

int data3;

int data4;

int data5;

int data6;

int data7;

int data8;

int max_value;

int max_index;

void setup()
{
  pinMode(2, INPUT);
  pinMode(3, INPUT);
  pinMode(4, INPUT);
  pinMode(5, INPUT);
  pinMode(6, INPUT);
  pinMode(7, INPUT);
  pinMode(8, INPUT);
  pinMode(A0, INPUT);
  Serial.begin(9600);

}


void loop()
{
  pulseIn(2,LOW,2000);

  data1 = pulseIn(2,LOW,2000);
  data2 = pulseIn(3,LOW,2000);
  data3 = pulseIn(4,LOW,2000);
  data4 = pulseIn(5,LOW,2000);
  data5 = pulseIn(6,LOW,2000);
  data6 = pulseIn(7,LOW,2000);
  data7 = pulseIn(8,LOW,2000);
  data8 = pulseIn(A0,LOW,2000);
  max_value = data1;
  max_index = 1;
  if (max_value < data2) {
    max_value = data2;
    max_index = 2;

  }
  if (max_value < data3) {
    max_value = data3;
    max_index = 3;

  }
  if (max_value < data4) {
    max_value = data4;
    max_index = 4;

  }
  if (max_value < data5) {
    max_value = data5;
    max_index = 5;

  }
  if (max_value < data6) {
    max_value = data6;
    max_index = 6;

  }
  if (max_value < data7) {
    max_value = data7;
    max_index = 7;

  }
  if (max_value < data8) {
    max_value = data8;
    max_index = 8;

  }
  Serial.println((max_index * 45 - 22.5));

}