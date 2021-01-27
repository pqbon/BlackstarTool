#pragma once

#include <cstdint>
#include <string>
#include <array>

#include "blackstaramp_types.h"
#include "blackstaramp_control.h"
#include "blackstaramp_hid.h"

namespace BlackstarAmps
{
    class Amp
    {
    public:
        VoiceType get_voice();
        void set_voice(VoiceType voice_);
        
        Byte get_gain();
        void set_gain(Byte gain_);

        Byte get_volume();
        void set_volume(Byte volume_);

        Byte get_bass();
        void set_bass(Byte bass_);

        Byte get_mid();
        void set_mid(Byte mid_);

        Byte get_treble();
        void set_treble(Byte treble_);

        Byte get_isf();
        void set_isf(Byte isf_);

        bool get_tvp_en();
        void set_tvp_en(bool en_);

        ValveType get_tvp();
        void set_tvp(ValveType tvp_);

        bool get_mod_en();
        void set_mod_en(bool en_);
        bool get_delay_en();
        void set_delay_en(bool en_);
        bool get_reverb_en();
        void set_reverb_en(bool en_);

        ModulationType get_mod_type();
        void set_mod_type(ModulationType type_);

        DelayType get_delay_type();
        void set_delay_type(DelayType type_);

        ReverbType get_reverb_type();
        void set_reverb_type(ReverbType type_);

        Byte get_mod_val();
        void set_mod_val(Byte val_);

        Byte get_delay_val();
        void set_delay_val(Byte val_);

        Byte get_reverb_val();
        void set_reverb_val(Byte val_);

        Byte get_mod_level();
        void set_mod_level(Byte level_);

        Byte get_delay_level();
        void set_delay_level(Byte level_);

        Byte get_reverb_level();
        void set_reverb_level(Byte level_);

        void set_modulation(bool en_, ModulationType type_, Byte val_, Byte level_);
        void set_reverb(bool en_, ReverbType type_, Byte val_, Byte level_);
        void set_delay(bool en_, DelayType type_, Byte val_, Byte level_);

    private:
        // PreAmp
        VOICE_Control voice {VoiceType::WARM, VoiceType::OD2};
        GAIN_Control gain {0, 0x7f};
        VOLUME_Control volume {0, 0x7f};

        // Equalisation
        BASS_Control bass {0, 0x7f};
        MID_Control mid {0, 0x7f};
        TREBLE_Control treble {0, 0x7f};
        ISF_Control isf {0, 0x7f};

        // True VALVE Power
        TVP_ENABLE_Control tvp_en {0, 1};
        TVP_VALUE_Control tvp_val {ValveType::TVP_EL84, ValveType::TVP_KT88};

        // Effects
        MOD_ENABLE_Control modulation_en {0, 1};
        DELAY_ENABLE_Control delay_en {0, 1};
        REVERB_ENABLE_Control reverb_en {0, 1};
        MOD_TYPE_Control modulation_type {ModulationType::CHORUS, ModulationType::TREMELO};
        DELAY_TYPE_Control delay_type {DelayType::ANALOG, DelayType::TAPE};
        REVERB_TYPE_Control reverb_type {ReverbType::HALL, ReverbType::SPRING};
        MOD_VALUE_Control modulation_val {0, 0x1f};
        DELAY_VALUE_Control delay_val {0, 0x1f};
        REVERB_VALUE_Control reverb_val {0, 0x1f};
        MOD_LEVEL_Control modulation_level {0, 0x7f};
        DELAY_LEVEL_Control delay_level {0, 0x7f};
        REVERB_LEVEL_Control reverb_level {0, 0x7f};

        // Configuration/Banks
        MANUAL_ENABLE_Control manual_en {0, 1};
        BANK_Control bank {0, 1};
        CHANNEL1_Control channel1 {0, 1};
        CHANNEL2_Control channel2 {0, 1};
        CHANNEL3_Control channel3 {0, 1};
        CHANNEL4_Control channel4 {0, 1};

        // Power Amp settings
        M_RESONENCE_Control pa_resonence {0, 1};
        M_PRESENCE_Control pa_presence {0, 1};
        M_VOLUME_Control pa_volume {0, 1};
    };
} // namespace BlackstarAmps