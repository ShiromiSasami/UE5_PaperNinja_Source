#pragma once

//#include "CoreMinimal.h"
//#include "IPropertyTypeCustomization.h"
//#include "PropertyHandle.h"
//
//class FSocketNameProperty : public IPropertyTypeCustomization
//{
//public:
//    FSocketNameProperty();
//
//    static TSharedRef<IPropertyTypeCustomization> MakeInstance() { return MakeShareable(new FSocketNameProperty); };
//    
//    virtual void CustomizeHeader(TSharedRef<IPropertyHandle> PropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& CustomizationUtils) override;
//    virtual void CustomizeChildren(TSharedRef<IPropertyHandle> PropertyHandle, IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& CustomizationUtils) override;
//
//private:
//
//    inline TSharedRef<SWidget> MakeSocketWidget(FName InItem)
//    {
//        return SNew(STextBlock).Text(FText::FromString(InItem.ToString()));
//    }
//
//    inline void OnSocketChanged(FName NewSelection, ESelectInfo::Type SelectInfo)
//    {
//        // ここにソケットが選択されたときの処理を記述
//    }
//
//private:
//    TArray<FName> _socketNameList;
//};