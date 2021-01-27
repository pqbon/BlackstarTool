#pragma once

#include <cstdint>
#include <string>
#include <array>
#include <memory>

#include <hidapi/hidapi.h>

#include "blackstaramp_types.h"

namespace BlackstarAmps
{
    //Black star amp HID reports defined as input and output arrays of 64B.
    //     wdeutsch@r2d2:~$ sudo usbhid-dump -e all
    // 001:003:000:DESCRIPTOR         1609523528.082706
    //  06 00 FF 09 01 A1 01 19 01 29 40 15 01 25 40 75
    //  08 95 40 81 00 19 01 29 40 91 00 C0

    // https://eleccelerator.com/usbdescreqparser/
    // 0x06, 0x00, 0xFF,  // Usage Page (Vendor Defined 0xFF00)
    // 0x09, 0x01,        // Usage (0x01)
    // 0xA1, 0x01,        // Collection (Application)
    // 0x19, 0x01,        //   Usage Minimum (0x01)
    // 0x29, 0x40,        //   Usage Maximum (0x40)
    // 0x15, 0x01,        //   Logical Minimum (1)
    // 0x25, 0x40,        //   Logical Maximum (64)
    // 0x75, 0x08,        //   Report Size (8)
    // 0x95, 0x40,        //   Report Count (64)
    // 0x81, 0x00,        //   Input (Data,Array,Abs,No Wrap,Linear,Preferred State,No Null Position)
    // 0x19, 0x01,        //   Usage Minimum (0x01)
    // 0x29, 0x40,        //   Usage Maximum (0x40)
    // 0x91, 0x00,        //   Output (Data,Array,Abs,No Wrap,Linear,Preferred State,No Null Position,Non-volatile)
    // 0xC0,              // End Collection

    constexpr unsigned short BSVendorID {0x27d4};
    constexpr unsigned short BSIDCore60H_DevID {0x0001};
    
    constexpr size_t hid_report_sz {64};

    using HidBuffer = std::array<Byte, hid_report_sz>;
    using HidBufferPnter = std::unique_ptr<HidBuffer>;

    enum class ControlBytePatches : Byte
    {
        SET_PATCH = 0x01,
        READ_NAME = 0x04,
        READ_PATCH = 0x05,
    };

    enum class ControlByteControls : Byte
    {
        VOICE = 0x01,
        GAIN = 0x02,
        VOLUME = 0x03,
        BASS = 0x04,
        MID = 0x05,
        TREBLE = 0x06,
        ISF = 0x07,
        TVP_VALUE = 0x08,

        M_RESONENCE = 0x0B,
        M_PRESENCE = 0x0C,
        M_VOLUME = 0x0D,

        TVP_ENABLE = 0x0E,
        MOD_ENABLE = 0x0F,
        DELAY_ENABLE = 0x10,
        REVERB_ENABLE = 0x11,

        MOD_TYPE = 0x12,
        MOD_VALUE = 0x15,
        MOD_TAPTEMPO = 0x16,

        DELAY_TYPE = 0x17,
        DELAY_VALUE = 0x1A,
        DELAY_TAPTEMPO = 0x1B,

        REVERB_TYPE = 0x1D,
        REVERB_VALUE = 0x20,

        // MOD_LEVEL,
        // DELAY_LEVEL,
        // REVERB_LEVEL,
        // MANUAL_ENABLE,
        // BANK,
        // CHANNEL1,
        // CHANNEL2,
        // CHANNEL3,
        // CHANNEL4,
    };

    enum class ControlPage : Byte
    {
        Patches = 0x2,
        Controls = 0x3,
    };

    class HIDAmp
    {
    public:
        HIDAmp();
        ~HIDAmp();
        HIDAmp(const HIDAmp &) = delete;
        HIDAmp(HIDAmp &&) noexcept = delete;
        HIDAmp & operator=(const HIDAmp &) = delete;
        HIDAmp & operator=(HIDAmp &&) noexcept = delete;

        void set_voice(const VoiceType voice_);
        void set_volume(const Byte val_);
        void set_gain(const Byte val_);
        void set_bass(const Byte val_);
        void set_mid(const Byte val_);
        void set_treble(const Byte val_);
        void set_isf(const Byte val_);
        void set_tvp(const ValveType val_);
        void set_tvp_en(const bool val_);
        void set_master_resonence(const Byte val_);
        void set_master_presence(const Byte val_);
        void set_master_volume(const Byte val_);
        void set_modulation_en(const bool val_);
        void set_delay_en(const bool val_);
        void set_reverb_en(const bool val_);

        void set_modulation_phaser(const Byte mix, const Byte depth, const Byte speed);
        void set_modulation_flanger(const Byte feedback, const Byte depth, const Byte speed);
        void set_modulation_chorus(const Byte mix, const Byte depth, const Byte speed);
        void set_modulation_tremolo(const Byte freq_mod_depth, const Byte amp_mod_depth, const Byte speed);
        
        void set_delay_linear(const Byte feedback, const Byte level, const Word time);
        void set_delay_analog(const Byte feedback, const Byte level, const Word time);
        void set_delay_tape(const Byte feedback, const Byte level, const Word time);
        void set_delay_multi(const Byte feedback, const Byte level, const Word time);

        void set_reverb_room(const Byte size, const Byte level);
        void set_reverb_hall(const Byte size, const Byte level);
        void set_reverb_spring(const Byte size, const Byte level);
        void set_reverb_plate(const Byte size, const Byte level);

        void set_patch(const Byte patch);
        void send_get_patch_name(const Byte patch);
        void send_get_patch(const Byte patch);

    private:
        template <ControlBytePatches cb_>
        void send_patch_cmd(const Byte patch);

        template <ModulationType mt_>
        void set_modulation(const Byte val0_, const Byte val1_, const Byte val2_);

        template <DelayType dt_>
        void set_delay(const Byte val0_, const Byte val1_, const Word val2_);

        template <ReverbType rt_>
        void set_reverb(const Byte val0_, const Byte val1_);

        template <ControlByteControls cb_, typename T>
        void set_hid_single_control(const T val_);
        template <ControlByteControls cb_>
        void set_hid_multi_control(const Byte val0_, const Byte val1_);

        HidBufferPnter get_hid_report();

        hid_device *dev_handle;
    };

} // namespace BlackstarAmps