# ~~~
# Summary:      Local, non-generic plugin setup
# Copyright (c) 2020-2021 Mike Rossiter
# License:      GPLv3+
# ~~~

# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 3 of the License, or
# (at your option) any later version.


# -------- Options ----------

set(OCPN_TEST_REPO
    "quinton/weather_routing_pi-alpha"
    CACHE STRING "Default repository for untagged builds"
)
set(OCPN_BETA_REPO
    "quinton/weather_routing_pi-beta"
    CACHE STRING
    "Default repository for tagged builds matching 'beta'"
)
set(OCPN_RELEASE_REPO
    "quinton/weather_routing_pi-prod"
    CACHE STRING
    "Default repository for tagged builds not matching 'beta'"
)

#
#
# -------  Plugin setup --------
#
set(PKG_NAME weather_routing_pi)
set(PKG_VERSION  1.15.45.8)
set(PKG_PRERELEASE "beta")  # Empty, or a tag like 'beta'

set(DISPLAY_NAME WeatherRouting)    # Dialogs, installer artifacts, ...
set(PLUGIN_API_NAME WeatherRouting) # As of GetCommonName() in plugin API
set(PKG_SUMMARY "Compute optimal routes based on weather and constraints.")
set(PKG_DESCRIPTION [=[
Features include: optimal routing subject to various constraints based
on weather data, automatic boat polar computation.
]=])

set(PKG_AUTHOR "Sean D'Epaigner")
set(PKG_IS_OPEN_SOURCE "yes")
set(PKG_HOMEPAGE  https://github.com/quinton-hoole/weather_routing_pi.git)
set(PKG_INFO_URL  "https://opencpn.org/OpenCPN/plugins/weatherroute.html")

set(SRC
  src/AboutDialog.cpp
  src/Boat.cpp
  src/BoatDialog.cpp
  src/ConfigurationBatchDialog.cpp
  src/ConfigurationDialog.cpp
  src/ConstraintChecker.cpp
  src/cutil.cpp
  src/EditPolarDialog.cpp
  src/FilterRoutesDialog.cpp
  src/georef.cpp
  src/GribRecord.cpp
  src/icons.cpp
  src/IsoRoute.cpp
  src/LineBufferOverlay.cpp
  src/navobj_util.cpp
  src/PlotDialog.cpp
  src/Polar.cpp
  src/PolygonRegion.cpp
  src/Position.cpp
  src/ReportDialog.cpp
  src/RouteMap.cpp
  src/RouteMapOverlay.cpp
  src/RoutePoint.cpp
  src/RouteSimplifier.cpp
  src/RoutingTablePanel.cpp
  src/SettingsDialog.cpp
  src/StatisticsDialog.cpp
  src/SunCalculator.cpp
  src/Utilities.cpp
  src/WeatherDataProvider.cpp
  src/WeatherRouting.cpp
  src/weather_routing_pi.cpp
  src/WeatherRoutingUI.cpp
  src/zuFile.cpp
  include/AboutDialog.h
  include/BoatDialog.h
  include/Boat.h
  include/ConfigurationBatchDialog.h
  include/ConfigurationDialog.h
  include/ConstraintChecker.h
  include/cutil.h
  include/EditPolarDialog.h
  include/FilterRoutesDialog.h
  include/georef.h
  include/GribRecord.h
  include/icons.h
  include/IsoRoute.h
  include/LineBufferOverlay.h
  include/navobj_util.h
  include/PlotDialog.h
  include/Polar.h
  include/PolygonRegion.h
  include/Position.h
  include/ReportDialog.h
  include/RouteMap.h
  include/RouteMapOverlay.h
  include/RoutePoint.h
  include/RouteSimplifier.h
  include/RoutingTablePanel.h
  include/SettingsDialog.h
  include/StatisticsDialog.h
  include/SunCalculator.h
  include/Utilities.h
  include/WeatherDataProvider.h
  include/WeatherRouting.h
  include/weather_routing_pi.h
  include/WeatherRoutingUI.h
  include/zuFile.h
)

set(PKG_API_LIB api-18)  #  A dir in opencpn-libs/ e. g., api-17 or api-16

cmake_policy(SET CMP0043 NEW)
cmake_policy(SET CMP0048 NEW)
cmake_policy(SET CMP0068 NEW)
if (POLICY CMP0076)
  cmake_policy(SET CMP0076 NEW)
endif ()
if (POLICY CMP0077)
  cmake_policy(SET CMP0077 NEW)
endif ()
if (POLICY CMP0079)
  cmake_policy(SET CMP0079 NEW)
endif ()
if (POLICY CMP0175)
  cmake_policy(SET CMP0175 NEW)
endif ()
if (POLICY CMP0177)
  cmake_policy(SET CMP0177 NEW)
endif ()


# Option to enable/disable testing
option(OCPN_BUILD_TEST "Build plugin tests" OFF)

macro(late_init)
  target_include_directories(
    ${PACKAGE_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/include
  )
endmacro ()

macro(add_plugin_libraries)
  set(CACHE USE_SYSTEM_TINYXML TYPE BOOL VALUE ON)
  add_subdirectory(opencpn-libs/tinyxml)
  target_link_libraries(${PACKAGE_NAME} ocpn::tinyxml)

  add_subdirectory(opencpn-libs/odapi)
  target_link_libraries(${PACKAGE_NAME} ocpn::odapi)

  add_subdirectory(opencpn-libs/jsonlib)
  target_link_libraries(${PACKAGE_NAME} ocpn::jsonlib)

  add_subdirectory(opencpn-libs/plugin_dc)
  target_link_libraries(${PACKAGE_NAME} ocpn::plugin-dc)

  add_subdirectory(opencpn-libs/pugixml)
  target_link_libraries(${PACKAGE_NAME} ocpn::pugixml)

  # @todo Why would this not be required on UNIX?
  # @todo@ On macos the build fails without it, and macos is UNIX
  # @todo See https://cmake.org/cmake/help/latest/variable/UNIX.html

  add_subdirectory(opencpn-libs/bzip2)
  target_link_libraries(${PACKAGE_NAME} ocpn::bzip2)

  add_subdirectory(opencpn-libs/libtess2)
  target_link_libraries(${PACKAGE_NAME} ocpn::libtess2)

  add_subdirectory(opencpn-libs/zlib)
  target_link_libraries(${PACKAGE_NAME} ocpn::zlib)

endmacro ()
