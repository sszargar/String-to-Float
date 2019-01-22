#include <iostream>
#include <stdlib.h>
#include <cmath>
  using namespace std;

enum State {
  START,
  DONE,
  GOT_DIGIT,
  GOT_DECIMAL,
  GOT_EXPONENT
}
\

float stringToFloat(const char input[]) {

  State s = START;
  int i = 0;
  int k = -1;
  int sign = 1;
  int exponent = 0;
  int expSign = 1;

  float total = 0;

  if (input[0] == '+' && input[1] == '+') {
    return NAN;
  }

  if (input[0] == '+' && input[1] == '-') {
    return NAN;
  }
  if (input[0] == '-' && input[1] == '+') {
    return NAN;
  }
  if (input[0] == '-' && input[1] == '-') {
    return NAN;
  }

  if (input[0] == '.' && input[1] == '\0') {
    return NAN;
  }

  while (s != DONE) {
    int num = input[i];

    switch (s) {
    case START:

      if (input[i] == '\0') {
        return NAN;
      }

      if (num == '-') {
        sign = -1;

        if (input[i + 1] == '.') {
          s = GOT_DECIMAL;
          i++;
        } else if (input[i + 1] >= '0' && input[i + 1] <= '9') {
          s = GOT_DIGIT;
          i++;
        }
      } else if (num == '+') {
        sign = 1;
        if (input[i + 1] == '.') {
          s = GOT_DECIMAL;
          i++;
        } else if (input[i + 1] >= '0' && input[i + 1] <= '9') {
          s = GOT_DIGIT;
          i++;
        }
      } else if (num >= '0' && num <= '9') {
        s = GOT_DIGIT;
      } else if (num == '.') {
        s = GOT_DECIMAL;
        i++;
      } else {
        return NAN;
      }

      break;

    case GOT_DIGIT:
      if (num == '.') {
        s = GOT_DECIMAL;
        i++;
      } else if (num >= '0' && num <= '9') {
        s = GOT_DIGIT;
        total = total * 10 + (num - 48);
        i++;
      } else if (num == '\0') {
        s = DONE;
      } else if (num == 'e' || num == 'E') {
        s = GOT_EXPONENT;
        i++;
      } else {
        return NAN;
      }

      break;

    case GOT_DECIMAL:
      if (num >= '0' && num <= '9') {
        s = GOT_DECIMAL;
        total = total + ((num - 48) * pow(10, k));
        k--;
        i++;
      } else if (num == 0) {
        s = DONE;
      } else if (num == 'e' || num == 'E') {
        s = GOT_EXPONENT;
        i++;
      } else {
        return NAN;
      }

      break;

    case GOT_EXPONENT:
      if ((input[i - 1] == 'e' && input[i] == '-') || (input[i - 1] == 'E' && input[i] == '-')) {
        expSign = -1;
        i++;
      }

      if (input[i - 1] == 'e' && num == '\0') {
        return NAN;
      } else if (num >= '0' && num <= '9') {
        cout << "exponent" << exponent << endl;
        s = GOT_EXPONENT;
        exponent = exponent * 10 + (num - 48);
        i++;
      } else if (num == 0) {
        s = DONE;
      } else {
        return NAN;
      }

      break;

    case DONE:
      return total;
      break;
    }

  }

  cout << total << endl;
  cout << exponent << endl;
  cout << expSign << endl;

  total = sign * total * pow(10.0, (exponent * expSign));
  return total;

}

#ifndef MARMOSET_TESTING
int main() {
  char input[] = {
    '.',
    '9',
    '2',
    'E',
    '9',
    '9',
    '\0'
  };
  cout << stringToFloat(input) << endl;
}
#endif
