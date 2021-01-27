#include <cstdint>
#include <string>
#include <array>
#include <memory>
#include <iostream>

#include <exception>

#include <hidapi/hidapi.h>

#include "blackstaramp.h"
#include "blackstaramp_types.h"
#include "blackstaramp_hid.h"

namespace BlackstarAmps
{
    HIDAmp::HIDAmp() : dev_handle {nullptr} {
        int res {};
        constexpr int MaxStr {255};
        wchar_t wstr[MaxStr];

	    res = hid_init();
        if(res < 0){
            goto error;
        }

	    // Open the device using the VID, PID,
	    // and optionally the Serial number.
	    dev_handle = hid_open(BSVendorID, BSIDCore60H_DevID, nullptr);

        if(dev_handle == nullptr){
            goto error;
        }

	    // Read the Manufacturer String
	    res = hid_get_manufacturer_string(dev_handle, wstr, MaxStr);
        if(res < 0){
            goto error;
        }
	    std::wcout << L"Manufacturer String: " << *wstr << std::endl;

	    // Read the Product String
	    res = hid_get_product_string(dev_handle, wstr, MaxStr);
        if(res < 0){
            goto error;
        }
	    std::wcout << L"Product String: " <<  *wstr << std::endl;

	    // Read the Serial Number String
	    res = hid_get_serial_number_string(dev_handle, wstr, MaxStr);
        if(res < 0){
            goto error;
        }
	    std::wcout << L"Serial Number String: " <<  static_cast<unsigned int>(wstr[0]) << " " <<  *wstr << std::endl;

        return;
error:
        throw std::runtime_error("HID Constructor Failed...");
    }

    HIDAmp::~HIDAmp() {
	    hid_close(dev_handle);

	    /* Free static HIDAPI objects. */
	    hid_exit();
    }

    void HIDAmp::set_voice(const VoiceType voice_) {
        set_hid_single_control<ControlByteControls::VOICE>(voice_);
    }

    void HIDAmp::set_volume(const Byte val_) {
        set_hid_single_control<ControlByteControls::VOLUME>(val_);
    }

    void HIDAmp::set_gain(const Byte val_) {
        set_hid_single_control<ControlByteControls::GAIN>(val_);
    }

    void HIDAmp::set_bass(const Byte val_) {
        set_hid_single_control<ControlByteControls::BASS>(val_);
    }

    void HIDAmp::set_mid(const Byte val_) {
        set_hid_single_control<ControlByteControls::MID>(val_);
    }

    void HIDAmp::set_treble(const Byte val_) {
        set_hid_single_control<ControlByteControls::TREBLE>(val_);
    }

    void HIDAmp::set_isf(const Byte val_) {
        set_hid_single_control<ControlByteControls::ISF>(val_);
    }

    void HIDAmp::set_tvp(const ValveType val_) {
        set_hid_single_control<ControlByteControls::TVP_VALUE>(val_);
    }

    void HIDAmp::set_tvp_en(const bool val_) {
        set_hid_single_control<ControlByteControls::TVP_ENABLE>(val_);
    }

    void HIDAmp::set_master_resonence(const Byte val_){
        set_hid_single_control<ControlByteControls::M_RESONENCE>(val_);
    }

    void HIDAmp::set_master_presence(const Byte val_){
        set_hid_single_control<ControlByteControls::M_PRESENCE>(val_);
    }

    void HIDAmp::set_master_volume(const Byte val_){
        set_hid_single_control<ControlByteControls::M_VOLUME>(val_);
    }

    void HIDAmp::set_modulation_en(const bool val_) {
        set_hid_single_control<ControlByteControls::MOD_ENABLE>(val_);
    }

    void HIDAmp::set_delay_en(const bool val_) {
        set_hid_single_control<ControlByteControls::DELAY_ENABLE>(val_);
    }

    void HIDAmp::set_reverb_en(const bool val_) {
        set_hid_single_control<ControlByteControls::REVERB_ENABLE>(val_);
    }

    void HIDAmp::set_modulation_phaser(const Byte mix, const Byte depth, const Byte speed){
        set_modulation<ModulationType::PHASER>(mix, depth, speed);
    }
    
    void HIDAmp::set_modulation_flanger(const Byte feedback, const Byte depth, const Byte speed){
        set_modulation<ModulationType::FLANGER>(feedback, depth, speed);
    }

    void HIDAmp::set_modulation_chorus(const Byte mix, const Byte depth, const Byte speed){
        set_modulation<ModulationType::CHORUS>(mix, depth, speed);
    }

    void HIDAmp::set_modulation_tremolo(const Byte freq_mod_depth, const Byte amp_mod_depth, const Byte speed){
        set_modulation<ModulationType::TREMELO>(freq_mod_depth, amp_mod_depth, speed);
    }
    
    
    void HIDAmp::set_delay_linear(const Byte feedback, const Byte level, const Word time){
        set_delay<DelayType::LINEAR>(feedback, level, time);
    }

