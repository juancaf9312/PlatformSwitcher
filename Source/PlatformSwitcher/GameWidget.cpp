// Fill out your copyright notice in the Description page of Project Settings.

#include "GameWidget.h"

#include "Runtime/UMG/Public/Components/TextBlock.h"
#include "Runtime/UMG/Public/Blueprint/WidgetTree.h"

void UGameWidget::Load()
{
	const FName TextBlockName = FName(TEXT("MessageBox"));
	if (MessageText == NULL) {
		MessageText = (UTextBlock*)(WidgetTree->FindWidget(TextBlockName));
	}
}

void UGameWidget::OnGameOver(bool win)
{
	if (MessageText) {
		if (win) MessageText->SetText(FText::FromString(TEXT("You won!\nPress R to play again")));
		else MessageText->SetText(FText::FromString(TEXT("You lost\nPress R to play again")));
	}
}
