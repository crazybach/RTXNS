#pragma once

#include "CoreMinimal.h"
#include "RTXNSRHIInterop.h"

#include <donut/core/vfs.h>
#include <memory>

#include "NeuralNetwork.h"
#include "NeuralNetworkTypes.h"

class FRTXNSHostNetworkWrapper
{
public:
    explicit FRTXNSHostNetworkWrapper(const FRTXNSRHIInteropRef& InInterop);

    bool Initialize(const rtxns::NetworkArchitecture& Architecture);
    bool InitializeFromFile(const FString& FilePath);
    bool InitializeFromJson(donut::vfs::IFileSystem& FileSystem, const FString& FilePath);
    bool InitializeFromNetwork(const FRTXNSHostNetworkWrapper& Other);

    void ResetParameters();
    bool SaveToFile(const FString& FilePath) const;

    const rtxns::NetworkArchitecture& GetArchitecture() const;
    const rtxns::NetworkLayout& GetLayout() const;
    const std::vector<uint8_t>& GetParameters() const;

    rtxns::NetworkLayout CreateDeviceLayout(rtxns::MatrixLayout TargetLayout,
                                            rtxns::Precision TargetPrecision = rtxns::Precision::F16) const;

    void UploadParameters(FRHICommandListImmediate& RHICmdList,
                          FRHIBuffer* DestBuffer,
                          uint64 DestOffset) const;

    void UpdateFromDeviceBufferToFile(FRHICommandListImmediate& RHICmdList,
                                      FRHIBuffer* HostLayoutBuffer,
                                      FRHIBuffer* DeviceLayoutBuffer,
                                      const rtxns::NetworkLayout& HostLayout,
                                      const rtxns::NetworkLayout& DeviceLayout,
                                      const FString& FilePath);

private:
    FRTXNSRHIInteropRef Interop;
    std::shared_ptr<rtxns::NetworkUtilities> NetworkUtils;
    rtxns::HostNetwork HostNetwork;
};
