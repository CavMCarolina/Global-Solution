// Bibliotecas que serão utilizadas
#include <Servo.h>
#include <Adafruit_LiquidCrystal.h> 

// Definindo Pinos
int ledR = 13;
int ledY = 12;
int ledG = 11;
int pin = A1;
int buzzer = 10;
int pir = 9;
Adafruit_LiquidCrystal lcd_1(0);

// Definindo servo e variáveis para leitura dos sensores
Servo servo;
int ler;
int lerLDR;

//Definir o que é output e o que é input, além de definir um pino para o servo
void setup()
{
  Serial.begin(9600);
  
  pinMode(ledR, OUTPUT);
  pinMode(ledY, OUTPUT);
  pinMode(ledG, OUTPUT);
  pinMode(pin, INPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(pir, INPUT);
  
  servo.attach(8);
  
  // Deixar LCD desligado no começo
  lcd_1.setBacklight(0);
}

// Se o sensor de movimento captar algo, "abrir a porta". Caso contrário, fechar.
void loop()
{ 
  ler = digitalRead(pir);
  if (ler == HIGH){
    servo.write(180);
    delay(1000); 
    
    // Quando alguém passar pela porta ativar o monitoramento automático.
    int lerLDR = analogRead(pin);

    // Printar a luminosidade na serial
    Serial.print("Luminosidade: ");
    Serial.println(lerLDR);
    
    // Caso esteja tudo bem, acender led verde
    if (lerLDR < 145) {
      digitalWrite(ledR, HIGH);
      digitalWrite(ledY, HIGH);
      digitalWrite(ledG, LOW);
      noTone(buzzer);
      
      // Printar a luminosidade no LCD
      lcd_1.setBacklight(1);
      lcd_1.begin(16, 2);
      lcd_1.print("Luminosidade: ");
      
      lcd_1.setCursor(13, 0);
  	  lcd_1.print(lerLDR);
      
      // Printar feedback
      lcd_1.setCursor(0,1);
      lcd_1.print("Tudo ok");
    }
    
    // Se estiver em estado alerta, acender o amarelo e apitar o buzzer
    else if (lerLDR <= 300) {
      digitalWrite(ledR, HIGH);
      digitalWrite(ledY, LOW);
      digitalWrite(ledG, HIGH);
      tone(buzzer, 500);
      delay(100);
      noTone(buzzer);
      delay(600);
      tone(buzzer, 500);
      delay(100);
      
      // Printar no LCD a luminosidade
      lcd_1.setBacklight(1);
      lcd_1.begin(16, 2);
      lcd_1.print("Luminosidade: ");
      
      lcd_1.setCursor(13, 0);
  	  lcd_1.print(lerLDR);
      
      // Printar feedback
      lcd_1.setCursor(0,1);
      lcd_1.print("Estado alerta");
    }
    
    // Para sinalizar perigo, acender o vermelho e som constante
    else {
      digitalWrite(ledR, LOW);
      digitalWrite(ledY, HIGH);
      digitalWrite(ledG, HIGH);
      tone(buzzer, 1000);
      
      // Printar no LCD a luminosidade
      lcd_1.setBacklight(1);
      lcd_1.begin(16, 2);
      lcd_1.print("Luminosidade: ");
      
      lcd_1.setCursor(13, 0);
  	  lcd_1.print(lerLDR);
      
      // Printar feedback
      lcd_1.setCursor(0,1);
      lcd_1.print("Estado critico");
    }
  }
  
  // Fechar a porta, deixar leds apagados e apagar lcd
  else {
    noTone(buzzer);
    digitalWrite(ledR, HIGH);
    digitalWrite(ledY, HIGH);
    digitalWrite(ledG, HIGH);
    servo.write(0);
    
    lcd_1.setBacklight(0);
  }
  
} 