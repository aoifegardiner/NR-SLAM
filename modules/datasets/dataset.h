#pragma once

#include <memory>

namespace dataset {

// Forward declaration of FrameBase
class FrameBase {
public:
    using Ptr = std::shared_ptr<FrameBase>;  // ✅ Fix this to refer to FrameBase
    virtual ~FrameBase() = default;
};

// Abstract base class for stereo datasets
class StereoDataset {
public:
    using Ptr = std::shared_ptr<StereoDataset>;

    virtual ~StereoDataset() = default;

    // Initialize the dataset (e.g., load image paths)
    virtual bool Init() = 0;

    // Load the next stereo frame pair
    virtual bool NextFrame(FrameBase::Ptr& left_frame, FrameBase::Ptr& right_frame) = 0;  // ✅ Use FrameBase
};

}  // namespace dataset
