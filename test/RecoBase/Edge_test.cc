/**
 * @file    Edge_test.cc
 * @brief   Simple test on a recob::Edge object
 * @author  Gianluca Petrillo (petrillo@fnal.gov)
 * @date    20170501
 * @version 1.0
 *
 * This test just exercises the comparison operators of `recob::Edge`.
 * 
 * Execution time (profiling mode): < 1s.
 */

// C/C++ standard library
#include <vector>
#include <algorithm> // std::sort(), std::lower_bound(), ...
#include <random> // std::default_random_engine

// Boost libraries
#define BOOST_TEST_MODULE ( SpacePoint_test )
#include "cetlib/quiet_unit_test.hpp" // BOOST_AUTO_TEST_CASE()
#include <boost/test/test_tools.hpp> // BOOST_CHECK()
#include <boost/test/floating_point_comparison.hpp> // BOOST_CHECK_CLOSE()


// LArSoft libraries
#include "lardataobj/RecoBase/Edge.h"
#include "lardataobj/RecoBase/SpacePoint.h"



//------------------------------------------------------------------------------
//--- Test code
//
void testDefaultConstructor() {
  
  // these constants are required because BOOST_CHECK_EQUAL tries to get the
  // address of the arguments, and the InvalidID constants have no address.
  auto const InvalidSP = recob::SpacePoint::InvalidID;
  auto const InvalidEdge = recob::Edge::InvalidID;
  
  recob::Edge e;
  BOOST_CHECK_EQUAL(e.FirstPointID(), InvalidSP);
  BOOST_CHECK_EQUAL(e.SecondPointID(), InvalidSP);
  BOOST_CHECK_EQUAL(e.Length(), 0.0); // exact matching is required here
  BOOST_CHECK_EQUAL(e.ID(), InvalidEdge);
  
} // testDefaultConstructor()


void testValuesConstructor() {
  
  recob::Edge e
    (/* length */ 5.0, /* firstPointID */ 3, /* secondPointID */ 4, /* id */ 3);
  BOOST_CHECK_EQUAL(e.FirstPointID(), 3);
  BOOST_CHECK_EQUAL(e.SecondPointID(), 4);
  BOOST_CHECK_EQUAL(e.Length(), 5.0); // exact matching is required here
  BOOST_CHECK_EQUAL(e.ID(), 3);
  
} // testValuesConstructor()


void testSpacePointConstructor() {
  
  double const err[6] = { 1.0, 0.0, 0.0, 0.0, 1.0, 1.0 };
  double pos[3] = { 1.0, 2.0, 3.0 };
  recob::SpacePoint A(pos, err, /* chisq */ 0.0, /* ID */ 1);
  pos[2] = -4.0; 
  recob::SpacePoint B(pos, err, /* chisq */ 0.0, /* ID */ 2);
  
  recob::Edge e(A, B, /* ID */ 3);
  BOOST_CHECK_EQUAL(e.FirstPointID(), 1);
  BOOST_CHECK_EQUAL(e.SecondPointID(), 2);
  BOOST_CHECK_CLOSE(e.Length(), 7.0, 1e-3);
  BOOST_CHECK_EQUAL(e.ID(), 3);
  
} // testSpacePointConstructor()


