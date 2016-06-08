/**
 @file    nlp_ipopt_zmp.h
 @author  Alexander W. Winkler (winklera@ethz.ch)
 @date    Jan 10, 2016
 @brief   Defines the Adapter class to interact with the Ipopt Library.
 */

#ifndef XXPP_ZMP_NLP_IPOPT_ZMP_H_
#define XXPP_ZMP_NLP_IPOPT_ZMP_H_

#include <IpTNLP.hpp>

#include <xpp/zmp/cost_container.h>
#include <xpp/zmp/cost_function_functor.h>

#include <xpp/zmp/constraint_container.h>
#include <xpp/zmp/optimization_variables.h>
#include <xpp/zmp/i_visualizer.h>

namespace Ipopt {

/** @brief Converts the NLP defined in the xpp interface to the IPOPT interface.
  *
  * This implements the Adapter pattern. This class should not add any functionality,
  * but merely delegate it to the Adaptee (the xpp code).
  */
class IpoptAdapter : public Ipopt::TNLP {

public:
  typedef xpp::zmp::ConstraintContainer ConstraintContainer;
  typedef xpp::zmp::CostContainer CostContainer;
  typedef xpp::zmp::CostFunctionFunctor CostFunctionFunctor;
  typedef Eigen::NumericalDiff<CostFunctionFunctor> NumericalDiffFunctor;
  typedef xpp::zmp::OptimizationVariables OptimizationVariables;
  typedef xpp::zmp::IVisualizer IVisualizer;
  typedef Eigen::VectorXd VectorXd;

	IpoptAdapter(OptimizationVariables& opt_variables,
	            CostContainer& cost_container,
	            ConstraintContainer& constraint_container,
	            IVisualizer& visualizer);

  /** default destructor */
  virtual ~IpoptAdapter() {};

  /**@name Overloaded from TNLP */
  //@{
  /** Method to return some info about the nlp */
  virtual bool get_nlp_info(Index& n, Index& m, Index& nnz_jac_g,
                            Index& nnz_h_lag, IndexStyleEnum& index_style);

  /** Method to return the bounds for my problem */
  virtual bool get_bounds_info(Index n, Number* x_l, Number* x_u,
                               Index m, Number* g_l, Number* g_u);

  /** Method to return the starting point for the algorithm */
  virtual bool get_starting_point(Index n, bool init_x, Number* x,
                                  bool init_z, Number* z_L, Number* z_U,
                                  Index m, bool init_lambda,
                                  Number* lambda);

  /** Method to return the objective value */
  virtual bool eval_f(Index n, const Number* x, bool new_x, Number& obj_value);

  /** Method to return the gradient of the objective */
  virtual bool eval_grad_f(Index n, const Number* x, bool new_x, Number* grad_f);

  /** Method to return the constraint residuals */
  virtual bool eval_g(Index n, const Number* x, bool new_x, Index m, Number* g);

  /** Method to return:
   *   1) The structure of the jacobian (if "values" is NULL)
   *   2) The values of the jacobian (if "values" is not NULL)
   */
  virtual bool eval_jac_g(Index n, const Number* x, bool new_x,
                          Index m, Index nele_jac, Index* iRow, Index *jCol,
                          Number* values);

  /** Method to return:
   *   1) The structure of the hessian of the lagrangian (if "values" is NULL)
   *   2) The values of the hessian of the lagrangian (if "values" is not NULL)
   */
//  virtual bool eval_h(Index n, const Number* x, bool new_x,
//                      Number obj_factor, Index m, const Number* lambda,
//                      bool new_lambda, Index nele_hess, Index* iRow,
//                      Index* jCol, Number* values);

  //@}


  virtual bool intermediate_callback(AlgorithmMode mode,
                                     Index iter, Number obj_value,
                                     Number inf_pr, Number inf_du,
                                     Number mu, Number d_norm,
                                     Number regularization_size,
                                     Number alpha_du, Number alpha_pr,
                                     Index ls_trials,
                                     const IpoptData* ip_data,
                                     IpoptCalculatedQuantities* ip_cq);


  /** @name Solution Methods */
  //@{
  /** This method is called when the algorithm is complete so the TNLP can store/write the solution */
  virtual void finalize_solution(SolverReturn status,
                                 Index n, const Number* x, const Number* z_L, const Number* z_U,
                                 Index m, const Number* g, const Number* lambda,
                                 Number obj_value,
                                 const IpoptData* ip_data,
                                 IpoptCalculatedQuantities* ip_cq);
  //@}

private:
  OptimizationVariables& opt_variables_;
  CostContainer& cost_container_;
  ConstraintContainer& constraint_container_;

  NumericalDiffFunctor cf_num_diff_functor_;
  IVisualizer& visualizer_;
};

} // namespace Ipopt

#endif /* XXPP_ZMP_NLP_IPOPT_ZMP_H_ */
