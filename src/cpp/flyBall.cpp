//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: flyBall.cpp
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
#include "flyBall.h"
#include "rtwtypes.h"
#include "flyBall_private.h"

//
// This function updates continuous states using the ODE4 fixed-step
// solver algorithm
//
void flyBall::rt_ertODEUpdateContinuousStates(RTWSolverInfo *si )
{
  time_T t { rtsiGetT(si) };

  time_T tnew { rtsiGetSolverStopTime(si) };

  time_T h { rtsiGetStepSize(si) };

  real_T *x { rtsiGetContStates(si) };

  ODE4_IntgData *id { static_cast<ODE4_IntgData *>(rtsiGetSolverData(si)) };

  real_T *y { id->y };

  real_T *f0 { id->f[0] };

  real_T *f1 { id->f[1] };

  real_T *f2 { id->f[2] };

  real_T *f3 { id->f[3] };

  real_T temp;
  int_T i;
  int_T nXc { 2 };

  rtsiSetSimTimeStep(si,MINOR_TIME_STEP);

  // Save the state values at time t in y, we'll use x as ynew.
  (void) std::memcpy(y, x,
                     static_cast<uint_T>(nXc)*sizeof(real_T));

  // Assumes that rtsiSetT and ModelOutputs are up-to-date
  // f0 = f(t,y)
  rtsiSetdX(si, f0);
  flyBall_derivatives();

  // f1 = f(t + (h/2), y + (h/2)*f0)
  temp = 0.5 * h;
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (temp*f0[i]);
  }

  rtsiSetT(si, t + temp);
  rtsiSetdX(si, f1);
  this->step();
  flyBall_derivatives();

  // f2 = f(t + (h/2), y + (h/2)*f1)
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (temp*f1[i]);
  }

  rtsiSetdX(si, f2);
  this->step();
  flyBall_derivatives();

  // f3 = f(t + h, y + h*f2)
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (h*f2[i]);
  }

  rtsiSetT(si, tnew);
  rtsiSetdX(si, f3);
  this->step();
  flyBall_derivatives();

  // tnew = t + h
  // ynew = y + (h/6)*(f0 + 2*f1 + 2*f2 + 2*f3)
  temp = h / 6.0;
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + temp*(f0[i] + 2.0*f1[i] + 2.0*f2[i] + f3[i]);
  }

  rtsiSetSimTimeStep(si,MAJOR_TIME_STEP);
}

