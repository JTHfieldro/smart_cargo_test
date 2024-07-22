// Auto-generated. Do not edit!

// (in-package smart_cargo_package.msg)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;

//-----------------------------------------------------------

class action_complete_msgs {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.time_stamp = null;
      this.receive_object = null;
      this.action_object = null;
      this.complete_action = null;
      this.error_code = null;
    }
    else {
      if (initObj.hasOwnProperty('time_stamp')) {
        this.time_stamp = initObj.time_stamp
      }
      else {
        this.time_stamp = {secs: 0, nsecs: 0};
      }
      if (initObj.hasOwnProperty('receive_object')) {
        this.receive_object = initObj.receive_object
      }
      else {
        this.receive_object = 0;
      }
      if (initObj.hasOwnProperty('action_object')) {
        this.action_object = initObj.action_object
      }
      else {
        this.action_object = 0;
      }
      if (initObj.hasOwnProperty('complete_action')) {
        this.complete_action = initObj.complete_action
      }
      else {
        this.complete_action = 0;
      }
      if (initObj.hasOwnProperty('error_code')) {
        this.error_code = initObj.error_code
      }
      else {
        this.error_code = 0;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type action_complete_msgs
    // Serialize message field [time_stamp]
    bufferOffset = _serializer.time(obj.time_stamp, buffer, bufferOffset);
    // Serialize message field [receive_object]
    bufferOffset = _serializer.int32(obj.receive_object, buffer, bufferOffset);
    // Serialize message field [action_object]
    bufferOffset = _serializer.int32(obj.action_object, buffer, bufferOffset);
    // Serialize message field [complete_action]
    bufferOffset = _serializer.int32(obj.complete_action, buffer, bufferOffset);
    // Serialize message field [error_code]
    bufferOffset = _serializer.int32(obj.error_code, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type action_complete_msgs
    let len;
    let data = new action_complete_msgs(null);
    // Deserialize message field [time_stamp]
    data.time_stamp = _deserializer.time(buffer, bufferOffset);
    // Deserialize message field [receive_object]
    data.receive_object = _deserializer.int32(buffer, bufferOffset);
    // Deserialize message field [action_object]
    data.action_object = _deserializer.int32(buffer, bufferOffset);
    // Deserialize message field [complete_action]
    data.complete_action = _deserializer.int32(buffer, bufferOffset);
    // Deserialize message field [error_code]
    data.error_code = _deserializer.int32(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    return 24;
  }

  static datatype() {
    // Returns string type for a message object
    return 'smart_cargo_package/action_complete_msgs';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '8cfdf36b4b872dd50c9838483632d5fd';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    time time_stamp       # Message 발행 시간 (ros::Time)
    int32 receive_object    # 수신 객체 H/W Index Enum   <----- 꼭 필요한지 생각해보자 
    int32 action_object    # 동작 객체 H/W Index Enum
    int32 complete_action  # 완료 동작 Action Index Enum (짝수만 와야 한다)
    int32 error_code       # Error-Code
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new action_complete_msgs(null);
    if (msg.time_stamp !== undefined) {
      resolved.time_stamp = msg.time_stamp;
    }
    else {
      resolved.time_stamp = {secs: 0, nsecs: 0}
    }

    if (msg.receive_object !== undefined) {
      resolved.receive_object = msg.receive_object;
    }
    else {
      resolved.receive_object = 0
    }

    if (msg.action_object !== undefined) {
      resolved.action_object = msg.action_object;
    }
    else {
      resolved.action_object = 0
    }

    if (msg.complete_action !== undefined) {
      resolved.complete_action = msg.complete_action;
    }
    else {
      resolved.complete_action = 0
    }

    if (msg.error_code !== undefined) {
      resolved.error_code = msg.error_code;
    }
    else {
      resolved.error_code = 0
    }

    return resolved;
    }
};

module.exports = action_complete_msgs;
