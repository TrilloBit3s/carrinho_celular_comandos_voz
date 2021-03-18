//Desenvolvido por MICHAEL MORAES SABINO
//E-MAIL estuartyy@gmail.com
//data 30-11-2017
//carrinho controlado por celular e comandos de voz

#include <SoftwareSerial.h>

#define LED_Verd_Esq 4 //define LED verde 1
#define LED_Verd_Dir 7  //define LED verde 2
#define LED_Verm_Esq 12 //define LED vermelho 1 
#define LED_Verm_Dir 13  //define LED vermelho 2

#define BUZZER 8 //BUZZER

SoftwareSerial BT(0, 1); //TX, RX respetively
String readvoice; //leitura de voz

const int motorA1  = 5;//Motor lado esquerdo
const int motorA2  = 6;//Motor lado esquerdo
const int motorB1  = 10;//Motor lado direito
const int motorB2  = 11;//Motor lado direito

const int ENA = 3;//ENA
const int ENB = 9;//ENB 

const int BTState = 2;//Pino 2 como o pino de comunicação do Bluetooth.

int i = 0;//VariáveL
int j = 0;//VariáveL
int state_rec;//variavel para armazenamento de dados.
int vSpeed = 200;//Define velocidade padrão 0 a 255.
char state;//state recebe os caracteres do celular

void setup() {
 
  BT.begin(9600);
  Serial.begin(9600);
 
  pinMode(motorA1, OUTPUT); 
  pinMode(motorA2, OUTPUT);
  pinMode(motorB1, OUTPUT);
  pinMode(motorB2, OUTPUT); 
  pinMode (ENA, OUTPUT);
  pinMode (ENB, OUTPUT);
  pinMode(BUZZER, OUTPUT);
  noTone(BUZZER);
  pinMode(LED_Verd_Esq, OUTPUT);//led verde esquerdo
  pinMode(LED_Verd_Dir, OUTPUT);//led verde direito
  pinMode(LED_Verm_Esq, OUTPUT);//led vermelho esquerdo
  pinMode(LED_Verm_Dir, OUTPUT);//led vermelho direito
  pinMode(BTState, INPUT); 
}

