include(ECMPoQmTools)

add_library(KF5WidgetsAddons)
add_library(KF5::WidgetsAddons ALIAS KF5WidgetsAddons)

ecm_create_qm_loader(KF5WidgetsAddons kwidgetsaddons5_qt)

target_sources(KF5WidgetsAddons PRIVATE
  kacceleratormanager.cpp
  kanimatedbutton.cpp
  kbusyindicatorwidget.cpp
  kcharselect.cpp
  kcharselectdata.cpp
  kcollapsiblegroupbox.cpp
  kcolorbutton.cpp
  kcolumnresizer.cpp
  kdatecombobox.cpp
  kdatepicker.cpp
  kdatetable.cpp
  kdatetimeedit.cpp
  kfontaction.cpp
  knewpasswordwidget.cpp
  kfontsizeaction.cpp
  kpopupframe.cpp
  kselectaction.cpp
  ktimecombobox.cpp
  kdragwidgetdecorator.cpp
  kdualaction.cpp
  kfontchooser.cpp
  kfontchooserdialog.cpp
  kguiitem.cpp
  kled.cpp
  kmessagebox.cpp
  kmessagebox_p.cpp
  kmultitabbar.cpp
  kstandardguiitem.cpp
  kurllabel.cpp # Not good enough quality. Needs to use QUrl instead of QString and should not inherit QLabel, but hold it as a member instead.
  kcapacitybar.cpp
  kfontrequester.cpp
  kpassworddialog.cpp
  kruler.cpp
  krecentfilesmenu.cpp
  kselector.cpp
  kxyselector.cpp
  kseparator.cpp
  ksqueezedtextlabel.cpp
  ktitlewidget.cpp
  ktoggleaction.cpp
  ktogglefullscreenaction.cpp
  kviewstateserializer.cpp
  kviewstatemaintainerbase.cpp
  keditlistwidget.cpp
  kcursor.cpp
  kratingwidget.cpp
  kratingpainter.cpp
  kactionselector.cpp
  kcolorcombo.cpp
  ktoolbarspaceraction.cpp
  kpixmapregionselectordialog.cpp
  kpixmapregionselectorwidget.cpp
  kactionmenu.cpp
  ktoolbarlabelaction.cpp
  ktoolbarpopupaction.cpp
  kpagedialog.cpp
  kpagemodel.cpp
  kpageview.cpp
  kpageview_p.cpp
  kpagewidget.cpp
  kpagewidgetmodel.cpp
  kassistantdialog.cpp
  kmessagewidget.cpp
  kmessagedialog.cpp
  knewpassworddialog.cpp
  lineediturldropeventfilter.cpp
  kpasswordlineedit.cpp
  kpixmapsequence.cpp
  kpixmapsequenceoverlaypainter.cpp
  kpixmapsequencewidget.cpp
  kmimetypechooser.cpp
  kmimetypeeditor.cpp
  common_helpers.cpp
  ksplittercollapserbutton.cpp
  kstyleextensions.cpp
  ktooltipwidget.cpp
  ktwofingerswipe.cpp
  ktwofingertap.cpp

  icons.qrc
)

set(kwidgetsaddons_UI_SRCS)
qt_wrap_ui(kwidgetsaddons_UI_SRCS
   kdatetimeedit.ui
   knewpassworddialog.ui
   knewpasswordwidget.ui
   kpassworddialog.ui
   kfontchooserwidget.ui
)
target_sources(KF5WidgetsAddons PRIVATE ${kwidgetsaddons_UI_SRCS})

ecm_qt_declare_logging_category(KF5WidgetsAddons
    HEADER loggingcategory.h
    IDENTIFIER KWidgetsAddonsLog
    CATEGORY_NAME kf.kwidgetsaddons
    DEFAULT_SEVERITY Warning
    DESCRIPTION "KWidgetsAddons"
    EXPORT KWIDGETSADDONS
)

ecm_generate_export_header(KF5WidgetsAddons
    BASE_NAME KWidgetsAddons
    GROUP_BASE_NAME KF
    VERSION ${KF_VERSION}
    DEPRECATED_BASE_VERSION 0
    DEPRECATION_VERSIONS 5.0 5.13 5.63 5.65 5.72 5.77 5.78 5.85 5.86
    EXCLUDE_DEPRECATED_BEFORE_AND_AT ${EXCLUDE_DEPRECATED_BEFORE_AND_AT}
)

