
///////////////////////////////////////////////////////////
///////   Biblioteca Biblioteca referente ao PID  /////////
///////////////////////////////////////////////////////////

#include <PID_v1.h>

//Variaveis de entrada e saida PID

double input;
double output;


// Setpoint e ganhos do PID
double setpoint=2500;
double Kp = 0.07;      // 0.1 Bateria Normal //0.09   //0.1    //0.07 bons
double Ki = 0.00001;     //0.01 Bateria Normal //0.015   //00  //0.00001
double Kd = 0.0017;       //0.0  Bateria Normal //00      //5.0 //0.001

// Limites PID

int max_pid = 255;
int min_pid = -255;
int min_vel = 20;

//Variáveis para Controle

int speed_dir = 0;
int speed_esq = 0;


///////////////////////////////////////////////////////////
////////////   Calculo Position Dragon Force  /////////////
///////////////////////////////////////////////////////////

float position_dragon=2500;   //posição em relação a linha branca 0--> totalmente a esquerda 2500 --> centro 5000-> totalmente a direta

int min_value_S0=172;
int min_value_S1=72;
int min_value_S2=171;
int min_value_S3=266;
int min_value_S4=284;
int min_value_S5=88;

int max_value_S0=1015;
int max_value_S1=1009;
int max_value_S2=1005;
int max_value_S3=1010;
int max_value_S4=1012;
int max_value_S5=1023;

float value_S0=0;
float value_S1=0;
float value_S2=0;
float value_S3=0;
float value_S4=0;
float value_S5=0;

float avg=0.0;    //media dos sensores 
float sun=0.0;    //soma dos sensores;
float last_position=2500.00;    //retenção da ultima posição caso sair para os lados




PID myController(&input, &output, &setpoint,Kp, Ki, Kd, DIRECT);

///////////////////////////////////////////////////////////
////////////////   Definição dos Pinos  ///////////////////
///////////////////////////////////////////////////////////


#define PININ1 2  //Avança Motor Direita  
#define PINENA 3  //PWM Motor Direita   AZUL
#define PININ2 4  //Retorna Motor Direita  
#define PININ3 5  //Avança Motor Esquerda  
#define PINENB 6  //PWM Motor Esquerda 
#define PININ4 7  //Retorna Motor Esquerda


///////////////////////////////////////////////////////////
////////////////   Tempo para execução  ///////////////////
///////////////////////////////////////////////////////////


#define RUNTIME 105500          // Valor para executar o percurso 



////////////////////////////////////////////////////////////

void setup()
{

    Serial.begin(9600);

   // Definições das portas digitais
  pinMode(PININ1, OUTPUT);
  pinMode(PININ2, OUTPUT);
  pinMode(PININ3, OUTPUT);
  pinMode(PININ4, OUTPUT);
  pinMode(PINENA, OUTPUT);
  pinMode(PINENB, OUTPUT);
  
  myController.SetMode(AUTOMATIC);
  myController.SetSampleTime(10);      // OPTIONAL - will ensure at least 10ms have past between successful compute() calls
  myController.SetOutputLimits(min_pid, max_pid);


  delay(2000);
  }

