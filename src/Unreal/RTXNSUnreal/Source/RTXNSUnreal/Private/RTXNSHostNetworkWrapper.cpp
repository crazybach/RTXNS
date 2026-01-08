#include "RTXNSHostNetworkWrapper.h"

#include <string>

FRTXNSHostNetworkWrapper::FRTXNSHostNetworkWrapper(const FRTXNSRHIInteropRef& InInterop)
    : Interop(InInterop)
    , NetworkUtils(std::make_shared<rtxns::NetworkUtilities>(InInterop->GetNvrhiDevice()))
    , HostNetwork(NetworkUtils)
{
}

bool FRTXNSHostNetworkWrapper::Initialize(const rtxns::NetworkArchitecture& Architecture)
{
    return HostNetwork.Initialise(Architecture);
}

bool FRTXNSHostNetworkWrapper::InitializeFromFile(const FString& FilePath)
{
    return HostNetwork.InitialiseFromFile(TCHAR_TO_UTF8(*FilePath));
}

bool FRTXNSHostNetworkWrapper::InitializeFromJson(donut::vfs::IFileSystem& FileSystem, const FString& FilePath)
{
    return HostNetwork.InitialiseFromJson(FileSystem, TCHAR_TO_UTF8(*FilePath));
}

bool FRTXNSHostNetworkWrapper::InitializeFromNetwork(const FRTXNSHostNetworkWrapper& Other)
{
    return HostNetwork.InitialiseFromNetwork(Other.HostNetwork);
}

void FRTXNSHostNetworkWrapper::ResetParameters()
{
    HostNetwork.ResetParameters();
}

bool FRTXNSHostNetworkWrapper::SaveToFile(const FString& FilePath) const
{
    return HostNetwork.WriteToFile(TCHAR_TO_UTF8(*FilePath));
}

const rtxns::NetworkArchitecture& FRTXNSHostNetworkWrapper::GetArchitecture() const
{
    return HostNetwork.GetNetworkArchitecture();
}

const rtxns::NetworkLayout& FRTXNSHostNetworkWrapper::GetLayout() const
{
    return HostNetwork.GetNetworkLayout();
}

const std::vector<uint8_t>& FRTXNSHostNetworkWrapper::GetParameters() const
{
    return HostNetwork.GetNetworkParams();
}

rtxns::NetworkLayout FRTXNSHostNetworkWrapper::CreateDeviceLayout(rtxns::MatrixLayout TargetLayout,
                                                                  rtxns::Precision TargetPrecision) const
{
    return NetworkUtils->GetNewMatrixLayout(HostNetwork.GetNetworkLayout(), TargetLayout, TargetPrecision);
}

void FRTXNSHostNetworkWrapper::UploadParameters(FRHICommandListImmediate& RHICmdList,
                                                FRHIBuffer* DestBuffer,
                                                uint64 DestOffset) const
{
    const std::vector<uint8_t>& Params = HostNetwork.GetNetworkParams();
    if (Params.empty())
    {
        return;
    }

    Interop->UpdateBuffer(RHICmdList, DestBuffer, DestOffset, Params.data(), Params.size());
}

void FRTXNSHostNetworkWrapper::UpdateFromDeviceBufferToFile(FRHICommandListImmediate& RHICmdList,
                                                            FRHIBuffer* HostLayoutBuffer,
                                                            FRHIBuffer* DeviceLayoutBuffer,
                                                            const rtxns::NetworkLayout& HostLayout,
                                                            const rtxns::NetworkLayout& DeviceLayout,
                                                            const FString& FilePath)
{
    HostNetwork.UpdateFromBufferToFile(Interop->GetNvrhiBuffer(HostLayoutBuffer),
                                       Interop->GetNvrhiBuffer(DeviceLayoutBuffer),
                                       HostLayout,
                                       DeviceLayout,
                                       TCHAR_TO_UTF8(*FilePath),
                                       Interop->GetNvrhiDevice(),
                                       Interop->GetNvrhiCommandList(RHICmdList));
}
