#pragma once

namespace VkShared::Enums {

enum class QueueFamily {
  Graphics,
  Transfer,
  Presentation,
  Compute
};

enum class PipelineType {
  Standard
};

}  // namespace VkShared::Enums
