
#include <LiquidCrystal.h> 
#include <Servo.h>
LiquidCrystal lcd(7,6,5,4,3,2);
//cccccc
char * mensaje1 = "WARNING!!!                WARNING!!!";
char * mensaje2 = "                ARE YOU READY FOR THE ROUND 2?!!                ";//mismo tamano ambos mensajes

const int sumar = 9;///
const int restar = 10;///
const int start = 8;///

unsigned long segundos = 0; // Tiempo inicial en segundos///
unsigned long minutos = 0; // Tiempo inicial en minutos///
boolean readyGo = false;///

int LEDVERDE = 13;  //Codigo de los Led's
int LEDROJO = 12;

Servo motor;    //Codigo del motor
int posicion = 0;
int PINSERVO = 11;

void setup()
{
  lcd.begin (16, 2);
  pinMode(sumar, INPUT_PULLUP);///
  pinMode(restar, INPUT_PULLUP);///
  
  motor.attach (PINSERVO);    //codigo del motor
}

long intervalo = 150;
long tiempoAntes = millis();

int i = 0;
void loop()
{
  
  long tiempoDespues = millis();                  //se le asigna a tiempoDespues el valor de millis
  long a = (segundos);                    //se aprobecha este recurso para darle a "s" los segundos
  long b = (minutos);                     //se aprobecha este recurso para darle a "m" los segundos
  lcd.setCursor(3, 1);                    //colocar el cursor en la columna 3 para escribir desde ahi en adelante
  

  if (readyGo){
    lcd.print("sssss");
  }
 

  if (!readyGo){     ////
    digitalWrite(LEDROJO, HIGH);   //Codigo de los Led's
    digitalWrite(LEDVERDE, LOW);
    motor.write(90);        //Codigo del motor
    if(digitalRead(sumar) == HIGH) {
    segundos += 10;
    lcd.setCursor(3, 1);                           //colocar el cursor en la columna 4 para escribir desde ahi en adelante
    lcd.print("                   ");
    }

    if (digitalRead(restar) == HIGH){   
      if(a >= 10) {
        segundos -= 10;
        lcd.setCursor(3, 1);                           //colocar el cursor en la columna 4 para escribir desde ahi en adelante
        lcd.print("                   ");
        delay(200);
      }
    }

    lcd.setCursor(3, 1);
    if(minutos <= 9 && segundos > 9){
    lcd.print("Time: 0" + String(b) +":"+ String(a));
    }
    else if(minutos <= 9 && segundos <= 9){
    lcd.print("Time: 0" + String(b) +":0"+ String(a));  
    }
    else if(minutos > 9 && segundos <= 9){
    lcd.print("Time: " + String(b) +":0"+ String(a));
    }
    else if(minutos > 9 && segundos > 9){
    lcd.print("Time: " + String(b) +":"+ String(a));
    }

    if (digitalRead(start) == HIGH){
      readyGo = true;
      delay(250);
    }

    if (segundos >= 51){
      segundos = 0;
      minutos += 1;
    }

    if (minutos >= 5 && segundos == 10){
      minutos = 0;
      segundos = 0;
    }
  
    if (digitalRead(restar) == HIGH && minutos >= 1 && segundos == 0){
      segundos = 50;
      minutos -= 1;
    }
      delay(200);
  }

  if (readyGo){                                               // empezando temporizador
    digitalWrite(LEDROJO, LOW);   //Codigo de los Led's
    digitalWrite(LEDVERDE, HIGH);
    lcd.setCursor(0, 0);                           //colocar el cursor en en la segunda fila
    motor.write(0);        //Codigo del motor

    if(segundos > 0){
      segundos--;
    }
    else if (minutos > 0){
      minutos--;
      segundos = 59;
    }
    else {
      readyGo = false;
    }
    delay(1000);
  }

  


  if(!readyGo){                                     //primera frase sin estar activado
    lcd.setCursor(0, 0);                           //colocar el cursor en en la segunda fila
    if(tiempoDespues - tiempoAntes>= intervalo){
      for (int j = i; j <= i+15; j++)               // recorrer los primerso 16 caracters en la linea para ser impresos
      {                                             // 
        lcd.print(mensaje2[j]);                     //imprimir los 16 caracteres segun el bucle for
      }


      i++;                                          //incrementar i
      tiempoAntes = tiempoDespues;                  //actualizar el tiempo
    } 
    if (i >= strlen(mensaje2) - 16){
      i = 0;                                        //cuando "i" tenga el mismo largo del mensaje menos 16, hacer "i" igual a 0 para repetir el mensaje
    }
  }

  if(readyGo){                                          //Segunda frase estando activado
    lcd.setCursor(0, 0);                           //colocar el cursor en en la segunda fila
    if(tiempoDespues - tiempoAntes>= intervalo){
      for (int j = i; j <= i+15; j++)               // recorrer los primerso 16 caracters en la linea para ser impresos
      {                                             // 
        lcd.print(mensaje1[j]);                     //imprimir los 16 caracteres segun el bucle for
      }


      i++;                                          //incrementar i
      tiempoAntes = tiempoDespues;                  //actualizar el tiempo
    } 
    if (i >= strlen(mensaje1) - 16){
      i = 0;                                        //cuando "i" tenga el mismo largo del mensaje menos 16, hacer "i" igual a 0 para repetir el mensaje
    }
  }
}
  //las pantallas no soportan mas de 20 caracteres
