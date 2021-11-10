#include "sense.h"

float randf(float min, float max){
  return min + (rand() / (RAND_MAX / (max - min)));
}

float bateria(float *carga){
  float decaimento = randf(0, 0.01);
  float tmp = (*carga) - decaimento;
  if(tmp <= 0.0) tmp = 0.0;
  (*carga) = tmp;
  return (*carga);
}