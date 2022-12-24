<?xml version="1.0" encoding="utf-8"?>
<!DOCTYPE TS>
<TS version="2.1" language="ru_RU">
<context>
    <name>CasDialog</name>
    <message>
        <location filename="../ui/casdialog.ui" line="14"/>
        <source>CAS effect settings</source>
        <translation>Настройки эффекта CAS</translation>
    </message>
    <message>
        <location filename="../ui/casdialog.ui" line="20"/>
        <source>&lt;html&gt;&lt;head/&gt;&lt;body&gt;&lt;p&gt;Sharpness specifies the amount of sharpening in the CAS shader.&lt;/p&gt;&lt;p&gt;0.0 less sharp, less artefacts, but not off.&lt;/p&gt;&lt;p&gt;1.0 maximum sharp more artefacts.&lt;/p&gt;&lt;p&gt;Everything in between is possible negative values sharpen even less, up to -1.0 make a visible difference.&lt;/p&gt;&lt;/body&gt;&lt;/html&gt;</source>
        <translation>&lt;html&gt;&lt;head/&gt;&lt;body&gt;&lt;p&gt;Резкость указывает степень повышения резкости в шейдере CAS.&lt;/p&gt;&lt;p&gt;0.0 - меньше резкость, меньше артефактов.&lt;/p&gt;&lt;p&gt;1.0 - максимальная резкость, больше артефактов.&lt;/p&gt;&lt;p&gt;Возможны отрицательные значения(эффект заметен  до -1.0)&lt;/p&gt;&lt;/body&gt;&lt;/html&gt;</translation>
    </message>
    <message>
        <location filename="../ui/casdialog.ui" line="23"/>
        <source>Sharpness</source>
        <translation>Резкость</translation>
    </message>
</context>
<context>
    <name>CasEffect</name>
    <message>
        <location filename="../src/effect.cpp" line="24"/>
        <source>Contrast Adaptive Sharpening</source>
        <translation>Контрастно-адаптивная резкость(CAS - Contrast Adaptive Sharpening)</translation>
    </message>
</context>
<context>
    <name>DebandDialog</name>
    <message>
        <location filename="../ui/debanddialog.ui" line="14"/>
        <source>Deband effect settings</source>
        <translation>Настройки эффекта Deband</translation>
    </message>
    <message>
        <location filename="../ui/debanddialog.ui" line="20"/>
        <source>Avgdiff</source>
        <translation>Средняя разница</translation>
    </message>
    <message>
        <location filename="../ui/debanddialog.ui" line="48"/>
        <source>Maxdiff</source>
        <translation>Максимальная разница</translation>
    </message>
    <message>
        <location filename="../ui/debanddialog.ui" line="76"/>
        <source>Middiff</source>
        <translation>Средняя разница</translation>
    </message>
    <message>
        <location filename="../ui/debanddialog.ui" line="104"/>
        <source>Range</source>
        <translation>Диапазон</translation>
    </message>
    <message>
        <location filename="../ui/debanddialog.ui" line="132"/>
        <source>Iterations</source>
        <translation>Количество итераций</translation>
    </message>
</context>
<context>
    <name>DebandEffect</name>
    <message>
        <location filename="../src/effect.cpp" line="89"/>
        <source>Deband</source>
        <translation>Эффект смягчающий ступенчатые градиенты</translation>
    </message>
