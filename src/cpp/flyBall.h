//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: flyBall.h
//
// Code generated for Simulink model 'flyBall'.
//
// Model version                  : 1.7
// Simulink Coder version         : 23.2 (R2023b) 01-Aug-2023
// C/C++ source code generated on : Mon May 20 07:50:22 2024
//
// Target selection: ert.tlc
// Embedded hardware selection: Intel->x86-64 (Windows64)
// Code generation objectives: Unspecified
// Validation result: Not run
//
#ifndef RTW_HEADER_flyBall_h_
#define RTW_HEADER_flyBall_h_
#include "rtwtypes.h"
#include "rtw_continuous.h"
#include "rtw_solver.h"
#include "flyBall_types.h"
#include <cstring>

// Macros for accessing real-time model data structure
#ifndef rtmGetErrorStatus
#define rtmGetErrorStatus(rtm)         ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
#define rtmSetErrorStatus(rtm, val)    ((rtm)->errorStatus = (val))
#endif

#ifndef rtmGetStopRequested
#define rtmGetStopRequested(rtm)       ((rtm)->Timing.stopRequestedFlag)
#endif

#ifndef rtmSetStopRequested
#define rtmSetStopRequested(rtm, val)  ((rtm)->Timing.stopRequestedFlag = (val))
#endif

#ifndef rtmGetStopRequestedPtr
#define rtmGetStopRequestedPtr(rtm)    (&((rtm)->Timing.stopRequestedFlag))
#endif

#ifndef rtmGetT
#define rtmGetT(rtm)                   (rtmGetTPtr((rtm))[0])
#endif

#ifndef rtmGetTPtr
#define rtmGetTPtr(rtm)                ((rtm)->Timing.t)
#endif

#ifndef rtmGetTStart
#define rtmGetTStart(rtm)              ((rtm)->Timing.tStart)
#endif

#ifndef ODE4_INTG
#define ODE4_INTG

// ODE4 Integration Data
struct ODE4_IntgData {
  real_T *y;                           // output
  real_T *f[4];                        // derivatives
};

#endif

// Class declaration for model flyBall
class flyBall final
{
  // public data and function members
 public:
  // Block signals (default storage)
  struct B_flyBall_T {
    real_T y;                          // '<Root>/Gain2'
    real_T vy_m;                       // '<Root>/vy'
    real_T vy;                         // '<Root>/Gain1'
    real_T reward;                     // '<S3>/Switch'
    real_T Add;                        // '<Root>/Add'
    real_T ay;                         // '<Root>/Gain'
  };

  // Continuous states (default storage)
  struct X_flyBall_T {
    real_T y_CSTATE;                   // '<Root>/y'
    real_T vy_CSTATE;                  // '<Root>/vy'
  };

  // State derivatives (default storage)
  struct XDot_flyBall_T {
    real_T y_CSTATE;                   // '<Root>/y'
    real_T vy_CSTATE;                  // '<Root>/vy'
  };

  // State disabled
  struct XDis_flyBall_T {
    boolean_T y_CSTATE;                // '<Root>/y'
    boolean_T vy_CSTATE;               // '<Root>/vy'
  };

  // Parameters (default storage)
  struct P_flyBall_T {
    real_T control;                    // Variable: control
                                          //  Referenced by: '<Root>/u'

    real_T target_t;                   // Variable: target_t
                                          //  Referenced by: '<S3>/Constant1'

    real_T target_vy;                  // Variable: target_vy
                                          //  Referenced by: '<S3>/Constant3'

    real_T target_y;                   // Variable: target_y
                                          //  Referenced by: '<S3>/Constant2'

  };

  // Real-time Model Data Structure
  struct RT_MODEL_flyBall_T {
    const char_T *errorStatus;
    RTWSolverInfo solverInfo;
    X_flyBall_T *contStates;
    int_T *periodicContStateIndices;
    real_T *periodicContStateRanges;
    real_T *derivs;
    XDis_flyBall_T *contStateDisabled;
    boolean_T zCCacheNeedsReset;
    boolean_T derivCacheNeedsReset;
    boolean_T CTOutputIncnstWithState;
    real_T odeY[2];
    real_T odeF[4][2];
    ODE4_IntgData intgData;

    //
    //  Sizes:
    //  The following substructure contains sizes information
    //  for many of the model attributes such as inputs, outputs,
    //  dwork, sample times, etc.

    struct {
      int_T numContStates;
      int_T numPeriodicContStates;
      int_T numSampTimes;
    } Sizes;

    //
    //  Timing:
    //  The following substructure contains information regarding
    //  the timing information for the model.

    struct {
      uint32_T clockTick0;
      time_T stepSize0;
      uint32_T clockTick1;
      time_T tStart;
      SimTimeStep simTimeStep;
      boolean_T stopRequestedFlag;
      time_T *t;
      time_T tArray[2];
    } Timing;
  };

  // Copy Constructor
  flyBall(flyBall const&) = delete;

  // Assignment Operator
  flyBall& operator= (flyBall const&) & = delete;

  // Move Constructor
  flyBall(flyBall &&) = delete;

  // Move Assignment Operator
  flyBall& operator= (flyBall &&) = delete;

  // Real-Time Model get method
  flyBall::RT_MODEL_flyBall_T * getRTM();

  // model initialize function
  void initialize();

  // model step function
  void step();

  // get access to the private members y, vy, ay, reward, target_y, target_vy, target_t
  double get_t();
  double get_y();
  double get_vy();
  double get_ay();
  double get_reward();
  double get_target_y();
  double get_target_vy();
  double get_target_t();

  // set control
  void set_control(double control);

  // model terminate function
  static void terminate();

  // Constructor
  flyBall();

  // Destructor
  ~flyBall();

  // private data and function members
 private:
  // Block signals
  B_flyBall_T flyBall_B;

  // Tunable parameters
  static P_flyBall_T flyBall_P;

  // Block continuous states
  X_flyBall_T flyBall_X;

  // Block Continuous state disabled vector
  XDis_flyBall_T flyBall_XDis;

  // Continuous states update member function
  void rt_ertODEUpdateContinuousStates(RTWSolverInfo *si );

  // Derivatives member function
  void flyBall_derivatives();

  // Real-Time Model
  RT_MODEL_flyBall_T flyBall_M;
};

//-
//  These blocks were eliminated from the model due to optimizations:
//
//  Block '<S3>/Gain2' : Eliminated nontunable gain of 1


//-
//  The generated code includes comments that allow you to trace directly
//  back to the appropriate location in the model.  The basic format
//  is <system>/block_name, where system is the system number (uniquely
//  assigned by Simulink) and block_name is the name of the block.
//
//  Use the MATLAB hilite_system command to trace the generated code back
//  to the model.  For example,
//
//  hilite_system('<S3>')    - opens system 3
//  hilite_system('<S3>/Kp') - opens and selects block Kp which resides in S3
//
//  Here is the system hierarchy for this model
//
//  '<Root>' : 'flyBall'
//  '<S1>'   : 'flyBall/Compare To Constant'
//  '<S2>'   : 'flyBall/Compare To Constant1'
//  '<S3>'   : 'flyBall/reward'

#endif                                 // RTW_HEADER_flyBall_h_

//
// File trailer for generated code.
//
// [EOF]
//
