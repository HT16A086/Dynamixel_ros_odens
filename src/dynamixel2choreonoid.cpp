#include "ros/ros.h"
#include "ros/time.h"
#include <sensor_msgs/Joy.h>
#include "std_msgs/Float64.h"
#include "std_msgs/String.h"
#include <std_msgs/Float32MultiArray.h>
#include "sensor_msgs/JointState.h"

using namespace std;

#define num 16

std_msgs::Float32MultiArray qt;
//qt.data.resize(num);
class Dynamixel2Choreonoid{
public:
  Dynamixel2Choreonoid();

private:
  void rudderCallback(const sensor_msgs::Joy::ConstPtr& rudder){
    rudder_ = *rudder;
  }

  void jointCallback(const sensor_msgs::JointStateConstPtr& msg){
    joint_state_ = *msg;
  }

  void monitorJointState_callback(const sensor_msgs::JointState::ConstPtr& msg){
    master_joint_state_ = *msg;
  }

  //void monitorJointState_callback(const sensor_msgs::JointState::ConstPtr& jointstate){
  //MFRAME.data = jointstate->name[0];    // 名前読み出し
  //BLOCK.data = jointstate->name[1];    // 名前読み出し

  //MFRAME_pos.data = jointstate->position[0];    // ポジション読み出し    loop_rate.sleep();
  //BLOCK_pos.data = jointstate->position[1];    // ポジション読み出し

  //MFRAME_vel.data = jointstate->velocity[0];    // 速度読み出し
  //BLOCK_vel.data = jointstate->velocity[1];    // 速度読み出し

  //MFRAME_eff.data = jointstate->effort[0];    // 負荷読み出し
  //BLOCK_eff.data = jointstate->effort[1];    // 負荷読み出し
  //}

  void timerCallback(const ros::TimerEvent& e);

  ros::NodeHandle nh;

  ros::Publisher vel_pub_;
  ros::Publisher qt_pub_;
  ros::Subscriber joy_sub_;
  ros::Subscriber rudder_sub_;
  ros::Subscriber joint_sub_;
  ros::Subscriber sub_joints;  // サブスクライバの作成

  bool use_rudder_;

  ros::Timer timer_;

  const double dt = 0.005;
  //std::vector<double> q_ref;

  sensor_msgs::Joy joy_;
  sensor_msgs::Joy rudder_;
  sensor_msgs::JointState joint_state_;
  sensor_msgs::JointState master_joint_state_;
  //std_msgs::String MFRAME, BLOCK,BOOM,ARM,TOHKU_PITCH,TOHKU_ROLL,TOHKU_TIP_01,TOHKU_TIP_02,UFRAME,MNP_SWING,MANIBOOM,MANIARM,MANIELBOW,YAWJOINT,HANDBASE,PUSHROD;
  //std_msgs::Float64 MFRAME_pos, BLOCK_pos,BOOM_pos,ARM_pos,TOHKU_PITCH_pos,TOHKU_ROLL_pos,TOHKU_TIP_01_pos,TOHKU_TIP_02_pos,UFRAME_pos,MNP_SWING_pos,MANIBOOM_pos,MANIARM_pos,MANIELBOW_pos,YAWJOINT_pos,HANDBASE_pos,PUSHROD_pos;
  //std_msgs::Float64 MFRAME_vel, BLOCK_vel;
  //std_msgs::Float64 MFRAME_eff, BLOCK_eff;
  bool robot_ready_;
};

Dynamixel2Choreonoid::Dynamixel2Choreonoid():
  use_rudder_(false)
{
  ros::NodeHandle pnh("~");
  ros::NodeHandle nh; // ノードハンドラ 
  pnh.getParam("use_rudder", use_rudder_);

  vel_pub_ = nh.advertise<std_msgs::Float32MultiArray>("vel", 1);
  qt_pub_ = nh.advertise<std_msgs::Float32MultiArray>("qt", 1);
  sub_joints = nh.subscribe("/dynamixel_workbench/joint_states", 10, &Dynamixel2Choreonoid::monitorJointState_callback, this);
  //joy_sub_ = nh_.subscribe<sensor_msgs::Joy>("joy", 10, &DoubleArmGameController::joyCallback, this);
  //rudder_sub_ = nh_.subscribe<sensor_msgs::Joy>("rudder", 10, &DoubleArmGameController::rudderCallback, this);
  joint_sub_ = nh.subscribe("DoubleArmV7/joint_states", 1, &Dynamixel2Choreonoid::jointCallback, this);
  timer_ = nh.createTimer(ros::Duration(dt), &Dynamixel2Choreonoid::timerCallback, this);
}

void Dynamixel2Choreonoid::timerCallback(const ros::TimerEvent& e){
  std_msgs::Float32MultiArray qt;
  qt.data.resize(num);
  if (master_joint_state_.header.seq == 0) return;
  //qt.data[0] = master_joint_state_.position[0];
  //qt.data[1] = master_joint_state_.position[1];
  //for (int i = 0; i < num; i++) {
    qt.data[0] = master_joint_state_.position[0];
    qt.data[1] = master_joint_state_.position[1];
    qt.data[2] = master_joint_state_.position[2];
    qt.data[3] = master_joint_state_.position[3];
    qt.data[4] = master_joint_state_.position[4];
    qt.data[5] = master_joint_state_.position[5];
    qt.data[6] = master_joint_state_.position[6];
    qt.data[7] = master_joint_state_.position[6];
    qt.data[8] = master_joint_state_.position[7];
    qt.data[9] = master_joint_state_.position[8];
    qt.data[10] = master_joint_state_.position[9];
    qt.data[11] = master_joint_state_.position[10];
    qt.data[12] = master_joint_state_.position[11];
    qt.data[13] = master_joint_state_.position[12];
    qt.data[14] = master_joint_state_.position[13];
    qt.data[15] = master_joint_state_.position[14];
    qt.data[16] = master_joint_state_.position[15];
    //ROS_INFO("pos%f",master_joint_state_.position[i]);

  //}
  
  qt_pub_.publish(qt);
  ROS_INFO("publish");
}

int main(int argc, char **argv){
  ros::init(argc, argv, "Dynamixel2Choreonoid_node");
  Dynamixel2Choreonoid dagc;
  
  //ros::spinOnce(); 
  //ros::Rate loop_rate(10);
	while(ros::ok()){
		//std::cout << "loop" << std::endl;
		ros::spinOnce();
		//loop_rate.sleep();
	}
  //return 0;
}