#include "HelperFunctions.h"
#include <stdio.h>


void makeCopyOfDataRow(char dataRow[], int length, char copyRow[]){
  int i = 0;
  for(i = 0; i <= length; i++){
    copyRow[i] = dataRow[i];
  }
  copyRow[i] = '\0';
}

int convertASCIIToFloats(char data_row[], float array[], int size){
  if (!data_row){
    return -1;
  }

  if (size < 4){
    return -1;
  }

  const char COMMA[2] = ",";
  char tmp[size];
  makeCopyOfDataRow(data_row, size, tmp);
  char token[10];
  bool tokenizeBuffer = myStrtok(true,tmp,COMMA,token);


  int var = 0;
  while( tokenizeBuffer ) {

    if (var >= 20) // 20 = elements in row
    {
      break;
    }
    float data_value = (float)stof(token);
    array[var] = data_value;

    var++;
    tokenizeBuffer = myStrtok(false,tmp,COMMA,token);
  }

  // if first element is empty
  if (array[0] == 0)
  {
    return -1;
  }

  return var;
}


/*
* Turns a char array into a float number
*/
float stof(char s []){
  float rez = 0, fact = 1;
  int pos = 0;
  if (s[pos] == '-'){
    pos++;
    fact = -1;
  }
  for (bool point_seen = false; s[pos] != '\0'; pos++){
    if (s[pos] == '.'){
      point_seen = true;
      continue;
    }
    int d = s[pos] - '0';
    if (d >= 0 && d <= 9){
      if (point_seen){
        fact /= 10.0f;
      }
      rez = rez * 10.0f + (float)d;
    }
  }
  return rez * fact;

}



/*
* Malins little version of strtok
* returns false when the end of the buffer is reached, otherwise returns true
*/
bool myStrtok(bool firstRun, char buffer [], const char delimiter [], char returnString []){
  static int bufferPosition;
  if(firstRun){
    bufferPosition = 0;
  }
  if(buffer[bufferPosition] == '\0'){ //when the end of buffer is reached
    return false;
  }

  int startPostion = bufferPosition;
  int endPosition = startPostion;

  while(buffer[endPosition] != delimiter[0]){
    endPosition++;
  }

  int i;
  int j = 0;
  for(i = startPostion; i < endPosition; i++){
    returnString[j] = buffer[i];
    j++;
  }
  returnString[j] = '\0';

  bufferPosition = endPosition + 1;

  return true;
}


bool isValueInArray(int val, int array[], int size){
  for(int i = 0; i < size; i++){
    if(array[i] == val){
      return true;
    }
  }
  return false;
}

/*
* Returns the corresponding register character in the supplied char array "result"
*/
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

/*
* Returns the corresponding operand character in the supplied char array "result"
*/
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

/*
* Returns the corresponding operation character in the supplied char array "result"
*/
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
