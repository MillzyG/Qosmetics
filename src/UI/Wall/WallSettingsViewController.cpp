#include "UI/Wall/WallSettingsViewController.hpp"
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
#include "UI/Wall/WallPreviewViewController.hpp"
#include "Qosmetic/QuestWall.hpp"

#include "Logging/UILogger.hpp"
#define INFO(value...) UILogger::GetLogger().WithContext("Wall Settings").info(value)
#define ERROR(value...) UILogger::GetLogger().WithContext("Wall Settings").error(value)
extern config_t config;
DEFINE_CLASS(Qosmetics::WallSettingsViewController);

using namespace QuestUI;
using namespace UnityEngine;
using namespace UnityEngine::UI;
using namespace UnityEngine::Events;
using namespace HMUI;

namespace Qosmetics
{
    void WallSettingsViewController::DidDeactivate(bool removedFromHierarchy, bool screenSystemDisabling)
    {
        SaveConfig();
    }

    void WallSettingsViewController::DidActivate(bool firstActivation, bool addedToHierarchy, bool screenSystemEnabling)
    {
        if (firstActivation)
        {
            get_gameObject()->AddComponent<Touchable*>();
            GameObject* container = BeatSaberUI::CreateScrollableSettingsContainer(get_transform());
            
            ExternalComponents* externalComponents = container->GetComponent<ExternalComponents*>();
            RectTransform* scrollTransform = externalComponents->Get<RectTransform*>();
            scrollTransform->set_sizeDelta(UnityEngine::Vector2(0.0f, 0.0f));
            
            BeatSaberUI::CreateToggle(container->get_transform(), "Force Disable Fake Glow", config.wallConfig.forceFakeGlowOff, il2cpp_utils::MakeDelegate<UnityAction_1<bool>*>(classof(UnityAction_1<bool>*), this, +[](WallSettingsViewController* view, bool value) { 
                    config.wallConfig.forceFakeGlowOff = value;
                    SaveConfig();
                    QuestWall::SelectionDefinitive();
                    WallPreviewViewController* previewController = Object::FindObjectOfType<WallPreviewViewController*>();//
                    if (previewController) previewController->UpdatePreview();
                    else ERROR("Couldn't find preview controller");
                }));
            BeatSaberUI::CreateToggle(container->get_transform(), "Force Core Off", config.wallConfig.forceCoreOff, il2cpp_utils::MakeDelegate<UnityAction_1<bool>*>(classof(UnityAction_1<bool>*), this, +[](WallSettingsViewController* view, bool value) { 
                    config.wallConfig.forceCoreOff = value;
                    SaveConfig();
                    QuestWall::SelectionDefinitive();
                    WallPreviewViewController* previewController = Object::FindObjectOfType<WallPreviewViewController*>();//
                    if (previewController) previewController->UpdatePreview();
                    else ERROR("Couldn't find preview controller");
                }));
            BeatSaberUI::CreateToggle(container->get_transform(), "Force Frame Off", config.wallConfig.forceFrameOff, il2cpp_utils::MakeDelegate<UnityAction_1<bool>*>(classof(UnityAction_1<bool>*), this, +[](WallSettingsViewController* view, bool value) { 
                    config.wallConfig.forceFrameOff = value;
                    SaveConfig();
                    QuestWall::SelectionDefinitive();
                    WallPreviewViewController* previewController = Object::FindObjectOfType<WallPreviewViewController*>();//
                    if (previewController) previewController->UpdatePreview();
                    else ERROR("Couldn't find preview controller");
                }));
        }
    }
}