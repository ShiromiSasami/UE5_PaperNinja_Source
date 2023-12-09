//#include "Interfaces/CustomEditorModule.h"
//
//#include "Interfaces/SocketNameProperty.h"
//
//#include <Modules/ModuleManager.h>
//
//void FCustomEditorModule::StartupModule()
//{
//	FPropertyEditorModule& PropertyModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");
//	PropertyModule.RegisterCustomPropertyTypeLayout("FName", FOnGetPropertyTypeCustomizationInstance::CreateStatic(&FSocketNameProperty::MakeInstance));
//}
//
//void FCustomEditorModule::ShutdownModule()
//{
//    if (FModuleManager::Get().IsModuleLoaded("PropertyEditor"))
//    {
//        FPropertyEditorModule& PropertyModule = FModuleManager::GetModuleChecked<FPropertyEditorModule>("PropertyEditor");
//        PropertyModule.UnregisterCustomPropertyTypeLayout("FName");
//    }
//}