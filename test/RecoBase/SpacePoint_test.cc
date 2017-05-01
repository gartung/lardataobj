/**
 * @file    SpacePoint_test.cc
 * @brief   Simple test on a recob::SpacePoint object
 * @author  Gianluca Petrillo (petrillo@fnal.gov)
 * @date    20170501
 * @version 1.0
 *
 * This test just exercises the comparison operators of `recob::SpacePoint`.
 * 
 * Execution time (profiling mode): < 1s.
 */

// C/C++ standard library
#include <vector>
#include <algorithm> // std::sort(), std::is_sorted(), std::shuffle(), ...
#include <random> // std::default_random_engine

// Boost libraries
#define BOOST_TEST_MODULE ( SpacePoint_test )
#include "cetlib/quiet_unit_test.hpp" // BOOST_AUTO_TEST_CASE()
#include <boost/test/test_tools.hpp> // BOOST_CHECK()

// LArSoft libraries
#include "lardataobj/RecoBase/SpacePoint.h"



//------------------------------------------------------------------------------
//--- Test code
//
void testSorting() {
  
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
  
  for (size_t i = 0; i < points.size(); ++i) {
    for (size_t j = 0; j < points.size(); ++j) {
      BOOST_TEST_MESSAGE("Compare: [i=" << i << "] -- [j=" << j << "]");
      if (i == j) {
        BOOST_CHECK(!(points[i] < points[j]));
        BOOST_CHECK(!(points[j] < points[i]));
      }
      else if (i < j) {
        BOOST_CHECK( (points[i] < points[j]));
        BOOST_CHECK(!(points[j] < points[i]));
        BOOST_CHECK_LT(points[i], points[j]);
      }
      else if (i > j) {
        BOOST_CHECK(!(points[i] < points[j]));
        BOOST_CHECK( (points[j] < points[i]));
        BOOST_CHECK_LT(points[j], points[i]);
      }
    } // for i
  } // for j
  
  // shuffle
  BOOST_CHECK(std::is_sorted(points.begin(), points.end()));
  BOOST_TEST_CHECKPOINT("Shuffling...");
  std::default_random_engine engine(12345U);
  do {
    std::shuffle(points.begin(), points.end(), engine);  
  } while (std::is_sorted(points.begin(), points.end()));
  BOOST_TEST_CHECKPOINT("Shuffling done.");
  
  std::sort(points.begin(), points.end());
  BOOST_CHECK(std::is_sorted(points.begin(), points.end()));
  
} // testSorting()



//------------------------------------------------------------------------------
//--- registration of tests
//

BOOST_AUTO_TEST_CASE(Sorting_test) {
  testSorting();
}
