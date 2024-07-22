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

class state_monitor {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.system_state = null;
      this.door_state = null;
      this.handler_state = null;
      this.docking_state = null;
      this.type = null;
    }
    else {
      if (initObj.hasOwnProperty('system_state')) {
        this.system_state = initObj.system_state
      }
      else {
        this.system_state = '';
      }
      if (initObj.hasOwnProperty('door_state')) {
        this.door_state = initObj.door_state
      }
      else {
        this.door_state = '';
      }
      if (initObj.hasOwnProperty('handler_state')) {
        this.handler_state = initObj.handler_state
      }
      else {
        this.handler_state = '';
      }
      if (initObj.hasOwnProperty('docking_state')) {
        this.docking_state = initObj.docking_state
      }
      else {
        this.docking_state = '';
      }
      if (initObj.hasOwnProperty('type')) {
        this.type = initObj.type
      }
      else {
        this.type = '';
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type state_monitor
    // Serialize message field [system_state]
    bufferOffset = _serializer.string(obj.system_state, buffer, bufferOffset);
    // Serialize message field [door_state]
    bufferOffset = _serializer.string(obj.door_state, buffer, bufferOffset);
    // Serialize message field [handler_state]
    bufferOffset = _serializer.string(obj.handler_state, buffer, bufferOffset);
    // Serialize message field [docking_state]
    bufferOffset = _serializer.string(obj.docking_state, buffer, bufferOffset);
    // Serialize message field [type]
    bufferOffset = _serializer.string(obj.type, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type state_monitor
    let len;
    let data = new state_monitor(null);
    // Deserialize message field [system_state]
    data.system_state = _deserializer.string(buffer, bufferOffset);
    // Deserialize message field [door_state]
    data.door_state = _deserializer.string(buffer, bufferOffset);
    // Deserialize message field [handler_state]
    data.handler_state = _deserializer.string(buffer, bufferOffset);
    // Deserialize message field [docking_state]
    data.docking_state = _deserializer.string(buffer, bufferOffset);
    // Deserialize message field [type]
    data.type = _deserializer.string(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    length += object.system_state.length;
    length += object.door_state.length;
    length += object.handler_state.length;
    length += object.docking_state.length;
    length += object.type.length;
    return length + 20;
  }

  static datatype() {
    // Returns string type for a message object
    return 'smart_cargo_package/state_monitor';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '155a94a5ff2117e15f117d9248317262';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    string system_state  # smart_cargo 현재 동작 상태
    string door_state    # 적재함 Door 현재 동작 상태
    string handler_state # Handler 현재 동작 상태
    string docking_state # IF_docking Message 수신 상태
    string type          # Message Object
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new state_monitor(null);
    if (msg.system_state !== undefined) {
      resolved.system_state = msg.system_state;
    }
    else {
      resolved.system_state = ''
    }

    if (msg.door_state !== undefined) {
      resolved.door_state = msg.door_state;
    }
    else {
      resolved.door_state = ''
    }

    if (msg.handler_state !== undefined) {
      resolved.handler_state = msg.handler_state;
    }
    else {
      resolved.handler_state = ''
    }

    if (msg.docking_state !== undefined) {
      resolved.docking_state = msg.docking_state;
    }
    else {
      resolved.docking_state = ''
    }

    if (msg.type !== undefined) {
      resolved.type = msg.type;
    }
    else {
      resolved.type = ''
    }

    return resolved;
    }
};

module.exports = state_monitor;
