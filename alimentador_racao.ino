    
#define button 5             // recarga de racao manualmente
int segs = 0;                //segundos do horario corrente 
int mins = 0;                //minutos do horario corrente
int hrs = 0;                 // horas do horario corrente

                                   
int carga_segs = 0;          //segundos do horario programado
int carga_mins = 0;          //minutos do horario programado
int carga_hrs = 3;           // horas do horario programado

int flag      =0 ;           // estado apos apertar o button

int rele = 12;

boolean buttonState;

unsigned long ini;       // horario inicial
unsigned long atual;     // horario atual
int conta = 0;

void setup() {
    pinMode(8,OUTPUT);  //pino 8 configurado como saída  
    pinMode(button,INPUT_PULLUP);
    //setando o horario inicial
    Serial.begin(9600);  
    pinMode(rele, OUTPUT); 
    hrs = 0;
    mins = 0;
    segs = 00;
    flag      =0;
}

void loop() {
  //computando o tempo
  atual = millis();
  
  if (( atual - ini) > 1000)
  {
      ini = ini +1000;
      
      segs +=1;
      if (segs > 59)
      {
        mins +=1;
        segs = 0;
        
      }

      if (mins > 59)
      {
        hrs += 1;
        mins = 0;
        
      }
      if (hrs > 23)
      {
        hrs = 0;
      }
        String hourSt = String(hrs);
        String minutesSt = String(mins);
        String segstesSt = String(segs);
        String carga_bandeja = String(conta);
        
      if(buttonState==0)
      {
        segs=0;
        flag=0;
      
      }

      if (carga_hrs==hrs&&carga_mins==mins||flag==0)
      {
          if(segs>1)
          {      flag=1;
             hrs = 0;
             mins = 0;
             segs = 00;   

             conta = conta + 1;
          
           }
          digitalWrite(rele, HIGH); 
          digitalWrite(8, HIGH); //acende Led 
      
      }else
      {
          digitalWrite(rele, LOW);
          digitalWrite(8, LOW); //apaga Led 
        
        
      }
      
        String dateTime = hourSt +":"+ minutesSt+":"+ segstesSt+ " Alimentação :"+carga_bandeja+" button : "+buttonState;
        buttonState = digitalRead(button);  
        Serial.println(dateTime);
  }


    delay(100);
}
