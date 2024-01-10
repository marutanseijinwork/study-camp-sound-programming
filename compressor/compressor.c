#include <stdio.h>
#include <stdlib.h>
#include "wave.h"

int main(void)
{
  MONO_PCM pcm0, pcm1;
  int n;
  double threshold, ratio, gain;
  
  mono_wave_read(&pcm0, "sample03.wav"); /* WAVE�t�@�C�����烂�m�����̉��f�[�^����͂��� */
  
  pcm1.fs = pcm0.fs; /* �W�{�����g�� */
  pcm1.bits = pcm0.bits; /* �ʎq�����x */
  pcm1.length = pcm0.length; /* ���f�[�^�̒��� */
  pcm1.s = calloc(pcm1.length, sizeof(double)); /* �������̊m�� */
  
  threshold = 0.2; /* �������l */
  ratio = 1.0 / 10.0; /* ���V�I */
  gain = 1.0 / (threshold + (1.0 - threshold) * ratio); /* ������ */
  
  for (n = 0; n < pcm1.length; n++)
  {
    pcm1.s[n] = pcm0.s[n];
    
    if (pcm1.s[n] > threshold)
    {
      pcm1.s[n] = threshold + (pcm1.s[n] - threshold) * ratio; /* �U���̈��k */
    }
    else if (pcm0.s[n] < -threshold)
    {
      pcm1.s[n] = -threshold + (pcm0.s[n] + threshold) * ratio; /* �U���̈��k */
    }
    
    pcm1.s[n] *= gain; /* �U���̑��� */
  }
  
  mono_wave_write(&pcm1, "compressor.wav"); /* WAVE�t�@�C���Ƀ��m�����̉��f�[�^���o�͂��� */
  
  free(pcm0.s); /* �������̉�� */
  free(pcm1.s); /* �������̉�� */
  
  return 0;
}