</context>
<context>
    <name>DlsDialog</name>
    <message>
        <location filename="../ui/dlsdialog.ui" line="14"/>
        <source>DLS effect settings</source>
        <translation>Настройки эффекта DLS</translation>
    </message>
    <message>
        <location filename="../ui/dlsdialog.ui" line="20"/>
        <source>&lt;html&gt;&lt;head/&gt;&lt;body&gt;&lt;p&gt;Sharpness specifies the amount of sharpening in the Denoised Luma Sharpening shader.&lt;/p&gt;&lt;p&gt;Increase to sharpen details within the image.&lt;/p&gt;&lt;p&gt;0.0 less sharp, less artefacts, but not off&lt;/p&gt;&lt;p&gt;1.0 maximum sharp more artefacts&lt;/p&gt;&lt;/body&gt;&lt;/html&gt;</source>
        <translation>&lt;html&gt;&lt;head/&gt;&lt;body&gt;&lt;p&gt;Определяет уровень резкости в шейдере DLS.&lt;/p&gt;&lt;p&gt;Увеличьте, чтобы повысить резкость деталей изображения.&lt;/p&gt;&lt;p&gt;0.0 меньше резкость, меньше артефактов&lt;/p&gt;&lt;p&gt;1.0 больше резкость, больше артефактов&lt;/p&gt;&lt;/body&gt;&lt;/html&gt;</translation>
    </message>
    <message>
        <location filename="../ui/dlsdialog.ui" line="23"/>
        <source>Sharpness</source>
        <translation>Резкость</translation>
    </message>
    <message>
        <location filename="../ui/dlsdialog.ui" line="51"/>
        <source>&lt;html&gt;&lt;head/&gt;&lt;body&gt;&lt;p&gt;Denoise specifies the amount of denoising in the Denoised Luma Sharpening shader.&lt;/p&gt;&lt;p&gt;Increase to limit how intensely film grain within the image gets sharpened.&lt;/p&gt;&lt;p&gt;0.0 min&lt;/p&gt;&lt;p&gt;1.0 max&lt;/p&gt;&lt;/body&gt;&lt;/html&gt;</source>
        <translation>&lt;html&gt;&lt;head/&gt;&lt;body&gt;&lt;p&gt;Определяет степень шумоподавления в шейдере DLS.&lt;/p&gt;&lt;p&gt;Увеличьте, чтобы уменьшить количество шумов.&lt;/p&gt;&lt;p&gt;Минимум: 0.0&lt;/p&gt;&lt;p&gt;Максимум: 1.0&lt;/p&gt;&lt;/body&gt;&lt;/html&gt;</translation>
    </message>
    <message>
        <location filename="../ui/dlsdialog.ui" line="54"/>
        <source>Denoise</source>
        <translation>Шумоподавление</translation>
    </message>
</context>
<context>
    <name>DlsEffect</name>
    <message>
        <location filename="../src/effect.cpp" line="37"/>
        <source>Denoised Luma Sharpening</source>
        <translation>Шумоподавление и увеличение резкости(DLS - Denoised Luma Sharpening)</translation>
    </message>
