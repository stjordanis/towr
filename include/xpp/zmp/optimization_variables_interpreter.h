/**
 @file    optimization_variables_interpreter.h
 @author  Alexander W. Winkler (winklera@ethz.ch)
 @date    Jun 3, 2016
 @brief   Brief description
 */

#ifndef USER_TASK_DEPENDS_XPP_OPT_INCLUDE_XPP_ZMP_OPTIMIZATION_VARIABLES_INTERPRETER_H_
#define USER_TASK_DEPENDS_XPP_OPT_INCLUDE_XPP_ZMP_OPTIMIZATION_VARIABLES_INTERPRETER_H_

#include <xpp/hyq/foothold.h>
#include <xpp/zmp/continuous_spline_container.h>

namespace xpp {
namespace zmp {

class OptimizationVariablesInterpreter {
public:
  typedef std::vector<xpp::hyq::Foothold> VecFoothold;
  typedef SplineContainer::VecSpline VecSpline;
  typedef std::vector<xpp::hyq::LegID> VecLegID;
  typedef xpp::utils::StdVecEigen2d FootholdPositionsXY;
  typedef Eigen::VectorXd VectorXd;
  typedef Eigen::Vector2d Vector2d;

  OptimizationVariablesInterpreter ();
  virtual ~OptimizationVariablesInterpreter ();

  void Init(const Vector2d& start_cog_p,
            const Vector2d& start_cog_v,
            const std::vector<xpp::hyq::LegID>& step_sequence,
            const VecFoothold& start_stance,
            const SplineTimes& times,
            double robot_height);

  double GetRobotHeight() const;
  ContinuousSplineContainer GetSplineStructure() const;
  VecFoothold GetStartStance() const;
  VecLegID GetStepSequence() const;

  VecFoothold GetFootholds(const FootholdPositionsXY&) const;
  VecSpline GetSplines(const VectorXd& spline_coeff_abcd) const;

private:
  VecLegID step_sequence_;
  VecFoothold start_stance_;
  ContinuousSplineContainer spline_structure_;
  double robot_height_;

  bool initialized_ = false; // checks if the Init() method has been called
};

} /* namespace zmp */
} /* namespace xpp */

#endif /* USER_TASK_DEPENDS_XPP_OPT_INCLUDE_XPP_ZMP_OPTIMIZATION_VARIABLES_INTERPRETER_H_ */
