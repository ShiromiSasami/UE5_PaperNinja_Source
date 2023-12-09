//#include "Interfaces/SocketNameProperty.h"
//
//#include <DetailWidgetRow.h>
//#include <Engine/SkeletalMeshSocket.h>
//#include <Widgets/Input/SComboBox.h>
//#include "Widgets/Text/STextBlock.h"
//
//FSocketNameProperty::FSocketNameProperty()
//{
//}
//
//void FSocketNameProperty::CustomizeHeader(TSharedRef<IPropertyHandle> PropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& CustomizationUtils)
//{
//    UObject* Object;
//    PropertyHandle->GetValue(Object);
//
//    USkeletalMeshComponent* SkeletalMeshComponent = Cast<USkeletalMeshComponent>(Object);
//    if (SkeletalMeshComponent && SkeletalMeshComponent->GetSkeletalMeshAsset())
//    {
//        // ソケットのリストを取得
//        const TArray<USkeletalMeshSocket*>& Sockets = SkeletalMeshComponent->GetSkeletalMeshAsset()->GetMeshOnlySocketList();
//
//        // ソケット名のリストを生成
//        for (USkeletalMeshSocket* Socket : Sockets)
//        {
//            if (Socket)
//            {
//                _socketNameList.Add(Socket->SocketName);
//            }
//        }
//    }
//
//    HeaderRow.NameContent()[PropertyHandle->CreatePropertyNameWidget()]
//        .ValueContent()
//        .MaxDesiredWidth(250)
//        [
//            SNew(SComboBox<FName>)
//                .OptionsSource(&_socketNameList)
//                .OnGenerateWidget(this, &FSocketNameProperty::MakeSocketWidget)
//                .OnSelectionChanged(this, &FSocketNameProperty::OnSocketChanged)
//                .InitiallySelectedItem(_socketNameList.Num() > 0 ? _socketNameList[0] : FName())
//                [
//                    SNew(STextBlock).Text(NSLOCTEXT("SocketName", "SelectSocket", "None"))
//                ]
//        ];
//}
//
//void FSocketNameProperty::CustomizeChildren(TSharedRef<IPropertyHandle> PropertyHandle, IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& CustomizationUtils)
//{
//
//}

