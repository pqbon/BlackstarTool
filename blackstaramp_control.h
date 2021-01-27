#pragma once

#include <cstdint>
#include <string>
#include <limits>

#include "blackstaramp_types.h"

namespace BlackstarAmps
{
    template <typename T, ControlType TYPE_>
    class Control
    {
    public:
        Control() = delete;
        Control(const T min_, const T max_) : min{min_}, max{max_} {}

        void set(T val_) { value = val_; }
        T get(void) const { return value; }

        Control<T, TYPE_>& operator=(T val) { this->value = val; return *this; };
        T& operator=(Control<T, TYPE_>& ctl) { return value; };

        operator T() { return value; };

    private:
        ControlType type{TYPE_};

        T value;
        const T min{std::numeric_limits<T>::min()};
        const T max{std::numeric_limits<T>::max()};
    };

    template <ControlType TYPE__>
    using ByteControl = Control<Byte, TYPE__>;

    using VOICE_Control = Control<VoiceType, ControlType::VOICE>;
    using GAIN_Control = ByteControl<ControlType::GAIN>;
    using VOLUME_Control = ByteControl<ControlType::VOLUME>;
    using BASS_Control = ByteControl<ControlType::BASS>;
    using MID_Control = ByteControl<ControlType::MID>;
    using TREBLE_Control = ByteControl<ControlType::TREBLE>;
    using ISF_Control = ByteControl<ControlType::ISF>;
    using TVP_ENABLE_Control = ByteControl<ControlType::TVP_ENABLE>;
    using TVP_VALUE_Control = Control<ValveType, ControlType::TVP_VALUE>;
    using MOD_ENABLE_Control = ByteControl<ControlType::MOD_ENABLE>;
    using DELAY_ENABLE_Control = ByteControl<ControlType::DELAY_ENABLE>;
    using REVERB_ENABLE_Control = ByteControl<ControlType::REVERB_ENABLE>;
    using MOD_TYPE_Control = Control<ModulationType, ControlType::MOD_TYPE>;
    using DELAY_TYPE_Control = Control<DelayType, ControlType::DELAY_TYPE>;
    using REVERB_TYPE_Control = Control<ReverbType, ControlType::REVERB_TYPE>;
    using MOD_VALUE_Control = ByteControl<ControlType::MOD_VALUE>;
    using DELAY_VALUE_Control = ByteControl<ControlType::DELAY_VALUE>;
    using REVERB_VALUE_Control = ByteControl<ControlType::REVERB_VALUE>;
    using MOD_LEVEL_Control = ByteControl<ControlType::MOD_LEVEL>;
    using DELAY_LEVEL_Control = ByteControl<ControlType::DELAY_LEVEL>;
    using REVERB_LEVEL_Control = ByteControl<ControlType::REVERB_LEVEL>;
    using MANUAL_ENABLE_Control = ByteControl<ControlType::MANUAL_ENABLE>;
    using BANK_Control = ByteControl<ControlType::BANK>;
    using CHANNEL1_Control = ByteControl<ControlType::CHANNEL1>;
    using CHANNEL2_Control = ByteControl<ControlType::CHANNEL2>;
    using CHANNEL3_Control = ByteControl<ControlType::CHANNEL3>;
    using CHANNEL4_Control = ByteControl<ControlType::CHANNEL4>;
    using M_RESONENCE_Control = ByteControl<ControlType::M_RESONENCE>;
    using M_PRESENCE_Control = ByteControl<ControlType::M_PRESENCE>;
    using M_VOLUME_Control = ByteControl<ControlType::M_VOLUME>;

} // namespace BlackstarAmps