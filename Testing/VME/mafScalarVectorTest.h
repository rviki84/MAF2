/*=========================================================================
  Program:   Multimod Application Framework
  Module:    $RCSfile: mafScalarVectorTest.h,v $
  Language:  C++
  Date:      $Date: 2009-08-19 15:14:02 $
  Version:   $Revision: 1.1.2.1 $
  Authors:   Alberto Losi
==========================================================================
  Copyright (c) 2002/2004 
  CINECA - Interuniversity Consortium (www.cineca.it)
=========================================================================*/

#ifndef __CPP_UNIT_mafScalarVectorTest_H__
#define __CPP_UNIT_mafScalarVectorTest_H__

#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/BriefTestProgressListener.h>
#include <cppunit/CompilerOutputter.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/TestResult.h>
#include <cppunit/TestResultCollector.h>
#include <cppunit/TestRunner.h>

class mafScalarVector;

/** Test for mafScalarVectorTest; Use this suite to trace memory problems */
class mafScalarVectorTest : public CPPUNIT_NS::TestFixture
{
public: 
  // CPPUNIT fixture: executed before each test
  void setUp();

  // CPPUNIT fixture: executed after each test
  void tearDown();

  // CPPUNIT test suite
  CPPUNIT_TEST_SUITE( mafScalarVectorTest );
  CPPUNIT_TEST(TestFixture);
  CPPUNIT_TEST(TestDynamicAllocation);
  CPPUNIT_TEST(TestAppendScalar);
  CPPUNIT_TEST(TestGetScalar);
  CPPUNIT_TEST(TestGetScalarVector);
  CPPUNIT_TEST(TestGetNumberOfScalars);
  CPPUNIT_TEST(TestGetNearestScalar);
  CPPUNIT_TEST(TestGetScalarBefore);
  CPPUNIT_TEST(TestGetScalar);
  CPPUNIT_TEST(TestSetScalar);
  CPPUNIT_TEST_SUITE_END();

private:
  void TestFixture();
  void TestDynamicAllocation();
  void TestAppendScalar();
  void TestGetScalarVector();
  void TestGetNumberOfScalars();
  void TestGetNearestScalar();
  void TestGetScalarBefore();
  void TestGetScalar();
  void TestSetScalar();

  bool result;
  mafScalarVector *m_ScalarVector;
};

int main( int argc, char* argv[] )
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
  runner.addTest( mafScalarVectorTest::suite());
  runner.run( controller );

  // Print test in a compiler compatible format.
  CPPUNIT_NS::CompilerOutputter outputter( &result, CPPUNIT_NS::stdCOut() );
  outputter.write(); 

  return result.wasSuccessful() ? 0 : 1;
}
#endif
