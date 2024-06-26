#ifndef NANOMAP_VISUALIZER_H
#define NANOMAP_VISUALIZER_H

#include <nanomap_ros/nanomap_types.h>
#include <ros/ros.h>
#include <visualization_msgs/Marker.h>
#include <visualization_msgs/MarkerArray.h>

class NanoMapVisualizer {
public:
  void Initialize(ros::NodeHandle &nh) {
    this->nh = nh;
    fov_pub = nh.advertise<visualization_msgs::Marker>("fov", 0);
    last_pose.setIdentity();
  }

  void SetLastPose(Matrix4 pose);
  void SetCameraInfo(const float& max_range, const int& width, const int& height,
                     const Matrix3 &K);

  void DrawFrustums(std::vector<Matrix4> edges);
  void PublishFovMarker(int fov_id, Vector3 body, Vector3 corner_1,
                        Vector3 corner_2, Vector3 corner_3, Vector3 corner_4,
                        bool color_in_fov);

private:
  Matrix4 last_pose;
  Matrix3 K;
  Matrix3 K_inv;
  int width;
  int height;
  float max_range;

  ros::NodeHandle nh;
  ros::Publisher fov_pub;
};

#endif