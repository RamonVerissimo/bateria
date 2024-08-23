///////////////////////////////   SETTING VALUE   ///////////////////////////////////

//Determine the setting value.
//By changing the number in this array you can set sensitivity, threshold and so on.

// Curva:
// 0 - linear
// 1 - exponencial 1
// 2 - exponencial 2
// 3 - Logarítmica 1
// 4 - Logarítmica 2

byte PAD[6] = {
  100,  //sensitivity (1-100)
  10,   //threshold (1-100)
  10,   //scan time (1-)
  20,   //mask time (1-) estava 30 //Aumentar o mask time caso o pad/prato esteja sendo reacionado com a vibração da peça.
  40,   //note (0-127)
  0     //curve type (0-4)
};

// Modificar os valore de threshold, scan time e mask time para diminuir a sensibilidade e toque duplo
byte RIDE[6] = {
  100,  //sensitivity (1-100)  //alterar para teste
  30,   //threshold (1-100)  //alterar para teste
  10,   //scan time (1-)  //alterar para teste
  60,   //mask time(1-)  //alterar para teste
  71,   //note (0-127)
  0     //curve type(0-4)
};

// Variáveis relacionadas ao chimbal e controlador de chimbal:
int nota;
int sensorValuePrev = 1;  // Valor anterior do sensor
int sensorValueCurr;
int choke;
int pinck = 40;

/////////////////////////////////////////////////////////////////////////////////////

#include <hellodrum.h>

//Using MIDI Library. If you want to use USB-MIDI, comment out the next two lines.
#include <MIDI.h>
MIDI_CREATE_DEFAULT_INSTANCE();

//Nomeação dos piezos:

// controlador do chimbal deve estar ligado na porta A0
HelloDrum hihat(1);
HelloDrum snare(2);
HelloDrum aro(3);
HelloDrum bumbo(4);
HelloDrum tom(5);
HelloDrum tom2(6);
HelloDrum surdo(7);
HelloDrum pataque1(8);
HelloDrum splash(9);
HelloDrum pataque2(10);
HelloDrum condCorpo(11);
HelloDrum condCupula(12);

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
  pinMode(A8, INPUT);
  pinMode(A9, INPUT);
  pinMode(A10, INPUT);
  pinMode(A11, INPUT);
  pinMode(A12, INPUT);
  pinMode(pinck, INPUT_PULLUP); //chave do choke do prato

  //Set Curve Type
  hihat.setCurve(PAD[5]);
  snare.setCurve(PAD[5]);
  aro.setCurve(PAD[5]);
  bumbo.setCurve(PAD[5]);  // Caso o som do bumbo não esteja bom, lterar de PAD[5] para 1 (curva exponencial)
  tom.setCurve(PAD[5]);
  tom2.setCurve(PAD[5]);
  surdo.setCurve(PAD[5]);
  pataque1.setCurve(PAD[5]);
  splash.setCurve(PAD[5]);
  pataque2.setCurve(PAD[5]);
  condCorpo.setCurve(PAD[5]);
  condCupula.setCurve(PAD[5]);
}
// 100,  //sensitivity (1-100)
// 10,   //threshold (1-100)
// 10,   //scan time (1-)
// 30,   //mask time (1-) //Aumentar o mask time caso o pad/prato esteja sendo reacionado com a vibração da peça.
// 40,   //note (0-127)
// 0     //curve type (0-4)
void loop() {
  //Piezo sensing is done in this line. And it is returned as a velocity of 127 stages.
  //For each piezo, one line is required.
  hihat.singlePiezo(PAD[0], 20, 6, 35);  //(byte sens, byte thre, byte scanTime, byte maskTime)
  snare.singlePiezo(PAD[0], PAD[1], 6, 10);
  aro.singlePiezo(PAD[0], 12, PAD[2], PAD[3]);  // 90 é o valor para que o piezo não fique tão sensível
  bumbo.singlePiezo(PAD[0], PAD[1], 5, 100);
  tom.singlePiezo(PAD[0], PAD[1], 6, 7);
  tom2.singlePiezo(PAD[0], PAD[1], 6, 7);
  surdo.singlePiezo(PAD[0], PAD[1], 6, 7);
  pataque1.singlePiezo(PAD[0], PAD[1], PAD[2], PAD[3]);
  splash.singlePiezo(PAD[0], 60, PAD[2], PAD[3]);
  pataque2.singlePiezo(PAD[0], PAD[1], PAD[2], PAD[3]);
  condCorpo.singlePiezo(RIDE[0], RIDE[1], RIDE[2], RIDE[3]);
  condCupula.singlePiezo(RIDE[0], RIDE[1], RIDE[2], RIDE[3]);

  //MIDI signals are transmitted with this IF statement.
  //For each piezo, one IF statement is required

  if (hihat.hit == true) {
    chimbal();  //executa som do chimbal
  }

  hihatc();  // função para detectar fechamento do chimbal

  if (snare.hit == true) {
    MIDI.sendNoteOn(38, snare.velocity, 1);  //(note, velocity, channel)
    MIDI.sendNoteOff(38, 0, 1);
  }

  if (aro.hit == true) {
    MIDI.sendNoteOn(42, 100, 1);  //(note, velocity, channel)
    MIDI.sendNoteOff(42, 0, 1);
  }

  if (bumbo.hit == true) {
    MIDI.sendNoteOn(36, bumbo.velocity, 1);  //(note, velocity, channel)
    MIDI.sendNoteOff(36, 0, 1);
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

  if (pataque1.hit == true) {
    MIDI.sendNoteOn(79, pataque1.velocity, 1);  //(note, velocity, channel)
    MIDI.sendNoteOff(79, 0, 1);
  }

  choke = digitalRead(pinck);
  if (choke == LOW){
    MIDI.sendNoteOn(80, pataque1.velocity, 1);  //(note, velocity, channel)
    MIDI.sendNoteOff(80, 0, 1);
  }

  if (splash.hit == true) {
    MIDI.sendNoteOn(91, splash.velocity, 1);  //(note, velocity, channel)
    MIDI.sendNoteOff(91, 0, 1);
  }

  if (pataque2.hit == true) {
    MIDI.sendNoteOn(77, pataque2.velocity, 1);  //(note, velocity, channel)
    MIDI.sendNoteOff(77, 0, 1);
  }

  if (condCorpo.hit == true) {
    MIDI.sendNoteOn(60, condCorpo.velocity, 1);  //(note, velocity, channel)
    MIDI.sendNoteOff(60, 0, 1);
  }

  if (condCupula.hit == true) {
    MIDI.sendNoteOn(61, condCupula.velocity, 1);  //(note, velocity, channel)
    MIDI.sendNoteOff(61, 0, 1);
  }
}
