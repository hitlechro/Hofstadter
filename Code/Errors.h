#ifndef ERRORS_H
#define ERRORS_H


#define EUINDEX -1  /* Index is out of bounds - less than startIndex */
#define EOINDEX -2  /* Index is out of bounds - too large */
#define ESYNTAX -3  /* Syntax error in equation */
#define ENUMBER -4  /* Number exception (divide by 0, etc) */
#define ESTRING -5  /* Invalid string was used (null, " ", etc) */
#define EFLOW -6    /* Overflow or Underflow Detected */
#endif // ERRORS_H
