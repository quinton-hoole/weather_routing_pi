/***************************************************************************
 *
 * Project:  OpenCPN
 *
 ***************************************************************************
 *   Copyright (C) 2013 by David S. Register                               *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   51 Franklin Street, Fifth Floor, Boston, MA 02110-1301,  USA.         *
 **************************************************************************/

#ifndef _NAVOBJUTIL_H__
#define _NAVOBJUTIL_H__

#include "pugixml.hpp"
#include <wx/string.h>
#include <wx/datetime.h>
#include <wx/math.h>
#include <vector>

/*
#include <wx/bitmap.h>
#include <wx/clrpicker.h>
#include <wx/font.h>
#include <wx/gauge.h>
#include <wx/gdicmn.h>

#include "bbox.h"
#include "hyperlink.h"
#include "chcanv.h"

#define MAX_INT_VAL 2147483647  // max possible integer value before 'rollover'

// minimal allowed ScaMin setting. prevents always hiding
#define SCAMIN_MIN  800

#define ETA_FORMAT_STR "%x %H:%M"
//"%d/%m/%Y %H:%M" //"%Y-%m-%d %H:%M"
*/

// RFC4122 version 4 compliant random UUIDs generator.
wxString GetUUID(void);
int GetRandomNumber(int range_min, int range_max);

class SimpleRoutePoint {
public:
  SimpleRoutePoint(double lat, double lon, const wxString& icon_ident,
                   const wxString& name, const wxString& sGUID = wxEmptyString);

  SimpleRoutePoint(SimpleRoutePoint* orig);
  SimpleRoutePoint();
  virtual ~SimpleRoutePoint(void) {};

  wxDateTime m_CreateTime;

#if 0
  void ReLoadIcon() { m_IconIsDirty = true; }

  void SetPosition(double lat, double lon);
  double GetLatitude() { return m_lat; };
  double GetLongitude() { return m_lon; };
  LLBBox &GetBBox() { return m_wpBBox; }

  bool IsSame(RoutePoint *pOtherRP);  // toh, 2009.02.11
  bool IsVisible() { return m_bIsVisible; }
  bool IsListed() { return m_bIsListed; }
  bool IsNameShown() { return m_bShowName; }

  bool IsShared() { return m_bsharedMark; }
  void SetShared(bool bshared) { m_bsharedMark = bshared; }

  bool IsSharedInVisibleRoute(void);

  bool IsVisibleSelectable(double scale_val, bool boverrideViz = false);
  void SetVisible(bool viz = true) { m_bIsVisible = viz; }
  void SetListed(bool viz = true) { m_bIsListed = viz; }
  void SetNameShown(bool viz = true) { m_bShowName = viz; }
  bool GetNameShown() { return m_bShowName; }
  virtual wxString GetName(void) { return m_MarkName; }
  wxString GetDescription(void) { return m_MarkDescription; }

  wxDateTime GetCreateTime(void);
  void SetCreateTime(wxDateTime dt);

  wxString GetIconName(void) { return m_IconName; }
  void SetIconName(wxString name) { m_IconName = name; }

  void *GetSelectNode(void) { return m_SelectNode; }
  void SetSelectNode(void *node) { m_SelectNode = node; }

  void *GetManagerListNode(void) { return m_ManagerNode; }
  void SetManagerListNode(void *node) { m_ManagerNode = node; }

  void SetName(const wxString &name);
  void CalculateNameExtents(void);

  void SetCourse(double course) { m_routeprop_course = course; };
  double GetCourse() { return m_routeprop_course; };
  void SetDistance(double distance) { m_routeprop_distance = distance; };
  double GetDistance() { return m_routeprop_distance; };

  void SetWaypointArrivalRadius(double dArrivalDistance) {
    m_WaypointArrivalRadius = dArrivalDistance;
  };
  void SetWaypointArrivalRadius(wxString wxArrivalDistance) {
    wxArrivalDistance.ToDouble(&m_WaypointArrivalRadius);
  };
  double GetWaypointArrivalRadius();
  bool GetShowWaypointRangeRings(void) { return m_bShowWaypointRangeRings; };
  int GetWaypointRangeRingsNumber(void);
  float GetWaypointRangeRingsStep(void);
  int GetWaypointRangeRingsStepUnits(void);
  wxColour GetWaypointRangeRingsColour(void);
  void SetShowWaypointRangeRings(bool b_showWaypointRangeRings) {
    m_bShowWaypointRangeRings = b_showWaypointRangeRings;
  };
  void SetWaypointRangeRingsNumber(int i_WaypointRangeRingsNumber) {
    m_iWaypointRangeRingsNumber = i_WaypointRangeRingsNumber;
  };
  void SetWaypointRangeRingsStep(float f_WaypointRangeRingsStep) {
    m_fWaypointRangeRingsStep = f_WaypointRangeRingsStep;
  };
  void SetWaypointRangeRingsStepUnits(int i_WaypointRangeRingsStepUnits) {
    m_iWaypointRangeRingsStepUnits = i_WaypointRangeRingsStepUnits;
  };
  void SetWaypointRangeRingsColour(wxColour wxc_WaypointRangeRingsColour) {
    m_wxcWaypointRangeRingsColour = wxc_WaypointRangeRingsColour;
  };
  void SetScaMin(wxString str);
  void SetScaMin(long val);
  long GetScaMin() { return m_ScaMin; };
  void SetScaMax(wxString str);
  void SetScaMax(long val);
  long GetScaMax() { return m_ScaMax; };
  bool GetUseSca() { return b_UseScamin; };
  void SetUseSca(bool value) { b_UseScamin = value; };
  bool IsDragHandleEnabled() { return m_bDrawDragHandle; }
  void SetPlannedSpeed(double spd);
  double GetPlannedSpeed();
  wxDateTime GetETD();
  wxDateTime GetManualETD();
  void SetETD(const wxDateTime &etd);
  bool SetETD(const wxString &ts);
  wxDateTime GetETA();
  wxString GetETE();
  void SetETE(wxLongLong secs);
#endif

