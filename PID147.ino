/* CONTROLE DIGITAL UTILIZANDO TÉCNICA P I D PARA AR CONDICIONADO VEICULAR
   PROJETO INICIADO EM 15/12/2014 - IDE 1.05
   LUCAS MALDONADO MORENO
   https://www.youtube.com/watch?v=txftR4TqKYA#t=104 - REFERENCIAS DO PROGRAMA
   //TESTE 05/12/2017
*/

/* SISTEMA HARDWARE
   PINO 3 - CONTROLE PWM DO VENTILADOR
   PINO 5 - CONTROLE ON/OFF DO COMPRESSOR
   PINO A0 - SENSOR DE TEMPERATURA LM35
 O HARDWARE DEVE CONTAR AINDA COM DISPLAY LCD E BOTÕES PARA CONTROLE DA TEMPERATURA
*/

#define pSENSOR A0
#define pVENTILADOR 3
#define pCOMPRESSOR 5

int destemperatura = 20; // Temperatura desejada ****


void setup(){
    Serial.begin(9600);
    
    pinMode(pSENSOR, INPUT);
    pinMode(pVENTILADOR, OUTPUT);
    pinMode(pCOMPRESSOR, OUTPUT);
    

}

double error = 0;
double temperature;
double lastTemperature;

double 
    kP = 1.0,   // Acertar aqui
    kI = 0.0,   // Acertar aqui
    kD = 0.0;   // Acertar aqui
    
double 
    P = 0, 
    I = 0, 
    D = 0;
    
double PID = 0;

double setPoint = destemperatura;
int controlePwm = 50; // ****

long lastProcess = 0;


void loop(){
        
        // Lê temperatura  
        temperature = map(analogRead(pSENSOR), 0, 1023, 0, 100); //Verificar esta conversão ****
        
        // Implementação P I D
        error = setPoint - temperature;
        float deltaTime = (millis() - lastProcess) / 1000;
        lastProcess = millis();
        
        // P
        P = error * kP;
        
        // I
        I += (error * kI) * deltaTime;
       
        // D
        D = (lastTemperature - temperature) * kD / deltaTime;
        lastTemperature = temperature;
        
        // Soma tudo
        PID = P + I + D;
        
        // Converte PID para controle PWM
        controlePwm = (PID); // Verificar ****
        
        /* ADICIONAR AQUI A ANÁLISE DO PID PARA CONTROLAR
           O COMPRESSOR
        */
       
        
        
        
        // Saida do controle ventilador
        analogWrite(pVENTILADOR, controlePwm);
        

}





