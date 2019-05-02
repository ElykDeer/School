#pragma once

// #include <WaveHC.h>
#include "File.h"
#include <WaveUtil.h>


#define CHANNEL_COUNT 16


class Player
{
 public:
  Player();

  bool play(const char* const filename);
  bool play(short index);
  // void mute();

  // bool is_playing() const;
  bool has_error() const;

 private:
  FatReader* find_and_load(const char* const filename);

  File* channels[CHANNEL_COUNT];
  short channel_top = 0;

  SdReader card;    // This object holds the information for the card
  FatVolume vol;    // This holds the information for the partition on the card
  FatReader root;   // This holds the information for the volumes root directory
};