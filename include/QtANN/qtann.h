/****************************************************************************
 *                                                                          *
 * Copyright (C) 2015 Neutrino International Inc.                           *
 *                                                                          *
 * Author : Brian Lin <lin.foxman@gmail.com>, Skype: wolfram_lin            *
 *                                                                          *
 ****************************************************************************/

#ifndef QT_ANN_H
#define QT_ANN_H

#include <QtCore>
#ifndef QT_STATIC
#include <QtScript>
#endif
#include <QtNetwork>
#include <QtSql>

QT_BEGIN_NAMESPACE

#ifndef QT_STATIC
#  if defined(QT_BUILD_QTANN_LIB)
#    define Q_ANN_EXPORT Q_DECL_EXPORT
#  else
#    define Q_ANN_EXPORT Q_DECL_IMPORT
#  endif
#else
#    define Q_ANN_EXPORT
#endif

// ANN => Artificial Neural Network

class Q_ANN_EXPORT QtAnnNeuron     ;
class Q_ANN_EXPORT QtAnnLayer      ;
class Q_ANN_EXPORT QtAnnConnection ;
class Q_ANN_EXPORT QtAnnTrain      ;
class Q_ANN_EXPORT QtANN           ;

namespace ANN
{

  /**************************************************************************\
   *                                                                        *
   * The activation functions used for the neurons during training. The     *
   * activation functions can either be defined for a group of neurons by   *
   * <fann_set_activation_function_hidden> and                              *
   * <fann_set_activation_function_output> or it can be defined for a       *
   * single neuron by <fann_set_activation_function>.                       *
   *                                                                        *
   * The steepness of an activation function is defined in the same way by  *
   * <fann_set_activation_steepness_hidden>,                                *
   * <fann_set_activation_steepness_output> and                             *
   * <fann_set_activation_steepness>.                                       *
   *                                                                        *
   * The functions are described with functions where:                      *
   * x is the input to the activation function,                             *
   * y is the output,                                                       *
   * s is the steepness and                                                 *
   * d is the derivation.                                                   *
   *                                                                        *
   * Linear - Linear activation function.                                   *
   *  * span: -inf < y < inf                                                *
   *  * y = x*s, d = 1*s                                                    *
   *  * Can NOT be used in fixed point.                                     *
   *                                                                        *
   * Threshold - Threshold activation function.                             *
   *  * x < 0 -> y = 0, x >= 0 -> y = 1                                     *
   *  * Can NOT be used during training.                                    *
   *                                                                        *
   * Symmetric Threshold - Threshold activation function.                   *
   *  * x < 0 -> y = 0, x >= 0 -> y = 1                                     *
   *  * Can NOT be used during training.                                    *
   *                                                                        *
   * Sigmoid - Sigmoid activation function.                                 *
   *  * One of the most used activation functions.                          *
   *  * span: 0 < y < 1                                                     *
   *  * y = 1/(1 + exp(-2*s*x))                                             *
   *  * d = 2*s*y*(1 - y)                                                   *
   *                                                                        *
   * Stepwise Sigmoid - Stepwise linear approximation to sigmoid.           *
   *  * Faster than sigmoid but a bit less precise.                         *
   *                                                                        *
   * Symmetric Sigmoid - Symmetric sigmoid activation function, aka. tanh.  *
   *  * One of the most used activation functions.                          *
   *  * span: -1 < y < 1                                                    *
   *  * y = tanh(s*x) = 2/(1 + exp(-2*s*x)) - 1                             *
   *  * d = s*(1-(y*y))                                                     *
   *                                                                        *
   * Symmetric Stepwise Sigmoid - Stepwise linear approximation to          *
   *                              symmetric sigmoid.                        *
   *  * Faster than symmetric sigmoid but a bit less precise.               *
   *                                                                        *
   * Gaussian - Gaussian activation function.                               *
   *  * 0 when x = -inf, 1 when x = 0 and 0 when x = inf                    *
   *  * span: 0 < y < 1                                                     *
   *  * y = exp(-x*s*x*s)                                                   *
   *  * d = -2*x*s*y*s                                                      *
   *                                                                        *
   * Symmetric gaussian - Symmetric gaussian activation function.           *
   *  * -1 when x = -inf, 1 when x = 0 and 0 when x = inf                   *
   *  * span: -1 < y < 1                                                    *
   *  * y = exp(-x*s*x*s)*2-1                                               *
   *  * d = -2*x*s*(y+1)*s                                                  *
   *                                                                        *
   * Elliot - Fast (sigmoid like) activation function                       *
   *          defined by David Elliott                                      *
   *  * span: 0 < y < 1                                                     *
   *  * y = ((x*s) / 2) / (1 + |x*s|) + 0.5                                 *
   *  * d = s*1/(2*(1+|x*s|)*(1+|x*s|))                                     *
   *                                                                        *
   * Symmetric Elliot - Fast (symmetric sigmoid like) activation function   *
   *  * span: -1 < y < 1                                                    *
   *  * y = (x*s) / (1 + |x*s|)                                             *
   *  * d = s*1/((1+|x*s|)*(1+|x*s|))                                       *
   *                                                                        *
   * Linear Piece - Bounded linear activation function.                     *
   *  * span: 0 <= y <= 1                                                   *
   *  * y = x*s, d = 1*s                                                    *
   *                                                                        *
   * Symmetric Linear Piece - Bounded linear activation function.           *
   *  * span: -1 <= y <= 1                                                  *
   *  * y = x*s, d = 1*s                                                    *
   *                                                                        *
   * Symmetric Sine - Periodical sinus activation function.                 *
   *  * span: -1 <= y <= 1                                                  *
   *  * y = sin(x*s)                                                        *
   *  * d = s*cos(x*s)                                                      *
   *                                                                        *
   * Symmetric Cosine - Periodical cosinus activation function.             *
   *  * span: -1 <= y <= 1                                                  *
   *  * y = cos(x*s)                                                        *
   *  * d = s*-sin(x*s)                                                     *
   *                                                                        *
   * Sine - Periodical sinus activation function.                           *
   *  * span: 0 <= y <= 1                                                   *
   *  * y = sin(x*s)/2+0.5                                                  *
   *  * d = s*cos(x*s)/2                                                    *
   *                                                                        *
   * Cosine - Periodical cosinus activation function.                       *
   *  * span: 0 <= y <= 1                                                   *
   *  * y = cos(x*s)/2+0.5                                                  *
   *  * d = s*-sin(x*s)/2                                                   *
   *                                                                        *
  \**************************************************************************/

