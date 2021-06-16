#include <qtann.h>

QtANN:: QtANN (void)
{
  ErrNo                                = ANN::NoError     ;
  ErrorString                          = ""               ;
  learning_rate                        = 0                ;
  learning_momentum                    = 0                ;
  connection_rate                      = 0                ;
  network_type                         = ANN::Layer       ;
  first_layer                          = NULL             ;
  last_layer                           = NULL             ;
  total_neurons                        = 0                ;
  num_input                            = 0                ;
  num_output                           = 0                ;
  weights                              = NULL             ;
  connections                          = NULL             ;
  train_errors                         = NULL             ;
  training_algorithm                   = ANN::Incremental ;
  total_connections                    = 0                ;
  output                               = NULL             ;
  num_MSE                              = 0                ;
  MSE_value                            = 0                ;
  num_bit_fail                         = 0                ;
  bit_fail_limit                       = 0                ;
  train_error_function                 = ANN::ErrorLinear ;
  train_stop_function                  = ANN::MSE         ;
  user_data                            = NULL             ;
  cascade_output_change_fraction       = 0                ;
  cascade_output_stagnation_epochs     = 0                ;
  cascade_candidate_change_fraction    = 0                ;
  cascade_candidate_stagnation_epochs  = 0                ;
  cascade_best_candidate               = 0                ;
  cascade_candidate_limit              = 0                ;
  cascade_weight_multiplier            = 0                ;
  cascade_max_out_epochs               = 0                ;
  cascade_max_cand_epochs              = 0                ;
  cascade_min_out_epochs               = 0                ;
  cascade_min_cand_epochs              = 0                ;
  cascade_activation_functions         = NULL             ;
  cascade_activation_functions_count   = 0                ;
  cascade_activation_steepnesses       = NULL             ;
  cascade_activation_steepnesses_count = 0                ;
  cascade_num_candidate_groups         = 0                ;
  cascade_candidate_scores             = NULL             ;
  total_neurons_allocated              = 0                ;
  total_connections_allocated          = 0                ;
  quickprop_decay                      = 0                ;
  quickprop_mu                         = 0                ;
  rprop_increase_factor                = 0                ;
  rprop_decrease_factor                = 0                ;
  rprop_delta_min                      = 0                ;
  rprop_delta_max                      = 0                ;
  rprop_delta_zero                     = 0                ;
  sarprop_weight_decay_shift           = 0                ;
  sarprop_step_error_threshold_factor  = 0                ;
  sarprop_step_error_shift             = 0                ;
  sarprop_temperature                  = 0                ;
  sarprop_epoch                        = 0                ;
  train_slopes                         = NULL             ;
  prev_steps                           = NULL             ;
  prev_train_slopes                    = NULL             ;
  prev_weights_deltas                  = NULL             ;
}

QtANN::~QtANN(void)
{
}
