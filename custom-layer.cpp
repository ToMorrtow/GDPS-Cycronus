#include "includes.h"
#include "custom-layer.hpp"
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <gd.h>
#include <windows.h>
#include <cocos2d.h>
#include "mod_utils.hpp"

using namespace cocos2d;

class GDPSTools : public cocos2d::CCLayer {

public:
    void Youtube(cocos2d::CCObject*) {
        CCApplication::sharedApplication()->openURL("https://www.youtube.com/@gdpscycronus");
    }

    void ModsList(cocos2d::CCObject*) {}

    void LevelStarter(cocos2d::CCObject*) {}

    void SeverDiscord(cocos2d::CCObject*) {
        CCApplication::sharedApplication()->openURL("https://discord.gg/sTUBweGFMF");
    }

    void InfoMod(cocos2d::CCObject*) {
         CreditosTw::create()->show();
    }
};

CustomLayer* CustomLayer::create() {
    auto ret = new CustomLayer();
    if (ret && ret->init()) {
        ret->autorelease();
    } else {
        // if `new` or `init` went wrong, delete the object and return a nullptr
        delete ret;
        ret = nullptr;
    }
    return ret;
}

bool CustomLayer::init() {

    auto TodoOwo = CCMenu::create();
    TodoOwo->setPosition({0, -16});

    auto Particulas = CCParticleSnow::create();
    this->addChild(Particulas);

    auto GDPSTools = CCLabelBMFont::create("GDPS Tools", "bigFont.fnt");
    GDPSTools->setScale({0.9f});

    auto Tool1 = CCLabelBMFont::create("Youtube", "bigFont.fnt");
    Tool1->setScale({0.8f});

    auto Tool2 = CCLabelBMFont::create("Mods List", "bigFont.fnt");
    Tool2->setScale({0.8f});

    auto Tool3 = CCLabelBMFont::create("Levels GL", "bigFont.fnt");
    Tool3->setScale({0.8f});

    auto Tool4 = CCLabelBMFont::create("Discord Server", "bigFont.fnt");
    Tool4->setScale({0.75f});

    auto SpriteInfo = CCSprite::create("GJ_infoBtn_001.png");
    SpriteInfo->setScale(0.7f);

    auto GDPSTool1Btn = gd::CCMenuItemSpriteExtra::create(Tool1, this, menu_selector(GDPSTools::Youtube));
    auto GDPSTool2Btn = gd::CCMenuItemSpriteExtra::create(Tool2, this, menu_selector(GDPSTools::ModsList));
    auto GDPSTool3Btn = gd::CCMenuItemSpriteExtra::create(Tool3, this, menu_selector(GDPSTools::LevelStarter));
    auto GDPSTool4Btn = gd::CCMenuItemSpriteExtra::create(Tool4, this, menu_selector(GDPSTools::SeverDiscord));
    auto InfoButton = gd::CCMenuItemSpriteExtra::create(SpriteInfo, this, menu_selector(GDPSTools::InfoMod));

    GDPSTool1Btn->setPosition({120.1, 192.98});
    GDPSTool2Btn->setPosition({274.44, 192.54});
    GDPSTool3Btn->setPosition({440.34, 189.7});
    GDPSTool4Btn->setPosition({295.5, 75.65});
    GDPSTools->setPosition({286.3, 277.74});
    InfoButton->setPosition({542 , 312});

    TodoOwo->addChild(GDPSTool1Btn);
    TodoOwo->addChild(GDPSTool2Btn);
    TodoOwo->addChild(GDPSTool3Btn);
    TodoOwo->addChild(GDPSTool4Btn);
    TodoOwo->addChild(InfoButton);
    TodoOwo->addChild(GDPSTools);
    this->addChild(TodoOwo);

    GDPSTool1Btn->runAction(CCRepeatForever::create(CCSequence::create(CCEaseSineInOut::create(CCMoveTo::create(1.5, {120.1, 192.98})), CCEaseSineInOut::create(CCMoveTo::create(1.5, {120.1, 189.98})), nullptr)));
    GDPSTool2Btn->runAction(CCRepeatForever::create(CCSequence::create(CCEaseSineInOut::create(CCMoveTo::create(1.5, {274.44, 192.98})), CCEaseSineInOut::create(CCMoveTo::create(1.5, {274.44, 189.98})), nullptr)));
    GDPSTool3Btn->runAction(CCRepeatForever::create(CCSequence::create(CCEaseSineInOut::create(CCMoveTo::create(1.5, {440.34 , 192.98})), CCEaseSineInOut::create(CCMoveTo::create(1.5, {440.34 , 189.98})), nullptr)));
    //GDPSTools->runAction(CCRepeatForever::create(CCSequence::create(CCEaseSineInOut::create(CCMoveTo::create(1.5, {286.3, 277.74})), CCEaseSineInOut::create(CCMoveTo::create(1.5, {286.3, 275.74})), nullptr)));

    auto sideArt = CCSprite::create("GJ_sideArt_001.png");
    sideArt->setPosition({534 , 34});
    sideArt->setScale(1.0f);
    sideArt->setScaleX(-1.0f);
    addChild(sideArt);

    auto sideArt2 = CCSprite::create("GJ_sideArt_001.png");
    sideArt2->setPosition({35 , 34});
    sideArt2->setScale(1.0f);
    addChild(sideArt2);

    auto backgroundSprite = CCSprite::create("GJ_gradientBG.png");
    
    auto winSize = CCDirector::sharedDirector()->getWinSize();
    auto size = backgroundSprite->getContentSize();

    backgroundSprite->setScaleX(winSize.width / size.width);
    backgroundSprite->setScaleY(winSize.height / size.height);
    
    backgroundSprite->setAnchorPoint({0, 0});
    
    backgroundSprite->setColor({ 0, 102, 255 });
    
    backgroundSprite->setZOrder(-1);
    addChild(backgroundSprite);
    
    gd::GameManager::sharedState()->fadeInMusic("menuLoop2.mp3");

    auto button = gd::CCMenuItemSpriteExtra::create(

        CCSprite::createWithSpriteFrameName("GJ_arrow_01_001.png"),
        this,
        menu_selector(CustomLayer::backButtonCallback)
    );

    auto menu = CCMenu::create();
    menu->addChild(button);
    
    menu->setPosition({25, winSize.height - 25});

    addChild(menu);

    setKeypadEnabled(true);

    return true;
}