    void HIDAmp::set_delay_analog(const Byte feedback, const Byte level, const Word time){
        set_delay<DelayType::ANALOG>(feedback, level, time);
    }

    void HIDAmp::set_delay_tape(const Byte feedback, const Byte level, const Word time){
        set_delay<DelayType::TAPE>(feedback, level, time);
    }

    void HIDAmp::set_delay_multi(const Byte feedback, const Byte level, const Word time){
        set_delay<DelayType::MULTI>(feedback, level, time);
    }


    void HIDAmp::set_reverb_room(const Byte size, const Byte level){
        set_reverb<ReverbType::ROOM>(size, level);
    }

    void HIDAmp::set_reverb_hall(const Byte size, const Byte level){
        set_reverb<ReverbType::HALL>(size, level);
    }

    void HIDAmp::set_reverb_spring(const Byte size, const Byte level){
        set_reverb<ReverbType::SPRING>(size, level);
    }

    void HIDAmp::set_reverb_plate(const Byte size, const Byte level){
        set_reverb<ReverbType::PLATE>(size, level);
    }

    void HIDAmp::set_patch(const Byte patch){
        send_patch_cmd<ControlBytePatches::SET_PATCH>(patch);            
    }

    void HIDAmp::send_get_patch_name(const Byte patch){
        send_patch_cmd<ControlBytePatches::READ_NAME>(patch);
    }

    void HIDAmp::send_get_patch(const Byte patch){
        send_patch_cmd<ControlBytePatches::READ_PATCH>(patch);
    }

    template <ControlBytePatches cb_>
    void HIDAmp::send_patch_cmd(const Byte patch){
        HidBufferPnter hidbuf { std::make_unique<HidBuffer>() };

        hidbuf->at(0) = static_cast<Byte>(ControlPage::Patches);
        hidbuf->at(1) = static_cast<Byte>(cb_);
        hidbuf->at(2) = static_cast<Byte>(patch);

        hid_write(dev_handle, hidbuf->data(), hidbuf->size());            
    }

    template <ModulationType mt_>
    void HIDAmp::set_modulation(const Byte val0_, const Byte val1_, const Byte val2_){
        set_hid_multi_control<ControlByteControls::MOD_TYPE>(static_cast<Byte>(mt_), val0_);
        set_hid_single_control<ControlByteControls::MOD_VALUE>(val1_);
        set_hid_single_control<ControlByteControls::MOD_TAPTEMPO>(val2_);
    }

    template <DelayType dt_>
    void HIDAmp::set_delay(const Byte val0_, const Byte val1_, const Word val2_){
        set_hid_multi_control<ControlByteControls::DELAY_TYPE>(static_cast<Byte>(dt_), val0_);
        set_hid_single_control<ControlByteControls::DELAY_VALUE>(val1_);
        set_hid_multi_control<ControlByteControls::DELAY_TAPTEMPO>(static_cast<Byte>(val2_ & 0xff), static_cast<Byte>((val2_ >> 8) & 0xff));
    }

    template <ReverbType rt_>
    void HIDAmp::set_reverb(const Byte val0_, const Byte val1_){
        set_hid_multi_control<ControlByteControls::REVERB_TYPE>(static_cast<Byte>(rt_), val0_);
        set_hid_single_control<ControlByteControls::REVERB_VALUE>(val1_);
    }

    template <ControlByteControls cb_, typename T>
    void HIDAmp::set_hid_single_control(const T val_){
        HidBufferPnter hidbuf { std::make_unique<HidBuffer>() };

        hidbuf->at(0) = static_cast<Byte>(ControlPage::Controls);
        hidbuf->at(1) = static_cast<Byte>(cb_);
        hidbuf->at(2) = static_cast<Byte>(0x0);
        hidbuf->at(3) = static_cast<Byte>(0x1); //Size...
        hidbuf->at(4) = static_cast<Byte>(val_);

        hid_write(dev_handle, hidbuf->data(), hidbuf->size());            
    }

    template <ControlByteControls cb_>
    void HIDAmp::set_hid_multi_control(const Byte val0_, const Byte val1_){
        HidBufferPnter hidbuf { std::make_unique<HidBuffer>() };

        hidbuf->at(0) = static_cast<Byte>(ControlPage::Controls);
        hidbuf->at(1) = static_cast<Byte>(cb_);
        hidbuf->at(2) = static_cast<Byte>(0x0);
        hidbuf->at(3) = static_cast<Byte>(0x2); //Size...
        hidbuf->at(4) = static_cast<Byte>(val0_);
        hidbuf->at(4) = static_cast<Byte>(val1_);

        hid_write(dev_handle, hidbuf->data(), hidbuf->size());            
    }

    HidBufferPnter HIDAmp::get_hid_report(){
        HidBufferPnter hidbuf { std::make_unique<HidBuffer>() };
        int res {};

        res = hid_read(dev_handle, hidbuf->data(), hidbuf->size());

        if(res != hid_report_sz){
            hidbuf.release();
            hidbuf = nullptr;
        }

        return hidbuf;
    }

}  // namespace BlackstarAmps