#ifndef LSDJ_H
#define LSDJ_H

#include "bn_common.h"

//---------------------------------------------------------------------------
#define LSDJ_CMD_WAIT 0x61 // wait vblank
#define LSDJ_CMD_EOM 0x66  // end of mark
#define LSDJ_CMD_WREG 0xb3 // write register

//---------------------------------------------------------------------------
typedef struct
{

    uint8_t id;
    const uint8_t* pCur;
    const uint8_t* pFile;

    bool isLoop;
    uint8_t loopCnt;

    uint8_t wave[0x10];

    int32_t vCnt;

} ST_LSDJ;

enum
{
    LSDJ_ID_STOP,
    LSDJ_ID_PLAY,
    LSDJ_ID_PAUSE,
};

//---------------------------------------------------------------------------
void LsdjInit(void);
void LsdjPlay(const uint8_t* pFile, bool isLoop);
BN_CODE_IWRAM void LsdjStop(void);
BN_CODE_IWRAM void LsdjIntrVCount(void);

uint32_t LsdjGetOffsetPlay(void);
uint32_t LsdjGetLoopCnt(void);
uint32_t LsdjGetWave(uint32_t i);

#endif
