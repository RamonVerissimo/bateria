int estado(int valor) {
  if (valor >= 900) {
    return 1;  // totalmente fechado
  } else if (valor < 900 && valor >= 700) {
    return 2;  // quase fechado
  } else if (valor < 700 && valor >= 500) {
    return 3;  // quase aberto
  } else if (valor < 500 && valor >= 150) {
    return 4;  // quase quase aberto
  } else if ( valor < 150){
    return 5; // totalmente aberto
  } else
  return 0;  // Valor de fallback (normalmente não vai chagar nessa condição)
}

void hihatc() {
  nota = analogRead(A0);
  sensorValueCurr = estado(nota);  // recebe 1, 2, 3, 4 ou 5.

  if (sensorValuePrev == 2 && sensorValueCurr == 1) {
    // novoValor = analogRead(A0);
    // novoValor = novoValor / 8;
    // MIDI.sendControlChange(4, novoValor, 1);
    //if (sensorValueCurr == 1) {
    MIDI.sendNoteOn(48, 127, 1);  // 48 --> nota fechamento do cimbal
    MIDI.sendNoteOff(48, 0, 1);
    delay(10);  // Pequeno delay para permitir que a mensagem NoteOn seja processada
    //}
  }

  sensorValuePrev = sensorValueCurr;  // Atualizar valor anterior
}

void chimbal() {
  // Quando o controlador do chimbal estiver funcionando, remover as duas linhas abaixo
  // e descomentar os demais ifs
  // MIDI.sendNoteOn(50, hihat.velocity, 1);  //(note, velocity, channel)
  // MIDI.sendNoteOff(50, 0, 1);


  nota = analogRead(A0);  // O controlador do chimbal deve estar ligado na porta A0

  switch (estado(nota)) {
    case 1:
      MIDI.sendNoteOn(50, hihat.velocity, 1);  //(note, velocity, channel)
      MIDI.sendNoteOff(50, 0, 1);
      // Serial.println("totalmente fechado"); ajustar os valores quando o pedal for montado.
      break;

    case 2:
      MIDI.sendNoteOn(52, hihat.velocity, 1);  //(note, velocity, channel)
      MIDI.sendNoteOff(52, 0, 1);
      // Serial.println("quase fechado");
      break;

    case 3:
      MIDI.sendNoteOn(54, hihat.velocity, 1);  //(note, velocity, channel)
      MIDI.sendNoteOff(54, 0, 1);
      // Serial.println("quase aberto");
      break;

    case 4:
      MIDI.sendNoteOn(56, hihat.velocity, 1);  //(note, velocity, channel)
      MIDI.sendNoteOff(56, 0, 1);
      // Serial.println("totalmente aberto");
      break;

    case 5:
      MIDI.sendNoteOn(57, hihat.velocity, 1);  //(note, velocity, channel)
      MIDI.sendNoteOff(57, 0, 1);
      // Serial.println("totalmente aberto");
      break;
  }
}