// Model step function
void flyBall::step()
{
  real_T rtb_Clock;
  real_T rtb_Gain;
  real_T rtb_Square1;
  real_T rtb_Square2;
  boolean_T OR;
  if (rtmIsMajorTimeStep((&flyBall_M))) {
    // set solver stop time
    rtsiSetSolverStopTime(&(&flyBall_M)->solverInfo,(((&flyBall_M)
      ->Timing.clockTick0+1)*(&flyBall_M)->Timing.stepSize0));
  }                                    // end MajorTimeStep

  // Update absolute time of base rate at minor time step
  if (rtmIsMinorTimeStep((&flyBall_M))) {
    (&flyBall_M)->Timing.t[0] = rtsiGetT(&(&flyBall_M)->solverInfo);
  }

  // Clock: '<Root>/Clock'
  rtb_Clock = (&flyBall_M)->Timing.t[0];

  // Logic: '<Root>/OR' incorporates:
  //   Constant: '<S1>/Constant'
  //   Constant: '<S2>/Constant'
  //   Integrator: '<Root>/y'
  //   RelationalOperator: '<S1>/Compare'
  //   RelationalOperator: '<S2>/Compare'

  OR = ((rtb_Clock >= 10.0) || (flyBall_X.y_CSTATE <= 0.0));
  if (rtmIsMajorTimeStep((&flyBall_M))) {
    // Stop: '<Root>/Stop Simulation'
    if (OR) {
      rtmSetStopRequested((&flyBall_M), 1);
    }

    // End of Stop: '<Root>/Stop Simulation'
  }

  // Gain: '<Root>/Gain2' incorporates:
  //   Integrator: '<Root>/y'

  flyBall_B.y = flyBall_X.y_CSTATE;

  // Integrator: '<Root>/vy'
  flyBall_B.vy_m = flyBall_X.vy_CSTATE;

  // Gain: '<Root>/Gain1'
  flyBall_B.vy = flyBall_B.vy_m;

  // Switch: '<S3>/Switch'
  if (OR) {
    // Sum: '<S3>/Add2' incorporates:
    //   Constant: '<S3>/Constant3'

    rtb_Gain = flyBall_B.vy + flyBall_P.target_vy;

    // Math: '<S3>/Square2'
    rtb_Square2 = rtb_Gain * rtb_Gain;

    // Gain: '<S3>/Gain1' incorporates:
    //   Constant: '<S3>/Constant2'
    //   Sum: '<S3>/Add1'

    rtb_Gain = (flyBall_B.y + flyBall_P.target_y) * 0.33333333333333331;

    // Math: '<S3>/Square1'
    rtb_Square1 = rtb_Gain * rtb_Gain;

    // Gain: '<S3>/Gain' incorporates:
    //   Constant: '<S3>/Constant1'
    //   Sum: '<S3>/Add'

    rtb_Gain = (rtb_Clock + flyBall_P.target_t) * 10.0;

    // Switch: '<S3>/Switch' incorporates:
    //   Constant: '<S3>/Constant4'
    //   Gain: '<S3>/Gain3'
    //   Math: '<S3>/Square'
    //   Sum: '<S3>/Add3'
    //   Sum: '<S3>/Add4'

    flyBall_B.reward = ((rtb_Gain * rtb_Gain + rtb_Square1) + rtb_Square2) *
      -0.01 + 5.0;
  } else {
    // Switch: '<S3>/Switch' incorporates:
    //   Constant: '<S3>/Constant'

    flyBall_B.reward = -0.001;
  }

  // End of Switch: '<S3>/Switch'
  if (rtmIsMajorTimeStep((&flyBall_M))) {
    // Sum: '<Root>/Add' incorporates:
    //   Constant: '<Root>/u'

    flyBall_B.Add = flyBall_P.control - 9.8;

    // Gain: '<Root>/Gain'
    flyBall_B.ay = flyBall_B.Add;
  }

  if (rtmIsMajorTimeStep((&flyBall_M))) {
    rt_ertODEUpdateContinuousStates(&(&flyBall_M)->solverInfo);

    // Update absolute time for base rate
    // The "clockTick0" counts the number of times the code of this task has
    //  been executed. The absolute time is the multiplication of "clockTick0"
    //  and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
    //  overflow during the application lifespan selected.

    ++(&flyBall_M)->Timing.clockTick0;
    (&flyBall_M)->Timing.t[0] = rtsiGetSolverStopTime(&(&flyBall_M)->solverInfo);

    {
      // Update absolute timer for sample time: [0.1s, 0.0s]
      // The "clockTick1" counts the number of times the code of this task has
      //  been executed. The resolution of this integer timer is 0.1, which is the step size
      //  of the task. Size of "clockTick1" ensures timer will not overflow during the
      //  application lifespan selected.

      (&flyBall_M)->Timing.clockTick1++;
    }
  }                                    // end MajorTimeStep
}

// Derivatives for root system: '<Root>'
void flyBall::flyBall_derivatives()
{
  flyBall::XDot_flyBall_T *_rtXdot;
  _rtXdot = ((XDot_flyBall_T *) (&flyBall_M)->derivs);

  // Derivatives for Integrator: '<Root>/y'
  _rtXdot->y_CSTATE = flyBall_B.vy_m;

  // Derivatives for Integrator: '<Root>/vy'
  _rtXdot->vy_CSTATE = flyBall_B.Add;
}

