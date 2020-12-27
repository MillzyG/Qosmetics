#include "UI/Saber/SaberSettingsViewController.hpp"
#include "config.hpp"
#include "Data/Descriptor.hpp"

#include "UnityEngine/RectOffset.hpp"
#include "UnityEngine/RectTransform.hpp"
#include "UnityEngine/Rect.hpp"
#include "UnityEngine/Vector2.hpp"
#include "UnityEngine/UI/Image.hpp"
#include "UnityEngine/UI/Toggle.hpp"
#include "UnityEngine/UI/Toggle_ToggleEvent.hpp"
#include "UnityEngine/UI/LayoutElement.hpp"
#include "UnityEngine/Events/UnityAction.hpp"
#include "UnityEngine/Events/UnityAction_1.hpp"
#include "HMUI/ScrollView.hpp"
#include "HMUI/ModalView.hpp"
#include "HMUI/Touchable.hpp"
#include "HMUI/InputFieldView.hpp"

#include "questui/shared/BeatSaberUI.hpp"
#include "questui/shared/CustomTypes/Components/ExternalComponents.hpp"
#include "questui/shared/CustomTypes/Components/Backgroundable.hpp"

#include "Logging/UILogger.hpp"
#define INFO(value...) UILogger::GetLogger().info(value)
extern config_t config;
DEFINE_CLASS(Qosmetics::SaberSettingsViewController);

using namespace QuestUI;
using namespace UnityEngine;
using namespace UnityEngine::UI;
using namespace UnityEngine::Events;
using namespace HMUI;

namespace Qosmetics
{
    void SaberSettingsViewController::DidDeactivate(bool removedFromHierarchy, bool screenSystemDisabling)
    {
        
    }

    void SaberSettingsViewController::DidActivate(bool firstActivation, bool addedToHierarchy, bool screenSystemEnabling)
    {
        if (firstActivation)
        {
            get_gameObject()->AddComponent<Touchable*>();
            GameObject* container = BeatSaberUI::CreateScrollableSettingsContainer(get_transform());
            QuestUI::IncrementSetting* saberWidthSetting = BeatSaberUI::CreateIncrementSetting(container->get_transform(), "Saber Width", 2, 0.05f, config.saberConfig.saberWidth, il2cpp_utils::MakeDelegate<UnityAction_1<float>*>(classof(UnityAction_1<float>*), this, +[](SaberSettingsViewController* view, float value) {
                    if (value >= 0.0f) config.saberConfig.saberWidth = value;
                    SaveConfig();
                }));
            BeatSaberUI::AddHoverHint(saberWidthSetting->get_gameObject(), "Makes the saber more or less wide in the <- -> directions, values below 0 get ignored");
            BeatSaberUI::CreateToggle(container->get_transform(), "Override Trail Length", config.saberConfig.overrideTrailLength, il2cpp_utils::MakeDelegate<UnityAction_1<bool>*>(classof(UnityAction_1<bool>*), this, +[](SaberSettingsViewController* view, bool value) { 
                    config.saberConfig.overrideTrailLength = value;
                    SaveConfig();
                }));
            QuestUI::IncrementSetting* trailLengthSetting = BeatSaberUI::CreateIncrementSetting(container->get_transform(), "Trail Lenght", 0, 1.0f, config.saberConfig.trailLength, il2cpp_utils::MakeDelegate<UnityAction_1<float>*>(classof(UnityAction_1<float>*), this, +[](SaberSettingsViewController* view, float value) {
                    if (value >= 0.0f) config.saberConfig.trailLength = value;
                    SaveConfig();
                }));
            BeatSaberUI::AddHoverHint(trailLengthSetting->get_gameObject(), "The overridden length of the trail, values below 0 get ignored");
            UnityEngine::UI::Toggle* whiteStepToggle = BeatSaberUI::CreateToggle(container->get_transform(), "Override White Step Value", config.saberConfig.overrideWhiteStep, il2cpp_utils::MakeDelegate<UnityAction_1<bool>*>(classof(UnityAction_1<bool>*), this, +[](SaberSettingsViewController* view, bool value) { 
                    config.saberConfig.overrideWhiteStep = value;
                    SaveConfig();
                }));
            BeatSaberUI::AddHoverHint(whiteStepToggle->get_gameObject(), "Override the size of the \"white\" part of the saber trail, set to 0 for off, values below 0 or above 1 get ignored");
            QuestUI::IncrementSetting* whiteStepSetting = BeatSaberUI::CreateIncrementSetting(container->get_transform(), "White Step Amount", 2, 0.05f, config.saberConfig.whiteStep, il2cpp_utils::MakeDelegate<UnityAction_1<float>*>(classof(UnityAction_1<float>*), this, +[](SaberSettingsViewController* view, float value) {
                    if (value >= 0.0f && value <= 1.0f) config.saberConfig.whiteStep = value;
                    SaveConfig();
                }));
            BeatSaberUI::CreateToggle(container->get_transform(), "Enable Menu Pointer", config.saberConfig.enableMenuPointer, il2cpp_utils::MakeDelegate<UnityAction_1<bool>*>(classof(UnityAction_1<bool>*), this, +[](SaberSettingsViewController* view, bool value) { 
                    config.saberConfig.enableMenuPointer = value;
                    SaveConfig();
                }));
            QuestUI::IncrementSetting* trailTypeSetting = BeatSaberUI::CreateIncrementSetting(container->get_transform(), "Trail Type", 0, 1.0f, (int)config.saberConfig.trailType, il2cpp_utils::MakeDelegate<UnityAction_1<float>*>(classof(UnityAction_1<float>*), this, +[](SaberSettingsViewController* view, float value) {
                    switch ((int)value)
                    {
                        case 0:
                            config.saberConfig.trailType = TrailType::custom;
                            break;
                        case 1:
                            config.saberConfig.trailType = TrailType::baseGame;
                            break;
                        case 2:
                            config.saberConfig.trailType = TrailType::none;
                            break;
                        default:
                            break;
                    }
                    SaveConfig();
                }));
            BeatSaberUI::AddHoverHint(trailTypeSetting->get_gameObject(), "Sets the trail type, 0 means the attached trails, 1 means base game, 2 means no trails, other values get ignored");
        }
    }
}