</context>
<context>
    <name>FxaaDialog</name>
    <message>
        <location filename="../ui/fxaadialog.ui" line="14"/>
        <source>FXAA effect settings</source>
        <translation>Настройки эффекта FXAA</translation>
    </message>
    <message>
        <location filename="../ui/fxaadialog.ui" line="20"/>
        <source>&lt;html&gt;&lt;head/&gt;&lt;body&gt;&lt;p&gt;fxaaQualitySubpix can effect sharpness.&lt;/p&gt;&lt;p&gt;1.00 - upper limit (softer)&lt;/p&gt;&lt;p&gt;0.75 - default amount of filtering&lt;/p&gt;&lt;p&gt;0.50 - lower limit (sharper, less sub-pixel aliasing removal)&lt;/p&gt;&lt;p&gt;0.25 - almost off&lt;/p&gt;&lt;p&gt;0.00 - completely off&lt;/p&gt;&lt;/body&gt;&lt;/html&gt;</source>
        <translation>&lt;html&gt;&lt;head/&gt;&lt;body&gt;&lt;p&gt;fxaaQualitySubpix может влиять на резкость.&lt;/p&gt;&lt;p&gt;1.00 - рекомендованный максимум&lt;/p&gt;&lt;p&gt;0.75 - степень фильтрации по умолчанию&lt;/p&gt;&lt;p&gt;0.50 - нижний предел (большая резкость, меньшее удаление субпиксельного наложения)&lt;/p&gt;&lt;p&gt;0.25 - почти выключено&lt;/p&gt;&lt;p&gt;0.00 - полностью выключено&lt;/p&gt;&lt;/body&gt;&lt;/html&gt;</translation>
    </message>
    <message>
        <location filename="../ui/fxaadialog.ui" line="23"/>
        <source>QualitySubpix</source>
        <translation>Качество субпикселей</translation>
    </message>
    <message>
        <location filename="../ui/fxaadialog.ui" line="51"/>
        <source>&lt;html&gt;&lt;head/&gt;&lt;body&gt;&lt;p&gt;fxaaQualityEdgeThreshold is the minimum amount of local contrast required to apply algorithm.&lt;/p&gt;&lt;p&gt;0.333 - too little (faster)&lt;/p&gt;&lt;p&gt;0.250 - low quality&lt;/p&gt;&lt;p&gt;0.166 - default&lt;/p&gt;&lt;p&gt;0.125 - high quality &lt;/p&gt;&lt;p&gt;0.063 - overkill (slower)&lt;/p&gt;&lt;/body&gt;&lt;/html&gt;</source>
        <translation>&lt;html&gt;&lt;head/&gt;&lt;body&gt;&lt;p&gt;fxaaQualityEdgeThreshold — это минимальное количество локальной контрастности, необходимое для применения алгоритма.&lt;/p&gt;&lt;p&gt;0.333 - очень низкое(быстро)&lt;/p&gt;&lt;p&gt;0.250 - низкое&lt;/p&gt;&lt;p&gt;0.166 - стандартное&lt;/p&gt;&lt;p&gt;0.125 - высокое &lt;/p&gt;&lt;p&gt;0.063 - слишком высокое(медленно)&lt;/p&gt;&lt;/body&gt;&lt;/html&gt;</translation>
    </message>
    <message>
        <location filename="../ui/fxaadialog.ui" line="54"/>
        <source>QualityEdgeThreshold</source>
        <translation>Порог качества краёв</translation>
    </message>
    <message>
        <location filename="../ui/fxaadialog.ui" line="82"/>
        <source>&lt;html&gt;&lt;head/&gt;&lt;body&gt;&lt;p&gt;fxaaQualityEdgeThresholdMin trims the algorithm from processing darks.&lt;/p&gt;&lt;p&gt;0.0833 - upper limit (default, the start of visible unfiltered edges)&lt;/p&gt;&lt;p&gt;0.0625 - high quality (faster)&lt;/p&gt;&lt;p&gt;0.0312 - visible limit (slower)&lt;/p&gt;&lt;p&gt;Special notes: due to the current implementation you&lt;/p&gt;&lt;p&gt;Likely want to set this to zero.&lt;/p&gt;&lt;p&gt;As colors that are mostly not-green&lt;/p&gt;&lt;p&gt;will appear very dark in the green channel!&lt;/p&gt;&lt;p&gt;Tune by looking at mostly non-green content,&lt;/p&gt;&lt;p&gt;then start at zero and increase until aliasing is a problem.&lt;/p&gt;&lt;/body&gt;&lt;/html&gt;</source>
        <translation>&lt;html&gt;&lt;head/&gt;&lt;body&gt;&lt;p&gt;fxaaQualityEdgeThresholdMin фильтрует обработку темных участков.&lt;/p&gt;&lt;p&gt;0.0833 - верхний предел(начало видимых нефильтрованных краев)&lt;/p&gt;&lt;p&gt;0.0625 - высокое качество(быстро)&lt;/p&gt;&lt;p&gt;0.0312 - видимый предел(медленно)&lt;/p&gt;&lt;p&gt;Из-за текущей реализации вы, вероятно, захотите установить это значение равным нулю.&lt;/p&gt;&lt;p&gt;Поскольку цвета, которые в основном не зеленые, будут казаться очень темными в зеленом канале!&lt;/p&gt;&lt;p&gt;Настраивайте, ориентируясь в основном на не зеленый контент, начиная с нуля и увеличивая до тех пор, пока не возникнет проблема наложения...&lt;/p&gt;&lt;/body&gt;&lt;/html&gt;</translation>
    </message>
    <message>
        <location filename="../ui/fxaadialog.ui" line="85"/>
        <source>QualityEdgeThresholdMin</source>
        <translation>Порог качества краёв(минимальный)</translation>
    </message>
