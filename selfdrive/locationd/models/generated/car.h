#pragma once
#include "rednose/helpers/common_ekf.h"
extern "C" {
void car_update_25(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_update_24(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_update_30(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_update_26(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_update_27(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_update_29(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_update_28(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_update_31(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_err_fun(double *nom_x, double *delta_x, double *out_1160912902492293220);
void car_inv_err_fun(double *nom_x, double *true_x, double *out_3114711529215166268);
void car_H_mod_fun(double *state, double *out_2799184021601232983);
void car_f_fun(double *state, double dt, double *out_8047485781251068468);
void car_F_fun(double *state, double dt, double *out_8124325998508320210);
void car_h_25(double *state, double *unused, double *out_394435484822648660);
void car_H_25(double *state, double *unused, double *out_8110192764782635771);
void car_h_24(double *state, double *unused, double *out_6938048359663727949);
void car_H_24(double *state, double *unused, double *out_6778625710124592709);
void car_h_30(double *state, double *unused, double *out_551622153173777805);
void car_H_30(double *state, double *unused, double *out_7818218350419667218);
void car_h_26(double *state, double *unused, double *out_4790245082712252758);
void car_H_26(double *state, double *unused, double *out_4368689445908579547);
void car_h_27(double *state, double *unused, double *out_3431221536266981345);
void car_H_27(double *state, double *unused, double *out_5594624279235724001);
void car_h_29(double *state, double *unused, double *out_8244687311092219335);
void car_H_29(double *state, double *unused, double *out_7307987006105275034);
void car_h_28(double *state, double *unused, double *out_1570451731393864300);
void car_H_28(double *state, double *unused, double *out_6056358050534746008);
void car_h_31(double *state, double *unused, double *out_6982263411298943823);
void car_H_31(double *state, double *unused, double *out_8140838726659596199);
void car_predict(double *in_x, double *in_P, double *in_Q, double dt);
void car_set_mass(double x);
void car_set_rotational_inertia(double x);
void car_set_center_to_front(double x);
void car_set_center_to_rear(double x);
void car_set_stiffness_front(double x);
void car_set_stiffness_rear(double x);
}