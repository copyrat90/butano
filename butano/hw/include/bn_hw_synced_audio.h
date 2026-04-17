#ifndef BN_HW_SYNCED_AUDIO_H
#define BN_HW_SYNCED_AUDIO_H

#ifdef BN_DMG_AUDIO_SYNC
    #include "bn_hw_synced_audio_maxmod_dmg_default.h"
#else
    #include "bn_hw_synced_audio_null.h"
#endif

#endif
