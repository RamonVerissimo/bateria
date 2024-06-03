int estado(int valor) {
  if (valor >= 900) {
    return 1;  // totalmente fechado
  } else if (valor < 900 && valor >= 400) {
    return 2;  // quase fechado
  } else if (valor < 400 && valor >= 200) {
    return 3;  // quase aberto
  } else if (valor < 200) {
    return 4;  // totalmente aberto
  }
  return 1;  // Valor de fallback (normalmente não chega nessa condição)
}

void fechamento() {

  sensorValueCurr = estado(nota);  // recebe 1, 2, 3 ou 4.

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

  valorSensor = analogRead(A1);  // Piezo do chimbal deve estar conectado na entrada A1.

  if (valorSensor > sensibilidade) {
    
    nota = analogRead(A0);
    valorSensor = valorSensor / 8;  //Limita o valor lido até 127

    switch (estado(nota)) {
      case 1:
        Serial.println(valorSensor);
        MIDI.sendNoteOn(50, valorSensor, 1);
        // delay(5);  // Pequeno delay para permitir que a mensagem NoteOn seja processada
        MIDI.sendNoteOff(50, 0, 1);
        delay(10);
        // Serial.println("totalmente fechado"); ajustar os valores quando o pedal for montado.
        break;

      case 2:
        MIDI.sendNoteOn(54, valorSensor, 1);
        // delay(5);
        MIDI.sendNoteOff(54, 0, 1);
        delay(10);
        // Serial.println("quase fechado");
        break;

      case 3:
        MIDI.sendNoteOn(55, valorSensor, 1);
        // delay(5);
        MIDI.sendNoteOff(55, 0, 1);
        delay(10);
        // Serial.println("quase aberto");
        break;

      case 4:
        MIDI.sendNoteOn(57, valorSensor, 1);
        // delay(5);
        MIDI.sendNoteOff(57, 0, 1);
        delay(10);
        // Serial.println("totalmente aberto");
        break;
    }
  }

  fechamento();  // função para detectar fechamento do chimbal
}