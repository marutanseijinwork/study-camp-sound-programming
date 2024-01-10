#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "wave.h"

int main(void)
{
  MONO_PCM pcm1;
  int n;
  double A, f0;
  
  pcm1.fs = 8000; /* �W�{�����g�� */
  pcm1.bits = 16; /* �ʎq�����x */
  pcm1.length = 8000; /* ���f�[�^�̒��� */
  pcm1.s = calloc(pcm1.length, sizeof(double)); /* �������̊m�� */
  
  A = 0.25; /* �U�� */
  f0 = 250.0; /* ��{���g�� */
  
  /* �T�C���g */
  for (n = 0; n < pcm1.length; n++)
  {
    pcm1.s[n] = A * sin(2.0 * M_PI * f0 * n / pcm1.fs);
  }
  
  mono_wave_write(&pcm1, "result.wav"); /* WAVE�t�@�C���Ƀ��m�����̉��f�[�^���o�͂��� */
  
  free(pcm1.s); /* �������̉�� */
  
  return 0;
}