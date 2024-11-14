// Copyright (c) 2024 UltiMaker
// CuraEngine is released under the terms of the AGPLv3 or higher

#ifndef PATHPROCESSING_FEATUREEXTRUSIONSCONSTRAINTSGENERATOR_H
#define PATHPROCESSING_FEATUREEXTRUSIONSCONSTRAINTSGENERATOR_H

#include <vector>

#include "path_planning/FeatureExtrusionsPtr.h"

namespace cura
{

class FeatureExtrusion;
struct FeatureExtrusionOrderingConstraint;

class FeatureExtrusionsConstraintsGenerator
{
public:
    virtual void appendConstraints(const std::vector<FeatureExtrusionPtr>& feature_extrusions, std::vector<FeatureExtrusionOrderingConstraint>& constraints) const = 0;
};

} // namespace cura

#endif // PATHPROCESSING_FEATUREEXTRUSIONSCONSTRAINTSGENERATOR_H
