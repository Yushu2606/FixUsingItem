/**
 * @file plugin.cpp
 * @brief The main file of the plugin
 */

#include <llapi/HookAPI.h>
#include <llapi/mc/Player.hpp>
#include <llapi/mc/ItemStack.hpp>

std::map<long long, int> data{};

TInstanceHook(void, "?startUsingItem@Player@@QEAAXAEBVItemStack@@H@Z", Player, ItemStack const& a1, int a2) {
    data[getOrCreateUniqueID()] = getSelectedItemSlot();
    original(this, a1, a2);
}

TInstanceHook(void, "?stopUsingItem@Player@@QEAAXXZ", Player) {
    data.erase(getOrCreateUniqueID());
    original(this);
}

TInstanceHook(void, "?releaseUsingItem@Player@@QEAAXXZ", Player) {
    if (data[getOrCreateUniqueID()] == getSelectedItemSlot()) {
        original(this);
        return;
    }
    stopUsingItem();
    original(this);
}
