// Fill out your copyright notice in the Description page of Project Settings.


#include "SCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
ASCharacter::ASCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>("SpringArmComponent");
	SpringArmComp->SetupAttachment(RootComponent);
	SpringArmComp->bUsePawnControlRotation = true;



	CameraComp = CreateDefaultSubobject<UCameraComponent>("CameraComp");
	CameraComp->SetupAttachment(SpringArmComp);

	GetCharacterMovement()->bOrientRotationToMovement = true;


	bUseControllerRotationYaw = false;



}

// Called when the game starts or when spawned
void ASCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}


void ASCharacter::MoveForward(float Value)
{
	FRotator ControlRot = GetControlRotation();

	ControlRot.Pitch = 0.0f;
	ControlRot.Roll = 0.0f;


	AddMovementInput(ControlRot.Vector(), Value);
}

void ASCharacter::MoveRight(float Value)


{

	FRotator ControlRot = GetControlRotation();

	ControlRot.Pitch = 0.0f;
	ControlRot.Roll = 0.0f;

	// X : forward
	// Y : right
	// Z : up

	FVector RightVector = FRotationMatrix(ControlRot).GetScaledAxis(EAxis::Y);


	AddMovementInput(RightVector, Value);
}


// Called every frame
void ASCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASCharacter::PrimaryAttack()
{

	FVector HandLocation = GetMesh()->GetSocketLocation("FX_Whip_Tip_A");

	FTransform SpawnTM = FTransform(GetControlRotation(), HandLocation);
	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	


	GetWorld()->SpawnActor<AActor>(ProjectileClass, SpawnTM, SpawnParams);
}



// Called to bind functionality to input
void ASCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);


	PlayerInputComponent->BindAxis("MoveForward", this, &ASCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ASCharacter::MoveRight);

	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &ASCharacter::AddControllerPitchInput);

	PlayerInputComponent->BindAction("PrimaryAttack", IE_Pressed, this, &ASCharacter::PrimaryAttack);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ASCharacter::Jump);



}

