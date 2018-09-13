#include "HelperFunctions.h"

bool isValueInArray(int val, int array[], int size){
  for(int i = 0; i < size; i++){
    if(array[i] == val){
      return true;
    }
  }
  return false;
}