void loop()
{
 
 //Bloco para controle via PID
 // postion_df();

  followLineMEF();

  
}
void postion_df(){

value_S0=map(analogRead(A0),min_value_S0,max_value_S0,1000,0);  //1000 totalmente branco e 0 totalmente preto
value_S1=map(analogRead(A1),min_value_S1,max_value_S1,1000,0);  //1000 totalmente branco e 0 totalmente preto
value_S2=map(analogRead(A2),min_value_S2,max_value_S2,1000,0);  //1000 totalmente branco e 0 totalmente preto
value_S3=map(analogRead(A3),min_value_S3,max_value_S3,1000,0);  //1000 totalmente branco e 0 totalmente preto
value_S4=map(analogRead(A4),min_value_S4,max_value_S4,1000,0);  //1000 totalmente branco e 0 totalmente preto
value_S5=map(analogRead(A5),min_value_S5,max_value_S5,1000,0);  //1000 totalmente branco e 0 totalmente preto


if (value_S0<0){value_S0=0;};
if (value_S1<0){value_S1=0;};
if (value_S2<0){value_S2=0;};
if (value_S3<0){value_S3=0;};
if (value_S4<0){value_S4=0;};
if (value_S5<0){value_S5=0;};

if (value_S0>1000){value_S0=1000;};
if (value_S1>1000){value_S1=1000;};
if (value_S2>1000){value_S2=1000;};
if (value_S3>1000){value_S3=1000;};
if (value_S4>1000){value_S4=1000;};
if (value_S5>1000){value_S5=1000;};


avg= ((value_S0*0)+(value_S1*1000)+(value_S2*2000)+(value_S3*3000)+(value_S4*4000)+(value_S5*5000));
sun= (value_S0+value_S1+value_S2+value_S3+value_S4+value_S5);

if (sun!=0){position_dragon=avg/sun;}

if (position_dragon<=4950.00){
   last_position=position_dragon;
}

if (last_position<50){
  position_dragon=0; //saiu para esquerda
}else if (last_position>4950){
   position_dragon=5000; //saiu para direita
}else if ((last_position>=50) || (last_position<=4950)){
   last_position=position_dragon; //saiu para direita
}




}


void motorControl(int speedRight , int speedLeft) {
  // Função para controle do driver de motor

  // Ajustes motor da esquerda
  if (speedLeft <0) {
    speedLeft = -speedLeft;
    digitalWrite (PININ3, LOW);//HIGH
    digitalWrite (PININ4, HIGH);//LOW
  } else {
    digitalWrite (PININ3, HIGH);
    digitalWrite (PININ4,LOW );
  }

  // Ajustes motor da direita
  if (speedRight < 0) {
    speedRight = -speedRight;
    digitalWrite (PININ1, LOW);
    digitalWrite (PININ2, HIGH);
  } else {
   digitalWrite (PININ1, HIGH );
    digitalWrite (PININ2, LOW);
  }
  analogWrite (PINENA, speedRight);
  analogWrite (PINENB, speedLeft);
}


bool motorStop(long runtime, long currentTime) {
  // Função de parada do robô
  if (millis() >= (runtime + currentTime)) {
   motorControl(0, 0);

    digitalWrite (PININ1, HIGH );
    digitalWrite (PININ2, HIGH);
    digitalWrite (PININ3, HIGH);
    digitalWrite (PININ4, HIGH);

    int cont = 0;
    while (true) {
         cont++;
    }
    return false;
  }
  return true;
}



void followLineMEF(void) {
  // Função para controle do seguidor de linha em modo de maquina de estado finita
  bool flag = true;
  long currentTime = millis();

  while (flag) {
    // Flag para verificar a parada
    flag = motorStop(RUNTIME, currentTime);

 postion_df();


input= position_dragon;


myController.Compute();


if (output>0){ // speed_dir=map(output,0,255,255,-140);
  if (output<=255/2) {        // para 
  speed_dir=map(output,0,122.5,255,min_vel);
  }else{
    speed_dir=map(output,122.5,255,-min_vel,-255);
  }

}else{
//speed_dir=map(output,-255,0,255,255);
speed_dir=255;
}

if (output>0){
speed_esq=255;
}else{//speed_esq = map(output,0,-255,255,-40);
    if (output<=255/2) {  
    speed_esq = map(output,0,-122.5,255,min_vel);
    }else{
    speed_esq = map(output,-122.5,-255,-min_vel,-255);
    }
}


motorControl(speed_dir,speed_esq);


 Serial.print(position_dragon);
      Serial.print(" ");
         Serial.print(output);
      Serial.print(" ");

     Serial.print(speed_dir);
     Serial.print(" ");
    Serial.print(speed_esq);
      Serial.print(" ");


      
      /*    Serial.print(digitalRead(PININ1));
      Serial.print(" ");
          Serial.print(digitalRead(PININ2));
      Serial.print(" ");
          Serial.print(digitalRead(PININ3));
      Serial.print(" ");
          Serial.print(digitalRead(PININ4));
          Serial.print(" ");
          Serial.print(analogRead(PINENA));
      Serial.print(" ");
        Serial.print(analogRead(PINENB));*/
      Serial.println(" ");
  }
}
