#include "car.h"

namespace {
#define DIM 9
#define EDIM 9
#define MEDIM 9
typedef void (*Hfun)(double *, double *, double *);

double mass;

void set_mass(double x){ mass = x;}

double rotational_inertia;

void set_rotational_inertia(double x){ rotational_inertia = x;}

double center_to_front;

void set_center_to_front(double x){ center_to_front = x;}

double center_to_rear;

void set_center_to_rear(double x){ center_to_rear = x;}

double stiffness_front;

void set_stiffness_front(double x){ stiffness_front = x;}

double stiffness_rear;

void set_stiffness_rear(double x){ stiffness_rear = x;}
const static double MAHA_THRESH_25 = 3.8414588206941227;
const static double MAHA_THRESH_24 = 5.991464547107981;
const static double MAHA_THRESH_30 = 3.8414588206941227;
const static double MAHA_THRESH_26 = 3.8414588206941227;
const static double MAHA_THRESH_27 = 3.8414588206941227;
const static double MAHA_THRESH_29 = 3.8414588206941227;
const static double MAHA_THRESH_28 = 3.8414588206941227;
const static double MAHA_THRESH_31 = 3.8414588206941227;

/******************************************************************************
 *                       Code generated with SymPy 1.12                       *
 *                                                                            *
 *              See http://www.sympy.org/ for more information.               *
 *                                                                            *
 *                         This file is part of 'ekf'                         *
 ******************************************************************************/
void err_fun(double *nom_x, double *delta_x, double *out_1160912902492293220) {
   out_1160912902492293220[0] = delta_x[0] + nom_x[0];
   out_1160912902492293220[1] = delta_x[1] + nom_x[1];
   out_1160912902492293220[2] = delta_x[2] + nom_x[2];
   out_1160912902492293220[3] = delta_x[3] + nom_x[3];
   out_1160912902492293220[4] = delta_x[4] + nom_x[4];
   out_1160912902492293220[5] = delta_x[5] + nom_x[5];
   out_1160912902492293220[6] = delta_x[6] + nom_x[6];
   out_1160912902492293220[7] = delta_x[7] + nom_x[7];
   out_1160912902492293220[8] = delta_x[8] + nom_x[8];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_3114711529215166268) {
   out_3114711529215166268[0] = -nom_x[0] + true_x[0];
   out_3114711529215166268[1] = -nom_x[1] + true_x[1];
   out_3114711529215166268[2] = -nom_x[2] + true_x[2];
   out_3114711529215166268[3] = -nom_x[3] + true_x[3];
   out_3114711529215166268[4] = -nom_x[4] + true_x[4];
   out_3114711529215166268[5] = -nom_x[5] + true_x[5];
   out_3114711529215166268[6] = -nom_x[6] + true_x[6];
   out_3114711529215166268[7] = -nom_x[7] + true_x[7];
   out_3114711529215166268[8] = -nom_x[8] + true_x[8];
}
void H_mod_fun(double *state, double *out_2799184021601232983) {
   out_2799184021601232983[0] = 1.0;
   out_2799184021601232983[1] = 0;
   out_2799184021601232983[2] = 0;
   out_2799184021601232983[3] = 0;
   out_2799184021601232983[4] = 0;
   out_2799184021601232983[5] = 0;
   out_2799184021601232983[6] = 0;
   out_2799184021601232983[7] = 0;
   out_2799184021601232983[8] = 0;
   out_2799184021601232983[9] = 0;
   out_2799184021601232983[10] = 1.0;
   out_2799184021601232983[11] = 0;
   out_2799184021601232983[12] = 0;
   out_2799184021601232983[13] = 0;
   out_2799184021601232983[14] = 0;
   out_2799184021601232983[15] = 0;
   out_2799184021601232983[16] = 0;
   out_2799184021601232983[17] = 0;
   out_2799184021601232983[18] = 0;
   out_2799184021601232983[19] = 0;
   out_2799184021601232983[20] = 1.0;
   out_2799184021601232983[21] = 0;
   out_2799184021601232983[22] = 0;
   out_2799184021601232983[23] = 0;
   out_2799184021601232983[24] = 0;
   out_2799184021601232983[25] = 0;
   out_2799184021601232983[26] = 0;
   out_2799184021601232983[27] = 0;
   out_2799184021601232983[28] = 0;
   out_2799184021601232983[29] = 0;
   out_2799184021601232983[30] = 1.0;
   out_2799184021601232983[31] = 0;
   out_2799184021601232983[32] = 0;
   out_2799184021601232983[33] = 0;
   out_2799184021601232983[34] = 0;
   out_2799184021601232983[35] = 0;
   out_2799184021601232983[36] = 0;
   out_2799184021601232983[37] = 0;
   out_2799184021601232983[38] = 0;
   out_2799184021601232983[39] = 0;
   out_2799184021601232983[40] = 1.0;
   out_2799184021601232983[41] = 0;
   out_2799184021601232983[42] = 0;
   out_2799184021601232983[43] = 0;
   out_2799184021601232983[44] = 0;
   out_2799184021601232983[45] = 0;
   out_2799184021601232983[46] = 0;
   out_2799184021601232983[47] = 0;
   out_2799184021601232983[48] = 0;
   out_2799184021601232983[49] = 0;
   out_2799184021601232983[50] = 1.0;
   out_2799184021601232983[51] = 0;
   out_2799184021601232983[52] = 0;
   out_2799184021601232983[53] = 0;
   out_2799184021601232983[54] = 0;
   out_2799184021601232983[55] = 0;
   out_2799184021601232983[56] = 0;
   out_2799184021601232983[57] = 0;
   out_2799184021601232983[58] = 0;
   out_2799184021601232983[59] = 0;
   out_2799184021601232983[60] = 1.0;
   out_2799184021601232983[61] = 0;
   out_2799184021601232983[62] = 0;
   out_2799184021601232983[63] = 0;
   out_2799184021601232983[64] = 0;
   out_2799184021601232983[65] = 0;
   out_2799184021601232983[66] = 0;
   out_2799184021601232983[67] = 0;
   out_2799184021601232983[68] = 0;
   out_2799184021601232983[69] = 0;
   out_2799184021601232983[70] = 1.0;
   out_2799184021601232983[71] = 0;
   out_2799184021601232983[72] = 0;
   out_2799184021601232983[73] = 0;
   out_2799184021601232983[74] = 0;
   out_2799184021601232983[75] = 0;
   out_2799184021601232983[76] = 0;
   out_2799184021601232983[77] = 0;
   out_2799184021601232983[78] = 0;
   out_2799184021601232983[79] = 0;
   out_2799184021601232983[80] = 1.0;
}
void f_fun(double *state, double dt, double *out_8047485781251068468) {
   out_8047485781251068468[0] = state[0];
   out_8047485781251068468[1] = state[1];
   out_8047485781251068468[2] = state[2];
   out_8047485781251068468[3] = state[3];
   out_8047485781251068468[4] = state[4];
   out_8047485781251068468[5] = dt*((-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]))*state[6] - 9.8000000000000007*state[8] + stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*state[1]) + (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*state[4])) + state[5];
   out_8047485781251068468[6] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*state[4])) + state[6];
   out_8047485781251068468[7] = state[7];
   out_8047485781251068468[8] = state[8];
}
void F_fun(double *state, double dt, double *out_8124325998508320210) {
   out_8124325998508320210[0] = 1;
   out_8124325998508320210[1] = 0;
   out_8124325998508320210[2] = 0;
   out_8124325998508320210[3] = 0;
   out_8124325998508320210[4] = 0;
   out_8124325998508320210[5] = 0;
   out_8124325998508320210[6] = 0;
   out_8124325998508320210[7] = 0;
   out_8124325998508320210[8] = 0;
   out_8124325998508320210[9] = 0;
   out_8124325998508320210[10] = 1;
   out_8124325998508320210[11] = 0;
   out_8124325998508320210[12] = 0;
   out_8124325998508320210[13] = 0;
   out_8124325998508320210[14] = 0;
   out_8124325998508320210[15] = 0;
   out_8124325998508320210[16] = 0;
   out_8124325998508320210[17] = 0;
   out_8124325998508320210[18] = 0;
   out_8124325998508320210[19] = 0;
   out_8124325998508320210[20] = 1;
   out_8124325998508320210[21] = 0;
   out_8124325998508320210[22] = 0;
   out_8124325998508320210[23] = 0;
   out_8124325998508320210[24] = 0;
   out_8124325998508320210[25] = 0;
   out_8124325998508320210[26] = 0;
   out_8124325998508320210[27] = 0;
   out_8124325998508320210[28] = 0;
   out_8124325998508320210[29] = 0;
   out_8124325998508320210[30] = 1;
   out_8124325998508320210[31] = 0;
   out_8124325998508320210[32] = 0;
   out_8124325998508320210[33] = 0;
   out_8124325998508320210[34] = 0;
   out_8124325998508320210[35] = 0;
   out_8124325998508320210[36] = 0;
   out_8124325998508320210[37] = 0;
   out_8124325998508320210[38] = 0;
   out_8124325998508320210[39] = 0;
   out_8124325998508320210[40] = 1;
   out_8124325998508320210[41] = 0;
   out_8124325998508320210[42] = 0;
   out_8124325998508320210[43] = 0;
   out_8124325998508320210[44] = 0;
   out_8124325998508320210[45] = dt*(stiffness_front*(-state[2] - state[3] + state[7])/(mass*state[1]) + (-stiffness_front - stiffness_rear)*state[5]/(mass*state[4]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[6]/(mass*state[4]));
   out_8124325998508320210[46] = -dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*pow(state[1], 2));
   out_8124325998508320210[47] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_8124325998508320210[48] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_8124325998508320210[49] = dt*((-1 - (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*pow(state[4], 2)))*state[6] - (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*pow(state[4], 2)));
   out_8124325998508320210[50] = dt*(-stiffness_front*state[0] - stiffness_rear*state[0])/(mass*state[4]) + 1;
   out_8124325998508320210[51] = dt*(-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]));
   out_8124325998508320210[52] = dt*stiffness_front*state[0]/(mass*state[1]);
   out_8124325998508320210[53] = -9.8000000000000007*dt;
   out_8124325998508320210[54] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front - pow(center_to_rear, 2)*stiffness_rear)*state[6]/(rotational_inertia*state[4]));
   out_8124325998508320210[55] = -center_to_front*dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*pow(state[1], 2));
   out_8124325998508320210[56] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_8124325998508320210[57] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_8124325998508320210[58] = dt*(-(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*pow(state[4], 2)) - (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*pow(state[4], 2)));
   out_8124325998508320210[59] = dt*(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(rotational_inertia*state[4]);
   out_8124325998508320210[60] = dt*(-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])/(rotational_inertia*state[4]) + 1;
   out_8124325998508320210[61] = center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_8124325998508320210[62] = 0;
   out_8124325998508320210[63] = 0;
   out_8124325998508320210[64] = 0;
   out_8124325998508320210[65] = 0;
   out_8124325998508320210[66] = 0;
   out_8124325998508320210[67] = 0;
   out_8124325998508320210[68] = 0;
   out_8124325998508320210[69] = 0;
   out_8124325998508320210[70] = 1;
   out_8124325998508320210[71] = 0;
   out_8124325998508320210[72] = 0;
   out_8124325998508320210[73] = 0;
   out_8124325998508320210[74] = 0;
   out_8124325998508320210[75] = 0;
   out_8124325998508320210[76] = 0;
   out_8124325998508320210[77] = 0;
   out_8124325998508320210[78] = 0;
   out_8124325998508320210[79] = 0;
   out_8124325998508320210[80] = 1;
}
void h_25(double *state, double *unused, double *out_394435484822648660) {
   out_394435484822648660[0] = state[6];
}
void H_25(double *state, double *unused, double *out_8110192764782635771) {
   out_8110192764782635771[0] = 0;
   out_8110192764782635771[1] = 0;
   out_8110192764782635771[2] = 0;
   out_8110192764782635771[3] = 0;
   out_8110192764782635771[4] = 0;
   out_8110192764782635771[5] = 0;
   out_8110192764782635771[6] = 1;
   out_8110192764782635771[7] = 0;
   out_8110192764782635771[8] = 0;
}
void h_24(double *state, double *unused, double *out_6938048359663727949) {
   out_6938048359663727949[0] = state[4];
   out_6938048359663727949[1] = state[5];
}
void H_24(double *state, double *unused, double *out_6778625710124592709) {
   out_6778625710124592709[0] = 0;
   out_6778625710124592709[1] = 0;
   out_6778625710124592709[2] = 0;
   out_6778625710124592709[3] = 0;
   out_6778625710124592709[4] = 1;
   out_6778625710124592709[5] = 0;
   out_6778625710124592709[6] = 0;
   out_6778625710124592709[7] = 0;
   out_6778625710124592709[8] = 0;
   out_6778625710124592709[9] = 0;
   out_6778625710124592709[10] = 0;
   out_6778625710124592709[11] = 0;
   out_6778625710124592709[12] = 0;
   out_6778625710124592709[13] = 0;
   out_6778625710124592709[14] = 1;
   out_6778625710124592709[15] = 0;
   out_6778625710124592709[16] = 0;
   out_6778625710124592709[17] = 0;
}
void h_30(double *state, double *unused, double *out_551622153173777805) {
   out_551622153173777805[0] = state[4];
}
void H_30(double *state, double *unused, double *out_7818218350419667218) {
   out_7818218350419667218[0] = 0;
   out_7818218350419667218[1] = 0;
   out_7818218350419667218[2] = 0;
   out_7818218350419667218[3] = 0;
   out_7818218350419667218[4] = 1;
   out_7818218350419667218[5] = 0;
   out_7818218350419667218[6] = 0;
   out_7818218350419667218[7] = 0;
   out_7818218350419667218[8] = 0;
}
void h_26(double *state, double *unused, double *out_4790245082712252758) {
   out_4790245082712252758[0] = state[7];
}
void H_26(double *state, double *unused, double *out_4368689445908579547) {
   out_4368689445908579547[0] = 0;
   out_4368689445908579547[1] = 0;
   out_4368689445908579547[2] = 0;
   out_4368689445908579547[3] = 0;
   out_4368689445908579547[4] = 0;
   out_4368689445908579547[5] = 0;
   out_4368689445908579547[6] = 0;
   out_4368689445908579547[7] = 1;
   out_4368689445908579547[8] = 0;
}
void h_27(double *state, double *unused, double *out_3431221536266981345) {
   out_3431221536266981345[0] = state[3];
}
void H_27(double *state, double *unused, double *out_5594624279235724001) {
   out_5594624279235724001[0] = 0;
   out_5594624279235724001[1] = 0;
   out_5594624279235724001[2] = 0;
   out_5594624279235724001[3] = 1;
   out_5594624279235724001[4] = 0;
   out_5594624279235724001[5] = 0;
   out_5594624279235724001[6] = 0;
   out_5594624279235724001[7] = 0;
   out_5594624279235724001[8] = 0;
}
void h_29(double *state, double *unused, double *out_8244687311092219335) {
   out_8244687311092219335[0] = state[1];
}
void H_29(double *state, double *unused, double *out_7307987006105275034) {
   out_7307987006105275034[0] = 0;
   out_7307987006105275034[1] = 1;
   out_7307987006105275034[2] = 0;
   out_7307987006105275034[3] = 0;
   out_7307987006105275034[4] = 0;
   out_7307987006105275034[5] = 0;
   out_7307987006105275034[6] = 0;
   out_7307987006105275034[7] = 0;
   out_7307987006105275034[8] = 0;
}
void h_28(double *state, double *unused, double *out_1570451731393864300) {
   out_1570451731393864300[0] = state[0];
}
void H_28(double *state, double *unused, double *out_6056358050534746008) {
   out_6056358050534746008[0] = 1;
   out_6056358050534746008[1] = 0;
   out_6056358050534746008[2] = 0;
   out_6056358050534746008[3] = 0;
   out_6056358050534746008[4] = 0;
   out_6056358050534746008[5] = 0;
   out_6056358050534746008[6] = 0;
   out_6056358050534746008[7] = 0;
   out_6056358050534746008[8] = 0;
}
void h_31(double *state, double *unused, double *out_6982263411298943823) {
   out_6982263411298943823[0] = state[8];
}
void H_31(double *state, double *unused, double *out_8140838726659596199) {
   out_8140838726659596199[0] = 0;
   out_8140838726659596199[1] = 0;
   out_8140838726659596199[2] = 0;
   out_8140838726659596199[3] = 0;
   out_8140838726659596199[4] = 0;
   out_8140838726659596199[5] = 0;
   out_8140838726659596199[6] = 0;
   out_8140838726659596199[7] = 0;
   out_8140838726659596199[8] = 1;
}
#include <eigen3/Eigen/Dense>
#include <iostream>