target_link_libraries(KF5WidgetsAddons PUBLIC Qt5::Widgets)

target_include_directories(KF5WidgetsAddons INTERFACE "$<INSTALL_INTERFACE:${KDE_INSTALL_INCLUDEDIR_KF5}/KWidgetsAddons>")

set_target_properties(KF5WidgetsAddons PROPERTIES VERSION   ${KWIDGETSADDONS_VERSION}
                                                  SOVERSION ${KWIDGETSADDONS_SOVERSION}
                                                  EXPORT_NAME WidgetsAddons
)

ecm_generate_headers(KWidgetsAddons_HEADERS
  HEADER_NAMES
  KAcceleratorManager
  KAnimatedButton
  KBusyIndicatorWidget
  KCharSelect
  KCollapsibleGroupBox
  KColorButton
  KColumnResizer
  KDateComboBox
  KDatePicker
  KDateTimeEdit
  KDragWidgetDecorator
  KDualAction
  KFontAction
  KFontChooser
  KFontChooserDialog
  KFontSizeAction
  KGuiItem
  KLed
  KMessageBox
  KMessageBoxDontAskAgainInterface
  KMultiTabBar,KMultiTabBarButton,KMultiTabBarTab
  KNewPasswordWidget
  KPopupFrame
  KSelectAction
  KStandardGuiItem
  KTimeComboBox
  KUrlLabel
  KCapacityBar
  KFontRequester
  KPasswordDialog
  KRuler
  KRecentFilesMenu
  KSelector,KGradientSelector
  KTitleWidget
  KXYSelector
  KSeparator
  KSqueezedTextLabel
  KToggleAction
  KToggleFullScreenAction
  KViewStateSerializer
  KViewStateMaintainerBase
  KEditListWidget
  KCursor
  KRatingPainter
  KRatingWidget
  KActionSelector
  KColorCombo
  KActionMenu
  KToolBarLabelAction
  KToolBarPopupAction
  KToolBarSpacerAction
  KPageDialog
  KPageModel
  KPageView
  KPageWidget
  KPageWidgetModel,KPageWidgetItem
  KAssistantDialog
  KMessageWidget
  KMessageDialog
  KNewPasswordDialog
  LineEditUrlDropEventFilter
  KPasswordLineEdit
  KPixmapSequence
  KPixmapSequenceOverlayPainter
  KPixmapSequenceWidget
  KPixmapRegionSelectorDialog
  KPixmapRegionSelectorWidget
  KMimeTypeChooser,KMimeTypeChooserDialog
  KMimeTypeEditor
  KMessageBoxNotifyInterface
  KSplitterCollapserButton
  KStyleExtensions
  KToolTipWidget
  KTwoFingerTap
  KTwoFingerSwipe
  REQUIRED_HEADERS KWidgetsAddons_HEADERS
)

find_package(PythonModuleGeneration)

