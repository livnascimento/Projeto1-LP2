#include <LiquidCrystal.h>

LiquidCrystal lcd(7, 6, 5, 4, 3, 2);

// ===== declaração das variáveis =======

int lux, gas;
float temp, tensaoTemp, tensaoLux, corrente, ldr, umid, ppm, res;

// =============== funções ==============
  
//Função do DHT22 - simulação de sensor umidade
  
float dht_readHumidity(){
  float umidade = map(analogRead(A3), 0, 1023, 0, 999);
  return umidade/10.0;  
}

// criar carctere personalizado °

byte graus[8] = { B00001100,B00010010,B00010010,B00001100,B00000000,B00000000,B00000000,B00000000};

void setup() {
  
  Serial.begin(9600);
  
  lcd.begin(16, 2);
  
  lcd.print("LP2 - PROJETO n1");
  lcd.setCursor(2,1);
  lcd.print("LIVIA RAIANE");
  delay(2000);
  lcd.clear();
  lcd.setCursor(2,0);
  lcd.print("UPE - 2020.2");
  lcd.setCursor(1,1);
  lcd.print("PROF. CARVALHO");
  delay(2000);
  lcd.clear();

//  analogReference(INTERNAL);
  
  lcd.createChar(0, graus);
}

void loop() {

// =============      fórmulas      ==============  
  
// temperatura
  
  tensaoTemp = (analogRead(A0)/1024.0)*5;
  temp = (tensaoTemp-0.5) * 100;
  
// luminosidade

  tensaoLux = (analogRead(A1)/1023.0)*5;
  res = tensaoLux*100000.0/(5-tensaoLux);
  lux = pow(10, 6.5 - 1.25*log10(res));
  
//  tensaoLux = analogRead(A1)*0.005;
//  corrente = (tensaoLux/10000);
//  ldr = (5 - tensaoLux)/corrente;
// lux = 255.84*pow(ldr, -10/9);
  
// gás
  
  ppm = pow(10, 2.3*log10(analogRead(A2))-3.1);

// umidade
               
  umid = 0.921455578*dht_readHumidity() + 2.560687389;
  

// ============= imprimindo na tela ==============
  
  lcd.clear();
  lcd.setCursor(0, 0);
  
// temperatura  
  
  lcd.print("Temp.: ");
  lcd.print(temp, 1);lcd.print(" "); lcd.write((uint8_t)0); lcd.print("C");
  delay(3000);
  lcd.clear();
  
// luminosidade
  
  lcd.setCursor(0, 0);
  lcd.print("Lum.: ");
  lcd.print(lux, 1); lcd.print(" Lux");
  
  // alerta de raios UV
  if (lux > 35){
    lcd.setCursor(0, 1);
    lcd.print("Use prote. solar");
  }
  
  delay(3000);
  lcd.clear();
    
// umidade
  
  lcd.setCursor(0, 0);
  lcd.print("Umid.: ");lcd.print(umid, 1); lcd.print(" %");
  delay(3000);
  lcd.clear();
  
// gás
    
  lcd.print("C.de Gas: "); lcd.print(ppm, 0); lcd.print(" ppm");
    
// verifica se deve ligar alerta de gás
  if (ppm > 300){
    tone(A4, 50, 3000);
    lcd.setCursor(0, 1);
    lcd.print("Gas detectado");

  }

  delay(3000);
} 