void testSorting() {
  
  std::vector<recob::Edge> edges;
  
  edges.emplace_back
    (/* Length */ 2.0, /* FirstPointID */ 2, /* SecondPointID */ 3, /* ID */ 1);
  edges.emplace_back
    (/* Length */ 2.0, /* FirstPointID */ 3, /* SecondPointID */ 2, /* ID */ 2);
  edges.emplace_back
    (/* Length */ 4.0, /* FirstPointID */ 3, /* SecondPointID */ 4, /* ID */ 3);
  edges.emplace_back
    (/* Length */ 0.0, /* FirstPointID */ 4, /* SecondPointID */ 4, /* ID */ 4);
  
  for (size_t i = 0; i < edges.size(); ++i) {
    for (size_t j = 0; j < edges.size(); ++j) {
      BOOST_TEST_MESSAGE("Compare: [i=" << i << "] -- [j=" << j << "]");
      if (i == j) {
        BOOST_CHECK(!(edges[i] < edges[j]));
        BOOST_CHECK(!(edges[j] < edges[i]));
      }
      else if (i < j) {
        BOOST_CHECK( (edges[i] < edges[j]));
        BOOST_CHECK(!(edges[j] < edges[i]));
        BOOST_CHECK_LT(edges[i], edges[j]);
      }
      else if (i > j) {
        BOOST_CHECK(!(edges[i] < edges[j]));
        BOOST_CHECK( (edges[j] < edges[i]));
        BOOST_CHECK_LT(edges[j], edges[i]);
      }
    } // for i
  } // for j
  
  // shuffle
  BOOST_CHECK(std::is_sorted(edges.begin(), edges.end()));
  BOOST_TEST_CHECKPOINT("Shuffling...");
  std::default_random_engine engine(12345U);
  do {
    std::shuffle(edges.begin(), edges.end(), engine);
  } while (std::is_sorted(edges.begin(), edges.end()));
  BOOST_TEST_CHECKPOINT("Shuffling done.");
  
  std::sort(edges.begin(), edges.end());
  BOOST_CHECK(std::is_sorted(edges.begin(), edges.end()));
  
} // testSorting()


void testDocumentation_FindSpacePoint() {
  
  std::vector<recob::SpacePoint> points;
  
  double const err[6] = { 1.0, 0.0, 0.0, 0.0, 1.0, 1.0 };
  double pos[3] = { 0.0, 0.0, 0.0 };
  points.emplace_back(pos, err, /* chisq */ 0.0, /* ID */ 1);
  
  pos[1] = 2.0;
  points.emplace_back(pos, err, /* chisq */ 0.0, /* ID */ 2);
  
  pos[0] = 2.0;
  points.emplace_back(pos, err, /* chisq */ 0.0, /* ID */ 3);
  
  pos[1] = 0.0;
  points.emplace_back(pos, err, /* chisq */ 0.0, /* ID */ 4);
  
  recob::Edge edge(points[1], points[2], /* ID */ 1);
  
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  if (!std::is_sorted(points.begin(), points.end()))
    throw std::runtime_error("Space points not sorted!");
  
  // find the first space point
  auto const iFirstPoint = std::lower_bound
    (points.begin(), points.end(), edge.FirstPointID());
  
  if (iFirstPoint == points.end()) {
    throw std::runtime_error
      ("First point not found: ID=" + std::to_string(edge.FirstPointID()));
  }  
  recob::SpacePoint const& firstPoint = *iFirstPoint;
  
  // find the second space point
  auto const iSecondPoint = std::lower_bound
    (points.begin(), points.end(), edge.SecondPointID());
  
  if (iSecondPoint == points.end()) {
    throw std::runtime_error
      ("Second point not found: ID=" + std::to_string(edge.SecondPointID()));
  }  
  recob::SpacePoint const& secondPoint = *iSecondPoint;
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  
  BOOST_CHECK_EQUAL(firstPoint.ID(), edge.FirstPointID());
  BOOST_CHECK_EQUAL(&firstPoint, &(points[1]));
  
  BOOST_CHECK_EQUAL(secondPoint.ID(), edge.SecondPointID());
  BOOST_CHECK_EQUAL(&secondPoint, &(points[2]));
  
  
} // testDocumentation_FindSpacePoint()


//------------------------------------------------------------------------------
//--- registration of tests
//

BOOST_AUTO_TEST_CASE(Constructors_test) {
  testDefaultConstructor();
  testValuesConstructor();
  testSpacePointConstructor();
}

BOOST_AUTO_TEST_CASE(Sorting_test) {
  testSorting();
}

BOOST_AUTO_TEST_CASE(Documentation_test) {
  testDocumentation_FindSpacePoint();
} // BOOST_AUTO_TEST_CASE(Documentation_test)