  double m_lat, m_lon;
  double m_seg_vmg;
  wxDateTime etd;
  wxString m_MarkName;
  wxString m_MarkDescription;
  wxString m_GUID;

#if 0
  double m_seg_len;  // length in NMI to this point
                     // undefined for starting point
  double m_seg_vmg;
  wxDateTime m_seg_etd;
  wxDateTime m_seg_eta;
  wxLongLong m_seg_ete = 0;
  bool m_manual_etd{false};

  bool m_bPtIsSelected;
  bool m_bRPIsBeingEdited;

  bool m_bIsInRoute;
  bool m_bIsolatedMark;  // This is an isolated mark

  bool m_bIsVisible;  // true if should be drawn, false if invisible
  bool m_bIsListed;
  bool m_bIsActive;
  bool m_IconIsDirty;
  wxString m_MarkDescription;
  wxString m_GUID;

  wxString m_TideStation;

  wxFont *m_pMarkFont;
  wxColour m_FontColor;

  wxSize m_NameExtents;

  bool m_bBlink;
  bool m_bDynamicName;
  bool m_bShowName, m_bShowNameData;
  wxRect CurrentRect_in_DC;
  int m_NameLocationOffsetX;
  int m_NameLocationOffsetY;
  bool m_bIsInLayer;
  int m_LayerID;

  double m_routeprop_course;  // course from this waypoint to the next waypoint
                              // if in a route.
  double m_routeprop_distance;  // distance from this waypoint to the next
                                // waypoint if in a route.

  bool m_btemp;

  bool m_bShowWaypointRangeRings;
  int m_iWaypointRangeRingsNumber;

  float m_fWaypointRangeRingsStep;
  int m_iWaypointRangeRingsStepUnits;
  wxColour m_wxcWaypointRangeRingsColour;


  wxDateTime m_CreateTimeX;

private:

  wxString m_MarkName;
  wxBitmap *m_pbmIcon;
  wxString m_IconName;

  void *m_SelectNode;
  void *m_ManagerNode;

  float m_IconScaleFactor;
  wxBitmap m_ScaledBMP;
  bool m_bPreScaled;
  bool m_bDrawDragHandle;
  wxBitmap m_dragIcon;
  int m_drag_line_length_man, m_drag_icon_offset;
  double m_dragHandleLat, m_dragHandleLon;
  int m_draggingOffsetx, m_draggingOffsety;
  bool b_UseScamin;
  long m_ScaMin;
  long m_ScaMax;
  double m_PlannedSpeed;

  bool m_bsharedMark /*m_bKeepXRoute*/;  // This is an isolated mark which is
                                         // also part of a route. It should not
                                         // be deleted with route.
#endif
};

class SimpleRoute {
public:
  SimpleRoute() {};

  virtual ~SimpleRoute() {
    for (size_t i = 0; i < m_vec_points.size(); i++) {
      delete m_vec_points[i];
    }
  }

  bool AddPoint(SimpleRoutePoint* point) {
    m_vec_points.push_back(point);
    return true;
  }

  wxString m_GUID;
  wxString m_RouteNameString;
  wxString m_RouteDescription;
  wxString m_RouteStartString;
  wxString m_RouteEndString;
  wxDateTime m_PlannedDeparture;
  double m_PlannedSpeed;

  std::vector<SimpleRoutePoint*> m_vec_points;
};

class SimpleNavObjectXML : public pugi::xml_document {
public:
  SimpleNavObjectXML();
  virtual ~SimpleNavObjectXML();

  bool CreateNavObjGPXRoute(const SimpleRoute& Route);

  // bool CreateNavObjGPXPoints(void);
  // bool CreateNavObjGPXRoutes(void);
  // bool CreateNavObjGPXTracks(void);

  // void AddGPXRoutesList(RouteList *pRoutes);
  // void AddGPXTracksList(std::vector<Track*> *pTracks);
  // bool AddGPXPointsList(RoutePointList *pRoutePoints);
  // bool AddGPXRoute(Route *pRoute);
  // bool AddGPXTrack(Track *pTrk);
  // bool AddGPXWaypoint(RoutePoint *pWP);

  bool CreateAllGPXObjects();
  bool LoadAllGPXObjects(bool b_full_viz, int& wpt_duplicates,
                         bool b_compute_bbox = false);
  int LoadAllGPXObjectsAsLayer(int layer_id, bool b_layerviz,
                               wxCheckBoxState b_namesviz);

  bool SaveFile(const wxString filename);

  void SetRootGPXNode(void);
  bool IsOpenCPN();
};

#endif  //_NAVOBJUTIL_H__
