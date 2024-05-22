//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: ert_main.cpp
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
// #include <stdio.h>              // This example main program uses printf/fflush
#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>
#include "flyBall.h"                   // Model header file

namespace py = pybind11;

static flyBall flyBall_Obj;            // Instance of model class

// 归一化函数
double normalize(double x, double x_min, double x_max){
  return (x - x_min) / (x_max - x_min);
}

//
// Associating rt_OneStep with a real-time clock or interrupt service routine
// is what makes the generated code "real-time".  The function rt_OneStep is
// always associated with the base rate of the model.  Subrates are managed
// by the base rate from inside the generated code.  Enabling/disabling
// interrupts and floating point context switches are target specific.  This
// example code indicates where these should take place relative to executing
// the generated code step function.  Overrun behavior should be tailored to
// your application needs.  This example simply sets an error status in the
// real-time model and returns from rt_OneStep.
//
void rt_OneStep(void);
void rt_OneStep(void)
{
  static boolean_T OverrunFlag{ false };

  // Disable interrupts here

  // Check for overrun
  if (OverrunFlag) {
    rtmSetErrorStatus(flyBall_Obj.getRTM(), "Overrun");
    return;
  }

  OverrunFlag = true;

  // Save FPU context here (if necessary)
  // Re-enable timer or interrupt here
  // Set model inputs here

  // Step the model
  flyBall_Obj.step();

  // Get model outputs here

  // Indicate task complete
  OverrunFlag = false;

  // Disable interrupts here
  // Restore FPU context here (if necessary)
  // Enable interrupts here
}

//
// The example main function illustrates what is required by your
// application code to initialize, execute, and terminate the generated code.
// Attaching rt_OneStep to a real-time clock is target specific. This example
// illustrates how you do this relative to initializing the model.
//
int_T main(int_T argc, const char *argv[])
{
  // Unused arguments
  (void)(argc);
  (void)(argv);

  // Initialize model
  flyBall_Obj.initialize();

  // Simulating the model step behavior (in non real-time) to
  //   simulate model behavior at stop time.

// done = ((rtmGetErrorStatus(flyBall_Obj.getRTM()) != (nullptr)) ||
//         rtmGetStopRequested(flyBall_Obj.getRTM()))
  while ((rtmGetErrorStatus(flyBall_Obj.getRTM()) == (nullptr)) &&
         !rtmGetStopRequested(flyBall_Obj.getRTM())) {
    rt_OneStep();
  }

  // Terminate model
  flyBall_Obj.terminate();
  return 0;
}

//
// File trailer for generated code.
//
// [EOF]
//


void reset(){
  flyBall_Obj.initialize();
}

void step(double control){
  flyBall_Obj.set_control(control);
  rt_OneStep();
}

// 获取真实状态量state=[t, y, vy, ay, target_t, target_y, target_vy]
py::array_t<double> get_real_state(){
  double state[7];
  state[0] = flyBall_Obj.get_t();
  state[1] = flyBall_Obj.get_y();
  state[2] = flyBall_Obj.get_vy();
  state[3] = flyBall_Obj.get_ay();
  state[4] = flyBall_Obj.get_target_t();
  state[5] = flyBall_Obj.get_target_y();
  state[6] = flyBall_Obj.get_target_vy();
  return py::array_t<double>(7, state);
}

// 获取归一化后的状态量state=[t, y, vy, ay, target_t, target_y, target_vy]
py::array_t<double> state(){
  double state[7];
  state[0] = normalize(flyBall_Obj.get_t(), 0, 10);
  state[1] = normalize(flyBall_Obj.get_y(), 0, 100);
  state[2] = normalize(flyBall_Obj.get_vy(), -50, 0);
  state[3] = normalize(flyBall_Obj.get_ay(), -20, 2);
  state[4] = normalize(flyBall_Obj.get_target_t(), 0, 10);
  state[5] = normalize(flyBall_Obj.get_target_y(), 0, 100);
  state[6] = normalize(flyBall_Obj.get_target_vy(), -50, 0);
  return py::array_t<double>(7, state);
}

// 获取reward
double reward(){
  return flyBall_Obj.get_reward();
}

// 获取是否结束
bool done(){
  return ((rtmGetErrorStatus(flyBall_Obj.getRTM()) != (nullptr)) ||
       rtmGetStopRequested(flyBall_Obj.getRTM()));
}

// 设置控制量
void set_control(double control){
  flyBall_Obj.set_control(control);
}

PYBIND11_MODULE(flyBall, m) {
  m.def("reset", &reset);
  m.def("step", &step);
  m.def("get_real_state", &get_real_state);
  m.def("state", &state);
  m.def("reward", &reward);
  m.def("done", &done);
  m.def("set_control", &set_control);
}
