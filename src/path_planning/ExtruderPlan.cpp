// Copyright (c) 2023 UltiMaker
// CuraEngine is released under the terms of the AGPLv3 or higher

#include "path_planning/ExtruderPlan.h"

#include "path_planning/FeatureExtrusion.h"
#include "path_processing/AddTravelMovesProcessor.h"

namespace cura
{
ExtruderPlan::ExtruderPlan(
    const size_t extruder,
    const LayerIndex layer_nr,
    const bool is_initial_layer,
    const bool is_raft_layer,
    const coord_t layer_thickness,
    const FanSpeedLayerTimeSettings& fan_speed_layer_time_settings,
    const RetractionConfig& retraction_config,
    const SpeedDerivatives& travel_speed)
    : extruder_nr_(extruder)
    , layer_nr_(layer_nr)
    , is_initial_layer_(is_initial_layer)
    , is_raft_layer_(is_raft_layer)
    , layer_thickness_(layer_thickness)
    , fan_speed_layer_time_settings_(fan_speed_layer_time_settings)
    , retraction_config_(retraction_config)
    , travel_speed_(travel_speed)
{
}

void ExtruderPlan::insertCommand(NozzleTempInsert&& insert)
{
    inserts_.emplace_back(insert);
}

void ExtruderPlan::handleInserts(const size_t path_idx, GCodeExporter& gcode, const double cumulative_path_time)
{
    while (! inserts_.empty() && path_idx >= inserts_.front().path_idx && inserts_.front().time_after_path_start < cumulative_path_time)
    { // handle the Insert to be inserted before this path_idx (and all inserts not handled yet)
        inserts_.front().write(gcode);
        inserts_.pop_front();
    }
}

void ExtruderPlan::handleAllRemainingInserts(GCodeExporter& gcode)
{
    while (! inserts_.empty())
    { // handle the Insert to be inserted before this path_idx (and all inserts not handled yet)
        NozzleTempInsert& insert = inserts_.front();
        insert.write(gcode);
        inserts_.pop_front();
    }
}

void ExtruderPlan::setFanSpeed(double _fan_speed)
{
    fan_speed = _fan_speed;
}
double ExtruderPlan::getFanSpeed()
{
    return fan_speed;
}

const SpeedDerivatives& ExtruderPlan::getTravelSpeed() const
{
    return travel_speed_;
}

void ExtruderPlan::applyBackPressureCompensation(const Ratio back_pressure_compensation)
{
    constexpr double epsilon_speed_factor = 0.001; // Don't put on actual 'limit double minimum', because we don't want printers to stall.
    for (auto& path : paths_)
    {
        const double nominal_width_for_path = static_cast<double>(path.config.getLineWidth());
        if (path.width_factor <= 0.0 || nominal_width_for_path <= 0.0 || path.config.isTravelPath() || path.config.isBridgePath())
        {
            continue;
        }
        const double line_width_for_path = path.width_factor * nominal_width_for_path;
        path.speed_back_pressure_factor = std::max(epsilon_speed_factor, 1.0 + (nominal_width_for_path / line_width_for_path - 1.0) * back_pressure_compensation);
    }
}

void ExtruderPlan::appendFeatureExtrusion(const std::shared_ptr<FeatureExtrusion>& feature_extrusion, const bool check_non_empty)
{
    if (! check_non_empty || ! feature_extrusion->empty())
    {
        appendOperation(feature_extrusion);
    }
}

void ExtruderPlan::applyProcessors(const std::vector<const PrintOperation*>& parents)
{
    PrintOperationSequence::applyProcessors(parents);

    AddTravelMovesProcessor<ExtruderPlan, FeatureExtrusion> add_travel_moves_processor(travel_speed_);
    add_travel_moves_processor.process(this);
}

} // namespace cura
