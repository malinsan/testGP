#include "HelperFunctions.h"
#include <stdio.h>

bool isValueInArray(int val, int array[], int size){
  for(int i = 0; i < size; i++){
    if(array[i] == val){
      return true;
    }
  }
  return false;
}

void getRegChar(int reg, char result[]){
  switch (reg) {
    case 0:
      sprintf(result, "a =");
      break;
    case 1:
      sprintf(result, "b =");
      break;
    case 2:
      sprintf(result, "c =");
      break;
    default:
      break;
  }
}

void getOperandChar(int op, char result[]){
  switch (op) {
    case 0:
      sprintf(result, "%s a", result);
      break;
    case 1:
      sprintf(result, "%s b", result);
      break;
    case 2:
      sprintf(result, "%s c", result);
      break;
    case 3:
      sprintf(result, "%s -1", result);
      break;
    case 4:
      sprintf(result, "%s 0", result);
      break;
    case 5:
      sprintf(result, "%s 1", result);
      break;
    default:
      break;
  }
}

void getOperationChar(int operation, char result[]){
  switch (operation) {
    case 0:
      sprintf(result, "%s +", result);
      break;
    case 1:
      sprintf(result, "%s -", result);
      break;
    case 2:
      sprintf(result, "%s *", result);
      break;
    default:
      break;
  }
}
