///////////////////////////////   SETTING VALUE   ///////////////////////////////////

//Determine the setting value.
//By changing the number in this array you can set sensitivity, threshold and so on.

byte SNARE[6] = {
  100,  //sensitivity (1-100)
  10,   //threshold (1-100)
  10,   //scan time (1-)
  30,   //mask time (1-)
  40,   //note (0-127)
  1     //curve type (0-4)
};

byte TOM[6] = {
  100,  //sensitivity (1-100)
  10,   //threshold (1-100)
  10,   //scan time (1-)
  30,   //mask time(1-)
  71,   //note (0-127)
  1     //curve type(0-4)
};

// Variáveis relacionadas ao chimbal e controlador de chimbal:
int sensibilidade = 100;
int valorSensor;
int nota;
int sensorValuePrev = 1;  // Valor anterior do sensor
int sensorValueCurr;
//int novoValor = 0; // variável de teste na função hihatc()

/////////////////////////////////////////////////////////////////////////////////////

#include <hellodrum.h>

//Using MIDI Library. If you want to use USB-MIDI, comment out the next two lines.
#include <MIDI.h>
MIDI_CREATE_DEFAULT_INSTANCE();

//Uncomment the next two lines for using USB-MIDI with atmega32u4 or Teensy
//#include <USB-MIDI.h>
//USBMIDI_CREATE_DEFAULT_INSTANCE();

//Please name your piezo.
//The piezo named snare is connected to the A2 pin and the piezo named tom is connected to the A3 pin.

// controlador do chimbal (A0)
// piezo do chimbal (A1)
HelloDrum snare(2);
HelloDrum tom(3);
HelloDrum tom2(4);
HelloDrum surdo(5);
HelloDrum bumbo(6);

void setup() {

  MIDI.begin(1);
  // Serial.begin(115200);
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  pinMode(A3, INPUT);
  pinMode(A4, INPUT);
  pinMode(A5, INPUT);
  pinMode(A6, INPUT);

  //Set Curve Type
  snare.setCurve(SNARE[5]);
  tom.setCurve(TOM[5]);
  tom2.setCurve(TOM[5]);
  surdo.setCurve(TOM[5]);
  bumbo.setCurve(TOM[5]);
}

void loop() {
  //Piezo sensing is done in this line. And it is returned as a velocity of 127 stages.
  //For each piezo, one line is required.
  snare.singlePiezo(SNARE[0], SNARE[1], SNARE[2], SNARE[3]);
  tom.singlePiezo(TOM[0], TOM[1], TOM[2], TOM[3]);
  tom2.singlePiezo(TOM[0], TOM[1], TOM[2], TOM[3]);
  surdo.singlePiezo(TOM[0], TOM[1], TOM[2], TOM[3]);
  bumbo.singlePiezo(TOM[0], TOM[1], TOM[2], TOM[3]);

  chimbal(); //execua som do chimbal e do controlador

  //MIDI signals are transmitted with this IF statement.
  //For each piezo, one IF statement is required
  if (snare.hit == true) {
    MIDI.sendNoteOn(38, snare.velocity, 1);  //(note, velocity, channel)
    MIDI.sendNoteOff(38, 0, 1);
  }

  if (tom.hit == true) {
    MIDI.sendNoteOn(71, tom.velocity, 1);  //(note, velocity, channel)
    MIDI.sendNoteOff(71, 0, 1);
  }

  if (tom2.hit == true) {
    MIDI.sendNoteOn(69, tom2.velocity, 1);  //(note, velocity, channel)
    MIDI.sendNoteOff(69, 0, 1);
  }

  if (surdo.hit == true) {
    MIDI.sendNoteOn(67, surdo.velocity, 1);  //(note, velocity, channel)
    MIDI.sendNoteOff(67, 0, 1);
  }

  if (bumbo.hit == true) {
    MIDI.sendNoteOn(36, bumbo.velocity, 1);  //(note, velocity, channel)
    MIDI.sendNoteOff(36, 0, 1);
  }


}