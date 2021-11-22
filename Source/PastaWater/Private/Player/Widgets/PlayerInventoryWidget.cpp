#include "Player/Widgets/PlayerInventoryWidget.h"

#include "Components/CanvasPanelSlot.h"
#include "Components/GridSlot.h"
#include "Core/Game/PastaWaterPlayerControllerBase.h"
#include "Core/Helpers/DebugHelpers.h"

FReply UPlayerInventoryWidget::NativeOnMouseMove(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseMove(InGeometry, InMouseEvent);
	if(GetVisibility() == ESlateVisibility::Visible)
	{
		UCanvasPanelSlot* CanvasPanelSlot = Cast<UCanvasPanelSlot>(MouseSlotBox->Slot);
		if(IsValid(CanvasPanelSlot))
		{
			FVector2D NewPosition = InGeometry.AbsoluteToLocal(InMouseEvent.GetScreenSpacePosition());
			CanvasPanelSlot->SetPosition(FVector2D(NewPosition.X, NewPosition.Y));
		} else
		{
			UDebugHelpers::ScreenLogError("Cannot find Canvas Panel Slot from Mouse Slot Widget");
		}
	}
	return FReply::Handled();
}

bool UPlayerInventoryWidget::CreateInventorySlots(const FString WidgetId)
{
	if(!Super::CreateInventorySlots(WidgetId))
	{
		return false;
	}

	// Add each item slot in hotbar
	for(int Index = 0; Index < Columns; Index++)
	{
		FString ItemSlotWidgetId = WidgetId+FString(" Hotbar Item Slot ")+FString::FromInt(Index+StartIndex);
		UItemStackSlotWidget* Widget = CreateWidget<UItemStackSlotWidget>(PlayerController, ItemStackSlotClass, FName(*ItemSlotWidgetId));
		if(IsValid(Widget))
		{
			Widget->InventoryAC = InventoryAC;
			Widget->InventoryACIndex = Index;
			Widget->SetVisibility(ESlateVisibility::Visible);
			Widget->AddToViewport();

			// Add to items grid panel
			const int Column = Index % Columns;
			UGridSlot* GridSlot = HotbarItemsGridPanel->AddChildToGrid(Widget, 0, Column);
			GridSlot->SetPadding(FMargin(8));
		}
	}

	// Setup mouse slot
	const FString MouseItemSlotWidgetId = WidgetId+FString(" Mouse Item Slot");
	UItemStackSlotWidget* MouseItemSlot = CreateWidget<UItemStackSlotWidget>(PlayerController, MouseItemStackSlotClass, FName(*MouseItemSlotWidgetId));
	if(IsValid(MouseItemSlot))
	{
		MouseItemSlot->InventoryAC = InventoryAC;
		MouseItemSlot->InventoryACIndex = -1;
		MouseItemSlot->SetVisibility(ESlateVisibility::HitTestInvisible);
		MouseItemSlot->AddToViewport();
	} else
	{
		UDebugHelpers::ScreenLogError("Mouse item slot did not create properly!");
	}
	MouseSlotBox->AddChild(MouseItemSlot);
	return true;
}

bool UPlayerInventoryWidget::UpdateInventorySlots()
{
	if(!Super::UpdateInventorySlots())
	{
		return false;
	}
	
	// Call "Update Item Details" on every item stack slot widget
	TArray<UWidget*> Widgets = HotbarItemsGridPanel->GetAllChildren();
	for(int Index = 0; Index < HotbarItemsGridPanel->GetChildrenCount(); Index++)
	{
		UItemStackSlotWidget* ItemStackSlot = Cast<UItemStackSlotWidget>(HotbarItemsGridPanel->GetChildAt(Index));
		ItemStackSlot->UpdateItemDetails();
	}

	UItemStackSlotWidget* MouseItemStackSlot = Cast<UItemStackSlotWidget>(MouseSlotBox->GetChildAt(0));
	MouseItemStackSlot->UpdateItemDetails();
	return true;
}

UPlayerInventoryWidget* UPlayerInventoryWidget::Create(
	TSubclassOf<UPlayerInventoryWidget> PlayerInventoryWidgetClass,
	APastaWaterPlayerControllerBase* OwningPlayerController,
	UPlayerInventoryAC* OwningPlayerInventoryAC)
{
	// Create widget
	UPlayerInventoryWidget* PlayerInventoryWidget = CreateWidget<UPlayerInventoryWidget>(
		OwningPlayerController,
		PlayerInventoryWidgetClass,
		"Player Inventory");

	// Failure check
	if(!IsValid(PlayerInventoryWidget))
	{
		UDebugHelpers::ScreenLogError("Could not initialise Player Inventory Widget.");
		return nullptr;
	}

	// Setup widget and return
	UDebugHelpers::ScreenLogInfo("Initialised Player Inventory Widget.");
	PlayerInventoryWidget->Setup(OwningPlayerInventoryAC);
	PlayerInventoryWidget->CreateInventorySlots("Inventory");
	PlayerInventoryWidget->UpdateInventorySlots();
	PlayerInventoryWidget->SetVisibility(ESlateVisibility::Hidden);
	PlayerInventoryWidget->AddToViewport();
	return PlayerInventoryWidget;
}
