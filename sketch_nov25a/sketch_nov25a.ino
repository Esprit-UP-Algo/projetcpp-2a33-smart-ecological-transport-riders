#define PIN_LED1 11 //le numéro de la broche sur laquelle la lampe 2  est branchée
#define PIN_LED2 13 // Le numéro de la broche sur laquelle la lampe 1 
#include <Keypad.h> //kerborad
#include <Servo.h>

//(par défaut intégrée dans la carte) est branchée 
#define pas  20 // incrément de l'intensité
char data; // variable contenant le caractère lu
int x; // variable contenant l'intensité de la deuxième lampe
int ID = 0;
Servo servo;



const byte ROWS = 4; //four rows
const byte COLS = 4; //four columns
//define the cymbols on the buttons of the keypads
char hexaKeys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte rowPins[ROWS] = {9, 8, 7, 6}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {5, 4, 3, 2}; //connect to the column pinouts of the keypad

//initialize an instance of class NewKeypad
Keypad customKeypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 




void setup() {
  // Configure la broche 11 sur laquelle est reliée notre LED  en sortie
  pinMode(PIN_LED1,OUTPUT);
//La LED reliée à la broche 11 est intialisé à l'état LOW
  digitalWrite(PIN_LED2,LOW);
  // Configure la broche 13 sur laquelle est reliée notre LED  en sortie
  pinMode(PIN_LED2,OUTPUT);
//La LED reliée à la broche 13 est intialisé à l'état LOW
pinMode(PIN_LED1,OUTPUT);
  analogWrite(PIN_LED1, 0);
  Serial.begin(9600); //Permet d'initialiser le moniteur série à 9600 bauds 
  x=0; // Intialiser l'intensité de la deuxième lampe 

servo.attach(12);
servo.write(50);
  delay(2000);

}



void loop() {
  
  if (Serial.available()){     
    //Si un message a été reçu  faire ceci
     data=Serial.read();  
     // controler la lampe 1 reliée à la broche 13
     //récuperer le caractère reçu
     if(data=='1') //si le caractère lu est égale à 1
    {
      digitalWrite(PIN_LED2,HIGH); // alumer la lampe 
      Serial.write('1'); //envoyer le nouvel état de la lampe 
      servo.write(50);
      delay(2500);
      servo.write(0);
      delay(2500);
      servo.write(50); 
      digitalWrite(PIN_LED2,LOW);
     }  
     else if(data=='0') //si le caractère lu est égale à 0

     {
        digitalWrite(PIN_LED2,LOW); //éteindre la lampe
        Serial.write('0'); //envoyer le nouvel état de la lampe
     
     }   
     // Régler l'intensité de la luminosité de la deuxième lampe branchée sur la broche 11
     else if(data=='2') //si le caractère reçu est égale à 2
     {
      digitalWrite(PIN_LED1,HIGH); // alumer la lampe 
      Serial.write('2'); //envoyer le nouvel état de la lampe 
      delay(2500);
        digitalWrite(PIN_LED1,LOW);
     }  
     else if(data=='3')
     {
        if((x>pas)) // si l'intesité est encore supérieur au pas 
         x=x-pas; // décreménter l'intensité 
        else 
         x=0;
         
        analogWrite(PIN_LED1,x);
     
     } 
  }



  char customKey = customKeypad.getKey();
  
  if (customKey){
    Serial.println(customKey);
  ID = (ID * 10) + (customKey - '0');
Serial.write((byte *)&ID, sizeof(ID));
  }


  
}
