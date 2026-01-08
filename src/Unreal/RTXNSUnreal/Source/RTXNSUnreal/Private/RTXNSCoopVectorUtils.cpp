#include "RTXNSCoopVectorUtils.h"

FRTXNSCoopVectorUtils::FRTXNSCoopVectorUtils(const FRTXNSRHIInteropRef& InInterop)
    : Interop(InInterop)
    , NetworkUtils(std::make_shared<rtxns::NetworkUtilities>(InInterop->GetNvrhiDevice()))
{
}

bool FRTXNSCoopVectorUtils::ValidateArchitecture(const rtxns::NetworkArchitecture& Architecture) const
{
    return NetworkUtils->ValidateNetworkArchitecture(Architecture);
}

rtxns::NetworkLayout FRTXNSCoopVectorUtils::CreateHostLayout(const rtxns::NetworkArchitecture& Architecture) const
{
    return NetworkUtils->CreateHostNetworkLayout(Architecture);
}

rtxns::NetworkLayout FRTXNSCoopVectorUtils::CreateDeviceLayout(const rtxns::NetworkLayout& SourceLayout,
                                                               rtxns::MatrixLayout TargetLayout,
                                                               rtxns::Precision TargetPrecision) const
{
    return NetworkUtils->GetNewMatrixLayout(SourceLayout, TargetLayout, TargetPrecision);
}

void FRTXNSCoopVectorUtils::ConvertWeights(const rtxns::NetworkLayout& SourceLayout,
                                           const rtxns::NetworkLayout& DestLayout,
                                           FRHIBuffer* SourceBuffer,
                                           uint64 SourceOffset,
                                           FRHIBuffer* DestBuffer,
                                           uint64 DestOffset,
                                           FRHICommandListImmediate& RHICmdList)
{
    nvrhi::CommandListHandle CommandList = Interop->GetNvrhiCommandList(RHICmdList);
    NetworkUtils->ConvertWeights(SourceLayout,
                                 DestLayout,
                                 Interop->GetNvrhiBuffer(SourceBuffer),
                                 SourceOffset,
                                 Interop->GetNvrhiBuffer(DestBuffer),
                                 DestOffset,
                                 Interop->GetNvrhiDevice(),
                                 CommandList);
}
