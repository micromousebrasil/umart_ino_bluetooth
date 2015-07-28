/**
 *****************************************************************
 * Arquivo  umart_ino_bluetooth.ino
 * Autor    Kleber Lima da Silva (micromousebrasil@gmail.com)
 * Versão   V1.0.0
 * Data     12-Maio-2015
 * Resumo   Programa para teste do hardware do Robô uMaRT-INO no
 *         modo micromouse (solucionador de labirinto)
 *****************************************************************
 */

// Definição dos pinos -------------------------------------------
const int B_ENC_E = 2;     // Encoder do motor esquerdo (sinal B)
const int A_ENC_D = 3;     // Encoder do motor direito (sinal A)
const int A_ENC_E = 4;     // Encoder do motor esquerdo (sinal A)
const int B_ENC_D = 5;     // Encoder do motor direito (sinal B)
const int PWM_E = 6;       // PWM do motor esquerdo
const int IN2_E = 7;       // IN2 da ponte H do motor esquerdo
const int IN1_E = 8;       // IN1 da ponte H do motor esquerdo
const int IN1_D = 9;       // IN1 da ponte H do motor direito
const int IN2_D = 10;      // IN2 da ponte H do motor direito
const int PWM_D = 11;      // PWM do motor direito
const int SW1 = 12;        // Botão SW1

// Protótipos das funções ----------------------------------------
void setMotores(int pwm_esquerda, int pwm_direita);

// Inicialização dos pinos ---------------------------------------
void setup()
{
  pinMode(0, INPUT);
  pinMode(1, OUTPUT);
  pinMode(PWM_E, OUTPUT);
  pinMode(IN1_E, OUTPUT);
  pinMode(IN2_E, OUTPUT);
  pinMode(PWM_D, OUTPUT);
  pinMode(IN1_D, OUTPUT);
  pinMode(IN2_D, OUTPUT);
  pinMode(SW1, INPUT);
  
  Serial.begin(115200);
  Serial.setTimeout(200);
  
  // Aguarda o botão SW1 ser pressionado para ligar o robô
  while(digitalRead(SW1) == LOW);
  delay(1000);
}


// LOOP principal do programa ------------------------------------
void loop()
{
  String str;
  int v1, v2;
  
  // Formatação do comando: "A100B100\n"
  // Onde o número depois do A é a velocidade do motor da esquerda
  //   e o número depois do B é a velocidade do motor da direita
  // Estes valores devem estar entre -100 e 100 (valores negativos
  //   indicam o sentido contrário do motor)
  if(Serial.available() > 0)
  {
    str = Serial.readStringUntil('A');
    v1 = Serial.parseInt();
    str = Serial.readStringUntil('B');
    v2 = Serial.parseInt(); 
    
    v1 = map(v1, -100, 100, -255, 255);
    v2 = map(v2, -100, 100, -255, 255);
      
    setMotores(v1, v2);
  }
}


/* Função para acionamento dos motores ---------------------------
 * pwm_esquerda e pwm_direita recebem valores entre -255 e 255
 * (valores negativos giram o respectivo motor para trás)
 */
void setMotores(int pwm_esquerda, int pwm_direita)
{
  if(pwm_esquerda < 0)
  {
    pwm_esquerda *= -1;
  
    digitalWrite(IN1_E, LOW);
    digitalWrite(IN2_E, HIGH);
  }
  else
  {
    digitalWrite(IN1_E, HIGH);
    digitalWrite(IN2_E, LOW);
  }
  
  if(pwm_direita < 0)
  {
    pwm_direita *= -1;
  
    digitalWrite(IN1_D, LOW);
    digitalWrite(IN2_D, HIGH);
  }
  else
  {
    digitalWrite(IN1_D, HIGH);
    digitalWrite(IN2_D, LOW);
  }
  
  if(pwm_esquerda > 255) pwm_esquerda = 255;
  if(pwm_direita > 255) pwm_direita = 255;
  
  analogWrite(PWM_E, pwm_esquerda);
  analogWrite(PWM_D, pwm_direita);
}

