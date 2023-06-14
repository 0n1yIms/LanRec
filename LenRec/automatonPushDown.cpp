#include "automatonPushDown.h"


State AutomatonPD::addState(){
  return states++;
}

SigmaT AutomatonPD::addSigmaTerminal(){
  return terminals++;
}

SigmaN AutomatonPD::addSigmaNoTerminal(){
  return noTerminals++;
}

void AutomatonPD::addTransitions(std::vector<Transition> transitions){
  for (Transition t : transitions){
    if(states >= 0 && t.from <= states && t.to <= states){
      this->transitions.push_back(t);
    }
  }
}


void AutomatonPD::run(char* input){
  State currentState = 0;
  std::vector<Alphabet> stack;
  int i = 0;
  while(input[i] != '\0'){
    for(Transition t : transitions){
      if(t.from == currentState && t.input == input[i] && t.stack == stack.back()){
        currentState = t.to;
        stack.pop_back();
        for(int j = t.output.size() - 1; j >= 0; j--){
          stack.push_back(t.output[j]);
        }
        break;
      }
    }
    i++;
  }
  // if(currentState == 1 && stack.back() == _epsilon){
    // std::cout << "Cadena aceptada" << std::endl;
  // }else{
    // std::cout << "Cadena no aceptada" << std::endl;
  // }
}







