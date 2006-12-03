/**********************************************************************
vector3.cpp - Handle 3D coordinates.
 
Copyright (C) 1998-2001 by OpenEye Scientific Software, Inc.
Some portions Copyright (C) 2001-2005 by Geoffrey R. Hutchison
 
This file is part of the Open Babel project.
For more information, see <http://openbabel.sourceforge.net/>
 
This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation version 2 of the License.
 
This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.
***********************************************************************/

#include "babelconfig.h"

#include <ostream>

#include "math/vector3.h"

using namespace std;

namespace OpenBabel
{

  /*! \class vector3
    \brief Represents a vector in the 3-dimensional real space.

    The vector3 class was designed to simplify operations with floating
    point coordinates. To this end many of the common operations have been
    overloaded for simplicity. Vector addition, subtraction, scalar
    multiplication, dot product, cross product, magnitude and a number of
    other utility functions are built in to the vector class. For a full
    description of the class member functions please consult the header
    file vector3.h. The following code demonstrates several of the
    functions of the vector class:
    \code
    vector3 v1,v2,v3;
    v1 = VX;
    v2 = VY;
    v3 = cross(v1,v2);
    v3 *= 2.5;
    v3.normalize();
    \endcode
  */

  /*! This (slow) method allows to access the elements of the
    vector as if it were an array of doubles. If the index is > 2,
    then a warning is printed and 0.0 is returned.
    Otherwise, if i is 0, 1 or 2, then a reference to x,
    y or z is returned, respectively.
  
    \warning This method is primarily designed to facilitate the
    integration ('Open Babelization') of code that uses arrays of
    doubles rather than the vector class. Due to the error checks
    the method is of course very slow and should therefore be
    avoided in production code.
  */
  double vector3::operator[] ( unsigned int i)
  {
#ifdef OB_OLD_MATH_CHECKS
    if (i > 2)
      {
        cerr << "ERROR in OpenBabel::vector3::operator[]" << endl
             << "The method has been called with an illegal index i=" << i << "." << endl
             << "Please contact the author of the offending program immediately." << endl;
        return 0.0;
      }
#endif
    if (i == 0)
      return _vx;
    if (i == 1)
      return _vy;
    else return _vz;
  }

  /*! replaces *this with a random unit vector, which is (supposed
    to be) uniformly distributed over the unit sphere. Uses the
    random number generator obRand, or uses the system number
    generator with a time seed if obRand == NULL.
     
    @param obRandP random number generator to use, or 0L, if the
    system random number generator (with time seed) should be used
  */
  void vector3::randomUnitVector(OBRandom *obRandP)
  {
    OBRandom *ptr;
    if (!obRandP)
      {
        ptr = new OBRandom(true);
        ptr->TimeSeed();
      }
    else
      ptr = obRandP;

    // obtain a random vector with 0.001 <= length^2 <= 1.0, normalize
    // the vector to obtain a random vector of length 1.0.
    double l;
    do
      {
        this->Set(ptr->NextFloat()-0.5, ptr->NextFloat()-0.5, ptr->NextFloat()-0.5);
        l = length_2();
      }
    while ( (l > 1.0) || (l < 1e-4) );
    this->normalize();

    if (!obRandP)
      delete ptr;
  }

  OBAPI ostream& operator<< ( ostream& co, const vector3& v )
  {
    co << "< " << v.x() << ", " << v.y() << ", " << v.z() << " >" ;
    return co ;
  }

  OBAPI int vector3::operator== ( const vector3& other ) const
  {
    return ( ( x() == other.x() ) &&
             ( y() == other.y() ) &&
             ( z() == other.z() ) );
  }

  bool vector3::IsApprox(const vector3 & other, const double & precision) const
  {
    return( distSq( other )
            <= precision * precision
               * fmin( length_2(), other.length_2() ) );
  }

  /*! This method returns true if *this can be safely normalized.
   * Vectors that can't be safely normalized are:
   * - the zero vector (0,0,0)
   * - vectors having coords that can't be squared without triggering
   * an overflow or underflow. This means doubles having absolute
   * value greater than 1e150 or smaller than 1e-150.
   */
  bool vector3::CanBeNormalized () const
  {
    if( _vx == 0.0 && _vy == 0.0 && _vz == 0.0 ) return false;
    return( CanBeSquared(_vx)
         && CanBeSquared(_vy)
         && CanBeSquared(_vz) );
  }

  /*! This method normalizes *this. In other words, it divides
   * the x,y,z coords of *this by this->length().
   * If *this can't be safely normalized, it remains unchanged.
   * See CanBeNormalized().

   @returns a reference to *this

   */
  vector3& vector3 :: normalize ()
  {
#ifdef OB_OLD_MATH_CHECKS
    if( CanBeNormalized() )
      (*this) /= length();
#else
    (*this) /= length();
#endif
    return(*this);
  }

