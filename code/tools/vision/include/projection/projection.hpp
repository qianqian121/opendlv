/**
 * Copyright (C) 2016 Chalmers REVERE
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301,
 * USA.
 */

#ifndef PROJECTION_PROJECTION_HPP_
#define PROJECTION_PROJECTION_HPP_

#include <memory>
#include <Eigen/Dense>

#include <opendavinci/odcore/base/module/TimeTriggeredConferenceClientModule.h>
#include <opendavinci/odcore/data/Container.h>

#include "opencv2/video/tracking.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

void LoggMouseClicks(int32_t , int32_t, int32_t, int32_t, void*);
void projectMouseClicks(int32_t, int32_t, int32_t, int32_t, void*);

namespace opendlv {
namespace tools {
namespace vision {
namespace projection {
class Projection
: public odcore::base::module::TimeTriggeredConferenceClientModule{
 public:
  Projection(int32_t const &, char **);
  Projection(Projection const &) = delete;
  Projection &operator=(Projection const &) = delete;
  virtual ~Projection();

  virtual void nextContainer(odcore::data::Container &);

 private:
  void setUp();
  void tearDown();

  odcore::data::dmcp::ModuleExitCodeMessage::ModuleExitCode body();
  void calibrate();
  void config();
  void save();
  void project();


  char m_option;
  double m_recHeight, m_recWidth, m_recPosX, m_recPosY;
  Eigen::MatrixXd m_aMatrix, m_bMatrix, m_projectionMatrix;
};

} // projection
} // vision
} // tools
} // opendlv

#endif
