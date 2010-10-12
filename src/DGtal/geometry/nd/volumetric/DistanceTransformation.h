/**
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Lesser General Public License as
 *  published by the Free Software Foundation, either version 3 of the
 *  License, or  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 **/
//LICENSE-END
#pragma once

/**
 * @file DistanceTransformation.h
 * @author David Coeurjolly (\c david.coeurjolly@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systèmes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 *
 * @date 2010/09/30
 *
 * Header file for module DistanceTransformation.cpp
 *
 * This file is part of the DGtal library.
 */

#if defined(DistanceTransformation_RECURSES)
#error Recursive header files inclusion detected in DistanceTransformation.h
#else // defined(DistanceTransformation_RECURSES)
/** Prevents recursive inclusion of headers. */
#define DistanceTransformation_RECURSES

#if !defined DistanceTransformation_h
/** Prevents repeated inclusion of headers. */
#define DistanceTransformation_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <iostream>
#include "DGtal/base/Common.h"
//////////////////////////////////////////////////////////////////////////////

namespace DGtal
{

  /////////////////////////////////////////////////////////////////////////////
  // template class DistanceTransformation
  /**
   * Description of template class 'DistanceTransformation' <p>
   * \brief Aim:
   */
  template <typename TImage, typename TImageOutput, typename TSeparableMetric >
  class DistanceTransformation
  {

  public:

    ///@todo check image concept
    typedef TImage Image;
    typedef TImageOutput ImageOutput;
    typedef TSeparableMetric SeparableMetric;
    typedef typename TSeparableMetric::InternalValueType InternalValueType;
    typedef typename Image::ValueType ValueType;
    typedef typename Image::Point Point;
    typedef typename Image::DimensionType DimensionType;
    
    
    /** 
     * Default Constructor
     */
    DistanceTransformation();
    
    /** 
     * Default destructor
     */
    ~DistanceTransformation();
    

    // ------- Private Functor to be used as a default template ----
   
  private: 
    /**
     * Default foregroundPredicate : we return true if the value at a
     * point differs from zero.
     *
     * @todo Refactoring needed to generalize this class !
     */
    struct DefaultForegroundPredicate
    {
      bool operator()(const Image &aImage, const typename Image::Point &aPoint) const
      {
	return (aImage(aPoint) !=0);
      }
      
      bool operator()(const Image &aImage, const typename Image::Iterator &it) const
      {
	return (aImage(it) !=0);
      }
      
      bool operator()(const Image &aImage, const typename Image::ConstIterator &it) const
      {
	return (aImage(it) !=0);
      }
      
      bool operator()(const Image &aImage, const typename Image::SpanIterator &it) const
      {
	return (aImage(it) !=0);
      }
      
      /*bool operator()(const Image &aImage, const typename Image::ConstSpanIterator &it)
      {
	return (aImage(it) !=0);
      }*/
    };
  public:

    /** 
     * Check the validity of the transformation. For instance, we
     * check that the output image pixel range is ok with respect to
     * the input image range and the SeparableMetric.
     * 
     * Warning and advices are print in the trace system.
     * 
     * @param aImage the image used to check the type consistency.
     */
    void checkTypesValidity(const Image & aImage);

    /** 
     * Compute the Distance Transformation of an image with the SeparableMetric metric.
     * The method associates to each point with value satisfying the
     * foreground predicate, its distance to the closest background point.
     * 
     * @param inputImage the input image 
     * @param foregroundPredicate a predicate to detect foreground
     * point from the image valuetype
     * @return the distance transformation image with the Internal format.
     */
    template <typename ForegroundPredicate>
    ImageOutput compute(const Image & inputImage, const ForegroundPredicate & predicate  );

    /** 
     * Compute the Distance Transformation of an image with the SeparableMetric metric.
     * The method associates to each point with value satisfying the
     * foreground predicate, its distance to the closest background point.
     * 
     * @param inputImage the input image 
     * @return the distance transformation image with the Internal format.
     */
    ImageOutput compute(const Image & inputImage )
    {
      return compute<DefaultForegroundPredicate>(inputImage, DefaultForegroundPredicate());
    };
    

    // ------------------- Private functions ------------------------
  private:
    
    template <typename ForegroundPredicate>
    void computeFirstStep(const Image & aImage, ImageOutput & output, const ForegroundPredicate &predicate) const;
 
    template <typename ForegroundPredicate>
    void computeFirstStep1D (const Image & aImage, ImageOutput & output,const Point &row, const ForegroundPredicate &predicate) const;
    
    void computeOtherSteps(const ImageOutput & inputImage, ImageOutput & output, const DimensionType dim)const;
    
    
    // ------------------- Private members ------------------------
  private:
    SeparableMetric myMetric;
    Point myLowerBoundCopy;
    Point myUpperBoundCopy;
      
      
  }; // end of class DistanceTransformation
    
} // namespace DGtal


  ///////////////////////////////////////////////////////////////////////////////
  // Includes inline functions.
#include "DGtal/geometry/nd/volumetric/DistanceTransformation.ih"

//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined DistanceTransformation_h

#undef DistanceTransformation_RECURSES
#endif // else defined(DistanceTransformation_RECURSES)