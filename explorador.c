// C++ code
//
//INCLUDES DE BIBLIOTECAS NECESSARIAS
#include <Servo.h>
#include <Ultrasonic.h>
//FIM DOS INCLUDES

//DEFINIÇÃO DE PINOS DE SENSORES
#define pino_trigger 9 //PINO TRIGGER SONAR
#define pino_echo 8 //PINO ECHO SONAR
//FIM DOS PINOS DE SENSORES

//DEFINIÇÃO DE PINOS DE MOTORES
#define servo 2 // DEFINIÇÃO PINO SERVO MOTOR
#define pino1Motor1 6 //MOTOR DIREITA +
#define pino2Motor1 7 //MOTOR DIREITA -
#define pino1Motor2 12 //MOTOR ESQUERDA +
#define pino2Motor2 13 //MOTOR ESQUERDA -
#define EN1 10
#define EN2 11
//FIM DOS PINOS DE MOTORES

//DECLARAÇÃO DE OBJETOS
Servo cabeca; //CRIAÇÃO DO OBJETO CABECA PARA SERVO MOTOR
Ultrasonic ultrasonic(pino_trigger, pino_echo); //CRIAÇÃO DO OBJETO PARA USO NA LEITURA DE DISTANCIA FUNÇÃO LEITURA()
//FIM DA DECLARAÇÃO DE OBJETOS

//DECLARAÇÃO DE VARIAVEIS
int angulo;
float distancia,distancia0,distancia90,distancia180;
//FIM DAS VARIAVEIS

void setup() {  

    //SETUP DE SENSORES  
    pinMode(pino_trigger, OUTPUT);
    pinMode(pino_echo, INPUT);
    //FIM SETUP SENSORES

    //SETUP DE MOTORES
    cabeca.attach(servo);
    pinMode(pino1Motor1, OUTPUT); 
    pinMode(pino2Motor1, OUTPUT); 
    pinMode(pino1Motor2, OUTPUT);
    pinMode(pino2Motor2, OUTPUT);
    pinMode(EN1, OUTPUT);
    pinMode(EN2, OUTPUT);
    //FIM SETUP DE MOTORES

    //SETUP SERIAL
    Serial.begin(9600); 
    //FIM SERIAL

    varredura();
    cabeca.write(90);
    digitalWrite(EN1, HIGH);
    digitalWrite(EN2, HIGH);



     
}
  
void loop () {

    
    leitura();
 
    
    if (distancia < 15){
      digitalWrite(pino1Motor1,LOW);
      digitalWrite(pino2Motor1,LOW);

      digitalWrite(pino1Motor2,LOW);
      digitalWrite(pino2Motor2,LOW);
      delay(500);
      varredura();
    }
    if ((distancia90 > 15) && (distancia90 > distancia0) && (distancia90 > distancia180)){

      digitalWrite(pino1Motor1,50);
      digitalWrite(pino2Motor1,LOW);

      digitalWrite(pino1Motor2,50);
      digitalWrite(pino2Motor2,LOW);
      delay(500);
      Serial.write("to para frente");
      
    }else if ((distancia0 < 15) && (distancia180 < 15) && (distancia90 < 15)){
      //liga motores para tras 
       Serial.write("re");
      digitalWrite(pino1Motor1,LOW);
      digitalWrite(pino2Motor1,50);

      digitalWrite(pino1Motor2,LOW);
      digitalWrite(pino2Motor2,50);
      delay(500);
    }else if ((distancia0 > distancia180) && (distancia0 > distancia90) && (distancia0 > 15)){
      //liga motores para esquerda
       Serial.write("to para esquerda");
       digitalWrite(pino1Motor1,50);
      digitalWrite(pino2Motor1,LOW);

      digitalWrite(pino1Motor2,LOW);
      digitalWrite(pino2Motor2,LOW);
      delay(500);
    }else if ((distancia180 > distancia0) && (distancia180 > distancia90) && (distancia180 > 15)){
      //Liga motores para direita
       Serial.write("to para direita");
      digitalWrite(pino1Motor1,LOW);
      digitalWrite(pino2Motor1,LOW);

      digitalWrite(pino1Motor2,50);
      digitalWrite(pino2Motor2,LOW);
      delay(500);
    }
     
  
}






void leitura() {
  //FUNÇÃO PARA LEITURA DE DISTANCIA SONAR
   
  long microsec = ultrasonic.timing();
  distancia = ultrasonic.convert(microsec, Ultrasonic::CM);
  //Exibe informacoes no serial monitor
  Serial.println("Distancia em cm: ");
  Serial.println(distancia);

  //FIM DA FUNÇÃO
}


void varredura(){
  
  //INICIA VARREDURA DE MELHORA CAMINHO  
  cabeca.write(0);
    leitura();
    distancia0=distancia;
    delay(1000);
  
    //cabeca.write(45);
    //leitura();
    //distancia45=distancia;
    //delay(1000);
  
    cabeca.write(90);
    leitura();
    distancia90=distancia;
    delay(1000);
  
    //cabeca.write(135);
    //leitura();
    //distancia135=distancia;
    //delay(1000);
  
    cabeca.write(180);
    leitura();
    distancia180=distancia;
  delay(1000);  
//FIM DA VARREDURA
  
}