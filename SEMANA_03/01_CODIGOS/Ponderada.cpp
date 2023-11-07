//Aqui defini os pinos para os botões e o buzzer
#define YELLOW_BUTTON 14
#define RED_BUTTON 26
#define GREEN_BUTTON 33
#define BLUE_BUTTON 25
#define RESET_BUTTON 12
#define BUZZER 18

//Aqui defini os pinos para os LEDs
#define GREEN_LED 0
#define BLUE_LED 4
#define RED_LED 16
#define YELLOW_LED 19

//Aqui declarei alguns arrays para:
int sequence[100]; // Armazenar a sequência do jogo
int playerSequence[100]; //Armazenar a sequência do jogador
int sequenceLength = 0; // O comprimento da sequência atual
int playerTurn = false; // Pra rastrear de quem é a vez de jogar (jogador ou jogo)
int currentStep = 0; // Para saber o passo atual

void setup() { //Inicio do programa e configuração de comunicação serial
  Serial.begin(9600);
  pinMode(BUZZER, OUTPUT);
  pinMode(YELLOW_BUTTON, INPUT);  
  pinMode(RED_BUTTON, INPUT);  
  pinMode(GREEN_BUTTON, INPUT);  
  pinMode(BLUE_BUTTON, INPUT);  
  pinMode(RESET_BUTTON, INPUT);  
  pinMode(BLUE_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);
  pinMode(YELLOW_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
}

void loop() {
  if (digitalRead(RESET_BUTTON)) { // Aqui verifica se o botão de reset foi pressionado
    resetGame();
  }

  if (!playerTurn) { // Aqui verifica se não é a vez do jogador
    addToSequence(); // Se não for  vez do jogador, vai gerar um novo movimento aleatório adicionando-o à sequência do jogo
    playSequence(); // Aqui reproduz a sequência de movimentos gerada pelo jogo depois de adicionar um novo movimento
    playerTurn = true; // Aqui é a vez do jogador
    currentStep = 0; // Jogador volta a estaca zero para tentar reproduzir a sequência de movimentos do jogo novamente
  }

  if (playerTurn) { // Aqui verifica se o jogador pressionou os botões certos de acordo com a sequência do jogo
    checkPlayerInput();
  }
}

void resetGame() { // Aqui é usado quando o botão 'reset' é pressionado
  sequenceLength = 0; // Restaurando a sequência de movimentos, ou seja, voltando ao início e colocando como comprimento de sequência o 0.
  playerTurn = false; // Aqui o jogo passa a voltar a ser jogado pelo jogo e não pelo jogador
}

void addToSequence() { // Aqui é usado para dar uma novo movimento para a sequência ao jogo
  int nextMove = random(1, 5); // Aqui vai gerar um número aleatório de 1 a 4
  sequence[sequenceLength] = nextMove; // Aqui vamos adicionar o movimento gerado à sequência do jogo no índice indicado por 'sequenceLength'
  sequenceLength++; // Aqui a variável 'sequenceLength' vai apontar para o próximo espaço vazio na sequência, onde o próximo movimento será adicionado
}

void playSequence() { // Aqui vai ser usado para reproduzir a sequência de movimentos gerada pelo jogo
  for (int i = 0; i < sequenceLength; i++) { // Loop for vai ser usado para percorrer a sequência de movimentos até o comprimento atual da sequência
    int move = sequence[i]; // Aqui temos o movimento atual da sequência e armazenamos em 'move'
    lightUp(move); // Aqui a função vai ser chamada para acender o LED e tocar o som correspondente ao movimento atual
    delay(1000); 
    turnOffLights(); // Aqui a função vai ser chamada para apagar o LED
    delay(500); 
  }
}

void lightUp(int move) { // Aqui essa função vai ser chamada pela função 'playSequence()' para acender um LED e tocar som com base no movimento atual
  switch (move) { // Aqui vai determinar o que fazer com base no valor de 'move', que é o movimento atual
    case 1:
      digitalWrite(YELLOW_LED, HIGH);
      tone(BUZZER, 262, 500); // Se 'move' for igual a 1, o LED amarelo vai acender e tocar um som
      break;
    case 2:
      digitalWrite(RED_LED, HIGH);
      tone(BUZZER, 294, 500); // Se 'move' for igual a 2, o LED vermelho vai acender e tocar um som
      break;
    case 3:
      digitalWrite(GREEN_LED, HIGH);
      tone(BUZZER, 330, 500); // Se 'move' for igual a 3, o LED verde vai acender e tocar um som
      break;
    case 4:
      digitalWrite(BLUE_LED, HIGH);
      tone(BUZZER, 349, 500); // Se 'move' for igual a 4, o LED azul vai acender e tocar um som
      break;
  }
}

void turnOffLights() { // Aqui vai apagar todos os LEDs e também parar de tocar os sons
  digitalWrite(YELLOW_LED, LOW);
  digitalWrite(RED_LED, LOW);
  digitalWrite(GREEN_LED, LOW);
  digitalWrite(BLUE_LED, LOW);
  noTone(BUZZER);
}

void checkPlayerInput() { // Aqui a função vai verificar se o jogador apertou os botões correspondentes às cores da sequência do jogo
  if (digitalRead(YELLOW_BUTTON)) { // Aqui verifica se o botão amarelo foi pressionado pelo jogador
    playerSequence[currentStep] = 1; // Se o botão amarelo foi pressionado, vamos atribuir o valor 1 na sequência do jogador na posição 'currentStep'
    lightUp(1); // LED amarelo acende e toca um som
    delay(500); 
    turnOffLights(); // LED amarelo desliga e para de tocar o som
    currentStep++; // A variável 'currentStep' vai acompanhar o progresso do jogador na sequência
  }
  if (digitalRead(RED_BUTTON)) { // Aqui verifica se o botão vermelho foi pressionado pelo jogador
    playerSequence[currentStep] = 2; // // Se o botão vermelho foi pressionado, vamos atribuir o valor 2 na sequência do jogador na posição 'currentStep'
    lightUp(2); // LED vermelho acende e toca um som
    delay(500);
    turnOffLights(); // LED vermelho desliga e para de tocar o som
    currentStep++; // A variável 'currentStep' vai acompanhar o progresso do jogador na sequência
  }
  if (digitalRead(GREEN_BUTTON)) { // Aqui verifica se o botão verde foi pressionado pelo jogador
    playerSequence[currentStep] = 3; // // Se o botão verde foi pressionado, vamos atribuir o valor 3 na sequência do jogador na posição 'currentStep'
    lightUp(3); // LED verde acende e toca um som
    delay(500);
    turnOffLights(); // LED verde desliga e para de tocar o som
    currentStep++; // A variável 'currentStep' vai acompanhar o progresso do jogador na sequência
  }
  if (digitalRead(BLUE_BUTTON)) { // Aqui verifica se o botão azul foi pressionado pelo jogador
    playerSequence[currentStep] = 4; // // Se o botão azul foi pressionado, vamos atribuir o valor 4 na sequência do jogador na posição 'currentStep'
    lightUp(4); // LED azul acende e toca um som
    delay(500);
    turnOffLights(); // LED azul desliga e para de tocar o som
    currentStep++; // A variável 'currentStep' vai acompanhar o progresso do jogador na sequência
  }

  if (currentStep == sequenceLength) { // Aqui vai verificar se o jogador completou a sequência da rodada atual
    checkRound(); // Aqui vai verificar se o jogador acertou a sequência e fornecer feedback com base em seu desempenho
  }
}

void checkRound() { // Aqui a função vai  verificar se o jogador acertou ou errou a sequência e fornecer feedback adequado
  bool correct = true; // Aqui vai determinar se o jogador acertou a sequência
  for (int i = 0; i < sequenceLength; i++) { // Loop for vai percorrer a sequência de movimentos gerada pelo jogo e a sequência do jogador
    if (playerSequence[i] != sequence[i]) { // Aqui vai comparar os movimentos na mesma posição nas duas sequências, se for diferente significa que o jogador errou a sequência
      correct = false;
      break; // Aqui sai do loop
    }
  }

  if (correct) { // Se o jogador acertou a sequência
    tone(BUZZER, 523, 1000); // O buzzer vai botar um som para feedback de acerto
  } else { // Se o jogador errou a sequência
    tone(BUZZER, 262, 1000); // O buzzer vai botar um som para feedback de erro
    // Aqui todos os LEDs vão acender se o jogador errar
    digitalWrite(YELLOW_LED, HIGH);
    digitalWrite(RED_LED, HIGH);
    digitalWrite(GREEN_LED, HIGH);
    digitalWrite(BLUE_LED, HIGH);
    delay(1000); 
    turnOffLights(); // LEDs vão se apagar
    resetGame(); // O jogo vai voltar a estaca zero
  }

  playerTurn = false; // Aqui vai ser a vez do jogo de jogar e não do jogador
}