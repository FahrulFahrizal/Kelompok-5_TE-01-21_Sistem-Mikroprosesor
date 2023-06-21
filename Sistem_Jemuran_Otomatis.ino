#include <Stepper.h> //library motor stepper

// Motor Stepper
int motor1 = 3; //pin motor stepper
int motor2 = 5; 
int motor3 = 6; 
int motor4 = 9;
const int stepsPerRevolution = 2048; //jumlah steps per revolusi 
const int rpm = 15; //kecepatan putaran motor stepper dalam rotasi per menit
bool hold1 = false; //status motor menahan putaran jemur 
bool hold2 = false; //status motor menahan putaran kembali
bool Stop = false; //status motor berhenti berputar
Stepper stepper1 = Stepper(stepsPerRevolution, motor1, motor3, motor2, motor4); //inisialisasi pin motor stepper 

// Sensor
const int bawah = 0; //nilai minimal sensor hujan
const int atas = 1023; //nilai maksimal sensor hujan
int hujan = A1; //pin sensor hujan
int ldr = A2; //pin sensorldr


void setup() { 
  Serial.begin(9600); //inisialisasi serial port

  pinMode(A1, INPUT); //input sensor hujan
  pinMode(A2, INPUT); //input sensor ldr
  Serial.println("Program Ready"); //menampilkan program
  stepper1.setSpeed(rpm); //mengatur kecepatan motor stepper
}

void jemur(){ //fungsi untuk menjemur
  Stop = false; 
  Serial.println("Menjemur");
    stepper1.step(-stepsPerRevolution*2); //fungsi untuk menggerakan motor stepper
    delay(100);
      hold1 = true;
      hold2 = false;
      berhenti(); //memanggil fungsi berhenti 
}

void kembali() { //fungsi untuk mengembalikan jemuran ke posisi awal 
  Stop = false;
  Serial.println("Memasukan Jemuran"); 
    stepper1.step(stepsPerRevolution*2); //fungsi untuk menggerakan motor stepper
    delay(100);
      hold1 = false;
      hold2 = true;
      berhenti(); //memanggil fungsi berhenti 
}
 
void berhenti() { //fungsi berhenti untuk menghentikan motor 
  stepper1.step(0); //motor tidak beregerak
  Stop = true;
  Serial.println("Berhenti Menjemur");
  delay(1000);
}

void loop() { //fungsi perulangan
  hujan = analogRead(A1); //membaca nilai sensor hujan 
  int range = map(hujan, bawah, atas, 0, 520); 
  ldr = analogRead(A2); //membaca nilai sensor hujan 
  Serial.print("Sensor LDR: "); //menampilkan nilai senso ldr
  Serial.println(ldr);
  Serial.print("Sensor Hujan: "); //menampilkan nilai senso hujan
  Serial.println(range);

  delay(1000);

if((ldr <= 110) && (range > 480)){ //kondisi ke-1 ketika cuaca cerah
  Serial.println("Terang dan Kering"); //menampilkan tulisan
    if(hold1 == false){ //menggerakan motor 
      jemur(); //masuk ke fungsi jemur
    }
    else{if (hold1 == false && hold2 == true && Stop == true) { //menggerakan motor dengan kondisi yang tertulis
    jemur(); //masuk ke fungsi jemur 
    }}
    delay(1000); 
  }

  else if ((ldr <= 110) && (range < 480)){ //kondisi ke-2 ketika cuaca mendung
  Serial.println("Terang dan Basah"); //menampilkan tulisan
    if (hold2 == false && Stop == true) { //menggerakan motor dengan kondisi yang tertulis 
    kembali(); //masuk ke fungsi kembali
    }
    delay(1000);
  }

  else if ((ldr > 110) && (range > 480)){ //kondisi ke-3 ketika cuaca berawan
  Serial.println("Gelap dan Kering"); //menampilkan tulisan
    if (hold2 == false && Stop == true) { //menggerakan motor dengan kondisi yang tertulis 
    kembali(); //mamsuk ke fungsi kembali 
    }
    delay(1000);
  }  

  else if ((ldr > 110)&&(range < 480)){ //kondisi ke-4 ketika cuaca hujan
    Serial.println("Gelap dan Basah"); //menampilkan tulisan
    if (hold2 == false && Stop == true) { //menggerakan motor dengan kondisi yang tertulis 
    kembali(); //masuk ke fungsi kembali 
    }

  } delay(1000);
}




