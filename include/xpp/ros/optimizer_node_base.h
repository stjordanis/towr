/*
 * optimizer_node_base.h
 *
 *  Created on: Apr 22, 2016
 *      Author: winklera
 */

#ifndef USER_TASK_DEPENDS_XPP_OPT_INCLUDE_XPP_ROS_OPTIMIZER_NODE_BASE_H_
#define USER_TASK_DEPENDS_XPP_OPT_INCLUDE_XPP_ROS_OPTIMIZER_NODE_BASE_H_

#include <xpp/utils/geometric_structs.h>
#include <xpp/hyq/foothold.h>
#include <xpp/zmp/spline_container.h>

// custom msg and srv
#include <xpp_opt/StateLin3d.h>
#include <xpp_opt/ReturnOptSplines.h>

#include <ros/ros.h>

namespace xpp {
namespace ros {

class OptimizerNodeBase {
public:
  typedef xpp::utils::Point2d State;
  typedef Eigen::VectorXd VectorXd;
  typedef xpp::hyq::Foothold Foothold;
  typedef xpp_opt::StateLin3d StateMsg;
  typedef xpp::zmp::SplineContainer::VecSpline VecSpline;
  typedef xpp_opt::ReturnOptSplines ReturnOptSplinesSrv;

public:
  OptimizerNodeBase ();
  virtual
  ~OptimizerNodeBase ();


protected:
  ::ros::NodeHandle n_;
  State goal_cog_;
  State curr_cog_;
  xpp::hyq::LegDataMap<Foothold> curr_stance_;
//  double curr_execution_time_;

  VecSpline opt_splines_;

private:
//  ::ros::Publisher opt_var_pub_;
//  ::ros::Subscriber curr_state_sub_;
  ::ros::Subscriber goal_state_sub_;
  ::ros::ServiceServer return_coeff_srv_;


  void CurrentStateCallback(const StateMsg& msg);
  void GoalStateCallback(const StateMsg& msg);
  bool ReturnOptimizedCoeff(ReturnOptSplinesSrv::Request& req,
                            ReturnOptSplinesSrv::Response& res);

};

} /* namespace ros */
} /* namespace xpp */

#endif /* USER_TASK_DEPENDS_XPP_OPT_INCLUDE_XPP_ROS_OPTIMIZER_NODE_BASE_H_ */
