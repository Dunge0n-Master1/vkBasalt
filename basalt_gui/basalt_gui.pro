QT += core gui widgets

CONFIG += c++17 lrelease embed_translations

DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000

INCLUDEPATH += ../src/reshade/

SOURCES += \
    src/casdialog.cpp \
    src/debanddialog.cpp \
    src/defsmodel.cpp \
    src/dlsdialog.cpp \
    src/effect.cpp \
    src/effectslist.cpp \
    src/fxaadialog.cpp \
    src/ignorewheeleventfilter.cpp \
    src/lutdialog.cpp \
    src/main.cpp \
    src/mainwindow.cpp \
    src/pathlistmodel.cpp \
    ../src/reshade/effect_expression.cpp \
    ../src/reshade/effect_symbol_table.cpp \
    ../src/reshade/effect_lexer.cpp \
    ../src/reshade/effect_parser.cpp \
    ../src/reshade/effect_preprocessor.cpp \
    ../src/reshade/effect_codegen_spirv.cpp \
    src/reshadedialog.cpp \
    src/reshadeeffect.cpp \
    src/settingsdialog.cpp \
    src/smaadialog.cpp

HEADERS += \
    src/casdialog.hpp \
    src/debanddialog.hpp \
    src/defsmodel.hpp \
    src/dlsdialog.hpp \
    src/effect.hpp \
    src/effectslist.hpp \
    src/fxaadialog.hpp \
    src/ignorewheeleventfilter.hpp \
    src/lutdialog.hpp \
    src/mainwindow.hpp \
    nlohmann/json.hpp \
    nlohmann/json-qt.hpp \
    src/pathlistmodel.hpp \
    ../src/reshade/effect_parser.hpp \
    ../src/reshade/effect_expression.hpp \
    ../src/reshade/effect_lexer.hpp \
    ../src/reshade/effect_symbol_table.hpp \
    ../src/reshade/effect_module.hpp \
    ../src/reshade/effect_token.hpp \
    ../src/reshade/effect_codegen.hpp \
    ../src/reshade/effect_preprocessor.hpp \
    src/reshadedialog.hpp \
    src/reshadeeffect.hpp \
    src/settingsdialog.hpp \
    src/smaadialog.hpp

FORMS += \
    ui/casdialog.ui \
    ui/debanddialog.ui \
    ui/dlsdialog.ui \
    ui/fxaadialog.ui \
    ui/lutdialog.ui \
    ui/mainwindow.ui \
    ui/reshadedialog.ui \
    ui/settingsdialog.ui \
    ui/smaadialog.ui

TRANSLATIONS += \
    i18n/vkBasaltGui_ru_RU.ts

target.path = $$INSTALL_ROOT/bin
INSTALLS += target
