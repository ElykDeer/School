#pragma once


#include "settings.h"
#include <FatReader.h>


class Sound;
struct File
{
  File() : active(false), index(-1), file(nullptr), sound(nullptr){ }

  bool active;
  short index;
  FatReader* file;
  Sound* sound;
};


class Sound {
 public:
  Sound(void);
  bool play(FatReader &f);
  void stop(void);

  void dac_handler();
  void sd_handler();

 private:
  uint8_t *playend;      ///< end position for current buffer
  uint8_t *playpos;      ///< position of next sample
  uint8_t *sdbuff;       ///< SD fill buffer
  uint8_t *sdend;        ///< end of data in sd buffer

  /** Wave file number of channels. Mono = 1, Stereo = 2 */
  uint8_t Channels;
  /** Wave file sample rate. Must be not greater than 44100/sec. */
  uint32_t dwSamplesPerSec;
  /** Wave file bits per sample.  Must be 8 or 16. */
  uint8_t BitsPerSample;
  /** Remaining bytes to be played in Wave file data chunk. */
  uint32_t remainingBytesInChunk;
  /** Has the value true if a wave file is playing else false. */
  volatile uint8_t isplaying;
  /** Number of times data was not available from the SD in the DAC ISR */
  uint32_t errors;

 #if DVOLUME
  /** Software volume control. Reduce volume by 6 dB per step. See DAC ISR. */
  uint8_t volume;
 #endif // DVOLUME
  /** FatReader instance for current wave file. */
  FatReader* fd;
  
  void play(void);
  uint8_t create(FatReader &f);

  uint32_t getSize(void) {return fd->fileSize();}
  // uint8_t isPaused(void);
  // void pause(void);
  int16_t readWaveData(uint8_t *buff, uint16_t len);
  // void resume(void);
  // void seek(uint32_t pos);
  // void setSampleRate(uint32_t samplerate);
};