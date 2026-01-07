#include <Geode/Geode.hpp>
#include <Geode/modify/PauseLayer.hpp>

using namespace geode::prelude;

class $modify(ConfirmExitPauseLayer, PauseLayer) {
    struct Fields {
        bool m_exit_confirmed = false;
    };
    
    void onQuit(cocos2d::CCObject* sender) {
        
        if (!m_fields->m_exit_confirmed) {
            geode::log::debug("onQuit called");
            
            geode::createQuickPopup(
                "Exit level",
                "Are you sure you want to <cr>exit</c>?",
                "Cancel", "Exit",
                [this, &sender](auto, bool btn2) {
                    if (btn2) {
                        m_fields->m_exit_confirmed = true;
                        PauseLayer::onQuit(sender);
                    }
                }
            );
        }
        else {
            geode::log::debug("onQuit re-called");
            PauseLayer::onQuit(sender);
        }
    }
};
