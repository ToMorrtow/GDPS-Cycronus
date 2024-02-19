#include <random>
#include <windows.h>
#pragma warning(push, 0)
#include <cocos2d.h>
#pragma warning(pop)
#include "LoadingLayer.hpp"
#include "custom-layer.hpp"
#include "includes.h"
#include <windows.h>
#include <shellapi.h>
#include <MinHook.h>
#include <gd.h>
#include <ctime>
#include <thread>
#include <chrono>

///Para iniciar xd cmake --build build --config Release --target ALL_BUILD

// porsiacaso cmake -DCMAKE_BUILD_TYPE=Release -T host=x86

bool write_bytes(
    const std::uintptr_t address,
    std::vector<uint8_t> const& bytes)
{
    return WriteProcessMemory(
        GetCurrentProcess(),
        reinterpret_cast<LPVOID>(address),
        bytes.data(),
        bytes.size(),
        nullptr);
}

class AkiomaeCrement : public cocos2d::CCLayer {

public:
    void ToMorritow(cocos2d::CCObject* pSender) {
        auto GM = gd::GameManager::sharedState();
        gd::FLAlertLayer::create(nullptr, "GDPS", "Ok", nullptr, "Mod creado por ToMorritow")->show();
    }
};

bool (__thiscall* MenuLayer_init)(CCLayer* self);
bool __fastcall MenuLayer_init_H(CCLayer* self, void*) {

    if (!MenuLayer_init(self)) return false;

    auto winSize = CCDirector::sharedDirector()->getWinSize();

    auto MenuBotones = reinterpret_cast<CCMenu*>(self->getChildren()->objectAtIndex(2));
    auto MenuBackground = reinterpret_cast<CCMenu*>(self->getChildren()->objectAtIndex(0));
    //auto BackgroundBG = reinterpret_cast<gd::CCMenuItemSpriteExtra*>(MenuBackground->getChildren()->objectAtIndex(0));

    auto uwu = CCLabelBMFont::create("Mods Modificados ToMorritowCode", "chatFont.fnt");
    uwu->setScale({0.6f});

    auto button1 = gd::CCMenuItemSpriteExtra::create(
        uwu,
        self,
        menu_selector(AkiomaeCrement::ToMorritow)
    );

    button1->setPosition({0, 138});
    MenuBotones->addChild(button1);

    //BackgroundBG->runAction(CCRepeatForever::create(CCSequence::create(
    //CCEaseSineInOut::create(CCScaleTo::create(0.40000001, 1.0, 1.0)), 
    //CCEaseSineInOut::create(CCScaleTo::create(0.40000001, 1.5, 1.5)), nullptr)));

    //auto BGSprite = CCSprite::createWithSpriteFrameName("game_bg_01_001.png");
    //BGSprite->setScale({1.181f});

    //BackgroundBG->setNormalImage(BGSprite);
    //BackgroundBG->setSelectedImage(BGSprite);

    return true;
}

bool (__thiscall* CreatorLayer_init)(CCLayer* self);
bool __fastcall CreatorLayer_init_H(CCLayer* self, void*) {

    if (!CreatorLayer_init(self)) return false;

    auto allBtns = reinterpret_cast<CCMenu*>(self->getChildren()->objectAtIndex(1));

    auto themap = CCSprite::createWithSpriteFrameName("GJ_eventBtn_001.png");
    themap->setScale(0.85f);
    auto TheMapBtn = gd::CCMenuItemSpriteExtra::create(themap, self, menu_selector(CustomLayer::switchToCustomLayerButton));
    allBtns->addChild(TheMapBtn);

    // Botones de la CreatorLayer
    auto CreateBtn = reinterpret_cast<gd::CCMenuItemSpriteExtra*>(allBtns->getChildren()->objectAtIndex(0));
    auto SaveBtn = reinterpret_cast<gd::CCMenuItemSpriteExtra*>(allBtns->getChildren()->objectAtIndex(1));
    auto ScoresBtn = reinterpret_cast<gd::CCMenuItemSpriteExtra*>(allBtns->getChildren()->objectAtIndex(2));
    auto QuestsBtn = reinterpret_cast<gd::CCMenuItemSpriteExtra*>(allBtns->getChildren()->objectAtIndex(3));
    auto DailyBtn = reinterpret_cast<gd::CCMenuItemSpriteExtra*>(allBtns->getChildren()->objectAtIndex(4));
    auto WeeklyBtn = reinterpret_cast<gd::CCMenuItemSpriteExtra*>(allBtns->getChildren()->objectAtIndex(5));
    auto SearchBtn = reinterpret_cast<gd::CCMenuItemSpriteExtra*>(allBtns->getChildren()->objectAtIndex(9));
    auto GauntletshBtn = reinterpret_cast<gd::CCMenuItemSpriteExtra*>(allBtns->getChildren()->objectAtIndex(10));
    auto mapPackBtn = reinterpret_cast<gd::CCMenuItemSpriteExtra*>(allBtns->getChildren()->objectAtIndex(8));
    auto TheSafeBtn = reinterpret_cast<gd::CCMenuItemSpriteExtra*>(allBtns->getChildren()->objectAtIndex(6));
    auto feacturedBtn = reinterpret_cast<gd::CCMenuItemSpriteExtra*>(allBtns->getChildren()->objectAtIndex(7));

    CreateBtn->setPosition({-150, 97});
    SaveBtn->setPosition({-50, 97});
    ScoresBtn->setPosition({50, 97});
    QuestsBtn->setPosition({150, 97});

    TheMapBtn->setPosition({-150, 0});

    return true;
}

const char* (__thiscall* LoadingLayer_getString_org)(LoadingLayer*);
const char* __fastcall LoadingLayer_getString_h(LoadingLayer* self, void*) {

    return "Holaw";
}

DWORD WINAPI thread_func(void* hModule) {

    MH_Initialize();

    auto base = reinterpret_cast<uintptr_t>(GetModuleHandle(0));

    MH_CreateHook( // MenuLayer
        reinterpret_cast<void*>(base + 0x1907b0),
        reinterpret_cast<void*>(&MenuLayer_init_H),
        reinterpret_cast<void**>(&MenuLayer_init)
    );

    MH_CreateHook(
        reinterpret_cast<void*>(base + 0x18cf40),
        reinterpret_cast<void*>(&LoadingLayer_getString_h),
        reinterpret_cast<void**>(&LoadingLayer_getString_org)
    );

    MH_CreateHook(
        reinterpret_cast<void*>(base + 0x4DE40),
        reinterpret_cast<void*>(&CreatorLayer_init_H),
        reinterpret_cast<void**>(&CreatorLayer_init)
    );

    MH_EnableHook(MH_ALL_HOOKS);


    return 0;
}

BOOL APIENTRY DllMain(HMODULE handle, DWORD reason, LPVOID reserved) {
    if (reason == DLL_PROCESS_ATTACH) {
        auto h = CreateThread(0, 0, thread_func, handle, 0, 0);
        if (h)
            CloseHandle(h);
        else
            return FALSE;
    }
    return TRUE;
}