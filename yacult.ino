#include <Stepper.h> 

//Numero de volta para cada passo do nosso modelo de motor
const int stepsPerRevolution = 32; 
  
//Inicializa a biblioteca utilizando as portas de 8 a 11 para 
//ligacao ao motor 
Stepper myStepper(stepsPerRevolution, 8,10,9,11); 

//Definicao das portas do sensor ultrassonico
#define pinTrig 2
#define pinEcho 3

//Inicializa variavel para verificar distancia para o sensor
double distancia1 = 0;
double distancia2 = 0;

//Recebe a quantidade de milisegundos que o arduino esta ligado
long tempoComporta = millis();

void setup()
{
 //Determina a velocidade inicial do motor 
 myStepper.setSpeed(480);
  pinMode(pinTrig, OUTPUT);
  pinMode(pinEcho, INPUT);
  
  Serial.begin(9600);
}

void loop()
{
  lerSonar();
  distancia1 = pulseIn(pinEcho, HIGH);
  //Formula simplificada para definir a distancia para o sensor em centimetros
  distancia1 = distancia1/58.3;
  delay(2000);

  lerSonar();
  distancia2 = pulseIn(pinEcho, HIGH);
  //Formula simplificada para definir a distancia para o sensor em centimetros
  distancia2 = distancia2/58.3;
  
  //Imprime na porta serial o monitoramento do sensor
  Serial.print(distancia1);
  Serial.println("  cm");
  Serial.print(distancia2);
  Serial.println("  cm");

  //Abre a comporta se as distancias estiverem entre 1 e 20cm e a ultima abertura estiver acontecido a mais de 10 segundos 
  if (distancia1 > 1 && distancia1 < 20 && distancia2 > 1 && distancia2 < 20 && (millis() - tempoComporta) > 10000)
  {    
    myStepper.step(512);
    myStepper.step(-512);
    tempoComporta = millis();
    delay(1000); 
  }

}

//Dispara a execucao do sonar
void lerSonar()
{
  digitalWrite(pinTrig, HIGH);
  delayMicroseconds(10);
  digitalWrite(pinTrig, LOW);
  
}
