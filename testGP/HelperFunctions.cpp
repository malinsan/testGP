#include "HelperFunctions.h"

bool isValueInArray(int val, int array[], int size){
  for(int i = 0; i < size; i++){
    if(array[i] == val){
      return true;
    }
  }
  return false;
}

char getRegChar(int reg){
  char result;
  switch (reg) {
    case 0:
      result = 'a';
      break;
    case 1:
      result = 'b';
      break;
    case 2:
      result = 'c';
      break;
    default:
      break;
  }
  return result;
}

char getOperandChar(int op){
  char result;
  switch (op) {
    case 0:
      result = 'a';
      break;
    case 1:
      result = 'b';
      break;
    case 2:
      result = 'c';
      break;
    case 3:
      result = '-1';
      break;
    case 4:
      result = '0';
      break;
    case 5:
      result = '1';
      break;
    default:
      break;
  }
  return result;
}

char getOperationChar(int operation){
  char result;
  switch (operation) {
    case 0:
      result = '+';
      break;
    case 1:
      result = '-';
      break;
    case 2:
      result = '*';
      break;
    default:
      break;
  }
}
