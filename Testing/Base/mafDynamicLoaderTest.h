/*=========================================================================
Program:   Multimod Application Framework
Module:    $RCSfile: mafDynamicLoaderTest.h,v $
Language:  C++
Date:      $Date: 2008-09-16 11:36:24 $
Version:   $Revision: 1.1 $
Authors:   Daniele Giunchi
==========================================================================
Copyright (c) 2002/2004 
CINECA - Interuniversity Consortium (www.cineca.it)
=========================================================================*/

#ifndef __CPP_UNIT_mafDynamicLoaderTest_H__
#define __CPP_UNIT_mafDynamicLoaderTest_H__

#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/BriefTestProgressListener.h>
#include <cppunit/CompilerOutputter.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/TestResult.h>
#include <cppunit/TestResultCollector.h>
#include <cppunit/TestRunner.h>

/** Test for mafDynamicLoader; Use this suite to trace memory problems */
class mafDynamicLoaderTest : public CPPUNIT_NS::TestFixture
{
public: 
  // CPPUNIT fixture: executed before each test
  void setUp();

  // CPPUNIT fixture: executed after each test
  void tearDown();

  // CPPUNIT test suite
  CPPUNIT_TEST_SUITE( mafDynamicLoaderTest );
  CPPUNIT_TEST(TestFixture); // just to test that the fixture has no leaks
	CPPUNIT_TEST(TestOpenLibrary);
  CPPUNIT_TEST(TestCloseLibrary);
  CPPUNIT_TEST(TestGetSymbolAddress);
  CPPUNIT_TEST(TestLibPrefix);
  CPPUNIT_TEST(TestLibExtension);
	CPPUNIT_TEST(TestLastError);
  
  CPPUNIT_TEST_SUITE_END();

private:
  void TestFixture();
	void TestOpenLibrary();
	void TestCloseLibrary();
	void TestGetSymbolAddress();
	void TestLibPrefix();
	void TestLibExtension();
	void TestLastError();

	bool result;
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
  runner.addTest( mafDynamicLoaderTest::suite());
  runner.run( controller );

  // Print test in a compiler compatible format.
  CPPUNIT_NS::CompilerOutputter outputter( &result, CPPUNIT_NS::stdCOut() );
  outputter.write(); 

  return result.wasSuccessful() ? 0 : 1;
}
#endif