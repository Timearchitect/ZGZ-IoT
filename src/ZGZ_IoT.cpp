#include "ZGZ_IoT.h"

String urlEncode(String s) {
  for (int i = 0; i < s.length(); i++) {
    if (s[i] == ' ') s[i] = '+';
  }
  return s;
}