  typedef enum                   {
    Nothing                  =  0 ,
    Linear                   =  1 ,
    Threshold                =  2 ,
    SymmetricThreshold       =  3 ,
    Sigmoid                  =  4 ,
    StepwiseSigmoid          =  5 ,
    SymmetricSigmoid         =  6 ,
    SymmetricStepwiseSigmoid =  7 ,
    Gaussian                 =  8 ,
    SymmetricGaussian        =  9 ,
    StepwiseGaussian         = 10 ,
    Elliot                   = 11 ,
    SymmetricElliot          = 12 ,
    LinearPiece              = 13 ,
    SymmetricLinearPiece     = 14 ,
    Sine                     = 15 ,
    SymmetricSine            = 16 ,
    Cosine                   = 17 ,
    SymmetricCosine          = 18
  } Functions                     ;

  typedef enum                    {
    NoError                  =  0 ,
    CannotOpenConfigR        =  1 ,
    CannotOpenConfigW        =  2 ,
    WrongConfigVersion       =  3 ,
    CannotReadConfig         =  4 ,
    CannotReadNeuron         =  5 ,
    CannotReadConnections    =  6 ,
    WrongNumConnections      =  7 ,
    CannotOpenTDW            =  8 ,
    CannotOpenTDR            =  9 ,
    CannotOpenTD             = 10 ,
    CannotAllocateMemory     = 11 ,
    CannotTrainActivation    = 12 ,
    CannotUseActivation      = 13 ,
    TrainDataMismatch        = 14 ,
    CannotUseTrainALG        = 15 ,
    TrainDataSubset          = 16 ,
    IndexOutOfBound          = 17 ,
    ScaleNotPresent          = 18 ,
    InputNoMatch             = 19 ,
    OutputNoMatch            = 20
  } Errors                        ;

  typedef enum                    {
    Layer                    =  0 ,
    Shortcut                 =  1
  } NetworkTypes                  ;

  typedef enum                    {
    Incremental              =  0 ,
    Batch                    =  1 ,
    RProp                    =  2 ,
    QuickProp                =  3 ,
    SarProp                  =  4
  } Trains                        ;

  typedef enum                    {
    ErrorLinear              =  0 ,
    ErrorTanh                =  1
  } ErrorFunctions                ;

