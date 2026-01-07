#include <Geode/Geode.hpp>
#include <Geode/modify/PauseLayer.hpp>

using namespace geode::prelude;

class $modify(ConfirmExitPauseLayer, PauseLayer) {
    struct Fields {
        uint8_t m_exit_confirmed = 0;
    };
    
    void onQuit(cocos2d::CCObject* sender) {
        /* ok so this is a stupid hacky fix.
         * basically for some ungodly reason the popup lambda calls
         * ConfirmExitPauseLayer::onQuit instead of PauseLayer::onQuit like it should.
         * the only way i could figure out how to fix this was to accept this and
         * set a separate variable to detect if we've already confirmed, and then call the function again.
         */
        if (m_fields->m_exit_confirmed == 0) {
            geode::log::debug("onQuit called");
            
            geode::createQuickPopup(
                "Exit level",
                "Are you sure you want to <cr>exit</c>?",
                "Cancel", "Exit",
                [this, &sender](auto, bool btn2) {
                    if (btn2) {
                        m_fields->m_exit_confirmed++;
                        PauseLayer::onQuit(sender);
                    }
                }
            );
        }
        else if (m_fields->m_exit_confirmed == 1) {
            geode::log::debug("onQuit re-called");
            m_fields->m_exit_confirmed++;
            PauseLayer::onQuit(sender);
            
        }
        else {
            geode::log::warn("Quit button broke! that's Not Good");
        }
        
    }
};
