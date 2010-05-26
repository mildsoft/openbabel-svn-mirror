/**********************************************************************
align.cpp - Align two molecules or vectors of vector3
 
Copyright (C) 2010 by Noel M. O'Boyle
 
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

#include <openbabel/babelconfig.h>

#include <vector>

#include <openbabel/math/align.h>
#include <openbabel/math/vector3.h>
#include <Eigen/Dense>

//#define VERBOSE_DEBUG

using namespace std;

namespace OpenBabel
{
  OBAlign::OBAlign() {
    _ready = false;
  }
  OBAlign::OBAlign(const vector<vector3> &ref, const vector<vector3> &target)
  {
    SetRef(ref);
    SetTarget(target);
  }
  OBAlign::OBAlign(const OBMol &refmol, const OBMol &targetmol) {
    SetRefMol(refmol);
    SetTargetMol(targetmol);
  }
  void OBAlign::VectorsToMatrix(const vector<vector3> *pcoords, Eigen::MatrixXd &coords) {
    
    vector<vector3>::size_type N = pcoords->size();
    coords.resize(3, N);

    // Create a 3xN matrix of the coords
    vector<vector3>::const_iterator it;
    vector<vector3>::size_type colm;
    for (colm=0,it=pcoords->begin();colm<N;++colm,++it)
      coords.col(colm) = Eigen::Vector3d( it->AsArray() );
  }

  Eigen::Vector3d OBAlign::MoveToOrigin(Eigen::MatrixXd &coords) {

    vector<vector3>::size_type N = coords.cols();

    // Find the centroid
    Eigen::Vector3d centroid;
    centroid = coords.rowwise().sum() / N;

    // Subtract the centroids
    for (vector<vector3>::size_type i=0; i<N; ++i)
      coords.col(i) -= centroid;
    return centroid;
  }

  void OBAlign::SetRef(const vector<vector3> &ref) {
    _pref = &ref;
    VectorsToMatrix(_pref, _mref);
    _ref_centr = MoveToOrigin(_mref);

    _ready = false;
  }

  void OBAlign::SetTarget(const vector<vector3> &target) {
    _ptarget = &target;
    VectorsToMatrix(_ptarget, _mtarget);
    MoveToOrigin(_mtarget); // No need to store this centroid

    _ready = false;
  }
  void OBAlign::SetRefMol(const OBMol &refmol) {
    _refmol_coords.resize(0);
    for (int i=1; i<=refmol.NumAtoms(); ++i)
      _refmol_coords.push_back(refmol.GetAtom(i)->GetVector());
    SetRef(_refmol_coords);
  }
  void OBAlign::SetTargetMol(const OBMol &targetmol) {
    _targetmol_coords.resize(0);
    for (int i=1; i<=targetmol.NumAtoms(); ++i)
      _targetmol_coords.push_back(targetmol.GetAtom(i)->GetVector());
    SetTarget(_targetmol_coords);
  }
  bool OBAlign::Align()
  {
    vector<vector3>::size_type N = _ptarget->size();

    if (_pref->size() != N) {
      // Warn!
      return false;
    }

    // Covariance matrix C = X times Y(t)
    Eigen::Matrix3d C = _mref * _mtarget.transpose();
    
    // Singular Value Decomposition of C into USV(t)
    Eigen::SVD<Eigen::Matrix3d> svd(C);

    // Prepare matrix T
    double sign = (C.determinant() > 0) ? 1. : -1.; // Sign of determinant
    Eigen::Matrix3d T = Eigen::Matrix3d::Identity();
    T(2,2) = sign;

    // Optimal rotation matrix, U, is V T U(t)
    _rotMatrix = svd.matrixV() * T * svd.matrixU().transpose();
    
    // Rotate target using rotMatrix
    _result = _mtarget.transpose() * _rotMatrix;
    _result.transposeInPlace(); // To give 3xN matrix

    Eigen::MatrixXd deviation = _result - _mref;
    Eigen::MatrixXd sqr = deviation.cwise().square();
    double sum = sqr.sum();
    _rmsd = sqrt( sum / sqr.size() );

    // Add back the centroid of the reference
    for (int i=0; i<N; ++i)
      _result.col(i) += _ref_centr;

    _ready = true;
    return true;
  }

  vector<vector3> OBAlign::GetAlignment() {
    if (!_ready) {
      // Warn!
      return (vector<vector3>) NULL;
    }

    // Convert result from MatrixXd to vector<vector3>
    vector<vector3> aligned_coords;
    aligned_coords.reserve(_result.cols());
    for (int i=0; i<_result.cols(); ++i)
      aligned_coords.push_back(vector3(_result(0, i), _result(1, i), _result(2, i)));

    return aligned_coords;
  }

  double OBAlign::GetRMSD() {
    if (!_ready) {
      // Warn!
      return (double) NULL;
    }
    
    return _rmsd;
  }

} // namespace OpenBabel

//! \file align.cpp
//! \brief Handle 3D coordinates.