# WRS2020トンネル競技に出場するODENSチーム用のマスタアームをROSで使うnode
大阪電気通信大学 升谷研究室  
2021年9月 

## 概要



## 参考



## 導入

- Ubuntu 18.04，ROS Melodicは導入済みとする．

- 端末で以下を実行．
  ```
  sudo apt-get install python-catkin-tools
  cd ~  
  mkdir -p dyna_ws/src  
  cd wrs_ws  
  catkin init  
  cd src
  git clone https://github.com/HT16A086/dynamixel_ros_odens.git  
  cd ..    
  catkin build 
  ```

