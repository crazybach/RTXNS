#pragma once

#include "CoreMinimal.h"
#include "RHI.h"
#include "RHICommandList.h"

#include <memory>

namespace nvrhi
{
    class IDevice;
    class ICommandList;
    class IBuffer;
    using DeviceHandle = std::shared_ptr<IDevice>;
    using CommandListHandle = std::shared_ptr<ICommandList>;
    using BufferHandle = std::shared_ptr<IBuffer>;
}

class IRTXNSRHIInterop
{
public:
    virtual ~IRTXNSRHIInterop() = default;

    virtual FRHIBuffer* CreateBuffer(uint64 Size, EBufferUsageFlags Usage, ERHIAccess Access, const TCHAR* DebugName) = 0;
    virtual void UpdateBuffer(FRHICommandListImmediate& RHICmdList, FRHIBuffer* Buffer, uint64 Offset, const void* Data, uint64 Size) = 0;
    virtual void CopyBuffer(FRHICommandListImmediate& RHICmdList, FRHIBuffer* Dest, uint64 DestOffset, FRHIBuffer* Source, uint64 SourceOffset, uint64 Size) = 0;
    virtual void SubmitCommands(FRHICommandListImmediate& RHICmdList) = 0;

    virtual nvrhi::DeviceHandle GetNvrhiDevice() const = 0;
    virtual nvrhi::CommandListHandle GetNvrhiCommandList(FRHICommandListImmediate& RHICmdList) const = 0;
    virtual nvrhi::BufferHandle GetNvrhiBuffer(FRHIBuffer* Buffer) const = 0;
};

using FRTXNSRHIInteropRef = TSharedRef<IRTXNSRHIInterop, ESPMode::ThreadSafe>;
