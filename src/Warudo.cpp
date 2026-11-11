#include <Geode/Geode.hpp>
#include <Geode/modify/PlayLayer.hpp>
#include <Geode/modify/PauseLayer.hpp>

using namespace geode::prelude;

// ZA WARUDO: quando true, o tempo da fase para
static bool g_frozen = false;

class $modify(WarudoPlayLayer, PlayLayer) {
    struct Fields {
        CCMenuItemSpriteExtra* m_unfreezeBtn = nullptr;
    };

    void setupHasCompleted() {
        PlayLayer::setupHasCompleted();
        g_frozen = false;

        // botão pra descongelar, fica no canto da tela
        auto menu = CCMenu::create();
        auto spr = CCSprite::createWithSpriteFrameName("GJ_editBtn_001.png");
        auto btn = CCMenuItemSpriteExtra::create(
            spr, this, menu_selector(WarudoPlayLayer::onUnfreeze)
        );
        btn->setID("warudo-unfreeze");
        menu->addChild(btn);
        menu->setPosition({40.f, 40.f});
        btn->setVisible(false);
        this->addChild(menu, 1000);
        m_fields->m_unfreezeBtn = btn;
    }

    void update(float dt) {
        if (g_frozen) return; // congela a fase
        PlayLayer::update(dt);
    }

    void onUnfreeze(CCObject*) {
        g_frozen = false;
        if (m_fields->m_unfreezeBtn) m_fields->m_unfreezeBtn->setVisible(false);
    }
};

class $modify(WarudoPauseLayer, PauseLayer) {
    void customSetup() {
        PauseLayer::customSetup();

        auto menu = this->getChildByID("right-button-menu");
        if (!menu) return;

        auto spr = CCSprite::createWithSpriteFrameName("GJ_editBtn_001.png");
        auto btn = CCMenuItemSpriteExtra::create(
            spr, this, menu_selector(WarudoPauseLayer::onWarudo)
        );
        btn->setID("warudo-button");
        menu->addChild(btn);
        menu->updateLayout();
    }

    void onWarudo(CCObject*) {
        g_frozen = true;

        // mostra o botão de descongelar na fase
        if (auto play = PlayLayer::get()) {
            if (auto m = static_cast<WarudoPlayLayer*>(play)->m_fields->m_unfreezeBtn) {
                m->setVisible(true);
            }
        }

        this->onResume(nullptr);
    }
};
