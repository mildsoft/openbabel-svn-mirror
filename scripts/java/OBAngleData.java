/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 1.3.30
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */


public class OBAngleData extends OBGenericData {
  private long swigCPtr;

  protected OBAngleData(long cPtr, boolean cMemoryOwn) {
    super(openbabelJNI.SWIGOBAngleDataUpcast(cPtr), cMemoryOwn);
    swigCPtr = cPtr;
  }

  protected static long getCPtr(OBAngleData obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if(swigCPtr != 0 && swigCMemOwn) {
      swigCMemOwn = false;
      openbabelJNI.delete_OBAngleData(swigCPtr);
    }
    swigCPtr = 0;
    super.delete();
  }

  public OBGenericData Clone(OBBase arg0) {
    long cPtr = openbabelJNI.OBAngleData_Clone(swigCPtr, this, OBBase.getCPtr(arg0), arg0);
    return (cPtr == 0) ? null : new OBGenericData(cPtr, false);
  }

  public void Clear() {
    openbabelJNI.OBAngleData_Clear(swigCPtr, this);
  }

  public long FillAngleArray(SWIGTYPE_p_p_int angles, SWIGTYPE_p_unsigned_int size) {
    return openbabelJNI.OBAngleData_FillAngleArray__SWIG_0(swigCPtr, this, SWIGTYPE_p_p_int.getCPtr(angles), SWIGTYPE_p_unsigned_int.getCPtr(size));
  }

  public boolean FillAngleArray(SWIGTYPE_p_std__vectorTstd__vectorTunsigned_int_t_t angles) {
    return openbabelJNI.OBAngleData_FillAngleArray__SWIG_1(swigCPtr, this, SWIGTYPE_p_std__vectorTstd__vectorTunsigned_int_t_t.getCPtr(angles));
  }

  public void SetData(OBAngle arg0) {
    openbabelJNI.OBAngleData_SetData(swigCPtr, this, OBAngle.getCPtr(arg0), arg0);
  }

  public long GetSize() {
    return openbabelJNI.OBAngleData_GetSize(swigCPtr, this);
  }

}
