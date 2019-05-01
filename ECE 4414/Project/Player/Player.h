#pragma once

#include <WaveHC.h>
#include <WaveUtil.h>
// #include <string.h>


// struct Sound
// {
//   Sound(string filename);

//   string name;
//   const uint8_t* data;
// }


class Player
{
 public:
  Player();

  bool play(const char* const filename);
  bool play(FatReader file);
  void mute();

  bool is_playing() const;
  bool has_error() const;

 private:
  FatReader find_and_load(const char* const filename);

  FatReader currently_loaded;

  SdReader card;    // This object holds the information for the card
  FatVolume vol;    // This holds the information for the partition on the card
  FatReader root;   // This holds the information for the volumes root directory
  WaveHC wave;      // This is the only wave (audio) object, since we will only play one at a time
};