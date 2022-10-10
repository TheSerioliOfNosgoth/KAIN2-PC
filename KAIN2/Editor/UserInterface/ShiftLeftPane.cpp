#include "ShiftLeftPane.h"

Shift::LeftPane::LeftPane(QWidget* parent)
{
    m_zoneSliceManagerWidget = new QDockWidget(QObject::tr("ZoneSliceManager"), parent);

    m_groupBox = new QGroupBox;
    m_zoneSliceManagerWidget->setWidget(m_groupBox);
    m_groupBox->setGeometry(0, 23, 278, 700);
    m_groupBox->setTitle("Debug");
    m_zoneSliceManagerWidget->setObjectName("zoneslicemanager");
    m_zoneSliceManagerWidget->setAllowedAreas(Qt::LeftDockWidgetArea);
    m_zoneSliceManagerWidget->setFixedWidth(278);

    m_placementBrowserWidget = new QDockWidget(QObject::tr("PlacementBrowser"), parent);
    m_placementBrowserWidget->setObjectName("placementbrowser");
    m_placementBrowserWidget->setAllowedAreas(Qt::LeftDockWidgetArea);
    m_placementBrowserWidget->setFixedWidth(278);

    m_labelObjects = new QLabel;
    m_labelObjects->setText("Objects");
    m_labelMeshes = new QLabel;
    m_labelMeshes->setText("Meshes");
    m_labelOther = new QLabel;
    m_labelMeshes->setText("Other");
    m_labelUnits = new QLabel;
    m_labelMeshes->setText("Units");
    m_labelInUse = new QLabel;
    m_labelMeshes->setText("In Use");
    m_labelFav = new QLabel;
    m_labelMeshes->setText("*");

    m_placementBrowserTabWidget = new QTabWidget(m_placementBrowserWidget);
    m_placementBrowserTabWidget->setObjectName(QObject::tr("placementbrowsertab"));
    m_placementBrowserTabWidget->addTab(m_labelObjects, QObject::tr("Objects"));
    m_placementBrowserTabWidget->addTab(m_labelMeshes, QObject::tr("Meshes"));
    m_placementBrowserTabWidget->addTab(m_labelOther, QObject::tr("Other"));
    m_placementBrowserTabWidget->addTab(m_labelUnits, QObject::tr("Units"));
    m_placementBrowserTabWidget->addTab(m_labelInUse, QObject::tr("In Use"));
    m_placementBrowserTabWidget->addTab(m_labelFav, QObject::tr("*"));
    m_placementBrowserWidget->setWidget(m_placementBrowserTabWidget);
}

Shift::LeftPane::~LeftPane()
{
    if (m_labelObjects != nullptr)
    {
        delete m_labelObjects;
    }

    if (m_labelMeshes != nullptr)
    {
        delete m_labelMeshes;
    }

    if (m_labelOther != nullptr)
    {
        delete m_labelOther;
    }

    if (m_labelUnits != nullptr)
    {
        delete m_labelUnits;
    }

    if (m_labelInUse != nullptr)
    {
        delete m_labelInUse;
    }

    if (m_labelFav != nullptr)
    {
        delete m_labelFav;
    }

    if (m_groupBox != nullptr)
    {
        delete m_groupBox;
    }

    if (m_zoneSliceManagerWidget != nullptr)
    {
        delete m_zoneSliceManagerWidget;
    }

    if (m_placementBrowserWidget != nullptr)
    {
        delete m_placementBrowserWidget;
    }
}

QDockWidget* Shift::LeftPane::getZoneSliceManagerWidget()
{
    return m_zoneSliceManagerWidget;
}

QDockWidget* Shift::LeftPane::getPlacementBrowserWidget()
{
    return m_placementBrowserWidget;
}