void loop() {

  analogWrite(ENA, 90); //velovidade do motor esquerdo
  analogWrite(ENB, 90); //velovidade do motor esquerdo
  
  while (BT.available()){  //Verifique se há um byte disponível para ler
  delay(5); //Atraso adicionado para tornar a coisa estável
  char c = BT.read(); //Conduzir uma leitura em série
  readvoice += c; //construir a string - "forward", "reverse", "left" e "right"
  } 
  if (readvoice.length() > 0) {
    Serial.println(readvoice);

  if(readvoice == "*para frente#")
  {
    analogWrite(motorA1, 0);
    analogWrite(motorA2, 100);
    analogWrite(motorB1, 100);
    analogWrite(motorB2, 0);
  }
  else if(readvoice == "*para trás#")
  {
    analogWrite(motorA1, 100);
    analogWrite(motorA2, 0);
    analogWrite(motorB1, 0);
    analogWrite(motorB2, 100);
  }
  else if (readvoice == "*esquerda#")
  {
    analogWrite(motorA1, 0);   
    analogWrite(motorA2, vSpeed);
    analogWrite(motorB1, 0); 
    analogWrite(motorB2, 100);
    delay(600);
    analogWrite(motorA1, 0);   
    analogWrite(motorA2, 0);
    analogWrite(motorB1, 0); 
    analogWrite(motorB2, 0);
  }
 else if (readvoice == "*direita#")
 {
    analogWrite(motorA1, 100); 
    analogWrite(motorA2, 0);
    analogWrite(motorB1, vSpeed);      
    analogWrite(motorB2, 0); 
    delay(600);
    analogWrite(motorA1, 0); 
    analogWrite(motorA2, 0);
    analogWrite(motorB1, 0);      
    analogWrite(motorB2, 0); 
 }
 else if (readvoice == "*pare#")
 {
    analogWrite(motorA1, 0);
    analogWrite(motorA2, 0);
    analogWrite(motorB1, 0);
    analogWrite(motorB2, 0);
 }
 else if (readvoice == "*ligar o farol da frente#")
 {      
    digitalWrite(LED_Verd_Esq, HIGH);
    digitalWrite(LED_Verd_Dir, HIGH);
    delay (100);
 }
  else if (readvoice == "*desligar o farol da frente#")
 {
   digitalWrite(LED_Verd_Esq, LOW);//led apagado
   digitalWrite(LED_Verd_Dir, LOW); 
   delay (100); 
 }
 else if (readvoice == "*ligar o farol de trás#")
 {      
    digitalWrite(LED_Verm_Esq, HIGH);
    digitalWrite(LED_Verm_Dir, HIGH);
    delay (100);
 }
  else if (readvoice == "*desligar o farol de trás#")
 {
    digitalWrite(LED_Verm_Esq, LOW);//led apagado
    digitalWrite(LED_Verm_Dir, LOW);  
   delay (100); 
 }
 else if (readvoice == "*ligar a buzina#")
 {      
    tone(BUZZER, 1000);
    delay (100);
 }
  else if (readvoice == "*desligar a buzina#")
 {
   noTone(BUZZER);
   delay (100); 
 }
  else if (readvoice == "*ligar os faróis#")
 {
    digitalWrite(LED_Verd_Esq, HIGH);
    digitalWrite(LED_Verd_Dir, HIGH);
    digitalWrite(LED_Verm_Esq, HIGH);
    digitalWrite(LED_Verm_Dir, HIGH);
   delay (100); 
 }
 else if (readvoice == "*desligar os faróis#")
 {      
   digitalWrite(LED_Verd_Esq, LOW);//led apagado
   digitalWrite(LED_Verd_Dir, LOW); 
   digitalWrite(LED_Verm_Esq, LOW);//led apagado
   digitalWrite(LED_Verm_Dir, LOW);
   delay (100);
 }
 
  readvoice="";
  }
  
  // Para o carrinho quando a conexão com Bluetooth é desconectada.
  if (digitalRead(BTState) == LOW) {
    state_rec = 'S';
  }

  // Salva os valores da variável 'state'
  if (Serial.available() > 0) {
    state_rec = Serial.read();
    state = state_rec;
    //Serial.println(vSpeed); //mostra na serial a velocidade
  }

  // Altera a velocidade de acordo com valores especificados.
  if (state == '0') {
    vSpeed = 0;
  }
  else if (state == '4') {
    vSpeed = 100;
  }
  else if (state == '6') {
    vSpeed = 155;
  }
  else if (state == '7') {
    vSpeed = 180;
  }
  else if (state == '8') {
    vSpeed = 200;
  }
  else if (state == '9') {
    vSpeed = 230;
  }
  else if (state == 'q') {
    vSpeed = 255;
  }  

  if (state != 'S') {
    Serial.print(state);
  }
   if (state == 'F') {// Se o estado recebido for igual a 'F', o carro se movimenta para frente.
    analogWrite(motorA1, 0);
    analogWrite(motorA2, vSpeed);
    analogWrite(motorB1, vSpeed);
    analogWrite(motorB2, 0);
  }
 
   else if (state == 'I') {// Se o estado recebido for igual a 'I', o carro se movimenta para Frente Direita.  
    analogWrite(motorA1, 100); 
    analogWrite(motorA2, 0);
    analogWrite(motorB1, vSpeed);      
    analogWrite(motorB2, 0); 
  }
  
   else if (state == 'G') {// Se o estado recebido for igual a 'G', o carro se movimenta para Frente Esquerda.
    analogWrite(motorA1, 0);   
    analogWrite(motorA2, vSpeed);
    analogWrite(motorB1, 0); 
    analogWrite(motorB2, 100);
  }

  else if (state == 'R') { // Se o estado recebido for igual a 'R', o carro se movimenta para direita.       
    analogWrite(motorB1, vSpeed);
    analogWrite(motorA1, vSpeed);
    analogWrite(motorA2, 0);
    analogWrite(motorB2, 0);
  }

   else if (state == 'H') {// Se o estado recebido for igual a 'H', o carro se movimenta para Trás Esquerda.
    analogWrite(motorA1, vSpeed); 
    analogWrite(motorA2, 0);
    analogWrite(motorB1, 0);    
    analogWrite(motorB2, 100);
  }  
  
  else if (state == 'J') {// Se o estado recebido for igual a 'J', o carro se movimenta para Trás Direita.
    analogWrite(motorA1, 0);   
    analogWrite(motorA2, 100);
    analogWrite(motorB1, 0);   
    analogWrite(motorB2, vSpeed);
  }
  
  else if (state == 'L') {// Se o estado recebido for igual a 'L', o carro se movimenta para esquerda.
    analogWrite(motorA1, 0);
    analogWrite(motorB1, 0);
    analogWrite(motorB2, vSpeed);
    analogWrite(motorA2, vSpeed);
  }
  
  else if (state == 'B') {// Se o estado recebido for igual a 'B', o carro se movimenta para trás.
    analogWrite(motorA1, vSpeed);
    analogWrite(motorA2, 0);
    analogWrite(motorB1, 0);
    analogWrite(motorB2, vSpeed);
  }
  
  else if (state == 'S') {// Se o estado recebido for igual a 'S', o carro permanece parado.
    analogWrite(motorA1, 0);
    analogWrite(motorA2, 0);
    analogWrite(motorB1, 0);
    analogWrite(motorB2, 0);
  }

  else if (state == 'V') { // Se o estado recebido for iguala 'V', aciona a buzina.
    if (j == 0) {
      tone(BUZZER, 1000);
      j = 1;
    }
    else if (j == 1) {
      noTone(BUZZER);
      j = 0;
    }
    state = 'n';
  }
   else if (state == 'W'){
    if(j == 0){
      digitalWrite(LED_Verd_Esq, HIGH);
      digitalWrite(LED_Verd_Dir, HIGH);
      j = 1;
    }
     else if (j == 1){
      digitalWrite(LED_Verd_Esq, LOW);//led apagado
      digitalWrite(LED_Verd_Dir, LOW);  
      j = 0;
     }
     state = 'n';
   }
   else if (state == 'U'){
    if(j == 0){
      digitalWrite(LED_Verm_Esq, HIGH);
      digitalWrite(LED_Verm_Dir, HIGH);
      delay(100);
      j = 1;
    }
     else if (j == 1){
      digitalWrite(LED_Verm_Esq, LOW);//led apagado
      digitalWrite(LED_Verm_Dir, LOW);  
      j = 0;
     }
     state = 'n';
   }
   else if (state == 'X'){
    if(j == 0){
     delay(100);
     j = 1;
    }
     else if (j == 1){   
      j = 0;
     }
    state = 'n';
   }
 } //fecha loop
