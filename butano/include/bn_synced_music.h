#ifndef BN_SYNCED_MUSIC_H
#define BN_SYNCED_MUSIC_H

/**
 * @brief
 * bn::synced_music header file.
 *
 * @ingroup synced_music
 */

#include "bn_config_doxygen.h"
#include "bn_fixed.h"
#include "bn_optional.h"

namespace bn
{
    class music_item;
    class dmg_music_item;
}

#if defined(BN_DMG_AUDIO_SYNC) || BN_DOXYGEN

/**
 * @brief Synchronized music (Direct Sound + DMG) related functions.
 *
 * @ingroup synced_music
 */
namespace bn::synced_music
{
    /**
     * @brief Indicates if currently there's any synchronized music playing or not.
     */
    [[nodiscard]] bool playing();

    /**
     * @brief Returns the active music_item if there's any synchronized music playing; bn::nullopt otherwise.
     */
    [[nodiscard]] optional<music_item> playing_music_item();

    /**
     * @brief Returns the active dmg_music_item if there's any synchronized music playing; bn::nullopt otherwise.
     */
    [[nodiscard]] optional<dmg_music_item> playing_dmg_music_item();

    /**
     * @brief Plays the synchronized music specified by the given music_item and dmg_music_item with default settings.
     *
     * Default settings are volume = 1 and loop enabled.
     */
    void play(music_item music_item, const dmg_music_item& dmg_music_item);

    /**
     * @brief Plays the synchronized music specified by the given music_item and dmg_music_item.
     * @param music_item Specifies the music to play.
     * @param dmg_music_item Specifies the DMG music to play.
     * @param music_volume Direct Sound volume level, in the range [0..1].
     */
    void play(music_item music_item, const dmg_music_item& dmg_music_item, fixed music_volume);

    /**
     * @brief Plays the synchronized music specified by the given music_item and dmg_music_item.
     * @param music_item Specifies the music to play.
     * @param dmg_music_item Specifies the DMG music to play.
     * @param music_volume Direct Sound volume level, in the range [0..1].
     * @param loop Indicates if it must be played until it is stopped manually or until end.
     */
    void play(music_item music_item, const dmg_music_item& dmg_music_item, fixed music_volume, bool loop);

    /**
     * @brief Stops playback of the active synchronized music.
     */
    void stop();

    /**
     * @brief Indicates if the active synchronized music has been paused or not.
     */
    [[nodiscard]] bool paused();

    /**
     * @brief Pauses playback of the active synchronized music.
     */
    void pause();

    /**
     * @brief Resumes playback of the paused synchronized music.
     */
    void resume();

    /**
     * @brief Returns the sequence position of the active Direct Sound music of the synchronized music.
     */
    [[nodiscard]] int music_position();

    /**
     * @brief Returns the sequence position of the active DMG music of the synchronized music.
     */
    [[nodiscard]] const bn::dmg_music_position& dmg_music_position();

    /**
     * @brief Returns the volume of the active Direct Sound music of the synchronized music.
     */
    [[nodiscard]] fixed music_volume();

    /**
     * @brief Sets the volume of the active Direct Sound music of the synchronized music.
     * @param volume Volume level, in the range [0..1].
     */
    void set_music_volume(fixed volume);

    /**
     * @brief Returns the volume of the active DMG music of the synchronized music for the left speaker.
     */
    [[nodiscard]] fixed dmg_music_left_volume();

    /**
     * @brief Returns the volume of the active DMG music of the synchronized music for the right speaker.
     */
    [[nodiscard]] fixed dmg_music_right_volume();

    /**
     * @brief Sets the volume of the active DMG music of the synchronized music for the left speaker.
     *
     * Volume change is not supported by the VGM player.
     *
     * @param left_volume Left speaker volume level, in the range [0..1].
     */
    void dmg_music_set_left_volume(fixed left_volume);

    /**
     * @brief Sets the volume of the active DMG music of the synchronized music for the right speaker.
     *
     * Volume change is not supported by the VGM player.
     *
     * @param right_volume Right speaker volume level, in the range [0..1].
     */
    void dmg_music_set_right_volume(fixed right_volume);

    /**
     * @brief Sets the volume of the active DMG music of the synchronized music for both speakers.
     *
     * Volume change is not supported by the VGM player.
     *
     * @param volume Volume level, in the range [0..1].
     */
    void dmg_music_set_volume(fixed volume);

    /**
     * @brief Sets the volume of the active DMG music of the synchronized music for both speakers.
     *
     * Volume change is not supported by the VGM player.
     *
     * @param left_volume Left speaker volume level, in the range [0..1].
     * @param right_volume Right speaker volume level, in the range [0..1].
     */
    void dmg_music_set_volume(fixed left_volume, fixed right_volume);

    /**
     * @brief Returns the tempo of the active synchronized music.
     */
    [[nodiscard]] fixed tempo();

    /**
     * @brief Sets the tempo of the active synchronized music.
     * 
     * Synchronized music must be paused before changing the tempo.
     *
     * @param tempo Tempo level, in the range [0.5..2].
     */
    void set_tempo(fixed tempo);

    /**
     * @brief Returns the pitch of the active Direct Sound music of the synchronized music.
     */
    [[nodiscard]] fixed music_pitch();

    /**
     * @brief Sets the pitch of the active Direct Sound music of the synchronized music.
     * @param pitch Pitch level, in the range [0.5..2].
     */
    void set_music_pitch(fixed pitch);
}

#endif

#endif
