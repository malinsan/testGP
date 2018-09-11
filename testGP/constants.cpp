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
}
