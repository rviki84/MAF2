/*=========================================================================
Program:   Multimod Application Framework
Module:    $RCSfile: mafOpFilterVolumeTest.h,v $
Language:  C++
Date:      $Date: 2010-01-26 11:43:43 $
Version:   $Revision: 1.1.2.1 $
Authors:   Matteo Giacomoni
==========================================================================
Copyright (c) 2010 
CINECA - Interuniversity Consortium (www.cineca.it)
=========================================================================*/

#ifndef __CPP_UNIT_mafOpFilterVolumeTest_H__
#define __CPP_UNIT_mafOpFilterVolumeTest_H__

#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/BriefTestProgressListener.h>
#include <cppunit/CompilerOutputter.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/TestResult.h>
#include <cppunit/TestResultCollector.h>
#include <cppunit/TestRunner.h>

class vtkImageData;
class vtkRectilinearGrid;

/** Test for mafMatrix; Use this suite to trace memory problems */
class mafOpFilterVolumeTest : public CPPUNIT_NS::TestFixture
{
public: 
  // CPPUNIT fixture: executed before each test
  void setUp();

  // CPPUNIT fixture: executed after each test
  void tearDown();

  // CPPUNIT test suite
  CPPUNIT_TEST_SUITE( mafOpFilterVolumeTest );
  CPPUNIT_TEST( TestFixture ); // just to test that the fixture has no leaks
  CPPUNIT_TEST( TestStaticAllocation );
  CPPUNIT_TEST( TestDynamicAllocation );
  CPPUNIT_TEST( TestOnSmooth );
  CPPUNIT_TEST( TestOnMedian );
  CPPUNIT_TEST( TestOnClear );
  CPPUNIT_TEST( TestAccept );
  CPPUNIT_TEST( TestUndo );
  CPPUNIT_TEST( TestApplyFiltersToInputData );
  CPPUNIT_TEST_SUITE_END();

private:
  void TestFixture();
  void TestStaticAllocation();
  void TestDynamicAllocation();
  void TestOnSmooth();
  void TestOnMedian();
  void TestOnClear();
  void TestAccept();
  void TestUndo();
  void TestApplyFiltersToInputData();

  void CreateDataTest();
  vtkImageData *m_InputIM;
  vtkRectilinearGrid *m_InputRG;
  bool m_Result;
};

int
main( int argc, char* argv[] )
{
  // Create the event manager and test controller
  CPPUNIT_NS::TestResult controller;

  // Add a listener that collects test result
  CPPUNIT_NS::TestResultCollector result;
  controller.addListener( &result );        

  // Add a listener that print dots as test run.
  CPPUNIT_NS::BriefTestProgressListener progress;
  controller.addListener( &progress );      

  // Add the top suite to the test runner
  CPPUNIT_NS::TestRunner runner;
  runner.addTest( mafOpFilterVolumeTest::suite());
  runner.run( controller );

  // Print test in a compiler compatible format.
  CPPUNIT_NS::CompilerOutputter outputter( &result, CPPUNIT_NS::stdCOut() );
  outputter.write(); 

  return result.wasSuccessful() ? 0 : 1;
}
#endif