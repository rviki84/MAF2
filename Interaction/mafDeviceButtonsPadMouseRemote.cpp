/*=========================================================================

 Program: MAF2
 Module: mafDeviceButtonsPadMouseRemote
 Authors: Marco Petrone
 
 Copyright (c) B3C
 All rights reserved. See Copyright.txt or
 http://www.scsitaly.com/Copyright.htm for details.

 This software is distributed WITHOUT ANY WARRANTY; without even
 the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
 PURPOSE.  See the above copyright notice for more information.

=========================================================================*/


#include "mafDefines.h" 
//----------------------------------------------------------------------------
// NOTE: Every CPP file in the MAF must include "mafDefines.h" as first.
// This force to include Window,wxWidgets and VTK exactly in this order.
// Failing in doing this will result in a run-time error saying:
// "Failure#0: The value of ESP was not properly saved across a function call"
//----------------------------------------------------------------------------

#include "mafDeviceButtonsPadMouseRemote.h"
#include "mafEventBase.h"
#include "mafView.h"
#include "mafSceneGraph.h"
#include "mafRWIBase.h"

#include "mafEventInteraction.h"
#include "mmuIdFactory.h"

#include "vtkRenderWindow.h"
#include "vtkRenderWindowInteractor.h"

//------------------------------------------------------------------------------
mafCxxTypeMacro(mafDeviceButtonsPadMouseRemote)
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
mafDeviceButtonsPadMouseRemote::mafDeviceButtonsPadMouseRemote()
//------------------------------------------------------------------------------
{
}
//------------------------------------------------------------------------------
mafDeviceButtonsPadMouseRemote::~mafDeviceButtonsPadMouseRemote()
//------------------------------------------------------------------------------
{
}
//------------------------------------------------------------------------------
void mafDeviceButtonsPadMouseRemote::OnEvent(mafEventBase *event)
//------------------------------------------------------------------------------
{
  assert(event);

  mafID id = event->GetId();
  mafEventInteraction *e = mafEventInteraction::SafeDownCast(event);

  m_FromRemote = true;
  double pos[2];
  if (e)
  {
    e->Get2DPosition(pos);
  }

  if (id == mafDeviceButtonsPadMouse::GetMouse2DMoveId())
  {
    NormalizedDisplayToDisplay(pos);
    SetLastPosition(pos[0],pos[1],e->GetModifiers());
  }
  else if (id == GetButtonDownId() || id == GetMouseDClickId())
  {
    // store the Selected RWI is needed for compounded view
    m_ButtonPressed = true;
    if (m_SelectedView)
    {
      m_SelectedRWI = m_SelectedView->GetRWI();
    }
    NormalizedDisplayToDisplay(pos);
    e->SetSender(this);
    m_LastPosition[0] = pos[0];
    m_LastPosition[1] = pos[1];
    e->Set2DPosition(m_LastPosition);
    InvokeEvent(e,MCH_INPUT);
  }
  else if (id == GetButtonUpId())
  {
    NormalizedDisplayToDisplay(pos);
    m_LastPosition[0] = pos[0];
    m_LastPosition[1] = pos[1];
    e->Set2DPosition(m_LastPosition);
    e->SetSender(this);
    InvokeEvent(e,MCH_INPUT);
  }
  else if (id == VIEW_SELECT)
  {
    mafEvent *ev = mafEvent::SafeDownCast(event);
    if (ev)
    {
      m_SelectedView = ev->GetView();
    }
  }
  else if (id == VIEW_DELETE)
  {
    m_SelectedView = NULL;
    m_SelectedRWI  = NULL;
  }
  else if (id == mafDeviceButtonsPadMouse::GetMouseCharEventId())
  {
    mafEvent *ev = mafEvent::SafeDownCast(event);
    if (ev)
    {
      unsigned char key = (unsigned char)ev->GetArg();
      mafEventInteraction ei(this, mafDeviceButtonsPadMouse::GetMouseCharEventId());
      ei.SetKey(key);
      InvokeEvent(ei,MCH_INPUT);
    }
  }

  m_FromRemote = false;
}
