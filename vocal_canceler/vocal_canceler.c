#include <stdio.h>
#include <stdlib.h>
#include "wave.h"

int main(void)
{
  STEREO_PCM pcm0; /* �X�e���I�̉��f�[�^ */
  MONO_PCM pcm1; /* ���m�����̉��f�[�^ */
  int n;
  
  stereo_wave_read(&pcm0, "sample11.wav"); /* WAVE�t�@�C������X�e���I�̉��f�[�^����͂��� */
  
  pcm1.fs = pcm0.fs; /* �W�{�����g�� */
  pcm1.bits = pcm0.bits; /* �ʎq�����x */
  pcm1.length = pcm0.length; /* ���f�[�^�̒��� */
  pcm1.s = calloc(pcm1.length, sizeof(double)); /* �������̊m�� */
  
  /* �{�[�J���L�����Z�� */
  for (n = 0; n < pcm1.length; n++)
  {
    pcm1.s[n] = pcm0.sL[n] - pcm0.sR[n];
  }
  
  mono_wave_write(&pcm1, "vocal_canceler.wav"); /* WAVE�t�@�C���Ƀ��m�����̉��f�[�^���o�͂��� */
  
  free(pcm0.sL); /* �������̉�� */
  free(pcm0.sR); /* �������̉�� */
  free(pcm1.s); /* �������̉�� */
  
  return 0;
}
