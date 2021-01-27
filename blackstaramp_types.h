#pragma once

#include <cstdint>

namespace BlackstarAmps
{
    using Byte = std::uint8_t;
    using Word = std::uint16_t;

    enum class ControlType : Byte
    {
        VOICE,
        GAIN,
        VOLUME,
        BASS,
        MID,
        TREBLE,
        ISF,
        TVP_VALUE,
        M_RESONENCE,
        M_PRESENCE,
        M_VOLUME,
        TVP_ENABLE,
        MOD_ENABLE,
        DELAY_ENABLE,
        REVERB_ENABLE,
        MOD_TYPE,
        MOD_VALUE,
        MOD_TAPTEMPO,
        DELAY_TYPE,
        DELAY_VALUE,
        DELAY_TAPTEMPO,
        REVERB_TYPE,
        REVERB_VALUE,
        MOD_LEVEL,
        DELAY_LEVEL,
        REVERB_LEVEL,
        MANUAL_ENABLE,
        BANK,
        CHANNEL1,
        CHANNEL2,
        CHANNEL3,
        CHANNEL4,
    };

    enum class VoiceType : Byte
    {
        WARM = 0,
        BRIGHT = 1,
        CHRUNCH = 2,
        SUPER_CRUNCH = 3,
        OD1 = 4,
        OD2 = 5,
    };

    enum class ValveType : Byte
    {
        TVP_EL84 = 0,
        TVP_6V6 = 1,
        TVP_EL34 = 2,
        TVP_KT66 = 3,
        TVP_6L6 = 4,
        TVP_KT88 = 5,
    };

    enum class ModulationType : Byte
    {
        PHASER,
        FLANGER,
        CHORUS,
        TREMELO,
    };

    enum class DelayType : Byte
    {
        LINEAR,
        ANALOG,
        TAPE,
        MULTI,
    };

    enum class ReverbType : Byte
    {
        ROOM,
        HALL,
        SPRING,
        PLATE,
    };

} // namespace BlackstarAmps