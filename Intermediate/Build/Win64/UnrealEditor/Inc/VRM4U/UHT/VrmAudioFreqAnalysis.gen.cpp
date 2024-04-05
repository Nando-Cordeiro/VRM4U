// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "VRM4U/Public/VrmAudioFreqAnalysis.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeVrmAudioFreqAnalysis() {}
// Cross Module References
	ENGINE_API UClass* Z_Construct_UClass_ASkeletalMeshActor_NoRegister();
	ENGINE_API UClass* Z_Construct_UClass_UActorComponent();
	ENGINE_API UClass* Z_Construct_UClass_UAudioComponent_NoRegister();
	ENGINE_API UClass* Z_Construct_UClass_USoundBase_NoRegister();
	UPackage* Z_Construct_UPackage__Script_VRM4U();
	VRM4U_API UClass* Z_Construct_UClass_UVrmAudioFreqAnalysis();
	VRM4U_API UClass* Z_Construct_UClass_UVrmAudioFreqAnalysis_NoRegister();
// End Cross Module References
	DEFINE_FUNCTION(UVrmAudioFreqAnalysis::execStartAnalysis)
	{
		P_GET_OBJECT(ASkeletalMeshActor,Z_Param_SceneCharacter);
		P_GET_OBJECT(USoundBase,Z_Param_Dialogue);
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->StartAnalysis(Z_Param_SceneCharacter,Z_Param_Dialogue);
		P_NATIVE_END;
	}
	void UVrmAudioFreqAnalysis::StaticRegisterNativesUVrmAudioFreqAnalysis()
	{
		UClass* Class = UVrmAudioFreqAnalysis::StaticClass();
		static const FNameNativePtrPair Funcs[] = {
			{ "StartAnalysis", &UVrmAudioFreqAnalysis::execStartAnalysis },
		};
		FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
	}
	struct Z_Construct_UFunction_UVrmAudioFreqAnalysis_StartAnalysis_Statics
	{
		struct VrmAudioFreqAnalysis_eventStartAnalysis_Parms
		{
			ASkeletalMeshActor* SceneCharacter;
			USoundBase* Dialogue;
		};
		static const UECodeGen_Private::FObjectPropertyParams NewProp_SceneCharacter;
		static const UECodeGen_Private::FObjectPropertyParams NewProp_Dialogue;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UVrmAudioFreqAnalysis_StartAnalysis_Statics::NewProp_SceneCharacter = { "SceneCharacter", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(VrmAudioFreqAnalysis_eventStartAnalysis_Parms, SceneCharacter), Z_Construct_UClass_ASkeletalMeshActor_NoRegister, METADATA_PARAMS(0, nullptr) };
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UVrmAudioFreqAnalysis_StartAnalysis_Statics::NewProp_Dialogue = { "Dialogue", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(VrmAudioFreqAnalysis_eventStartAnalysis_Parms, Dialogue), Z_Construct_UClass_USoundBase_NoRegister, METADATA_PARAMS(0, nullptr) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UVrmAudioFreqAnalysis_StartAnalysis_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UVrmAudioFreqAnalysis_StartAnalysis_Statics::NewProp_SceneCharacter,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UVrmAudioFreqAnalysis_StartAnalysis_Statics::NewProp_Dialogue,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UVrmAudioFreqAnalysis_StartAnalysis_Statics::Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Public/VrmAudioFreqAnalysis.h" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UVrmAudioFreqAnalysis_StartAnalysis_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UVrmAudioFreqAnalysis, nullptr, "StartAnalysis", nullptr, nullptr, Z_Construct_UFunction_UVrmAudioFreqAnalysis_StartAnalysis_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UVrmAudioFreqAnalysis_StartAnalysis_Statics::PropPointers), sizeof(Z_Construct_UFunction_UVrmAudioFreqAnalysis_StartAnalysis_Statics::VrmAudioFreqAnalysis_eventStartAnalysis_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UVrmAudioFreqAnalysis_StartAnalysis_Statics::Function_MetaDataParams), Z_Construct_UFunction_UVrmAudioFreqAnalysis_StartAnalysis_Statics::Function_MetaDataParams) };
	static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UVrmAudioFreqAnalysis_StartAnalysis_Statics::PropPointers) < 2048);
	static_assert(sizeof(Z_Construct_UFunction_UVrmAudioFreqAnalysis_StartAnalysis_Statics::VrmAudioFreqAnalysis_eventStartAnalysis_Parms) < MAX_uint16);
	UFunction* Z_Construct_UFunction_UVrmAudioFreqAnalysis_StartAnalysis()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UVrmAudioFreqAnalysis_StartAnalysis_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(UVrmAudioFreqAnalysis);
	UClass* Z_Construct_UClass_UVrmAudioFreqAnalysis_NoRegister()
	{
		return UVrmAudioFreqAnalysis::StaticClass();
	}
	struct Z_Construct_UClass_UVrmAudioFreqAnalysis_Statics
	{
		static UObject* (*const DependentSingletons[])();
		static const FClassFunctionLinkInfo FuncInfo[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_AudioComponent_MetaData[];
#endif
		static const UECodeGen_Private::FObjectPropertyParams NewProp_AudioComponent;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_EnvelopeFollowerAttackTime_MetaData[];
#endif
		static const UECodeGen_Private::FIntPropertyParams NewProp_EnvelopeFollowerAttackTime;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_EnvelopeFollowerReleaseTime_MetaData[];
#endif
		static const UECodeGen_Private::FIntPropertyParams NewProp_EnvelopeFollowerReleaseTime;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_OpenCounterThreshold_MetaData[];
#endif
		static const UECodeGen_Private::FIntPropertyParams NewProp_OpenCounterThreshold;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_ClosedCounterThreshold_MetaData[];
#endif
		static const UECodeGen_Private::FIntPropertyParams NewProp_ClosedCounterThreshold;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_PercentRange_MetaData[];
#endif
		static const UECodeGen_Private::FFloatPropertyParams NewProp_PercentRange;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_Character_MetaData[];
#endif
		static const UECodeGen_Private::FObjectPropertyParams NewProp_Character;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UVrmAudioFreqAnalysis_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UActorComponent,
		(UObject* (*)())Z_Construct_UPackage__Script_VRM4U,
	};
	static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UVrmAudioFreqAnalysis_Statics::DependentSingletons) < 16);
	const FClassFunctionLinkInfo Z_Construct_UClass_UVrmAudioFreqAnalysis_Statics::FuncInfo[] = {
		{ &Z_Construct_UFunction_UVrmAudioFreqAnalysis_StartAnalysis, "StartAnalysis" }, // 514994111
	};
	static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UVrmAudioFreqAnalysis_Statics::FuncInfo) < 2048);
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UVrmAudioFreqAnalysis_Statics::Class_MetaDataParams[] = {
		{ "BlueprintSpawnableComponent", "" },
		{ "ClassGroupNames", "Custom" },
		{ "IncludePath", "VrmAudioFreqAnalysis.h" },
		{ "ModuleRelativePath", "Public/VrmAudioFreqAnalysis.h" },
	};
