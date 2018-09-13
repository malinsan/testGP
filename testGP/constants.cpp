#include "StringPrinter.h"

namespace Constants
{
  extern const int MAX_INDIVIDUAL_LENGTH = 50;

  /*
    * Registers:  a, b, c :
               :  0, 1, 2 :
    * Operands :  a, b, c, -1, 0, 1 :
               :  0, 1, 2,  3, 4, 5 :
    * Operators:  +, -, * :
               :  0, 1, 2 :
  */
  extern const int REG_MAX = 2;
  extern const int OPERAND_MAX = 5;
  extern const int OPERATOR_MAX = 2;


  //testdata
  extern const int TEST_DATA_X[] = {0,1,2,3,4,5,6,7,8,9,10};
  extern const int TEST_DATA_A_Y[] = {1,2,5,10,17,26,37,50,65,82,101}; // x²+1
}


namespace Helper_Functions
{

}