void CustomLayer::keyBackClicked() {
    CCDirector::sharedDirector()->popSceneWithTransition(0.5f, PopTransition::kPopTransitionFade);
}

void CustomLayer::backButtonCallback(CCObject* object) {
    keyBackClicked();
}

void CustomLayer::switchToCustomLayerButton(CCObject* object) {
    auto layer = CustomLayer::create();
    auto scene = CCScene::create();
    scene->addChild(layer);
    
    auto transition = CCTransitionFade::create(0.5f, scene);
    
    CCDirector::sharedDirector()->pushScene(transition);
}

bool CreditosTw::init() {
	auto winSize = CCDirector::sharedDirector()->getWinSize();

	if (!this->initWithColor({ 0, 0, 0, 75 })) return false;
	m_pLayer = CCLayer::create();
	this->addChild(m_pLayer);

	auto bg = CCScale9Sprite::create("GJ_square02.png", { 0.0f, 0.0f, 80.0f, 80.0f });
	bg->setContentSize({ 380.0f, 103.0f });
	bg->setPosition(winSize.width / 2, winSize.height / 2);
	m_pLayer->addChild(bg);

	m_pButtonMenu = CCMenu::create();
	m_pLayer->addChild(m_pButtonMenu,5);

	auto textBg = CCScale9Sprite::create("square02_001.png", { 0.0f, 0.0f, 80.0f, 80.0f });
	textBg->setPosition({330.1, 160});
	textBg->setContentSize({ 320.0f, 100.f });
	textBg->setOpacity(60);
	textBg->setScaleX({0.840});
	textBg->setScaleY({0.808});
	m_pLayer->addChild(textBg);

	auto Titulo = CCLabelBMFont::create("The Keymaster", "bigFont.fnt", 320, kCCTextAlignmentCenter);
	Titulo->setScale(0.5f);
	Titulo->setPosition({265.24, 189.3});
	m_pLayer->addChild(Titulo);

	auto SpriteLogo = CCSprite::create("dialogIcon_002.png");
    SpriteLogo->setPosition({146.49, 160.0});
    SpriteLogo->setScale({1.1f});
	m_pLayer->addChild(SpriteLogo);

	auto Texto1 = CCLabelBMFont::create("Mod Developeado by: ToMorritow", "chatFont.fnt");
	Texto1->setPosition({32.99, -5.3});

	m_pButtonMenu->addChild(Texto1);

	//this->runAction(CCSequence::create(CCDelayTime::create(2.70f), CCCallFuncO::create(this, callfuncO_selector(CreditosTw::onOk), this), nullptr));

	this->setKeypadEnabled(true);
	this->setTouchEnabled(true);

	return true;
}

void CreditosTw::onOk(cocos2d::CCObject*) {
	this->removeFromParentAndCleanup(true);
	//menu_selector(NuevoLayer::switchToCustomLayerButton);
}

CreditosTw* CreditosTw::create() {
	CreditosTw* pRet = new CreditosTw();
	if (pRet && pRet->init()) {
		pRet->autorelease();
		return pRet;
	}
	else {
		CC_SAFE_DELETE(pRet);
		return nullptr;
	}
}