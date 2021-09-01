#include "ros/ros.h"
#include "ros/time.h"

#include "std_msgs/Float64.h"
#include "std_msgs/String.h"

#include "sensor_msgs/JointState.h"

std_msgs::String MFRAME, BLOCK;
std_msgs::Float64 MFRAME_pos, BLOCK_pos;
std_msgs::Float64 MFRAME_vel, BLOCK_vel;
std_msgs::Float64 MFRAME_eff, BLOCK_eff;

void monitorJointState_callback(const sensor_msgs::JointState::ConstPtr& jointstate)
{
  MFRAME.data = jointstate->name[0];    // 名前読み出し
  BLOCK.data = jointstate->name[1];    // 名前読み出し

  MFRAME_pos.data = jointstate->position[0];    // ポジション読み出し    loop_rate.sleep();
  BLOCK_pos.data = jointstate->position[1];    // ポジション読み出し

  MFRAME_vel.data = jointstate->velocity[0];    // 速度読み出し
  BLOCK_vel.data = jointstate->velocity[1];    // 速度読み出し

  MFRAME_eff.data = jointstate->effort[0];    // 負荷読み出し
  BLOCK_eff.data = jointstate->effort[1];    // 負荷読み出し
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "dynamixel_reader");  // ノードの初期化
  ros::NodeHandle nh; // ノードハンドラ  
  ros::Subscriber sub_joints;  // サブスクライバの作成
  sub_joints = nh.subscribe("/dynamixel_workbench/joint_states", 10, monitorJointState_callback);

  ros::Rate loop_rate(10);  // 制御周期10Hz設定

  while (ros::ok()) { // 無限ループ

    ros::spinOnce();   // コールバック関数を呼ぶ
    loop_rate.sleep();  //wait
    ROS_INFO("MFRAME(%s)= %f | %f | %f ||| BLOCK(%s)= %f | %f | %f ", MFRAME.data.c_str(),MFRAME_pos.data,MFRAME_vel.data,MFRAME_eff.data,BLOCK.data.c_str(),BLOCK_pos.data,BLOCK_vel.data,BLOCK_eff.data);
  }
  
  return 0;
}