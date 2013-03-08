/*
 * Copyright (c) 2008, Willow Garage, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of the Willow Garage, Inc. nor the names of its
 *       contributors may be used to endorse or promote products derived from
 *       this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef RVIZ_ROBOT_MODEL_DISPLAY_H
#define RVIZ_ROBOT_MODEL_DISPLAY_H

#include "rviz/display.h"
#include <geometry_msgs/PoseStamped.h>

#include <flor_ocs_msgs/OCSTemplateList.h>
#include <flor_ocs_msgs/OCSTemplateUpdate.h>

#include <OGRE/OgreVector3.h>
#include "OGRE/OgreRoot.h"
#include "OGRE/OgreRenderSystem.h"
#include "OGRE/OgreRenderWindow.h"
#include "OGRE/OgreWindowEventUtilities.h"
#include "OGRE/OgreManualObject.h"
#include "OGRE/OgreEntity.h"
#include <OGRE/OgreSceneNode.h>

#include <map>
#include <vector>

namespace Ogre
{
class Entity;
class SceneNode;
}

namespace rviz
{
class Axes;
}

namespace rviz
{

class FloatProperty;
class Property;
class Robot;
class StringProperty;

/**
 * \class TemplateDisplayCustom
 * \brief Uses a robot xml description to display the pieces of a robot at the transforms broadcast by rosTF
 */
class TemplateDisplayCustom: public Display
{
Q_OBJECT
public:
  TemplateDisplayCustom();
  virtual ~TemplateDisplayCustom();

  // Overrides from Display
  virtual void onInitialize();
  virtual void update( float wall_dt, float ros_dt );
  virtual void fixedFrameChanged();
  virtual void reset();

  void clear();

  void processPoseChange(const geometry_msgs::PoseStamped::ConstPtr& pose);
  void processTemplateList(const flor_ocs_msgs::OCSTemplateList::ConstPtr& msg);

private Q_SLOTS:
  void updateVisualVisible();
  void updateCollisionVisible();
  void updateTfPrefix();
  void updateAlpha();
  void updateRobotDescription();

protected:
  /** @brief Loads a URDF from the ros-param named by our
   * "Robot Description" property, iterates through the links, and
   * loads any necessary models. */
  virtual void load();

  // overrides from Display
  virtual void onEnable();
  virtual void onDisable();

  bool has_new_transforms_;      ///< Callback sets this to tell our update function it needs to update the transforms

  float time_since_last_transform_;

  std::string robot_description_;

  Property* visual_enabled_property_;
  Property* collision_enabled_property_;
  FloatProperty* update_rate_property_;
  StringProperty* robot_description_property_;
  FloatProperty* alpha_property_;
  StringProperty* tf_prefix_property_;

private:
  void addTemplate(std::string path, Ogre::Vector3 pos, Ogre::Quaternion quat);

  ros::NodeHandle nh_;
  ros::Subscriber template_pose_sub_;
  ros::Subscriber template_list_sub_;

  std::vector<std::string> template_list_;
  std::vector<Ogre::SceneNode*> template_node_list_;

};

} // namespace rviz

#endif

