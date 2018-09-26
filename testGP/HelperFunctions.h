#ifndef HELPERFUNCTIONS_H
#define HELPERFUNCTIONS_H

int convertASCIIToFloats(char data_row[], float array[], int size);
float stof(char s []);
bool myStrtok(bool firstRun, char buffer [], const char delimiter [], char returnString []);

bool isValueInArray(int val, int array[], int size);

void getRegChar(int reg, char result[]);
void getOperandChar(int op, char result[]);
void getOperationChar(int operation, char result[]);


#endif
