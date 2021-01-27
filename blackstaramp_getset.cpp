#include "blackstaramp_control.h"
#include "blackstaramp.h"

namespace BlackstarAmps
{
    VoiceType Amp::get_voice()
    {
        return voice;
    }
    void Amp::set_voice(VoiceType voice_)
    {
        voice = voice_;
    }

    Byte Amp::get_gain()
    {
        return gain;
    }
    void Amp::set_gain(Byte gain_)
    {
        gain = gain_;
    }

    Byte Amp::get_volume()
    {
        return volume;
    }
    void Amp::set_volume(Byte volume_)
    {
        volume = volume_;
    }

    Byte Amp::get_bass()
    {
        return bass;
    }
    void Amp::set_bass(Byte bass_)
    {
        bass = bass_;
    }

    Byte Amp::get_mid()
    {
        return mid;
    }
    void Amp::set_mid(Byte mid_)
    {
        mid = mid_;
    }

    Byte Amp::get_treble()
    {
        return treble;
    }
    void Amp::set_treble(Byte treble_)
    {
        treble = treble_;
    }

    Byte Amp::get_isf()
    {
        return isf;
    }
    void Amp::set_isf(Byte isf_)
    {
        isf = isf_;
    }

    bool Amp::get_tvp_en()
    {
        return tvp_en;
    }
    void Amp::set_tvp_en(bool en_)
    {
        tvp_en = en_;
    }

    ValveType Amp::get_tvp()
    {
        return tvp_val;
    }
    void Amp::set_tvp(ValveType tvp_)
    {
        tvp_val = tvp_;
    }

    bool Amp::get_mod_en()
    {
        return modulation_en;
    }
    void Amp::set_mod_en(bool en_)
    {
        modulation_en = en_;
    }
    bool Amp::get_delay_en()
    {
        return delay_en;
    }
    void Amp::set_delay_en(bool en_)
    {
        delay_en = en_;
    }
    bool Amp::get_reverb_en()
    {
        return reverb_en;
    }
    void Amp::set_reverb_en(bool en_)
    {
        reverb_en = en_;
    }

    ModulationType Amp::get_mod_type()
    {
        return modulation_type;
    }
    void Amp::set_mod_type(ModulationType type_)
    {
        modulation_type = type_;
    }

    DelayType Amp::get_delay_type()
    {
        return delay_type;
    }
    void Amp::set_delay_type(DelayType type_)
    {
        delay_type = type_;
    }

    ReverbType Amp::get_reverb_type()
    {
        return reverb_type;
    }
    void Amp::set_reverb_type(ReverbType type_)
    {
        reverb_type = type_;
    }

    Byte Amp::get_mod_val()
    {
        return modulation_val;
    }
    void Amp::set_mod_val(Byte val_)
    {
        modulation_val = val_;
    }

    Byte Amp::get_delay_val()
    {
        return delay_val;
    }
    void Amp::set_delay_val(Byte val_)
    {
        delay_val = val_;
    }

    Byte Amp::get_reverb_val()
    {
        return reverb_val;
    }
    void Amp::set_reverb_val(Byte val_)
    {
        reverb_val = val_;
    }

    Byte Amp::get_mod_level()
    {
        return modulation_level;
    }
    void Amp::set_mod_level(Byte level_)
    {
        modulation_level = level_;
    }

    Byte Amp::get_delay_level()
    {
        return delay_level;
    }
    void Amp::set_delay_level(Byte level_)
    {
        delay_level = level_;
    }

    Byte Amp::get_reverb_level()
    {
        return reverb_level;
    }
    void Amp::set_reverb_level(Byte level_)
    {
        reverb_level = level_;
    }

    void Amp::set_modulation(bool en_, ModulationType type_, Byte val_, Byte level_) {
        modulation_en = en_;
        modulation_type = type_;
        modulation_val = val_;
        modulation_level = level_;
    }
    void Amp::set_reverb(bool en_, ReverbType type_, Byte val_, Byte level_) {
        reverb_en = en_;
        reverb_type = type_;
        reverb_val = val_;
        reverb_level = level_;
    }
    void Amp::set_delay(bool en_, DelayType type_, Byte val_, Byte level_) {
        delay_en = en_;
        delay_type = type_;
        delay_val = val_;
        delay_level = level_;
    }

} // namespace BlackstarAmps