#endif
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UVrmAudioFreqAnalysis_Statics::NewProp_AudioComponent_MetaData[] = {
		{ "Category", "VrmAudioFreqAnalysis" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/VrmAudioFreqAnalysis.h" },
	};
#endif
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UVrmAudioFreqAnalysis_Statics::NewProp_AudioComponent = { "AudioComponent", nullptr, (EPropertyFlags)0x0010000000080009, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UVrmAudioFreqAnalysis, AudioComponent), Z_Construct_UClass_UAudioComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UVrmAudioFreqAnalysis_Statics::NewProp_AudioComponent_MetaData), Z_Construct_UClass_UVrmAudioFreqAnalysis_Statics::NewProp_AudioComponent_MetaData) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UVrmAudioFreqAnalysis_Statics::NewProp_EnvelopeFollowerAttackTime_MetaData[] = {
		{ "Category", "VrmAudioFreqAnalysis" },
		{ "ModuleRelativePath", "Public/VrmAudioFreqAnalysis.h" },
	};
#endif
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UClass_UVrmAudioFreqAnalysis_Statics::NewProp_EnvelopeFollowerAttackTime = { "EnvelopeFollowerAttackTime", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UVrmAudioFreqAnalysis, EnvelopeFollowerAttackTime), METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UVrmAudioFreqAnalysis_Statics::NewProp_EnvelopeFollowerAttackTime_MetaData), Z_Construct_UClass_UVrmAudioFreqAnalysis_Statics::NewProp_EnvelopeFollowerAttackTime_MetaData) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UVrmAudioFreqAnalysis_Statics::NewProp_EnvelopeFollowerReleaseTime_MetaData[] = {
		{ "Category", "VrmAudioFreqAnalysis" },
		{ "ModuleRelativePath", "Public/VrmAudioFreqAnalysis.h" },
	};
