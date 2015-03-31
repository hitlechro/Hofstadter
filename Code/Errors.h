#ifndef ERRORS_H
#define ERRORS_H


#define EINDEX -1   /* Index is out of bounds (too large, or nonpositive) */
#define ESYNTAX -2  /* Syntax error in equation */
#define ENUMBER -3  /* Number exception (divide by 0, etc) */
#define ESTRING -4  /* Invalid string was used (null, " ", etc) */
#define EFLOW -5    /* Overflow or Underflow Detected */
#endif // ERRORS_H
