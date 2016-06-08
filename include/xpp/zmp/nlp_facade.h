/*
 * nlp_optimizer.h
 *
 *  Created on: Mar 18, 2016
 *      Author: winklera
 */

#ifndef USER_TASK_DEPENDS_XPP_OPT_INCLUDE_XPP_ZMP_NLP_FACADE_H_
#define USER_TASK_DEPENDS_XPP_OPT_INCLUDE_XPP_ZMP_NLP_FACADE_H_

#include <xpp/zmp/optimization_variables.h>
#include <xpp/zmp/constraint_container.h>
#include <xpp/zmp/cost_container.h>

#include <xpp/zmp/i_visualizer.h>

#include <IpIpoptApplication.hpp>
#include <IpSolveStatistics.hpp>

namespace xpp {
namespace hyq {
class Foothold;
}
}

namespace xpp {
namespace zmp {

class OptimizationVariablesInterpreter;
class InterpretingObserver;
class ZmpSpline;

/** @brief Simplified interface to setup and solve a Nonlinear-Program.
  *
  * This follows the facade pattern, to hide the complexity of the cost and
  * constraint object creation from the client. The client can optionally
  * pass in a visualizer, but ultimately this class is ROS independent.
  */
class NlpFacade {
public:
  typedef xpp::utils::Point2d State;
  typedef std::shared_ptr<OptimizationVariablesInterpreter> InterpreterPtr;
  typedef Ipopt::SmartPtr<Ipopt::TNLP> IpoptPtr;
  typedef std::shared_ptr<InterpretingObserver> InterpretingObserverPtr;
  typedef std::vector<xpp::hyq::Foothold> VecFoothold;
  typedef std::vector<ZmpSpline> VecSpline;

  NlpFacade (IVisualizer& visualizer = do_nothing_visualizer);
  virtual ~NlpFacade () {};

  /** @brief Solves the nonlinear program (NLP) of moving the CoG from an initial to a
    * final state while keeping the Zero-Moment-Point (ZMP) inside the support
    * polygons created by the contact points (e.g. feet).
    *
    * @param initial_state position, velocity and acceleration of the CoG
    * @param final_state desired final position, velocity and acceleration of the CoG
    * @param step_sequence the sequence (e.g. left hind, left front,...) of steps to be taken
    * @param start_stance the initial contacts (e.g left front,...) and position
    * @param times the duration of the different splines
    * @param robot_height the walking height of the robot (affects ZMP)
    */
  void SolveNlp(const Eigen::Vector2d& initial_acc,
                const State& final_state,
                const InterpreterPtr&);

  void AttachVisualizer(IVisualizer& visualizer);
  InterpretingObserverPtr GetObserver() const;

  VecFoothold GetFootholds() const;
  VecSpline GetSplines() const;

private:
  void SolveIpopt(const IpoptPtr& nlp);

  OptimizationVariables opt_variables_;
  ConstraintContainer constraints_;
  CostContainer costs_;

  InterpretingObserverPtr interpreting_observer_;
  IVisualizer* visualizer_;

  Ipopt::IpoptApplication ipopt_solver_;
  Ipopt::ApplicationReturnStatus status_;
};

} /* namespace zmp */
} /* namespace xpp */

#endif /* USER_TASK_DEPENDS_XPP_OPT_INCLUDE_XPP_ZMP_NLP_FACADE_H_ */
