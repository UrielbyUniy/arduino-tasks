#include <Keypad.h>
#include <Servo.h>
#include <LiquidCrystal.h>

const byte FILAS = 2;  //Codigo del teclado
const byte COLUMNAS = 2;
char keys[FILAS][COLUMNAS] = { 
  {'1','A'},
  {'0','B'},
};

byte pinesFilas[FILAS] = {5,4};
byte pinesColumnas[COLUMNAS] = {3,2};

Keypad teclado = Keypad(makeKeymap(keys), pinesFilas, pinesColumnas, FILAS, COLUMNAS);

char TECLA;
char CLAVE[7];
char CLAVE_MAESTRA[7] = "111111";
byte INDICE = 0;

int LEDVERDE = 13;  //Codigo de los Led's
int LEDROJO = 12;

Servo motor;    //Codigo del motor
int posicion = 0;
int PINSERVO = 11;

int TIEMPO;  //Codigo de tiempo
int POT = 0;

LiquidCrystal lcd(7,6,5,4,3,2);   //Codigo del LCD

void setup()
{
 Serial.begin(9600);
 pinMode(LEDVERDE, OUTPUT);    //Codigo de los Led's
 pinMode(LEDROJO, OUTPUT);
 motor.attach (PINSERVO);
}

void loop(){
  digitalWrite(LEDROJO, HIGH);   //Codigo de los Led's
  digitalWrite(LEDVERDE, LOW);
  motor.write(90);              //Codigo del motor
  
  TIEMPO = analogRead(POT) * 15; //Codigo del tiempo

  TECLA = teclado.getKey();       //Codigo del teclado
  if (TECLA) {
    CLAVE[INDICE] = TECLA;
    INDICE++;
    Serial.print(TECLA);
  }
    if (INDICE == 6) 
    {
      if(!strcmp(CLAVE, CLAVE_MAESTRA)) {
      digitalWrite(LEDVERDE, HIGH);     //Codigo de los Led's
      digitalWrite(LEDROJO, LOW);
      motor.write(0);                   //Codigo del motor
    
    }
      else {
      digitalWrite(LEDVERDE, LOW);
      digitalWrite(LEDROJO, HIGH);
    }
      delay(1000);
      INDICE = 0;
    }
}
  
