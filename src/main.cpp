#include <Geode/Geode.hpp>
#include <Geode/modify/PauseLayer.hpp>

using namespace geode::prelude;

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
        // TODO: pausar, guardar o estado e abrir o LevelEditorLayer
        FLAlertLayer::create("Mix Editor", "Botão funcionando!", "OK")->show();
    }
};
