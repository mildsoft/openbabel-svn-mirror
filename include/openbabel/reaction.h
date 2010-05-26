/**********************************************************************
reaction.h - Handle chemical reactions (i.e., lists of reagents and products).

Copyright (C) 2005 by Chris Morley
 
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

#ifndef OB_REACT_H
#define OB_REACT_H

#include <vector>
#include <openbabel/mol.h>

#ifdef USE_BOOST
  #include <boost/shared_ptr.hpp>
  #define shared_ptr boost::shared_ptr
#else
  #include <memory>
  #if __GNUC__ == 4 && __GNUC_MINOR__ < 6
    #include <tr1/memory>
  #endif
  using std::tr1::shared_ptr;
#endif

namespace OpenBabel
{

//!\brief Used to store chemical reactions (i.e., reactants -> products)
//!
//! Reactants and products stored as smart pointers to molecules stored elsewhere.
//!
//! For performing actual reaction transformations (i.e., deleting atoms,
//! changing bonds, etc.) use the OBChemTsfm class.
class OBReaction : public OBBase
{
private:
  std::vector<shared_ptr<OBMol> > _reactants;
  std::vector<shared_ptr<OBMol> > _products;
  shared_ptr<OBMol> _ts; 
  shared_ptr<OBMol> _agent; 
  std::string _title;
  std::string _comment;
  bool _reversible;
public:
  OBReaction() : _reversible(false)
  {}

  int NumReactants() const
  { return _reactants.size(); }

  int NumProducts()const
  { return _products.size(); }
  
  void AddReactant(const shared_ptr<OBMol> sp)
  { _reactants.push_back(sp); }
  
  void AddProduct(const shared_ptr<OBMol> sp)
  { _products.push_back(sp); }

  void SetTransitionState(const shared_ptr<OBMol> sp)
  { _ts = sp; }

  void AddAgent(const shared_ptr<OBMol> sp)
  { _agent = sp; }
  
  shared_ptr<OBMol> GetReactant(const unsigned i)
  {
    shared_ptr<OBMol> sp;
    if(i<_reactants.size())
      sp = _reactants[i];
    return sp; //returns empty if out of range
  }
  shared_ptr<OBMol> GetProduct(const unsigned i)
  {
    shared_ptr<OBMol> sp;
    if(i<_products.size())
      sp = _products[i];
    return sp; //returns empty if out of range
  }

  shared_ptr<OBMol> GetTransitionState()const
  { return _ts; }

  shared_ptr<OBMol> GetAgent()const
  { return _agent; }

  std::string GetTitle()	const { return _title; }
  std::string GetComment()	const { return _comment; }
  void SetTitle(const std::string& title) { _title=title; }
  void SetComment(const std::string& comment) { _comment=comment; }

  bool IsReversible() const       {return _reversible;}
  void SetReversible(bool b=true) {_reversible=b;}

  static const char* ClassDescription()
  {
    return " reactions\n";
  }

  bool Clear()
  {
    _reactants.clear();
    _products.clear();
    _ts.reset();
    _agent.reset();
    _title.clear();
    _comment.clear();
    _reversible = false;
    return true;
  }
};


} //namespace OpenBabel
#endif

//! \file reaction.h
//! \brief Handle chemical reactions (i.e., lists of reagents and products).
