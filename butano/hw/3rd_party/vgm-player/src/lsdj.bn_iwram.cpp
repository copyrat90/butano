#include "../include/lsdj.h"

#define REG_BASE 0x04000000
#define REG_IME *(volatile uint16_t*)(REG_BASE + 0x208)
#define REG_DISPSTAT *((volatile uint16_t*)(REG_BASE + 0x04))
#define STAT_MASK 0x00ff

#define VCOUNT(m) (m << 8)
#define LCDC_VCNT (1 << 5)

//---------------------------------------------------------------------------
// Vcount Interrupt Table
int32_t lsdjVmap[6] = {
    0, 38, 76, 114, 152, 190,
};

//---------------------------------------------------------------------------
ST_LSDJ lsdj;

//---------------------------------------------------------------------------
BN_CODE_IWRAM void LsdjStop(void)
{
    lsdj.id = LSDJ_ID_STOP;

    // REG_SOUNDCNT
    *(volatile uint8_t*)(REG_BASE + 0x84) = 0x00;

    // ch1
    *(volatile uint8_t*)(REG_BASE + 0x60) = 0x80;
    *(volatile uint8_t*)(REG_BASE + 0x62) = 0xBF;
    *(volatile uint8_t*)(REG_BASE + 0x63) = 0xF3;
    *(volatile uint8_t*)(REG_BASE + 0x64) = 0xC1;
    *(volatile uint8_t*)(REG_BASE + 0x65) = 0xBF;

    // ch2
    *(volatile uint8_t*)(REG_BASE + 0x68) = 0x00;
    *(volatile uint8_t*)(REG_BASE + 0x69) = 0x00;
    *(volatile uint8_t*)(REG_BASE + 0x6c) = 0x00;
    *(volatile uint8_t*)(REG_BASE + 0x6d) = 0xB8;

    // ch3
    *(volatile uint8_t*)(REG_BASE + 0x70) = 0x7F;
    *(volatile uint8_t*)(REG_BASE + 0x72) = 0x00;
    *(volatile uint8_t*)(REG_BASE + 0x73) = 0x9F;
    *(volatile uint8_t*)(REG_BASE + 0x74) = 0x00;
    *(volatile uint8_t*)(REG_BASE + 0x75) = 0xB8;

    // wave
    *(volatile uint8_t*)(REG_BASE + 0x90 + 0x0) = 0x96;
    *(volatile uint8_t*)(REG_BASE + 0x90 + 0x1) = 0xF2;
    *(volatile uint8_t*)(REG_BASE + 0x90 + 0x2) = 0xAA;
    *(volatile uint8_t*)(REG_BASE + 0x90 + 0x3) = 0xA7;
    *(volatile uint8_t*)(REG_BASE + 0x90 + 0x4) = 0x24;
    *(volatile uint8_t*)(REG_BASE + 0x90 + 0x5) = 0x4C;
    *(volatile uint8_t*)(REG_BASE + 0x90 + 0x6) = 0x8A;
    *(volatile uint8_t*)(REG_BASE + 0x90 + 0x7) = 0xD5;
    *(volatile uint8_t*)(REG_BASE + 0x90 + 0x8) = 0x11;
    *(volatile uint8_t*)(REG_BASE + 0x90 + 0x9) = 0xF3;
    *(volatile uint8_t*)(REG_BASE + 0x90 + 0xA) = 0xD0;
    *(volatile uint8_t*)(REG_BASE + 0x90 + 0xB) = 0xC1;
    *(volatile uint8_t*)(REG_BASE + 0x90 + 0xC) = 0x19;
    *(volatile uint8_t*)(REG_BASE + 0x90 + 0xD) = 0xEA;
    *(volatile uint8_t*)(REG_BASE + 0x90 + 0xE) = 0x18;
    *(volatile uint8_t*)(REG_BASE + 0x90 + 0xF) = 0x6F;

    // ch4
    *(volatile uint8_t*)(REG_BASE + 0x78) = 0xC0;
    *(volatile uint8_t*)(REG_BASE + 0x79) = 0xC0;
    *(volatile uint8_t*)(REG_BASE + 0x7c) = 0x00;
    *(volatile uint8_t*)(REG_BASE + 0x7d) = 0xBF;

    // REG_SOUNDCNT
    *(volatile uint8_t*)(REG_BASE + 0x80) = 0x77;
    *(volatile uint8_t*)(REG_BASE + 0x81) = 0xF3;
    //	*(volatile uint8_t*)(REG_BASE + 0x84) = 0xF1;
}
//---------------------------------------------------------------------------
BN_CODE_IWRAM void LsdjIntrVCount(void)
{
    if (lsdj.id == LSDJ_ID_STOP)
    {
        goto End;
    }

    for (;;)
    {
        uint8_t cmd = *lsdj.pCur++;

        if (cmd == LSDJ_CMD_WAIT)
        {
            goto End;
        }

        if (cmd == LSDJ_CMD_WREG)
        {
            uint8_t adr = *lsdj.pCur++;
            uint8_t dat = *lsdj.pCur++;
            *(uint8_t*)(REG_BASE + adr) = dat;

            if (adr >= 0x90 && adr <= 0x9f)
            {
                lsdj.wave[adr - 0x90] = dat;
            }

            continue;
        }

        if (cmd == LSDJ_CMD_EOM)
        {
            if (lsdj.isLoop == false)
            {
                LsdjStop();

                goto End;
            }

            lsdj.pCur = lsdj.pFile;
            lsdj.loopCnt++;

            continue;
        }

        // SystemError("LsdjIntrVblank adr=%x", lsdj.pCur - lsdj.pFile);
    }

End:

    lsdj.vCnt++;

    if (lsdj.vCnt >= 6)
    {
        lsdj.vCnt = 0;
    }

    REG_DISPSTAT = (REG_DISPSTAT & STAT_MASK) | LCDC_VCNT | VCOUNT(lsdjVmap[lsdj.vCnt]);
}
