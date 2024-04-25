#include "../include/lsdj.h"

#include "bn_memory.h"

extern ST_LSDJ lsdj;

//---------------------------------------------------------------------------
void LsdjInit(void)
{
    bn::memory::clear(1, lsdj);
}
//---------------------------------------------------------------------------
void LsdjPlay(const uint8_t* pFile, bool isLoop)
{
    LsdjInit();
    LsdjStop();

    lsdj.id = LSDJ_ID_PLAY;
    lsdj.pCur = pFile;
    lsdj.pFile = pFile;
    lsdj.isLoop = isLoop;
}
//---------------------------------------------------------------------------
uint32_t LsdjGetOffsetPlay(void)
{
    return (uint32_t)(lsdj.pCur - lsdj.pFile);
}
//---------------------------------------------------------------------------
uint32_t LsdjGetLoopCnt(void)
{
    return lsdj.loopCnt;
}
//---------------------------------------------------------------------------
uint32_t LsdjGetWave(uint32_t i)
{
    return lsdj.wave[i & 0xf];
}
