#include "reshadeeffect.hpp"
#include "reshadedialog.hpp"

ReshadeEffect::ReshadeEffect(const QString& n, nlohmann::json& j, QObject* parent) : Effect(j, parent)
{
    name = n;
}

bool ReshadeEffect::isReshade() const
{
    return true;
}

void ReshadeEffect::openSettingsDialog(QWidget* parent)
{
    ReshadeDialog dlg(json, &name, &desc, parent);
    dlg.exec();
}
