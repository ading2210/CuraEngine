// Copyright (c) 2024 UltiMaker
// CuraEngine is released under the terms of the AGPLv3 or higher.

#include "utils/scoring/ExclusionAreaScoringCriterion.h"

#include "geometry/Shape.h"
#include "path_processing/StartCandidatePoint.h"


namespace cura
{

ExclusionAreaScoringCriterion::ExclusionAreaScoringCriterion(const std::vector<StartCandidatePoint>& points, const std::shared_ptr<Shape>& exclusion_area)
    : points_(points)
    , exclusion_area_(exclusion_area)
{
}

double ExclusionAreaScoringCriterion::computeScore(const size_t candidate_index) const
{
    const Point2LL candidate_position = points_.at(candidate_index).position.toPoint2LL();
    return exclusion_area_->inside(candidate_position, true) ? 0.0 : 1.0;
}

} // namespace cura
