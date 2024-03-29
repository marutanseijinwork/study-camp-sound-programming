#include <stdio.h>
#include <stdlib.h>
#include "wave.h"

int main(void)
{
  MONO_PCM pcm0, pcm1;
  int n;
  double gain, level;
  
  mono_wave_read(&pcm0, "sample02.wav"); /* WAVEファイルからモノラルの音データを入力する */
  
  pcm1.fs = pcm0.fs; /* 標本化周波数 */
  pcm1.bits = pcm0.bits; /* 量子化精度 */
  pcm1.length = pcm0.length; /* 音データの長さ */
  pcm1.s = calloc(pcm1.length, sizeof(double)); /* メモリの確保 */
  
  gain = 100.0; /* 増幅率 */
  level = 0.5; /* レベル */
  
  for (n = 0; n < pcm1.length; n++)
  {
    pcm1.s[n] = pcm0.s[n] * gain; /* 音データの増幅 */
    
    if (pcm1.s[n] > 1.0)
    {
      pcm1.s[n] = 1.0; /* クリッピング */
    }
    else if (pcm1.s[n] < -1.0)
    {
      pcm1.s[n] = -1.0; /* クリッピング */
    }
    
    pcm1.s[n] *= level; /* 音の大きさを調節する */
  }
  
  mono_wave_write(&pcm1, "distortion.wav"); /* WAVEファイルにモノラルの音データを出力する */
  
  free(pcm0.s); /* メモリの解放 */
  free(pcm1.s); /* メモリの解放 */
  
  return 0;
}