#endif
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UClass_UVrmAudioFreqAnalysis_Statics::NewProp_EnvelopeFollowerReleaseTime = { "EnvelopeFollowerReleaseTime", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UVrmAudioFreqAnalysis, EnvelopeFollowerReleaseTime), METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UVrmAudioFreqAnalysis_Statics::NewProp_EnvelopeFollowerReleaseTime_MetaData), Z_Construct_UClass_UVrmAudioFreqAnalysis_Statics::NewProp_EnvelopeFollowerReleaseTime_MetaData) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UVrmAudioFreqAnalysis_Statics::NewProp_OpenCounterThreshold_MetaData[] = {
		{ "Category", "VrmAudioFreqAnalysis" },
		{ "ModuleRelativePath", "Public/VrmAudioFreqAnalysis.h" },
	};
#endif
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UClass_UVrmAudioFreqAnalysis_Statics::NewProp_OpenCounterThreshold = { "OpenCounterThreshold", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UVrmAudioFreqAnalysis, OpenCounterThreshold), METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UVrmAudioFreqAnalysis_Statics::NewProp_OpenCounterThreshold_MetaData), Z_Construct_UClass_UVrmAudioFreqAnalysis_Statics::NewProp_OpenCounterThreshold_MetaData) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UVrmAudioFreqAnalysis_Statics::NewProp_ClosedCounterThreshold_MetaData[] = {
		{ "Category", "VrmAudioFreqAnalysis" },
		{ "ModuleRelativePath", "Public/VrmAudioFreqAnalysis.h" },
	};
#endif
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UClass_UVrmAudioFreqAnalysis_Statics::NewProp_ClosedCounterThreshold = { "ClosedCounterThreshold", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UVrmAudioFreqAnalysis, ClosedCounterThreshold), METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UVrmAudioFreqAnalysis_Statics::NewProp_ClosedCounterThreshold_MetaData), Z_Construct_UClass_UVrmAudioFreqAnalysis_Statics::NewProp_ClosedCounterThreshold_MetaData) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UVrmAudioFreqAnalysis_Statics::NewProp_PercentRange_MetaData[] = {
		{ "Category", "VrmAudioFreqAnalysis" },
		{ "ModuleRelativePath", "Public/VrmAudioFreqAnalysis.h" },
	};
#endif
	const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_UVrmAudioFreqAnalysis_Statics::NewProp_PercentRange = { "PercentRange", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UVrmAudioFreqAnalysis, PercentRange), METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UVrmAudioFreqAnalysis_Statics::NewProp_PercentRange_MetaData), Z_Construct_UClass_UVrmAudioFreqAnalysis_Statics::NewProp_PercentRange_MetaData) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UVrmAudioFreqAnalysis_Statics::NewProp_Character_MetaData[] = {
		{ "Category", "VrmAudioFreqAnalysis" },
		{ "ModuleRelativePath", "Public/VrmAudioFreqAnalysis.h" },
	};
