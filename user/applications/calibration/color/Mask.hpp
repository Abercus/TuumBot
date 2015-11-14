/**
 *  @file Mask.hpp
 *  Color calibration application mask class.
 *
 *  @authors Ants-Oskar Mäesalu
 *  @version 0.1
 *  @date 14 November, 2015
 */

#ifndef RTX_APPLICATIONS_CALIBRATION_COLOR_MASK_H
#define RTX_APPLICATIONS_CALIBRATION_COLOR_MASK_H

#include <vector>
#include <set>


namespace rtx {

  typedef std::set<unsigned int> MaskValueSet;
  typedef std::vector<MaskValueSet> MaskList;
  typedef std::vector<std::vector<bool>> MaskValueMap;
  typedef std::vector<MaskValueMap> MaskMapList;

  class Mask {

    public:
      Mask();
      virtual ~Mask();

      MaskList getAdditionValues() const;
      MaskValueSet getAdditionValues(const unsigned int&) const;

      MaskList getRemovalValues() const;
      MaskValueSet getRemovalValues(const unsigned int&) const;

      MaskMapList getAdditionMaps() const;
      MaskValueMap getAdditionMap(const unsigned int&) const;

      MaskMapList getRemovalMaps() const;
      MaskValueMap getRemovalMap(const unsigned int&) const;

      bool isEmpty() const;
      bool isEmpty(const unsigned int&) const;
      bool isAdditionEmpty(const unsigned int&) const;
      bool isRemovalEmpty(const unsigned int&) const;

      void add(const unsigned int&, const unsigned int&);
      void remove(const unsigned int&, const unsigned int&);

    private:
      MaskList additionValues;
      MaskList removalValues;
      MaskMapList additionMaps;
      MaskMapList removalMaps;

      void change(const unsigned int&, const unsigned int&, const bool&);

  };

}

#endif RTX_APPLICATIONS_CALIBRATION_COLOR_MASK_H