typedef Eigen::Matrix<double, DIM, DIM, Eigen::RowMajor> DDM;
typedef Eigen::Matrix<double, EDIM, EDIM, Eigen::RowMajor> EEM;
typedef Eigen::Matrix<double, DIM, EDIM, Eigen::RowMajor> DEM;

void predict(double *in_x, double *in_P, double *in_Q, double dt) {
  typedef Eigen::Matrix<double, MEDIM, MEDIM, Eigen::RowMajor> RRM;

  double nx[DIM] = {0};
  double in_F[EDIM*EDIM] = {0};

  // functions from sympy
  f_fun(in_x, dt, nx);
  F_fun(in_x, dt, in_F);


  EEM F(in_F);
  EEM P(in_P);
  EEM Q(in_Q);

  RRM F_main = F.topLeftCorner(MEDIM, MEDIM);
  P.topLeftCorner(MEDIM, MEDIM) = (F_main * P.topLeftCorner(MEDIM, MEDIM)) * F_main.transpose();
  P.topRightCorner(MEDIM, EDIM - MEDIM) = F_main * P.topRightCorner(MEDIM, EDIM - MEDIM);
  P.bottomLeftCorner(EDIM - MEDIM, MEDIM) = P.bottomLeftCorner(EDIM - MEDIM, MEDIM) * F_main.transpose();

  P = P + dt*Q;

  // copy out state
  memcpy(in_x, nx, DIM * sizeof(double));
  memcpy(in_P, P.data(), EDIM * EDIM * sizeof(double));
}

