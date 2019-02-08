/** ****************************************************************************
 * @file Waveform.cxx
 * @brief Definition of basic channel signal object.
 * @author brebel@fnal.gov
 * @see  Waveform.h
 * 
 * ****************************************************************************/

#include "lardataobj/Simulation/Waveform.h"

// C/C++ standard libraries
#include <utility> // std::move()

namespace sim{

  //----------------------------------------------------------------------
  Waveform::Waveform()
    : fChannel(raw::InvalidChannelID)
    , fView(geo::kUnknown)
    , fSignalROI()
    {}

  //----------------------------------------------------------------------
  Waveform::Waveform(
    RegionsOfInterest_t const& sigROIlist,
    raw::ChannelID_t channel,
    geo::View_t view
    )
    : fChannel(channel)
    , fView(view)
    , fSignalROI(sigROIlist)
    {}

  //----------------------------------------------------------------------
  Waveform::Waveform(
    RegionsOfInterest_t&& sigROIlist,
    raw::ChannelID_t channel,
    geo::View_t view
    )
    : fChannel(channel)
    , fView(view)
    , fSignalROI(std::move(sigROIlist))
    {}


  //----------------------------------------------------------------------
  std::vector<float> Waveform::Signal() const {
    return { fSignalROI.begin(), fSignalROI.end() };
  } // Waveform::Signal()


}
////////////////////////////////////////////////////////////////////////

