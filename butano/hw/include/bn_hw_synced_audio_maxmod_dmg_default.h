#ifndef BN_HW_SYNCED_AUDIO_MAXMOD_DMG_DEFAULT_H
#define BN_HW_SYNCED_AUDIO_MAXMOD_DMG_DEFAULT_H

#include "bn_common.h"

#include "../3rd_party/maxmod/include/mm_types.h"

namespace bn
{
    enum class dmg_music_type : uint8_t;
}

namespace bn::hw::synced_audio
{
    void init();

    void enable();

    void disable();

    [[nodiscard]] bool music_playing();

    void play_music(int mus_id, const void* dmg_mus_song, dmg_music_type dmg_mus_type, bool loop);

    void stop_music();

    void pause_music();

    void resume_music();

    void on_vblank();

    mm_word am_sync_maxmod_tick_callback_handler(mm_word msg, mm_word param);
}

#endif
