/* 
 * Developers: DSOR Team -> @tecnico.ulisboa.pt Instituto Superior Tecnico 
 */
#include "CppCounterNode.h"
#include "CppCounterAlgorithm.h"

// @.@ Constructor
CppCounterNode::CppCounterNode(ros::NodeHandle *nodehandle, ros::NodeHandle *nodehandle_private):nh_(*nodehandle), nh_private_(*nodehandle_private) {

  loadParams();
  initializeSubscribers();
  initializePublishers();
  // initializeServices();
  initializeTimer();

}

// @.@ Destructor
CppCounterNode::~CppCounterNode() {

  // +.+ shutdown publishers


  // +.+ shutdown subscribers


  // +.+ stop timer
  timer_.stop();

  // +.+ shutdown node
  nh_.shutdown();
  nh_private_.shutdown();
}

// @.@ Member helper to load parameters from parameter server
void CppCounterNode::loadParams() {
  ROS_INFO("Load the CppCounterNode parameters");

  p_node_frequency_ = FarolGimmicks::getParameters<double>(nh_private_, "node_frequency");
  count_ = FarolGimmicks::getParameters<int>(nh_private_, "start_num");
  pause = false;
}


// @.@ Member helper function to set up subscribers
void CppCounterNode::initializeSubscribers() {
  ROS_INFO("Initializing Subscribers for CppCounterNode");
  pause_sub = nh_private_.subscribe(FarolGimmicks::getParameters<std::string>(nh_private_, "topics/subscribers/pause"), 1, &CppCounterNode::setPause, this);
}


// @.@ Member helper function to set up publishers
void CppCounterNode::initializePublishers() {
  ROS_INFO("Initializing Publishers for CppCounterNode");
  count_pub = nh_private_.advertise<std_msgs::Int32>(FarolGimmicks::getParameters<std::string>(nh_private_, "topics/publishers/count"), 1);
}


// @.@ Member helper function to set up services
void CppCounterNode::initializeServices() {
  ROS_INFO("Initializing Services for CppCounterNode");

}


// @.@ Member helper function to set up the timer
void CppCounterNode::initializeTimer() {
  timer_ = nh_.createTimer(ros::Duration(1.0/p_node_frequency_), &CppCounterNode::timerIterCallback, this);
}


// @.@ Where the magic should happen.
void CppCounterNode::timerIterCallback(const ros::TimerEvent &event) {
  std_msgs::Int32 count_to_send;
  if(pause) count_to_send.data = count_;
  else count_to_send.data = counting(&count_);
  count_pub.publish(count_to_send);
}


void CppCounterNode::setPause(const std_msgs::Bool msg) {
  pause = msg.data;
}


/*
  @.@ Main
*/
int main(int argc, char** argv)
{
  // +.+ ROS set-ups:
  ros::init(argc, argv, "cpp_counter_node"); //node name
  
  // +.+ node handle
  ros::NodeHandle nh;

  // +.+ private node handle
  ros::NodeHandle nh_private("~");

  ROS_INFO("main: instantiating an object of type CppCounterNode");

  // +.+ instantiate an CppCounterNode class object and pass in pointers to nodehandle public and private for constructor to use
  CppCounterNode cpp_counter(&nh,&nh_private);

  // +.+  Going into spin; let the callbacks do all the magic
  ros::spin();

  return 0;
}
