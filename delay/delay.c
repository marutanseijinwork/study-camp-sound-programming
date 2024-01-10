#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "wave.h"

int main(void)
{
  MONO_PCM pcm0, pcm1;
  int n, m, i, repeat;
  double a, d;
  
  mono_wave_read(&pcm0, "sample01.wav"); /* WAVE�t�@�C�����烂�m�����̉��f�[�^����͂��� */
  
  pcm1.fs = pcm0.fs; /* �W�{�����g�� */
  pcm1.bits = pcm0.bits; /* �ʎq�����x */
  pcm1.length = pcm0.length; /* ���f�[�^�̒��� */
  pcm1.s = calloc(pcm1.length, sizeof(double)); /* �������̊m�� */
  
  a = 0.5; /* ������ */
  d = pcm1.fs * 0.375; /* �x������ */
  repeat = 2; /* �J��Ԃ��� */
  
  for (n = 0; n < pcm1.length; n++)
  {
    pcm1.s[n] = pcm0.s[n]; /* ���݂̎����̉��f�[�^ */
    
    for (i = 1; i <= repeat; i++)
    {
      m = (int)((double)n - (double)i * d);
      
      if (m >= 0)
      {
        pcm1.s[n] += pow(a, (double)i) * pcm0.s[m]; /* �ߋ��̉��f�[�^���~�b�N�X���� */
      }
    }
  }
  
  mono_wave_write(&pcm1, "delay.wav"); /* WAVE�t�@�C���Ƀ��m�����̉��f�[�^���o�͂��� */
  
  free(pcm0.s); /* �������̉�� */
  free(pcm1.s); /* �������̉�� */
  
  return 0;
}
