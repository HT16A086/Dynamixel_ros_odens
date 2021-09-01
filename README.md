# WRS2020トンネル競技に出場するODENSチーム用のマスタアームをROSで使うnode
大阪電気通信大学 升谷研究室  
2021年9月 

## 概要



## 参考



## 導入

- Ubuntu 18.04，ROS Melodicとhttps://github.com/MasutaniLab/choreonoid_ros_odensは導入済みとする．

- 端末で以下を実行．
  ```
  sudo apt-get install python-catkin-tools
  cd ~  
  mkdir -p dyna_ws/src  
  cd dyna_ws  
  catkin init  
  cd src
  git clone https://github.com/HT16A086/dynamixel_ros_odens.git  
  cd ..    
  catkin build 
  ```

## 動作確認
- USB2DynamixelをUSBポートに接続．
- 端末1：dynamixel_workbench_controllersを起動.
```
- roslaunch dynamixel_workbench_controllers dynamixel_controllers.launch.
```
- 端末2：choreonoidを起動.
  - AGXありの場合
    ```
    roslaunch choreonoid_ros_odens qr_a.launch
    ```
  - AGXなしの場合
    ```
    roslaunch choreonoid_ros_odens qr_s.launch
    ```
- 端末2：マスタスレーブ用プログラムを起動.
- ```
  rosrun dynamixel_ros_odens dynamixel2choreonoid
  ```
- 
