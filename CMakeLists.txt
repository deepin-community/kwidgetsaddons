cmake_minimum_required(VERSION 3.16)

set(KF_VERSION "5.103.0") # handled by release scripts
project(KWidgetsAddons VERSION ${KF_VERSION})

include(FeatureSummary)
find_package(ECM 5.103.0  NO_MODULE)
set_package_properties(ECM PROPERTIES TYPE REQUIRED DESCRIPTION "Extra CMake Modules." URL "https://commits.kde.org/extra-cmake-modules")
feature_summary(WHAT REQUIRED_PACKAGES_NOT_FOUND FATAL_ON_MISSING_REQUIRED_PACKAGES)


set(CMAKE_MODULE_PATH ${ECM_MODULE_PATH})

include(KDEInstallDirs)
include(KDEFrameworkCompilerSettings NO_POLICY_SCOPE)
include(KDECMakeSettings)

include(KDEGitCommitHooks)
include(ECMDeprecationSettings)

set(REQUIRED_QT_VERSION 5.15.2)
find_package(Qt${QT_MAJOR_VERSION} ${REQUIRED_QT_VERSION} CONFIG REQUIRED Widgets)


include(ECMGenerateExportHeader)
include(CMakePackageConfigHelpers)
include(ECMSetupVersion)
include(ECMGenerateHeaders)
include(ECMAddQch)
include(ECMPoQmTools)
include(ECMQtDeclareLoggingCategory)
include(CMakeDependentOption)

ecm_setup_version(PROJECT VARIABLE_PREFIX KWIDGETSADDONS
                        VERSION_HEADER "${CMAKE_CURRENT_BINARY_DIR}/kwidgetsaddons_version.h"
                        PACKAGE_VERSION_FILE "${CMAKE_CURRENT_BINARY_DIR}/KF5WidgetsAddonsConfigVersion.cmake"
                        SOVERSION 5)

set(EXCLUDE_DEPRECATED_BEFORE_AND_AT 0 CACHE STRING "Control the range of deprecated API excluded from the build [default=0].")

option(BUILD_QCH "Build API documentation in QCH format (for e.g. Qt Assistant, Qt Creator & KDevelop)" OFF)
add_feature_info(QCH ${BUILD_QCH} "API documentation in QCH format (for e.g. Qt Assistant, Qt Creator & KDevelop)")

cmake_dependent_option(BUILD_DESIGNERPLUGIN "Build plugin for Qt Designer" ON "NOT CMAKE_CROSSCOMPILING" OFF)
add_feature_info(DESIGNERPLUGIN ${BUILD_DESIGNERPLUGIN} "Build plugin for Qt Designer")


ecm_install_po_files_as_qm(poqm)

configure_file(test-config.h.in ${CMAKE_CURRENT_BINARY_DIR}/test-config.h)

ecm_set_disabled_deprecation_versions(
    QT 5.14 # QLabel::pixmap(), cannot be ported, but in a deprecated method
)

add_subdirectory(src)
if (BUILD_TESTING)
    add_subdirectory(autotests)
    add_subdirectory(tests)
    add_subdirectory(examples)
endif()

# create a Config.cmake and a ConfigVersion.cmake file and install them
set(CMAKECONFIG_INSTALL_DIR "${KDE_INSTALL_CMAKEPACKAGEDIR}/KF5WidgetsAddons")

if (BUILD_QCH)
    ecm_install_qch_export(
        TARGETS KF5WidgetsAddons_QCH
        FILE KF5WidgetsAddonsQchTargets.cmake
        DESTINATION "${CMAKECONFIG_INSTALL_DIR}"
        COMPONENT Devel
    )
    set(PACKAGE_INCLUDE_QCHTARGETS "include(\"\${CMAKE_CURRENT_LIST_DIR}/KF5WidgetsAddonsQchTargets.cmake\")")
endif()

configure_package_config_file("${CMAKE_CURRENT_SOURCE_DIR}/KF5WidgetsAddonsConfig.cmake.in"
                              "${CMAKE_CURRENT_BINARY_DIR}/KF5WidgetsAddonsConfig.cmake"
                              INSTALL_DESTINATION  ${CMAKECONFIG_INSTALL_DIR}
                              )

install(FILES  "${CMAKE_CURRENT_BINARY_DIR}/KF5WidgetsAddonsConfig.cmake"
               "${CMAKE_CURRENT_BINARY_DIR}/KF5WidgetsAddonsConfigVersion.cmake"
        DESTINATION "${CMAKECONFIG_INSTALL_DIR}"
        COMPONENT Devel )

install(EXPORT KF5WidgetsAddonsTargets DESTINATION "${CMAKECONFIG_INSTALL_DIR}" FILE KF5WidgetsAddonsTargets.cmake NAMESPACE KF5:: )

install(FILES
  ${CMAKE_CURRENT_BINARY_DIR}/kwidgetsaddons_version.h
  DESTINATION ${KDE_INSTALL_INCLUDEDIR_KF}/KWidgetsAddons COMPONENT Devel
)

feature_summary(WHAT ALL   FATAL_ON_MISSING_REQUIRED_PACKAGES)

kde_configure_git_pre_commit_hook(CHECKS CLANG_FORMAT)