</context>
<context>
    <name>FxaaEffect</name>
    <message>
        <location filename="../src/effect.cpp" line="50"/>
        <source>Fast Approximate Anti-Aliasing</source>
        <translation>Быстрое приблизительное сглаживание(FXAA - Fast Approximate Anti-Aliasing)</translation>
    </message>
</context>
<context>
    <name>LutDialog</name>
    <message>
        <location filename="../ui/lutdialog.ui" line="14"/>
        <source>LUT effect settings</source>
        <translation>Настройки эффекта LUT</translation>
    </message>
    <message>
        <location filename="../ui/lutdialog.ui" line="20"/>
        <source>&lt;html&gt;&lt;head/&gt;&lt;body&gt;&lt;p&gt;lutFile is the path to the LUT file that will be used&lt;/p&gt;&lt;p&gt;supported are .CUBE files and .png with width == height * height&lt;/p&gt;&lt;/body&gt;&lt;/html&gt;</source>
        <translation>&lt;html&gt;&lt;head/&gt;&lt;body&gt;&lt;p&gt;Пусть к файлу LUT&lt;/p&gt;&lt;p&gt;поддерживаются форматы CUBE и PNG с (ширина = высота * высота)&lt;/p&gt;&lt;/body&gt;&lt;/html&gt;</translation>
    </message>
    <message>
        <location filename="../ui/lutdialog.ui" line="23"/>
        <source>File</source>
        <translation>Файл</translation>
    </message>
    <message>
        <location filename="../src/lutdialog.cpp" line="27"/>
        <source>Select LUT file</source>
        <translation>Выберите файл LUT</translation>
    </message>
</context>
<context>
    <name>LutEffect</name>
    <message>
        <location filename="../src/effect.cpp" line="76"/>
        <source>Color LookUp Table</source>
        <translation>Таблица поиска цветов(LUT - Color LookUp Table)</translation>
    </message>
