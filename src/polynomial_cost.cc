/**
 @file    polynomial_cost.cc
 @author  Alexander W. Winkler (winklera@ethz.ch)
 @date    May 30, 2016
 @brief   Definition of the ASplineCost, QuadraticSplineCost, SquaredSplineCost
 */

#include <xpp/opt/costs/polynomial_cost.h>

#include <Eigen/Dense>

#include <xpp/opt/variables/base_motion.h>

namespace xpp {
namespace opt {


QuadraticPolynomialCost::QuadraticPolynomialCost (const OptVarsPtr& opt_vars,
                                                  const MatVec& mat_vec,
                                                  double weight)
{
  SetName("QuadraticPolynomialCost");
  matrix_vector_ = mat_vec;
  weight_ = weight;

  SetDimensions(opt_vars, 1);
  com_motion_    = std::dynamic_pointer_cast<BaseMotion>(opt_vars->GetComponent("base_motion"));
}

QuadraticPolynomialCost::~QuadraticPolynomialCost ()
{
}

QuadraticPolynomialCost::VectorXd
QuadraticPolynomialCost::GetValues () const
{
  VectorXd cost = VectorXd(num_rows_);
  VectorXd spline_coeff_ = com_motion_->GetXYSplineCoeffients();

  cost += spline_coeff_.transpose() * matrix_vector_.M * spline_coeff_;
  cost += matrix_vector_.v.transpose() * spline_coeff_;

  return weight_*cost;
}

void
QuadraticPolynomialCost::FillJacobianWithRespectTo(std::string var_set, Jacobian& jac) const
{
  if (var_set == com_motion_->GetName()) {
    VectorXd grad = 2.0 * matrix_vector_.M * com_motion_->GetXYSplineCoeffients();
    jac.row(0) =  grad.transpose().sparseView();
  }
}

} /* namespace opt */
} /* namespace xpp */
