#pragma once

#include "effect.hpp"
#include "nlohmann/json-qt.hpp"

class ReshadeEffect : public Effect
{
    Q_OBJECT
public:
    explicit ReshadeEffect(const QString& name, nlohmann::json& j, QObject* parent = nullptr);

    bool isReshade() const override;
    void openSettingsDialog(QWidget* parent) override;
};