if (PythonModuleGeneration_FOUND)
  ecm_generate_python_binding(
    TARGET KF5::WidgetsAddons
    PYTHONNAMESPACE PyKF5
    MODULENAME KWidgetsAddons
    RULES_FILE "${CMAKE_SOURCE_DIR}/cmake/rules_PyKF5.py"
    SIP_DEPENDS
      QtWidgets/QtWidgetsmod.sip
    HEADERS
      kacceleratormanager.h
      kanimatedbutton.h
      kbusyindicatorwidget.h
      kcharselect.h
      kcollapsiblegroupbox.h
      kcolorbutton.h
      kcolumnresizer.h
      kdatecombobox.h
      kdatepicker.h
      kdatetimeedit.h
      kdragwidgetdecorator.h
      kdualaction.h
      kfontaction.h
      kfontchooser.h
      kfontchooserdialog.h
      kfontsizeaction.h
      kguiitem.h
      kled.h
      kmessagebox.h
      kmessageboxdontaskagaininterface.h
      kmultitabbar.h
      knewpasswordwidget.h
      kpopupframe.h
      kselectaction.h
      kstandardguiitem.h
      ktimecombobox.h
      kurllabel.h
      kcapacitybar.h
      kfontrequester.h
      kpassworddialog.h
      kruler.h
      kselector.h
      ktitlewidget.h
      kxyselector.h
      kseparator.h
      ksqueezedtextlabel.h
      ktoggleaction.h
      ktogglefullscreenaction.h
      kviewstateserializer.h
      kviewstatemaintainerbase.h
      keditlistwidget.h
      kcursor.h
      kratingpainter.h
      kratingwidget.h
      kactionselector.h
      kcolorcombo.h
      kactionmenu.h
      ktoolbarlabelaction.h
      ktoolbarpopupaction.h
      ktoolbarspaceraction.h
      kpagedialog.h
      kpagemodel.h
      kpageview.h
      kpagewidget.h
      kpagewidgetmodel.h
      kassistantdialog.h
      kmessagewidget.h
      kmessagedialog.h
      knewpassworddialog.h
      lineediturldropeventfilter.h
      kpasswordlineedit.h
      kpixmapsequence.h
      kpixmapsequenceoverlaypainter.h
      kpixmapsequencewidget.h
      kpixmapregionselectordialog.h
      kpixmapregionselectorwidget.h
      kmimetypechooser.h
      kmimetypeeditor.h
      kmessageboxnotifyinterface.h
      ksplittercollapserbutton.h
      kstyleextensions.h
      ktwofingerswipe.h
      ktwofingertap.h
  )
endif()

install(TARGETS KF5WidgetsAddons EXPORT KF5WidgetsAddonsTargets ${KF5_INSTALL_TARGETS_DEFAULT_ARGS})

install(FILES
  ${KWidgetsAddons_HEADERS}
  ${CMAKE_CURRENT_BINARY_DIR}/kwidgetsaddons_export.h
  DESTINATION ${KDE_INSTALL_INCLUDEDIR_KF5}/KWidgetsAddons COMPONENT Devel
)

install(FILES kcharselect-data  DESTINATION  ${KDE_INSTALL_DATADIR_KF5}/kcharselect)

if (BUILD_QCH)
    ecm_add_qch(
        KF5WidgetsAddons_QCH
        NAME KWidgetsAddons
        BASE_NAME KF5WidgetsAddons
        VERSION ${KF_VERSION}
        ORG_DOMAIN org.kde
        SOURCES # using only public headers, to cover only public API
            ${KWidgetsAddons_HEADERS}
        MD_MAINPAGE "${CMAKE_SOURCE_DIR}/README.md"
        IMAGE_DIRS "${CMAKE_SOURCE_DIR}/docs/pics"
        LINK_QCHS
            Qt5Core_QCH
            Qt5Gui_QCH
            Qt5Widgets_QCH
        INCLUDE_DIRS
            ${CMAKE_CURRENT_BINARY_DIR}
        BLANK_MACROS
            KWIDGETSADDONS_EXPORT
            KWIDGETSADDONS_DEPRECATED_EXPORT
            KWIDGETSADDONS_DEPRECATED
            "KWIDGETSADDONS_DEPRECATED_VERSION(x, y, t)"
        TAGFILE_INSTALL_DESTINATION ${KDE_INSTALL_QTQCHDIR}
        QCH_INSTALL_DESTINATION ${KDE_INSTALL_QTQCHDIR}
        COMPONENT Devel
    )
endif()

if(BUILD_DESIGNERPLUGIN)
    add_subdirectory(designer)
endif()

ecm_qt_install_logging_categories(
    EXPORT KWIDGETSADDONS
    FILE kwidgetsaddons.categories
    DESTINATION ${KDE_INSTALL_LOGGINGCATEGORIESDIR}
)

include(ECMGeneratePriFile)
ecm_generate_pri_file(BASE_NAME KWidgetsAddons LIB_NAME KF5WidgetsAddons DEPS "widgets" FILENAME_VAR PRI_FILENAME INCLUDE_INSTALL_DIR ${KDE_INSTALL_INCLUDEDIR_KF5}/KWidgetsAddons)
install(FILES ${PRI_FILENAME} DESTINATION ${ECM_MKSPECS_INSTALL_DIR})