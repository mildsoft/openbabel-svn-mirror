/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 1.3.30
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */


public class OBResidue extends OBBase {
  private long swigCPtr;

  protected OBResidue(long cPtr, boolean cMemoryOwn) {
    super(net.sourceforge.openbabelJNI.SWIGOBResidueUpcast(cPtr), cMemoryOwn);
    swigCPtr = cPtr;
  }

  protected static long getCPtr(OBResidue obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if(swigCPtr != 0 && swigCMemOwn) {
      swigCMemOwn = false;
      net.sourceforge.openbabelJNI.delete_OBResidue(swigCPtr);
    }
    swigCPtr = 0;
    super.delete();
  }

  public OBResidue() {
    this(net.sourceforge.openbabelJNI.new_OBResidue__SWIG_0(), true);
  }

  public OBResidue(OBResidue arg0) {
    this(net.sourceforge.openbabelJNI.new_OBResidue__SWIG_1(OBResidue.getCPtr(arg0), arg0), true);
  }

  public void AddAtom(OBAtom atom) {
    net.sourceforge.openbabelJNI.OBResidue_AddAtom(swigCPtr, this, OBAtom.getCPtr(atom), atom);
  }

  public void InsertAtom(OBAtom atom) {
    net.sourceforge.openbabelJNI.OBResidue_InsertAtom(swigCPtr, this, OBAtom.getCPtr(atom), atom);
  }

  public void RemoveAtom(OBAtom atom) {
    net.sourceforge.openbabelJNI.OBResidue_RemoveAtom(swigCPtr, this, OBAtom.getCPtr(atom), atom);
  }

  public void Clear() {
    net.sourceforge.openbabelJNI.OBResidue_Clear(swigCPtr, this);
  }

  public void SetName(String resname) {
    net.sourceforge.openbabelJNI.OBResidue_SetName(swigCPtr, this, resname);
  }

  public void SetNum(long resnum) {
    net.sourceforge.openbabelJNI.OBResidue_SetNum(swigCPtr, this, resnum);
  }

  public void SetChain(char chain) {
    net.sourceforge.openbabelJNI.OBResidue_SetChain(swigCPtr, this, chain);
  }

  public void SetChainNum(long chainnum) {
    net.sourceforge.openbabelJNI.OBResidue_SetChainNum(swigCPtr, this, chainnum);
  }

  public void SetIdx(long idx) {
    net.sourceforge.openbabelJNI.OBResidue_SetIdx(swigCPtr, this, idx);
  }

  public void SetAtomID(OBAtom atom, String id) {
    net.sourceforge.openbabelJNI.OBResidue_SetAtomID(swigCPtr, this, OBAtom.getCPtr(atom), atom, id);
  }

  public void SetHetAtom(OBAtom atom, boolean hetatm) {
    net.sourceforge.openbabelJNI.OBResidue_SetHetAtom(swigCPtr, this, OBAtom.getCPtr(atom), atom, hetatm);
  }

  public void SetSerialNum(OBAtom atom, long sernum) {
    net.sourceforge.openbabelJNI.OBResidue_SetSerialNum(swigCPtr, this, OBAtom.getCPtr(atom), atom, sernum);
  }

  public String GetName() {
    return net.sourceforge.openbabelJNI.OBResidue_GetName(swigCPtr, this);
  }

  public long GetNum() {
    return net.sourceforge.openbabelJNI.OBResidue_GetNum(swigCPtr, this);
  }

  public long GetNumAtoms() {
    return net.sourceforge.openbabelJNI.OBResidue_GetNumAtoms(swigCPtr, this);
  }

  public char GetChain() {
    return net.sourceforge.openbabelJNI.OBResidue_GetChain(swigCPtr, this);
  }

  public long GetChainNum() {
    return net.sourceforge.openbabelJNI.OBResidue_GetChainNum(swigCPtr, this);
  }

  public long GetIdx() {
    return net.sourceforge.openbabelJNI.OBResidue_GetIdx(swigCPtr, this);
  }

  public long GetResKey() {
    return net.sourceforge.openbabelJNI.OBResidue_GetResKey(swigCPtr, this);
  }

  public SWIGTYPE_p_std__vectorTOpenBabel__OBAtom_p_t GetAtoms() {
    return new SWIGTYPE_p_std__vectorTOpenBabel__OBAtom_p_t(net.sourceforge.openbabelJNI.OBResidue_GetAtoms(swigCPtr, this), true);
  }

  public SWIGTYPE_p_std__vectorTOpenBabel__OBBond_p_t GetBonds(boolean exterior) {
    return new SWIGTYPE_p_std__vectorTOpenBabel__OBBond_p_t(net.sourceforge.openbabelJNI.OBResidue_GetBonds__SWIG_0(swigCPtr, this, exterior), true);
  }

  public SWIGTYPE_p_std__vectorTOpenBabel__OBBond_p_t GetBonds() {
    return new SWIGTYPE_p_std__vectorTOpenBabel__OBBond_p_t(net.sourceforge.openbabelJNI.OBResidue_GetBonds__SWIG_1(swigCPtr, this), true);
  }

  public String GetAtomID(OBAtom atom) {
    return net.sourceforge.openbabelJNI.OBResidue_GetAtomID(swigCPtr, this, OBAtom.getCPtr(atom), atom);
  }

  public long GetSerialNum(OBAtom atom) {
    return net.sourceforge.openbabelJNI.OBResidue_GetSerialNum(swigCPtr, this, OBAtom.getCPtr(atom), atom);
  }

  public boolean GetAminoAcidProperty(int arg0) {
    return net.sourceforge.openbabelJNI.OBResidue_GetAminoAcidProperty(swigCPtr, this, arg0);
  }

  public boolean GetAtomProperty(OBAtom arg0, int arg1) {
    return net.sourceforge.openbabelJNI.OBResidue_GetAtomProperty(swigCPtr, this, OBAtom.getCPtr(arg0), arg0, arg1);
  }

  public boolean GetResidueProperty(int arg0) {
    return net.sourceforge.openbabelJNI.OBResidue_GetResidueProperty(swigCPtr, this, arg0);
  }

  public boolean IsHetAtom(OBAtom atom) {
    return net.sourceforge.openbabelJNI.OBResidue_IsHetAtom(swigCPtr, this, OBAtom.getCPtr(atom), atom);
  }

  public boolean IsResidueType(int arg0) {
    return net.sourceforge.openbabelJNI.OBResidue_IsResidueType(swigCPtr, this, arg0);
  }

  public OBAtom BeginAtom(SWIGTYPE_p_std__vectorTOpenBabel__OBAtom_p_t__iterator i) {
    long cPtr = net.sourceforge.openbabelJNI.OBResidue_BeginAtom(swigCPtr, this, SWIGTYPE_p_std__vectorTOpenBabel__OBAtom_p_t__iterator.getCPtr(i));
    return (cPtr == 0) ? null : new OBAtom(cPtr, false);
  }

  public OBAtom NextAtom(SWIGTYPE_p_std__vectorTOpenBabel__OBAtom_p_t__iterator i) {
    long cPtr = net.sourceforge.openbabelJNI.OBResidue_NextAtom(swigCPtr, this, SWIGTYPE_p_std__vectorTOpenBabel__OBAtom_p_t__iterator.getCPtr(i));
    return (cPtr == 0) ? null : new OBAtom(cPtr, false);
  }

}
