///////////////////////////////   SETTING VALUE   ///////////////////////////////////

//Determine the setting value.
//By changing the number in this array you can set sensitivity, threshold and so on.

byte pad[6] = {
  100,  //sensitivity (1-100)
  10,   //threshold (1-100)
  10,   //scan time (1-)
  30,   //mask time (1-)
  0,    //note (0-127)
  1     //curve type (0-4)
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
#include <MIDI.h>
MIDI_CREATE_DEFAULT_INSTANCE();

//Please name your piezo.
//The piezo named snare is connected to the A2 pin and the piezo named tom is connected to the A3 pin.
// controlador do chimbal (A0)
// piezo do chimbal (A1)
HelloDrum caixa(2);
HelloDrum aro(3);
HelloDrum bumbo(4);
HelloDrum tom(5);
HelloDrum tom2(6);
HelloDrum surdo(7);

void setup() {

  MIDI.begin(1);
  Serial.begin(115200);
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  pinMode(A3, INPUT);
  pinMode(A4, INPUT);
  pinMode(A5, INPUT);
  pinMode(A6, INPUT);
  pinMode(A7, INPUT);

  //Set Curve Type
  caixa.setCurve(pad[5]);
  aro.setCurve(pad[5]);
  bumbo.setCurve(pad[5]);
  tom.setCurve(pad[5]);
  tom2.setCurve(pad[5]);
  surdo.setCurve(pad[5]);
}

void loop() {
  //Piezo sensing is done in this line. And it is returned as a velocity of 127 stages.
  //For each piezo, one line is required.
  caixa.singlePiezo(pad[0], pad[1], pad[2], pad[3]);
  aro.singlePiezo(pad[0], pad[1], pad[2], pad[3]);
  bumbo.singlePiezo(pad[0], pad[1], pad[2], pad[3]);
  tom.singlePiezo(pad[0], pad[1], pad[2], pad[3]);
  tom2.singlePiezo(pad[0], pad[1], pad[2], pad[3]);
  surdo.singlePiezo(pad[0], pad[1], pad[2], pad[3]);

  chimbal();  //executa som do chimbal e do controlador

  //MIDI signals are transmitted with this IF statement.
  //For each piezo, one IF statement is required
  if (caixa.hit == true) {
    MIDI.sendNoteOn(38, caixa.velocity, 1);  //(note, velocity, channel)
    MIDI.sendNoteOff(38, 0, 1);
  }

  if (aro.hit == true) {
    MIDI.sendNoteOn(42, caixa.velocity, 1);  //(note, velocity, channel)
    MIDI.sendNoteOff(38, 0, 1);
  }

  if (surdo.hit == true) {
    MIDI.sendNoteOn(67, surdo.velocity, 1);  //(note, velocity, channel)
    MIDI.sendNoteOff(67, 0, 1);
  }

  if (tom.hit == true) {
    MIDI.sendNoteOn(71, tom.velocity, 1);  //(note, velocity, channel)
    MIDI.sendNoteOff(71, 0, 1);
  }

  if (tom2.hit == true) {
    MIDI.sendNoteOn(69, tom2.velocity, 1);  //(note, velocity, channel)
    MIDI.sendNoteOff(69, 0, 1);
  }

  if (bumbo.hit == true) {
    MIDI.sendNoteOn(36, bumbo.velocity, 1);  //(note, velocity, channel)
    MIDI.sendNoteOff(36, 0, 1);
  }
}
