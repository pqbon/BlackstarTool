#include <iostream>
#include <vector>
#include <chrono>
#include <thread>

#include "blackstaramp.h"
#include "blackstaramp_types.h"
#include "blackstaramp_control.h"
#include "blackstaramp_hid.h"


int main([[maybe_unused]] int argc, [[maybe_unused]] char *argv[]){
    BlackstarAmps::HIDAmp amp_hid;

    const std::vector<BlackstarAmps::VoiceType> voices {BlackstarAmps::VoiceType::BRIGHT, BlackstarAmps::VoiceType::WARM,
            BlackstarAmps::VoiceType::CHRUNCH, BlackstarAmps::VoiceType::SUPER_CRUNCH,
            BlackstarAmps::VoiceType::OD1, BlackstarAmps::VoiceType::OD2};

    // for(auto voice : voices){
    //     amp_hid.set_voice(voice);
    //     using namespace std::chrono_literals;
    //     std::this_thread::sleep_for(3s);
    //     //const auto start {std::chrono::steady_clock::now()};
    // }

    for(auto patch_id {1}; patch_id < 129; ++patch_id){
        std::string name {};
        amp_hid.get_patch_name(patch_id, name);
        std::cout << "Patch: " << patch_id << " Name Len: " << std::dec << name.size() << " - " << name << std::endl;
        amp_hid.get_patch(patch_id);
    }

}