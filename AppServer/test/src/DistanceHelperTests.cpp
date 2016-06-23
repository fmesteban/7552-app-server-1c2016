#include <limits.h>
#include "gtest/gtest.h"
#include "../src/web_server/helpers/distance.h"

class DistanceHelperTest : public ::testing::Test {
 protected:
  virtual void SetUp() {
  }

  virtual void TearDown() {
    // Code here will be called immediately after each test
    // (right before the destructor).
  }
};

TEST_F(DistanceHelperTest, twoValues){
    const double lat1 = -34.6970;
    const double long1 = -58.3768;
    const double lat2 = -34.6975;
    const double long2 = -58.37704;
    // Acoording to http://www.movable-type.co.uk/scripts/latlong.html
    const double distance = 0.05977; // In KM
    DistanceHelper distanceHelper;
    ASSERT_FLOAT_EQ(distance, distanceHelper.distanceEarth(lat1, long1, lat2, long2));
}