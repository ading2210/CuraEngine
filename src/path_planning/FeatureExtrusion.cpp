// Copyright (c) 2024 UltiMaker
// CuraEngine is released under the terms of the AGPLv3 or higher

#include "path_planning/FeatureExtrusion.h"

#include "path_planning/ExtrusionMove.h"

namespace cura
{

FeatureExtrusion::FeatureExtrusion(const GCodePathConfig& config)
    : config_(config)
{
}

void FeatureExtrusion::addExtrusionMove(const Point3LL& position, const Ratio& line_width_ratio)
{
    auto extrusion_move = std::make_shared<ExtrusionMove>(position, line_width_ratio);
    appendExtruderMove(extrusion_move);
}

const Velocity& FeatureExtrusion::getSpeed() const
{
    return config_.getSpeed();
}

PrintFeatureType FeatureExtrusion::getPrintFeatureType() const
{
    return config_.getPrintFeatureType();
}

coord_t FeatureExtrusion::getLineWidth() const
{
    return std::llrint(getFlow() * getWidthFactor() * static_cast<double>(config_.getLineWidth()) * config_.getFlowRatio());
}

coord_t FeatureExtrusion::getLayerThickness() const
{
    return config_.getLayerThickness();
}

double FeatureExtrusion::getExtrusionMM3perMM() const
{
    return config_.getExtrusionMM3perMM();
}

const Ratio& FeatureExtrusion::getFlow() const
{
    return flow_;
}

const Ratio& FeatureExtrusion::getWidthFactor() const
{
    return width_factor_;
}

} // namespace cura
