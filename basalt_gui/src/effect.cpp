#include "effect.hpp"
#include "casdialog.hpp"
#include "debanddialog.hpp"
#include "dlsdialog.hpp"
#include "fxaadialog.hpp"
#include "lutdialog.hpp"
#include "smaadialog.hpp"

Effect::Effect(nlohmann::json& j, QObject* parent) : QObject(parent), json(j)
{
}

void Effect::openSettingsDialog(QWidget*)
{
    assert(false);
}

CasEffect::CasEffect(nlohmann::json& j, QObject* parent) : Effect(j, parent)
{
    name = "cas";
    desc = tr("Contrast Adaptive Sharpening");
}

void CasEffect::openSettingsDialog(QWidget* parent)
{
    CasDialog dlg(json, parent);
    dlg.exec();
}

DlsEffect::DlsEffect(nlohmann::json& j, QObject* parent) : Effect(j, parent)
{
    name = "dls";
    desc = tr("Denoised Luma Sharpening");
}

void DlsEffect::openSettingsDialog(QWidget* parent)
{
    DlsDialog dlg(json, parent);
    dlg.exec();
}

FxaaEffect::FxaaEffect(nlohmann::json& j, QObject* parent) : Effect(j, parent)
{
    name = "fxaa";
    desc = tr("Fast Approximate Anti-Aliasing");
}

void FxaaEffect::openSettingsDialog(QWidget* parent)
{
    FxaaDialog dlg(json, parent);
    dlg.exec();
}

SmaaEffect::SmaaEffect(nlohmann::json& j, QObject* parent) : Effect(j, parent)
{
    name = "smaa";
    desc = tr("Enhanced Subpixel Morphological Antialiasing");
}

void SmaaEffect::openSettingsDialog(QWidget* parent)
{
    SmaaDialog dlg(json, parent);
    dlg.exec();
}

LutEffect::LutEffect(nlohmann::json& j, QObject* parent) : Effect(j, parent)
{
    name = "lut";
    desc = tr("Color LookUp Table");
}

void LutEffect::openSettingsDialog(QWidget* parent)
{
    LutDialog dlg(json, parent);
    dlg.exec();
}

DebandEffect::DebandEffect(nlohmann::json& j, QObject* parent) : Effect(j, parent)
{
    name = "deband";
    desc = tr("Deband");
}

void DebandEffect::openSettingsDialog(QWidget* parent)
{
    DebandDialog dlg(json, parent);
    dlg.exec();
}
