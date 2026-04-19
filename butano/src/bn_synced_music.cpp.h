#include "bn_synced_music.h"

#include "bn_dmg_music_item.h"
#include "bn_music_item.h"
#include "bn_audio_manager.h"

namespace bn::synced_music
{

bool playing()
{
    return audio_manager::synced_music_playing();
}

optional<music_item> playing_music_item()
{
    return audio_manager::playing_synced_music_item();
}

optional<dmg_music_item> playing_dmg_music_item()
{
    return audio_manager::playing_synced_dmg_music_item();
}

void play(music_item mus_item, const dmg_music_item& dmg_mus_item)
{
    audio_manager::play_synced_music(mus_item, dmg_mus_item, 1, true);
}

void play(music_item mus_item, const dmg_music_item& dmg_mus_item, fixed mus_volume)
{
    BN_BASIC_ASSERT(mus_volume >= 0 && mus_volume <= 1, "Volume range is [0..1]: ", mus_volume);

    audio_manager::play_synced_music(mus_item, dmg_mus_item, mus_volume, true);
}

void play(music_item mus_item, const dmg_music_item& dmg_mus_item, fixed mus_volume, bool loop)
{
    BN_BASIC_ASSERT(mus_volume >= 0 && mus_volume <= 1, "Volume range is [0..1]: ", mus_volume);

    audio_manager::play_synced_music(mus_item, dmg_mus_item, mus_volume, loop);
}

void stop()
{
    audio_manager::stop_synced_music();
}

bool paused()
{
    return audio_manager::synced_music_paused();
}

void pause()
{
    audio_manager::pause_synced_music();
}

void resume()
{
    audio_manager::resume_synced_music();
}

}
