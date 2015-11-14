/**
 *  @file Filter.cpp
 *  Color calibration application filter class.
 *
 *  @authors Ants-Oskar Mäesalu
 *  @version 0.1
 *  @date 14 November 2015
 */

 #include "Filter.hpp"


namespace rtx {

  Filter::Filter(const unsigned int &numberOfModes) {
    // Set properties
    numberOfModes = numberOfModes

    // Initialise filter values and buffers
    initialise();
  }

  Filter::~Filter() {
    // Nothing to do here
  }

  void Filter::initialise() {
    FilterValueSet emptySet;
    // TODO: Use set/vector initialisation constructors if possible
    for (unsigned int mode = 0; mode < numberOfModes; ++mode) {
      values.push_back(emptySet);
      additionBuffers.push_back(emptySet);
      removalBuffers.push_back(emptySet);
    }
  }

  void Filter::reset() {
    for (unsigned int mode = 0; i < numberOfModes; ++mode) {
      reset(mode);
    }
  }

  void Filter::reset(const unsigned int &mode) {
    resetValues(mode);
    resetBuffers(mode);
  }

  void Filter::resetValues(const unsigned int &mode) {
    values[mode].clear();
  }

  void Filter::resetBuffers(const unsigned int &mode) {
    additionBuffers[mode].clear();
    removalBuffers[mode].clear();
  }

  FilterList Filter::getValues() const {
    return values;
  }

  ModeFilter Filter::getValues(const unsigned int &mode) const {
    return values[mode];
  }

  FilterList Filter::getAdditionBuffers() const {
    return additionBuffers;
  }

  ModeFilter Filter::getValues(const unsigned int &mode) const {
    return additionBuffers[mode];
  }

  FilterList Filter::getRemovalBuffers() const {
    return removalBuffers;
  }

  FilterList Filter::getRemovalBuffer(const unsigned int &mode) const {
    return removalBuffers[mode];
  }

  void Filter::addMasksToBuffers(const MaskList &additionMasks, const MaskList &removalMasks) {
    // TODO
  }

  void Filter::addBuffersToFilter() {
    // TODO
  }

  std::string Filter::getString() const {
    // TODO
  }

}