#endif
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UVrmAudioFreqAnalysis_Statics::NewProp_Character = { "Character", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UVrmAudioFreqAnalysis, Character), Z_Construct_UClass_ASkeletalMeshActor_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UVrmAudioFreqAnalysis_Statics::NewProp_Character_MetaData), Z_Construct_UClass_UVrmAudioFreqAnalysis_Statics::NewProp_Character_MetaData) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UVrmAudioFreqAnalysis_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UVrmAudioFreqAnalysis_Statics::NewProp_AudioComponent,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UVrmAudioFreqAnalysis_Statics::NewProp_EnvelopeFollowerAttackTime,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UVrmAudioFreqAnalysis_Statics::NewProp_EnvelopeFollowerReleaseTime,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UVrmAudioFreqAnalysis_Statics::NewProp_OpenCounterThreshold,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UVrmAudioFreqAnalysis_Statics::NewProp_ClosedCounterThreshold,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UVrmAudioFreqAnalysis_Statics::NewProp_PercentRange,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UVrmAudioFreqAnalysis_Statics::NewProp_Character,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_UVrmAudioFreqAnalysis_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UVrmAudioFreqAnalysis>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_UVrmAudioFreqAnalysis_Statics::ClassParams = {
		&UVrmAudioFreqAnalysis::StaticClass,
		"Engine",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		FuncInfo,
		Z_Construct_UClass_UVrmAudioFreqAnalysis_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		UE_ARRAY_COUNT(FuncInfo),
		UE_ARRAY_COUNT(Z_Construct_UClass_UVrmAudioFreqAnalysis_Statics::PropPointers),
		0,
		0x00B000A4u,
		METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UVrmAudioFreqAnalysis_Statics::Class_MetaDataParams), Z_Construct_UClass_UVrmAudioFreqAnalysis_Statics::Class_MetaDataParams)
	};
	static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UVrmAudioFreqAnalysis_Statics::PropPointers) < 2048);
	UClass* Z_Construct_UClass_UVrmAudioFreqAnalysis()
	{
		if (!Z_Registration_Info_UClass_UVrmAudioFreqAnalysis.OuterSingleton)
		{
			UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UVrmAudioFreqAnalysis.OuterSingleton, Z_Construct_UClass_UVrmAudioFreqAnalysis_Statics::ClassParams);
		}
		return Z_Registration_Info_UClass_UVrmAudioFreqAnalysis.OuterSingleton;
	}
	template<> VRM4U_API UClass* StaticClass<UVrmAudioFreqAnalysis>()
	{
		return UVrmAudioFreqAnalysis::StaticClass();
	}
	DEFINE_VTABLE_PTR_HELPER_CTOR(UVrmAudioFreqAnalysis);
	UVrmAudioFreqAnalysis::~UVrmAudioFreqAnalysis() {}
	struct Z_CompiledInDeferFile_FID_VRM4U_Plugin_Plugins_VRM4U_Source_VRM4U_Public_VrmAudioFreqAnalysis_h_Statics
	{
		static const FClassRegisterCompiledInInfo ClassInfo[];
	};
	const FClassRegisterCompiledInInfo Z_CompiledInDeferFile_FID_VRM4U_Plugin_Plugins_VRM4U_Source_VRM4U_Public_VrmAudioFreqAnalysis_h_Statics::ClassInfo[] = {
		{ Z_Construct_UClass_UVrmAudioFreqAnalysis, UVrmAudioFreqAnalysis::StaticClass, TEXT("UVrmAudioFreqAnalysis"), &Z_Registration_Info_UClass_UVrmAudioFreqAnalysis, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UVrmAudioFreqAnalysis), 3604404419U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_VRM4U_Plugin_Plugins_VRM4U_Source_VRM4U_Public_VrmAudioFreqAnalysis_h_1419887543(TEXT("/Script/VRM4U"),
		Z_CompiledInDeferFile_FID_VRM4U_Plugin_Plugins_VRM4U_Source_VRM4U_Public_VrmAudioFreqAnalysis_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_VRM4U_Plugin_Plugins_VRM4U_Source_VRM4U_Public_VrmAudioFreqAnalysis_h_Statics::ClassInfo),
		nullptr, 0,
		nullptr, 0);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
