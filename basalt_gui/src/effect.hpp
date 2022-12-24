#pragma once

#include <QObject>

#include "nlohmann/json-qt.hpp"

class Effect : public QObject
{
    Q_OBJECT
public:
    explicit Effect(nlohmann::json& j, QObject* parent = nullptr);

    virtual bool isReshade() const
    {
        return false;
    }

    const QString& getName() const
    {
        return name;
    }
    const QString& getDesc() const
    {
        return desc;
    }

public slots:
    virtual void openSettingsDialog(QWidget* parent);

protected:
    QString         name;
    QString         desc;
    nlohmann::json& json;
};

class CasEffect : public Effect
{
    Q_OBJECT
public:
    explicit CasEffect(nlohmann::json& j, QObject* parent = nullptr);

    void openSettingsDialog(QWidget* parent) override;
};

class DlsEffect : public Effect
{
    Q_OBJECT
public:
    explicit DlsEffect(nlohmann::json& j, QObject* parent = nullptr);

    void openSettingsDialog(QWidget* parent) override;
};

class FxaaEffect : public Effect
{
    Q_OBJECT
public:
    explicit FxaaEffect(nlohmann::json& j, QObject* parent = nullptr);

    void openSettingsDialog(QWidget* parent) override;
};

class SmaaEffect : public Effect
{
    Q_OBJECT
public:
    explicit SmaaEffect(nlohmann::json& j, QObject* parent = nullptr);

    void openSettingsDialog(QWidget* parent) override;
};

class LutEffect : public Effect
{
    Q_OBJECT
public:
    explicit LutEffect(nlohmann::json& j, QObject* parent = nullptr);

    void openSettingsDialog(QWidget* parent) override;
};

class DebandEffect : public Effect
{
    Q_OBJECT
public:
    explicit DebandEffect(nlohmann::json& j, QObject* parent = nullptr);

    void openSettingsDialog(QWidget* parent) override;
};
