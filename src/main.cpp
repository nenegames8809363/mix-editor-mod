#include <Geode/Geode.hpp>
#include <Geode/modify/PauseLayer.hpp>
#include <Geode/modify/PlayLayer.hpp>

using namespace geode::prelude;

// level da fase que tá rodando, salvo quando a fase carrega
static GJGameLevel* g_mixLevel = nullptr;

class $modify(MixPlayLayer, PlayLayer) {
    void setupHasCompleted() {
        PlayLayer::setupHasCompleted();
        g_mixLevel = m_level;
    }
};

class $modify(MixPauseLayer, PauseLayer) {
    void customSetup() {
        PauseLayer::customSetup();

        auto menu = this->getChildByID("right-button-menu");
        if (!menu) return;

        auto spr = CCSprite::createWithSpriteFrameName("GJ_editBtn_001.png");
        auto btn = CCMenuItemSpriteExtra::create(
            spr, this, menu_selector(MixPauseLayer::onMix)
        );
        btn->setID("mix-editor-button");
        menu->addChild(btn);
        menu->updateLayout();
    }

    void onMix(CCObject*) {
        if (!g_mixLevel) {
            FLAlertLayer::create("Mix Editor", "Level não encontrado.", "OK")->show();
            return;
        }

        auto scene = LevelEditorLayer::scene(g_mixLevel, false);
        CCDirector::sharedDirector()->replaceScene(
            CCTransitionFade::create(0.5f, scene)
        );
    }
};