// Model initialize function
void flyBall::initialize()
{
  //初始化运行终止标志
  (void) std::memset((static_cast<void *>(&flyBall_M)), 0,
                     sizeof(RT_MODEL_flyBall_T));
  // Registration code
  {
    // Setup solver object
    rtsiSetSimTimeStepPtr(&(&flyBall_M)->solverInfo, &(&flyBall_M)
                          ->Timing.simTimeStep);
    rtsiSetTPtr(&(&flyBall_M)->solverInfo, &rtmGetTPtr((&flyBall_M)));
    rtsiSetStepSizePtr(&(&flyBall_M)->solverInfo, &(&flyBall_M)
                       ->Timing.stepSize0);
    rtsiSetdXPtr(&(&flyBall_M)->solverInfo, &(&flyBall_M)->derivs);
    rtsiSetContStatesPtr(&(&flyBall_M)->solverInfo, (real_T **) &(&flyBall_M)
                         ->contStates);
    rtsiSetNumContStatesPtr(&(&flyBall_M)->solverInfo, &(&flyBall_M)
      ->Sizes.numContStates);
    rtsiSetNumPeriodicContStatesPtr(&(&flyBall_M)->solverInfo, &(&flyBall_M)
      ->Sizes.numPeriodicContStates);
    rtsiSetPeriodicContStateIndicesPtr(&(&flyBall_M)->solverInfo, &(&flyBall_M
      )->periodicContStateIndices);
    rtsiSetPeriodicContStateRangesPtr(&(&flyBall_M)->solverInfo, &(&flyBall_M)
      ->periodicContStateRanges);
    rtsiSetContStateDisabledPtr(&(&flyBall_M)->solverInfo, (boolean_T**)
      &(&flyBall_M)->contStateDisabled);
    rtsiSetErrorStatusPtr(&(&flyBall_M)->solverInfo, (&rtmGetErrorStatus
      ((&flyBall_M))));
    rtsiSetRTModelPtr(&(&flyBall_M)->solverInfo, (&flyBall_M));
  }

  rtsiSetSimTimeStep(&(&flyBall_M)->solverInfo, MAJOR_TIME_STEP);
  (&flyBall_M)->intgData.y = (&flyBall_M)->odeY;
  (&flyBall_M)->intgData.f[0] = (&flyBall_M)->odeF[0];
  (&flyBall_M)->intgData.f[1] = (&flyBall_M)->odeF[1];
  (&flyBall_M)->intgData.f[2] = (&flyBall_M)->odeF[2];
  (&flyBall_M)->intgData.f[3] = (&flyBall_M)->odeF[3];
  (&flyBall_M)->contStates = ((X_flyBall_T *) &flyBall_X);
  (&flyBall_M)->contStateDisabled = ((XDis_flyBall_T *) &flyBall_XDis);
  (&flyBall_M)->Timing.tStart = (0.0);
  rtsiSetSolverData(&(&flyBall_M)->solverInfo, static_cast<void *>(&(&flyBall_M
    )->intgData));
  rtsiSetIsMinorTimeStepWithModeChange(&(&flyBall_M)->solverInfo, false);
  rtsiSetSolverName(&(&flyBall_M)->solverInfo,"ode4");
  rtmSetTPtr((&flyBall_M), &(&flyBall_M)->Timing.tArray[0]);
  (&flyBall_M)->Timing.stepSize0 = 0.1;

  // InitializeConditions for Integrator: '<Root>/y'
  flyBall_X.y_CSTATE = 100.0;

  // InitializeConditions for Integrator: '<Root>/vy'
  flyBall_X.vy_CSTATE = 0.0;

  flyBall_B.y = flyBall_X.y_CSTATE;

  // Integrator: '<Root>/vy'
  flyBall_B.vy_m = flyBall_X.vy_CSTATE;

  // Gain: '<Root>/Gain1'
  flyBall_B.vy = flyBall_B.vy_m;
  flyBall_B.reward = 0.0;
  flyBall_B.Add = - 9.8;
}

// Model terminate function
void flyBall::terminate()
{
  // (no terminate code required)
}


double flyBall::get_t()
{
  return flyBall_M.Timing.t[0];
}

double flyBall::get_y()
{
  return flyBall_B.y;
}

double flyBall::get_vy()
{
  return flyBall_B.vy;
}

double flyBall::get_ay()
{
  return flyBall_B.ay;
}

double flyBall::get_reward()
{
  return flyBall_B.reward;
}

double flyBall::get_target_y()
{
  return flyBall_P.target_y;
}

double flyBall::get_target_vy()
{
  return flyBall_P.target_vy;
}

double flyBall::get_target_t()
{
  return flyBall_P.target_t;
}

void flyBall::set_control(double control)
{
  flyBall_P.control = control;
}


// Constructor
flyBall::flyBall() :
  flyBall_B(),
  flyBall_X(),
  flyBall_XDis(),
  flyBall_M()
{
  // Currently there is no constructor body generated.
}

// Destructor
// Currently there is no destructor body generated.
flyBall::~flyBall() = default;

// Real-Time Model get method
flyBall::RT_MODEL_flyBall_T * flyBall::getRTM()
{
  return (&flyBall_M);
}

//
// File trailer for generated code.
//
// [EOF]
//
