/*
 * Copyright (C) 2012-2016 Open Source Robotics Foundation
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
*/
/*
 * Desc: Object disposal plugin
 * Author: Deanna Hood
 */
#ifndef _GAZEBO_OBJECT_DISPOSAL_PLUGIN_HH_
#define _GAZEBO_OBJECT_DISPOSAL_PLUGIN_HH_

#include <gazebo/common/Plugin.hh>
#include <gazebo/math/Pose.hh>
#include <gazebo/sensors/sensors.hh>
#include <gazebo/util/system.hh>

#include "SideContactPlugin.hh"

namespace gazebo
{
  /// \brief A plugin for a contact sensor attached to a model disposal unit.
  class GAZEBO_VISIBLE ObjectDisposalPlugin : public SideContactPlugin
  {
    /// \brief Constructor.
    public: ObjectDisposalPlugin();

    /// \brief Destructor.
    public: virtual ~ObjectDisposalPlugin();

    /// \brief Load the model plugin.
    /// \param[in] _model Pointer to the model that loaded this plugin.
    /// \param[in] _sdf SDF element that describes the plugin.
    public: virtual void Load(physics::ModelPtr _model, sdf::ElementPtr _sdf);

    /// \brief Callback that receives the world update event
    protected: void OnUpdate(const common::UpdateInfo &_info);

    /// \brief Act on models that are ontop of the sensor's link
    protected: void ActOnContactingModels();

    /// \brief Callback for state changes.
    protected: void OnActivation(ConstGzStringPtr &_msg);

    /// \brief If true, only delete models if their CoG is within the bounding box of the link
    protected: bool centerOfGravityCheck;

    /// \brief Whether or not models in contact will be deleted.
    protected: bool active = false;

    /// \brief Pose where the object will be teleported.
    protected: math::Pose disposalPose;

    /// \brief How many models have been removed.
    protected: int numRemovedModels = 0;

    /// \brief Node for communication.
    protected: transport::NodePtr node;

    /// \brief Subscription for activation topic.
    protected: transport::SubscriberPtr activationSub;

    /// \brief Publishers for closing box visuals.
    protected: std::map<std::string, transport::PublisherPtr> closeBoxPubMap;

    /// \brief Status of close box requests.
    protected: std::map<std::string, bool> boxClosedMap;
  };
}
#endif

