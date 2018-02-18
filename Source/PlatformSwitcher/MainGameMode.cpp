// Fill out your copyright notice in the Description page of Project Settings.

#include "MainGameMode.h"
#include "GameWidget.h"

#include "Blueprint/UserWidget.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Runtime/Engine/Classes/GameFramework/Character.h"

void AMainGameMode::BeginPlay()
{
	Super::BeginPlay();

	ChangeMenuWidget(StartingWidgetClass);
	if(CurrentWidget)
		((UGameWidget*)CurrentWidget)->Load();

	GetWorld()->GetFirstPlayerController()->InputComponent->BindAction("Switch",IE_Pressed,this,&AMainGameMode::OnSwitch);
	GetWorld()->GetFirstPlayerController()->InputComponent->BindAction("Restart", IE_Pressed, this, &AMainGameMode::OnRsestart).bExecuteWhenPaused = true;
}


void AMainGameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMainGameMode::OnSwitch()
{
	if (Switched) {
		FVector NewLocation = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)->GetActorLocation();
		NewLocation.X = 1200.f;
		UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)->SetActorLocation(NewLocation);
	}
	else {
		FVector NewLocation = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)->GetActorLocation();
		NewLocation.X = 110.f;
		UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)->SetActorLocation(NewLocation);
	}

	Switched = !Switched;
}

void AMainGameMode::OnRsestart()
{
	UGameplayStatics::OpenLevel(this, FName(*GetWorld()->GetName()), false);
}

void AMainGameMode::OnGameOver(bool win)
{
	((UGameWidget*)CurrentWidget)->OnGameOver(win);
	UGameplayStatics::SetGamePaused(GetWorld(), true);
}

void AMainGameMode::ChangeMenuWidget(TSubclassOf<UUserWidget> NewWidgetClass)
{
	if (CurrentWidget) {
		CurrentWidget->RemoveFromViewport();
		CurrentWidget = nullptr;
	}
	if (NewWidgetClass) {
		CurrentWidget = CreateWidget<UUserWidget>(GetWorld(), NewWidgetClass);
		if (CurrentWidget)CurrentWidget->AddToViewport();
	}
}
