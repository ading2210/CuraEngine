// Copyright (c) 2024 UltiMaker
// CuraEngine is released under the terms of the AGPLv3 or higher

#ifndef PATHEXPORT_MULTIEXPORTER_H
#define PATHEXPORT_MULTIEXPORTER_H

#include <memory>
#include <vector>

#include "path_export/PathExporter.h"

namespace cura
{

class MultiExporter : public PathExporter
{
public:
    void appendExporter(const std::shared_ptr<PathExporter> exporter);

    virtual void writeExtrusion(
        const Point3LL& p,
        const Velocity& speed,
        const double extrusion_mm3_per_mm,
        const coord_t line_width,
        const coord_t line_thickness,
        const PrintFeatureType feature,
        const bool update_extrusion_offset) override;

    virtual void writeTravelMove(const Point3LL& position, const Velocity& speed, const PrintFeatureType feature) override;

    virtual void writeLayerStart(const LayerIndex& layer_index, const Point3LL& start_position) override;

    virtual void writeLayerEnd(const LayerIndex& layer_index, const coord_t z, const coord_t layer_thickness) override;

private:
    std::vector<std::shared_ptr<PathExporter>> exporters_;
};

} // namespace cura

#endif // PATHEXPORT_MULTIEXPORTER_H
