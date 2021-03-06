/*=========================================================================

 Program: MAF2
 Module: mafVMEOutputPointSet
 Authors: Marco Petrone
 
 Copyright (c) B3C
 All rights reserved. See Copyright.txt or
 http://www.scsitaly.com/Copyright.htm for details.

 This software is distributed WITHOUT ANY WARRANTY; without even
 the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
 PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#ifndef __mafVMEOutputPointSet_h
#define __mafVMEOutputPointSet_h
//----------------------------------------------------------------------------
// Include:
//----------------------------------------------------------------------------
#include "mafVMEOutputVTK.h"
//----------------------------------------------------------------------------
// forward declarations :
//----------------------------------------------------------------------------
class vtkPolyData;
class mmaMaterial;

/** NULL output for VME node with a VTK image output data.
  mafVMEOutputPointSet is the output produced by a node generating an output
  with a VTK dataset.
*/
class MAF_EXPORT mafVMEOutputPointSet : public mafVMEOutputVTK
{
public:
  mafVMEOutputPointSet();
  virtual ~mafVMEOutputPointSet();

  mafTypeMacro(mafVMEOutputPointSet,mafVMEOutputVTK);

  /**
    Return a VTK dataset corresponding to the current time. This is
    the output of the DataPipe currently attached to the VME.
    Usually the output is a  "smart copy" of one of the dataset in 
    the DataArray. In some cases it can be NULL, e.g. in case the number
    of stored Items is 0. Also special VME could not support VTK dataset output.
    An event is rised when the output data changes to allow attached classes to 
    update their input.*/
  virtual vtkPolyData *GetPointSetData();

  /** return material attribute of this surface if present */
  mmaMaterial *GetMaterial();

  /** set the material of the surface */ 
  void SetMaterial(mmaMaterial *material);

  /** Update all the output data structures (data, bounds, matrix and abs matrix).*/
  virtual void Update();

protected:
  mafGUI *CreateGui();
  mafString     m_NumPoints;
  mmaMaterial  *m_Material; ///< material object used to store shading propertied to render the pointset

private:
  mafVMEOutputPointSet(const mafVMEOutputPointSet&); // Not implemented
  void operator=(const mafVMEOutputPointSet&); // Not implemented
};

#endif

