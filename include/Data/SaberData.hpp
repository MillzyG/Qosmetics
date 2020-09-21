#pragma once
#include <string>
#include "bs-utils/shared/AssetBundle.hpp"
#include "UnityEngine/TextAsset.hpp"
#include "UnityEngine/Texture2D.hpp"
#include "UnityEngine/GameObject.hpp"
#include "UnityEngine/Object.hpp"
#include "modloader/shared/modloader.hpp"
#include "UnityEngine/Material.hpp"
#include "Data/Descriptor.hpp"
#include "Config/SaberConfig.hpp"
#include "beatsaber-hook/shared/rapidjson/include/rapidjson/document.h"
#include "beatsaber-hook/shared/utils/utils.h"
#include "beatsaber-hook/shared/utils/logging.hpp"
#include "modloader/shared/modloader.hpp"
#include "beatsaber-hook/shared/utils/il2cpp-functions.hpp"
#include "beatsaber-hook/shared/utils/il2cpp-utils.hpp" 
#include "beatsaber-hook/shared/utils/typedefs.h"
#include "Logging/SaberLogger.hpp"
//#include "beatsaber-hook"
namespace Qosmetics
{
    class SaberData 
    {
        public:
            static const Logger& getLogger() 
            {
                return SaberLogger::GetLogger();
            };

            Qosmetics::Descriptor* saberDescriptor = nullptr;
            Qosmetics::SaberConfig* saberConfig = nullptr;
            
            SaberData(){}

            SaberData(const std::string &filePath)
            {
                this->filePath = filePath;
            }

            const UnityEngine::GameObject* get_saber()
            {
                return saberPrefab;
            }
            
            UnityEngine::GameObject* get_saberPrefab()
            {
                return saberPrefab;
            }

            bool get_isLoading()
            {
                return isLoading;
            }

            bool get_complete()
            {
                if (finishedSaberLoad) return true;
        
                finishedSaberLoad = objectComplete && configComplete && descriptorComplete;
                return finishedSaberLoad;
            }

            bool get_replacedMaterials()
            {
                return replacedMaterials;
            }

            void set_replacedMaterials(bool value)
            {
                replacedMaterials = value;
            }
            
            SaberData(std::string filePath, bool alsoLoadBundle)
            {
                this->filePath = filePath;
                if (alsoLoadBundle) LoadBundle();
            }

            /// @brief loads asset bundle using bs utils
            /// @param filePath path to load the bundle from
            void LoadBundle(std::string filePath);

            /// @brief loads asset bundle using bs utils, only use if filePath is already given
            void LoadBundle();

            void LoadAssets();
        private:
        
            void OnSaberLoadComplete(UnityEngine::GameObject* saber, bool DontDestroyOnLoad);

            void OnConfigLoadComplete(UnityEngine::TextAsset* configAsset);
            
            void OnDescriptorLoadComplete(UnityEngine::TextAsset* descriptorAsset);

            void OnTextureLoadComplete(UnityEngine::Texture2D* texture);
            
            std::string filePath = "";

            UnityEngine::GameObject* saberPrefab = nullptr;

            bool finishedSaberLoad = false;
            bool objectComplete = false;
            bool configComplete = false;
            bool descriptorComplete = false;
            bool isLoading = false;
            bool replacedMaterials = false;
            bool bundleLoading = false;
            bs_utils::AssetBundle* bundle = nullptr;
    };
}