  typedef enum                    {
    MSE                      =  0 ,
    BIT                      =  1
  } StopFunctions                 ;

}

class Q_ANN_EXPORT QtAnnNeuron
{
  public:

    unsigned int   first     ;
    unsigned int   last      ;
    double         sum       ;
    double         value     ;
    double         steepness ;
    ANN::Functions function  ;

    explicit QtAnnNeuron (void) ;
    virtual ~QtAnnNeuron (void) ;

  protected:

  private:

};

class Q_ANN_EXPORT QtAnnLayer
{
  public:

    QtAnnNeuron * first ;
    QtAnnNeuron * last  ;

    explicit QtAnnLayer (void) ;
    virtual ~QtAnnLayer (void) ;

  protected:

  private:

};

class Q_ANN_EXPORT QtAnnConnection
{
  public:

    unsigned int from   ;
    unsigned int to     ;
    double       weight ;

    explicit QtAnnConnection (void) ;
    virtual ~QtAnnConnection (void) ;

  protected:

  private:

};

class Q_ANN_EXPORT QtAnnTrain
{
  public:

    ANN::Errors  ErrNo       ;
    QString      ErrorString ;
    unsigned int num_data    ;
    unsigned int num_input   ;
    unsigned int num_output  ;
    double    ** input       ;
    double    ** output      ;

    explicit QtAnnTrain (void) ;
    virtual ~QtAnnTrain (void) ;

  protected:

  private:

};

class Q_ANN_EXPORT QtANN
{
  public:

    ANN::Errors         ErrNo                                ;
    QString             ErrorString                          ;
    double              learning_rate                        ;
    double              learning_momentum                    ;
    double              connection_rate                      ;
    ANN::NetworkTypes   network_type                         ;
    QtAnnLayer       *  first_layer                          ;
    QtAnnLayer       *  last_layer                           ;
    unsigned int        total_neurons                        ;
    unsigned int        num_input                            ;
    unsigned int        num_output                           ;
    double           *  weights                              ;
    QtAnnNeuron      ** connections                          ;
    double           *  train_errors                         ;
    ANN::Trains         training_algorithm                   ;
    unsigned int        total_connections                    ;
    double           *  output                               ;
    unsigned int        num_MSE                              ;
    double              MSE_value                            ;
    unsigned int        num_bit_fail                         ;
    double              bit_fail_limit                       ;
    ANN::ErrorFunctions train_error_function                 ;
    ANN::StopFunctions  train_stop_function                  ;
    void             *  user_data                            ;
    double              cascade_output_change_fraction       ;
    unsigned int        cascade_output_stagnation_epochs     ;
    double              cascade_candidate_change_fraction    ;
    unsigned int        cascade_candidate_stagnation_epochs  ;
    unsigned int        cascade_best_candidate               ;
    double              cascade_candidate_limit              ;
    double              cascade_weight_multiplier            ;
    unsigned int        cascade_max_out_epochs               ;
    unsigned int        cascade_max_cand_epochs              ;
    unsigned int        cascade_min_out_epochs               ;
    unsigned int        cascade_min_cand_epochs              ;
    ANN::Functions   *  cascade_activation_functions         ;
    unsigned int        cascade_activation_functions_count   ;
    double           *  cascade_activation_steepnesses       ;
    unsigned int        cascade_activation_steepnesses_count ;
    unsigned int        cascade_num_candidate_groups         ;
    double           *  cascade_candidate_scores             ;
    unsigned int        total_neurons_allocated              ;
    unsigned int        total_connections_allocated          ;
    double              quickprop_decay                      ;
    double              quickprop_mu                         ;
    double              rprop_increase_factor                ;
    double              rprop_decrease_factor                ;
    double              rprop_delta_min                      ;
    double              rprop_delta_max                      ;
    double              rprop_delta_zero                     ;
    double              sarprop_weight_decay_shift           ;
    double              sarprop_step_error_threshold_factor  ;
    double              sarprop_step_error_shift             ;
    double              sarprop_temperature                  ;
    unsigned int        sarprop_epoch                        ;
    double           *  train_slopes                         ;
    double           *  prev_steps                           ;
    double           *  prev_train_slopes                    ;
    double           *  prev_weights_deltas                  ;

    explicit QtANN (void) ;
    virtual ~QtANN (void) ;

  protected:

  private:

};

QT_END_NAMESPACE

#endif
