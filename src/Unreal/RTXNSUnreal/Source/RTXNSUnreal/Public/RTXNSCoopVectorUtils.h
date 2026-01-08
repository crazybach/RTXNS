#pragma once

#include "CoreMinimal.h"
#include "RTXNSRHIInterop.h"

#include "NeuralNetworkTypes.h"
#include "NeuralNetwork.h"

#include <memory>

class IRTXNSCoopVectorUtils
{
public:
    virtual ~IRTXNSCoopVectorUtils() = default;

    virtual bool ValidateArchitecture(const rtxns::NetworkArchitecture& Architecture) const = 0;
    virtual rtxns::NetworkLayout CreateHostLayout(const rtxns::NetworkArchitecture& Architecture) const = 0;
    virtual rtxns::NetworkLayout CreateDeviceLayout(const rtxns::NetworkLayout& SourceLayout,
                                                    rtxns::MatrixLayout TargetLayout,
                                                    rtxns::Precision TargetPrecision = rtxns::Precision::F16) const = 0;
    virtual void ConvertWeights(const rtxns::NetworkLayout& SourceLayout,
                                const rtxns::NetworkLayout& DestLayout,
                                FRHIBuffer* SourceBuffer,
                                uint64 SourceOffset,
                                FRHIBuffer* DestBuffer,
                                uint64 DestOffset,
                                FRHICommandListImmediate& RHICmdList) = 0;
};

class FRTXNSCoopVectorUtils final : public IRTXNSCoopVectorUtils
{
public:
    explicit FRTXNSCoopVectorUtils(const FRTXNSRHIInteropRef& InInterop);

    bool ValidateArchitecture(const rtxns::NetworkArchitecture& Architecture) const override;
    rtxns::NetworkLayout CreateHostLayout(const rtxns::NetworkArchitecture& Architecture) const override;
    rtxns::NetworkLayout CreateDeviceLayout(const rtxns::NetworkLayout& SourceLayout,
                                            rtxns::MatrixLayout TargetLayout,
                                            rtxns::Precision TargetPrecision) const override;
    void ConvertWeights(const rtxns::NetworkLayout& SourceLayout,
                        const rtxns::NetworkLayout& DestLayout,
                        FRHIBuffer* SourceBuffer,
                        uint64 SourceOffset,
                        FRHIBuffer* DestBuffer,
                        uint64 DestOffset,
                        FRHICommandListImmediate& RHICmdList) override;

private:
    FRTXNSRHIInteropRef Interop;
    std::shared_ptr<rtxns::NetworkUtilities> NetworkUtils;
};
