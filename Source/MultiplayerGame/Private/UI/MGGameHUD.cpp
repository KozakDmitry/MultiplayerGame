// Multiplayer Game

#include "UI/MGGameHUD.h"
#include "Engine/Canvas.h"
#include "UI/MGPlayerHUDWidget.h"

UE_DISABLE_OPTIMIZATION
void AMGGameHUD::DrawHUD()
{
	Super::DrawHUD();
	DrawCrosshair();
}

void AMGGameHUD::DrawCrosshair()
{
	const TInterval<float> Center(Canvas->SizeX * 0.5f, Canvas->SizeY * 0.5f);

	const float HalfLineSize = 10.0f;
	const float LineThickness = 2.0f;
	const FLinearColor LineColor = FLinearColor::Green;

	DrawLine(Center.Min - HalfLineSize, Center.Max, Center.Min + HalfLineSize, Center.Max, LineColor, LineThickness);
	DrawLine(Center.Min, Center.Max - HalfLineSize, Center.Min, Center.Max + HalfLineSize, LineColor, LineThickness);
}

void AMGGameHUD::DrawHP()
{

	//if (!PlayerHUDWidget)
	//{
	//	PlayerHUDWidget = CreateWidget<UMGPlayerHUDWidget>(GetWorld(), PlayerHUD);
	//}
	//if (PlayerHUDWidget)
	//{
	//	PlayerHUDWidget->AddToViewport();
	//}
}
void AMGGameHUD::SetPlayerWidget(UMGPlayerHUDWidget *widget)
{
	if (!widget)
	{
		return;
	}
	PlayerHUDWidget = widget;
	
}
UE_ENABLE_OPTIMIZATION