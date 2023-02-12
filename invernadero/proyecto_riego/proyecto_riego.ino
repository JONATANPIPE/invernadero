#include <LiquidCrystal.h>    // PARA UTLIZAR LIBRERIA DE LA LCD
LiquidCrystal lcd(13, 12, 11, 10, 9, 8); // Asignamos lospines de salida a la lcd que tomamos en cuenta al conectar el arduino con la lcd
int F1 = 3; int F2 = 2; // declaramos los pines dentrada del contador 
int E4 = 4; int E2 = 6; int E1 = 7; int E3 = 5; // declaramos lo pines de entrada del contador
int motor = 1; int PR = 0; int SR = 0; int TR = 0; // declaramos unas variables que necesitamos para ejecutar el programa 
int motor2 = 0; int i; double valor = 0; double sensor = 0; int analog = A0;  // declaramos otras variables necesaria he incluida la del puerto analogo
void setup()
{ lcd.begin(16, 2);   // inicializamos la lcd
  pinMode(F1, INPUT);   pinMode(F2, INPUT);  // decimos que los pines conectados con los contadores son entradas
  pinMode(E4, INPUT); pinMode(E2, INPUT); pinMode(E1, INPUT); pinMode(E3, INPUT);// decimos que los pines conectados con los contadores son entradas
  pinMode(motor, OUTPUT);  pinMode(motor2, OUTPUT); // decimos que lo pines que conectamos a las bobinas son salidas
  lcd.setCursor(0, 0); // colocamos el cursor en la columna 0 fila 0
  lcd.print("RIEGO DESACTIVADO"); // aqui imprimimos el mensaje que el riego no esta activado
}
void encendido() // cree una funcion que se va ejecutar cadavez que la llamemos en el void lopp, esta funcion lo que hace es activar las bobinas para que se active el motobomba del riego sin fertilizante
{ lcd.clear(); // limpiamos la lcd
  lcd.setCursor(0, 0); // colocamos el cursor en la columna 0 fila 0
  lcd.print("RIEGO ACTIVADO"); // aqui imprimimos el mensaje que el riego esta activado
  lcd.setCursor(0, 1);  // colocamos el cursor en la columna 0 fila 1
  lcd.print("SIN FERTILIZANTE");  // aqui imprimimos el mensaje que el sin fertilizante
  digitalWrite(motor, HIGH);  // aqui activamos las bobinas
  delay(5000);                // retardo 5 segundos
  digitalWrite(motor, LOW);   // aqui desactivamos las bobinas
  lcd.clear();                //aqui limpiamos la lcd 
  lcd.setCursor(0, 0);        // colocamos el cursor en la columna 0 fila 0
  lcd.print("RIEGO DESACTIVADO"); // aqui imprimimos el mensaje que el riego no esta activado
}
void encendido2() // cree una funcion que se va ejecutar cadavez que la llamemos en el void lopp, esta funcion lo que hace es activar las bobinas para que se active el motobomba del riego con fertilizante
{ lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("RIEGO ACTIVADO");
  lcd.setCursor(0, 1);
  lcd.print("CON FERTILIZANTE");
  digitalWrite(motor2, HIGH);  // aqui activamos la otra bobina
  delay(5000);
  lcd.clear();
  digitalWrite(motor2, LOW);   // aqui desactivamios la otra bobina
  lcd.setCursor(0, 0);
  lcd.print("RIEGO DESACTIVADO");
   
}

void loop()
{ valor = analogRead(analog); // valor en el que esta el puerto analogo
  sensor = (valor * 5) / 1024; // conversion para saber en voltaje esta el sensor 
  if (sensor > 4)  // si es sensor esta mayor a 4 voltios i va a valor 1
  { i = 1;
  }
  if (sensor == 0 && i > 0) // si el sensor es igual a cero y i es mayor a 1 entra y llama a la funcion 2
  { encendido2(); // llamo la funcion del encendido  para el riego con fertilizante 
    i = 0;        // actualizo i para cuando vuelva a llover
  }
  if (digitalRead(E2) == HIGH &&digitalRead(E3) == HIGH &&digitalRead(F1) == HIGH &&PR == 0) // el contador esta activo y no se haya activado el riego en el dia entre a la condicion 
  { encendido();   // llamamos la funcion encendido sin fertilizante 
    PR++;          // aunmetamos PR para que no vuelva a entrar en el condicional asi E1 este activada 
  } else if ( digitalRead(F2) == HIGH && digitalRead(E2) == HIGH && SR == 0)
  { encendido();
    SR++;
  } else if (digitalRead(F1) == HIGH && digitalRead(E1) == HIGH && digitalRead(E4) == HIGH && TR == 0)
  { encendido();
    TR++;
  }
  if (digitalRead(F1) == LOW && digitalRead(F2) == LOW && digitalRead(E4) == LOW  && digitalRead(E2) == LOW && digitalRead(E1) == LOW && digitalRead(E3) == LOW )
  { PR = 0;  SR = 0; TR = 0;
  }
}
