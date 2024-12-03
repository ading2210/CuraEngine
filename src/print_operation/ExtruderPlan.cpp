// Copyright (c) 2024 UltiMaker
// CuraEngine is released under the terms of the AGPLv3 or higher

#include "print_operation/ExtruderPlan.h"

#include "print_operation/FeatureExtrusion.h"

namespace cura
{

ExtruderPlan::ExtruderPlan(const size_t extruder_nr, const SpeedDerivatives& travel_speed) noexcept
    : extruder_nr_(extruder_nr)
    , travel_speed_(travel_speed)
{
}

size_t ExtruderPlan::getExtruderNr() const noexcept
{
    return extruder_nr_;
}

const SpeedDerivatives& ExtruderPlan::getTravelSpeed() const noexcept
{
    return travel_speed_;
}

void ExtruderPlan::appendFeatureExtrusion(const std::shared_ptr<FeatureExtrusion>& feature_extrusion, const bool check_non_empty)
{
    if (! check_non_empty || ! feature_extrusion->empty())
    {
        appendOperation(feature_extrusion);
    }
}

} // namespace cura