// note: extra_args dim only correct when null space projecting
// otherwise 1
template <int ZDIM, int EADIM, bool MAHA_TEST>
void update(double *in_x, double *in_P, Hfun h_fun, Hfun H_fun, Hfun Hea_fun, double *in_z, double *in_R, double *in_ea, double MAHA_THRESHOLD) {
  typedef Eigen::Matrix<double, ZDIM, ZDIM, Eigen::RowMajor> ZZM;
  typedef Eigen::Matrix<double, ZDIM, DIM, Eigen::RowMajor> ZDM;
  typedef Eigen::Matrix<double, Eigen::Dynamic, EDIM, Eigen::RowMajor> XEM;
  //typedef Eigen::Matrix<double, EDIM, ZDIM, Eigen::RowMajor> EZM;
  typedef Eigen::Matrix<double, Eigen::Dynamic, 1> X1M;
  typedef Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor> XXM;

  double in_hx[ZDIM] = {0};
  double in_H[ZDIM * DIM] = {0};
  double in_H_mod[EDIM * DIM] = {0};
  double delta_x[EDIM] = {0};
  double x_new[DIM] = {0};


  // state x, P
  Eigen::Matrix<double, ZDIM, 1> z(in_z);
  EEM P(in_P);
  ZZM pre_R(in_R);

  // functions from sympy
  h_fun(in_x, in_ea, in_hx);
  H_fun(in_x, in_ea, in_H);
  ZDM pre_H(in_H);

  // get y (y = z - hx)
  Eigen::Matrix<double, ZDIM, 1> pre_y(in_hx); pre_y = z - pre_y;
  X1M y; XXM H; XXM R;
  if (Hea_fun){
    typedef Eigen::Matrix<double, ZDIM, EADIM, Eigen::RowMajor> ZAM;
    double in_Hea[ZDIM * EADIM] = {0};
    Hea_fun(in_x, in_ea, in_Hea);
    ZAM Hea(in_Hea);
    XXM A = Hea.transpose().fullPivLu().kernel();


    y = A.transpose() * pre_y;
    H = A.transpose() * pre_H;
    R = A.transpose() * pre_R * A;
  } else {
    y = pre_y;
    H = pre_H;
    R = pre_R;
  }
  // get modified H
  H_mod_fun(in_x, in_H_mod);
  DEM H_mod(in_H_mod);
  XEM H_err = H * H_mod;

  // Do mahalobis distance test
  if (MAHA_TEST){
    XXM a = (H_err * P * H_err.transpose() + R).inverse();
    double maha_dist = y.transpose() * a * y;
    if (maha_dist > MAHA_THRESHOLD){
      R = 1.0e16 * R;
    }
  }

  // Outlier resilient weighting
  double weight = 1;//(1.5)/(1 + y.squaredNorm()/R.sum());

  // kalman gains and I_KH
  XXM S = ((H_err * P) * H_err.transpose()) + R/weight;
  XEM KT = S.fullPivLu().solve(H_err * P.transpose());
  //EZM K = KT.transpose(); TODO: WHY DOES THIS NOT COMPILE?
  //EZM K = S.fullPivLu().solve(H_err * P.transpose()).transpose();
  //std::cout << "Here is the matrix rot:\n" << K << std::endl;
  EEM I_KH = Eigen::Matrix<double, EDIM, EDIM>::Identity() - (KT.transpose() * H_err);

  // update state by injecting dx
  Eigen::Matrix<double, EDIM, 1> dx(delta_x);
  dx  = (KT.transpose() * y);
  memcpy(delta_x, dx.data(), EDIM * sizeof(double));
  err_fun(in_x, delta_x, x_new);
  Eigen::Matrix<double, DIM, 1> x(x_new);

  // update cov
  P = ((I_KH * P) * I_KH.transpose()) + ((KT.transpose() * R) * KT);

  // copy out state
  memcpy(in_x, x.data(), DIM * sizeof(double));
  memcpy(in_P, P.data(), EDIM * EDIM * sizeof(double));
  memcpy(in_z, y.data(), y.rows() * sizeof(double));
}




}
extern "C" {

void car_update_25(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_25, H_25, NULL, in_z, in_R, in_ea, MAHA_THRESH_25);
}
void car_update_24(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<2, 3, 0>(in_x, in_P, h_24, H_24, NULL, in_z, in_R, in_ea, MAHA_THRESH_24);
}
void car_update_30(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_30, H_30, NULL, in_z, in_R, in_ea, MAHA_THRESH_30);
}
void car_update_26(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_26, H_26, NULL, in_z, in_R, in_ea, MAHA_THRESH_26);
}
void car_update_27(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_27, H_27, NULL, in_z, in_R, in_ea, MAHA_THRESH_27);
}
void car_update_29(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_29, H_29, NULL, in_z, in_R, in_ea, MAHA_THRESH_29);
}
void car_update_28(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_28, H_28, NULL, in_z, in_R, in_ea, MAHA_THRESH_28);
}
void car_update_31(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_31, H_31, NULL, in_z, in_R, in_ea, MAHA_THRESH_31);
}
void car_err_fun(double *nom_x, double *delta_x, double *out_1160912902492293220) {
  err_fun(nom_x, delta_x, out_1160912902492293220);
}
void car_inv_err_fun(double *nom_x, double *true_x, double *out_3114711529215166268) {
  inv_err_fun(nom_x, true_x, out_3114711529215166268);
}
void car_H_mod_fun(double *state, double *out_2799184021601232983) {
  H_mod_fun(state, out_2799184021601232983);
}
void car_f_fun(double *state, double dt, double *out_8047485781251068468) {
  f_fun(state,  dt, out_8047485781251068468);
}
void car_F_fun(double *state, double dt, double *out_8124325998508320210) {
  F_fun(state,  dt, out_8124325998508320210);
}
void car_h_25(double *state, double *unused, double *out_394435484822648660) {
  h_25(state, unused, out_394435484822648660);
}
void car_H_25(double *state, double *unused, double *out_8110192764782635771) {
  H_25(state, unused, out_8110192764782635771);
}
void car_h_24(double *state, double *unused, double *out_6938048359663727949) {
  h_24(state, unused, out_6938048359663727949);
}
void car_H_24(double *state, double *unused, double *out_6778625710124592709) {
  H_24(state, unused, out_6778625710124592709);
}
void car_h_30(double *state, double *unused, double *out_551622153173777805) {
  h_30(state, unused, out_551622153173777805);
}
void car_H_30(double *state, double *unused, double *out_7818218350419667218) {
  H_30(state, unused, out_7818218350419667218);
}
void car_h_26(double *state, double *unused, double *out_4790245082712252758) {
  h_26(state, unused, out_4790245082712252758);
}
void car_H_26(double *state, double *unused, double *out_4368689445908579547) {
  H_26(state, unused, out_4368689445908579547);
}
void car_h_27(double *state, double *unused, double *out_3431221536266981345) {
  h_27(state, unused, out_3431221536266981345);
}
void car_H_27(double *state, double *unused, double *out_5594624279235724001) {
  H_27(state, unused, out_5594624279235724001);
}
void car_h_29(double *state, double *unused, double *out_8244687311092219335) {
  h_29(state, unused, out_8244687311092219335);
}
void car_H_29(double *state, double *unused, double *out_7307987006105275034) {
  H_29(state, unused, out_7307987006105275034);
}
void car_h_28(double *state, double *unused, double *out_1570451731393864300) {
  h_28(state, unused, out_1570451731393864300);
}
void car_H_28(double *state, double *unused, double *out_6056358050534746008) {
  H_28(state, unused, out_6056358050534746008);
}
void car_h_31(double *state, double *unused, double *out_6982263411298943823) {
  h_31(state, unused, out_6982263411298943823);
}
void car_H_31(double *state, double *unused, double *out_8140838726659596199) {
  H_31(state, unused, out_8140838726659596199);
}
void car_predict(double *in_x, double *in_P, double *in_Q, double dt) {
  predict(in_x, in_P, in_Q, dt);
}
void car_set_mass(double x) {
  set_mass(x);
}
void car_set_rotational_inertia(double x) {
  set_rotational_inertia(x);
}
void car_set_center_to_front(double x) {
  set_center_to_front(x);
}
void car_set_center_to_rear(double x) {
  set_center_to_rear(x);
}
void car_set_stiffness_front(double x) {
  set_stiffness_front(x);
}
void car_set_stiffness_rear(double x) {
  set_stiffness_rear(x);
}
}

