// Copyright (c) 2024 UltiMaker
// CuraEngine is released under the terms of the AGPLv3 or higher

#ifndef PATHEXPORT_COMMUNICATIONEXPORTER_H
#define PATHEXPORT_COMMUNICATIONEXPORTER_H

#include <memory>
#include <vector>

#include "path_export/PathExporter.h"

namespace cura
{
class Communication;

class CommunicationExporter : public PathExporter
{
public:
    explicit CommunicationExporter(const std::shared_ptr<Communication>& communication);

    virtual void writeExtrusion(
        const Point3LL& p,
        const Velocity& speed,
        const double extrusion_mm3_per_mm,
        const coord_t line_width,
        const coord_t line_thickness,
        const PrintFeatureType feature,
        const bool update_extrusion_offset) override;

private:
    std::shared_ptr<Communication> communication_;
};

} // namespace cura

#endif // PATHEXPORT_COMMUNICATIONEXPORTER_H
