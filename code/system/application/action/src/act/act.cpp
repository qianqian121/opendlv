/**
 * Copyright (C) 2015 Chalmers REVERE
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

#include <ctype.h>
#include <cstring>
#include <cmath>
#include <iostream>

#include "opendavinci/odcore/data/Container.h"
#include "opendavinci/odcore/data/TimeStamp.h"

#include "opendlvdata/GeneratedHeaders_opendlvdata.h"

#include "act/act.hpp"

namespace opendlv {
namespace action {
namespace act {

/**
  * Constructor.
  *
  * @param a_argc Number of command line arguments.
  * @param a_argv Command line arguments.
  */
Act::Act(int32_t const &a_argc, char **a_argv)
    : TimeTriggeredConferenceClientModule(a_argc, a_argv, "action-act")
{
}

Act::~Act()
{
}

/**
 * Receives control correction requests, including a modality, if inhibitory,
 * amplitude, and a start time.
 * Sends modulated contol signal as individual samples, per modality to Proxy
 * actuators.
 */
odcore::data::dmcp::ModuleExitCodeMessage::ModuleExitCode Act::body()
{
  while (getModuleStateAndWaitForRemainingTimeInTimeslice() ==
      odcore::data::dmcp::ModuleStateMessage::RUNNING) {

    float acceleration = 0.0f;
    float steering = 0.0f;
  
    opendlv::proxy::Actuation actuation(acceleration, steering);
    odcore::data::Container c(actuation);
    getConference().send(c);
  }

  return odcore::data::dmcp::ModuleExitCodeMessage::OKAY;
}

void Act::nextContainer(odcore::data::Container &c)
{
  if(c.getDataType() == opendlv::action::Correction::ID()) {
    opendlv::action::Correction correction = 
      c.getData<opendlv::action::Correction>();

    odcore::data::TimeStamp t0 = correction.getStartTime();
    std::string type = correction.getType();
    //bool isInhibitory = correction.getIsInhibitory();
    float amplitude = correction.getAmplitude();

    if (type == "accelerate") {
      std::cout << "accelerate: " << amplitude << std::endl;
    } else if (type == "brake") {
      std::cout << "brake: " << amplitude << std::endl;
    }
  }
}

void Act::setUp()
{
}

void Act::tearDown()
{
}

} // act
} // action
} // opendlv