const EKF car = {
  .name = "car",
  .kinds = { 25, 24, 30, 26, 27, 29, 28, 31 },
  .feature_kinds = {  },
  .f_fun = car_f_fun,
  .F_fun = car_F_fun,
  .err_fun = car_err_fun,
  .inv_err_fun = car_inv_err_fun,
  .H_mod_fun = car_H_mod_fun,
  .predict = car_predict,
  .hs = {
    { 25, car_h_25 },
    { 24, car_h_24 },
    { 30, car_h_30 },
    { 26, car_h_26 },
    { 27, car_h_27 },
    { 29, car_h_29 },
    { 28, car_h_28 },
    { 31, car_h_31 },
  },
  .Hs = {
    { 25, car_H_25 },
    { 24, car_H_24 },
    { 30, car_H_30 },
    { 26, car_H_26 },
    { 27, car_H_27 },
    { 29, car_H_29 },
    { 28, car_H_28 },
    { 31, car_H_31 },
  },
  .updates = {
    { 25, car_update_25 },
    { 24, car_update_24 },
    { 30, car_update_30 },
    { 26, car_update_26 },
    { 27, car_update_27 },
    { 29, car_update_29 },
    { 28, car_update_28 },
    { 31, car_update_31 },
  },
  .Hes = {
  },
  .sets = {
    { "mass", car_set_mass },
    { "rotational_inertia", car_set_rotational_inertia },
    { "center_to_front", car_set_center_to_front },
    { "center_to_rear", car_set_center_to_rear },
    { "stiffness_front", car_set_stiffness_front },
    { "stiffness_rear", car_set_stiffness_rear },
  },
  .extra_routines = {
  },
};

ekf_init(car);
