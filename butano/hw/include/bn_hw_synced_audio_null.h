#ifndef BN_HW_SYNCED_AUDIO_NULL_H
#define BN_HW_SYNCED_AUDIO_NULL_H

#include "bn_common.h"

namespace bn
{
    enum class dmg_music_type : uint8_t;
}

namespace bn::hw::synced_audio
{
    inline void init()
    {
    }

    inline void enable()
    {
    }

    inline void disable()
    {
    }

    [[nodiscard]] inline bool music_playing()
    {
        return false;
    }

    inline void play_music(int, const void*, dmg_music_type, bool)
    {
    }

    inline void stop_music()
    {
    }

    inline void pause_music()
    {
    }

    inline void resume_music()
    {
    }

    inline void on_vblank()
    {
    }
}

#endif