</context>
<context>
    <name>MainWindow</name>
    <message>
        <location filename="../ui/mainwindow.ui" line="21"/>
        <source>Avaliable</source>
        <translation>Доступные</translation>
    </message>
    <message>
        <location filename="../ui/mainwindow.ui" line="52"/>
        <source>Use selected effect</source>
        <translation>Использовать выбранный эффект</translation>
    </message>
    <message>
        <location filename="../ui/mainwindow.ui" line="62"/>
        <source>Open selected effect`s parameters</source>
        <translation>Открыть параметры выбранного эффекта</translation>
    </message>
    <message>
        <location filename="../ui/mainwindow.ui" line="65"/>
        <source>parameters</source>
        <translation>параметры</translation>
    </message>
    <message>
        <location filename="../ui/mainwindow.ui" line="72"/>
        <source>Add effect</source>
        <translation>Добавить эффект</translation>
    </message>
    <message>
        <location filename="../ui/mainwindow.ui" line="82"/>
        <source>Add all effects from directory</source>
        <translation>Добавить все эффекты из директории</translation>
    </message>
    <message>
        <location filename="../ui/mainwindow.ui" line="85"/>
        <source>add from dir</source>
        <translation>добавить из
директории</translation>
    </message>
    <message>
        <location filename="../ui/mainwindow.ui" line="99"/>
        <source>Remove selected effect from list</source>
        <translation>Удалить выбранный эффект из списка</translation>
    </message>
    <message>
        <location filename="../ui/mainwindow.ui" line="127"/>
        <source>Used</source>
        <translation>Используемые</translation>
    </message>
    <message>
        <location filename="../ui/mainwindow.ui" line="151"/>
        <source>Move selected effect upper</source>
        <translation>Поднять выбранный эффект</translation>
    </message>
    <message>
        <location filename="../ui/mainwindow.ui" line="154"/>
        <source>up</source>
        <translation>вверх</translation>
    </message>
    <message>
        <location filename="../ui/mainwindow.ui" line="161"/>
        <source>Move selected effect down</source>
        <translation>Опустить выбранный эффект</translation>
    </message>
    <message>
        <location filename="../ui/mainwindow.ui" line="164"/>
        <source>down</source>
        <translation>вниз</translation>
    </message>
    <message>
        <location filename="../ui/mainwindow.ui" line="178"/>
        <source>Remove selected effect from used effects list</source>
        <translation>Убрать выбранный эффект из используемых</translation>
    </message>
    <message>
        <location filename="../ui/mainwindow.ui" line="223"/>
        <source>File</source>
        <translation>Файл</translation>
    </message>
    <message>
        <location filename="../ui/mainwindow.ui" line="263"/>
        <source>Save</source>
        <translation>Сохранить</translation>
    </message>
    <message>
        <location filename="../ui/mainwindow.ui" line="266"/>
        <source>Save file</source>
        <translation>Сохранить файл</translation>
    </message>
    <message>
        <location filename="../ui/mainwindow.ui" line="278"/>
        <source>Save as</source>
        <translation>Сохранить как</translation>
    </message>
    <message>
        <location filename="../ui/mainwindow.ui" line="281"/>
        <source>Save file as</source>
        <translation>Сохранить файл как</translation>
    </message>
    <message>
        <location filename="../ui/mainwindow.ui" line="293"/>
        <source>Open</source>
        <translation>Открыть</translation>
    </message>
    <message>
        <location filename="../ui/mainwindow.ui" line="296"/>
        <source>Open file</source>
        <translation>Открыть файл</translation>
    </message>
    <message>
        <location filename="../ui/mainwindow.ui" line="308"/>
        <source>Settings</source>
        <translation>Настройки</translation>
    </message>
    <message>
        <location filename="../ui/mainwindow.ui" line="311"/>
        <source>Open settings</source>
        <translation>Открыть настройки</translation>
    </message>
    <message>
        <location filename="../ui/mainwindow.ui" line="320"/>
        <source>New</source>
        <translation>Новый</translation>
    </message>
    <message>
        <location filename="../ui/mainwindow.ui" line="323"/>
        <source>Create new file</source>
        <translation>Создать новый файл</translation>
    </message>
    <message>
        <location filename="../ui/mainwindow.ui" line="334"/>
        <source>Auto save</source>
        <translation>Автоматическое сохранение</translation>
    </message>
    <message>
        <location filename="../ui/mainwindow.ui" line="337"/>
        <source>Auto save file every 2 seconds</source>
        <translation>Автоматически сохранять файл каждые 2 секунды</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="82"/>
        <source>Do you really want to close this program without saving the configuration?</source>
        <translation>Вы действительно хотите закрыть эту программу не сохраняя конфигурацию?</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="94"/>
        <source>Open vkBasalt config file</source>
        <translation>Выберите конфиг vkBasalt</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="152"/>
        <source>Open failed</source>
        <translation>Не получилось открыть конфиг</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="170"/>
        <source>Save vkBasalt config file</source>
        <translation>Выберите файл, в который нужно сохранить конфиг vkBasalt</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="190"/>
        <source>Save failed</source>
        <translation>Не получилось сохранить конфиг</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="263"/>
        <source>Effect name:</source>
        <translation>Название эффекта:</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="277"/>
        <source>Select directory with *.fx files</source>
        <translation>Выберите директорию с файлами *.fx</translation>
    </message>
</context>
<context>
    <name>ReshadeDialog</name>
    <message>
        <location filename="../ui/reshadedialog.ui" line="14"/>
        <source>Reshade effect parameters</source>
        <translation>Параметры эффекта reshade</translation>
    </message>
    <message>
        <location filename="../ui/reshadedialog.ui" line="35"/>
        <source>Path to shader</source>
        <translation>Путь к шейдеру</translation>
    </message>
    <message>
        <location filename="../ui/reshadedialog.ui" line="38"/>
        <source>Shader</source>
        <translation>Шейдер</translation>
    </message>
    <message>
        <location filename="../ui/reshadedialog.ui" line="58"/>
        <source>Defines</source>
        <translation>Определения</translation>
    </message>
    <message>
        <location filename="../src/reshadedialog.cpp" line="79"/>
        <source>Select effect file</source>
        <translation>Выберите файл шейдера эффекта</translation>
    </message>
    <message>
        <location filename="../src/reshadedialog.cpp" line="195"/>
        <source>Reshade effect %1:
	Path: %2
</source>
        <translation>Эффект reshade %1:
	Путь: %2
</translation>
    </message>
    <message>
        <location filename="../src/reshadedialog.cpp" line="199"/>
        <source>	Technique &apos;%1&apos;:
</source>
        <translation>	Техника &apos;%1&apos;:
</translation>
    </message>
    <message>
        <location filename="../src/reshadedialog.cpp" line="259"/>
        <source>Min: %1
</source>
        <translation>Минимум: %1
</translation>
    </message>
    <message>
        <location filename="../src/reshadedialog.cpp" line="261"/>
        <source>Max: %1
</source>
        <translation>Максимум: %1
</translation>
    </message>
    <message>
        <location filename="../src/reshadedialog.cpp" line="306"/>
        <source>Change color</source>
        <translation>Изменить цвет</translation>
    </message>
    <message>
        <location filename="../src/reshadedialog.cpp" line="547"/>
        <source>Default: %1
</source>
        <translation>По умолчанию: %1
</translation>
    </message>
    <message>
        <location filename="../src/reshadedialog.cpp" line="566"/>
        <source>Input define name</source>
        <translation>Введите название определения</translation>
    </message>
</context>
<context>
    <name>SettingsDialog</name>
    <message>
        <location filename="../ui/settingsdialog.ui" line="14"/>
        <source>Settings</source>
        <translation>Настройки</translation>
    </message>
    <message>
        <location filename="../ui/settingsdialog.ui" line="20"/>
        <source>Toggle key</source>
        <translation>Кнопка переключения</translation>
    </message>
    <message>
        <location filename="../ui/settingsdialog.ui" line="36"/>
        <source>Reload key</source>
        <translation>Кнопка перезагрузки конфига</translation>
    </message>
    <message>
        <location filename="../ui/settingsdialog.ui" line="52"/>
        <location filename="../ui/settingsdialog.ui" line="58"/>
        <source>Enable on launch</source>
        <translation>Включить при старте приложения</translation>
    </message>
    <message>
        <location filename="../ui/settingsdialog.ui" line="68"/>
        <location filename="../ui/settingsdialog.ui" line="74"/>
        <source>Depth capture</source>
        <translation>Захват глубины</translation>
    </message>
    <message>
        <location filename="../ui/settingsdialog.ui" line="84"/>
        <source>Reshade include directories</source>
        <translation>Директории с заголовочниками для эффектов reshade</translation>
    </message>
    <message>
        <location filename="../ui/settingsdialog.ui" line="151"/>
        <source>Reshade texture directories</source>
        <translation>Директории с текстурами для эффектов reshade</translation>
    </message>
    <message>
        <location filename="../src/settingsdialog.cpp" line="128"/>
        <source>Select reshade textures directory</source>
        <translation>Выберите директорию с текстурами для эффектов reshade</translation>
    </message>
    <message>
        <location filename="../src/settingsdialog.cpp" line="148"/>
        <source>Select reshade include directory</source>
        <translation>Выберите директорию с заголовочниками для эффектов reshade</translation>
    </message>
</context>
<context>
    <name>SmaaDialog</name>
    <message>
        <location filename="../ui/smaadialog.ui" line="14"/>
        <source>SMAA effect settings</source>
        <translation>Настройки эффекта SMAA</translation>
    </message>
    <message>
        <location filename="../ui/smaadialog.ui" line="20"/>
        <source>&lt;html&gt;&lt;head/&gt;&lt;body&gt;&lt;p&gt;smaaEdgeDetection changes the edge detection shader:&lt;/p&gt;&lt;p&gt;luma  - default&lt;/p&gt;&lt;p&gt;color - might catch more edges, but is more expensive&lt;/p&gt;&lt;/body&gt;&lt;/html&gt;</source>
        <translation>&lt;html&gt;&lt;head/&gt;&lt;body&gt;&lt;p&gt;Выбирает способ поиска краёв:&lt;/p&gt;&lt;p&gt;яркость - по умолчанию&lt;/p&gt;&lt;p&gt;цвет - может найти больше краёв, но работает медленнее&lt;/p&gt;&lt;/body&gt;&lt;/html&gt;</translation>
    </message>
    <message>
        <location filename="../ui/smaadialog.ui" line="23"/>
        <source>EdgeDetection</source>
        <translation>Поиск краёв</translation>
    </message>
    <message>
        <location filename="../ui/smaadialog.ui" line="30"/>
        <source>luma</source>
        <translation>яркость</translation>
    </message>
    <message>
        <location filename="../ui/smaadialog.ui" line="35"/>
        <source>color</source>
        <translation>цвет</translation>
    </message>
    <message>
        <location filename="../ui/smaadialog.ui" line="46"/>
        <source>&lt;html&gt;&lt;head/&gt;&lt;body&gt;&lt;p&gt;smaaThreshold specifies the threshold or sensitivity to edges&lt;/p&gt;&lt;p&gt;Lowering this value you will be able to detect more edges at the expense of performance.&lt;/p&gt;&lt;p&gt;Range: [0, 0.5]&lt;/p&gt;&lt;p&gt;0.1 is a reasonable value, and allows to catch most visible edges.&lt;/p&gt;&lt;p&gt;0.05 is a rather overkill value, that allows to catch &apos;em all.&lt;/p&gt;&lt;/body&gt;&lt;/html&gt;</source>
        <translation>&lt;html&gt;&lt;head/&gt;&lt;body&gt;&lt;p&gt;Определяет чувствительность поиска краёв&lt;/p&gt;&lt;p&gt;Чем меньше значение, тем хуже производительность и больше краёв будет обнаружено&lt;/p&gt;&lt;p&gt;Диапазон: [0, 0.5]&lt;/p&gt;&lt;p&gt;0.1 - нормальное значение, позволяющие обнаружить все видимые края&lt;/p&gt;&lt;p&gt;0.05 - позволяет обнаружить все края.&lt;/p&gt;&lt;/body&gt;&lt;/html&gt;</translation>
    </message>
    <message>
        <location filename="../ui/smaadialog.ui" line="49"/>
        <source>Threshold</source>
        <translation>Порог чувствительности поиска краёв</translation>
    </message>
    <message>
        <location filename="../ui/smaadialog.ui" line="77"/>
        <source>&lt;html&gt;&lt;head/&gt;&lt;body&gt;&lt;p&gt;smaaMaxSearchSteps specifies the maximum steps performed in the horizontal/vertical pattern searches&lt;/p&gt;&lt;p&gt;Range: [0, 112]&lt;/p&gt;&lt;p&gt;4  - low&lt;/p&gt;&lt;p&gt;8  - medium&lt;/p&gt;&lt;p&gt;16 - high&lt;/p&gt;&lt;p&gt;32 - ultra&lt;/p&gt;&lt;/body&gt;&lt;/html&gt;</source>
        <translation>&lt;html&gt;&lt;head/&gt;&lt;body&gt;&lt;p&gt;Определяет максимальное количество итераций при горизонтальном/вертикальном поиске&lt;/p&gt;&lt;p&gt;Диапазон: [0, 112]&lt;/p&gt;&lt;p&gt;4 - низкое качество&lt;/p&gt;&lt;p&gt;8 - среднее качество&lt;/p&gt;&lt;p&gt;16 - высокое качество&lt;/p&gt;&lt;p&gt;32 - ультра качество&lt;/p&gt;&lt;/body&gt;&lt;/html&gt;</translation>
    </message>
    <message>
        <location filename="../ui/smaadialog.ui" line="80"/>
        <source>MaxSearchSteps</source>
        <translation>Максимальное количество итераций поиска</translation>
    </message>
    <message>
        <location filename="../ui/smaadialog.ui" line="102"/>
        <source>&lt;html&gt;&lt;head/&gt;&lt;body&gt;&lt;p&gt;smaaMaxSearchStepsDiag specifies the maximum steps performed in the diagonal pattern searches&lt;/p&gt;&lt;p&gt;Range: [0, 20]&lt;/p&gt;&lt;p&gt;0  - low, medium&lt;/p&gt;&lt;p&gt;8  - high&lt;/p&gt;&lt;p&gt;16 - ultra&lt;/p&gt;&lt;/body&gt;&lt;/html&gt;</source>
        <translation>&lt;html&gt;&lt;head/&gt;&lt;body&gt;&lt;p&gt;Определяет максимальное количество итераций при диагональном поиске&lt;/p&gt;&lt;p&gt;Диапазон: [0, 20]&lt;/p&gt;&lt;p&gt;0 - среднее/низкое качество&lt;/p&gt;&lt;p&gt;8 - высокое качество&lt;/p&gt;&lt;p&gt;16 - ультра качество&lt;/p&gt;&lt;/body&gt;&lt;/html&gt;</translation>
    </message>
    <message>
        <location filename="../ui/smaadialog.ui" line="105"/>
        <source>MaxSearchStepsDiag</source>
        <translation>Максимальное количество итераций поиска(по диагонали)</translation>
    </message>
    <message>
        <location filename="../ui/smaadialog.ui" line="127"/>
        <source>&lt;html&gt;&lt;head/&gt;&lt;body&gt;&lt;p&gt;smaaCornerRounding specifies how much sharp corners will be rounded&lt;/p&gt;&lt;p&gt;Range: [0, 100]&lt;/p&gt;&lt;p&gt;25 is a reasonable value&lt;/p&gt;&lt;/body&gt;&lt;/html&gt;</source>
        <translation>&lt;html&gt;&lt;head/&gt;&lt;body&gt;&lt;p&gt;Определяет сколько острых углов будет скруглено&lt;/p&gt;&lt;p&gt;Диапазон: [0, 100]&lt;/p&gt;&lt;p&gt;25 нормальное значение&lt;/p&gt;&lt;/body&gt;&lt;/html&gt;</translation>
    </message>
    <message>
        <location filename="../ui/smaadialog.ui" line="130"/>
        <source>CornerRounding</source>
        <translation>Скругление углов</translation>
    </message>
</context>
<context>
    <name>SmaaEffect</name>
    <message>
        <location filename="../src/effect.cpp" line="63"/>
        <source>Enhanced Subpixel Morphological Antialiasing</source>
        <translation>Улучшенное субпиксельное морфологическое сглаживание(smaa - Enhanced Subpixel Morphological Antialiasing)</translation>
    </message>
</context>
</TS>
