#include <stdio.h>
#include <stdlib.h>
#include "wave.h"

int main(void)
{
  MONO_PCM pcm0, pcm1;
  int n;
  double threshold, ratio, gain;
  
  mono_wave_read(&pcm0, "sample03.wav"); /* WAVEファイルからモノラルの音データを入力する */
  
  pcm1.fs = pcm0.fs; /* 標本化周波数 */
  pcm1.bits = pcm0.bits; /* 量子化精度 */
  pcm1.length = pcm0.length; /* 音データの長さ */
  pcm1.s = calloc(pcm1.length, sizeof(double)); /* メモリの確保 */
  
  threshold = 0.2; /* しきい値 */
  ratio = 1.0 / 10.0; /* レシオ */
  gain = 1.0 / (threshold + (1.0 - threshold) * ratio); /* 増幅率 */
  
  for (n = 0; n < pcm1.length; n++)
  {
    pcm1.s[n] = pcm0.s[n];
    
    if (pcm1.s[n] > threshold)
    {
      pcm1.s[n] = threshold + (pcm1.s[n] - threshold) * ratio; /* 振幅の圧縮 */
    }
    else if (pcm0.s[n] < -threshold)
    {
      pcm1.s[n] = -threshold + (pcm0.s[n] + threshold) * ratio; /* 振幅の圧縮 */
    }
    
    pcm1.s[n] *= gain; /* 振幅の増幅 */
  }
  
  mono_wave_write(&pcm1, "compressor.wav"); /* WAVEファイルにモノラルの音データを出力する */
  
  free(pcm0.s); /* メモリの解放 */
  free(pcm1.s); /* メモリの解放 */
  
  return 0;
}
