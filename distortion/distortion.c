#include <stdio.h>
#include <stdlib.h>
#include "wave.h"

int main(void)
{
  MONO_PCM pcm0, pcm1;
  int n;
  double gain, level;
  
  mono_wave_read(&pcm0, "sample02.wav"); /* WAVE�t�@�C�����烂�m�����̉��f�[�^����͂��� */
  
  pcm1.fs = pcm0.fs; /* �W�{�����g�� */
  pcm1.bits = pcm0.bits; /* �ʎq�����x */
  pcm1.length = pcm0.length; /* ���f�[�^�̒��� */
  pcm1.s = calloc(pcm1.length, sizeof(double)); /* �������̊m�� */
  
  gain = 100.0; /* ������ */
  level = 0.5; /* ���x�� */
  
  for (n = 0; n < pcm1.length; n++)
  {
    pcm1.s[n] = pcm0.s[n] * gain; /* ���f�[�^�̑��� */
    
    if (pcm1.s[n] > 1.0)
    {
      pcm1.s[n] = 1.0; /* �N���b�s���O */
    }
    else if (pcm1.s[n] < -1.0)
    {
      pcm1.s[n] = -1.0; /* �N���b�s���O */
    }
    
    pcm1.s[n] *= level; /* ���̑傫���𒲐߂��� */
  }
  
  mono_wave_write(&pcm1, "distortion.wav"); /* WAVE�t�@�C���Ƀ��m�����̉��f�[�^���o�͂��� */
  
  free(pcm0.s); /* �������̉�� */
  free(pcm1.s); /* �������̉�� */
  
  return 0;
}