  OBAPI vector3 cross ( const vector3& v1, const vector3& v2 )
  {
    vector3 vv ;

    vv.x() =   v1.y()*v2.z() - v1.z()*v2.y() ;
    vv.y() = - v1.x()*v2.z() + v1.z()*v2.x() ;
    vv.z() =   v1.x()*v2.y() - v1.y()*v2.x() ;

    return ( vv ) ;
  }


  /*! This method calculates the angle between two vectors
     
  \warning If length() of any of the two vectors is == 0.0,
  this method will divide by zero. If the product of the
  length() of the two vectors is very close to 0.0, but not ==
  0.0, this method may behave in unexpected ways and return
  almost random results; details may depend on your particular
  floating point implementation. The use of this method is
  therefore highly discouraged, unless you are certain that the
  length()es are in a reasonable range, away from 0.0 (Stefan
  Kebekus)

  \deprecated This method will probably replaced by a safer
  algorithm in the future.

  \todo Replace this method with a more fool-proof version.

  @returns the angle in degrees (0-360)
  */
  OBAPI double vectorAngle ( const vector3& v1, const vector3& v2 )
  {
    double dp;

    dp = dot(v1,v2)/ ( v1.length() * v2.length() );

#ifdef OB_OLD_MATH_CHECKS
    if (dp < -0.999999)
      dp = -0.9999999;

    if (dp > 0.9999999)
      dp = 0.9999999;
#endif

    return((RAD_TO_DEG * acos(dp)));
  }

  /*!  This function calculates the tortion angle of three vectors, represented
    by four points A--B--C--D, i.e. B and C are vertexes, but none of A--B,
    B--C, and C--D are colinear.  A "tortion angle" is the amount of "twist"
    or torsion needed around the B--C axis to bring A--B into the same plane
    as B--C--D.  The torsion is measured by "looking down" the vector B--C so
    that B is superimposed on C, then noting how far you'd have to rotate
    A--B to superimpose A over D.  Angles are + in theanticlockwise
    direction.  The operation is symmetrical in that if you reverse the image
    (look from C to B and rotate D over A), you get the same answer.
  */

  OBAPI double CalcTorsionAngle(const vector3 &a, const vector3 &b,
                                const vector3 &c, const vector3 &d)
  {
    double torsion;
    vector3 b1,b2,b3,c1,c2,c3;

    b1 = a - b;
    b2 = b - c;
    b3 = c - d;

    c1 = cross(b1,b2);
    c2 = cross(b2,b3);
    c3 = cross(c1,c2);

#ifdef OB_OLD_MATH_CHECKS
    if (c1.length() * c2.length() < 0.001)
    {
      torsion = 0.0;
      return torsion;
    }
#endif

    torsion = vectorAngle(c1,c2);
    if (dot(b2,c3) > 0.0)
      torsion = -torsion;

    return(torsion);
  }

  /*! This method constructs a unit vector orthogonal to *this.
   * It requires that *this is normalizable; otherwise it just
   * returns false. See CanBeNormalized.

   @param res reference by which to pass the result.

   @returns false if *this was not normalizable.

  */
  bool vector3::createOrthoVector(vector3 &res) const
  {
#ifdef OB_OLD_MATH_CHECKS
    // sanity check
    if( ! CanBeNormalized() ) return false;
#endif

    /* Let us compute the crossed product of *this with a vector
       that is not too close to being colinear to *this.
    */

    /* if the absolute values of _vx and _vy are not of the same
    order of magnitude, then (_vy,_vx,_vz) is not close to being
    colinear to *this.
    */
    if( ! IsApprox_pos ( fabs(_vx), fabs(_vy), 0.1 ) )
    {
      // store in res the crossed product of *this with (_vy,_vx,_vz),
      // and normalize it.
      res._vx = (_vy-_vx)*_vz;
      res._vy = res._vx;
      res._vz = _vx*_vx - _vy*_vy;
      res.normalize();
    }
    /* on the other hand, if the absolute values of the x and y-coords
    are of the same order of
    magnitude, then the vector is far from being colinear to (1, 0, 0).
    */
    else
    {
      // store in res the crossed product of *this with (1,0,0),
      // divided by its norm. In this case the computation is much simpler.
      double norm = sqrt( _vy*_vy + _vz*_vz );
      res._vx = 0.0;
      res._vy = _vz / norm;
      res._vz = -_vy / norm;
    }

    return true;
  }

  const vector3 VZero ( 0.0, 0.0, 0.0 ) ;
  const vector3 VX    ( 1.0, 0.0, 0.0 ) ;
  const vector3 VY    ( 0.0, 1.0, 0.0 ) ;
  const vector3 VZ    ( 0.0, 0.0, 1.0 ) ;

  /* Calculate the distance of point a to the plane determined by b,c,d */
  double Point2Plane(vector3 a, vector3 b, vector3 c, vector3 d)
  {
    vector3 v_ba = a-b;
    vector3 v_normal = cross(c-b, d-b);
    return fabs( dot( v_normal, v_ba ) / v_normal.length() );
  }

} // namespace OpenBabel

//! \file vector3.cpp
//! \brief Handle 3D coordinates.
